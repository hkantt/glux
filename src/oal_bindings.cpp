
#include "oal_bindings.h"

#define STB_VORBIS_IMPLEMENTATION
#include "stb_vorbis.c"

#define DR_MP3_IMPLEMENTATION
#include "dr_mp3.h"


bool decode_mp3(const std::string& filename, std::vector<short>& samples, int& channels, int& sample_rate) {
    drmp3 mp3;
    if (!drmp3_init_file(&mp3, filename.c_str(), nullptr)) {
        return false;
    }

    sample_rate = mp3.sampleRate;
    channels = mp3.channels;

    drmp3_uint64 total_frames = drmp3_get_pcm_frame_count(&mp3);
    samples.resize(total_frames * channels);

    drmp3_read_pcm_frames_s16(&mp3, total_frames, samples.data());
    drmp3_uninit(&mp3);

    return true;
}

bool decode_wav(const std::string& filename, std::vector<short>& samples, int& channels, int& sample_rate) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) return false;

    char riff_header[12];
    file.read(riff_header, 12);
    if (std::strncmp(riff_header, "RIFF", 4) != 0 || std::strncmp(riff_header + 8, "WAVE", 4) != 0)
        return false;

    char chunk_id[4];
    uint32_t chunk_size;

    short audio_format = 0;
    short num_channels = 0;
    int sample_rate_ = 0;
    short bits_per_sample = 0;
    std::vector<char> pcm_data;

    while (file.read(chunk_id, 4)) {
        file.read(reinterpret_cast<char*>(&chunk_size), 4);

        if (std::strncmp(chunk_id, "fmt ", 4) == 0) {
            file.read(reinterpret_cast<char*>(&audio_format), 2);
            file.read(reinterpret_cast<char*>(&num_channels), 2);
            file.read(reinterpret_cast<char*>(&sample_rate_), 4);
            file.ignore(6); // byte rate + block align
            file.read(reinterpret_cast<char*>(&bits_per_sample), 2);
            file.ignore(chunk_size - 16); // skip any extra fmt bytes
        } else if (std::strncmp(chunk_id, "data", 4) == 0) {
            pcm_data.resize(chunk_size);
            file.read(pcm_data.data(), chunk_size);
        } else {
            file.ignore(chunk_size); // skip unknown chunks
        }
    }

    if (audio_format != 1 || bits_per_sample != 16) return false; // PCM only, 16-bit only

    int total_samples = pcm_data.size() / 2;
    samples.resize(total_samples);
    std::memcpy(samples.data(), pcm_data.data(), pcm_data.size());

    channels = num_channels;
    sample_rate = sample_rate_;
    return true;
}

bool decode_ogg(const std::string& filename, std::vector<short>& samples, int& channels, int& sample_rate) {
    int error;
    stb_vorbis* vorbis = stb_vorbis_open_filename(filename.c_str(), &error, nullptr);
    if (!vorbis) return false;

    stb_vorbis_info info = stb_vorbis_get_info(vorbis);
    channels = info.channels;
    sample_rate = info.sample_rate;

    int total_samples = stb_vorbis_stream_length_in_samples(vorbis);
    samples.resize(total_samples * channels);

    int actual_samples = stb_vorbis_get_samples_short_interleaved(vorbis, channels, samples.data(), samples.size());
    samples.resize(actual_samples * channels);

    stb_vorbis_close(vorbis);
    return true;
}


OpenALContext::OpenALContext() {
    device = alcOpenDevice(nullptr);
    if (!device) throw std::runtime_error("Failed to open OpenAL device");

    context = alcCreateContext(device, nullptr);
    if (!context || !alcMakeContextCurrent(context))
        throw std::runtime_error("Failed to create/make current OpenAL context");
}

OpenALContext::~OpenALContext() {
    if (context) {
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(context);
    }
    if (device) alcCloseDevice(device);
}

std::string OpenALContext::get_device_name() {
    return alcGetString(device, ALC_DEVICE_SPECIFIER);
}

int OpenALContext::create_source() {
    ALuint source;
    alGenSources(1, &source);
    return source;
}

int OpenALContext::create_buffer() {
    ALuint buffer;
    alGenBuffers(1, &buffer);
    return buffer;
}

