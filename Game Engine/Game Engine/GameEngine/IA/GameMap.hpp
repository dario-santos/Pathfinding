/***********************************************************************
* \brief  BFS algorithm
*
* \author Dário Santos
* \date   May 2020
* **********************************************************************/
#pragma once

#include "IAlgorithm.hpp"

#include <GameEngine/Components/GameObject.hpp>

#include <vector>
#include <glm/glm.hpp>
using glm::ivec2;

using namespace std;

class GameMap
{
public:
  vector<vector<char>> gameMap;
  vector<vector<IPrimitive*>> gameMapPrim;
  vector<vector<ivec2>> visited;
  vector<ivec2> toVisit;

  IAlgorithm* algorithm = nullptr;

  ivec2 origin;
  ivec2 goal;

  GameMap(vector<vector<char>> gameMap, vector<vector<IPrimitive*>> gameMapPrim, IAlgorithm* algorithm, ivec2 origin, ivec2 goal);

  void CalculatePath();

  void DoStep();
};