#pragma once
#include "Vec2.h"

static constexpr unsigned int ScreenWidth = 800u;
static constexpr unsigned int ScreenHeight = 800u;

class ScreenTransformer
{
public:
	ScreenTransformer()
		:
		xFactor( float( ScreenWidth ) / 2.0f ),
		yFactor( float( ScreenHeight ) / 2.0f )
	{}

	Vec2& Transform( Vec2& v ) const
	{
		v.x = (v.x + 1.0f) * xFactor;
		v.y = (-v.y + 1.0f) * yFactor;
		return v;
	}
	Vec2 GetTransformed( const Vec2& v ) const
	{
		return Transform( Vec2( v ) );
	}

private:
	float xFactor;
	float yFactor;
};