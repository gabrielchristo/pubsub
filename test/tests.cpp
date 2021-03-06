
#include "../dispatcher.h"
#include <gtest/gtest.h>

// global auxiliar variables to test the callbacks
short idResult(-1);
int intResult(-1);
float floatResult(-1);
const char* stringResult = NULL;

enum MessageTypes {
    NONE = -1,
    INT = 0,
    FLOAT,
    STRING,
    STRUCT,
    NUMBER_OF_MESSAGE_TYPES
};

enum Priority {
    NORMAL = 0,
    HIGH
};

struct TestClass {

    static void intMessageTest(const Message& msg) {
        intResult = *reinterpret_cast<const int*>(msg.getData());
        idResult = msg.getMsgID();
    }

    void floatMessageTest(const Message& msg) {
        floatResult = *reinterpret_cast<const float*>(msg.getData());
        idResult = msg.getMsgID();
    }

    static void stringMessageTest(const Message& msg){
        stringResult = reinterpret_cast<const std::string*>(msg.getData())->c_str();
        idResult = msg.getMsgID();
    }

    void unsubscribeTest(const Message& msg){
        stringResult = "unsubscribe_test";
    }

    static void priorityTestNormal(const Message& msg){
        intResult = *(int*)msg.getData();
    }

    static void priorityTestHigh(const Message& msg){
        intResult = *(int*)msg.getData() + 1;
    }

};

// test integer as callback message data
TEST(MessageParameter, IntMessageTest){
    auto d = Dispatcher::Instance();
    int data(-6), id(MessageTypes::INT);
    Message m(id, sizeof(data), &data);
    d->Subscribe("IntMessageTest", &TestClass::intMessageTest);
    d->Publish("IntMessageTest", m);
    ASSERT_EQ(intResult, data);
    ASSERT_EQ(idResult, id);
}

// test float as callback message data
TEST(MessageParameter, FloatMessageTest){
    auto d = Dispatcher::Instance();
    TestClass testClass;
    int id(MessageTypes::FLOAT); float data(4.5);
    Message m(id, sizeof(data), &data);
    d->Subscribe("FloatMessageTest", &TestClass::floatMessageTest, &testClass);
    d->Publish("FloatMessageTest", m);
    ASSERT_FLOAT_EQ(floatResult, data);
    ASSERT_EQ(idResult, id);
}

// test std::string as callback message data
TEST(MessageParameter, StringMessageTest){
    auto d = Dispatcher::Instance();
    std::string str("string_test");
    int id(MessageTypes::STRING);
    Message m(id, sizeof(str), &str);
    d->Subscribe("StringMessageTest", &TestClass::stringMessageTest);
    d->Publish("StringMessageTest", m);
    ASSERT_STREQ(stringResult, str.c_str());
    ASSERT_EQ(idResult, id);
}

// test unsubscription of callback function
TEST(UnsubscribeTest, UnsubscribeTest){
    auto d = Dispatcher::Instance();
    TestClass testClass;
    short token = d->Subscribe("UnsubscribeTest", &TestClass::unsubscribeTest, &testClass);
    d->Unsubscribe("UnsubscribeTest", token);
    Message m(MessageTypes::NONE, 0, NULL);
    d->Publish("UnsubscribeTest", m);
    ASSERT_STRNE(stringResult, "unsubscribe_test");
}

// test callbacks priority
TEST(PriorityTest, PriorityTest){
    auto d = Dispatcher::Instance();
    d->Subscribe("PriorityTest", &TestClass::priorityTestNormal, NORMAL);
    d->Subscribe("PriorityTest", &TestClass::priorityTestHigh, HIGH);
    int data(13);
    Message msg(MessageTypes::INT, sizeof(int), &data);
    d->Publish("PriorityTest", msg);
    ASSERT_EQ(intResult, data);
}

// test reset callbacks map
TEST(ResetTest, ResetTest){
    auto d = Dispatcher::Instance();
    int data(11); intResult = data; data++;
    d->Subscribe("ResetTest", &TestClass::intMessageTest);
    Message msg(MessageTypes::INT, sizeof(int), &data);
    d->Reset();
    d->Publish("ResetTest", msg);
    ASSERT_EQ(intResult, data-1);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
