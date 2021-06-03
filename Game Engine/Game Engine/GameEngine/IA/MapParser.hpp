/*********************************************************************
 * \file   Parser.hpp
 * \brief  Parser class, parses the map file(s)
 *
 * \author Dário Santos
 * \date   May 2020
***********************************************************************/
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;

/**
 * MapParser
 */
class MapParser
{
private:
  MapParser() = default;
  ~MapParser() = default;

public:
  /**
   * ParseMapFile
   *
   * \param path The path of the file that will be parsed
   */
  static vector<vector<char>> ParseMapFile(char const* path)
  {
    vector<vector<char>> map(0);

    ifstream file;
    string line = "";
    
    file.open(path);

    if (!file.is_open())
      return map;
    
    // 1 - Ignore first four lines
    getline(file, line);
    getline(file, line);
    getline(file, line);
    getline(file, line);

    while (getline(file, line))
    {
      vector<char> line_buff(0);

      for(char c : line)
        if(c != '\n')
          line_buff.push_back(c);

      map.push_back(line_buff);
    }
    file.close();

    return map;
  }
};
