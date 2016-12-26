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
