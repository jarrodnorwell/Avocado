#pragma once

#include <string_view>

#include "platform/windows/gui/window.h"

namespace avocado
{

    namespace gui
    {

        struct About : public Window
        {
            bool open{false};

            virtual void design() override;
            virtual void display() override;

        private:
            void PropertyRow(const char *, std::string_view, bool = true);
            void SectionHeader(const char *);
        };

    };

};