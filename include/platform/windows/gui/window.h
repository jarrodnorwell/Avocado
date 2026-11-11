#pragma once

#include <optional>
#include <string>
#include <string_view>

#include <imgui.h>

namespace avocado
{

    namespace gui
    {

        struct Window
        {
            void Header(std::string_view title, std::string_view subtitle, std::optional<std::string> character, ImVec2 size = {48.0f, 48.0f})
            {
                constexpr float titleScale = 1.5f;

                const float contentWidth = ImGui::GetContentRegionAvail().x;

                if (character.has_value())
                {
                    auto &value{character.value()};

                    ImGui::Spacing();
                    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (contentWidth - size.x) * 0.5f);

                    ImGui::Button(value.c_str(), size);
                    ImGui::Spacing();
                }

                {
                    const ImVec2 textSize = ImGui::CalcTextSize(
                        title.data(), title.data() + title.size());

                    ImGui::SetCursorPosX(
                        ImGui::GetCursorPosX() + (contentWidth - textSize.x * titleScale) * 0.5f);

                    ImGui::SetWindowFontScale(titleScale);
                    ImGui::TextUnformatted(title.data(), title.data() + title.size());
                    ImGui::SetWindowFontScale(1.0f);
                }

                {
                    const ImVec2 textSize = ImGui::CalcTextSize(
                        subtitle.data(), subtitle.data() + subtitle.size());

                    ImGui::SetCursorPosX(
                        ImGui::GetCursorPosX() + (contentWidth - textSize.x) * 0.5f);

                    ImGui::TextDisabled(
                        "%.*s",
                        static_cast<int>(subtitle.size()),
                        subtitle.data());
                }

                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();
            };

            virtual void design() = 0;
            virtual void display() = 0;
        };

    };

};