#pragma once

#include "BoundingVolumes.h"
#include "Collision.h"
//#include "Shapes.h"

class Body
{
public:
	Body();
	Body( float size, Vec2 position, float mass, float bounciness);
	~Body();
	
	// NOTE - GetLines and drawing / vertex related functions now in SHAPE
	void Thrust( Vec2 force, float deltaT );

	void Stop();

	void UpdatePosition( float deltaT );

public:
	float m_theta = 0.f;

	AABB m_bounds;
	Vec2 m_position;
	Vec2 m_velocity = { 0.f, 0.f };
	Vec2 m_force;

	float m_mass;
	float m_inverseMass;
	float m_restitution;

	Shape* m_pShape;
};

