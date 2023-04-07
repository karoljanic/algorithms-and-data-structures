// Clock.hpp
// Class Measuring Execution Time 
// it returns time of executing code in seconds 
// Karol Janic February 2023

#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <chrono>

class Clock {
private:
    std::chrono::steady_clock::time_point lastTimeStamp;
    std::chrono::steady_clock::time_point currentTimeStamp;

public:
    Clock() : lastTimeStamp(std::chrono::steady_clock::now()), currentTimeStamp(std::chrono::steady_clock::now()) { }

    void startMeasurement() {
        lastTimeStamp = std::chrono::steady_clock::now(); 
    }

    double takeMeasurement(bool startNextMeasurement) {
        currentTimeStamp = std::chrono::steady_clock::now(); 

        std::chrono::duration<double> timeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(currentTimeStamp - lastTimeStamp);

        if(startNextMeasurement) {
            lastTimeStamp = currentTimeStamp;
        }

        return timeSpan.count();
    }
};

#endif // CLOCK_HPP