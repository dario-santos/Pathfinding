#include "GameMap.hpp"
#include <algorithm>


GameMap::GameMap(vector<vector<char>> gameMap, vector<vector<IPrimitive*>> gameMapPrim, IAlgorithm* algorithm, ivec2 origin, ivec2 goal)
{
  this->gameMap = gameMap;

  this->origin = origin;
  this->goal = goal;

  this->algorithm = algorithm;
  this->gameMapPrim = gameMapPrim;

  gameMapPrim[goal.x][goal.y]->UpdateColor(vec3(0, 255, 0));
  gameMapPrim[origin.x][origin.y]->UpdateColor(vec3(0, 0, 255));


  int a = int(gameMap.size());
  int b = int(gameMap[0].size());

  
  this->visited = vector<vector<ivec2>>(a, vector<ivec2>(b, ivec2(-1, -1)));

  // 2 - Initialize toVisit to origin
  this->toVisit = { origin };
  
  this->visited[origin.x][origin.y] = origin;

}

void GameMap::CalculatePath()
{
  for(auto v : this->algorithm->GetPath(gameMap, origin, goal))
    gameMapPrim[v.x][v.y]->UpdateColor(vec3(52, 152, 219));
}

void GameMap::DoStep()
{
  if(visited[goal.x][goal.y] != ivec2(-1, -1))
    return;

  auto old = toVisit;


  toVisit = algorithm->DoStep(gameMap, &visited, toVisit);
  
  for(auto p : toVisit)
    gameMapPrim[p.x][p.y]->UpdateColor(vec3(243, 156, 18));

  for(auto p : old)
    if(std::count(toVisit.begin(), toVisit.end(), p) == 0)
      gameMapPrim[p.x][p.y]->UpdateColor(vec3(211, 84, 0));

  // 2 - Draw path if goal has been discovere
  if (visited[goal.x][goal.y] == ivec2(-1, -1))
    return;

  ivec2 pos = goal;

  while (pos != origin)
  {
    gameMapPrim[pos.x][pos.y]->UpdateColor(vec3(52, 152, 219));
    
    // 2.1 - Get next pos
    pos = visited[pos.x][pos.y];
  }
}