void OpenALContext::load_audio(int buffer, const std::string& path) {
    std::vector<short> samples;
    int channels = 0, sample_rate = 0;

    std::string ext = path.substr(path.size() - 4);
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    if (ext == ".ogg") {
        if (!decode_ogg(path, samples, channels, sample_rate))
            throw std::runtime_error("Failed to decode OGG file: " + path);
    } else if (ext == ".wav") {
        if (!decode_wav(path, samples, channels, sample_rate))
            throw std::runtime_error("Failed to decode WAV file: " + path);
    } else if (ext == ".mp3") {
        if (!decode_mp3(path, samples, channels, sample_rate))
            throw std::runtime_error("Failed to decode MP3 file: " + path);
    } else {
        throw std::runtime_error("Unsupported audio format: " + path);
    }

    int format = (channels == 1) ? AL_FORMAT_MONO16 :
                 (channels == 2) ? AL_FORMAT_STEREO16 :
                 throw std::runtime_error("Unsupported channel count");

    alBufferData(buffer, format, samples.data(), samples.size() * sizeof(short), sample_rate);
}

void OpenALContext::play(int source, int buffer) {
    alSourcei(source, AL_BUFFER, buffer);
    alSourcePlay(source);
}

void OpenALContext::pause(int source) {
    alSourcePause(source);
}

void OpenALContext::resume(int source) {
    ALint state;
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    if (state == AL_PAUSED) {
        alSourcePlay(source);
    }
}

void OpenALContext::stop(int source) {
    alSourceStop(source);
}

void OpenALContext::rewind(int source) {
    alSourceRewind(source);
}

void OpenALContext::set_looping(int source, bool loop) {
    alSourcei(source, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
}

void OpenALContext::set_gain(int source, float gain) {
    alSourcef(source, AL_GAIN, gain);
}

void OpenALContext::set_offset(int source, float seconds) {
    alSourcef(source, AL_SEC_OFFSET, seconds);
}

float OpenALContext::get_offset(int source) {
    float offset;
    alGetSourcef(source, AL_SEC_OFFSET, &offset);
    return offset;
}

bool OpenALContext::is_initial(int source) {
    ALint state;
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    return state == AL_INITIAL;
}

bool OpenALContext::is_playing(int source) {
    ALint state;
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    return state == AL_PLAYING;
}

bool OpenALContext::is_paused(int source) {
    ALint state;
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    return state == AL_PAUSED;
}

bool OpenALContext::is_stopped(int source) {
    ALint state;
    alGetSourcei(source, AL_SOURCE_STATE, &state);
    return state == AL_STOPPED;
}

void OpenALContext::delete_source(int source) {
    alDeleteSources(1, reinterpret_cast<ALuint*>(&source));
}

void OpenALContext::delete_buffer(int buffer) {
    alDeleteBuffers(1, reinterpret_cast<ALuint*>(&buffer));
}

void bind_oal(py::module_& m) {
    py::class_<OpenALContext>(m, "Context")
        .def(py::init<>())
        .def("get_device_name", &OpenALContext::get_device_name)
        .def("create_source", &OpenALContext::create_source)
        .def("create_buffer", &OpenALContext::create_buffer)
        .def("load_audio", &OpenALContext::load_audio)
        .def("play", &OpenALContext::play)
        .def("pause", &OpenALContext::pause)
        .def("resume", &OpenALContext::resume)
        .def("stop", &OpenALContext::stop)
        .def("rewind", &OpenALContext::rewind)
        .def("set_looping", &OpenALContext::set_looping)
        .def("set_gain", &OpenALContext::set_gain)
        .def("set_offset", &OpenALContext::set_offset)
        .def("get_offset", &OpenALContext::get_offset)
        .def("is_initial", &OpenALContext::is_initial)
        .def("is_playing", &OpenALContext::is_playing)
        .def("is_paused", &OpenALContext::is_paused)
        .def("is_stopped", &OpenALContext::is_stopped)
        .def("delete_source", &OpenALContext::delete_source)
        .def("delete_buffer", &OpenALContext::delete_buffer);

    m.attr("AL_FORMAT_MONO16") = AL_FORMAT_MONO16;
    m.attr("AL_FORMAT_STEREO16") = AL_FORMAT_STEREO16;
}