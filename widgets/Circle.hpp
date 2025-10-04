#include "Widget.hpp"

template<uint8_t RADIUS>
class Circle: public Widget
{
public:
    Circle(bool filled = true) : filled_{filled}
    {
        setWidth(RADIUS * 2);
        setHeight(RADIUS * 2);
        draw_circle_on_pixel_map();
        setPixelMap(pixel_map_.data());
    }

private:
    void draw_circle_on_pixel_map()
    {
        const double center_x{RADIUS - 0.5};
        const double center_y{RADIUS - 0.5};

        for (uint8_t y = 0; y < RADIUS * 2; ++y)
        {
            for (uint8_t x = 0; x < RADIUS * 2; ++x)
            {
                const double dx = x - center_x;
                const double dy = y - center_y;
                if (filled_)
                {
                    if (dx * dx + dy * dy <= RADIUS * RADIUS)
                    {
                        pixel_map_[y * (RADIUS * 2) + x] = 255;
                    }
                }
                else
                {
                    if (std::abs((RADIUS * RADIUS) - (dx * dx + dy * dy)) < RADIUS)
                    {
                        pixel_map_[y * (RADIUS * 2) + x] = 255;
                    }
                }
            }
        }
    }

    std::array<uint8_t, RADIUS * 2 * RADIUS * 2> pixel_map_{};
    bool filled_;
};