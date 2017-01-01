#pragma once

#include "Collision.h"
#include "IndexedLineList.h"

class Square
{
public:
	Square() {}

	Square( float size, Vec2 position = { 0.f, 0.f }, float mass = 1.0f)
		:
		m_position( position ),
		m_bounds( position, { size, size } ),
		m_mass(mass)
	{
		const float side = size / 2.0f;

		vertices.emplace_back( -side, -side);
		vertices.emplace_back( -side, side );
		vertices.emplace_back( side, side);
		vertices.emplace_back( side, -side);
	}

	~Square() {}

	IndexedLineList GetLines() const
	{
		return{ 
			vertices,{ 0,1,1,2,2,3,3,0}
		};
	}

	void Thrust( Vec2 force, float deltaT )
	{
		m_velocity += force * deltaT;
	}

	void Stop()
	{
		m_velocity = { 0.f, 0.f };
	}

	void Rebound( Vec2 position, Vec2 velocity )
	{
		m_velocity = velocity;
	}

	void ReboundAlt( Square& other )
	{
		float massRatio = m_mass / other.m_mass;

		// TODO: Use Minkowski difference
		/*
		http://www.wildbunny.co.uk/blog/2011/04/20/collision-detection-for-dummies/
		*/

		// TODO: GET CLOSEST FACE - 
		/*
		A supporting vertex is simply a vertex which is "most in the direction of" 
		a given direction vector. Mathematically, this can be found as THE VERTEX 
		WHICH HAS THE GREATEST DOT PRODUCT with a given direction vector.
		*/
		
	//	if ( other.m_mass >= 200.f ) // Partner has INFINITE MASS
	//  {	
	//		// GET CLOSEST FACE 
	//	Vec2 normal = { 0.f, 1.f};

	//	XMFLOAT3 rbndComponent = normal * DotProduct( m_attributes.velocLin, normal );
	//	forceOnThis = m_attributes.velocLin - rbndComponent * 3.2f;
	//	forceOnPartner = { 0.f, 0.f, 0.f };
	//}
	//	else if ( m_attributes.mass >= 4000 ) // This object has INFINITE MASS
	//	{
	//		//XMFLOAT3 normal = m_AABBNorms[ eDir ];
	//		XMFLOAT3 normal = { 0.f, 1.f, 0.f };

	//		XMFLOAT3 rbndComponent = normal * DotProduct( partnerAttributes.velocLin, normal );
	//		forceOnThis = { 0.f, 0.f, 0.f };
	//		forceOnPartner = partnerAttributes.velocLin + rbndComponent;
	//	}

		// swap velocities
		Vec2 tempVeloc = m_velocity;
		m_velocity = other.m_velocity * massRatio;
		other.m_velocity = tempVeloc / massRatio;
	}

	void UpdatePositon(float deltaT)
	{
		m_position += m_velocity*deltaT;
		m_bounds.ResetMinMax(m_position);
	}

public:
	float m_theta = 0.f;
	Vec2 m_position;
	AABB m_bounds;
	Vec2 m_velocity = { 0.f, 0.f };
	float m_mass;
private:
	std::vector<Vec2> vertices;
};

