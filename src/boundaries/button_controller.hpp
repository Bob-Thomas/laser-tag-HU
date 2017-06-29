/**
 * \file      button_controller.hpp
 * \brief     Task that listens for a button press and notifies a controller
 * \author    Bob Thomas
 * \copyright Copyright (c) 2017, Lasertak
 */

#ifndef BUTTON_CONTROLLER_HPP
#define BUTTON_CONTROLLER_HPP
#include "rtos.hpp"
#include "hwlib.hpp"
#include "../interfaces/i-controller.hpp"
/**
 * \brief ButtonController class that is an rtos task
 * A task that polls to check if a button is pressed
 */
class ButtonController : public rtos::task<>{
private:
    /// the button pin the task will poll
    hwlib::target::pin_in &button;
    /// A pointer to an existing controller that needs to be notified
    IController *listener = nullptr;
    /// Rtos clock that let's the task poll every x time
    rtos::clock clock;
    /// A toggle bool to avoid spamming of the button
    bool clicked = false;
    /// Rtos main loop
    void main();
public:
    /**
     * \brief ButtonController constructor
     * \param[in] button hwlib pin that the button is wired to
     * \param[in] listener a pointer to an existing Controller
     */
    ButtonController(hwlib::target::pin_in& button, IController *listener);
};
#endif //BUTTTON_CONTROLLER_HPP