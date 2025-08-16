
#include "imgui_bindings.h"


void bind_imgui_vecs(py::module_& m) {
    py::class_<ImVec2>(m, "Vec2")
        .def(py::init<float, float>(), py::arg("x") = 0.0f, py::arg("y") = 0.0f)
        .def_readwrite("x", &ImVec2::x)
        .def_readwrite("y", &ImVec2::y);

    py::class_<ImVec4>(m, "Vec4")
        .def(py::init<float, float, float, float>(), py::arg("x") = 0.0f, py::arg("y") = 0.0f, py::arg("z") = 0.0f, py::arg("w") = 0.0f)
        .def_readwrite("x", &ImVec4::x)
        .def_readwrite("y", &ImVec4::y)
        .def_readwrite("z", &ImVec4::z)
        .def_readwrite("w", &ImVec4::w);
}

void bind_imgui_color(py::module_& m) {
    py::class_<ImColor>(m, "Color")
        .def(py::init<float, float, float, float>(), py::arg("r"), py::arg("g"), py::arg("b"), py::arg("a") = 1.0f)
        .def(py::init<const ImVec4&>())
        .def("to_vec4", [](const ImColor& color) {
        return ImVec4(color.Value.x, color.Value.y, color.Value.z, color.Value.w);
            })
        .def_readwrite("value", &ImColor::Value);  // Optional: expose raw value
}

