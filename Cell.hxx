#ifndef CELL_HXX
#define CELL_HXX

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

class Cell
{
 public:
  bool neighborsSet;
  int gridX;
  int posX;
  int gridY;
  int posY;
  bool life;
  Cell* north;
  Cell* east;
  Cell* south;
  Cell* west;
  Cell* northwest;
  Cell* northeast;
  Cell* southeast;
  Cell* southwest;
  std::vector<Cell*> neighbors;
  Cell(int locX, int locY, bool tempLife, const int tileSize);

  void draw(SDL_Renderer *renderer, const int tileSize);
  void setNeighbors(Cell* north, Cell* east, Cell* south, Cell* west, Cell*northwest, Cell* northeast, Cell* southeast, Cell* southwest);
  void checkNeighbors();
};

#endif // CELL_HXX
