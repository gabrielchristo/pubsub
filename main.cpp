#include "dispatcher.h"

struct Test{

    enum MessageType {
        NONE = -1,
        INT = 0,
        FLOAT,
        STRING,
        STRUCT,
        NUMBER_OF_MESSAGE_TYPES
    }; // static enum as message identifier

    static void staticCallback(const Message& msg){
        msg.Print();
    }

    void nonStaticCallback(const Message& msg){
        msg.Print();
    }

};

int main(int argc, char** argv)
{
    auto pubsub = Dispatcher::Instance();
    Test test;

    int number = 5;
    Message m(Test::MessageType::INT, sizeof(number), &number);

    pubsub->Subscribe("event_1", &Test::staticCallback);
    pubsub->Subscribe("event_2", &Test::nonStaticCallback, &test);
    pubsub->Print();

    pubsub->Publish("event_1", m);
    pubsub->Publish("event_2", m);

    return 0;
}