void bind_imgui_io(py::module_& m) {
    py::class_<ImGuiIO>(m, "IO")
        .def_readwrite("display_size", &ImGuiIO::DisplaySize)
        .def_readwrite("delta_time", &ImGuiIO::DeltaTime)
        .def_readwrite("ini_saving_rate", &ImGuiIO::IniSavingRate)
        .def_readwrite("font_global_scale", &ImGuiIO::FontGlobalScale)
        .def_readwrite("display_framebuffer_scale", &ImGuiIO::DisplayFramebufferScale)
        .def_readwrite("mouse_draw_cursor", &ImGuiIO::MouseDrawCursor)
        .def_readwrite("mouse_wheel", &ImGuiIO::MouseWheel)
        .def_readwrite("mouse_wheel_h", &ImGuiIO::MouseWheelH)
        .def_readwrite("key_ctrl", &ImGuiIO::KeyCtrl)
        .def_readwrite("key_shift", &ImGuiIO::KeyShift)
        .def_readwrite("key_alt", &ImGuiIO::KeyAlt)
        .def_readwrite("key_super", &ImGuiIO::KeySuper)
        .def_readwrite("want_set_mouse_pos", &ImGuiIO::WantSetMousePos)

        .def_readwrite("config_flags", &ImGuiIO::ConfigFlags)
        .def_readwrite("backend_flags", &ImGuiIO::BackendFlags)
        .def_readwrite("config_nav_swap_gamepad_buttons", &ImGuiIO::ConfigNavSwapGamepadButtons)
        .def_readwrite("config_nav_move_set_mouse_pos", &ImGuiIO::ConfigNavMoveSetMousePos)
        .def_readwrite("config_nav_capture_keyboard", &ImGuiIO::ConfigNavCaptureKeyboard)
        .def_readwrite("config_nav_escape_clear_focus_item", &ImGuiIO::ConfigNavEscapeClearFocusItem)
        .def_readwrite("config_nav_escape_clear_focus_window", &ImGuiIO::ConfigNavEscapeClearFocusWindow)
        .def_readwrite("config_nav_cursor_visible_auto", &ImGuiIO::ConfigNavCursorVisibleAuto)
        .def_readwrite("config_nav_cursor_visible_always", &ImGuiIO::ConfigNavCursorVisibleAlways)

        .def_readwrite("config_input_trickle_event_queue", &ImGuiIO::ConfigInputTrickleEventQueue)
        .def_readwrite("config_input_text_cursor_blink", &ImGuiIO::ConfigInputTextCursorBlink)
        .def_readwrite("config_input_text_enter_keep_active", &ImGuiIO::ConfigInputTextEnterKeepActive)
        .def_readwrite("config_drag_click_to_input_text", &ImGuiIO::ConfigDragClickToInputText)
        .def_readwrite("config_windows_resize_from_edges", &ImGuiIO::ConfigWindowsResizeFromEdges)
        .def_readwrite("config_windows_move_from_title_bar_only", &ImGuiIO::ConfigWindowsMoveFromTitleBarOnly)
        .def_readwrite("config_scrollbar_scroll_by_page", &ImGuiIO::ConfigScrollbarScrollByPage)

        .def_readwrite("mouse_double_click_time", &ImGuiIO::MouseDoubleClickTime)
        .def_readwrite("mouse_double_click_max_dist", &ImGuiIO::MouseDoubleClickMaxDist)
        .def_readwrite("mouse_drag_threshold", &ImGuiIO::MouseDragThreshold)
        .def_readwrite("key_repeat_delay", &ImGuiIO::KeyRepeatDelay)
        .def_readwrite("key_repeat_rate", &ImGuiIO::KeyRepeatRate)

        .def_property("framerate", [](const ImGuiIO& io) { return io.Framerate; }, nullptr)
        .def_property("want_capture_mouse", [](const ImGuiIO& io) { return io.WantCaptureMouse; }, nullptr)
        .def_property("want_capture_keyboard", [](const ImGuiIO& io) { return io.WantCaptureKeyboard; }, nullptr)
        .def_property("want_text_input", [](const ImGuiIO& io) { return io.WantTextInput; }, nullptr)
        .def_property("nav_active", [](const ImGuiIO& io) { return io.NavActive; }, nullptr)
        .def_property("nav_visible", [](const ImGuiIO& io) { return io.NavVisible; }, nullptr)
        .def_property("font_default",
            [](ImGuiIO& io) -> ImFont* {
                return io.FontDefault;
            },
            [](ImGuiIO& io, ImFont* font) {
                io.FontDefault = font;
            },
            py::return_value_policy::reference)
        .def_property_readonly("fonts", [](ImGuiIO& io) -> ImFontAtlas& {
                return *io.Fonts;
            }, py::return_value_policy::reference)

        .def_property("mouse_down",
            [](const ImGuiIO& io) {
                return std::vector<bool>(io.MouseDown, io.MouseDown + IM_ARRAYSIZE(io.MouseDown));
            },
            [](ImGuiIO& io, const std::vector<bool>& v) {
                for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown) && i < (int)v.size(); ++i)
                    io.MouseDown[i] = v[i];
            })

        .def_property("ini_filename",
            [](ImGuiIO& io) { return io.IniFilename ? std::string(io.IniFilename) : ""; },
            [](ImGuiIO& io, const std::string& s) {
                io.IniFilename = s.empty() ? nullptr : strdup(s.c_str());
            })

        .def_property("log_filename",
            [](ImGuiIO& io) { return io.LogFilename ? std::string(io.LogFilename) : ""; },
            [](ImGuiIO& io, const std::string& s) {
                io.LogFilename = s.empty() ? nullptr : strdup(s.c_str());
            })
        ;

    m.def("get_io", []() -> ImGuiIO& {
        return ImGui::GetIO();
    }, py::return_value_policy::reference);
}

