#pragma once
#include "SFML/Graphics/Rect.hpp"
#include "Vector2.h"
namespace Math
{
	struct Rect
	{
        Math::Vector2f position, size;

        float& x, y, w, h;

        constexpr Rect() : position({0, 0}), size({0 , 0}), x(position.x), y(position.y), w(size.x), h(size.y) {}
        constexpr Rect(float _x, float _y, float _w, float _h) : position(_x, _y), size(_w, _h), x(position.x), y(position.y), w(size.x), h(size.y) {}
        constexpr Rect(Vector2f _pos, Vector2f _size) : position(_pos), size(_size), x(position.x), y(position.y), w(size.x), h(size.y) {}

        inline float* Data() { return &x; }
        inline const float* Data() const { return &x; }
        inline float* PositionData() { return &position.x; }
        inline float* SizeData() { return &size.x; }

        inline bool Contains(const Vector2& point) const
        {
            return point.x >= x &&
                point.x <= x + w &&
                point.y >= y &&
                point.y <= y + h;
        }

        inline Math::Vector2f Centre()
        {
            return { x + (w / 2), y + (h / 2) };
        }

        operator sf::FloatRect() const
        {
            return sf::FloatRect({ x, y }, { w, h });
        }


	};
};

