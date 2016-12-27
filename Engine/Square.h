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