void bind_imgui_style(py::module_& m) {
    py::class_<ImGuiStyle>(m, "Style")
        .def_readwrite("alpha", &ImGuiStyle::Alpha)
        .def_readwrite("disabled_alpha", &ImGuiStyle::DisabledAlpha)
        .def_readwrite("window_rounding", &ImGuiStyle::WindowRounding)
        .def_readwrite("window_border_size", &ImGuiStyle::WindowBorderSize)
        .def_readwrite("window_border_hover_padding", &ImGuiStyle::WindowBorderHoverPadding)
        .def_readwrite("child_rounding", &ImGuiStyle::ChildRounding)
        .def_readwrite("child_border_size", &ImGuiStyle::ChildBorderSize)
        .def_readwrite("popup_rounding", &ImGuiStyle::PopupRounding)
        .def_readwrite("popup_border_size", &ImGuiStyle::PopupBorderSize)
        .def_readwrite("frame_rounding", &ImGuiStyle::FrameRounding)
        .def_readwrite("frame_border_size", &ImGuiStyle::FrameBorderSize)
        .def_readwrite("indent_spacing", &ImGuiStyle::IndentSpacing)
        .def_readwrite("columns_min_spacing", &ImGuiStyle::ColumnsMinSpacing)
        .def_readwrite("scrollbar_size", &ImGuiStyle::ScrollbarSize)
        .def_readwrite("scrollbar_rounding", &ImGuiStyle::ScrollbarRounding)
        .def_readwrite("grab_min_size", &ImGuiStyle::GrabMinSize)
        .def_readwrite("grab_rounding", &ImGuiStyle::GrabRounding)
        .def_readwrite("log_slider_deadzone", &ImGuiStyle::LogSliderDeadzone)
        .def_readwrite("image_border_size", &ImGuiStyle::ImageBorderSize)
        .def_readwrite("tab_rounding", &ImGuiStyle::TabRounding)
        .def_readwrite("tab_border_size", &ImGuiStyle::TabBorderSize)
        .def_readwrite("tab_close_button_min_width_selected", &ImGuiStyle::TabCloseButtonMinWidthSelected)
        .def_readwrite("tab_close_button_min_width_unselected", &ImGuiStyle::TabCloseButtonMinWidthUnselected)
        .def_readwrite("tab_bar_border_size", &ImGuiStyle::TabBarBorderSize)
        .def_readwrite("tab_bar_overline_size", &ImGuiStyle::TabBarOverlineSize)
        .def_readwrite("table_angled_headers_angle", &ImGuiStyle::TableAngledHeadersAngle)
        .def_readwrite("tree_lines_size", &ImGuiStyle::TreeLinesSize)
        .def_readwrite("tree_lines_rounding", &ImGuiStyle::TreeLinesRounding)
        .def_readwrite("separator_text_border_size", &ImGuiStyle::SeparatorTextBorderSize)
        .def_readwrite("mouse_cursor_scale", &ImGuiStyle::MouseCursorScale)
        .def_readwrite("curve_tessellation_tol", &ImGuiStyle::CurveTessellationTol)
        .def_readwrite("circle_tessellation_max_error", &ImGuiStyle::CircleTessellationMaxError)
        .def_readwrite("hover_stationary_delay", &ImGuiStyle::HoverStationaryDelay)
        .def_readwrite("hover_delay_short", &ImGuiStyle::HoverDelayShort)
        .def_readwrite("hover_delay_normal", &ImGuiStyle::HoverDelayNormal)

        .def_readwrite("anti_aliased_lines", &ImGuiStyle::AntiAliasedLines)
        .def_readwrite("anti_aliased_lines_use_tex", &ImGuiStyle::AntiAliasedLinesUseTex)
        .def_readwrite("anti_aliased_fill", &ImGuiStyle::AntiAliasedFill)

        .def_readwrite("window_padding", &ImGuiStyle::WindowPadding)
        .def_readwrite("window_min_size", &ImGuiStyle::WindowMinSize)
        .def_readwrite("window_title_align", &ImGuiStyle::WindowTitleAlign)
        .def_readwrite("frame_padding", &ImGuiStyle::FramePadding)
        .def_readwrite("item_spacing", &ImGuiStyle::ItemSpacing)
        .def_readwrite("item_inner_spacing", &ImGuiStyle::ItemInnerSpacing)
        .def_readwrite("cell_padding", &ImGuiStyle::CellPadding)
        .def_readwrite("touch_extra_padding", &ImGuiStyle::TouchExtraPadding)
        .def_readwrite("table_angled_headers_text_align", &ImGuiStyle::TableAngledHeadersTextAlign)
        .def_readwrite("button_text_align", &ImGuiStyle::ButtonTextAlign)
        .def_readwrite("selectable_text_align", &ImGuiStyle::SelectableTextAlign)
        .def_readwrite("separator_text_align", &ImGuiStyle::SeparatorTextAlign)
        .def_readwrite("separator_text_padding", &ImGuiStyle::SeparatorTextPadding)
        .def_readwrite("display_window_padding", &ImGuiStyle::DisplayWindowPadding)
        .def_readwrite("display_safe_area_padding", &ImGuiStyle::DisplaySafeAreaPadding)

        .def_readwrite("window_menu_button_position", &ImGuiStyle::WindowMenuButtonPosition)
        .def_readwrite("color_button_position", &ImGuiStyle::ColorButtonPosition)
        .def_readwrite("tree_lines_flags", &ImGuiStyle::TreeLinesFlags)
        .def_readwrite("hover_flags_for_tooltip_mouse", &ImGuiStyle::HoverFlagsForTooltipMouse)
        .def_readwrite("hover_flags_for_tooltip_nav", &ImGuiStyle::HoverFlagsForTooltipNav)

        .def_property("colors",
            [](ImGuiStyle& style) {
                return std::vector<ImVec4>(style.Colors, style.Colors + ImGuiCol_COUNT);
            },
            [](ImGuiStyle& style, const std::vector<ImVec4>& colors) {
                for (int i = 0; i < ImGuiCol_COUNT && i < (int)colors.size(); ++i)
                    style.Colors[i] = colors[i];
            })

        .def("scale_all_sizes", &ImGuiStyle::ScaleAllSizes)
        ;
        
    m.def("get_style", []() -> ImGuiStyle& {
        return ImGui::GetStyle();
    }, py::return_value_policy::reference);
}

