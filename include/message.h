#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
struct message {
    int id;
    std::string str;
    message(int id_arg, const std::string & str_arg):
        id(id_arg), str(str_arg){;};
    const std::string & get_str() {
        return str;
    }
    int get_id() {
        return id;
    }
};
#endif 
