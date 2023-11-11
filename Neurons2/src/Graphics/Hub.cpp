#include "Graphics/Hub.h"

Hub::Hub()
{
  //ctor
}

Hub::~Hub()
{
  //dtor
}

void Hub::run(){
  createMap({"mapSettings.json"});
  initMap({});
  auto _consoleRet = async(&ConsoleHandler::run, &_console);
  while(true){
    parseConsoleInstructions();
    runSimulations();
    if(_neuronWindow.isOpen() || _mapWindow.isOpen()){
      handleSdlEvents();
    }
  }
}

void Hub::parseConsoleInstructions(){
  int debug = 0;
  while(_console.instructions.size()>0){
    cout << "instructionlist size " << _console.instructions.size() << endl;
    switch(_console.instructions[0].inst){
      case CREATE_MAP:
        createMap(_console.instructions[0].strArgs);
        break;
      case INIT_MAP:
        initMap(_console.instructions[0].args);
        break;
      case DELETE_MAP:
        deleteMap(_console.instructions[0].args);
        break;
      case VIEW_MAP:
        viewMap(_console.instructions[0].args);
        break;
      case RUN_SIMULATION_STEPS:
        runSimulationSteps(_console.instructions[0].args);
        break;
      case RUN_SIMULATION_GENERATIONS:
        runSimulationGenerations(_console.instructions[0].args);
        break;
      case COPY_MAP:
        copyMap(_console.instructions[0].args);
        break;
      case OUTPUT_SIMULATION_STATUS:
        outputSimulationStatus(_console.instructions[0].args);
        break;
      case OUTPUT_MAPS_ONELINE:
        outputMapsOneline(_console.instructions[0].args);
        break;
    }
    _console.instructions.erase(_console.instructions.begin());
    cout << "instructionlist size " << _console.instructions.size() << endl;
  }
}

void Hub::handleSdlEvents(){
  if(_mapWindow.isOpen()){
    _mapWindow.prepareRender();
    _mapWindow.render();
  }
  if(_neuronWindow.isOpen()){
    _neuronWindow.prepareRender();
    _neuronWindow.render();
  }
  SDL_Event e;
  while(SDL_PollEvent(&e) != 0){
    switch(e.type){
      case SDL_WINDOWEVENT:
        handleWindowEvents(e);
        break;
      case SDL_KEYDOWN:
        handleKeyEvents(e);
        break;
    }
  }
}

void Hub::handleWindowEvents(SDL_Event& e){
  switch((int)e.window.event)
  {
    case SDL_WINDOWEVENT_CLOSE:
      if(e.window.windowID == _mapWindow.windowId && _mapWindow.isOpen())
        _mapWindow.close();
      if(e.window.windowID == _neuronWindow.windowId && _neuronWindow.isOpen())
        _neuronWindow.close();
      break;
    case SDL_WINDOWEVENT_SIZE_CHANGED:
      if(e.window.windowID == _mapWindow.windowId && _mapWindow.isOpen()){
        cout << "Size changed" << endl;
        _mapWindow.resizeWindow(e.window.data2, e.window.data1);
        _mapWindow.prepareRender();
        _mapWindow.render();
      }
      if(e.window.windowID == _neuronWindow.windowId && _neuronWindow.isOpen()){
        _neuronWindow.resizeWindow(e.window.data2, e.window.data1);
        _neuronWindow.prepareRender();
        _neuronWindow.render();
      }
      break;
    case SDL_WINDOWEVENT_EXPOSED:
      if(e.window.windowID == _mapWindow.windowId && _mapWindow.isOpen())
        _mapWindow.render();
      if(e.window.windowID == _neuronWindow.windowId && _neuronWindow.isOpen())
        _neuronWindow.render();
      break;
    case SDL_WINDOWEVENT_FOCUS_GAINED:
      if(e.window.windowID == _mapWindow.windowId && _mapWindow.isOpen())
        _mapWindow.keyFocus = true;
      if(e.window.windowID == _neuronWindow.windowId && _neuronWindow.isOpen())
        _neuronWindow.keyFocus = true;
      break;
    case SDL_WINDOWEVENT_FOCUS_LOST:
      if(e.window.windowID == _mapWindow.windowId && _mapWindow.isOpen())
        _mapWindow.keyFocus = false;
      if(e.window.windowID == _neuronWindow.windowId && _neuronWindow.isOpen())
        _neuronWindow.keyFocus = false;
      break;
  }
}

void Hub::handleKeyEvents(SDL_Event& e){
  switch((int)e.key.keysym.sym)
  {
    //TODO Handle hotkeys for mapwindow and neuronwindow
    case SDLK_q:
      break;
    case SDLK_w:
      break;
    case SDLK_a:
      break;
    case SDLK_s:
      break;
    case SDLK_z:
      break;
    case SDLK_p:
      break;
    case SDLK_LEFT:
      break;
    case SDLK_RIGHT:
      break;
    case SDLK_UP:
      break;
    case SDLK_DOWN:
      break;
  }
}

