#pragma once

#include "BoundingVolumes.h"
#include "Collision.h"
#include <memory>

class Body
{
public:
	Body() = default;
	Body(Body &&){}
	Body( float size, Vec2 position, float mass, float bounciness, Shape::eShape type = Shape::SQUARE);

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

//	Shape* m_pShape;
	std::unique_ptr<Shape> m_pShape;
};

