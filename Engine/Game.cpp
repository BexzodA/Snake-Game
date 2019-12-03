/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
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
#include "SpriteCodex.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	board(gfx),
	snek({20,15}),
	rng(rd()),
	goal(rng,board,snek)
{

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
	if (!gameIsOver) {
		if (wnd.kbd.KeyIsPressed(VK_UP) && delta_loc.y != 1) {
			delta_loc = { 0,-1 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_DOWN) && delta_loc.y != -1) {
			delta_loc = { 0,1 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_RIGHT) && delta_loc.x != -1) {
			delta_loc = { 1,0 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_LEFT) && delta_loc.x != 1) {
			delta_loc = { -1,0 };
		}

		snekMoveCounter++;

		if (snekMoveCounter == snekMoveRate) {
			if (wnd.kbd.KeyIsPressed(VK_UP) && delta_loc.y != 1) {
				delta_loc = { 0,-1 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_DOWN) && delta_loc.y != -1) {
				delta_loc = { 0,1 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_RIGHT) && delta_loc.x != -1) {
				delta_loc = { 1,0 };
			}
			else if (wnd.kbd.KeyIsPressed(VK_LEFT) && delta_loc.x != 1) {
				delta_loc = { -1,0 };
			}
			snekMoveCounter = 0;
			const Location next = snek.GetNextHeadLocation(delta_loc);

			const bool eaten = next == goal.GetLocation();

			for (int i = 0; i < usedObstacles; i++) {
				if (next == obs[i].GetLocation()) {
					gameIsOver = true;
					return;
				}
			}

			if (!board.IsInsideGrid(next) || snek.IsInTileExceptEnd(next)) {
				gameIsOver = true;
			}
			else {
				if (eaten) {

					snek.Grow(rng);

					goal.Respawn(rng, board, snek);

					if (usedObstacles < maxObstacles) {
						obs[usedObstacles] = Obstacle(rng, board, snek, goal);
						usedObstacles++;
					}

					if(snekMoveRate >= maxSpeed)
						snekMoveRate -= 2;
				}

				snek.MoveBy(delta_loc);
			}
		}
	}
}

void Game::ComposeFrame()
{	
	for (int i = 0; i < usedObstacles; i++) {
		obs[i].Draw(board);
	}
	gfx.DrawRect(17, 17, Graphics::ScreenWidth - 20, 20, Color(255, 255, 255));
	gfx.DrawRect(Graphics::ScreenWidth - 17, 17, Graphics::ScreenWidth - 20, Graphics::ScreenHeight - 20, Color(255, 255, 255));
	gfx.DrawRect(17, 17, 20, Graphics::ScreenHeight - 20, Color(255, 255, 255));
	gfx.DrawRect(17, Graphics::ScreenHeight - 17, Graphics::ScreenWidth - 20, Graphics::ScreenHeight - 20, Color(255, 255, 255));
	goal.Draw(board);
	snek.Draw(board);
	if (gameIsOver) {
		SpriteCodex::DrawGameOver(200,200,gfx);
	}
}
