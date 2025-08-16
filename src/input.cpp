
#define EXPORT_KEY(name) m.attr(#name) = GLFW_KEY_##name
#define EXPORT_MOUSE_BUTTON(name) m.attr(#name) = GLFW_MOUSE_BUTTON_##name

#include "input.h"


Keyboard keyboard;
Mouse mouse;
Cursor cursor;

void Keyboard::set(int k, int s, int a, int m) {
    key = k;
    scancode = s;
    action = a;
    mods = m;
}

void Mouse::set(int b, int a, int m) {
    button = b;
    action = a;
    mods = m;
}

void Mouse::set_scroll(double xoff, double yoff) {
    xoffset = xoff;
    yoffset = yoff;
}

void Cursor::set(double xpos, double ypos) {
    x = xpos;
    y = ypos;
}

void bind_keyboard(py::module& m) {
    py::class_<Keyboard>(m, "Keyboard")
        .def_readonly("key", &Keyboard::key)
        .def_readonly("scancode", &Keyboard::scancode)
        .def_readonly("action", &Keyboard::action)
        .def_readonly("mods", &Keyboard::mods);
    m.attr("keyboard") = &keyboard;
}

void bind_mouse(py::module& m) {
    py::class_<Mouse>(m, "Mouse")
        .def_readonly("button", &Mouse::button)
        .def_readonly("action", &Mouse::action)
        .def_readonly("mods", &Mouse::mods)
        .def_readonly("xoffset", &Mouse::xoffset)
        .def_readonly("yoffset", &Mouse::yoffset);
    m.attr("mouse") = &mouse;
}

void bind_cursor(py::module& m) {
    py::class_<Cursor>(m, "Cursor")
        .def_readonly("x", &Cursor::x)
        .def_readonly("y", &Cursor::y);
    m.attr("cursor") = &cursor;
}

void bind_mods(py::module_& m) {
    m.attr("SHIFT") = GLFW_MOD_SHIFT;
    m.attr("CONTROL") = GLFW_MOD_CONTROL;
    m.attr("ALT") = GLFW_MOD_ALT;
    m.attr("SUPER") = GLFW_MOD_SUPER;
    m.attr("CAPS_LOCK") = GLFW_MOD_CAPS_LOCK;
    m.attr("NUM_LOCK") = GLFW_MOD_NUM_LOCK;
}

void bind_actions(py::module_& m) {
    m.attr("PRESS") = GLFW_PRESS;
    m.attr("RELEASE") = GLFW_RELEASE;
    m.attr("REPEAT") = GLFW_REPEAT;
}

