/**
 * Widget.hpp
 *
 *  Created on: 07-04-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_GUI_WIDGET_HPP_
#define APP_GUI_WIDGET_HPP_

#include <cstdint>
#include <span>

class Widget;

struct WidgetAndPositions {
    uint8_t x;
    uint8_t y;
    const Widget & widget;
};

class Widget
{
public:
    Widget() = default;

    [[nodiscard]] uint8_t getWidth() const
    {
        return width_;
    }

    [[nodiscard]] uint8_t getHeight() const
    {
        return height_;
    }

    [[nodiscard]] const uint8_t * get_pixel_map() const
    {
        return pixel_map_;
    }

    virtual void update() const = 0;

    [[nodiscard]] virtual bool is_self_updatable() const
    {
        return false;
    }

    virtual ~Widget()
    {
    }

    void setPixelMap(const uint8_t * pixel_map) const
    {
        pixel_map_ = pixel_map;
    }

    [[nodiscard]] bool is_visible() const
    {
        return is_visible_;
    }

    void hide() const
    {
        is_visible_ = false;
    }

    void show() const
    {
        is_visible_ = true;
    }

    void add_children(std::span<WidgetAndPositions> children)
    {
        children_ = children;
    }

    [[nodiscard]] const std::span<WidgetAndPositions> & get_children() const
    {
        return children_;
    }

protected:
    void setWidth(uint8_t width) const
    {
        width_ = width;
    }
    void setHeight(uint8_t height) const
    {
        height_ = height;
    }

    mutable uint8_t width_{0};
    mutable uint8_t height_{0};

    mutable const uint8_t * pixel_map_{nullptr};

    mutable bool is_visible_{true};

private:
    mutable std::span<WidgetAndPositions> children_{};
};

#endif /* APP_GUI_WIDGET_HPP_ */
