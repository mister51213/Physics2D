#pragma once

#include "Utilities.h"
#include "IndexedLineList.h"

class Square
{
public:
	Square() {}

	Square( float size, Vec2 position = { 0.f, 0.f } )
		:
		m_position( position )
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

	void UpdatePositon(float deltaT)
	{
		m_position += m_velocity*deltaT;
	}

public:
	float m_theta = 0.f;
	Vec2 m_position;

private:
	//AABB m_bounds;
	std::vector<Vec2> vertices;

	Vec2 m_velocity = { 0.f, 0.f };
};

