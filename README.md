## Publish Subscribe Example ##

A simple argument-and-event-based publish-subscribe implementation where a singleton manages the events and generic callbacks

Support to static and non-static methods

### Tests ###

Using google unit test framework (requires pthread)

```
git clone https://github.com/google/googletest/
cd googletest && mkdir build && cd build && cmake ../ && make
```
### Callback ###

Every callback method must have the following signature

```
void callbackMethod(const Message& msg)
{
    ...
}
```

### Static Callback Methods ###

For static methods you just need to pass the function pointer to the Subscribe call

```
short token = pubsub->Subscribe("event", &Class::callbackFunction);
```

### Non-Static Callback Methods ###

In this case you must pass the function pointer and the caller object instance pointer

```
Class m_class;
short token = pubsub->Subscribe("event", &Class::callbackFunction, &m_class);
```
### Publish ###

To dispatch you must create a message and publish to desired events

```
int msgType = MsgEnum::MyStructType;
MyStruct myStruct;
Message msg(msgType, sizeof(MyStruct), &myStruct);
pubsub->Publish("event", msg);
```
