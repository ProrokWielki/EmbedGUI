/**
 * Canvas.hpp
 *
 *  Created on: 02-04-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_GUI_CANVAS_HPP_
#define APP_GUI_CANVAS_HPP_

#include <cstdint>

#include "GUI.hpp"
#include "Widget.hpp"

class Canvas
{
public:
    Canvas() = default;

    /**
     * @brief Adds widget to the canvas.
     */
    void add(Widget * widget, uint8_t x = 0, uint8_t y = 0)
    {
        widgets_and_positions[num_of_widgets++] = {x, y, widget};
    }

    void validate()
    {
        ready = false;
        frame_buffer_ = GUI::getBackFrameBuffer();
        for (uint8_t widget = 0; widget < num_of_widgets; widget++)
        {
            uint8_t widget_line, line;
            for (line = widgets_and_positions[widget].y, widget_line = 0;
                 line < widgets_and_positions[widget].widget->getHeight() - widgets_and_positions[widget].y and line < height_; line++, widget_line++)
            {
                uint8_t column, widget_column;
                for (column = widgets_and_positions[widget].x, widget_column = 0;
                     column < (widgets_and_positions[widget].widget)->getWidth() - widgets_and_positions[widget].x and column < width_;
                     column++, widget_column++)
                {
                    frame_buffer_[column + line * width_] =
                    widgets_and_positions[widget].widget->get_pixel_map()[widget_column + widget_line * widgets_and_positions[widget].widget->getWidth()];
                }
            }
        }
        ready = true;
    }

    void clear()
    {
        ready = false;

        frame_buffer_ = GUI::getBackFrameBuffer();

        for (uint16_t i = 0; i < height_ * width_; i++)
        {
            frame_buffer_[i] = 0;
        }

        num_of_widgets = 0;

        ready = true;
    }

    bool isReady()
    {
        if (ready == true)
        {
            ready = false;
            return true;
        }
        return ready;
    }

    virtual void init()
    {
    }

    virtual void up_date() = 0;

    void update()
    {
        ready = false;
        for (uint8_t widget = 0; widget < num_of_widgets; widget++)
        {
            widgets_and_positions[widget].widget->update();
        }
        validate();
        up_date();
    }

    virtual ~Canvas() = default;

private:
    struct WidgetAndPositions {
        uint8_t x;
        uint8_t y;
        Widget * widget;
    };

    uint8_t * frame_buffer_{};

    uint8_t width_{32};
    uint8_t height_{32};

    std::array<WidgetAndPositions, 10> widgets_and_positions;
    uint8_t num_of_widgets{0};

    bool ready{false};
};

#endif /* APP_GUI_CANVAS_HPP_ */
