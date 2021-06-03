#include "MapManager.hpp"

MapManager::MapManager(GameMap* gameMap)
{
  this->gameMap = gameMap;
}

void MapManager::Update()
{
  if (Input::GetKeyDown(KeyCode::RightArrow) && !pressed)
  {
    pressed = true;
    gameMap->DoStep();
  }

  if (Input::GetKeyUp(KeyCode::RightArrow))
    pressed = false;

  if (Input::GetKeyDown(KeyCode::D))
    gameMap->CalculatePath();
}
