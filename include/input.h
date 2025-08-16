
#pragma once

#include <GLFW/glfw3.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;


class Keyboard {
public:
    int key = -1;
    int scancode = -1;
    int action = -1;
    int mods = 0;

    void set(int k, int s, int a, int m);
};

class Mouse {
public:
    int button = -1;
    int action = -1;
    int mods = 0;
    double xoffset = 0.0;
    double yoffset = 0.0;

    void set(int b, int a, int m);
    void set_scroll(double xoff, double yoff);
};

class Cursor {
public:
    double x = 0.0;
    double y = 0.0;

    void set(double xpos, double ypos);
};

extern Keyboard keyboard;
extern Mouse mouse;
extern Cursor cursor;

void bind_keyboard(py::module_& m);
void bind_mouse(py::module_& m);
void bind_cursor(py::module_& m);
void bind_keys(py::module_& m);
void bind_buttons(py::module_& m);
void bind_actions(py::module_& m);
void bind_mods(py::module_& m);
