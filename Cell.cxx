#include "Cell.hxx"

Cell::Cell(int locX, int locY, bool tempLife, const int tileSize)
{
  neighborsSet = false;
  posX = locX;
  posY = locY;
  gridX = posX/tileSize;
  gridY = posY/tileSize;
  life = tempLife;
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
