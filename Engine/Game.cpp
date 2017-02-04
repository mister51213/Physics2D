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
#include "Mat2.h"

using namespace std;

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
	/*************SET MASS TO 0 FOR IMMOBILE OBJECT**************/
	// colliding squares
	m_squares.push_back( Square( .1f, { -.5f, 0.f }, 1.f, 0.5f ) );
	m_squares.push_back( Square( .1f, { .5f, 0.f }, 1.f, 0.5f ) );

	// walls
	m_squares.push_back( Square( 1.45f, { -1.5f, 0.f }, 0.f, 1.0f ) );
	m_squares.push_back( Square( 1.45f, { 1.5f, 0.f }, 0.f, 1.0f ) );

	// floor
	m_squares.push_back( Square( 1.45f, { 0.f, -1.5f }, 0.f, 1.0f ) );

	// ceiling
	m_squares.push_back( Square( 1.45f, { 0.f, 1.5f }, 0.f, 1.0f ) );
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
	for ( int i = 0; i < m_squares.size() - 1; ++i )
	{
		for ( int j = i + 1; j < m_squares.size(); ++j )
		{
			Vec2 normal;
			float penetration = 0.01f; // TODO: change this
			if ( Overlap_AABB( m_squares[ i ].m_bounds, m_squares[ j ].m_bounds, normal ) )
			{
				ResolveCollision( m_squares[ i ], m_squares[ j ], normal );
				CorrectPosition( m_squares[ i ], m_squares[ j ] , normal, penetration);			
			}
		}
	}
}

void Game::UpdateModel()
{	
	// TIMER 
	#ifdef NDEBUG
	float dTime = m_timer.SecondsPassed();
	#else
	float dTime = 0.016f; // avg time btwn frames (60 FPS)
	#endif

	DoCollision();

	for ( int i = 0; i < /*nObjects*/2; i++ )
	{
		m_squares[ i ].UpdatePositon(dTime);
	}

		// VECS TOWARD CENTER
		//Vec2 center = { 0.f, 0.f };
		//Vec2 thrustVecL = center - m_squares[ 0 ].m_position;
		//thrustVecL.Normalize();
		//thrustVecL *= 0.4;
		//Vec2 thrustVecR = -thrustVecL;

		// MOVE LEFT SQUARE
		if ( wnd.kbd.KeyIsPressed( 'W' ) )
		{
			m_squares[ 0 ].Thrust( {0.f, 0.3f}, dTime );
		}
		if ( wnd.kbd.KeyIsPressed( 'S' ) )
		{
			m_squares[ 0 ].Thrust( {0.f, -0.3f}, dTime );
		}
		if ( wnd.kbd.KeyIsPressed( 'A' ) )
		{
			m_squares[ 0 ].Thrust( {-0.4, 0.f}, dTime );
		}
		if ( wnd.kbd.KeyIsPressed( 'D' ) )
		{
			m_squares[ 0 ].Thrust( {0.4, 0.f}, dTime );
		}

		// MOVE RIGHT SQUARE
		if ( wnd.kbd.KeyIsPressed( VK_UP ) )
		{
			m_squares[ 1 ].Thrust( { 0.f, 0.3f }, dTime );
		}
		if ( wnd.kbd.KeyIsPressed( VK_DOWN ) )
		{
			m_squares[ 1 ].Thrust( { 0.f, -0.3f }, dTime );
		}
		if ( wnd.kbd.KeyIsPressed( VK_LEFT ) )
		{
			m_squares[ 1 ].Thrust( {-0.4, 0.f}, dTime );
		}
		if ( wnd.kbd.KeyIsPressed( VK_RIGHT ) )
		{
			m_squares[ 1 ].Thrust( {0.4, 0.f}, dTime );
		}
}

void Game::ComposeFrame()
{
//	vector<IndexedLineList> lines( nObjects );
//	for ( int i = 0; i < nObjects; i++)
//	{
//		lines[ i ] = gameObjects[ i ].GetLines();
//	}
//
//	// Rotate each Vertex
//	for ( int i = 0; i < nObjects; i++ )
//	{
//		const Mat3 rot =
//			Mat3::RotationX( gameObjects[ i ].theta_x ) *
//			Mat3::RotationY( gameObjects[ i ].theta_y ) *
//			Mat3::RotationZ( gameObjects[ i ].theta_z );
//		for ( Vec3& v : lines[ i ].vertices )
//		{
//			v *= rot;
//			v += { 0.0f, 0.0f, 1.0f };
//			sTransformer.Transform( v );
//		}
//	}
//
//	// Connect the vertices with lines here to form cube
//	for ( int ind = 0; ind < nObjects; ind++ )
//	{
//		IndexedLineList linesLocal = lines[ ind ]; // TODO: shouldnt be copying them
//		for ( auto i = linesLocal.indices.cbegin(),
//			  end = linesLocal.indices.cend();
//
//			  i != end; std::advance( i, 2 ) )
//		{
//			gfx.DrawLine( linesLocal.vertices[ *i ], linesLocal.vertices[ *std::next( i ) ], Colors::Blue );
//		}
//	}

	vector<IndexedLineList> lineLists( nObjects );
	for ( int i = 0; i < nObjects; i++)
	{
		lineLists[ i ] = m_squares[ i ].GetLines();
	}

	// Rotate each Vertex
	for ( int i = 0; i < nObjects; i++ )
	{
		const Mat2 rot =
			Mat2::Rotation( m_squares[ i ].m_theta );

		for ( Vec2& v : lineLists[ i ].vertices )
		{
			// Rotate
			v *= rot;
			// TODO: Translate to world space

			v += m_squares[ i ].m_position;

			// Translate to Screen space
			sTransformer.Transform( v );
		}
	}

	// Connect the vertices with lines here to form cube
	for ( int ind = 0; ind < nObjects; ind++ )
	{
		// for filling
		int left = gfx.ScreenWidth;
		int right = 0;

		// iterate all lines
		IndexedLineList linesLocal = lineLists[ ind ]; // TODO: shouldnt be copying them
		for ( auto i = linesLocal.indices.cbegin(),
			  end = linesLocal.indices.cend();

	    i != end; std::advance( i, 2 ) )
		{
			// TODO: doesnt work and too slow
			// get info for filling 
			//if ( linesLocal.vertices[ *i ].x < left )
			//	left = linesLocal.vertices[ *i ].x < left;
			//if ( linesLocal.vertices[ *i ].x > right )
			//	right = linesLocal.vertices[ *i ].x;
			//if ( linesLocal.vertices[ *std::next( i ) ].x < left )
			//	left = linesLocal.vertices[ *std::next( i ) ].x < left;
			//if ( linesLocal.vertices[ *std::next( i ) ].x > right )
			//	right = linesLocal.vertices[ *std::next( i ) ].x;

			gfx.DrawLine( linesLocal.vertices[ *i ], linesLocal.vertices[ *std::next( i ) ], Colors::Blue );
		}

		// Fill in cube left to right
		//for ( int x = left; x < right; x++ )
		//{
		//	for( int y = 0; y < 50; y++)
		//	gfx.PutPixel( x, y, Colors::Red );
		//}
	}
}



