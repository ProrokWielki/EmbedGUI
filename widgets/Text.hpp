/**
 * Text.hpp
 *
 *  Created on: 11-06-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_GUI_WIDGETS_TEXT_HPP_
#define APP_GUI_WIDGETS_TEXT_HPP_

#include <algorithm>
#include <cstdint>
#include <functional>
#include <memory>
#include <numeric>
#include <string>

#include <Image.hpp>

#include "../Widget.hpp"
#include "Circle.hpp"

enum class TextAlignment
{
    LEFT,
    CENTER,
    RIGHT
};

class Text: public Widget
{
public:
    Text(const std::string & raw_text, std::function<const Image &(char)> converter) : converter_{std::move(converter)}
    {
        setText(raw_text);
        setWidth(getTextWidth());
    }

    Text(const std::string & raw_text, std::function<const Image &(char)> converter, uint8_t text_field_width, TextAlignment alignment = TextAlignment::LEFT)
    : converter_{std::move(converter)}
    {
        setWidth(text_field_width);
        setText(raw_text, alignment);
    }

    void setText(const std::string & raw_text, TextAlignment alignment = TextAlignment::LEFT)
    {
        uint8_t num_of_chars{0};
        uint8_t current_x{0};

        for (const auto character : raw_text)
        {
            const auto & char_img = converter_(character);
            std::construct_at(&characters_buffer.at(num_of_chars), WidgetAndPositions{.x = 0, .y = 0, .widget = char_img});
            ++num_of_chars;
        }

        characters_ = std::span(characters_buffer).subspan(0, num_of_chars);

        auto text_width = getTextWidth();

        if (alignment == TextAlignment::RIGHT)
        {
            current_x = getWidth() - text_width;
        }
        else if (alignment == TextAlignment::CENTER)
        {
            current_x = (getWidth() - text_width) / 2;
        }

        for (auto & character : characters_)
        {
            character.x = current_x;
            current_x += character.widget.getWidth();
        }

        add_children(characters_);

        auto highest_char = *std::ranges::max_element(
        characters_, [](const WidgetAndPositions lhs, const WidgetAndPositions rhs) { return lhs.widget.getHeight() < rhs.widget.getHeight(); });
        auto text_height = highest_char.widget.getHeight();
        setHeight(text_height);
    }

    void update() const override
    {
    }

private:
    uint8_t getTextWidth() const
    {
        return std::accumulate(characters_.cbegin(), characters_.cend(), 0,
                               [](int sum, const WidgetAndPositions widget) { return sum + widget.widget.getWidth(); });
    }

    constexpr static size_t MAX_NUM_OF_CHARS{16};
    std::array<WidgetAndPositions, MAX_NUM_OF_CHARS> characters_buffer = []<size_t... Is>(std::index_sequence<Is...>) {
        return std::array<WidgetAndPositions, MAX_NUM_OF_CHARS>{((void)Is, WidgetAndPositions{.x = 0, .y = 0, .widget = Circle<1>{}})...};
    }(std::make_index_sequence<MAX_NUM_OF_CHARS>{});

    std::span<WidgetAndPositions> characters_{};

    std::function<const Image &(char)> converter_;
};

#endif /* APP_GUI_WIDGETS_TEXT_HPP_ */
