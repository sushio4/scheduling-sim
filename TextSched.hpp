#pragma once
#include "BaseScheduler.hpp"

#include <string>
#include <memory>

/**
 * @brief Text ui for scheduler simulations
*/
class TextScheduler {
public:
    TextScheduler() = default;
    TextScheduler(const TextScheduler& other) = delete;
    TextScheduler(TextScheduler&& other) = default;
    TextScheduler& operator=(TextScheduler&& other) = default;

    /**
     * @brief Constructor taking a pointer to existing Scheduler
     * @param ptr Unique pointer to Scheduler object
    */
    TextScheduler(std::unique_ptr<Scheduler>&& ptr);

    /**
     *  @brief Draws the next frame of the scheduler
    */
    void draw_frame();
    /**
     *  @brief Draws a legend for better understanding
    */
    void draw_legend();
    /**
     *  @brief Draws a summary for the simulation
    */
    void draw_summary();

    inline bool is_running() {return !sched->done;}

    template<typename Sched, typename... _Args>
    static void run(_Args&&... _args) {
        auto sim = TextScheduler(std::make_unique<Sched>(std::forward<_Args>(_args)...));

        sim.draw_legend();
        
        while(sim.is_running())
            sim.draw_frame();
        
        sim.draw_summary();
    };

private:
    std::unique_ptr<Scheduler> sched;
    std::vector<int> finished;
    std::vector<int> waiting_times;
};