#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "Util.hpp"
#include "RoundRobin.hpp"
#include "FCFS.hpp"
#include "Priority.hpp"
#include "TextSched.hpp"

void display_help();

int main(int argc, char* argv[]) {

    char* fname = nullptr;
    char* outfname = nullptr;
    struct {
        bool roundrobin = false;
        bool fcfs = false;
        bool priority = false;
        bool help = false;
        bool all = false;
        bool file = false;
        bool visual = false;
        bool visualplus = false;
    } flags;

    for(int i = 1; i < argc; i++) {
        if(argv[i][0] != '-') {
            if(fname) {
                std::cout << "Warning: specified filename multiple times! Taking only the 2nd.\n";
            }

            fname = argv[i];
            continue;
        }

        for(auto p = &argv[i][1]; *p != '\0'; p++) {
            auto str = argv[i];
            switch(*p) {
            case 'R':
                flags.roundrobin = true;
                break;
            case 'F':
                flags.fcfs = true;
                break;
            case 'P':
                flags.priority = true;
                break;
            case 'h':
                flags.help = true;
                break;
            case 'f':
                if(flags.file) continue;
                flags.file = true;
                outfname = argv[++i];
                break;
            case 'v':
                if(!flags.visual)
                    flags.visual = true;
                else
                    flags.visualplus = true;
                break;
            case 'a':
                flags.all = true;
                break;
            default:
                std::cout << "Warning: unrecognized option: " << str << '\n';
            }
        }
    }   

    if(flags.help) {
        display_help();
        return 0;
    }

    if(!fname) {
        std::cout << "Error: input file not specified!\n";
        display_help();
        return 1;
    }

    if(!flags.roundrobin && !flags.fcfs &&
        !flags.priority && !flags.all) {
        std::cout << "Error: algorithm not specified!\n";
        display_help();
        return 1;
    }

    //parse input file
    std::ifstream file(fname);
    if(!file) {
        std::cout << "Could not open file: " << fname << '\n';
        return 1;
    }

    //open output file
    std::ofstream ofile(outfname);
    if(!ofile && flags.file) {
        std::cout << "Could not open file: " << outfname << '\n';
        return 1;
    }
    std::ostream& output = flags.file ? ofile : std::cout;

    TextMode mode = TextMode::summary;
    if(flags.visual) 
        mode = mode | TextMode::frames;
    if(flags.visualplus)
        mode = TextMode::all;

    std::vector<int> arrivals;
    std::vector<int> durations;
    std::vector<int> priorities;

    std::string tempstr;

    std::getline(file, tempstr);
    split_stoi(tempstr, ' ', arrivals);
    
    std::getline(file, tempstr);
    split_stoi(tempstr, ' ', durations);

    std::getline(file, tempstr);
    split_stoi(tempstr, ' ', priorities);

    std::getline(file, tempstr);
    int starvation = std::stoi(tempstr);

    std::getline(file, tempstr);
    int quant = std::stoi(tempstr);

    file.close();

    if(flags.all) {
        std::array<std::pair<std::string, float>, 3> wait_table{{
            {"FCFS", 0},
            {"Round-Robin", 0},
            {"Priority", 0}
        }};

        TextScheduler(tag<FCFS>{}, arrivals, durations)
            .run(mode, output)
            .get_avg_wait(wait_table[0].second);

        TextScheduler(tag<RoundRobin>{}, arrivals, durations, quant)
            .run(mode, output)
            .get_avg_wait(wait_table[1].second);

        TextScheduler(tag<Priority>{}, arrivals, durations, priorities, starvation)
            .run(mode | TextMode::show_priority, output)
            .get_avg_wait(wait_table[2].second);

        //sort waiting times in order to compare them
        std::sort(wait_table.begin(), wait_table.end(), [](const auto& a, const auto& b) {
            return a.second < b.second;
        });

        std::cout << "Waiting times for all algorithms:\n";
        for(auto p : wait_table) {
            std::cout << std::setw(12) << std::left << p.first << '|' 
                << std::setw(10) << std::right << p.second << '\n';
        }

        if(ofile)
            ofile.close();

        return 0;
    }
    
    if(flags.fcfs)
        TextScheduler(tag<FCFS>{}, arrivals, durations)
            .run(mode, output);
    if(flags.roundrobin)
        TextScheduler(tag<RoundRobin>{}, arrivals, durations, quant)
            .run(mode, output);
    if(flags.priority)
        TextScheduler(tag<Priority>{}, arrivals, durations, priorities, starvation)
            .run(mode | TextMode::show_priority, output);

    if(ofile)
        ofile.close();

    return 0;
}

void display_help() {
    std::cout << "Usage:\n"
        "schedule [options] [input file]\n\n"
        "Available options:\n"
        "-h shows this message\n"
        "-f [FILE] stores info in a FILE\n"
        "-v shows every step, enter vv for graphical represenation\n"
        "-a selects all algorithms and compares them\n"
        "\nAlgorithms:\n"
        "-R corresponds to Round-robin algorithm\n"
        "-F corresponds to FCFS algorithm\n"
        "-P corresponds to Priority Pre-empting algorithm\n"
        "\nMade by Maciej Suski\n";
}