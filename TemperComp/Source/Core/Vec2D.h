#pragma once
#include <math.h>

//----------------------------------------------------------

struct Vec2D
{
public:
	float x, y;

	Vec2D() : x( 0 ), y( 0 )										{}
	Vec2D( float unit ) : x( unit ), y( unit )						{}
	Vec2D( float newX, float newY ) : x( newX ), y( newY )			{}
	Vec2D( const Vec2D& other ) : x( other.x ), y( other.y )		{}

	inline Vec2D operator+( const Vec2D& rhs ) const				{ return Vec2D( this->x + rhs.x, this->y + rhs.y ); }
	inline Vec2D operator-( const Vec2D& rhs ) const				{ return Vec2D( this->x - rhs.x, this->y - rhs.y ); }

	inline Vec2D operator+( float rhs ) const;						// See the INL file
	inline Vec2D operator-( float rhs ) const;						// See the INL file
	inline Vec2D operator*( float rhs ) const						{ return Vec2D( this->x * rhs, this->y * rhs ); }
	inline Vec2D operator/( float rhs ) const						{ return Vec2D( this->x / rhs, this->y / rhs ); }
	friend inline Vec2D operator*( float lhs, Vec2D rhs )			{ return Vec2D( rhs.x * lhs, rhs.y * lhs ); }
	friend inline Vec2D operator/( float lhs, Vec2D rhs )			{ return Vec2D( rhs.x / lhs, rhs.y / lhs ); }

	inline void operator+=( const Vec2D& rhs )						{ this->x += rhs.x; this->y += rhs.y; }
	inline void operator-=( const Vec2D& rhs )						{ this->x -= rhs.x; this->y -= rhs.y; }

	inline void operator+=( float rhs );							// See the INL file
	inline void operator-=( float rhs );							// See the INL file
	inline void operator*=( float rhs )								{ this->x *= rhs; this->y *= rhs; }
	inline void operator/=( float rhs )								{ this->x /= rhs; this->y /= rhs; }

	inline float GetLengthSqr() const								{ return ( x * x ) + ( y * y ); }
	inline float GetLength() const									{ return sqrtf( ( x * x ) + ( y * y ) ); }

	inline float DotProduct( const Vec2D& other ) const				{ return ( this->x * other.x ) + ( this->y * other.y ); }
	inline Vec2D GetNormalised() const;								// See the INL file
	inline void Normalise();										// See the INL file

	inline Vec2D GetPerpendicularVector() const						{ return Vec2D( -y, x ); }
	inline Vec2D GetReverse() const									{ return Vec2D( -x, -y ); }

	// Returns a vector reflected by the normal (must be unit length), like the path of light reflecting off a mirror
	inline void Reflect( const Vec2D& normal )						{ *this += ( ( 2.0f * DotProduct( normal ) ) * normal.GetReverse() ); }
	inline void Clamp( float maxLength )							{ *this = GetLength() < maxLength ? *this : GetNormalised() * maxLength; }
};

//----------------------------------------------------------

#define DEFAULT_EPSILON 0.001f

//----------------------------------------------------------

inline bool operator==( const Vec2D& lhs, const Vec2D rhs )
{
	return fabs( lhs.x - rhs.x ) < DEFAULT_EPSILON && fabs( lhs.y - rhs.y ) < DEFAULT_EPSILON;
}

//----------------------------------------------------------

inline bool operator!=( const Vec2D& lhs, const Vec2D rhs )
{
	return fabs( lhs.x - rhs.x ) > DEFAULT_EPSILON || fabs( lhs.y - rhs.y ) > DEFAULT_EPSILON;
}

//----------------------------------------------------------