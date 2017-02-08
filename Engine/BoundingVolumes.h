#pragma once

#include <vector>

#include "Vec2.h"

struct AABB
{
public:
	AABB();
	AABB(Vec2 position, Vec2 scale);
	void ResetMinMax(Vec2 position);

	Vec2 m_center;
    Vec2 m_extentHalf;
	Vec2 m_min;
    Vec2 m_max;
	std::vector<Vec2> m_Normals;
};