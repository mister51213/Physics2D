#include "Body.h"

Body::Body()
{}

Body::Body( float size, Vec2 position, float mass, float bounciness, Shape::eShape type )
	:
	m_position( position ),
	m_bounds( position, { size, size } ),
	m_mass( mass ),
	m_restitution( bounciness )
{
	// SET INVERSE MASS
	if ( m_mass == 0.0f )
		m_inverseMass = 0.0f;
	else
		m_inverseMass = 1.0f / m_mass;

	// SET SHAPE TYPE
	m_pShape->thisShape = type;

	// TODO: encapsulate for different shapes
	const float side = size / 2.0f;
	
	m_pShape->vertices.emplace_back( -side, -side );
	m_pShape->vertices.emplace_back( -side, side );
	m_pShape->vertices.emplace_back( side, side );
	m_pShape->vertices.emplace_back( side, -side );
}

Body::~Body()
{}

void Body::Thrust( Vec2 force, float deltaT )
{
	m_velocity += force *m_inverseMass* deltaT;
}

void Body::Stop()
{
	m_velocity = { 0.f, 0.f };
}

void Body::UpdatePosition( float deltaT )
{
	m_position += m_velocity*deltaT;
	m_bounds.ResetMinMax(m_position);
}