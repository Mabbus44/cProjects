#include <SDL.h>
#include <iostream>
#include "Includes.h"
#include "Graphics/SDLWindow.h"
#include <time.h>
#include <stdlib.h>
#include "Map.h"
#include "Graphics/ConsoleHandler.h"
#include "Graphics/Hub.h"

using namespace std;

int main( int argc, char* args2[] )
{
  srand (time(NULL));
  Hub h;
  h.run();
  return 0;
}

