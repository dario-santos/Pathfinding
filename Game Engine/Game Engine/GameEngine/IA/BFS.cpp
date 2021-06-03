#include "BFS.hpp"

BFS::BFS(){}

// Possible Neighbors
//         y   
//   +---+---+---+
//   + - | 1 | - |
//   +---+---+---+   
// x + 2 |   | 3 |
//   +---+---+---+
//   | - | 4 | - |
//   +---+---+---+
//

vector<ivec2> BFS::GetNeighbors(vector<vector<char>> gameMap, vector<vector<ivec2>> *visited, ivec2 pos, ivec2 goal, bool* containsGoal)
{
  int height = int(gameMap.size());
  int width = int(gameMap[0].size());

  int x = pos.x;
  int y = pos.y;

  vector<ivec2> neighbors = {                     ivec2(x - 1,y),
                              ivec2(x,  y - 1),                   ivec2(x,  y + 1),
                                                  ivec2(x + 1,y)};

  vector<ivec2> nextToVisit(0);

  *containsGoal = false;

  for (auto v : neighbors)
  {
    // 1 - Is the position valid?
    if (v.x < 0 || v.x >= height || v.y < 0 || v.y >= width)
      continue;

    // 2 - Has this position been visited?
    if ((*visited)[v.x][v.y] != ivec2(-1, -1))
      continue;

    // 3 - Is tile valid?
    if (gameMap[v.x][v.y] != '.')
      continue;

    if (goal == v)
      *containsGoal = true;

    // 3 - If everything is okay then add to visit and mark as visited
    nextToVisit.push_back(v);
    (*visited)[v.x][v.y] = pos;
  }

  return nextToVisit;
}


vector<ivec2> BFS::GetPath(vector<vector<char>> gameMap, ivec2 origin, ivec2 goal)
{

  int a = int(gameMap.size());
  int b = int(gameMap[0].size());

  vector<vector<ivec2>> visited(a, vector<ivec2>(b, ivec2(-1, -1)));

  // 2 - Initialize toVisit to origin
  vector<ivec2> toVisit = { origin };
  vector<ivec2> nextToVisit(0);

  visited[origin.x][origin.y] = origin;

  bool containsGoal = false;

  while(!containsGoal)
  {
    for (ivec2 pos : toVisit)
    {
      // 3.1 - Is this the goal?
      if (pos == goal) 
        break;

      // 3.2 - Add neighbors to nextToVisit
      auto tmp = GetNeighbors(gameMap, &visited, pos, goal, &containsGoal);
      nextToVisit.insert(nextToVisit.end(), tmp.begin(), tmp.end());
    }
    toVisit = nextToVisit;
  }

  // 4 - Construct path
  vector<ivec2> path = { goal };
  
  while (path.back() != origin)
  {
    ivec2 pos = path.back();

    // 4.1 - Get next pos
    path.push_back(visited[pos.x][pos.y]);
  }

  return path;
}



vector<ivec2> BFS::DoStep(vector<vector<char>> gameMap, vector<vector<ivec2>> *visited, vector<ivec2> toVisit)
{
  vector<ivec2> nextToVisit(0);
  bool t = false;

  for (ivec2 pos : toVisit)
  {
    // Add neighbors to nextToVisit
    auto tmp = GetNeighbors(gameMap, visited, pos, pos, &t);
    nextToVisit.insert(nextToVisit.end(), tmp.begin(), tmp.end());
  }
  return nextToVisit;
}