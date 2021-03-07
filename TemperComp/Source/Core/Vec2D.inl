#include "Vec2D.h"

//----------------------------------------------------------

inline Vec2D Vec2D::operator+( float rhs ) const
{
	float newLength = GetLengthSqr() + rhs;
	Vec2D newVector = GetNormalised();
	return newVector * ( newLength );
}

//----------------------------------------------------------

inline Vec2D Vec2D::operator-( float rhs ) const
{
	float newLength = GetLengthSqr() - rhs;
	Vec2D newVector = GetNormalised();
	return newVector * ( newLength );
}

//----------------------------------------------------------

inline void Vec2D::operator+=( float rhs )
{
	float newLength = GetLengthSqr() + rhs;
	Normalise();
	*this *= ( newLength );
}

//----------------------------------------------------------

inline void Vec2D::operator-=( float rhs )
{
	float newLength = GetLengthSqr() - rhs;
	Normalise();
	*this *= ( newLength );
}

//----------------------------------------------------------

inline Vec2D Vec2D::GetNormalised() const
{
	float length = GetLengthSqr();
	return Vec2D( x / length, y / length );
}

//----------------------------------------------------------

inline void Vec2D::Normalise()
{
	float length = GetLengthSqr();
	x /= length;
	y /= length;
}

//----------------------------------------------------------