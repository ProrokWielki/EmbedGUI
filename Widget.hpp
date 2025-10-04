/**
 * Widget.hpp
 *
 *  Created on: 07-04-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_GUI_WIDGET_HPP_
#define APP_GUI_WIDGET_HPP_

#include <cstdint>
#include <vector>

class Widget;

struct WidgetAndPositions {
    uint8_t x;
    uint8_t y;
    Widget * widget;
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

    virtual void update()
    {
    }

    [[nodiscard]] virtual bool is_self_updatable() const
    {
        return false;
    }

    virtual ~Widget()
    {
    }

    void setPixelMap(const uint8_t * pixel_map)
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

    void add_child(Widget * child, uint8_t x = 0, uint8_t y = 0)
    {
        children_.push_back({x, y, child});
    }

    void clear_children()
    {
        children_.clear();
    }

    [[nodiscard]] const std::vector<WidgetAndPositions> & get_children() const
    {
        return children_;
    }

protected:
    void setWidth(uint8_t width)
    {
        width_ = width;
    }
    void setHeight(uint8_t width)
    {
        height_ = width;
    }

    uint8_t width_{};
    uint8_t height_{};

    const uint8_t * pixel_map_{};

    mutable bool is_visible_{true};

private:
    std::vector<WidgetAndPositions> children_{};
};

#endif /* APP_GUI_WIDGET_HPP_ */
