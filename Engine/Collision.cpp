#include "Collision.h"

namespace Collision
{
	CollisionAddress CollisionArray[ Shape::NGON ][ Shape::NGON ] =
	{
		{
			AABBvAABB, AABBvCircle
		},
		{
			CirclevCircle, CirclevNgon
		}
	};

	bool AABBvAABB( Square& A, Square& B, Vec2& normal, float& penetration )
	{
		// A SEPARATING AXIS WAS FOUND, so exit with no intersection
		if ( A.m_bounds.m_max.x < B.m_bounds.m_min.x || A.m_bounds.m_min.x > B.m_bounds.m_max.x ) return false;
		if ( A.m_bounds.m_max.y < B.m_bounds.m_min.y || A.m_bounds.m_min.y > B.m_bounds.m_max.y ) return false;
		// IF we get to this step, then boxes have collided, now create normals/penetration (MANIFOLD)

		// Get Vector from A to B
		Vec2 AtoB = B.m_position - A.m_position;

		// Calculate overlap on x axis
		float xOverlap = A.m_bounds.m_extentHalf.x + B.m_bounds.m_extentHalf.x - abs( AtoB.x );

		// Separating axis theorem test for X AXIS
		if ( xOverlap > 0.0f )
		{
			// Calculate overlap on y axis
			float yOverlap = A.m_bounds.m_extentHalf.y + B.m_bounds.m_extentHalf.y - abs( AtoB.y );

			// SAT test on y axis
			if ( yOverlap > 0.0f )
			{
				if ( xOverlap < yOverlap ) // Axis of least penetration = X
				{	// If AtoB vector is (-), so is collision normal
					if ( AtoB.x < 0 )
						normal = Vec2( -1.0f, 0.0f );
					else
						normal = Vec2( 1.0f, 0.0f );

					penetration = xOverlap;
					return true;
				}
				else // Axis of least penetration = Y
				{	 // If AtoB vector is (-), so is collision normal
					if ( AtoB.y < 0 )
						normal = Vec2( 0.0f, -1.0f );
					else
						normal = Vec2( 0.0f, 1.0f );
					penetration = yOverlap;
					return true;
				}
			}
		}
	}

	bool AABBvAABB_temp( Body& A, Body& B, Vec2& normal, float& penetration )
	{
		std::shared_ptr<AABB> boundsA = A.m_pShape->m_bounds;
		std::shared_ptr<AABB> boundsB = B.m_pShape->m_bounds;

		// A SEPARATING AXIS WAS FOUND, so exit with no intersection
		if ( boundsA->m_max.x < boundsB->m_min.x || boundsA->m_min.x > boundsB->m_max.x ) return false;
		if ( boundsA->m_max.y < boundsB->m_min.y || boundsA->m_min.y > boundsB->m_max.y ) return false;
		// IF we get to this step, then boxes have collided, now create normals/penetration (MANIFOLD)

		// Get Vector from A to B
		Vec2 AtoB = B.m_position - A.m_position;

		// Calculate overlap on x axis
		float xOverlap = boundsA->m_extentHalf.x + boundsB->m_extentHalf.x - abs( AtoB.x );

		// Separating axis theorem test for X AXIS
		if ( xOverlap > 0.0f )
		{
			// Calculate overlap on y axis
			float yOverlap = boundsA->m_extentHalf.y + boundsB->m_extentHalf.y - abs( AtoB.y );

			// SAT test on y axis
			if ( yOverlap > 0.0f )
			{
				if ( xOverlap < yOverlap ) // Axis of least penetration = X
				{	// If AtoB vector is (-), so is collision normal
					if ( AtoB.x < 0 )
						normal = Vec2( -1.0f, 0.0f );
					else
						normal = Vec2( 1.0f, 0.0f );

					penetration = xOverlap;
					return true;
				}
				else // Axis of least penetration = Y
				{	 // If AtoB vector is (-), so is collision normal
					if ( AtoB.y < 0 )
						normal = Vec2( 0.0f, -1.0f );
					else
						normal = Vec2( 0.0f, 1.0f );
					penetration = yOverlap;
					return true;
				}
			}
		}
	}

	bool CirclevCircle( Square & A, Square & B, Vec2 & normal, float & penetration )
	{
		return false;
	}

	bool AABBvCircle( Square & A, Square & B, Vec2 & normal, float & penetration )
	{
		return false;
	}

	bool CirclevNgon( Square & A, Square & B, Vec2 & normal, float & penetration )
	{
		return false;
	}

	void ResolveCollision_temp( Body& A, Body& B, Vec2& normal )
	{
		// Velocity vector between the centers of the colliding objects
		Vec2 relativeVelo = B.m_velocity - A.m_velocity;

		// Project this velocity onto the normal
		// float velAlongNorm = relativeVelo*A.m_normal;
		float velAlongNorm = relativeVelo*normal;

		// Do not resolve if velocities are separating
		bool separating = velAlongNorm > 0;
		if ( separating )
			return;

		// Coefficient of resitution (min of two)
		float coefRest = min( A.m_restitution, B.m_restitution );

		// Calculate impulse scalar
		float j = -( 1.0f + coefRest ) * velAlongNorm; // NOTE: 2 INFINITE MASSES will cause a crash!
		j /= ( A.m_inverseMass + B.m_inverseMass );

		//Vec2 impulse = A.m_normal * j;
		Vec2 impulse = normal * j;

		// DISTRIBUTE THE IMPULSE AMONG BOTH OBJECTS ACCORDING TO THEIR RELATIVE MASSES
		A.m_velocity -= impulse * A.m_inverseMass;
		B.m_velocity += impulse * B.m_inverseMass;
	}

