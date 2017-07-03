#ifndef COMMAND_HPP
#define COMMAND_HPP
#include "hwlib.hpp"
/**
 * \brief command class that can encode and decode our ir protocol
 * testing for bitmask was done at -> http://cpp.sh/4ftmz
 */
typedef unsigned short uint16_t;
class Command {
private:
    static constexpr int get_id(uint16_t data) {
        return (int) (data & 0b0111110000000000 >> 10);
    }
    static constexpr int get_data(uint16_t data) {
        return (int) (data & 0b0000001111100000 >> 5);
    }
    static constexpr bool is_valid(uint16_t data) {
        return (bool) ((get_id(data) ^ get_data(data)) == (data & 0b0000000000011111));
    }

    int id = 0, data = 0;
    uint16_t encoded = -1;
    void encode();
    int decode();
public:
    Command();
    Command(uint16_t data);
    Command(int id, int sender);

    int get_id();
    int get_data();

    uint16_t get_encoded();

    
};
#endif //COMMAND_HPP