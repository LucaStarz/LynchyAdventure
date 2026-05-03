#pragma once

#include <3ds.h>
#include <unordered_map>
#include "utils/sounds.hpp"

namespace systems {
    typedef struct {
        void *data;
        u32 size;
        u8 loading_count;
    } Audio;

    class SoundManager final {
    public:
        static SoundManager &getInstance();

        SoundManager(const SoundManager&) = delete;
        SoundManager &operator=(const SoundManager&) = delete;

        void loadSound(utils::SOUNDS_ID id);
        void unloadSound(utils::SOUNDS_ID id);
        void playSound(utils::SOUNDS_ID id);
    private:
        std::unordered_map<utils::SOUNDS_ID, Audio> audios;
        ndspWaveBuf wave_buffer;

        SoundManager();
        ~SoundManager();

        void loadCommonSounds();
    };
}