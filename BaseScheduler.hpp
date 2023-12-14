#pragma once
#include <list>
#include <vector>
#include <tuple>

struct Process
{
    int arrive_time;
    int duration_time;
    int id;
    int time_spent;
};

enum EventType : int{
    none,
    add_process,
    switch_process,
    finish_process
};

struct SchedulerEvent 
{
    EventType type;
    int pid;
    int pid2;
};

class TextScheduler;

class Scheduler {
public:
    Scheduler(const Scheduler& other) = delete;
    Scheduler(Scheduler&& other) = default;

    Scheduler(const std::vector<int>& arrivals, const std::vector<int>& durations);

    inline bool running() { return !done; };

    friend TextScheduler;

protected:
    std::vector<Process> processes;
    std::list<Process> queue;
    int time = 0;
    bool done = false;

    /**
     *  @brief Calculates the next event
    */
    virtual SchedulerEvent next_frame() = 0;

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
};