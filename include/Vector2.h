#pragma once
#include "SFML/System/Vector2.hpp"
#include "json.hpp"
#include "EngineAPI.h"
// allows the user to automatically use a Math::Vector2x when needing a sf::Vector2, but not use a sf::Vector2 in place of Math::Vector2
namespace Math
{
	template <typename T = float>
	struct Vector2
	{
		T x, y;

		constexpr Vector2() = default;
		constexpr Vector2(T _x, T _y) : x(_x), y(_y) {}
		inline constexpr bool IsZero()
		{
			return x == 0 && y == 0;
		}

		operator sf::Vector2<T>() const
		{
			return sf::Vector2<T>(x, y);
		}
		explicit Vector2(const sf::Vector2<T>& v)
			: x(v.x), y(v.y) {
		}


		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Vector2, x, y);
	};


	using Vector2f = Vector2<float>;
	using Vector2u = Vector2<unsigned int>;
	using Vector2i = Vector2<int>;
}

