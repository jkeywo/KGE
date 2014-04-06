#include "KGE.hpp"
#include "Core/Maths/Vec2f.hpp"

///////////////////////////////////////////////////////////////////////////
//	Vec2f

namespace KGE
{
	float Vec2f::Magnitude() const
	{
		return sqrt(MagnitudeSq());
	}
	float Vec2f::MagnitudeSq() const
	{
		return X * X + Y * Y;
	}
	float Vec2f::Normalise()
	{
		float fMagnitude = Magnitude();
		operator*=(1.0f / fMagnitude);
		return fMagnitude;
	}
	Vec2f Vec2f::operator*(float fRHS) const
	{
		return Vec2f(X * fRHS, Y * fRHS);
	}
	void Vec2f::operator*=(float fRHS)
	{
		X *= fRHS;
		Y *= fRHS;
	}

	bool Vec2f::operator==(const Vec2f& xRHS) const
	{
		return X == xRHS.X && Y == xRHS.Y;
	}
	bool Vec2f::operator!=(const Vec2f& xRHS) const
	{
		return X != xRHS.X || Y != xRHS.Y;
	}

	void Vec2f::operator+=(const Vec2f& xRHS)
	{
		X += xRHS.X;
		Y += xRHS.Y;
	}
	void Vec2f::operator-=(const Vec2f& xRHS)
	{
		X -= xRHS.X;
		Y -= xRHS.Y;
	}
	Vec2f Vec2f::operator+(const Vec2f& xRHS) const
	{
		return Vec2f(X + xRHS.X, Y + xRHS.Y);
	}
	Vec2f Vec2f::operator-(const Vec2f& xRHS) const
	{
		return Vec2f(X - xRHS.X, Y - xRHS.Y);
	}


	Vec2f Vec2f::CreateFromAngle(float fAngle, float fMagnitude /*= 1.0f*/)
	{
		Vec2f xRet;
		xRet.SetFromAngle(fAngle, fMagnitude);
		return xRet;
	}
	Vec2f Vec2f::RotateBy(Vec2f xInput, float fAngle)
	{
		xInput.RotateBy(fAngle);
		return xInput;
	}

	float Vec2f::ToAngle() const
	{
		Vec2f xVector(*this);
		if (MagnitudeSq() != 1.0f)
		{
			xVector.Normalise();
		}
		return acos(xVector.Y) * ((xVector.X > 0.0f) ? 1.0f : -1.0f);
	}
	void Vec2f::SetFromAngle(float fAngle, float fMagnitude /*= 1.0f*/)
	{
		X = sin(fAngle) * fMagnitude;
		Y = cos(fAngle) * fMagnitude;
	}
	void Vec2f::RotateBy(float fAngle)
	{
		Vec2f xVector(*this);
		float cs = cos(fAngle);
		float sn = sin(fAngle);
		X = xVector.X * cs - xVector.Y * sn;
		Y = xVector.X * sn + xVector.Y * cs;
	}

	void Vec2f::ReadFromString(const char* szInput)
	{
		char szBuffer[16];
		const char* pxRead = szInput;
		char* pxWrite = szBuffer;
		while (true)
		{
			if (*pxRead == '\0')
			{
				*pxWrite = '\0';
				Y = static_cast<float>(atof(szBuffer));
				break;
			}
			else if (*pxRead == ',')
			{
				*pxWrite = '\0';
				X = static_cast<float>(atof(szBuffer));
				pxWrite = szBuffer;
			}
			else if ((*pxRead >= '0' && *pxRead <= '9') || *pxRead == '.')
			{
				*pxWrite = *pxRead;
				pxWrite++;
			}
			pxRead++;
		}
	}
}
