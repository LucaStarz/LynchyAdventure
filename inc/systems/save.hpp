#pragma once

#include "systems/text.hpp"

namespace systems {
    class SaveSystem {
    public:
        static SaveSystem &getInstance();

        SaveSystem(const SaveSystem&) = delete;
        SaveSystem &operator=(const SaveSystem&) = delete;

        void loadConfigurations();
        void loadPlayerSave();
        void storePlayerSave();

        u8 getLang() const;
    private:
        u8 lang;

        SaveSystem();
        ~SaveSystem();

        void initConfigurations();
        void initPlayerSave();

        void createDirectory(const char *directory);
    };
}