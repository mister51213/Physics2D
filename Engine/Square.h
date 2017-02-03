#pragma once

#include "Collision.h"
#include "IndexedLineList.h"

class Square
{
public:
	Square() {}

	Square( float size, Vec2 position = { 0.f, 0.f }, float mass = 1.0f, bool mobility = true)
		:
		m_position( position ),
		m_bounds( position, { size, size } ),
		m_mass(mass),
		m_mobility(mobility)
	{
		const float side = size / 2.0f;

		vertices.emplace_back( -side, -side);
		vertices.emplace_back( -side, side );
		vertices.emplace_back( side, side);
		vertices.emplace_back( side, -side);
	}

	~Square() {}

	bool IsMobile()	{return m_mobility;}

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

	void ResolveCollision( Square& square, Square& otherSquare )
	{
		// OLD WAY (SWAP VELOCITIES)
		//float massRatio = m_mass / other.m_mass;
		//Vec2 tempVeloc = m_velocity;
		//m_velocity = other.m_velocity * massRatio;
		//other.m_velocity = tempVeloc / massRatio;
		Vec2 velo1 = square.m_velocity;
			Vec2 velo2 = otherSquare.m_velocity;
		
		// Velocity vector between the centers of the colliding objects
		Vec2 relativeVelo = velo1 - velo2;
		// Project this velocity onto the normal
		float velProjNorm = relativeVelo*normal();
	
	
	}

	void UpdatePositon(float deltaT)
	{
		m_position += m_velocity*deltaT;
		m_bounds.ResetMinMax(m_position);
	}

public:
	float m_theta = 0.f;
	AABB m_bounds;
	Vec2 m_position;
	Vec2 m_normal;
	Vec2 m_velocity = { 0.f, 0.f };
	float m_mass;
	bool m_mobility;

private:
	std::vector<Vec2> vertices;
};

