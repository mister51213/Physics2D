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

		//WRONG: Must translate the squares AFTER rotation!
		//vertices.push_back( { position.x - side, position.y - side } );
		//vertices.push_back( {position.x - side, position.y + side} );
		//vertices.push_back( {position.x + side, position.y + side} );
		//vertices.push_back( {position.x +side, position.y -side});

		//vertices.push_back( { -side, -side } );
		//vertices.push_back( { -side, side } );
		//vertices.push_back( { side, side } );
		//vertices.push_back( {side, -side} );

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

public:
	float m_theta;
	Vec2 m_position;

private:
	//AABB m_bounds;
	std::vector<Vec2> vertices;

};

