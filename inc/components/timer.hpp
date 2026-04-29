#pragma once

#include "components/squared_detector.hpp"

namespace components {
    class Timer : public Component {
    public:
        Timer(u16 duration, bool repeat);
        ~Timer();

        void update(entities::Entity *parent, entities::Zone *container) override;

        bool isFinished() const;
        void reset();
    private:
        u16 duration, current;
        bool repeat;
    };
}