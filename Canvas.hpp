/**
 * Canvas.hpp
 *
 *  Created on: 02-04-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_GUI_CANVAS_HPP_
#define APP_GUI_CANVAS_HPP_

#include <cstdint>
#include <cstring>

#include "GUI.hpp"
#include "Widget.hpp"

class Canvas
{
public:
    Canvas()
    {
        validate();
    }

    /**
     * @brief Adds widget to the canvas.
     */
    void add(Widget * widget, uint8_t x = 0, uint8_t y = 0)
    {
        widgets_and_positions.push_back({.x = x, .y = y, .widget = widget});
    }

    [[nodiscard]]  bool isReady() const
    {
        return ready;
    }

    void swapped()
    {
        ready = false;
    }

    virtual void init()
    {
    }

    virtual void up_date() = 0;

    void update()
    {
        if (ready == true)
        {
            return;
        }

        up_date();

        validate();

        ready = true;
    }

    void clear()
    {
        ready = false;
        widgets_and_positions.clear();
        clear_framebuffer();
        ready = true;
    }

    [[nodiscard]] constexpr static uint8_t get_width()
    {
        return width_;
    }

    [[nodiscard]] constexpr static uint8_t get_height()
    {
        return height_;
    }

    [[nodiscard]] constexpr static uint8_t max_x_index()
    {
        return get_width() - 1U;
    }

    [[nodiscard]] constexpr static uint8_t max_y_index()
    {
        return get_height() - 1U;
    }

    virtual ~Canvas() = default;

protected:
    uint8_t * frame_buffer_{};

private:
    bool is_pixel_position_valid(uint8_t x, uint8_t y)
    {
        return x < width_ && y < height_;
    }

    void validate_children(const Widget * widget)
    {
        for(const auto& child: widget->get_children())
        {
            if (child.widget == nullptr)
            {
                continue;
            }
            child.widget->update();
            validate_children(child.widget);
        }
    }

    void validate()
    {

        frame_buffer_ = GUI::getBackFrameBuffer();
        clear_framebuffer();

        for (auto& widget: widgets_and_positions)
        {

            if (widget.widget == nullptr || not widget.widget->is_visible())
            {
                continue;
            }
            widget.widget->update();
            put_widget_on_framebuffer(widget);
        }

        postprocess();
    }

    void put_pixel_on_frame_buffer(uint8_t x, uint8_t y, uint8_t pixel_value)
    {
        if (not is_pixel_position_valid(x, y))
        {
            return;
        }

        frame_buffer_[width_ * y + x] = pixel_value;
    }

    void put_widget_on_framebuffer(const WidgetAndPositions & widget_and_position, uint8_t x_offset = 0, uint8_t y_offset = 0)
    {
        const Widget & widget = *(widget_and_position.widget);

        uint8_t x_on_canvas = widget_and_position.x + x_offset;
        uint8_t y_on_canvas = widget_and_position.y + y_offset;

        for (uint8_t widget_x{0}; widget_x < widget.getWidth(); ++widget_x)
        {
            for (uint8_t widget_y{0}; widget_y < widget.getHeight(); ++widget_y)
            {
                uint8_t current_y = y_on_canvas + widget_y;
                uint8_t current_x = x_on_canvas + widget_x;

                put_pixel_on_frame_buffer(current_x, current_y, widget.get_pixel_map()[widget_x + widget_y * widget.getWidth()]);
            }
        }

        for (const auto& child : widget.get_children())
        {
            put_widget_on_framebuffer(child, x_on_canvas + x_offset, y_on_canvas + y_offset);
        }
    }

    virtual void postprocess()
    {
    }

    void clear_framebuffer()
    {
        memset(frame_buffer_, 0, 32 * 32);
    }

    constexpr static uint8_t width_{32};
    constexpr static uint8_t height_{32};

    std::vector<WidgetAndPositions> widgets_and_positions;

    volatile bool ready{true};
};

#endif /* APP_GUI_CANVAS_HPP_ */
