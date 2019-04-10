#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include "event.pb.h"

typedef myevent::event message;

/*class message {
 private:
    int id;
    std::string str;
 public:
    message(int id_arg, const std::string & str_arg):
        id(id_arg), str(str_arg){;};
    const std::string & get_str() const{
        return str;
    }
    int get_id() const{
        return id;
    }
};*/
#endif 
