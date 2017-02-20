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
#include "Shapes.h"
#include "Square.h"
#include "Body.h"
#include "BoundingVolumes.h"
#include "Vec2.h"
#include <memory>
#include <algorithm>
#include <cstdint>

namespace Collision
{
	bool AABBvAABB( Body& A, Body& B, Vec2& normal, float& penetration );
	bool CirclevCircle( Body& A, Body& B, Vec2& normal, float& penetration );
	bool AABBvCircle( Body& A, Body& B, Vec2& normal, float& penetration );
	bool CirclevAABB( Body& A, Body& B, Vec2& normal, float& penetration );

	bool CirclevNGON( Body& A, Body& B, Vec2& normal, float& penetration );
	bool NGONvCircle( Body& A, Body& B, Vec2& normal, float& penetration );
	bool AABBvNGON( Body & A, Body & B, Vec2 & normal, float & penetration );
	bool NGONvAABB( Body& A, Body& B, Vec2& normal, float& penetration );
	bool NGONvNGON( Body & A, Body & B, Vec2 & normal, float & penetration );

	void ResolveCollision( Body& A, Body& B, Vec2& normal );
	void CorrectPosition( Body& A, Body& B, const Vec2& normal, float penetration );

	//////////////////// 2D JUMP TABLE ///////////////////////////
	typedef bool( *CollisionAddress )( Body& A, Body& B, Vec2& normal, float& penetration );

	// NOTE - we implicitly cast NGON enum value to an int to tell size of the array
	extern CollisionAddress CollisionArray[ Shape::SHAPECOUNT ][ Shape::SHAPECOUNT ];

}