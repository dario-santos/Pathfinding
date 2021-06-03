#include "AStar.hpp"

AStar::AStar(ivec2 origin, ivec2 goal)
{
  this->origin = origin;
  this->goal = goal;
}

// Função da distância de Manhattan
//
//      f(p) = g(p) + h(p)
// 
//  f(p) : distance from the start point to point n
//  h(p) : estimated distance from point n to the goal point
//  g(p) : current estimated cost for point n
//
int AStar::Distance(ivec2 point)
{
  int f = glm::abs(point.x - origin.x) + glm::abs(point.y - origin.y);
  int g = glm::abs(point.x - goal.x) + glm::abs(point.y - goal.y);

  return f + g;
}

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

vector<ivec2> AStar::GetNeighbors(vector<vector<char>> gameMap, vector<vector<ivec2>> *visited, ivec2 pos, ivec2 goal, bool* containsGoal)
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

vector<ivec2> AStar::GetPath(vector<vector<char>> gameMap, ivec2 origin, ivec2 goal)
{

  int a = int(gameMap.size());
  int b = int(gameMap[0].size());

  vector<vector<ivec2>> visited(a, vector<ivec2>(b, ivec2(-1, -1)));

  // 2 - Initialize toVisit to origin
  vector<ivec2> toVisit = { origin };
  vector<ivec2> nextToVisit(0);

  visited[origin.x][origin.y] = origin;

  bool containsGoal = false;
  ivec2 point = toVisit[0];
  int min = Distance(point);
  int index = 0;

  while(!containsGoal)
  {

      for (int i = 0; i < toVisit.size(); i++)
      {

        // Get the point that minimizes g(n) + h(n)
        if (Distance(toVisit[i]) < min)
        {
          point = toVisit[i];
          min = Distance(toVisit[i]);
          index = i;
        }
      }
        if (point == goal) 
          break;

      // Remove searched element
      toVisit.erase(toVisit.begin() + index);

      auto tmp = GetNeighbors(gameMap, &visited, point, point, &containsGoal);
      toVisit.insert(toVisit.end(), tmp.begin(), tmp.end());
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

vector<ivec2> AStar::DoStep(vector<vector<char>> gameMap, vector<vector<ivec2>> *visited, vector<ivec2> toVisit)
{
  bool t = false;

  // Get the point that minimizes g(n) + h(n)
  ivec2 point = toVisit[0];
  int min = Distance(point);
  int index = 0;

  for(int i = 0 ; i < toVisit.size() ; i++)
  {
    if (Distance(toVisit[i]) < min)
    {
      point = toVisit[i];
      min = Distance(toVisit[i]);
      index = i;
    }
  }
  // Remove searched element
  toVisit.erase(toVisit.begin()+index);

  auto tmp = GetNeighbors(gameMap, visited, point, point, &t);
  toVisit.insert(toVisit.end(), tmp.begin(), tmp.end());
  
  return toVisit;
}