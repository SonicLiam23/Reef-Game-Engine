#pragma once
#include "SFML/System/Vector2.hpp"
#include "box2d/b2_math.h"
#include "json.hpp"
#include "EngineAPI.h"
#include <cmath>
// allows the user to automatically use a Math::Vector2x when needing a sf::Vector2, but not use a sf::Vector2 in place of Math::Vector2
namespace Math
{
	template <typename T = float>
	struct Vector2
	{
		static_assert(std::is_arithmetic_v<T>, "Vector2s type must be numeric");
		T x, y;

		constexpr Vector2() = default;
		constexpr Vector2(T _x, T _y) : x(_x), y(_y) {}
		inline constexpr bool IsZero() const
		{
			return x == 0 && y == 0;
		}

		inline operator sf::Vector2<T>() const
		{
			return sf::Vector2<T>(x, y);
		}

		inline explicit Vector2<T>(const sf::Vector2<T>& v)
			: x(v.x), y(v.y) {}

		inline operator b2Vec2() const
		{
			return b2Vec2(x, y);
		}
		inline explicit Vector2<T>(const b2Vec2& v)
			: x(v.x), y(v.y) {}


		template <typename U>
		constexpr Vector2(const Vector2<U>& other) 
			: x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {
		};

		// addition
		inline Vector2<T> operator+(const Vector2<T>& rhs)
		{
			
			return Vector2<T>(x + rhs.x, y + rhs.y);
		}
		inline Vector2<T> operator+(const T& rhs)
		{
			return Vector2<T>(x + rhs, y + rhs);
		}

		// subtract
		inline Vector2<T> operator-(const Vector2<T>& rhs)
		{
			return Vector2<T>(x - rhs.x, y - rhs.y);
		}
		inline Vector2<T> operator-(const T& rhs)
		{
			return Vector2<T>(x - rhs, y - rhs);
		}

		// multiplication by scalar
		inline Vector2<T> operator*(const T& rhs)
		{
			return Vector2<T>(x * rhs, y * rhs);
		}
		
		// division by scalar
		inline Vector2<T> operator/(const T& rhs)
		{
			return Vector2<T>(x / rhs, y / rhs);
		}

		inline float GetLength()
		{
			return std::sqrt((x * x) + (y * y));
		}

		inline void Normalize()
		{
			Vector2<T> temp = Normalized();
			x = temp.x; y = temp.y;
		}

		inline Vector2<T> Normalized()
		{
			Vector2<T> newVec;
			if (x == 0)
			{
				newVec = { 0, 1 };
			}
			else if (y == 0)
			{
				newVec = { 1, 0 };
			}
			else
			{
				float length = GetLength();
				newVec.x = x / length;
				newVec.y = y / length;
			}

			return newVec;
		}

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Vector2, x, y);
	};

	
	using Vector2f = Vector2<float>;
	using Vector2u = Vector2<unsigned int>;
	using Vector2i = Vector2<int>;
}

