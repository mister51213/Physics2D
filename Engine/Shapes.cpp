#include "Shapes.h"
#include "IndexedLineList.h"
#include <iostream>

	Material::Material( eMaterial mat )
	{
		type = mat;

		switch ( mat )
		{
			case ROCK:
				Density = 0.6;  Restitution = 0.1;
				break;
			case WOOD:
				Density = 0.3;  Restitution = 0.2;
				break;
			case METAL:
				Density = 1.2;  Restitution = 0.05;
				break;
			case BOUNCYBALL:
				Density = 0.3;  Restitution = 0.8;
				break;
			case SUPERBALL:
				Density = 0.3;  Restitution = 0.95;
				break;
			case PILLOW:
				Density = 0.1;  Restitution = 0.2;
				break;
			case STATIC:
				Density = 0.0;  Restitution = 0.4;
				break;
			default:
				break;
		}
	}

	Shape::Shape() {}

	Shape::Shape( eShape type, float size, Vec2 position )
	{
		thisShape = type;

		// TODO: customize for all types
		switch ( type )
		{
			case Shape::CIRCLE:
			{
				m_radius = size;
				break;
			}
			case Shape::SQUARE:
			{
				const float side = size / 2.0f;
				vertices.emplace_back( -side, -side );
				vertices.emplace_back( -side, side );
				vertices.emplace_back( side, side );
				vertices.emplace_back( side, -side );

				m_bounds.reset( new AABB( position, { size, size } ) );
				break;
			}
			case Shape::TRIANGLE:
				break;
			case Shape::NGON:
				break;
			default:
				break;
		}
	}

	Shape::~Shape()
	{
		std::cout << "SHAPE WAS DESTROYED"  << std::endl;
	}

	void Shape::Draw()
	{
	// TODO: encapsulate draw here
	}

	Shape::eShape Shape::GetType()
	{
		return thisShape;
	}


IndexedLineList Shape::GetLines(Shape::eShape thisShape) const
{
	// TODO: customize for different shape types
	switch ( thisShape )
	{
		case Shape::CIRCLE:
			return{	vertices, { 0, 1, 1, 2, 2, 3, 3, 0 }};
			break;
		case Shape::SQUARE:
			return{	vertices, { 0, 1, 1, 2, 2, 3, 3, 0 }};
			break;
		case Shape::TRIANGLE:
			return{	vertices, { 0, 1, 1, 2, 2, 3, 3, 0 }};
			break;
		case Shape::NGON:
			return{	vertices, { 0, 1, 1, 2, 2, 3, 3, 0 }};
			break;
		default:
			return{	vertices, { 0, 1, 1, 2, 2, 3, 3, 0 }};
			break;
	}
}