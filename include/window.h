
#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <pybind11/pybind11.h>
#include <functional>
#include <string>
#include <iostream>


extern int window_width;
extern int window_height;
extern bool y_up;
extern int gl_ver_major;
extern int gl_ver_minor;
extern bool vsync;
extern std::string window_title;
extern std::function<void()> events_fn;
extern std::function<void()> process_fn;
extern std::function<void()> render_fn;
extern std::function<void()> render_ui_fn;
extern GLFWwindow* window;

void set_window_size(int width, int height);
void set_gl_version(int major, int minor);
void set_vsync(bool value);
std::pair<int, int> get_window_size();
void set_window_title(const std::string& title);
void set_coordinate_system(const std::string& system);
void init();
void run();