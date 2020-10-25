
#include "../dispatcher.h"
#include <gtest/gtest.h>

// global auxiliar variables
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

struct TestClass {

    static void intMessageTest(Message* msg) {
        intResult = *reinterpret_cast<const int*>(msg->getData());
        idResult = msg->getMsgID();
    }

    void floatMessageTest(Message* msg) {
        floatResult = *reinterpret_cast<const float*>(msg->getData());
        idResult = msg->getMsgID();
    }

    static void stringMessageTest(Message* msg){
        stringResult = reinterpret_cast<const std::string*>(msg->getData())->c_str();
        idResult = msg->getMsgID();
    }

    void unsubscribeTest(Message* msg){
        stringResult = "unsubscribe_test";
    }

};

// test integer as callback message data
TEST(PubSub, IntMessageTest){
    auto d = Dispatcher::Instance();
    int data(6), id(MessageTypes::INT);
    Message m(id, sizeof(data), &data);
    d->Subscribe("IntMessageTest", &TestClass::intMessageTest);
    d->Publish("IntMessageTest", &m);
    ASSERT_EQ(intResult, data);
    ASSERT_EQ(idResult, id);
}

// test float as callback message data
TEST(PubSub, FloatMessageTest){
    auto d = Dispatcher::Instance();
    TestClass testClass;
    int id(MessageTypes::FLOAT); float data(4.5);
    Message m(id, sizeof(data), &data);
    d->Subscribe("FloatMessageTest", std::bind(&TestClass::floatMessageTest, &testClass, std::placeholders::_1));
    d->Publish("FloatMessageTest", &m);
    ASSERT_FLOAT_EQ(floatResult, data);
    ASSERT_EQ(idResult, id);
}

// test std::string as callback message data
TEST(PubSub, StringMessageTest){
    auto d = Dispatcher::Instance();
    std::string str("string_test");
    int id(MessageTypes::STRING);
    Message m(id, sizeof(str), &str);
    d->Subscribe("StringMessageTest", &TestClass::stringMessageTest);
    d->Publish("StringMessageTest", &m);
    ASSERT_STREQ(stringResult, str.c_str());
    ASSERT_EQ(idResult, id);
}

// test unsubscription of callback function
TEST(PubSub, UnsubscribeTest){
    auto d = Dispatcher::Instance();
    TestClass testClass;
    short token = d->Subscribe("UnsubscribeTest", std::bind(&TestClass::unsubscribeTest, &testClass, std::placeholders::_1));
    d->Unsubscribe("UnsubscribeTest", token);
    Message m(MessageTypes::NONE, 0, NULL);
    d->Publish("UnsubscribeTest", &m);
    ASSERT_STRNE(stringResult, "unsubscribe_test");
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
