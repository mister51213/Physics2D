/******************************************************************************************
*	Chili DirectX Framework Version 16.10.01											  *
*	Game.h																				  *
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
#pragma once

#include "Graphics.h"
#include "ScreenTransformer.h"
#include "Cube.h"
#include "Square.h"
#include <vector>
#include "Timer.h"

/// GLOBAL FUNCTIONS ///
	static void ResolveCollision( Square& A, Square& B, Vec2 normal )
	{
		// Velocity vector between the centers of the colliding objects
		Vec2 relativeVelo = B.m_velocity - A.m_velocity;

		// Project this velocity onto the normal
//		float velAlongNorm = relativeVelo*A.m_normal;
		float velAlongNorm = relativeVelo*normal;

		// Do not resolve if velocities are separating
		bool separating = velAlongNorm > 0;
		if(separating)
		return;

		// Coefficient of resitution (min of two)
		float coefRest = std::min(A.m_restitution, B.m_restitution); 

		// Calculate impulse scalar
		float j = -( 1.0f + coefRest ) * velAlongNorm; // NOTE: 2 INFINITE MASSES will cause a crash!
		j /= (A.m_inverseMass + B.m_inverseMass);

		//Vec2 impulse = A.m_normal * j;
		Vec2 impulse = normal * j;

		// DISTRIBUTE THE IMPULSE AMONG BOTH OBJECTS ACCORDING TO THEIR RELATIVE MASSES
		A.m_velocity -= impulse * A.m_inverseMass;
		B.m_velocity += impulse * B.m_inverseMass;

		// NOTE: could also do it this (slower) way
		//float mass_sum = A.m_mass + B.m_mass;
		//float ratioA = A.m_mass / mass_sum;
		//float ratioB = B.m_mass / mass_sum;
		//A.m_velocity -= impulse * ratioA;
		//B.m_velocity += impulse * ratioB;
	}


class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
	void DoCollision();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	ScreenTransformer sTransformer;

	static constexpr int nObjects = 6;	
	Square m_squares[ nObjects ];

	static constexpr float dTheta = PI;

	Timer m_timer;
	/********************************/
};