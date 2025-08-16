
#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

void bind_imgui_window_flags(py::module_& m);
void bind_imgui_child_flags(py::module_& m);
void bind_imgui_item_flags(py::module_& m);
void bind_imgui_input_text_flags(py::module_& m);
void bind_imgui_tree_node_flags(py::module_& m);
void bind_imgui_popup_flags(py::module_& m);
void bind_imgui_selectable_flags(py::module_& m);
void bind_imgui_combo_flags(py::module_& m);
void bind_imgui_tab_bar_flags(py::module_& m);
void bind_imgui_tab_item_flags(py::module_& m);
void bind_imgui_focused_flags(py::module_& m);
void bind_imgui_hovered_flags(py::module_& m);
void bind_imgui_drag_drop_flags(py::module_& m);
void bind_imgui_input_flags(py::module_& m);
void bind_imgui_config_flags(py::module_& m);
void bind_imgui_button_flags(py::module_& m);
void bind_imgui_color_edit_flags(py::module_& m);
void bind_imgui_slider_flags(py::module_& m);
void bind_imgui_table_flags(py::module_& m);
void bind_imgui_table_column_flags(py::module_& m);
void bind_imgui_table_row_flags(py::module_& m);
void bind_imgui_multi_select_flags(py::module_& m);
void bind_imgui_draw_list_flags(py::module_& m);
void bind_imgui_font_atlas_flags(py::module_& m);
void bind_imgui_draw_flags(py::module_& m);
void bind_imgui_data_type(py::module_& m);
void bind_imgui_dir(py::module_& m);
void bind_imgui_sort_direction(py::module_& m);
void bind_imgui_key(py::module_& m);
void bind_imgui_col(py::module_& m);
void bind_imgui_style_var(py::module_& m);
void bind_imgui_mouse_button(py::module_& m);
void bind_imgui_mouse_cursor(py::module_& m);
void bind_imgui_cond(py::module_& m);
void bind_imgui_table_bg_target(py::module_& m);
void bind_imgui_selection_request_type(py::module_& m);

void bind_imgui_vecs(py::module_& m);
void bind_imgui_color(py::module_& m);
void bind_imgui_io(py::module_& m);
void bind_imgui_style(py::module_& m);
void bind_imgui_draw_list(py::module_& m);
void bind_imgui_viewport(py::module_& m);
void bind_imgui_font_config(py::module_& m);
void bind_imgui_font_glyph(py::module_& m);
void bind_imgui_font_glyph_ranges_builder(py::module_& m);
void bind_imgui_font_atlas_custom_rect(py::module_& m);
void bind_imgui_font_atlas(py::module_& m);
void bind_imgui_font(py::module_& m);

void bind_imgui_core(py::module_& m);