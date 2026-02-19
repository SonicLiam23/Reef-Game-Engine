#pragma once
#include "SFML/System/Vector2.hpp"
// allows the user to automatically use a Math::Vector2x when needing a sf::Vector2, but not use a sf::Vector2 in place of Math::Vector2
namespace Math
{
	struct Vector2f
	{
		float x{}, y{};

		constexpr Vector2f() = default;
		constexpr Vector2f(float _x, float _y) : x(_x), y(_y) {}

		operator sf::Vector2f() const
		{
			return sf::Vector2f(x, y);
		}
		explicit Vector2f(const sf::Vector2f& v)
			: x(v.x), y(v.y) {}

	};
	using Vector2 = Vector2f;

	struct Vector2u
	{
		unsigned int x{}, y{};

		constexpr Vector2u() = default;
		constexpr Vector2u(float _x, float _y) : x(_x), y(_y) {}

		operator sf::Vector2u() const
		{
			return sf::Vector2u(x, y);
		}

		explicit Vector2u(const sf::Vector2u& v)
			: x(v.x), y(v.y) {}
	};

	struct Vector2i
	{
		int x{}, y{};

		constexpr Vector2i() = default;
		constexpr Vector2i(int _x, int _y) : x(_x), y(_y) {}

		operator sf::Vector2i() const
		{
			return sf::Vector2i(x, y);
		}

		explicit Vector2i(const sf::Vector2i& v)
			: x(v.x), y(v.y) {}
	};
}

