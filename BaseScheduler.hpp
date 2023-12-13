#pragma once
#include <list>
#include <vector>
#include <string>
#include <tuple>

struct Process
{
    int arrive_time;
    int duration_time;
    int id;
    int time_spent;
};

class Scheduler {
public:
    Scheduler(Scheduler& other) = delete;
    Scheduler(Scheduler&& other) = default;

    Scheduler(const std::vector<int>& arrivals, const std::vector<int>& durations);

    /**
     *  @brief Calculates next thing that the scheduler would do
     *  @return String represenation of what happened
    */
    std::string next_frame_str();

    inline bool running() { return !done; };

protected:
    std::vector<Process> processes;
    std::list<Process> queue;
    int time = 0;
    bool done = false;

    /**
     *  @brief Calculates the next event
    */
    virtual void next_frame() = 0;

    /**
     *  @brief Looks for processes that should be enqueued
     *  @param dt   Defines timeframe for checking process' arrivals, 0 for no limitation
     *  @return     Arrival time of enqueued process
     * 
     *  Loops over all processes looking for the one with the smallest arrival time
     *  that is inside the timeframe [time, time + dt) and enqueues it returning its
     *  arrival time.
    */
    int enqueue_process(int dt);

    /**
     *  @brief Calculates time to next process' arrival
     *  @return tuple (time to the arrival, iterator to process to arrive)
    */
    auto to_arrive() -> std::tuple<int, decltype(processes.begin())>;

    /**
     *  @brief Shows queue's state
     *  @return     String representation of queue
    */
    std::string queue_str();
};