	//void ResolveCollision( Square& A, Square& B, Vec2& normal )
	//{
	//	// Velocity vector between the centers of the colliding objects
	//	Vec2 relativeVelo = B.m_velocity - A.m_velocity;

	//	// Project this velocity onto the normal
	//	// float velAlongNorm = relativeVelo*A.m_normal;
	//	float velAlongNorm = relativeVelo*normal;

	//	// Do not resolve if velocities are separating
	//	bool separating = velAlongNorm > 0;
	//	if ( separating )
	//		return;

	//	// Coefficient of resitution (min of two)
	//	float coefRest = min( A.m_restitution, B.m_restitution );

	//	// Calculate impulse scalar
	//	float j = -( 1.0f + coefRest ) * velAlongNorm; // NOTE: 2 INFINITE MASSES will cause a crash!
	//	j /= ( A.m_inverseMass + B.m_inverseMass );

	//	//Vec2 impulse = A.m_normal * j;
	//	Vec2 impulse = normal * j;

	//	// DISTRIBUTE THE IMPULSE AMONG BOTH OBJECTS ACCORDING TO THEIR RELATIVE MASSES
	//	A.m_velocity -= impulse * A.m_inverseMass;
	//	B.m_velocity += impulse * B.m_inverseMass;

	//	// NOTE: could also do it this (slower) way
	//	//float mass_sum = A.m_mass + B.m_mass;
	//	//float ratioA = A.m_mass / mass_sum;
	//	//float ratioB = B.m_mass / mass_sum;
	//	//A.m_velocity -= impulse * ratioA;
	//	//B.m_velocity += impulse * ratioB;
	//}

	// prevent objects from sinking
	//void CorrectPosition( Square& A, Square& B, const Vec2& normal, float penetration )
	//{
	//	const float percent = 0.2; // usually 20% to 80%
	//	const float threshold = 0.01; // usually 0.01 to 0.1
	//	float correctionAmt = max( penetration - threshold, 0.0f );

	//	correctionAmt /= A.m_inverseMass + B.m_inverseMass;

	//	float totalCorrection = percent * correctionAmt;

	//	Vec2 correctionVec = normal * totalCorrection;
	//	A.m_position -= correctionVec * A.m_inverseMass;
	//	B.m_position += correctionVec * B.m_inverseMass;
	//}

	void CorrectPosition_temp( Body& A, Body& B, const Vec2& normal, float penetration )
	{
		const float percent = 0.2; // usually 20% to 80%
		const float threshold = 0.01; // usually 0.01 to 0.1
		float correctionAmt = max( penetration - threshold, 0.0f );

		correctionAmt /= A.m_inverseMass + B.m_inverseMass;

		float totalCorrection = percent * correctionAmt;

		Vec2 correctionVec = normal * totalCorrection;
		A.m_position -= correctionVec * A.m_inverseMass;
		B.m_position += correctionVec * B.m_inverseMass;
	}
}

/// OLD IMPLEMENTATION ///
//static bool Overlap_AABB_OLD( const AABB& boxA, const AABB& boxB, Vec2& normal )
//{
//	// A SEPARATING AXIS WAS FOUND, so exit with no intersection
//	if ( boxA.m_max.x < boxB.m_min.x || boxA.m_min.x > boxB.m_max.x ) return false;
//	if ( boxA.m_max.y < boxB.m_min.y || boxA.m_min.y > boxB.m_max.y ) return false;
//
//	// get slope of line
//	Vec2 AtoB = boxB.m_center - boxA.m_center;
//	float slope;
//
//	// catch infinite slope error
//	if ( AtoB.x == 0.0f )
//		slope = 2.0f; // anything above 1 will do!
//	else
//		slope = AtoB.y / AtoB.x;
//
//	// DETERMINE ORTHO NORMALS (BRUTE FORCE)
//	if ( abs( slope ) > 1.0 ) // STEEP SLOPE = EITHER ABOVE OR BELOW
//	{
//		if ( AtoB.y > 0.0f ) // A is BELOW
//		{
//			normal = { 0.0f, 1.0f };
//			return true;
//		}
//		else // A is ABOVE
//		{
//			normal = { 0.0f, -1.0f };
//			return true;
//		}
//	}
//	else if ( abs( slope ) < 1.0f )// SHALLOW SLOPE = EITHER LEFT OR RIGHT
//	{
//		if ( AtoB.x > 0.0f ) // RIGHT SIDE
//		{
//			normal = { 1.0f, 0.0f };
//			return true;
//		}
//		else // LEFT SIDE
//		{
//			normal = { -1.0f, 0.0f };
//			return true;
//		}
//	}
//	// DETERMINE DIAGONAL NORMALS (CORNER CASES)
//	else if ( slope == 1.0 ) // EITHER TOP RIGHT OR BOTTOM LEFT
//	{
//		if ( AtoB.x > 0.0f ) // RIGHT SIDE
//		{
//			normal = { 0.707107, 0.707107 };
//			return true;
//		}
//		else // LEFT SIDE
//		{
//			normal = { -0.707107, -0.707107 };
//			return true;
//		}
//	}
//	else if ( slope == -1.0 ) // EITHER TOP LEFT OR BOTTOM RIGHT
//	{
//		if ( AtoB.x > 0.0f ) // RIGHT SIDE
//		{
//			normal = { 0.707107, -0.707107 };
//			return true;
//		}
//		else // LEFT SIDE
//		{
//			normal = { -0.707107, 0.707107 };
//			return true;
//		}
//	}
//	else // No separating axis found, therefore there is at least one overlapping axis
//		return true;
//}