void bind_imgui_draw_list(py::module_& m) {
    py::class_<ImDrawList>(m, "DrawList")
        .def("add_line", &ImDrawList::AddLine, py::arg("p1"), py::arg("p2"), py::arg("col"), py::arg("thickness") = 1.0f)
        .def("add_rect", &ImDrawList::AddRect, py::arg("p_min"), py::arg("p_max"), py::arg("col"), py::arg("rounding") = 0.0f, py::arg("flags") = 0, py::arg("thickness") = 1.0f)
        .def("add_rect_filled", &ImDrawList::AddRectFilled, py::arg("p_min"), py::arg("p_max"), py::arg("col"), py::arg("rounding") = 0.0f, py::arg("flags") = 0)
        .def("add_circle", &ImDrawList::AddCircle, py::arg("center"), py::arg("radius"), py::arg("col"), py::arg("num_segments") = 0, py::arg("thickness") = 1.0f)
        .def("add_circle_filled", &ImDrawList::AddCircleFilled, py::arg("center"), py::arg("radius"), py::arg("col"), py::arg("num_segments") = 0)
        .def("add_triangle", &ImDrawList::AddTriangle, py::arg("p1"), py::arg("p2"), py::arg("p3"), py::arg("col"), py::arg("thickness") = 1.0f)
        .def("add_triangle_filled", &ImDrawList::AddTriangleFilled, py::arg("p1"), py::arg("p2"), py::arg("p3"), py::arg("col"))
        .def("add_ngon", &ImDrawList::AddNgon, py::arg("center"), py::arg("radius"), py::arg("col"), py::arg("num_segments"), py::arg("thickness") = 1.0f)
        .def("add_ngon_filled", &ImDrawList::AddNgonFilled, py::arg("center"), py::arg("radius"), py::arg("col"), py::arg("num_segments"))
        .def("add_quad", &ImDrawList::AddQuad, py::arg("p1"), py::arg("p2"), py::arg("p3"), py::arg("p4"), py::arg("col"), py::arg("thickness") = 1.0f)
        .def("add_quad_filled", &ImDrawList::AddQuadFilled, py::arg("p1"), py::arg("p2"), py::arg("p3"), py::arg("p4"), py::arg("col"))

        .def("add_text", [](ImDrawList& self, const ImVec2& pos, ImU32 col, const std::string& text) {
            self.AddText(pos, col, text.c_str());
        }, py::arg("pos"), py::arg("col"), py::arg("text"))

        .def("add_bezier_cubic", &ImDrawList::AddBezierCubic, py::arg("p1"), py::arg("p2"), py::arg("p3"), py::arg("p4"), py::arg("col"), py::arg("thickness"), py::arg("num_segments") = 0)
        .def("add_bezier_quadratic", &ImDrawList::AddBezierQuadratic, py::arg("p1"), py::arg("p2"), py::arg("p3"), py::arg("col"), py::arg("thickness"), py::arg("num_segments") = 0)

        .def("push_clip_rect", &ImDrawList::PushClipRect, py::arg("min"), py::arg("max"), py::arg("intersect_with_current") = false)
        .def("pop_clip_rect", &ImDrawList::PopClipRect)
        .def("get_clip_rect_min", &ImDrawList::GetClipRectMin)
        .def("get_clip_rect_max", &ImDrawList::GetClipRectMax)

        .def("push_texture_id", &ImDrawList::PushTextureID)
        .def("pop_texture_id", &ImDrawList::PopTextureID)

        .def("path_clear", &ImDrawList::PathClear)
        .def("path_line_to", &ImDrawList::PathLineTo)
        .def("path_fill_convex", &ImDrawList::PathFillConvex)
        .def("path_stroke", &ImDrawList::PathStroke, py::arg("col"), py::arg("flags") = 0, py::arg("thickness") = 1.0f)

        .def_readwrite("flags", &ImDrawList::Flags)

        .def("clone_output", &ImDrawList::CloneOutput, py::return_value_policy::reference)
        ;
}

