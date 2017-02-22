/******************************************************************************************
*	Chili DirectX Framework Version 16.10.01											  *
*	Game.cpp																			  *
*	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "Mat3.h"
//#include "Mat2.h"
#include "Collision.h"
#include "Shapes.h"

using namespace std;
using namespace Collision;

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
	/*************SET MASS TO 0 FOR IMMOBILE OBJECT***********/
	// colliding objects
	m_bodies.emplace_back( new Body( .2f, { -.5f, 0.f }, 0.f, 0.5f, Shape::SQUARE ) );
	m_bodies.emplace_back( new Body( .1f, { .5f, 0.f }, 1.f, 0.5f, Shape::CIRCLE ) );

	m_normVisual = m_bodies[0]->m_position;
	//m_bodies.emplace_back( new Body( .1f, { .3f, 0.f }, 1.f, 0.5f, Shape::SQUARE ) );

	//// walls, ceiling, floor
	//m_bodies.emplace_back( new Body( 1.48f, { -1.5f, 0.f }, 0.f, 1.0f, Shape::SQUARE ) );
	//m_bodies.emplace_back( new Body( 1.44f, { 1.5f, 0.f }, 0.f, 1.0f, Shape::SQUARE ) );
	//m_bodies.emplace_back( new Body( 1.41f, { 0.f, -1.5f }, 0.f, 1.0f, Shape::SQUARE ) );
	//m_bodies.emplace_back( new Body( 1.38f, { 0.f, 1.5f }, 0.f, 1.0f, Shape::SQUARE ) );
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::DoCollision()
{
	for ( int i = 0; i < m_bodies.size() - 1; ++i )
	{
		for ( int j = i + 1; j < m_bodies.size(); ++j )
		{
			Vec2 normal;
			float penetration;
			if ( CollisionArray[ m_bodies[ i ]->m_pShape->GetType() ][ m_bodies[ j ]->m_pShape->GetType() ]( *m_bodies[ i ], *m_bodies[ j ], normal, penetration ) )
			{
				//m_bodies[ i ]->Stop();
				//m_bodies[ j ]->Stop();

				m_normVisual = normal;

				ResolveCollision( *m_bodies[ i ], *m_bodies[ j ], normal );			
				CorrectPosition( *m_bodies[ i ], *m_bodies[ j ] , normal, penetration);			
			}
		}
	}
}

void Game::UpdateModel()
{	
	// TODO: Get Discrete chunks of time
	/*
	https://gamedevelopment.tutsplus.com/tutorials/how-to-create-a-custom-2d-physics-engine-the-core-engine--gamedev-7493#integration
	*/

	// TIMER 
	#ifdef NDEBUG
	float dTime = m_timer.SecondsPassed();
	#else
	float dTime = 0.016f; // avg time btwn frames (60 FPS)
	#endif

	DoCollision();

	for ( int i = 0; i < m_bodies.size()/*nObjects*/; i++ )
	{
		m_bodies[ i ]->UpdatePosition(dTime);
	}
	
		// MOVE LEFT SQUARE
		if ( wnd.kbd.KeyIsPressed( 'W' ) )
		{
			m_bodies[ 0 ]->Thrust( {0.f, 0.3f}, dTime );
		}
		if ( wnd.kbd.KeyIsPressed( 'S' ) )
		{
			m_bodies[ 0 ]->Thrust( {0.f, -0.3f}, dTime );
		}
		if ( wnd.kbd.KeyIsPressed( 'A' ) )
		{
			m_bodies[ 0 ]->Thrust( {-0.4, 0.f}, dTime );
		}
		if ( wnd.kbd.KeyIsPressed( 'D' ) )
		{
			m_bodies[ 0 ]->Thrust( {0.4, 0.f}, dTime );
		}

		// MOVE RIGHT SQUARE
		if ( wnd.kbd.KeyIsPressed( VK_UP ) )
		{
			m_bodies[ 1 ]->Thrust( { 0.f, 0.3f }, dTime );
		}
		if ( wnd.kbd.KeyIsPressed( VK_DOWN ) )
		{
			m_bodies[ 1 ]->Thrust( { 0.f, -0.3f }, dTime );
		}
		if ( wnd.kbd.KeyIsPressed( VK_LEFT ) )
		{
			m_bodies[ 1 ]->Thrust( {-0.4, 0.f}, dTime );
		}
		if ( wnd.kbd.KeyIsPressed( VK_RIGHT ) )
		{
			m_bodies[ 1 ]->Thrust( {0.4, 0.f}, dTime );
		}
}

void Game::ComposeFrame()
{
	for ( int ind = 0; ind < m_bodies.size(); ind++ )
	{
		// GET POSITION (copy it so actual actor stays unaffected)
		Vec2 position = m_bodies[ ind ]->m_position;

		// Polymorphic draw call
		m_bodies[ ind ]->m_pShape->Draw(&gfx, position, Colors::Cyan);

		Vec2 norm = m_normVisual;
		Vec2 pos = m_bodies[ ind ]->m_position;

		sTransformer.Transform( norm );
		sTransformer.Transform( pos );

		gfx.DrawLine( norm, pos, Colors::Green );
	}
}