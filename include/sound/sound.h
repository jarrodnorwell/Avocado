#pragma once

#if __APPLE__
#include <TargetConditionals.h>
#endif

#if TARGET_OS_IPHONE

#include "avocado/constants.h"
#include "avocado/device/spu/spu.h"

#else

#include "constants.h"
#include "device/spu/spu.h"

#endif // TARGET_OS_IPHONE

#include <cstdint>
#include <deque>
#include <iterator>
#include <mutex>

namespace Sound
{
    extern std::deque<uint16_t> buffer;
    extern std::mutex mutex;

    template <typename Iterator>
    void append(const Iterator &start, const Iterator &end)
    {
        std::unique_lock<std::mutex> lock{Sound::mutex};

        if (Sound::buffer.size() > constants::sound::SIZE)
            Sound::buffer.clear();

        Sound::buffer.insert(Sound::buffer.end(), start, end);
    }

    void clear(), close(), init(), play(), stop();
} // namespace Sound