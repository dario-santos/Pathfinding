#pragma once

#include "GameEngine/Components/Script.hpp"

#include "GameEngine/Input/Input.hpp"

#include <GameEngine/IA/GameMap.hpp>

/*
 * Class: MapManager
 * --------------------------------
 *   Interface: Script
 */
class MapManager : public Script
{
private:
  // Game Map
  GameMap* gameMap;
  bool pressed = false;
 
public:
  /*
  * Function: BallManager
  * --------------------------------
  *  BallManager constructor
  *
  *  transform: The transform of the gameObject;
  *  gameObject: The ball gameObject.
  */
  MapManager(GameMap* gameMap);

  /*
  * Function: Update
  * --------------------------------
  *  The Update event
  */
  void Update() override;
};