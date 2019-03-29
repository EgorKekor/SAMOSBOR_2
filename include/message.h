#ifndef MESSAGE_H
#define MESSAGE_H
struct message {
    int id;
    int mes;
    message(int id_arg, int mes_arg):
        id(id_arg), mes(mes_arg){;};
    message() {;};
};
#endif 
