#include "GUI.hpp"
#include "Canvas.hpp"

uint8_t GUI::width_ = 32;
uint8_t GUI::height_ = 32;

uint8_t FrameBuffer1[32][32];
uint8_t FrameBuffer2[32][32];

uint8_t * GUI::front_framebuffer_ = &FrameBuffer1[0][0];  // Todo it cant be like that.
uint8_t * GUI::back_framebuffer_ = &FrameBuffer2[0][0];

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