void bind_imgui_viewport(py::module_& m) {
    py::class_<ImGuiViewport>(m, "Viewport")
        .def_readonly("id", &ImGuiViewport::ID)
        .def_readonly("flags", &ImGuiViewport::Flags)

        .def_readwrite("pos", &ImGuiViewport::Pos)
        .def_readwrite("size", &ImGuiViewport::Size)
        .def_readwrite("work_pos", &ImGuiViewport::WorkPos)
        .def_readwrite("work_size", &ImGuiViewport::WorkSize)

        .def_readonly("platform_handle", &ImGuiViewport::PlatformHandle)
        .def_readonly("platform_handle_raw", &ImGuiViewport::PlatformHandleRaw)

        .def("get_center", &ImGuiViewport::GetCenter)
        .def("get_work_center", &ImGuiViewport::GetWorkCenter)
        ;
}

void bind_imgui_font_config(py::module_& m) {
    py::class_<ImFontConfig>(m, "FontConfig")
        .def(py::init<>())
        .def_readwrite("font_data", &ImFontConfig::FontData)
        .def_readwrite("font_data_size", &ImFontConfig::FontDataSize)
        .def_readwrite("font_data_owned_by_atlas", &ImFontConfig::FontDataOwnedByAtlas)
        .def_readwrite("merge_mode", &ImFontConfig::MergeMode)
        .def_readwrite("pixel_snap_h", &ImFontConfig::PixelSnapH)
        .def_readwrite("font_no", &ImFontConfig::FontNo)
        .def_readwrite("oversample_h", &ImFontConfig::OversampleH)
        .def_readwrite("oversample_v", &ImFontConfig::OversampleV)
        .def_readwrite("size_pixels", &ImFontConfig::SizePixels)
        .def_readwrite("glyph_offset", &ImFontConfig::GlyphOffset)
        .def_readwrite("glyph_ranges", &ImFontConfig::GlyphRanges)
        .def_readwrite("glyph_min_advance_x", &ImFontConfig::GlyphMinAdvanceX)
        .def_readwrite("glyph_max_advance_x", &ImFontConfig::GlyphMaxAdvanceX)
        .def_readwrite("glyph_extra_advance_x", &ImFontConfig::GlyphExtraAdvanceX)
        .def_readwrite("font_builder_flags", &ImFontConfig::FontBuilderFlags)
        .def_readwrite("rasterizer_multiply", &ImFontConfig::RasterizerMultiply)
        .def_readwrite("rasterizer_density", &ImFontConfig::RasterizerDensity)
        .def_readwrite("ellipsis_char", &ImFontConfig::EllipsisChar)
        .def_property("name",
            [](const ImFontConfig &cfg) { return std::string(cfg.Name); },
            [](ImFontConfig &cfg, const std::string &val) { strncpy(cfg.Name, val.c_str(), 39); cfg.Name[39] = '\0'; })
        .def_readwrite("dst_font", &ImFontConfig::DstFont);
}

void bind_imgui_font_glyph(py::module_& m) {
    py::class_<ImFontGlyph>(m, "FontGlyph")
        .def_property("colored",
            [](const ImFontGlyph& g) { return g.Colored != 0; },
            [](ImFontGlyph& g, bool value) { g.Colored = value ? 1 : 0; })
        .def_property("visible",
            [](const ImFontGlyph& g) { return g.Visible != 0; },
            [](ImFontGlyph& g, bool value) { g.Visible = value ? 1 : 0; })
        .def_property("codepoint",
            [](const ImFontGlyph& g) { return g.Codepoint; },
            [](ImFontGlyph& g, unsigned int value) { g.Codepoint = value; })
        .def_readwrite("advance_x", &ImFontGlyph::AdvanceX)
        .def_readwrite("x0", &ImFontGlyph::X0)
        .def_readwrite("y0", &ImFontGlyph::Y0)
        .def_readwrite("x1", &ImFontGlyph::X1)
        .def_readwrite("y1", &ImFontGlyph::Y1)
        .def_readwrite("u0", &ImFontGlyph::U0)
        .def_readwrite("v0", &ImFontGlyph::V0)
        .def_readwrite("u1", &ImFontGlyph::U1)
        .def_readwrite("v1", &ImFontGlyph::V1);
}

