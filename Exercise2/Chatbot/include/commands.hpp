#ifndef INC_TINNES02_COMMANDS_HPP
#define INC_TINNES02_COMMANDS_HPP


#include "Arduino.h"


typedef void (*fn_command_callback)(void *args, uint8_t len);


const uint8_t MAX_DESCRIPTOR_LENGTH = 10;



class Command
{
    public:
                Command(uint8_t id, char *descriptor, fn_command_callback callback);
        void    call(void *args, uint8_t len);
        char*   get_descriptor();

    private:
        uint8_t             _id;
        char                _descriptor[MAX_DESCRIPTOR_LENGTH];
        fn_command_callback _callback;
};


struct CommandNode
{
    Command *command;
    struct CommandNode *next; 
};


class CommandHandler
{
    public:
                CommandHandler(char prefix, uint8_t max_depth);
        void    register_command(Command *command);
        void    execute_command(char *descriptor, void *args, uint8_t len);
        uint8_t get_total_commands();

    private:
        char                _command_prefix;
        uint8_t             _max_depth;
        struct CommandNode* _head;
};


#endif