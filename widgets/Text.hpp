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
#include <numeric>
#include <string>
#include <vector>

#include <Image.hpp>

#include "../Widget.hpp"
#include "Texts/texts.hpp"

enum class TextAlignment
{
    LEFT,
    CENTER,
    RIGHT
};

class Text: public Widget
{
public:
    Text(const std::string & raw_text)
    {
        setText(raw_text);
        setWidth(getTextWidth());
    }

    Text(const std::string & raw_text, uint8_t text_field_width, TextAlignment alignment = TextAlignment::LEFT)
    {
        setWidth(text_field_width);
        setText(raw_text, alignment);
    }

    void setText(const std::string & raw_text, TextAlignment alignment = TextAlignment::LEFT)
    {
        characters_.clear();
        clear_children();

        uint8_t current_x{0};

        for (const auto character : raw_text)
        {
            auto * char_ptr = TextFactory::to_image(character);
            characters_.push_back(char_ptr);
        }

        auto text_width = std::accumulate(characters_.cbegin(), characters_.cend(), 0, [](int sum, Image * image) { return sum + image->getWidth(); });

        if (alignment == TextAlignment::RIGHT)
        {
            current_x = getWidth() - text_width;
        }
        else if (alignment == TextAlignment::CENTER)
        {
            current_x = (getWidth() - text_width) / 2;
        }

        for (const auto & character : characters_)
        {
            add_child(character, current_x, 0);
            current_x += character->getWidth();
        }

        auto highest_char = *std::ranges::max_element(characters_, [](Image * lhs, Image * rhs) { return lhs->getHeight() < rhs->getHeight(); });
        auto text_height = highest_char->getHeight();
        setHeight(text_height);
    }

private:
    uint8_t getTextWidth() const
    {
        return std::accumulate(characters_.cbegin(), characters_.cend(), 0, [](int sum, Image * image) { return sum + image->getWidth(); });
    }
    // uint8_t dummy_data[32 * 23] = {0};
    std::vector<Image *> characters_;
};

#endif /* APP_GUI_WIDGETS_TEXT_HPP_ */
