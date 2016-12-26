#pragma once

#include "Utilities.h"
#include "IndexedLineList.h"

class Square
{
public:
	Square() = default;

	Square( float size, Vec2 position)
		:
		m_position(position)/*,
		m_bounds(position, {size,size})*/
	{
		const float side = size / 2.0f;

		vertices.emplace_back( -side,-side);
		vertices.emplace_back( -side,side);
		vertices.emplace_back( side,side);
		vertices.emplace_back( side,-side);
	}

	~Square() = default;

	IndexedLineList GetLines() const
	{
		return{ 
			vertices,{ 0,1,1,2,2,3,3,0}
		};
	}

public:
	float m_theta;

private:
	//AABB m_bounds;
	Vec2 m_position;
	std::vector<Vec2> vertices;

};

