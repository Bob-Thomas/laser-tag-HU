/**
 * \file        ir-send-controller.hpp
 * \brief       This class will send a 16 bit IR-signal.
 * \author      René de Kluis
 * \copyright   Copyright (c) 2017, The R2D2 Team
 * \license     See LICENSE
 */

#ifndef LASER_IR_H
#define LASER_IR_H

#include "hwlib.hpp"

class IrController {
private:
    hwlib::target::d2_36kHz & diode;

    /**
     * \brief Send a bit
     *
     * This function will send a bit that is given as parameter.
     *
     * \param[in] b Bit to send
     *
     */
    void sendBit(bool b);
public:

    /**
     * /brief constructor
     *
     * \param diode The IR-LED
     *
     */
    IrController(hwlib::target::d2_36kHz & diode);

    /**
     * \brief Send a bitstream
     *
     * This function will send a bitstream (2 times) from an uint16_t.
     *
     * \param bits Bitstream that has to be send.
     */
    void send(uint16_t bits);

};


#endif //LASER_IR_H
