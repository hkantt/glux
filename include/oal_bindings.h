
#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <stdexcept>

#include <AL/al.h>
#include <AL/alc.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

class OpenALContext {
    ALCdevice* device = nullptr;
    ALCcontext* context = nullptr;

public:
    OpenALContext();
    ~OpenALContext();

    std::string get_device_name();
    int create_source();
    int create_buffer();
    void load_audio(int buffer, const std::string& path);
    void play(int source, int buffer);
    void pause(int source);
    void resume(int source);
    void stop(int source);
    void rewind(int source);
    void set_looping(int source, bool loop);
    void set_gain(int source, float gain);
    void set_offset(int source, float seconds);
    float get_offset(int source);
    bool is_initial(int source);
    bool is_playing(int source);
    bool is_paused(int source);
    bool is_stopped(int source);
    void delete_source(int source);
    void delete_buffer(int buffer);
};

void bind_oal(py::module_& m);