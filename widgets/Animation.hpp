/**
 * Animation.hpp
 *
 *  Created on: 02-04-2019
 *  @author: Paweł Warzecha
 */

#ifndef APP_GUI_WIDGETS_ANIMATION_HPP_
#define APP_GUI_WIDGETS_ANIMATION_HPP_

#include <cstdint>
#include <functional>
#include <vector>

#include "../Widget.hpp"
#include <widgets/Image.hpp>

class Animation: public Widget
{
public:
    Animation(const std::vector<std::reference_wrapper<const Image>> & frames) : frames_{frames}
    {
        update_frame();
    }

    void update() override
    {
        ++current_frame;
        current_frame = current_frame >= frames_.size() ? 0 : current_frame;

        update_frame();
    }

    [[nodiscard]] bool is_self_updatable() const override
    {
        return true;
    }

private:
    void update_frame()
    {
        setWidth(frames_[current_frame].get().getWidth());
        setHeight(frames_[current_frame].get().getHeight());
        setPixelMap((frames_[current_frame].get().get_pixel_map()));
    }

    uint8_t current_frame{0};
    std::vector<std::reference_wrapper<const Image>> frames_;
};

#endif /* APP_GUI_WIDGETS_ANIMATION_HPP_ */
