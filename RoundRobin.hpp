#pragma once 
#include "BaseScheduler.hpp"
#include <iostream>

class RoundRobin : public Scheduler {
public:
    RoundRobin(const RoundRobin& other) = delete;
    RoundRobin(RoundRobin&& other) = default;
    /**
     *  @brief  Creates a new RR scheduler simulation
     *  @param arrivals     Times at which processes arrive
     *  @param durations    Durations of all processes
     *  @param time_quant   Time given for each process
    */
    RoundRobin(const std::vector<int>& arrivals, const std::vector<int>& durations, int time_quant);

    /**
     *  @brief  Calculates next thing that the scheduler would do
    */
    void next_frame();

private: 
    int time_quant;
    int time_to_change = 0;
};