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
	m_squares[0] = ( Square( 1.f, { -.5f, 0.f } ) );
	m_squares[1] = ( Square( 6.f, { .5f, 0.f } ) );
	m_squares[2] = ( Square( .4f, { 0.f, .5f } ) );
	m_squares[3] = ( Square( .2f, { 0.f, -.5f } ) );
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dTime = 1.0f / 120.0f;

	// 3D rotation
	for ( int i = 0; i < nObjects; i++ )
	{
		float dThetL = dTheta;;
		if ( i / 2 == 0 )
			dThetL *= -1.f;

		// SPIN
		if ( wnd.kbd.KeyIsPressed( 'Q' ) )
		{
			m_squares[ i ].m_theta = wrap_angle( m_squares[ i ].m_theta + dThetL * dTime );
		}
		if ( wnd.kbd.KeyIsPressed( 'W' ) )
		{
			m_squares[ i ].m_theta = wrap_angle( m_squares[ i ].m_theta + dThetL * dTime );
		}
		if ( wnd.kbd.KeyIsPressed( 'E' ) )
		{
			m_squares[ i ].m_theta = wrap_angle( m_squares[ i ].m_theta + dThetL * dTime );
		}
		if ( wnd.kbd.KeyIsPressed( 'A' ) )
		{
			m_squares[ i ].m_theta = wrap_angle( m_squares[ i ].m_theta - dThetL * dTime );
		}
		if ( wnd.kbd.KeyIsPressed( 'S' ) )
		{
			m_squares[ i ].m_theta = wrap_angle( m_squares[ i ].m_theta - dThetL * dTime );
		}
		if ( wnd.kbd.KeyIsPressed( 'D' ) )
		{
			m_squares[ i ].m_theta = wrap_angle( m_squares[ i ].m_theta - dThetL * dTime );
		}

		// MOVE
		if ( wnd.kbd.KeyIsPressed( VK_UP ) )
		{
			m_squares[ i ].m_position += {0.f, 0.01f};
		}
		if ( wnd.kbd.KeyIsPressed( VK_DOWN ) )
		{
			m_squares[ i ].m_position += {0.f, -0.01f};
		}
		if ( wnd.kbd.KeyIsPressed( VK_LEFT ) )
		{
			m_squares[ i ].m_position += {-0.01f, 0.f};
		}
		if ( wnd.kbd.KeyIsPressed( VK_RIGHT ) )
		{
			m_squares[ i ].m_position += {0.01f, 0.f};
		}
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
		IndexedLineList linesLocal = lineLists[ ind ]; // TODO: shouldnt be copying them
		for ( auto i = linesLocal.indices.cbegin(),
			  end = linesLocal.indices.cend();

			  i != end; std::advance( i, 2 ) )
		{
			gfx.DrawLine( linesLocal.vertices[ *i ], linesLocal.vertices[ *std::next( i ) ], Colors::Blue );
		}
	}
}



