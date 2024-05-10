#pragma once
#include "imessage.h"
#include <iostream>
#include <vector>

class Logger
{
private:
    std::vector<IMessage*> logs;
public:
    Logger() = default;
    Logger(const Logger&&) = delete;
    Logger(const Logger&) = delete;

    ~Logger()
    {
        for (auto log : logs)
            delete log;
    }

    void log(const IMessage& msg) {this->logs.push_back(msg.clone());}

    Logger& operator<<(const IMessage& msg)
    {
        this->log(msg);
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Logger& logger)
    {
        for (auto log : logger.logs)
        {
            (*log).write(os);
            os << "\n";
        }

        return os;
    }
};