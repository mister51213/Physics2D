#pragma once

#include <d3d11.h>
#include <windows.h>
#include <d2d1_1.h>
#include <d3dcompiler.h>
#include <dwrite.h>
#include <wincodec.h>
#include <DirectXMath.h>
#include <wrl.h>
#include <vector>
#include "Vec2.h"

struct AABB
{
	AABB() = default;
	AABB(Vec2 position, Vec2 scale);
	void ResetMinMax(Vec2 position);

	Vec2 m_center;
    Vec2 m_extentHalf;
	Vec2 m_min;
    Vec2 m_max;
	std::vector<Vec2> m_Normals;
};

//Vec2 operator*= ( Vec2 thisVec, float scalar );
//Vec2 operator* ( Vec2 thisVec, float scalar );