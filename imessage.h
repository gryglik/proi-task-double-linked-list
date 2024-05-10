# pragma once
#include<vector>
#include<iostream>

struct IMessage
{
    virtual void write(std::ostream& os) const = 0;
    virtual std::string severity() const = 0;
};

class TraceMessage : public IMessage
{
private:
    std::string msg;
public:
    TraceMessage(const std::string message)
        : msg(message) {};

    void write(std::ostream& os) const override
    {
        os << "[ TRACE ] "<< msg;
    }

    std::string severity() const override
    {
        return "Trace";
    }
};

class DebugMessage : public IMessage
{
private:
    std::string msg;
public:
    DebugMessage(const std::string message)
        : msg(message) {};

    void write(std::ostream& os) const override
    {
        os << "[ DEBUG ] "<< msg;
    }

    std::string severity() const override
    {
        return "Debug";
    }
};

class InfoMessage : public IMessage
{
private:
    std::string msg;
public:
    InfoMessage(const std::string message)
        : msg(message) {};

    void write(std::ostream& os) const override
    {
        os << "[ INFO ] "<< msg;
    }

    std::string severity() const override
    {
        return "Info";
    }
};

class WarningMessage : public IMessage
{
private:
    std::string msg;
public:
    WarningMessage(const std::string message)
        : msg(message) {};

    void write(std::ostream& os) const override
    {
        os << "[ WARNING ] "<< msg;
    }

    std::string severity() const override
    {
        return "Warning";
    }
};

class ErrorMessage : public IMessage
{
private:
    std::string msg;
public:
    ErrorMessage(const std::string message)
        : msg(message) {};

    void write(std::ostream& os) const override
    {
        os << "[ ERROR ] "<< msg;
    }

    std::string severity() const override
    {
        return "Error";
    }
};

class FatalMessage : public IMessage
{
private:
    std::string msg;
public:
    FatalMessage(const std::string message)
        : msg(message) {};

    void write(std::ostream& os) const override
    {
        os << "[ FATAL ] "<< msg;
    }

    std::string severity() const override
    {
        return "Fatal";
    }
};