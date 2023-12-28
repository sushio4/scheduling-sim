#pragma once

#include "BaseScheduler.hpp"

class Priority : public Scheduler {
public:
    Priority(const Priority& other) = delete;
    Priority(Priority&& other) = default;

    /**
     *  @brief  Creates a new RR scheduler simulation
     *  @param arrivals     Times at which processes arrive
     *  @param durations    Durations of all processes
     *  @param priorities   Priority values for respective processes
     *  @param starvation   Time quant after which every waiting process will have an increased priority
    */
    Priority(const std::vector<int>& arrivals, const std::vector<int>& durations,
            const std::vector<int>& priorities, int starvation);
    
    auto next_frame() -> SchedulerEvent;

private:
    auto highest_priority() -> decltype(queue.begin());

    int time_quant;
    int time_to_change = 0;
};