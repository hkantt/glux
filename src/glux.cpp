
#include "window.h"
#include "input.h"
#include "imgui_bindings.h"
#include "oal_bindings.h"

namespace py = pybind11;

void set_events_callback(py::function f) { events_fn = f; }
void set_process_callback(py::function f) { process_fn = f; }
void set_render_callback(py::function f)  { render_fn = f; }
void set_render_ui_callback(py::function f)  { render_ui_fn = f; }

PYBIND11_MODULE(glux, m) {

    // Window Bindings
    m.def("init", &init);
    m.def("run", &run);
    m.def("set_events_callback", &set_events_callback);
    m.def("set_process_callback", &set_process_callback);
    m.def("set_render_callback", &set_render_callback);
    m.def("set_render_ui_callback", &set_render_ui_callback);
    m.def("set_window_size", &set_window_size);
    m.def("set_window_title", &set_window_title);
    m.def("set_gl_version", &set_gl_version);
    m.def("set_vsync", &set_vsync);
    m.def("set_coordinate_system", &set_coordinate_system);
    m.def("get_window_size", &get_window_size);

    // Input Bindings
    bind_keyboard(m);
    bind_mouse(m);
    bind_cursor(m);
    py::module_ keys = m.def_submodule("keys");
    py::module_ buttons = m.def_submodule("buttons");
    py::module_ actions = m.def_submodule("actions");
    py::module_ mods = m.def_submodule("mods");
    py::module_ scancodes = m.def_submodule("scancodes");
    bind_keys(keys);
    bind_buttons(buttons);
    bind_actions(actions);
    bind_mods(mods);
    scancodes.attr("KEY_UNKNOWN") = GLFW_KEY_UNKNOWN;

    // OpenAL Soft Bindings
    py::module_ oal = m.def_submodule("oal", "OpenAL Soft bindings");
    bind_oal(oal);

    // ImGui Bindings
    py::module_ imgui = m.def_submodule("imgui", "Dear ImGui bindings");
    
    // Flag Bindings
    bind_imgui_window_flags(imgui);
    bind_imgui_child_flags(imgui);
    bind_imgui_item_flags(imgui);
    bind_imgui_input_text_flags(imgui);
    bind_imgui_tree_node_flags(imgui);
    bind_imgui_popup_flags(imgui);
    bind_imgui_selectable_flags(imgui);
    bind_imgui_combo_flags(imgui);
    bind_imgui_tab_bar_flags(imgui);
    bind_imgui_tab_item_flags(imgui);
    bind_imgui_focused_flags(imgui);
    bind_imgui_hovered_flags(imgui);
    bind_imgui_drag_drop_flags(imgui);
    bind_imgui_input_flags(imgui);
    bind_imgui_config_flags(imgui);
    bind_imgui_button_flags(imgui);
    bind_imgui_color_edit_flags(imgui);
    bind_imgui_slider_flags(imgui);
    bind_imgui_table_flags(imgui);
    bind_imgui_table_column_flags(imgui);
    bind_imgui_table_row_flags(imgui);
    bind_imgui_multi_select_flags(imgui);
    bind_imgui_draw_list_flags(imgui);
    bind_imgui_font_atlas_flags(imgui);
    bind_imgui_draw_flags(imgui);
    bind_imgui_data_type(imgui);
    bind_imgui_dir(imgui);
    bind_imgui_sort_direction(imgui);
    bind_imgui_key(imgui);
    bind_imgui_col(imgui);
    bind_imgui_style_var(imgui);
    bind_imgui_mouse_button(imgui);
    bind_imgui_mouse_cursor(imgui);
    bind_imgui_cond(imgui);
    bind_imgui_table_bg_target(imgui);
    bind_imgui_selection_request_type(imgui);

    // Struct Bindings
    bind_imgui_vecs(imgui);
    bind_imgui_color(imgui);
    bind_imgui_io(imgui);
    bind_imgui_style(imgui);
    bind_imgui_draw_list(imgui);
    bind_imgui_viewport(imgui);
    bind_imgui_font_config(imgui);
    bind_imgui_font_glyph(imgui);
    bind_imgui_font_glyph_ranges_builder(imgui);
    bind_imgui_font_atlas_custom_rect(imgui);
    bind_imgui_font_atlas(imgui);
    bind_imgui_font(imgui);

    // Function Bindings
    bind_imgui_core(imgui);
}