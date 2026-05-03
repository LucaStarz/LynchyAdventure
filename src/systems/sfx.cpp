#include <cstring>
#include <cstdio>
#include "systems/sfx.hpp"
#include "utils/utilities.hpp"
#include "utils/constants.hpp"

using namespace systems;

SoundManager &SoundManager::getInstance() {
    static SoundManager instance;
    return instance;
}

SoundManager::SoundManager() {
    ndspInit();
    ndspSetOutputMode(NDSP_OUTPUT_STEREO);
    ndspChnReset(0);
    ndspChnSetInterp(0, NDSP_INTERP_POLYPHASE);
    ndspChnSetRate(0, 22050);
    ndspChnSetFormat(0, NDSP_FORMAT_MONO_PCM16);

    this->loadCommonSounds();
}

SoundManager::~SoundManager() {
    ndspExit();
    for (auto it : this->audios)
        linearFree(it.second.data);
}

void SoundManager::loadCommonSounds() {
    this->loadSound(utils::SND_COIN);
}

void SoundManager::loadSound(utils::SOUNDS_ID id) {
    auto audio = this->audios.find(id);
    if (audio != this->audios.end()) {
        audio->second.loading_count += 1;
        return;
    }

    Audio new_audio;
    new_audio.loading_count = 0;
    char filename[64];
    sprintf(filename, SFX_PATH, id);

    FILE *sound_file = fopen(filename, "rb");
    if (!sound_file)
        return;

    fseek(sound_file, 0, SEEK_END);
    new_audio.size = ftell(sound_file) - 44;
    rewind(sound_file);
    fseek(sound_file, 44, SEEK_SET);

    new_audio.data = linearAlloc(new_audio.size);
    fread(new_audio.data, 1, new_audio.size, sound_file);
    fclose(sound_file);

    PRINT("Sound %u was loaded\n", id);
    this->audios[id] = std::move(new_audio);
}

void SoundManager::unloadSound(utils::SOUNDS_ID id) {
    auto audio = this->audios.find(id);
    if (audio == this->audios.end())
        return;
    
    audio->second.loading_count -= 1;
    if (!audio->second.loading_count) {
        PRINT("Sound %u was unloaded\n", id);
        this->audios.erase(audio);
    }
}

void SoundManager::playSound(utils::SOUNDS_ID id) {
    auto audio = this->audios.find(id);
    if (audio == this->audios.end())
        return;
    
    memset(&this->wave_buffer, 0, sizeof(this->wave_buffer));

    this->wave_buffer.data_vaddr = audio->second.data;
    this->wave_buffer.nsamples = audio->second.size / 2;
    this->wave_buffer.looping = false;

    DSP_FlushDataCache(audio->second.data, audio->second.size);
    ndspChnWaveBufAdd(0, &this->wave_buffer);
}