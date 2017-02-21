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

		switch ( type )
		{
			case Shape::CIRCLE:
			{
				m_scale = size * 0.5;
				break;
			}
			case Shape::SQUARE:
			{
				m_scale = size * 0.5;
				const float side = size * 0.5f;		

				vertices.emplace_back( -side, -side );
				vertices.emplace_back( -side, side );
				vertices.emplace_back( side, side );
				vertices.emplace_back( side, -side );

				m_bounds.reset( new AABB( position, { size, size } ) );
				break;
			}
			default:
				break;
		}
	}

	Shape::~Shape()
	{
		std::cout << "SHAPE WAS DESTROYED"  << std::endl;
	}

	// TODO: properly linkup theta from Body for rotated drawing
	void Shape::Draw(Graphics* gfx, const Vec2& position, const Color& c)
	{
		switch ( thisShape )
		{
			case Shape::CIRCLE:
				gfx->DrawCircle(position, m_scale, c);
				break;
			case Shape::SQUARE:
				gfx->DrawPoly(GetLines(), position, 0.f, m_scale, c);
				break;
			case Shape::SHAPECOUNT:
				break;
			default:
				break;
		}
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
		default:
			return{	vertices, { 0, 1, 1, 2, 2, 3, 3, 0 }};
			break;
	}
}

void Shape::UpdatePosition( const Vec2& position )
{
	// TODO: act differently depending on its shape
	switch ( thisShape )
	{
		case Shape::CIRCLE:
			break;
		case Shape::SQUARE:
			m_bounds->ResetMinMax(position);
			break;
		default:
			break;
	}
}