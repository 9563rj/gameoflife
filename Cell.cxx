#include "Cell.hxx"

Cell::Cell(int locX, int locY, bool tempLife, const int tileSize)
{
  neighborsSet = false;
  posX = locX;
  posY = locY;
  gridX = posX/tileSize;
  std::cout << "gridX for this tile is " << gridX << std::endl;
  gridY = posY/tileSize;
  std::cout << "gridY for this tile is " << gridY << std::endl;
  life = tempLife;
  std::cout << "this cell is " << life << std::endl;
}

void Cell::draw(SDL_Renderer *renderer, const int tileSize)
{
  if(life)
    {
      SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    }
  else
    {
      SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    }
  SDL_Rect drawDest = {posX, posY, posX+tileSize, posY+tileSize};
  SDL_RenderFillRect(renderer, &drawDest);
}

void Cell::setNeighbors(Cell* northT, Cell* eastT, Cell* southT, Cell* westT, Cell*northwestT, Cell* northeastT, Cell* southeastT, Cell* southwestT)
{
  neighborsSet = true;
  north = northT;
  std::cout << "Cell north of cell at " << gridX << " X and " << gridY << " Y is " << north->gridX << " and " << north->gridY << std::endl;
  east = eastT;
  south = southT;
  west = westT;
  northwest = northwestT;
  northeast = northeastT;
  southeast = southeastT;
  southwest = southwestT;
  neighbors.push_back(north);
  neighbors.push_back(east);
  neighbors.push_back(south);
  neighbors.push_back(west);
  neighbors.push_back(northwest);
  neighbors.push_back(northeast);
  neighbors.push_back(southeast);
  neighbors.push_back(southwest);
  std::cout << "size of neighbors for cell at " << gridX << " " << gridY << " is " << neighbors.size() << std::endl;
}

void Cell::checkNeighbors()
{
  if(neighborsSet)
    {
      std::vector<Cell*>::iterator it;
      int neighborCount = 0;
      for(it=neighbors.begin();it!=neighbors.end();it++)
	{
	  Cell *cell = *it;
	  if(cell->life)
	    {
	      neighborCount++;
	    }
	}
      std::cout << "neighborCount for cell at " << gridX << " and " << gridY << " is " << neighborCount << std::endl;
      if(neighborCount < 2 && life)
	{
	  life = false;
	}
      if(neighborCount > 3 && life)
	{
	  life = false;
	}
      if(neighborCount == 3 && life == false)
	{
	  life = true;
	}
    }
}
