#ifndef UTILS_H
#define UTILS_H

#include <string_view>
#include <iostream>
#include <chrono>

namespace Minecraft {
namespace Utils {

enum LogLevel {
    LOG_TYPE_WARNING,
    LOG_TYPE_INFO,
    LOG_TYPE_ERROR
};    


inline void PrintCurrentTime() {

    using namespace std::chrono;

    auto now = zoned_time{current_zone(), system_clock::now()}.get_local_time();

    auto today = floor<days>(now);
    hh_mm_ss time{floor<seconds>(now - today)};

    std::cout << "[" << time.hours().count() << ":" << time.minutes().count() << ":" << time.seconds().count() << "]";
}

inline void LogMessage(LogLevel level, std::string_view text) {

    static constexpr std::array<std::string_view, 3> logLabels = {
        "[WARNING]", "[INFO]", "[ERROR]"
    };

    PrintCurrentTime(); // add the time before the msg
    std::cout << logLabels[level]  << " " << text << "\n";
}



}
}
#endif