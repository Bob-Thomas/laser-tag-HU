/**
 * \file      command.hpp
 * \author    Bob Thomas
 * \copyright Copyright (c) 2017, Lasertak
 */
#include "command.hpp"

Command::Command() : id(0), data(0) {
    encode();
}
Command::Command(int id, int data) : id(id), data(data) {
    encode();
}

Command::Command(uint16_t data)  {
    encoded = data;
    if(!decode()) {
        hwlib::cout << "invalid command\n";
    }
}

void Command::encode() {
    encoded = (1 << 15) + (id << 10) + (data << 5) + ((id ^ data));
}
int Command::decode() {
    if(!is_valid(data) && !((data >> 15) & 1)) {
        return 0;
    } else {
        id = get_id(data);
        data = get_data(data);
    }
    return 1;
}

uint16_t Command::get_encoded() {
    return encoded;
}

int Command::get_id() {
    return id;
}

int Command::get_data() {
    return data;
}