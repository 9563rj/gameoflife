#include "Cell.hxx"
#include <SDL2/SDL.h>
#include <iostream>
#include <random>
using namespace std;

const int tileSize = 1;
const int ticksFrame = 8;
const int nCols = 400;
const int nRows = 300;
const int winX = nCols*tileSize;
const int winY = nRows*tileSize;

vector<Cell*> cells;

random_device rd;
mt19937 eng(rd());

bool init(SDL_Window *&window, SDL_Renderer *&renderer)
{
  SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, winX, winY, 0);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

  bool gridSetupRunning = true;
  int cursorX = 0;
  int cursorY = 0;
  while(gridSetupRunning)
    {
      uniform_int_distribution<> lifePicker(0,1);
      Cell *cell = new Cell(cursorX*tileSize, cursorY*tileSize, lifePicker(eng), tileSize);
      cells.push_back(cell);
      cursorX++;
      if(cursorX == nCols)
	{
	  cursorX = 0;
	  cursorY++;
	}
      if(cursorY == nRows)
	{
	  gridSetupRunning = false;
	}
    }
  for(int row = 1; row < nRows-1; row++)
    {
      for(int col = 1; col < nCols-1; col++)
	{
	  int index = col+row*nCols;
	  cells[index]->setNeighbors(cells[index-nCols], cells[index+1], cells[index+nCols], cells[index-1], cells[index-(nCols+1)], cells[index-(nCols-1)], cells[index+(nCols+1)], cells[index+(nCols-1)]);
	}
    }
}
bool cycle()
{
  vector<Cell*>::iterator it;
  for(it=cells.begin();it!=cells.end();it++)
    {
      Cell *cell = *it;
      cell->checkNeighbors();
    }
}

bool inputHandler()
{
  SDL_PumpEvents();
  const Uint8* keys = SDL_GetKeyboardState(NULL);
  if(keys[SDL_SCANCODE_ESCAPE]) {return false;}
  else {return true;}
}

bool render(SDL_Renderer *renderer)
{
  SDL_RenderClear(renderer);
  vector<Cell*>::iterator it;
  for(it=cells.begin(); it!=cells.end(); it++)
    {
      Cell *cell = *it;
      cell->draw(renderer, tileSize);
    }
  SDL_RenderPresent(renderer);
}

bool cleanup(SDL_Window *window, SDL_Renderer *renderer)
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

int main()
{
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  
  init(window, renderer);
  render(renderer);

  bool running = true;
  while(running)
    {
      cycle();
      render(renderer);
      running = inputHandler();
    }
  cleanup(window, renderer);
}

