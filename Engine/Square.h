#pragma once

#include "Collision.h"
#include "IndexedLineList.h"

class Square
{
public:
	Square() {}

	Square( float size, Vec2 position = { 0.f, 0.f }, float mass = 1.0f, float bounciness = 1.0f, bool mobility = true)
		:
		m_position( position ),
		m_bounds( position, { size, size } ),
		m_mass(mass),
		m_mobility(mobility),
		m_restitution(bounciness)
	{
		if ( m_mass == 0.0f )
			m_inverseMass = 0.0f;
		else
			m_inverseMass = 1.0f / m_mass;

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
	float m_inverseMass;
	bool m_mobility;
	float m_restitution;

private:
	std::vector<Vec2> vertices;
};

