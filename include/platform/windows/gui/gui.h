#pragma once

#include "platform/windows/gui/debug/cdrom.h"
#include "platform/windows/gui/debug/cpu.h"
#include "platform/windows/gui/debug/gpu.h"
#include "platform/windows/gui/debug/gte.h"
#include "platform/windows/gui/debug/io.h"
#include "platform/windows/gui/debug/kernel.h"
#include "platform/windows/gui/debug/spu.h"
#include "platform/windows/gui/debug/timers.h"
#include "platform/windows/gui/file/open.h"
#include "platform/windows/gui/help/about.h"
#include "platform/windows/gui/options/bios.h"
#include "platform/windows/gui/options/memory_card.h"
#include "platform/windows/gui/options/options.h"
#include "platform/windows/gui/options/system_options.h"
#include "platform/windows/gui/toasts.h"

#include <optional>

#include <SDL.h>

struct System;

class GUI {
    int busToken;
    SDL_Window* window;
    bool notInitializedWindowShown = false;
    std::string iniPath;

    gui::file::Open openFile;

    gui::debug::Cdrom cdromDebug;
    gui::debug::CPU cpuDebug;
    gui::debug::GPU gpuDebug;
    gui::debug::Timers timersDebug;
    gui::debug::GTE gteDebug;
    gui::debug::SPU spuDebug;
    gui::debug::IO ioDebug;

    gui::options::Bios biosOptions;
    gui::options::MemoryCard memoryCardOptions;
    gui::options::System systemOptions;

    avocado::gui::About about;

    gui::Toasts toasts;

    void mainMenu(std::unique_ptr<System>& sys);
    void memoryCardDialog();
    void discDialog();
    void drawControls(std::unique_ptr<System>& sys);
    void renderController();

   public:
    static float scale;

    bool singleFrame = false;
    bool showGui = true;
    bool showMenu = true;

    // Status
    double statusFps = 0.0;
    bool statusFramelimitter = true;
    bool statusMouseLocked = false;

    // Drag&drop
    std::optional<std::string> droppedItem;

    enum class DroppedItemDialog { None, Disc, MemoryCard };
    DroppedItemDialog droppedItemDialog = DroppedItemDialog::None;

    GUI(SDL_Window* window, void* glContext);
    ~GUI();

    void processEvent(SDL_Event* e);
    void render(std::unique_ptr<System>& sys);
};