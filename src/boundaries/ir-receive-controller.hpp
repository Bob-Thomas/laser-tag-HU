
#ifndef LASER_IRRECEIVECONTROLLER_HPP
#define LASER_IRRECEIVECONTROLLER_HPP

#include "./rtos.hpp"
#include "../application-logic/command.hpp"
#include "../interfaces/i-controller.hpp"

class IrReceiveController : public rtos::task<> {
private:
    /// Pin the ir data output is on
    hwlib::target::pin_in &ir;

    /// Pointer to an existing controller to use the interface functions of
    IController *controller = nullptr;

    /**
     * \brief The main loop.
     *
     * This function will be running as RTOS task.
     *
     */
    void main();

    /**
     * \brief Get a IR-bit
     *
     * This Function will get a bit from the IR-receiver.
     *
     * \param[in] start A parameter that is used for recursion.
     *
     * \return uint8_t The bit that the IR receiver gets (2 if there is no signal).
     *
     */
    uint8_t getBit(long long int start = 0);

    /**
     * \brief Get the full bit signal
     *
     * This function will obtain the full 16-bit signal from the IR-receiver in the form of an unsigned 16 bit value.
     *
     * \param[in]   bitStream   A temporary bit stream that is used for recursion.
     * \param[in]   i           Indexer of where the obtained bit should be placed in the full signal.
     *
     * \return      uint16_t    The full 16-bit signal that is received from the IR-receiver.
     *
     */
    uint16_t getByte(uint16_t bitStream = 0, uint16_t i = 0);


public:

    /**
     * \brief contructor.
     *
     * \param[in] ir The receiver pin.
     * \param[in] controller Pointer to a existing controller to communicate with
     */
    IrReceiveController(hwlib::target::pin_in &ir, IController *controller);

};


#endif //LASER_IRRECEIVECONTROLLER_HPP
