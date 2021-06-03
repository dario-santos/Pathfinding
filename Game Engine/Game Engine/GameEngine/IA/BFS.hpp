/*********************************************************************
 * \file   BFS.hpp
 * \brief  BFS algorithm
 *
 * \author Dário Santos
 * \date   May 2020
***********************************************************************/
#pragma once

#include "IAlgorithm.hpp"

#include <vector>
#include <glm/glm.hpp>
using glm::ivec2;

using namespace std;

class BFS: public IAlgorithm
{
public:
  BFS();

  vector<ivec2> GetNeighbors(vector<vector<char>> gameMap, vector<vector<ivec2>> *visited, ivec2 pos, ivec2 goal, bool* containsGoal);

  vector<ivec2> GetPath(vector<vector<char>> gameMap, ivec2 origin, ivec2 goal);

  vector<ivec2> DoStep(vector<vector<char>> gameMap, vector<vector<ivec2>> *visited, vector<ivec2> toVisit);
};