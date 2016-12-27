#include "Utilities.h"


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

bool AABB::Overlaps( const AABB& box2 )
{
	// A SEPARATING AXIS WAS FOUND, so exit with no intersection
	if ( m_max.x < box2.m_min.x || m_min.x > box2.m_max.x ) return false;
	if ( m_max.y < box2.m_min.y || m_min.y > box2.m_max.y ) return false;
 
  // No separating axis found, therefore there is at least one overlapping axis
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
