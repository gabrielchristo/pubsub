#ifndef MANAGER_H
#define MANAGER_H
#pragma once

#include "definitions.h"

// singleton that manages events and registrations
class Dispatcher
{

public:

    static Dispatcher* Instance();

    // add callback method to desired event
    short Subscribe(const std::string& event, FunctionPtr method);

    // publish event with desired message
    void Publish(const std::string& event, Message* arg);

    // remove callback from desired event
    void Unsubscribe(const std::string& event, short id);

    // reset all events and subscriptions
    void Reset();

private:

    Dispatcher();

    static Dispatcher* m_instance;

    static short functionID;

    // keeps events and its callback list
    CallbacksMap m_callbacks;
};

#endif
