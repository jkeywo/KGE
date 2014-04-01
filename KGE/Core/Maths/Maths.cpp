#include "KGL.h"
#include "Core/KGL_Maths.h"

///////////////////////////////////////////////////////////////////////////
//	KGL_Vec2

float KGL_Vec2::Magnitude() const
{
	return sqrt( MagnitudeSq() );
}
float KGL_Vec2::MagnitudeSq() const
{
	return X * X + Y * Y;
}
float KGL_Vec2::Normalise()
{
	float fMagnitude = Magnitude();
	operator*=( 1.0f / fMagnitude );
	return fMagnitude;
}
KGL_Vec2 KGL_Vec2::operator*( float fRHS ) const
{
	return KGL_Vec2( X * fRHS, Y * fRHS );
}
void KGL_Vec2::operator*=( float fRHS )
{
	X *= fRHS;
	Y *= fRHS;
}

void KGL_Vec2::operator+=(const KGL_Vec2& xRHS)
{
	X += xRHS.X;
	Y += xRHS.Y;
}
void KGL_Vec2::operator-=(const KGL_Vec2& xRHS)
{
	X -= xRHS.X;
	Y -= xRHS.Y;
}
KGL_Vec2 KGL_Vec2::operator+(const KGL_Vec2& xRHS) const
{
	return KGL_Vec2( X + xRHS.X, Y + xRHS.Y );
}
KGL_Vec2 KGL_Vec2::operator-(const KGL_Vec2& xRHS) const
{
	return KGL_Vec2( X - xRHS.X, Y - xRHS.Y );
}


KGL_Vec2 KGL_Vec2::CreateFromAngle( float fAngle, float fMagnitude /*= 1.0f*/ )
{
	KGL_Vec2 xRet;
	xRet.SetFromAngle( fAngle, fMagnitude );
	return xRet;
}
KGL_Vec2 KGL_Vec2::RotateBy( KGL_Vec2 xInput, float fAngle )
{
	xInput.RotateBy( fAngle );
	return xInput;
}

float KGL_Vec2::ToAngle() const
{
	KGL_Vec2 xVector(*this);
	if( MagnitudeSq() != 1.0f )
	{
		xVector.Normalise();
	}
	return acos( xVector.Y ) * ( (xVector.X > 0.0f) ? 1.0f : -1.0f);
}
void KGL_Vec2::SetFromAngle( float fAngle, float fMagnitude /*= 1.0f*/ )
{
	X = sin( fAngle ) * fMagnitude;
	Y = cos( fAngle ) * fMagnitude;
}
void KGL_Vec2::RotateBy( float fAngle )
{
	KGL_Vec2 xVector(*this);
	float cs = cos( fAngle );
	float sn = sin( fAngle );
	X = xVector.X * cs - xVector.Y * sn;
	Y = xVector.X * sn + xVector.Y * cs;
}

void KGL_Vec2::ReadFromString(const char* szInput)
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
		else if ((*pxRead >= '0' && *pxRead <= '9') || *pxRead == '.' )
		{
			*pxWrite = *pxRead;
			pxWrite++;
		}
		pxRead++;
	}
}