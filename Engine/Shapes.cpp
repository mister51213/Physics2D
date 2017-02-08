#include "Shapes.h"

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

	Shape::Shape( eShape type )
	{
		thisShape = type;
	}

	void Shape::Draw()
	{
	
	}

	Shape::eShape Shape::GetType()
	{
		return thisShape;
	}
