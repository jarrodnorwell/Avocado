cmake_minimum_required(VERSION 4.0)

project(Avocado LANGUAGES CXX)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_CRT_SECURE_NO_WARNINGS")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

    find_package(OpenGL REQUIRED)
endif()

include(FetchContent)

FetchContent_Declare(cereal GIT_REPOSITORY https://github.com/uscilab/cereal GIT_TAG master)
set(SKIP_PERFORMANCE_COMPARISON ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(cereal)

FetchContent_Declare(EventBus GIT_REPOSITORY https://github.com/jarrodnorwell/eventbus GIT_TAG main)
FetchContent_MakeAvailable(EventBus)

FetchContent_Declare(FLAC GIT_REPOSITORY https://github.com/xiph/flac GIT_TAG master)
set(BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(INSTALL_MANPAGES OFF CACHE BOOL "" FORCE)
set(WITH_OGG OFF CACHE BOOL "" FORCE)
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(FLAC)

FetchContent_Declare(fmt GIT_REPOSITORY https://github.com/fmtlib/fmt GIT_TAG main)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(imgui GIT_REPOSITORY https://github.com/ocornut/imgui GIT_TAG master)
FetchContent_MakeAvailable(imgui)

FetchContent_Declare(magic_enum GIT_REPOSITORY https://github.com/neargye/magic_enum GIT_TAG master)
FetchContent_MakeAvailable(magic_enum)
    
FetchContent_Declare(miniz GIT_REPOSITORY https://github.com/richgel999/miniz GIT_TAG master)
FetchContent_MakeAvailable(miniz)

FetchContent_Declare(nlohmann_json GIT_REPOSITORY https://github.com/nlohmann/json GIT_TAG develop)
FetchContent_MakeAvailable(nlohmann_json)

FetchContent_Declare(SDL2 GIT_REPOSITORY https://github.com/libsdl-org/sdl GIT_TAG 25f9ed87ff6947d9576fc9d79dee0784e638ac58)
set(SDL_SHARED ON CACHE BOOL "" FORCE)
set(SDL_STATIC OFF CACHE BOOL "" FORCE)
set(SDL_TEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SDL2)

if (MSVC)
    target_compile_options(SDL2 PRIVATE $<$<CONFIG:Debug>:/RTC->)
endif()

FetchContent_Declare(zlib GIT_REPOSITORY https://github.com/madler/zlib GIT_TAG develop)
FetchContent_MakeAvailable(zlib)

add_library(glad STATIC externals/glad/glad.c)
target_include_directories(glad PUBLIC externals/glad/include)

set(IMGUI_SOURCES
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp

    ${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp
)

set(IMGUI_BACKEND_SOURCES
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC ${IMGUI_SOURCES} ${IMGUI_BACKEND_SOURCES})

# Specify include directories so the target knows where headers live
target_include_directories(imgui PUBLIC 
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
    ${imgui_SOURCE_DIR}/misc/cpp
)

# Link the backend dependencies directly to your custom imgui target
target_link_libraries(imgui PUBLIC OpenGL::GL SDL2::SDL2)

add_library(lzma STATIC
    externals/lzma-sdk/C/Alloc.c
    externals/lzma-sdk/C/Bra86.c
    externals/lzma-sdk/C/Bra.c
    externals/lzma-sdk/C/BraIA64.c
    externals/lzma-sdk/C/CpuArch.c
    externals/lzma-sdk/C/Delta.c
    externals/lzma-sdk/C/LzFind.c
    externals/lzma-sdk/C/Lzma86Dec.c
    externals/lzma-sdk/C/Lzma86Enc.c
    externals/lzma-sdk/C/LzmaDec.c
    externals/lzma-sdk/C/LzmaEnc.c
    externals/lzma-sdk/C/LzmaLib.c
    externals/lzma-sdk/C/Sort.c
)
target_include_directories(lzma PUBLIC externals/lzma-sdk/C)
target_compile_definitions(lzma PRIVATE _7ZIP_ST)

add_library(chdr STATIC
    externals/libchdr/src/bitstream.c
    externals/libchdr/src/cdrom.c
    externals/libchdr/src/chd.c
    externals/libchdr/src/huffman.c
    externals/libchdr/src/flac.c
)
target_include_directories(chdr PUBLIC externals/libchdr/src)
target_link_libraries(chdr FLAC lzma miniz zlib)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} assets/app.rc)

if (MSVC)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:zlib>
        $<TARGET_FILE_DIR:Avocado>
        COMMENT "Copying zlib shared library to execution directory..."
    )

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL2::SDL2>
        $<TARGET_FILE_DIR:Avocado>
        COMMENT "Copying SDL shared library to execution directory..."
    )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE include externals/stb)

target_link_libraries(${PROJECT_NAME} PRIVATE cereal chdr Dexode::EventBus fmt-header-only glad imgui magic_enum miniz nlohmann_json OpenGL::GL SDL2::SDL2)

set(SOURCES
    # BIOS
    sources/bios/functions.cpp

    # CPU
    sources/cpu/cop0.cpp
    sources/cpu/cpu.cpp
    sources/cpu/instructions.cpp

    # CPU/GTE
    sources/cpu/gte/gte.cpp
    sources/cpu/gte/math.cpp
    sources/cpu/gte/opcodes.cpp

    # DEBUGGER
    sources/debugger/debugger.cpp

    # DEVICE
    sources/device/cache_control.cpp
    sources/device/expansion2.cpp
    sources/device/interrupt.cpp
    sources/device/memory_control.cpp
    sources/device/ram_control.cpp
    sources/device/serial.cpp
    sources/device/timer.cpp

    # DEVICE/CDROM
    sources/device/cdrom/cdrom.cpp
    sources/device/cdrom/commands.cpp

    # DEVICE/CONTROLLER
    sources/device/controller/controller.cpp

    # DEVICE/CONTROLLER/PERIPHERALS
    sources/device/controller/peripherals/abstract_device.cpp
    sources/device/controller/peripherals/analog_controller.cpp
    sources/device/controller/peripherals/digital_controller.cpp
    sources/device/controller/peripherals/memory_card.cpp
    sources/device/controller/peripherals/mouse.cpp
    sources/device/controller/peripherals/none.cpp

    # DEVICE/DMA
    sources/device/dma/dma_channel.cpp
    sources/device/dma/dma.cpp
    sources/device/dma/dma0_channel.cpp
    sources/device/dma/dma1_channel.cpp
    sources/device/dma/dma2_channel.cpp
    sources/device/dma/dma3_channel.cpp
    sources/device/dma/dma4_channel.cpp
    sources/device/dma/dma5_channel.cpp
    sources/device/dma/dma6_channel.cpp

    # DEVICE/GPU
    sources/device/gpu/color_depth.cpp
    sources/device/gpu/gpu.cpp
    sources/device/gpu/psx_color.cpp

    # DEVICE/GPU/RENDER
    sources/device/gpu/render/dither.cpp
    sources/device/gpu/render/render_line.cpp
    sources/device/gpu/render/render_rectangle.cpp
    sources/device/gpu/render/render_triangle.cpp

    # DEVICE/MDEC
    sources/device/mdec/algorithm.cpp
    sources/device/mdec/mdec.cpp

    # DEVICE/SPU
    sources/device/spu/adsr.cpp
    sources/device/spu/interpolation.cpp
    sources/device/spu/noise.cpp
    sources/device/spu/reverb.cpp
    sources/device/spu/spu.cpp
    sources/device/spu/voice.cpp

    # DISC
    sources/disc/disc.cpp
    sources/disc/load.cpp
    sources/disc/position.cpp
    sources/disc/subchannel_q.cpp
    sources/disc/track.cpp

    # DISC/FORMAT
    sources/disc/format/chd_format.cpp
    sources/disc/format/cue_parser.cpp
    sources/disc/format/cue.cpp
    sources/disc/format/ecm_parser.cpp
    sources/disc/format/ecm.cpp

    # INPUT
    sources/input/input_manager.cpp

    # MEMORY_CARD
    sources/memory_card/card_formats.cpp

    # RENDERER
    sources/renderer/opengl/opengl.cpp
    sources/renderer/opengl/shader/attribute.cpp
    sources/renderer/opengl/shader/buffer.cpp
    sources/renderer/opengl/shader/framebuffer.cpp
    sources/renderer/opengl/shader/program.cpp
    sources/renderer/opengl/shader/shader.cpp
    sources/renderer/opengl/shader/texture.cpp
    sources/renderer/opengl/shader/uniform.cpp
    sources/renderer/opengl/shader/vertex_array_object.cpp

    # SOUND
    sources/sound/adpcm.cpp
    sources/sound/sound.cpp
    sources/sound/tables.cpp
    sources/sound/wave.cpp

    # STATE
    sources/state/state.cpp

    # UTILS
    sources/utils/bcd.cpp
    sources/utils/event.cpp
    sources/utils/file.cpp
    sources/utils/gpu_draw_list.cpp
    sources/utils/psf.cpp
    sources/utils/stb_image_write.cpp
    sources/utils/string.cpp
    sources/utils/vector.cpp

    sources/config.cpp
    sources/stdafx.cpp
    sources/system.cpp
    sources/system_tools.cpp
)

if (MSVC)
    list(APPEND SOURCES
        sources/platform/windows/config_parser.cpp
        sources/platform/windows/main.cpp

        sources/platform/windows/file/file.cpp
        
        sources/platform/windows/gui/gui.cpp
        sources/platform/windows/gui/images.cpp
        sources/platform/windows/gui/toasts.cpp
        
        sources/platform/windows/gui/debug/cdrom.cpp
        sources/platform/windows/gui/debug/cpu.cpp
        sources/platform/windows/gui/debug/gpu.cpp
        sources/platform/windows/gui/debug/gte.cpp
        sources/platform/windows/gui/debug/io.cpp
        sources/platform/windows/gui/debug/kernel.cpp
        sources/platform/windows/gui/debug/spu.cpp
        sources/platform/windows/gui/debug/timers.cpp
        
        sources/platform/windows/gui/file/open.cpp
        
        sources/platform/windows/gui/help/about.cpp
        
        sources/platform/windows/gui/helper/file_dialog.cpp
        
        sources/platform/windows/gui/options/bios.cpp
        sources/platform/windows/gui/options/memory_card.cpp
        sources/platform/windows/gui/options/options.cpp
        sources/platform/windows/gui/options/system_options.cpp
        
        sources/platform/windows/input/key.cpp
        sources/platform/windows/input/sdl_input_manager.cpp
        
        sources/platform/windows/utils/platform_tools.cpp
    )
endif()

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})