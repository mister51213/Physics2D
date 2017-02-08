#pragma once

#include <vector>
#include "Vec2.h"

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

Shape() = default;

Shape( eShape type );

// TODO: encapsulate GetLines into this
void Draw();

eShape GetType();

// TODO: customize this based on shape
IndexedLineList GetLines(Shape::eShape shape = Shape::SQUARE) const;

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

