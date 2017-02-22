#pragma once

#include "BoundingVolumes.h"
#include "Collision.h"
#include <memory>

class Body
{
friend class Shape;

public:
	Body() = default;
	Body(Body &&){}
	Body( float size, Vec2 position, float mass, float bounciness, Shape::eShape type = Shape::SQUARE);

	~Body();

	// NOTE - GetLines and drawing / vertex related functions now in SHAPE
	void Thrust( Vec2 force, float deltaT );

	void AddForce( const Vec2& force );

	void Stop();

	void UpdateForces( float deltaT );

	void UpdatePosition( float deltaT );

public:
	float m_theta = 0.f;

	//AABB m_bounds;
	Vec2 m_position;
	Vec2 m_velocity = { 0.f, 0.f };
	Vec2 m_force;

	float m_mass;
	float m_inverseMass;
	float m_restitution;

	std::shared_ptr<Shape> m_pShape;

	Vec2 m_netForce = { 0.f, 0.f };
};

