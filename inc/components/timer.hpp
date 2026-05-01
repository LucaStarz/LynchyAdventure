#pragma once

#include "components/component.hpp"
#include <3ds.h>

namespace components {
    class Timer : public Component {
    public:
        Timer(u16 duration, bool repeat);
        ~Timer();

        void update(entities::Entity *parent, entities::Zone *container) override;

        bool isFinished() const;
        void setFinished();
        void reset();
        void setDuration(u16 duration);
    private:
        u16 duration, current;
        bool repeat;
    };
}