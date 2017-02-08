#pragma once

#include "IndexedLineList.h"
#include "BoundingVolumes.h"

struct AABB;

class Square
{
public:
	Square() {}

	Square( float size, Vec2 position, float mass, float bounciness);

	~Square() {}

	IndexedLineList GetLines() const;

	void Thrust( Vec2 force, float deltaT );

	void Stop();

	// TODO: add Symplectic Euler
	// v += (1/m * F) * dt
	// x += v * dt
	/*
	https://www.niksula.hut.fi/~hkankaan/Homepages/gravity.html
	*/
	void UpdatePosition( float deltaT );

public:
	float m_theta = 0.f;
	AABB m_bounds;
	Vec2 m_position;
	Vec2 m_velocity = { 0.f, 0.f };
	float m_mass;
	float m_inverseMass;
	float m_restitution;

private:
	std::vector<Vec2> vertices;
};

