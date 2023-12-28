#pragma once

#include "BaseScheduler.hpp"

class FCFS : public Scheduler {
public:
    FCFS(const FCFS& other) = delete;
    FCFS(FCFS&& other) = default;
    /**
     *  @brief  Creates a new FCFS scheduler simulation
     *  @param arrivals     Times at which processes arrive
     *  @param durations    Durations of all processes
    */
    FCFS(const std::vector<int>& arrivals, const std::vector<int>& durations);

    /**
     *  @brief  Calculates next thing that the scheduler would do
    */
    auto next_frame() -> SchedulerEvent;
};