/**
 * Text.hpp
 *
 *  Created on: 11-06-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_GUI_WIDGETS_TEXT_HPP_
#define APP_GUI_WIDGETS_TEXT_HPP_

#include <cstdint>
#include <string>
#include <vector>

#include <Image.hpp>

#include "../Widget.hpp"
#include "Assets/Text/texts.hpp"

enum class TextAlignment
{
    LEFT,
    // CENTER,
    RIGHT
};

class Text: public Widget
{
public:
    Text(const std::string & raw_text, TextAlignment alignment = TextAlignment::LEFT)
    {
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

        if (alignment == TextAlignment::RIGHT)
        {
            current_x = 32;

            for (const auto & character : characters_)
            {
                current_x -= character->getWidth();
            }
        }

        for (const auto & character : characters_)
        {
            add_child(character, current_x, 0);
            current_x += character->getWidth();
        }
    }

private:
    // uint8_t dummy_data[32 * 23] = {0};
    std::vector<Image *> characters_;
};

#endif /* APP_GUI_WIDGETS_TEXT_HPP_ */
