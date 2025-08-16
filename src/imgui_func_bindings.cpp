
#include "imgui_bindings.h"


void bind_imgui_core(py::module_& m) {
    m.def("begin", [](const std::string& name, bool* p_open = nullptr, ImGuiWindowFlags flags = 0) {
        return ImGui::Begin(name.c_str(), p_open, flags);
    }, py::arg("name"), py::arg("p_open") = nullptr, py::arg("flags") = 0);

    m.def("end", &ImGui::End);

    m.def("text", [](const std::string& text) {
        ImGui::Text("%s", text.c_str());
    }, py::arg("text"));

    m.def("text_colored", [](const ImVec4& color, const std::string& text) {
        ImGui::TextColored(color, "%s", text.c_str());
    }, py::arg("color"), py::arg("text"));

    m.def("push_style_color", [](ImGuiCol idx, const ImVec4& color) {
        ImGui::PushStyleColor(idx, color);
    }, py::arg("idx"), py::arg("color"));

    m.def("push_style_var_float", [](ImGuiStyleVar idx, float val) {
        ImGui::PushStyleVar(idx, val);
    }, py::arg("idx"), py::arg("value"));

    m.def("push_style_var_vec2", [](ImGuiStyleVar idx, const ImVec2& val) {
        ImGui::PushStyleVar(idx, val);
    }, py::arg("idx"), py::arg("value"));

    m.def("pop_style_var", &ImGui::PopStyleVar, py::arg("count") = 1);

    m.def("pop_style_color", &ImGui::PopStyleColor, py::arg("count") = 1);

    m.def("same_line", &ImGui::SameLine, py::arg("offset_from_start_x") = 0.0f, py::arg("spacing") = -1.0f);

    m.def("separator", &ImGui::Separator);

    m.def("spacing", &ImGui::Spacing);

    m.def("set_next_window_pos", &ImGui::SetNextWindowPos,
          py::arg("pos"), py::arg("cond") = 0, py::arg("pivot") = ImVec2(0, 0));

    m.def("set_next_window_size", &ImGui::SetNextWindowSize,
          py::arg("size"), py::arg("cond") = 0);

    m.def("set_next_window_size_constraints",
          [](const ImVec2& min, const ImVec2& max) {
              ImGui::SetNextWindowSizeConstraints(min, max, nullptr, nullptr);
          },
          py::arg("size_min"), py::arg("size_max"));

    m.def("set_next_window_content_size", &ImGui::SetNextWindowContentSize,
          py::arg("size"));

    m.def("set_next_window_collapsed", &ImGui::SetNextWindowCollapsed,
          py::arg("collapsed"), py::arg("cond") = 0);

    m.def("set_next_window_focus", &ImGui::SetNextWindowFocus);

    m.def("set_cursor_pos", &ImGui::SetCursorPos, py::arg("local_pos"));
    m.def("set_cursor_screen_pos", &ImGui::SetCursorScreenPos, py::arg("screen_pos"));

    m.def("set_item_default_focus", &ImGui::SetItemDefaultFocus);

    m.def("button", &ImGui::Button, py::arg("label"), py::arg("size") = ImVec2(0, 0));

    m.def("checkbox", [](const char* label, bool value) {
        bool v = value;
        bool changed = ImGui::Checkbox(label, &v);
        return std::make_tuple(changed, v);
    }, py::arg("label"), py::arg("value"));

    m.def("radio_button", [](const char* label, int current_value, int button_value) {
        bool changed = ImGui::RadioButton(label, current_value == button_value);
        if (changed)
            return std::make_tuple(true, button_value);
        return std::make_tuple(false, current_value);
    }, py::arg("label"), py::arg("current_value"), py::arg("button_value"));

    m.def("input_float", [](const char* label, float value, float step, float step_fast, const char* format) {
        float v = value;
        bool changed = ImGui::InputFloat(label, &v, step, step_fast, format);
        return std::make_tuple(changed, v);
    }, py::arg("label"), py::arg("value"), py::arg("step") = 0.0f, py::arg("step_fast") = 0.0f, py::arg("format") = "%.3f");

    m.def("input_int", [](const char* label, int value, int step, int step_fast) {
        int v = value;
        bool changed = ImGui::InputInt(label, &v, step, step_fast);
        return std::make_tuple(changed, v);
    }, py::arg("label"), py::arg("value"), py::arg("step") = 1, py::arg("step_fast") = 100);

    m.def("slider_float", [](const char* label, float value, float min, float max, const char* format) {
        float v = value;
        bool changed = ImGui::SliderFloat(label, &v, min, max, format);
        return std::make_tuple(changed, v);
    }, py::arg("label"), py::arg("value"), py::arg("min"), py::arg("max"), py::arg("format") = "%.3f");

    m.def("slider_int", [](const char* label, int value, int min, int max) {
        int v = value;
        bool changed = ImGui::SliderInt(label, &v, min, max);
        return std::make_tuple(changed, v);
    }, py::arg("label"), py::arg("value"), py::arg("min"), py::arg("max"));

    m.def("combo", [](const char* label, int current_item, const std::vector<std::string>& items) {
        std::vector<const char*> c_items;
        for (const auto& s : items) c_items.push_back(s.c_str());
        int v = current_item;
        bool changed = ImGui::Combo(label, &v, c_items.data(), static_cast<int>(c_items.size()));
        return std::make_tuple(changed, v);
    }, py::arg("label"), py::arg("current_item"), py::arg("items"));

    m.def("color_edit3", [](const char* label, const ImVec4& color) {
        float col[3] = { color.x, color.y, color.z };
        bool changed = ImGui::ColorEdit3(label, col);
        ImVec4 result(col[0], col[1], col[2], color.w);
        return std::make_tuple(changed, result);
    }, py::arg("label"), py::arg("color"));

    m.def("color_edit4", [](const char* label, const ImVec4& color, ImGuiColorEditFlags flags) {
        float col[4] = { color.x, color.y, color.z, color.w };
        bool changed = ImGui::ColorEdit4(label, col, flags);
        ImVec4 result(col[0], col[1], col[2], col[3]);
        return std::make_tuple(changed, result);
    }, py::arg("label"), py::arg("color"), py::arg("flags") = 0);

    m.def("color_picker3", [](const char* label, ImVec4 color, ImGuiColorEditFlags flags) {
        float col[3] = { color.x, color.y, color.z };
        bool changed = ImGui::ColorPicker3(label, col, flags);
        ImVec4 result(col[0], col[1], col[2], color.w);  // Keep original alpha
        return std::make_tuple(changed, result);
    }, py::arg("label"), py::arg("color"), py::arg("flags") = 0);

    m.def("color_picker4", [](const char* label, ImVec4 color, ImGuiColorEditFlags flags) {
        float col[4] = { color.x, color.y, color.z, color.w };
        bool changed = ImGui::ColorPicker4(label, col, flags);
        ImVec4 result(col[0], col[1], col[2], col[3]);
        return std::make_tuple(changed, result);
    }, py::arg("label"), py::arg("color"), py::arg("flags") = 0);

    m.def("color_button", [](const char* desc_id, const ImVec4& color, ImGuiColorEditFlags flags, const ImVec2& size) {
        return ImGui::ColorButton(desc_id, color, flags, size);
    }, py::arg("desc_id"), py::arg("color"), py::arg("flags") = 0, py::arg("size") = ImVec2(0, 0));


    // InputText with a buffer
    m.def("input_text", [](const std::string& label, const std::string& text, ImGuiInputTextFlags flags = 0) {
        // Copy text into heap-allocated std::string
        std::string buffer = text;

        // Ensure space for editing
        buffer.resize(std::max<size_t>(buffer.size() + 32, 64));

        // Setup callback data
        struct CallbackData {
            std::string* str;
        } user_data { &buffer };

        bool changed = ImGui::InputText(
            label.c_str(),
            buffer.data(),
            buffer.capacity(),
            flags | ImGuiInputTextFlags_CallbackResize,
            [](ImGuiInputTextCallbackData* data) -> int {
                if (data->EventFlag == ImGuiInputTextFlags_CallbackResize) {
                    auto* user = reinterpret_cast<CallbackData*>(data->UserData);
                    user->str->resize(data->BufTextLen + 1);
                    data->Buf = user->str->data();
                }
                return 0;
            },
            &user_data
        );

        // Trim to actual length (remove pre-allocated extra space)
        buffer.resize(std::strlen(buffer.c_str()));

        return std::make_tuple(changed, buffer);
    }, py::arg("label"), py::arg("text"), py::arg("flags") = 0);

    m.def("input_text_multiline", [](const std::string& label, const std::string& text, const ImVec2& size = ImVec2(0, 0), ImGuiInputTextFlags flags = 0) {
        std::string buffer = text;
        buffer.resize(std::max<size_t>(buffer.size() + 32, 64));

        struct CallbackData {
            std::string* str;
        } user_data { &buffer };

        bool changed = ImGui::InputTextMultiline(
            label.c_str(),
            buffer.data(),
            buffer.capacity(),
            size,
            flags | ImGuiInputTextFlags_CallbackResize,
            [](ImGuiInputTextCallbackData* data) -> int {
                if (data->EventFlag == ImGuiInputTextFlags_CallbackResize) {
                    auto* user = reinterpret_cast<CallbackData*>(data->UserData);
                    user->str->resize(data->BufTextLen + 1);
                    data->Buf = user->str->data();
                }
                return 0;
            },
            &user_data
        );

        buffer.resize(std::strlen(buffer.c_str()));
        return std::make_tuple(changed, buffer);
    }, py::arg("label"), py::arg("text"), py::arg("size") = ImVec2(0, 0), py::arg("flags") = 0);

    m.def("drag_float", [](const std::string& label, float value, float speed, float min, float max, const char* format, ImGuiSliderFlags flags) {
        float v = value;
        bool changed = ImGui::DragFloat(label.c_str(), &v, speed, min, max, format, flags);
        return std::make_tuple(changed, v);
    }, py::arg("label"), py::arg("value"), py::arg("speed") = 1.0f, py::arg("min") = 0.0f, py::arg("max") = 0.0f, py::arg("format") = "%.3f", py::arg("flags") = 0);

    m.def("drag_float2", [](const std::string& label, std::array<float, 2> value, float speed, float min, float max, const char* format, ImGuiSliderFlags flags) {
        float v[2] = { value[0], value[1] };
        bool changed = ImGui::DragFloat2(label.c_str(), v, speed, min, max, format, flags);
        return std::make_tuple(changed, std::make_tuple(v[0], v[1]));
    }, py::arg("label"), py::arg("value"), py::arg("speed") = 1.0f, py::arg("min") = 0.0f, py::arg("max") = 0.0f, py::arg("format") = "%.3f", py::arg("flags") = 0);

    m.def("drag_float3", [](const std::string& label, std::array<float, 3> value, float speed, float min, float max, const char* format, ImGuiSliderFlags flags) {
        float v[3] = { value[0], value[1], value[2] };
        bool changed = ImGui::DragFloat3(label.c_str(), v, speed, min, max, format, flags);
        return std::make_tuple(changed, std::make_tuple(v[0], v[1], v[2]));
    }, py::arg("label"), py::arg("value"), py::arg("speed") = 1.0f, py::arg("min") = 0.0f, py::arg("max") = 0.0f, py::arg("format") = "%.3f", py::arg("flags") = 0);

    m.def("drag_float4", [](const std::string& label, std::array<float, 4> value, float speed, float min, float max, const char* format, ImGuiSliderFlags flags) {
        float v[4] = { value[0], value[1], value[2], value[3] };
        bool changed = ImGui::DragFloat4(label.c_str(), v, speed, min, max, format, flags);
        return std::make_tuple(changed, std::make_tuple(v[0], v[1], v[2], v[3]));
    }, py::arg("label"), py::arg("value"), py::arg("speed") = 1.0f, py::arg("min") = 0.0f, py::arg("max") = 0.0f, py::arg("format") = "%.3f", py::arg("flags") = 0);

    m.def("drag_int", [](const std::string& label, int value, float speed, int min, int max, const char* format, ImGuiSliderFlags flags) {
        int v = value;
        bool changed = ImGui::DragInt(label.c_str(), &v, speed, min, max, format, flags);
        return std::make_tuple(changed, v);
    }, py::arg("label"), py::arg("value"), py::arg("speed") = 1.0f, py::arg("min") = 0, py::arg("max") = 0, py::arg("format") = "%d", py::arg("flags") = 0);

    m.def("drag_int2", [](const std::string& label, std::array<int, 2> value, float speed, int min, int max, const char* format, ImGuiSliderFlags flags) {
        int v[2] = { value[0], value[1] };
        bool changed = ImGui::DragInt2(label.c_str(), v, speed, min, max, format, flags);
        return std::make_tuple(changed, std::make_tuple(v[0], v[1]));
    }, py::arg("label"), py::arg("value"), py::arg("speed") = 1.0f, py::arg("min") = 0, py::arg("max") = 0, py::arg("format") = "%d", py::arg("flags") = 0);

    m.def("drag_int3", [](const std::string& label, std::array<int, 3> value, float speed, int min, int max, const char* format, ImGuiSliderFlags flags) {
        int v[3] = { value[0], value[1], value[2] };
        bool changed = ImGui::DragInt3(label.c_str(), v, speed, min, max, format, flags);
        return std::make_tuple(changed, std::make_tuple(v[0], v[1], v[2]));
    }, py::arg("label"), py::arg("value"), py::arg("speed") = 1.0f, py::arg("min") = 0, py::arg("max") = 0, py::arg("format") = "%d", py::arg("flags") = 0);

    m.def("drag_int4", [](const std::string& label, std::array<int, 4> value, float speed, int min, int max, const char* format, ImGuiSliderFlags flags) {
        int v[4] = { value[0], value[1], value[2], value[3] };
        bool changed = ImGui::DragInt4(label.c_str(), v, speed, min, max, format, flags);
        return std::make_tuple(changed, std::make_tuple(v[0], v[1], v[2], v[3]));
    }, py::arg("label"), py::arg("value"), py::arg("speed") = 1.0f, py::arg("min") = 0, py::arg("max") = 0, py::arg("format") = "%d", py::arg("flags") = 0);

    m.def("get_window_draw_list", &ImGui::GetWindowDrawList, py::return_value_policy::reference);
    m.def("get_background_draw_list", &ImGui::GetBackgroundDrawList, py::return_value_policy::reference);
    m.def("get_foreground_draw_list", &ImGui::GetForegroundDrawList, py::return_value_policy::reference);

    m.def("get_main_viewport", []() -> ImGuiViewport* {
        return ImGui::GetMainViewport();
    }, py::return_value_policy::reference);

    m.def("image", [](ImTextureID texture_id, float width, float height,
                    ImVec2 uv0, ImVec2 uv1) {
        ImGui::Image(texture_id, ImVec2(width, height), uv0, uv1);
    });

    m.def("get_available_region", []() {
        ImVec2 size = ImGui::GetContentRegionAvail();
        return std::make_tuple(size.x, size.y);
    });

    m.def("get_glyph_ranges_default", &ImFontAtlas::GetGlyphRangesDefault, py::return_value_policy::reference);
    m.def("get_glyph_ranges_greek", &ImFontAtlas::GetGlyphRangesGreek, py::return_value_policy::reference);
    m.def("get_glyph_ranges_korean", &ImFontAtlas::GetGlyphRangesKorean, py::return_value_policy::reference);
    m.def("get_glyph_ranges_japanese", &ImFontAtlas::GetGlyphRangesJapanese, py::return_value_policy::reference);
    m.def("get_glyph_ranges_chinese_full", &ImFontAtlas::GetGlyphRangesChineseFull, py::return_value_policy::reference);
    m.def("get_glyph_ranges_chinese_simplified_common", &ImFontAtlas::GetGlyphRangesChineseSimplifiedCommon, py::return_value_policy::reference);
    m.def("get_glyph_ranges_cyrillic", &ImFontAtlas::GetGlyphRangesCyrillic, py::return_value_policy::reference);
    m.def("get_glyph_ranges_thai", &ImFontAtlas::GetGlyphRangesThai, py::return_value_policy::reference);
    m.def("get_glyph_ranges_vietnamese", &ImFontAtlas::GetGlyphRangesVietnamese, py::return_value_policy::reference);

    m.def("push_font", &ImGui::PushFont);
    m.def("pop_font", &ImGui::PopFont);
}