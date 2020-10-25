#include "dispatcher.h"

Dispatcher* Dispatcher::m_instance = nullptr;
short Dispatcher::functionID = 0;

Dispatcher* Dispatcher::Instance()
{
    if(m_instance == nullptr)
        m_instance = new Dispatcher;
    return m_instance;
}

Dispatcher::Dispatcher()
{
}

short Dispatcher::Subscribe(const std::string& event, FunctionPtr function, const short& priority)
{
    m_callbacks[event].push_back(Callback(function, functionID, priority));
    return functionID++;
}

void Dispatcher::Unsubscribe(const std::string& event, short id)
{
    short i = 0;
    std::for_each(m_callbacks[event].begin(), m_callbacks[event].end(), [this, &id, &i, &event](Callback cb){
        if(cb.getID() == id)
            m_callbacks[event].erase(m_callbacks[event].begin() + i);
        i++;
    });
}

void Dispatcher::Reset()
{
    m_callbacks.clear();
}

void Dispatcher::Print()
{
    std::for_each(m_callbacks.begin(), m_callbacks.end(), [](CallbacksMapPair pair){
        std::cout << "Event '" << pair.first << "' Callbacks: " << pair.second.size() << std::endl;
    });
}

void Dispatcher::Publish(const std::string& event, const Message& arg)
{
    auto list = m_callbacks[event];

    std::sort(list.begin(), list.end(), [](Callback cbLeft, Callback cbRight){
       return cbLeft.getPriority() > cbRight.getPriority();
    });

    std::for_each(list.begin(), list.end(), [&arg](Callback cb){
        (cb.getMethod())(arg);
    });
}
