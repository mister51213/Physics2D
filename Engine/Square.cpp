#include "Square.h"
#include "Collision.h"

Square::Square( float size, Vec2 position, float mass, float bounciness )
	:
	m_position( position ),
	m_bounds( position, { size, size } ),
	m_mass( mass ),
	m_restitution( bounciness )
{
	if ( m_mass == 0.0f )
		m_inverseMass = 0.0f;
	else
		m_inverseMass = 1.0f / m_mass;

	const float side = size / 2.0f;

	vertices.emplace_back( -side, -side );
	vertices.emplace_back( -side, side );
	vertices.emplace_back( side, side );
	vertices.emplace_back( side, -side );
}

IndexedLineList Square::GetLines() const
{
	return
	{
		vertices, { 0, 1, 1, 2, 2, 3, 3, 0 }
	};
}

void Square::Thrust( Vec2 force, float deltaT )
{
	m_velocity += force *m_inverseMass* deltaT;
}

void Square::Stop()
{
	m_velocity = { 0.f, 0.f };
}

void Square::UpdatePosition( float deltaT )
	{
		m_position += m_velocity*deltaT;
		m_bounds.ResetMinMax(m_position);
	}
