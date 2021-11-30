#include <SDL.h>
#include <iostream>
#include "Includes.h"
#include "Graphics/SDLWindow.h"
#include <time.h>
#include <stdlib.h>
#include "Map.h"
#include <thread>
#include <future>
#include "Graphics/ConsoleHandler.h"

using namespace std;

int main( int argc, char* args2[] )
{
  srand (time(NULL));
  ConsoleHandler c;
  c.run();
  return 0;
}

