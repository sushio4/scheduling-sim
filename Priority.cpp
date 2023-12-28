#include "Priority.hpp"

Priority::Priority(const std::vector<int>& arrivals, const std::vector<int>& durations,
            const std::vector<int>& priorities, int starvation) :
    Scheduler(arrivals, durations),
    time_quant(starvation),
    time_to_change(starvation) {

    for(int i = 0; i < priorities.size(); i++) {
        processes.at(i).priority = priorities[i];
    }

    name = "Priority";
}

SchedulerEvent Priority::next_frame() {
    auto tup = to_arrive();
    int arrive_time = std::get<0>(tup);

    if(queue.empty() && time == 0) {
        queue.push_back(*std::get<1>(tup));
        time += arrive_time;
        time_to_change -= arrive_time;
        return {EventType::add_process, (*std::get<1>(tup)).id, 0};
    }

    auto& current = queue.front();
    int finish_time = current.duration_time - current.time_spent;

    //look for the smallest time 
    auto result = SchedulerEvent{EventType::none, 0, 0};

    if(arrive_time <= finish_time &&
       arrive_time <= time_to_change) {
        //process arrives
        result = {EventType::add_process, (*std::get<1>(tup)).id, 0};

        time += arrive_time;
        time_to_change -= arrive_time;
        current.time_spent += arrive_time;

        //check if it's of a higher priority than the current process
        if((*std::get<1>(tup)).priority > queue.front().priority) {
            result.type = EventType::add_switch;
            result.pid = current.id;
            queue.push_front(*std::get<1>(tup));
            result.pid2 = queue.front().id;
        }
        else {
            queue.push_back(*std::get<1>(tup));
        }
    }
    else if((finish_time < arrive_time &&
            finish_time < time_to_change) 
            ) {
        //process finishes
        result = {EventType::finish_process, queue.front().id, 0};

        queue.pop_front();
        time += finish_time;
        time_to_change -= finish_time;

        if(queue.size() == 1) {
            done = true;
            return result;
        }
        //now get the highest priority process
        auto it = highest_priority();
        auto p = *it;
        queue.erase(it);
        queue.push_front(p);
    }
    else {
        //we starve processes
        result = {EventType::starve, 0, 0};

        for(auto& p : queue) {
            p.priority++;
        }
        current.priority--;

        current.time_spent += time_to_change;
        time += time_to_change;
        time_to_change = time_quant;

        //check for priority
        auto it = highest_priority();
        if(it != queue.end() &&
          it->priority > current.priority) {
            auto p = *it;

            result.type = EventType::starve_switch;
            result.pid = it->id;

            queue.erase(it);
            queue.push_front(p);
        }
    }

    if(queue.empty())
        done = true;

    return result;
}

auto Priority::highest_priority() -> decltype(queue.begin()) {
    int highest = -1;
    auto p = queue.end();

    auto it = queue.begin();
    it++;

    for(; it != queue.end(); it++) {
        if(it->priority > highest) {
            highest = it->priority;
            p = it;
        }
    }

    return p;
}