void bind_imgui_font_glyph_ranges_builder(py::module_& m) {
    py::class_<ImFontGlyphRangesBuilder>(m, "FontGlyphRangesBuilder")
        .def(py::init<>())
        .def("clear", &ImFontGlyphRangesBuilder::Clear)
        .def("get_bit", &ImFontGlyphRangesBuilder::GetBit)
        .def("set_bit", &ImFontGlyphRangesBuilder::SetBit)
        .def("add_char", &ImFontGlyphRangesBuilder::AddChar)
        .def("add_text", &ImFontGlyphRangesBuilder::AddText, py::arg("text"), py::arg("text_end") = nullptr)
        .def("add_ranges", &ImFontGlyphRangesBuilder::AddRanges)
        .def("build_ranges", [](ImFontGlyphRangesBuilder& self) {
            auto out = new ImVector<ImWchar>();
            self.BuildRanges(out);
            return out;
        }, py::return_value_policy::reference);
}

void bind_imgui_font_atlas_custom_rect(py::module_& m) {
    py::class_<ImFontAtlasCustomRect>(m, "FontAtlasCustomRect")
        .def(py::init<>())
        .def_readwrite("x", &ImFontAtlasCustomRect::X)
        .def_readwrite("y", &ImFontAtlasCustomRect::Y)
        .def_readwrite("width", &ImFontAtlasCustomRect::Width)
        .def_readwrite("height", &ImFontAtlasCustomRect::Height)
        .def_property("glyph_id",
            [](const ImFontAtlasCustomRect& r) { return r.GlyphID; },
            [](ImFontAtlasCustomRect& r, unsigned int val) { r.GlyphID = val; })
        .def_property("glyph_colored",
            [](const ImFontAtlasCustomRect& r) { return r.GlyphColored != 0; },
            [](ImFontAtlasCustomRect& r, bool val) { r.GlyphColored = val ? 1 : 0; })
        .def_readwrite("glyph_advance_x", &ImFontAtlasCustomRect::GlyphAdvanceX)
        .def_readwrite("glyph_offset", &ImFontAtlasCustomRect::GlyphOffset)
        .def_readwrite("font", &ImFontAtlasCustomRect::Font)
        .def("is_packed", &ImFontAtlasCustomRect::IsPacked);
}

