#include "platform/windows/gui/help/about.h"
#include "version.h"

#include <imgui.h>

namespace avocado
{

    namespace gui
    {

        void About::design()
        {
            const ImGuiViewport *viewport = ImGui::GetMainViewport();

            ImGui::SetNextWindowPos(
                viewport->GetCenter(),
                ImGuiCond_Always,
                ImVec2(0.5f, 0.5f));

            ImGui::SetNextWindowSizeConstraints(
                ImVec2(640.f, -1.f),
                ImVec2(FLT_MAX, FLT_MAX));

            if (!ImGui::Begin("About", &open, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove))
            {
                ImGui::End();
                return;
            }

            Header("Avocado", "Build information", "A", {48.0f, 48.0f});

            ImGui::Spacing();
            SectionHeader("BUILD");

            if (ImGui::BeginTable(
                    "##build",
                    2,
                    ImGuiTableFlags_SizingStretchProp |
                        ImGuiTableFlags_NoBordersInBody))
            {
                ImGui::TableSetupColumn(
                    "Property",
                    ImGuiTableColumnFlags_WidthFixed,
                    110.0f);

                ImGui::TableSetupColumn(
                    "Value",
                    ImGuiTableColumnFlags_WidthStretch);

                PropertyRow("Architecture", BUILD_ARCH);
                PropertyRow("Branch", BUILD_BRANCH);
                PropertyRow("Commit", BUILD_COMMIT);
                PropertyRow("Commit count", std::to_string(BUILD_COMMIT_COUNT));
                PropertyRow("Tag", BUILD_TAG[0] ? BUILD_TAG : "—");
                PropertyRow("Build date", BUILD_DATE);

                ImGui::EndTable();
            }

            ImGui::Spacing();
            SectionHeader("COMMIT");

            if (ImGui::BeginTable(
                    "##commit",
                    2,
                    ImGuiTableFlags_SizingStretchProp |
                        ImGuiTableFlags_NoBordersInBody))
            {
                ImGui::TableSetupColumn(
                    "Property",
                    ImGuiTableColumnFlags_WidthFixed,
                    110.0f);

                ImGui::TableSetupColumn(
                    "Value",
                    ImGuiTableColumnFlags_WidthStretch);

                PropertyRow("Full hash", BUILD_COMMIT_FULL);
                PropertyRow("Date", BUILD_COMMIT_DATE);
                PropertyRow("Subject", BUILD_COMMIT_SUBJECT);

                ImGui::EndTable();
            }

            ImGui::Spacing();
            SectionHeader("REPOSITORY");

            if (ImGui::BeginTable(
                    "##repository",
                    2,
                    ImGuiTableFlags_SizingStretchProp |
                        ImGuiTableFlags_NoBordersInBody))
            {
                ImGui::TableSetupColumn(
                    "Property",
                    ImGuiTableColumnFlags_WidthFixed,
                    110.0f);

                ImGui::TableSetupColumn(
                    "Value",
                    ImGuiTableColumnFlags_WidthStretch);

                PropertyRow("Remote", BUILD_REMOTE);

                ImGui::EndTable();
            }

            ImGui::Spacing();
            SectionHeader("WORKING TREE");

            ImGui::Bullet();
            ImGui::SameLine();

            if (BUILD_DIRTY)
            {
                ImGui::TextColored(
                    ImVec4(1.0f, 0.65f, 0.2f, 1.0f),
                    "Modified");

                ImGui::SameLine();
                ImGui::TextDisabled(
                    "Uncommitted changes are present.");
            }
            else
            {
                ImGui::TextColored(
                    ImVec4(0.35f, 0.8f, 0.45f, 1.0f),
                    "Clean");

                ImGui::SameLine();
                ImGui::TextDisabled(
                    "Working tree is clean.");
            }

            ImGui::Spacing();

            ImGui::End();
        };

        void About::display()
        {
            if (open)
                design();
        };

        void About::PropertyRow(
            const char *label,
            std::string_view value,
            bool copyable)
        {
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::TextDisabled("%s", label);

            ImGui::TableSetColumnIndex(1);

            ImGui::PushID(label);

            ImGui::TextWrapped("%.*s",
                               static_cast<int>(value.size()),
                               value.data());

            if (copyable && ImGui::IsItemHovered())
            {
                ImGui::SetTooltip("Click to copy");
            }

            if (copyable && ImGui::IsItemClicked())
            {
                ImGui::SetClipboardText(
                    std::string(value).c_str());
            }

            ImGui::PopID();
        }

        void About::SectionHeader(const char *label)
        {
            ImGui::Spacing();
            ImGui::TextDisabled("%s", label);
            ImGui::Separator();
            ImGui::Spacing();
        }

    };

};