#ifndef DEFINITIONS_H
#define DEFINITIONS_H
#pragma once

#include <functional>
#include <unordered_map>
#include <vector>
#include <string.h>
#include <iostream>
#include <algorithm>

#define BUFFER_SIZE 200

typedef unsigned char byte;

// message struct to pass between callbacks
class Message{

    #pragma pack(1)
    short m_id;    // message identifier (2 bytes)
    short m_len;   // message size (2 bytes)
    byte m_data[BUFFER_SIZE];  // byte array to keep generic data (BUFFER_SIZE bytes)
    #pragma pack()

public:

    Message(short id, short len, const void* data) : m_id(id), m_len(len)
    {
        memset(&m_data[0], 0, BUFFER_SIZE);
        memcpy(&m_data[0], data, m_len);
    }

    void Print() const
    {
        std::cout << "Msg ID:" << m_id << " Msg Size:" << m_len << " Msg Content:";
        for(int i(0); i < m_len; i++) printf("[%X]", m_data[i]);
        std::cout << std::endl;
    }

    short getMsgID() const{return m_id;}
    short getMsgSize() const{return m_len;}
    const void* getData() const{return &m_data[0];}

};

// callback default method
typedef std::function<void(const Message&)> FunctionPtr;

// keeps function and its identifier
class Callback{
  FunctionPtr m_method;
  short m_id;
  short m_priority;
public:
  Callback(FunctionPtr method, short id, short priority) : m_method(method), m_id(id), m_priority(priority){}
  const FunctionPtr getMethod(){return m_method;}
  short getID() const{return m_id;}
  short getPriority() const{return m_priority;}
};

// data structure to map the events and callback registrations
typedef std::unordered_map<std::string, std::vector<Callback>> CallbacksMap;
typedef std::pair<std::string, std::vector<Callback>> CallbacksMapPair;

#endif
