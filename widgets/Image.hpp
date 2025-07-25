/**
 * Image.hpp
 *
 *  Created on: 02-04-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_GUI_WIDGETS_IMAGE_HPP_
#define APP_GUI_WIDGETS_IMAGE_HPP_

#include "../Widget.hpp"
#include <cstdint>

struct RawImage;

class Image: public Widget
{
public:
    /**
     * @brief Constructor.
     */
    Image(uint8_t width, uint8_t height, const uint8_t * const raw_image)
    {
        setWidth(width);
        setHeight(height);
        setPixelMap(raw_image);
    }

    virtual ~Image()
    {
    }
};

#endif /* APP_GUI_WIDGETS_IMAGE_HPP_ */