void bind_imgui_font_atlas(py::module_& m) {
    py::class_<ImFontAtlas>(m, "FontAtlas")
        .def(py::init<>())
        .def("add_font", &ImFontAtlas::AddFont, py::arg("font_cfg"))
        .def("add_font_default", [](ImFontAtlas& atlas, ImFontConfig* cfg) {
            return atlas.AddFontDefault(cfg);
        }, py::arg("font_cfg") = nullptr)
        .def("add_font_from_file_ttf", [](ImFontAtlas& atlas,
                                        const std::string& filename,
                                        float size_pixels,
                                        ImFontConfig* font_cfg = nullptr,
                                        py::object glyph_ranges = py::none()) {
            const ImWchar* ranges = glyph_ranges.is_none() ? nullptr :
                reinterpret_cast<const ImWchar*>(glyph_ranges.cast<intptr_t>());
            return atlas.AddFontFromFileTTF(filename.c_str(), size_pixels, font_cfg, ranges);
        }, py::arg("filename"), py::arg("size_pixels"), py::arg("font_cfg") = nullptr, py::arg("glyph_ranges") = py::none())
        .def("add_font_from_memory_ttf", [](ImFontAtlas& atlas,
                                            py::bytes data,
                                            float size_pixels,
                                            ImFontConfig* font_cfg = nullptr,
                                            py::object glyph_ranges = py::none()) {
            std::string buffer = data;
            void* font_data = (void*)buffer.data();
            int size = (int)buffer.size();
            const ImWchar* ranges = glyph_ranges.is_none() ? nullptr :
                reinterpret_cast<const ImWchar*>(glyph_ranges.cast<intptr_t>());
            return atlas.AddFontFromMemoryTTF(font_data, size, size_pixels, font_cfg, ranges);
        }, py::arg("font_data"), py::arg("size_pixels"), py::arg("font_cfg") = nullptr, py::arg("glyph_ranges") = py::none())
        .def("add_font_from_memory_compressed_ttf", [](ImFontAtlas& atlas,
                                                    py::bytes data,
                                                    float size_pixels,
                                                    ImFontConfig* font_cfg = nullptr,
                                                    py::object glyph_ranges = py::none()) {
            std::string buffer = data;
            const void* font_data = (const void*)buffer.data();
            int size = (int)buffer.size();
            const ImWchar* ranges = glyph_ranges.is_none() ? nullptr :
                reinterpret_cast<const ImWchar*>(glyph_ranges.cast<intptr_t>());
            return atlas.AddFontFromMemoryCompressedTTF(font_data, size, size_pixels, font_cfg, ranges);
        }, py::arg("data"), py::arg("size_pixels"), py::arg("font_cfg") = nullptr, py::arg("glyph_ranges") = py::none())
        .def("add_font_from_memory_compressed_base85_ttf", [](ImFontAtlas& atlas,
                                                            const std::string& base85,
                                                            float size_pixels,
                                                            ImFontConfig* font_cfg = nullptr,
                                                            py::object glyph_ranges = py::none()) {
            const ImWchar* ranges = glyph_ranges.is_none() ? nullptr :
                reinterpret_cast<const ImWchar*>(glyph_ranges.cast<intptr_t>());
            return atlas.AddFontFromMemoryCompressedBase85TTF(base85.c_str(), size_pixels, font_cfg, ranges);
        }, py::arg("data_base85"), py::arg("size_pixels"), py::arg("font_cfg") = nullptr, py::arg("glyph_ranges") = py::none())
        .def("get_glyph_ranges_default", &ImFontAtlas::GetGlyphRangesDefault)
        .def("get_glyph_ranges_greek", &ImFontAtlas::GetGlyphRangesGreek)
        .def("get_glyph_ranges_korean", &ImFontAtlas::GetGlyphRangesKorean)
        .def("get_glyph_ranges_japanese", &ImFontAtlas::GetGlyphRangesJapanese)
        .def("get_glyph_ranges_chinese_full", &ImFontAtlas::GetGlyphRangesChineseFull)
        .def("get_glyph_ranges_chinese_simplified_common", &ImFontAtlas::GetGlyphRangesChineseSimplifiedCommon)
        .def("get_glyph_ranges_cyrillic", &ImFontAtlas::GetGlyphRangesCyrillic)
        .def("get_glyph_ranges_thai", &ImFontAtlas::GetGlyphRangesThai)
        .def("get_glyph_ranges_vietnamese", &ImFontAtlas::GetGlyphRangesVietnamese)
        .def("get_tex_data_as_rgba32", [](ImFontAtlas& atlas) {
            unsigned char* pixels = nullptr;
            int width = 0, height = 0, bytes_per_pixel = 0;
            atlas.GetTexDataAsRGBA32(&pixels, &width, &height, &bytes_per_pixel);
            size_t size = width * height * bytes_per_pixel;
            return py::bytes(reinterpret_cast<const char*>(pixels), size);
        })
        .def("get_tex_data_as_alpha8", [](ImFontAtlas& atlas) {
            unsigned char* pixels = nullptr;
            int width = 0, height = 0, bytes_per_pixel = 0;
            atlas.GetTexDataAsAlpha8(&pixels, &width, &height, &bytes_per_pixel);
            size_t size = width * height * bytes_per_pixel;
            return py::bytes(reinterpret_cast<const char*>(pixels), size);
        })
        .def("is_built", &ImFontAtlas::IsBuilt)
        .def("set_tex_id", &ImFontAtlas::SetTexID)
        .def("clear", &ImFontAtlas::Clear)
        .def("clear_fonts", &ImFontAtlas::ClearFonts)
        .def("clear_input_data", &ImFontAtlas::ClearInputData)
        .def("clear_tex_data", &ImFontAtlas::ClearTexData)
        .def("build", &ImFontAtlas::Build)
        .def("add_custom_rect_regular", &ImFontAtlas::AddCustomRectRegular)
        .def("add_custom_rect_font_glyph", &ImFontAtlas::AddCustomRectFontGlyph, py::arg("font"), py::arg("id"), py::arg("width"), py::arg("height"), py::arg("advance_x"), py::arg("offset") = ImVec2(0, 0))
        .def("get_custom_rect_by_index", &ImFontAtlas::GetCustomRectByIndex, py::arg("index"), py::return_value_policy::reference)
        .def_readwrite("flags", &ImFontAtlas::Flags)
        .def_readwrite("tex_id", &ImFontAtlas::TexID)
        .def_readwrite("tex_desired_width", &ImFontAtlas::TexDesiredWidth)
        .def_readwrite("tex_glyph_padding", &ImFontAtlas::TexGlyphPadding)
        .def_readwrite("user_data", &ImFontAtlas::UserData)
        .def_readwrite("tex_width", &ImFontAtlas::TexWidth)
        .def_readwrite("tex_height", &ImFontAtlas::TexHeight)
        .def_readwrite("tex_uv_scale", &ImFontAtlas::TexUvScale)
        .def_readwrite("tex_uv_white_pixel", &ImFontAtlas::TexUvWhitePixel)
        .def_readwrite("fonts", &ImFontAtlas::Fonts)
        .def_readwrite("custom_rects", &ImFontAtlas::CustomRects)
        .def_readwrite("sources", &ImFontAtlas::Sources);
}

