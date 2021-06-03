/*********************************************************************
 * \file   IAlgorithm.hpp
 * \brief  Pathfinding algorithm interface
 *
 * \author Dário Santos
 * \date   May 2020
***********************************************************************/
#pragma once

#include <vector>
#include <glm/glm.hpp>
using glm::ivec2;

using namespace std;

class IAlgorithm
{
public:
  virtual vector<ivec2> GetPath(vector<vector<char>> gameMap, ivec2 origin, ivec2 goal) = 0;

  virtual vector<ivec2> DoStep(vector<vector<char>> gameMap, vector<vector<ivec2>> *visited, vector<ivec2> toVisit) = 0;
};