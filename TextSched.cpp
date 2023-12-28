#include "TextSched.hpp"
#include <iomanip>
#include <numeric>

TextScheduler::TextScheduler(std::unique_ptr<Scheduler>&& ptr) :
    sched(std::move(ptr)) {
    finished.reserve(sched->processes.size());
    waiting_times.reserve(sched->processes.size());
}

void TextScheduler::draw_frame(TextMode mode, std::ostream& outstream) {
    //update
    auto event = sched->next_frame();

    if(event.type == EventType::finish_process) {
        waiting_times.push_back(sched->time - sched->processes[event.pid].arrive_time);
        //save who finished
        finished.push_back(event.pid);
    }

    using namespace std;
    /** should look like this
     *           [   P0   ]
     * |time |   [a:  00  ]
     * |  2  |   [t:  02  ]
     *           [d:  12  ]
    */
    if(mode & TextMode::frames)
    switch(event.type) {
    case EventType::add_process:
        outstream << "Process P" << event.pid << " arrived at the end of the queue\n";
        break;
    case EventType::switch_process:
        outstream << "Time is up for process P" << event.pid << " and it's switched for P" << event.pid2 << '\n';
        break;
    case EventType::finish_process:
        outstream << "Process P" << event.pid << " has finished and it's removed from the queue\n";
        break;
    case EventType::add_switch:
        outstream << "Process P" << event.pid2 << " arrived and pre-empted P" << event.pid << '\n';
        break;
    case EventType::starve:
        outstream << "Waiting processes have been starved\n";
        break;
    case EventType::starve_switch:
        outstream << "Waiting processes have been starved. Switching execution to P" << event.pid << '\n';
        break;
    default:
        outstream << "This should not happen. Contact developer: suskimaciej@interia.pl\n";
        return;
    }

    if(!(mode & TextMode::visual)) return;
    //first line
    outstream << "\n          ";
    for(auto p : sched->queue) {
        outstream << "[   P" << setw(4) << left << p.id << "]  ";
    }
    //2nd
    outstream << "\n|time |   ";
    for(auto p : sched->queue) {
        outstream << "[a:" << setw(6) << right << p.arrive_time << "]  ";
    }
    //3rd
    outstream << "\n|" << setw(5) << left << sched->time << "|   ";
    for(auto p :sched->queue) {
        outstream << "[t:" << setw(6) << right << p.time_spent << "]  ";
    }
    //4th
    outstream << "\n          ";
    for(auto p : sched->queue) {
        outstream << "[d:" << setw(6) << right << p.duration_time << "]  ";
    }
    //5th
    outstream << "\n          ";
    for(auto p : sched->queue) {
        outstream << "[p:" << setw(6) << right << p.priority << "]  ";
    }
    outstream << "\n\n";
}

void TextScheduler::draw_legend(std::ostream& outstream) {
    outstream << "\"time\" stands for time elapsed in the system\n"
        "\"Pn\" is the process with id n\n"
        "\"a\" is the arrival time of a process\n"
        "\"t\" is the time process has been active\n"
        "\"d\" is the total duration of a process, how long does it take\n\n";
}

void TextScheduler::draw_summary(std::ostream& outstream) {
    outstream << "Processes finished with such order:\n";
    for(auto it = finished.begin(); it < finished.end(); it++) {
        if(it != finished.begin()) 
            outstream << ", ";
        outstream << 'P' << *it;
    }
    outstream << "\n\nFinish times in order:\n";
    for(auto it = waiting_times.begin(); it < waiting_times.end(); it++) {
        if(it != waiting_times.begin())
            outstream << ", ";
        outstream << *it;
    }
    //calculate average waiting time
    int sum = std::accumulate(waiting_times.begin(), waiting_times.end(), 0);
    average_wait = (float)sum / (float)waiting_times.size();
    outstream << "\n\nAverage finish time: " << average_wait << "\n\n";
}

TextScheduler& TextScheduler::run(TextMode mode, std::ostream& outstream) {
    outstream << "----Running algorithm: " << sched->name << "----\n\n";

    if(mode & TextMode::legend)
        draw_legend(outstream);
    
    while(is_running())
        draw_frame(mode, outstream);
    
    if(mode & TextMode::summary)
        draw_summary(outstream);

    return *this;
};