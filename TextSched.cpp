#include "TextSched.hpp"
#include <iomanip>
#include <iostream>

TextScheduler::TextScheduler(std::unique_ptr<Scheduler>&& ptr) :
    sched(std::move(ptr)) {}

void TextScheduler::draw_frame() {
    //update
    sched->next_frame();

    using namespace std;
    /** should look like this
     *           [   P0   ]
     * |time |   [a:  00  ]
     * |  2  |   [t:  02  ]
     *           [d:  12  ]
    */

    //first line
    cout << "\n          ";
    for(auto p : sched->queue) {
        cout << "[   P" << setw(4) << left << p.id << "]  ";
    }
    //2nd
    cout << "\n|time |   ";
    for(auto p : sched->queue) {
        cout << "[a:" << setw(6) << right << p.arrive_time << "]  ";
    }
    //3rd
    cout << "\n|" << setw(5) << left << sched->time << "|   ";
    for(auto p :sched->queue) {
        cout << "[t:" << setw(6) << right << p.time_spent << "]  ";
    }
    //4th
    cout << "\n          ";
    for(auto p : sched->queue) {
        cout << "[d:" << setw(6) << right << p.duration_time << "]  ";
    }
    cout << '\n';
}