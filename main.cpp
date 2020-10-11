
#include "dispatcher.h"

struct Test{

    enum MessageType {
        INT = 0,
        FLOAT,
        STRING,
        NUMBER_OF_MESSAGE_TYPES
    }; // static enum as message identifier

    // static callback
    static void callback1(Message* msg){
        msg->Print();
    }

    // non-static callback
    void callback2(Message* msg){
        msg->Print();
        if(msg->getMsgID() == MessageType::STRING){
            std::cout << *(std::string*)msg->getData() << std::endl;
        }
    }

};

int main(int argc, char** argv)
{
    auto pubsub = Dispatcher::Instance();
    auto test = new Test;

    // static method
    int n1 = 5;
    float n2 = 5.67;
    Message m1(Test::MessageType::INT, sizeof(n1), &n1);
    Message m2(Test::MessageType::FLOAT, sizeof(n2), &n2);
    short token1 = pubsub->Subscribe("event_1", &Test::callback1);
    pubsub->Publish("event_1", &m1);
    pubsub->Publish("event_1", &m2);

    // non-static method (must bind callback to object instance pointer)
    // the std::placeholder::_1 defines a fixed argument (in this case Message*)
    std::string str = "hello world!";
    Message m3(Test::MessageType::STRING, str.length(), &str);
    short token2 = pubsub->Subscribe("event_2", std::bind(&Test::callback2, test, std::placeholders::_1));
    short token3 = pubsub->Subscribe("event_2", &Test::callback1);
    pubsub->Unsubscribe("event_2", token3);
    pubsub->Publish("event_2", &m3);

    return 0;
}
