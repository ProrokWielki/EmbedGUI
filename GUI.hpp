/**
 * GUI.hpp
 *
 *  Created on: 04-04-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_GUI_GUI_HPP_
#define APP_GUI_GUI_HPP_

#include <algorithm>
#include <cstdint>
#include <functional>
#include <span>
#include <utility>

enum class Signal;
class Canvas;

struct Transition {
    Canvas * source_canvas;
    Signal trigger;
    Canvas * target_canvas;
};


class GUI
{

public:
    /**
     *  Default constructor
     */

    GUI(std::span<Transition> transitionMatrix, Canvas * startState, std::function<void(uint8_t *)> set_framebuffer_callback, uint8_t *front_frame_buffer, uint8_t* back_frame_buffer)
        : transitionMatrix_(transitionMatrix), curent_canvas_(startState), set_framebuffer_callback_(std::move(set_framebuffer_callback))
    {
        front_framebuffer_ = front_frame_buffer;
        back_framebuffer_ = back_frame_buffer;
    }

    /**
     * @brief Swaps frame buffers if they are ready to swap.
     */
    void swap_framebuffers();

    void update();

    uint8_t * getFrameBuffer()
    {
        return front_framebuffer_;
    }

    void signal_callback(const Signal & signal)
    {
        recieved_ = signal;
        updateNedded = true;
    }

    static uint8_t * getFrontFrameBuffer()
    {
        return front_framebuffer_;
    }

    static uint8_t * getBackFrameBuffer()
    {
        return back_framebuffer_;
    }

private:
    std::span<Transition> transitionMatrix_;

    Canvas * transiton(Signal signal)
    {

        auto it = std::find_if(transitionMatrix_.cbegin(), transitionMatrix_.cend(),
                               [&](Transition transition) { return transition.source_canvas == curent_canvas_ && transition.trigger == signal; });

        if (it == transitionMatrix_.end())
        {
            return curent_canvas_;
        }

        return it->target_canvas;
    }

    Signal recieved_{};

    bool updateNedded{false};

    static uint8_t width_;
    static uint8_t height_;

    static uint8_t * front_framebuffer_;
    static uint8_t * back_framebuffer_;

    bool isDoubleFrameBuffer{true};
    
    Canvas * curent_canvas_;
    std::function<void(uint8_t *)> set_framebuffer_callback_;
};

#endif /* APP_GUI_GUI_HPP_ */
