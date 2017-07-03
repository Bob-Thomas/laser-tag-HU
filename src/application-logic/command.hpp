/**
 * \file      command.hpp
 * \author    Bob Thomas
 * \brief     Class that can be used to decode and encode the ir protocol
 * \copyright Copyright (c) 2017, Lasertak
 */
#ifndef COMMAND_HPP
#define COMMAND_HPP
#include "hwlib.hpp"
/**
 * \brief command class that can encode and decode our ir protocol
 * testing for bitmask was done at -> http://cpp.sh/4ftmz
 */
class Command {
private:
    /**
     * \brief returns a bool by checking the checksum
     * The checksum is a XOR of the id and data
     */
    static constexpr bool is_valid(uint16_t data) {
        return (bool) ((get_id(data) ^ get_data(data)) == (data & 0b0000000000011111));
    }
    /// id of the sender
    int id = 0;
    /// data of the command
    int data = 0;
    /// Encoded comand in 16bits
    uint16_t encoded = -1;

    /**
     * \brief Encodes the id and data into a 16bit and fills the encoded variable
     * shifts the id and data into a 16 bits uint16_t generates a checksum by XORING the id and data
     *
     */
    void encode();
    /**
     * \brief decodes the uint16_t into usable id and data values and checks if the checksum is valid
     */
    int decode();
public:
    /**
     * \brief contstructor for an Empty command
     */
    Command();

    /**
     * \brief constructor to construct a command from a bitstream
     * \param[in] data a uint16_t bitstream
     */
    Command(uint16_t data);

    /**
     * \brief constructor to create a command from id and data
     * Creates a command for the given id and data and fills the encoded variable with the encoded value of id and data plus checksum
     * \param[in] id the ID you want to send as
     * \param[in] data The data you want to send
     */
    Command(int id, int data);

    /**
     * \brief returns a int combined from 5 bits msb skipping the first
     * This represents the id in our ir protocol
     */
    static constexpr int get_id(uint16_t data) {
        return (int) ((data & 0b0111110000000000) >> 10);
    }
    /**
     * \brief returns a int combined from 10 bits msb skipping the first
     * This represents the data in our ir protocol
     */
    static constexpr int get_data(uint16_t data) {
        return (int) ((data & 0b0000001111100000) >> 5);
    }

    /**
     * \brief returns the id
     */
    int get_id();
    /**
     * \brief returns the data
     */
    int get_data();

    /**
     * returns the encoded bitstream of the command
     */
    uint16_t get_encoded();


};
#endif //COMMAND_HPP