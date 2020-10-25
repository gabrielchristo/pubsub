## Publish Subscribe Example ##

A simple argument-and-event-based publish-subscribe implementation where a singleton manages the events and generic callbacks

Support to static and non-static methods

### Tests ###

Using google unit test framework (requires pthread)

```
git clone https://github.com/google/googletest/
cd googletest && mkdir build && cd build && cmake ../ && make
```

### Static Methods ###

For static methods you just need to pass the function pointer to the Subscribe call

```
short token = pubsub->Subscribe("event", &Class::callbackFunction);
```

### Non-Static Methods ###

In this case you must bind the function pointer to the caller object instance pointer

Furthermore you must pass the std::placeholder::_1 argument, which represents the fixed Message parameter

```
Class m_class;
short token = pubsub->Subscribe("event", std::bind(&Class::callbackFunction, &m_class, std::placeholders::_1));
```

### TO DO ###
- set/get notify enabled
- use fixed-size buffer instead void pointer
- add tests: struct data, unsubscribe, reset, callback order
- callback priority
- convert message pointer to const reference
- dispatcher print table method
