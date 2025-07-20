/**
 * @file RotatableCanvas.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-03-26
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <cassert>
#include <cstdint>
#include <cstring>

#include "Canvas.hpp"
#include "GUI.hpp"
#include "Widget.hpp"

enum class Rotation
{
    BOTTOM_EDGE_ON_THE_BOTTOM,
    RIGHT_EDGE_ON_THE_BOTTOM,
    TOP_EDGE_ON_THE_BOTTOM,
    LEFT_EDGE_ON_THE_BOTTOM
};

struct Coordinates {
    uint8_t x{};
    uint8_t y{};
};

class RotatableCanvas: public Canvas
{
public:
    void postprocess() override
    {
        uint8_t tmp_frame_buffer[32 * 32];
        memcpy(tmp_frame_buffer, frame_buffer_, 32 * 32);

        for (uint8_t x{0}; x < 32; ++x)
        {
            for (uint8_t y{0}; y < 32; ++y)
            {
                auto [new_x, new_y] = translate_corrdinates(x, y, rotation);

                frame_buffer_[x + 32 * y] = tmp_frame_buffer[new_x + new_y * 32];
            }
        }
    }

    virtual ~RotatableCanvas() = default;

private:
    Coordinates translate_corrdinates(uint8_t x, uint8_t y, Rotation rotation)
    {
        switch (rotation)
        {
            case Rotation::BOTTOM_EDGE_ON_THE_BOTTOM:
                return {.x = x, .y = y};
            case Rotation::RIGHT_EDGE_ON_THE_BOTTOM:
                return {.x = y, .y = static_cast<uint8_t>(32 - x - 1)};
            case Rotation::TOP_EDGE_ON_THE_BOTTOM:
                return {.x = static_cast<uint8_t>(32 - x - 1), .y = static_cast<uint8_t>(32 - y - 1)};
            case Rotation::LEFT_EDGE_ON_THE_BOTTOM:
                return {.x = static_cast<uint8_t>(32 - y - 1), .y = x};
            default:
                assert(false && "invalid rotation.");
                return {.x = 0, .y = 0};
        }
    }

    Rotation rotation{Rotation::BOTTOM_EDGE_ON_THE_BOTTOM};
};
