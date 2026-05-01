#pragma once

#include <3ds.h>
#include "entities/weapon.hpp"

namespace systems {
    class SaveSystem final {
    public:
        static SaveSystem &getInstance();

        SaveSystem(const SaveSystem&) = delete;
        SaveSystem &operator=(const SaveSystem&) = delete;

        void loadConfigurations();
        void loadPlayerSave();
        void storePlayerSave();
        void loadWeaponData(entities::Weapon *weapon, u16 weapon_id);

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