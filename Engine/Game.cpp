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

using namespace std;

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
	gameObjects[0] = ( Cube( 1.0f ) );
	gameObjects[1] = ( Cube( .5f ) );
	gameObjects[2] = ( Cube( .3f ) );
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
	const float dTime = 1.0f / 60.0f;

	// 3D rotation
	for ( int i = 0; i < nObjects; i++ )
	{

		if ( wnd.kbd.KeyIsPressed( 'Q' ) )
		{
			gameObjects[ i ].theta_x = wrap_angle( gameObjects[ i ].theta_x + dTheta * dTime );
		}
		if ( wnd.kbd.KeyIsPressed( 'W' ) )
		{
			gameObjects[ i ].theta_y = wrap_angle( gameObjects[ i ].theta_y + dTheta * dTime );
		}
		if ( wnd.kbd.KeyIsPressed( 'E' ) )
		{
			gameObjects[ i ].theta_z = wrap_angle( gameObjects[ i ].theta_z + dTheta * dTime );
		}
		if ( wnd.kbd.KeyIsPressed( 'A' ) )
		{
			gameObjects[ i ].theta_x = wrap_angle( gameObjects[ i ].theta_x - dTheta * dTime );
		}
		if ( wnd.kbd.KeyIsPressed( 'S' ) )
		{
			gameObjects[ i ].theta_y = wrap_angle( gameObjects[ i ].theta_y - dTheta * dTime );
		}
		if ( wnd.kbd.KeyIsPressed( 'D' ) )
		{
			gameObjects[ i ].theta_z = wrap_angle( gameObjects[ i ].theta_z - dTheta * dTime );
		}
	}
}

void Game::ComposeFrame()
{
	//auto lines1 = cube1.GetLines();
	//auto lines2 = cube2.GetLines();
	//auto lines3 = cube3.GetLines();

	vector<IndexedLineList> lines( nObjects );
	for ( int i = 0; i < nObjects; i++)
	{
		lines[ i ] = gameObjects[ i ].GetLines();
	}

	//const Mat3 rot =
	//	Mat3::RotationX( theta_x ) *
	//	Mat3::RotationY( theta_y ) *
	//	Mat3::RotationZ( theta_z );
	//for( auto& v : lines1.vertices )
	//{
	//	v *= rot;
	//	v += { 0.0f,0.0f,1.0f };
	//	sTransformer.Transform( v );
	//}
	//for( auto& v : lines2.vertices )
	//{
	//	v *= rot;
	//	v += { 0.0f,0.0f,1.0f };
	//	sTransformer.Transform( v );
	//}

	//for( auto& v : lines3.vertices )
	//{
	//	v *= rot;
	//	v += { 0.0f,0.0f,1.0f };
	//	sTransformer.Transform( v );
	//}

	for ( int i = 0; i < nObjects; i++ )
	{
		const Mat3 rot =
			Mat3::RotationX( gameObjects[ i ].theta_x ) *
			Mat3::RotationY( gameObjects[ i ].theta_y ) *
			Mat3::RotationZ( gameObjects[ i ].theta_z );
		for ( auto& v : lines[ i ].vertices )
		{
			v *= rot;
			v += { 0.0f, 0.0f, 1.0f };
			sTransformer.Transform( v );
		}
	}

	// Connect the vertices with lines here to form cube

	//for( auto i = lines1.indices.cbegin(),
	//	end = lines1.indices.cend();
	//	i != end; std::advance( i,2 ) )
	//{
	//	gfx.DrawLine( lines1.vertices[*i],lines1.vertices[*std::next( i )],Colors::White );
	//}

	//for( auto i = lines2.indices.cbegin(),
	//	end = lines2.indices.cend();
	//	i != end; std::advance( i,2 ) )
	//{
	//	gfx.DrawLine( lines2.vertices[*i],lines2.vertices[*std::next( i )],Colors::Red );
	//}

	//for( auto i = lines3.indices.cbegin(),
	//	end = lines3.indices.cend();
	//	i != end; std::advance( i,2 ) )
	//{
	//	gfx.DrawLine( lines3.vertices[*i],lines3.vertices[*std::next( i )],Colors::Blue );
	//}

	for ( int ind = 0; ind < nObjects; ind++ )
	{
		IndexedLineList linesLocal = lines[ ind ];
		for ( auto i = linesLocal.indices.cbegin(),
			  end = linesLocal.indices.cend();

			  i != end; std::advance( i, 2 ) )
		{
			gfx.DrawLine( linesLocal.vertices[ *i ], linesLocal.vertices[ *std::next( i ) ], Colors::Blue );
		}
	}
}



