#pragma once

#include <vector>
#include "Vec2.h"
#include "BoundingVolumes.h"
#include <memory>

struct IndexedLineList;

enum eMaterial
{
	ROCK,
	WOOD,
	METAL,
	BOUNCYBALL,
	SUPERBALL,
	PILLOW,
	STATIC
};

struct Material
{
public:
	eMaterial type;
	float Density;
	float Restitution;

	Material( eMaterial mat );
};

class Shape
{
public:
enum eShape
{
	CIRCLE, 
	SQUARE,
	TRIANGLE,
	NGON
};

friend class Body;

eShape thisShape;
Shape();
Shape( eShape type, float size, Vec2 position );
~Shape();

// TODO: encapsulate GetLines into this
void Draw();

eShape GetType();

// TODO: customize this based on shape
IndexedLineList GetLines(Shape::eShape shape = Shape::SQUARE) const;

float m_radius = 0.1f;
std::shared_ptr<AABB> m_bounds;

private:
	std::vector<Vec2> vertices;
};

struct Body_For_Reference
{
	Shape* pShape;
	Material material;
	float mass;
	float inverseMass;
	Vec2 velocity;
	Vec2 force;
};

