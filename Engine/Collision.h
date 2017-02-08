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
#include "BoundingVolumes.h"
#include "Vec2.h"

namespace Collision
{
	bool AABBvAABB( Square& A, Square& B, Vec2& normal, float& penetration );

	bool CirclevCircle( Square& A, Square& B, Vec2& normal, float& penetration );

	bool AABBvCircle( Square& A, Square& B, Vec2& normal, float& penetration );

	//static bool Overlap_CircleNgon(Vec2& normal, float& penetration){}
	bool CirclevNgon( Square& A, Square& B, Vec2& normal, float& penetration );

	void ResolveCollision( Square& A, Square& B, Vec2& normal );

	void CorrectPosition( Square& A, Square& B, const Vec2& normal, float penetration );

	//////////////////// 2D JUMP TABLE ///////////////////////////
	// pointer to a function
	typedef bool( *CollisionAddress )( Square& A, Square& B, Vec2& normal, float& penetration );

	// this should return the address of the proper collision function
	// TODO: make implement Body class so it can be passed to the overlap functions
	// NOTE - we implicitly cast NGON enum value to an int to tell size of the array
	extern CollisionAddress CollisionArray[ Shape::NGON ][ Shape::NGON ];

}