void bind_keys(py::module_& m) {
    EXPORT_KEY(SPACE);
    EXPORT_KEY(APOSTROPHE);
    EXPORT_KEY(COMMA);
    EXPORT_KEY(MINUS);
    EXPORT_KEY(PERIOD);
    EXPORT_KEY(SLASH);
    EXPORT_KEY(0);
    EXPORT_KEY(1);
    EXPORT_KEY(2);
    EXPORT_KEY(3);
    EXPORT_KEY(4);
    EXPORT_KEY(5);
    EXPORT_KEY(6);
    EXPORT_KEY(7);
    EXPORT_KEY(8);
    EXPORT_KEY(9);
    EXPORT_KEY(SEMICOLON);
    EXPORT_KEY(EQUAL);
    EXPORT_KEY(A);
    EXPORT_KEY(B);
    EXPORT_KEY(C);
    EXPORT_KEY(D);
    EXPORT_KEY(E);
    EXPORT_KEY(F);
    EXPORT_KEY(G);
    EXPORT_KEY(H);
    EXPORT_KEY(I);
    EXPORT_KEY(J);
    EXPORT_KEY(K);
    EXPORT_KEY(L);
    EXPORT_KEY(M);
    EXPORT_KEY(N);
    EXPORT_KEY(O);
    EXPORT_KEY(P);
    EXPORT_KEY(Q);
    EXPORT_KEY(R);
    EXPORT_KEY(S);
    EXPORT_KEY(T);
    EXPORT_KEY(U);
    EXPORT_KEY(V);
    EXPORT_KEY(W);
    EXPORT_KEY(X);
    EXPORT_KEY(Y);
    EXPORT_KEY(Z);
    EXPORT_KEY(LEFT_BRACKET);
    EXPORT_KEY(BACKSLASH);
    EXPORT_KEY(RIGHT_BRACKET);
    EXPORT_KEY(GRAVE_ACCENT);
    EXPORT_KEY(WORLD_1);
    EXPORT_KEY(WORLD_2);
    EXPORT_KEY(ESCAPE);
    EXPORT_KEY(ENTER);
    EXPORT_KEY(TAB);
    EXPORT_KEY(BACKSPACE);
    EXPORT_KEY(INSERT);
    EXPORT_KEY(DELETE);
    EXPORT_KEY(RIGHT);
    EXPORT_KEY(LEFT);
    EXPORT_KEY(DOWN);
    EXPORT_KEY(UP);
    EXPORT_KEY(PAGE_UP);
    EXPORT_KEY(PAGE_DOWN);
    EXPORT_KEY(HOME);
    EXPORT_KEY(END);
    EXPORT_KEY(CAPS_LOCK);
    EXPORT_KEY(SCROLL_LOCK);
    EXPORT_KEY(NUM_LOCK);
    EXPORT_KEY(PRINT_SCREEN);
    EXPORT_KEY(PAUSE);
    EXPORT_KEY(F1);
    EXPORT_KEY(F2);
    EXPORT_KEY(F3);
    EXPORT_KEY(F4);
    EXPORT_KEY(F5);
    EXPORT_KEY(F6);
    EXPORT_KEY(F7);
    EXPORT_KEY(F8);
    EXPORT_KEY(F9);
    EXPORT_KEY(F10);
    EXPORT_KEY(F11);
    EXPORT_KEY(F12);
    EXPORT_KEY(F13);
    EXPORT_KEY(F14);
    EXPORT_KEY(F15);
    EXPORT_KEY(F16);
    EXPORT_KEY(F17);
    EXPORT_KEY(F18);
    EXPORT_KEY(F19);
    EXPORT_KEY(F20);
    EXPORT_KEY(F21);
    EXPORT_KEY(F22);
    EXPORT_KEY(F23);
    EXPORT_KEY(F24);
    EXPORT_KEY(F25);
    EXPORT_KEY(KP_0);
    EXPORT_KEY(KP_1);
    EXPORT_KEY(KP_2);
    EXPORT_KEY(KP_3);
    EXPORT_KEY(KP_4);
    EXPORT_KEY(KP_5);
    EXPORT_KEY(KP_6);
    EXPORT_KEY(KP_7);
    EXPORT_KEY(KP_8);
    EXPORT_KEY(KP_9);
    EXPORT_KEY(KP_DECIMAL);
    EXPORT_KEY(KP_DIVIDE);
    EXPORT_KEY(KP_MULTIPLY);
    EXPORT_KEY(KP_SUBTRACT);
    EXPORT_KEY(KP_ADD);
    EXPORT_KEY(KP_ENTER);
    EXPORT_KEY(KP_EQUAL);
    EXPORT_KEY(LEFT_SHIFT);
    EXPORT_KEY(LEFT_CONTROL);
    EXPORT_KEY(LEFT_ALT);
    EXPORT_KEY(LEFT_SUPER);
    EXPORT_KEY(RIGHT_SHIFT);
    EXPORT_KEY(RIGHT_CONTROL);
    EXPORT_KEY(RIGHT_ALT);
    EXPORT_KEY(RIGHT_SUPER);
    EXPORT_KEY(MENU);
}

void bind_buttons(py::module_& m) {
    EXPORT_MOUSE_BUTTON(1);
    EXPORT_MOUSE_BUTTON(2);
    EXPORT_MOUSE_BUTTON(3);
    EXPORT_MOUSE_BUTTON(4);
    EXPORT_MOUSE_BUTTON(5);
    EXPORT_MOUSE_BUTTON(6);
    EXPORT_MOUSE_BUTTON(7);
    EXPORT_MOUSE_BUTTON(8);
    EXPORT_MOUSE_BUTTON(LEFT);
    EXPORT_MOUSE_BUTTON(RIGHT);
    EXPORT_MOUSE_BUTTON(MIDDLE);
}