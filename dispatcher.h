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
    short Subscribe(const std::string& event, FunctionPtr method, const short& priority = 0);

    // overload to generic callback on non static member functions
    template<typename T>
    short Subscribe(const std::string& event, void(T::*method)(const Message&), T* instance, const short& priority = 0)
    {
        auto bind = std::bind(method, instance, std::placeholders::_1);
        return Subscribe(event, bind, priority);
    }

    // publish event with desired message
    void Publish(const std::string& event, const Message& arg);

    // remove callback from desired event
    void Unsubscribe(const std::string& event, const short id);

    // reset all events and subscriptions
    void Reset();

    // print entries on callbacks map
    void Print();

private:

    Dispatcher();

    static Dispatcher* m_instance;

    static short functionID;

    // keeps events and its callback list
    CallbacksMap m_callbacks;
};

#endif
