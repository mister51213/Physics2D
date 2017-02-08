#pragma once

#include "Vec2.h"

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
};

struct Body
{
	Shape* pShape;
	Material material;
	float mass;
	float inverseMass;
	Vec2 velocity;
	Vec2 force;
};