void Hub::runSimulations(){
  for(SimulationJob& job:_jobs){
    cout << "run simulation" << endl;
    if(!job.m->pause || job.m->runManual>0){
      if(job.m->runManual>0)
        job.m->runManual--;
      bool generationDone = job.m->tick();
      if(job.simulationType == SIMULATION_GENERATION && generationDone)
        job.stepsLeft--;
      if(job.simulationType == SIMULATION_STEP)
        job.stepsLeft--;
    }
  }
  for(int i=_jobs.size()-1; i>=0; i--){
    if(_jobs[i].stepsLeft<=0)
      _jobs.erase(_jobs.begin()+i);
  }
}

void Hub::createMap(vector<string> args){
  cout << "Creating map " << _maps.size() << "..." << endl;
  if(args.size() < 1){
    cout << "Error: No filename provided" << endl;
    return;
  }
  Map* m = new Map();
  if(m->loadMapSettings(args[0])){
    _maps.push_back(m);
    cout << "Map " << _maps.size()-1 << " created" << endl;
  }else{
    delete m;
    cout << "Error: Could not create map" << endl;
  }
}

void Hub::initMap(vector<int> args){
  Map* m;
  int i=-1;
  if(args.size()>0)
    i=args[0];
  if(!(m=map(i)))
    return;
  cout << "Initializing map " << i << "..." << endl;
  if(m->resetMap())
    cout << "Map " << i << " initialized" << endl;
}

void Hub::deleteMap(vector<int> args){
  Map* m;
  int i=-1;
  if(args.size()>0)
    i=args[0];
  if(!(m=map(i)))
    return;
  cout << "Deleting map " << i << "..." << endl;
  delete m;
  _maps.erase(_maps.begin()+i);
  cout << "Map " << i << " deleted" << endl;
}

void Hub::viewMap(vector<int> args){
  Map* m;
  int i=-1;
  if(args.size()>0)
    i=args[0];
  if(!(m=map(i)))
    return;
  if(!_mapWindow.isOpen()){
    _mapWindow.mapRef = m;
    _mapWindow.open();
  }
  if(!_neuronWindow.isOpen()){
    //TODO Set mapref and what to show of neuron window
    //_neuronWindow.open();
  }
  cout << "window for map " << i << " opened" << endl;
}

void Hub::runSimulationSteps(vector<int> args){
  Map* m;
  int i=-1;
  if(args.size()>0)
    i=args[0];
  if(!(m=map(i)))
    return;
  int steps = 1;
  if(args.size()>1 && args[1]>0)
    steps=args[1];
  cout << "Starting simulation on map " << i << " for " << steps << " step(s)..." << endl;
  _jobs.push_back(SimulationJob(SIMULATION_STEP, steps, m));
}

void Hub::runSimulationGenerations(vector<int> args){
  Map* m;
  int i=-1;
  if(args.size()>0)
    i=args[0];
  if(!(m=map(i)))
    return;
  int steps = 1;
  if(args.size()>1 && args[1]>0)
    steps=args[1];
  cout << "Starting simulation on map " << i << " for " << steps << " generation(s)..." << endl;
  _jobs.push_back(SimulationJob(SIMULATION_GENERATION, steps, m));
}

void Hub::copyMap(vector<int> args){
  Map* m;
  int i=-1;
  if(args.size()>0)
    i=args[0];
  if(!(m=map(i)))
    return;
  cout << "Copying map " << i << "..." << endl;
  //TODO Copy map
  cout << "Done" << endl;
}

void Hub::outputSimulationStatus(vector<int> args){
  if(_jobs.size()==0)
    cout << "No simulations running" << endl;
  for(SimulationJob& job: _jobs){
    cout << "Simulation have " << job.stepsLeft;
    if(job.simulationType == SIMULATION_GENERATION)
      cout << " generation";
    if(job.simulationType == SIMULATION_STEP)
      cout << " step";
    if(job.stepsLeft>1)
      cout << "s";
    cout << " left" << endl;
  }
}

Map* Hub::map(int i){
  if(_maps.size() == 0){
    cout << "No maps available " << endl;
    return NULL;
  }
  if(i<-1 || i>=(int)_maps.size()){
    cout << "Map " << i << " does not exist" << endl;
    return NULL;
  }
  if(i==-1)
    i=_maps.size()-1;
  return _maps[i];
}

void Hub::outputMapsOneline(vector<int> args){
  for(int i=0 ; i<(int)_maps.size(); i++){
    cout << "Map " << i << ": ";
    _maps[i]->output("", OUTPUT_ONELINE);
    cout << endl;
  }
}
