#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include "event.pb.h"

#define CONNECTION_ABORTED 8

typedef myevent::event message;
typedef myevent::object object;
typedef myevent::command command;

#endif 
