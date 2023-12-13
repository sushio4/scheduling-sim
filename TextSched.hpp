#pragma once
#include "BaseScheduler.hpp"

#include <string>
#include <memory>

/**
 * @brief Text ui for scheduler simulations
*/
class TextScheduler {
public:
    TextScheduler(const TextScheduler& other) = delete;
    TextScheduler(TextScheduler&& other) = default;

    /**
     * @brief Constructor taking a pointer to existing Scheduler
     * @param ptr Unique pointer to Scheduler object
    */
    TextScheduler(std::unique_ptr<Scheduler>&& ptr);

    /**
     *  @brief Draws the next frame of the scheduler
    */
    void draw_frame();

    inline bool is_running() {return !sched->done;}

private:
    std::unique_ptr<Scheduler> sched;
};