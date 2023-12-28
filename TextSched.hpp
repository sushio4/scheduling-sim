#pragma once
#include "BaseScheduler.hpp"
#include "Util.hpp"

#include <string>
#include <memory>
#include <iostream>

enum class TextMode : unsigned char {
    none    = 0,
    visual  = 1,
    frames  = 2,
    summary = 4,
    legend  = 8,
    all     = 15
};

inline TextMode operator|(TextMode a, TextMode b) {
    return static_cast<TextMode>(static_cast<unsigned char>(a) | static_cast<unsigned char>(b));
}

inline unsigned char operator&(TextMode a, TextMode b) {
    return static_cast<unsigned char>(a) & static_cast<unsigned char>(b);
}

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
     * @brief Constructor that creates appropriate scheduler
     * @param _args arguments to the consttructor
    */
    template<typename Sched, typename... _Args>
    TextScheduler(tag<Sched>, _Args&&... _args) : 
        TextScheduler(std::make_unique<Sched>(std::forward<_Args>(_args)...)) 
    {}

    /**
     *  @brief Draws the next frame of the scheduler
    */
    void draw_frame(TextMode mode, std::ostream& outstream);
    /**
     *  @brief Draws a legend for better understanding
    */
    void draw_legend(std::ostream& outstream);
    /**
     *  @brief Draws a summary for the simulation
    */
    void draw_summary(std::ostream& outstream);

    inline bool is_running() {return !sched->done;}

    /** 
     * @brief runs the simulation
     * @param mode indicates what information shall be printed
     * @param outstream points where to print information
     * @return returns itself to allow method chaining
    */
    auto run(TextMode mode = TextMode::all, std::ostream& outstream = std::cout) -> TextScheduler&;

    /**
     * @brief returns average waiting time of threads
     * @param avg_wait reference to where to store it
     * @return returns itself to allow method chaining
    */
    inline TextScheduler& get_avg_wait(float& avg_wait) {
        avg_wait = average_wait;
        return *this;
    };

private:
    std::unique_ptr<Scheduler> sched;
    std::vector<int> finished;
    std::vector<int> waiting_times;
    float average_wait = 0;
};