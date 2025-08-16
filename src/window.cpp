
#include "window.h"
#include "input.h"


namespace py = pybind11;

int window_width = 800;
int window_height = 600;
bool y_up = true;
int gl_ver_major = 3;
int gl_ver_minor = 3;
bool vsync = true;
std::string window_title = "GLUX";
std::function<void()> events_fn = []() {};
std::function<void()> process_fn = []() {};
std::function<void()> render_fn = []() {};
std::function<void()> render_ui_fn = []() {};
GLFWwindow* window = nullptr;

void set_window_size(int width, int height) {
    window_width = width;
    window_height = height;
    if (window) {
        glfwSetWindowSize(window, width, height);
    }
}

void set_gl_version(int major, int minor) {
    gl_ver_major = major;
    gl_ver_minor = minor;
}

std::pair<int, int> get_window_size() {
    if (window) {
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        return {width, height};
    }
    return {window_width, window_height};
}

void set_window_title(const std::string& title) {
    window_title = title;
    if (window) {
        glfwSetWindowTitle(window, window_title.c_str());
    }
}

void set_vsync(bool value) {
    vsync = value;
    if (window) {
        glfwSwapInterval(static_cast<int>(vsync));
    }
}

void set_coordinate_system(const std::string& system){
    if (system == "y_up"){
        y_up = true;
    }
    if (system == "y_down"){
        y_up = false;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    window_width = width;
    window_height = height;
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    keyboard.set(key, scancode, action, mods);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    mouse.set(button, action, mods);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    mouse.set_scroll(xoffset, yoffset);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    if (y_up){
        cursor.set(xpos, window_height - ypos - 1);
    }
    else {
        cursor.set(xpos, ypos);
    }
}

void init() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_ver_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_ver_minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(window_width, window_height, window_title.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(static_cast<int>(vsync));

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);

    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void run() {
    while (!glfwWindowShouldClose(window)) {
        events_fn();
        process_fn();
        render_fn();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        render_ui_fn();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        keyboard.key = -1;
        keyboard.scancode = -1;
        keyboard.action = -1;
        keyboard.mods = 0;
        mouse.button = -1;
        mouse.action = -1;
        mouse.mods = 0;
        mouse.xoffset = 0.0;
        mouse.yoffset = 0.0;
        glfwPollEvents();
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}