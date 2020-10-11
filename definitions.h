#ifndef DEFINITIONS_H
#define DEFINITIONS_H
#pragma once

#include <functional>
#include <unordered_map>
#include <vector>
#include <string.h>
#include <iostream>
#include <algorithm>

typedef unsigned char byte;

// message struct to pass between callbacks
class Message{

    #pragma pack(1)
    short m_id;    // message identifier (2 bytes)
    short m_len;   // message size (2 bytes)
    void* m_data;  // pointer to generic data (m_len bytes)
    #pragma pack()

public:

    Message(short id, short len, const void* data) : m_id(id), m_len(len)
    {
        m_data = malloc(m_len);
        memcpy(m_data, data, m_len);
    }

    void Print()
    {
        std::cout << "Msg ID:" << m_id << " Msg Size:" << m_len << " Msg Content:";
        for(int i(0); i<m_len; i++) printf("[%X]", ((byte*)m_data)[i]);
        std::cout << std::endl;
    }

    short getMsgID() const{return m_id;}
    short getMsgSize() const{return m_len;}
    const void* getData(){return m_data;}

};

// callback default method
typedef std::function<void(Message*)> FunctionPtr;

// keeps function and its identifier
class Callback{
  FunctionPtr m_method;
  short m_id;
public:
  Callback(FunctionPtr method, short id) : m_method(method), m_id(id){}
  const FunctionPtr getMethod(){return m_method;}
  short getID() const{return m_id;}
};

// data structure to map the events and callback registrations
typedef std::unordered_map<std::string, std::vector<Callback>> CallbacksMap;

#endif