void bind_imgui_font(py::module_& m) {
    py::class_<ImFont>(m, "Font")
        .def("find_glyph", &ImFont::FindGlyph, py::arg("c"), py::return_value_policy::reference)
        .def("find_glyph_no_fallback", &ImFont::FindGlyphNoFallback, py::arg("c"), py::return_value_policy::reference)
        .def("get_char_advance", &ImFont::GetCharAdvance)
        .def("is_loaded", &ImFont::IsLoaded)
        .def("get_debug_name", &ImFont::GetDebugName)
        .def("calc_text_size_a", [](ImFont& font, float size, float max_width, float wrap_width,
                                    const std::string& text, py::object text_end = py::none()) {
            const char* text_begin = text.c_str();
            const char* text_end_cstr = nullptr;
            if (!text_end.is_none()) {
                std::string end_str = text_end.cast<std::string>();
                text_end_cstr = end_str.c_str();
            }
            return font.CalcTextSizeA(size, max_width, wrap_width, text_begin, text_end_cstr);
        },
        py::arg("size"), py::arg("max_width"), py::arg("wrap_width"),
        py::arg("text"), py::arg("text_end") = py::none())
        .def("render_char", &ImFont::RenderChar, py::arg("draw_list"), py::arg("size"), py::arg("pos"), py::arg("col"), py::arg("c"), py::arg("clip_rect") = nullptr)
        .def("render_text", &ImFont::RenderText, py::arg("draw_list"), py::arg("size"), py::arg("pos"), py::arg("col"), py::arg("clip_rect"), py::arg("text_begin"), py::arg("text_end"), py::arg("wrap_width") = 0.0f, py::arg("cpu_fine_clip") = false)
        .def_readwrite("fallback_advance_x", &ImFont::FallbackAdvanceX)
        .def_readwrite("font_size", &ImFont::FontSize)
        .def_readwrite("fallback_glyph", &ImFont::FallbackGlyph)
        .def_readwrite("fallback_char", &ImFont::FallbackChar)
        .def_readwrite("scale", &ImFont::Scale)
        .def_readwrite("ascent", &ImFont::Ascent)
        .def_readwrite("descent", &ImFont::Descent)
        .def_readwrite("ellipsis_char", &ImFont::EllipsisChar)
        .def_readwrite("ellipsis_char_count", &ImFont::EllipsisCharCount)
        .def_readwrite("ellipsis_width", &ImFont::EllipsisWidth)
        .def_readwrite("ellipsis_char_step", &ImFont::EllipsisCharStep)
        .def_readwrite("metrics_total_surface", &ImFont::MetricsTotalSurface)
        .def_readwrite("dirty_lookup_tables", &ImFont::DirtyLookupTables);
}