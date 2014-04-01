#pragma once

namespace KGE
{
	struct Vec2f
	{
		Vec2f() : X(0.0f), Y(0.0f) {}
		Vec2f(float fX, float fY) : X(fX), Y(fY) {}
		Vec2f(const Vec2f& xCopy) : X(xCopy.X), Y(xCopy.Y) {}

		float X;
		float Y;

		// magnitudes
		float Magnitude() const;
		float MagnitudeSq() const;
		float Normalise();
		Vec2f operator*(float fRHS) const;
		void operator*=(float fRHS);

		void operator+=(const Vec2f& xRHS);
		void operator-=(const Vec2f& xRHS);
		Vec2f operator+(const Vec2f& xRHS) const;
		Vec2f operator-(const Vec2f& xRHS) const;

		// angles
		static Vec2f CreateFromAngle(float fAngle, float fMagnitude = 1.0f);
		static Vec2f RotateBy(Vec2f xInput, float fAngle);
		float ToAngle() const;
		void SetFromAngle(float fAngle, float fMagnitude = 1.0f);
		void RotateBy(float fAngle);

		// type conversions
		const sf::Vector2f&	AsSFVec2f() const	{ return *reinterpret_cast<const sf::Vector2f*>(this); }
		sf::Vector2f&	AsSFVec2f()				{ return *reinterpret_cast<sf::Vector2f*>(this); }
		const b2Vec2&	AsB2Vec2() const		{ return *reinterpret_cast<const b2Vec2*>(this); }
		b2Vec2&			AsB2Vec2()				{ return *reinterpret_cast<b2Vec2*>(this); }

		void ReadFromString(const char* szInput);
	};

}