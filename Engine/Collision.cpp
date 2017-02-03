#include "Collision.h"


AABB::AABB( Vec2 position, Vec2 scale)
{
	m_extentHalf = scale * .5f;
	m_center = position;
	ResetMinMax(m_center);

	// TODO: rotate and translate this every time it moves for non-axis-alligned BB
}

void AABB::ResetMinMax(Vec2 position)
{
	m_center = position;

	m_max =
	{ m_center.x + m_extentHalf.x,
		m_center.y + m_extentHalf.y };

	m_min =
	{ m_center.x - m_extentHalf.x,
		m_center.y - m_extentHalf.y };
}

bool AABB::Overlaps( const AABB& boxB, Vec2& normal )
{
	// A SEPARATING AXIS WAS FOUND, so exit with no intersection
	if ( m_max.x < boxB.m_min.x || m_min.x > boxB.m_max.x ) return false;
	if ( m_max.y < boxB.m_min.y || m_min.y > boxB.m_max.y ) return false;

	// get slope of line
	Vec2 AtoB = boxB.m_center - m_center;
	float slope;

	// catch infinite slope error
	if ( AtoB.x == 0.0f )
		slope = 2.0f; // anything above 1 will do!
	else
		slope = AtoB.y / AtoB.x;

	// DETERMINE ORTHO NORMALS (BRUTE FORCE)
	if ( abs( slope ) > 1.0 ) // STEEP SLOPE = EITHER ABOVE OR BELOW
	{
		if ( AtoB.y > 0.0f ) // A is BELOW
		{
			normal = { 0.0f, 1.0f };
			return true;
		}
		else // A is ABOVE
		{
			normal = { 0.0f, -1.0f };
			return true;
		}
	}
	else if ( abs( slope ) < 1.0f )// SHALLOW SLOPE = EITHER LEFT OR RIGHT
	{
		if ( AtoB.x > 0.0f ) // RIGHT SIDE
		{
			normal = { 1.0f, 0.0f };
			return true;
		}
		else // LEFT SIDE
		{
			normal = { -1.0f, 0.0f };
			return true;
		}
	}
	// DETERMINE DIAGONAL NORMALS (CORNER CASES)
	else if ( slope == 1.0 ) // EITHER TOP RIGHT OR BOTTOM LEFT
	{
		if ( AtoB.x > 0.0f ) // RIGHT SIDE
		{
			normal = { 0.707107, 0.707107 };
			return true;
		}
		else // LEFT SIDE
		{
			normal = { -0.707107, -0.707107 };
			return true;
		}
	}
	else if ( slope == -1.0 ) // EITHER TOP LEFT OR BOTTOM RIGHT
	{
		if ( AtoB.x > 0.0f ) // RIGHT SIDE
		{
			normal = { 0.707107, -0.707107 };
			return true;
		}
		else // LEFT SIDE
		{
			normal = { -0.707107, 0.707107 };
			return true;
		}
	}
	else // No separating axis found, therefore there is at least one overlapping axis
		return true;
}

//
//Vec2 operator*= (Vec2 thisVec, float scalar)
//{
//	return{ thisVec.x*scalar, thisVec.y*scalar};
//}
//
//Vec2 operator*( Vec2 thisVec, float scalar )
//{
//	return{ thisVec.x*scalar, thisVec.y*scalar};
//}