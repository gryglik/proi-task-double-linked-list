# pragma once
#include<vector>
#include<iostream>

class IMessage
{
protected:
    std::string msg;

public:
    virtual ~IMessage() = default;

    virtual IMessage* clone() const = 0;

    void write(std::ostream& os) const { os << "[ " << this->severity() << "\t ] " << this->msg; }

    virtual std::string severity() const = 0;
};

class TraceMessage : public IMessage
{
public:
    TraceMessage(const std::string message) {this->msg = message;}

    TraceMessage* clone() const override {return new TraceMessage(*this);}

    std::string severity() const override {return "TRACE";}
};

class DebugMessage : public IMessage
{
public:
    DebugMessage(const std::string message) {this->msg = message;}

    DebugMessage* clone() const override {return new DebugMessage(*this);}

    std::string severity() const override {return "DEBUG";}
};

class InfoMessage : public IMessage
{
public:
    InfoMessage(const std::string message) {this->msg = message;}

    InfoMessage* clone() const override { return new InfoMessage(*this);}

    std::string severity() const override {return "INFO";}
};

class WarningMessage : public IMessage
{
public:
    WarningMessage(const std::string message) {this->msg = message;}

    WarningMessage* clone() const override { return new WarningMessage(*this);}

    std::string severity() const override {return "WARNING";}
};

class ErrorMessage : public IMessage
{
public:
    ErrorMessage(const std::string message) {this->msg = message;}

    ErrorMessage* clone() const override {return new ErrorMessage(*this);}

    std::string severity() const override {return "ERROR";}
};

class FatalMessage : public IMessage
{
public:
    FatalMessage(const std::string message) {this->msg = message;}

    FatalMessage* clone() const override {return new FatalMessage(*this);}

    std::string severity() const override {return "FATAL";}
};