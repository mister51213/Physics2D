#include "Body.h"

Body::Body( float size, Vec2 position, float mass, float bounciness, Shape::eShape type )
	:
	m_position( position ),
//	m_bounds( position, { size, size } ),
	m_mass( mass ),
	m_restitution( bounciness )
{
	// SET INVERSE MASS
	if ( m_mass == 0.0f )
		m_inverseMass = 0.0f;
	else
		m_inverseMass = 1.0f / m_mass;

	// INIT SHAPE
	m_pShape.reset(new Shape( type, size, position ));
}

Body::~Body()
{}

void Body::Thrust( Vec2 force, float deltaT )
{
	//m_velocity += force *m_inverseMass* deltaT;
	AddForce( force );
}

void Body::AddForce(const Vec2& force)
{
	m_netForce += force;
}

void Body::Stop()
{
	m_velocity = { 0.f, 0.f };
}

void Body::UpdateForces( float deltaT )
{
	m_velocity += m_netForce *m_inverseMass* deltaT;
	m_netForce = {0.f, 0.f};
}

void Body::UpdatePosition( float deltaT )
{
	m_position += m_velocity*deltaT;
	m_pShape->UpdatePosition(m_position);
}