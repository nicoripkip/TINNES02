#include "commands.hpp"
#include "Arduino.h"


Command::Command(uint8_t id, char *descriptor, fn_command_callback callback)
{
    this->_id = id;
    memset(this->_descriptor, 0, 10);
    strncpy(this->_descriptor, descriptor, MAX_DESCRIPTOR_LENGTH);
    this->_callback = callback;
}


void Command::call(void *args, uint8_t len)
{
    this->_callback(args, len);
}


char* Command::get_descriptor()
{
    return this->_descriptor;
}


CommandHandler::CommandHandler(char prefix, uint8_t max_depth)
{
    this->_command_prefix = prefix;
    this->_max_depth = max_depth;
    this->_head = nullptr;
}


void CommandHandler::register_command(Command *command)
{
    Serial.println("ESP32 tries to register a new command!");

    if (this->_head == nullptr) {
        Serial.println("Henk");
        this->_head = (struct CommandNode *)malloc(sizeof(struct CommandNode));
        Serial.println("Henk 2");
        this->_head->command = command;
        this->_head->next = nullptr;
    } else {
        struct CommandNode *temp = this->_head;
        while(temp != nullptr) {
            temp = temp->next;
        }

        temp = (struct CommandNode *)malloc(sizeof(struct CommandNode));
        this->_head->command = command;
        this->_head->next = nullptr;
    }

    Serial.println("ESP32 has succesfully registered a new command!");
}


void CommandHandler::execute_command(char *descriptor, void *args, uint8_t len)
{
    if (this->_head != nullptr) {
        struct CommandNode *tmp = this->_head;

        while (tmp != nullptr) {
            char buff[11];
            memset(buff, 0, 11);
            strncat(buff, &this->_command_prefix, 1);
            strncat(buff, tmp->command->get_descriptor(), 10);
            // snprintf(buff, 11, "%s%s", &this->_command_prefix, tmp->command->get_descriptor());

            Serial.println(descriptor);
            Serial.println(buff);
            Serial.println(strcmp(descriptor, buff));

            if (strcmp(descriptor, buff) == 0) {
                tmp->command->call(args, len);
            }

            tmp = tmp->next;
        }
    }
}


uint8_t CommandHandler::get_total_commands()
{
    uint8_t i = 0;

    struct CommandNode *tmp = this->_head;
    while (tmp != nullptr) {
        i++;
        tmp = tmp->next;
    }

    return i;
}