#include "GUI.hpp"

#include "../DataContainer.hpp"

uint8_t GUI::width_ = 32;
uint8_t GUI::height_ = 32;

uint8_t * GUI::front_framebuffer_ = DataContainer::FrameBuffer1;  // Todo it cant be like that.
uint8_t * GUI::back_framebuffer_ = DataContainer::FrameBuffer2;

void GUI::swap_framebuffers()
{
    if (curent_canvas_->isReady() and isDoubleFrameBuffer)
    {
        std::swap(front_framebuffer_, back_framebuffer_);
        front_framebufferPointer = front_framebuffer_;
    }
}

void GUI::update()
{
    if (updateNedded)
    {
        curent_canvas_ = transiton(recieved_);
        updateNedded = false;
        curent_canvas_->clear();
        curent_canvas_->init();
    }

    curent_canvas_->update();
}
