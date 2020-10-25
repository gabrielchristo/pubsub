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

    static void staticCallback(Message msg){
        msg.Print();
    }

    void nonStaticCallback(Message msg){
        msg.Print();
    }

};

int main(int argc, char** argv)
{
    auto pubsub = Dispatcher::Instance();

    int number = 5;
    Message m(Test::MessageType::INT, sizeof(number), &number);
    short token = pubsub->Subscribe("event_1", &Test::staticCallback);
    pubsub->Print();
    pubsub->Publish("event_1", m);

    return 0;
}
