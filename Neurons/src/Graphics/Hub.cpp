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
  createMap({});
  initMap({});
  auto consoleRet = async(&ConsoleHandler::run, &console);
  while(true){
    parseConsoleInstructions();
    runSimulations();
    if(neuronWindow.isOpen() || mapWindow.isOpen()){
      handleSdlEvents();
    }
  }
}

void Hub::parseConsoleInstructions(){
  while(console.instructions.size()>0){
    switch(console.instructions[0].inst){
      case CREATE_MAP:
        createMap(console.instructions[0].args);
        break;
      case INIT_MAP:
        initMap(console.instructions[0].args);
        break;
      case DELETE_MAP:
        deleteMap(console.instructions[0].args);
        break;
      case VIEW_MAP:
        viewMap(console.instructions[0].args);
        break;
      case RUN_SIMULATION_STEPS:
        runSimulationSteps(console.instructions[0].args);
        break;
      case RUN_SIMULATION_GENERATIONS:
        runSimulationGenerations(console.instructions[0].args);
        break;
      case COPY_MAP:
        copyMap(console.instructions[0].args);
        break;
      case OUTPUT_SIMULATION_STATUS:
        outputSimulationStatus(console.instructions[0].args);
        break;
      case OUTPUT_MAPS:
        outputMaps(console.instructions[0].args);
        break;
      case OUTPUT_MAPS_ONELINE:
        outputMapsOneline(console.instructions[0].args);
        break;
      case OUTPUT_ANIMALS:
        outputAnimal(console.instructions[0].args);
        break;
      case OUTPUT_NEURONS:
        outputNeuron(console.instructions[0].args);
        break;
      case MUTATE_NEURONS:
        mutateNeurons(console.instructions[0].args);
        break;
    }
    console.instructions.erase(console.instructions.begin());
  }
}

void Hub::handleSdlEvents(){
  if(mapWindow.isOpen()){
    mapWindow.prepareRender();
    mapWindow.render();
  }
  if(neuronWindow.isOpen()){
    neuronWindow.prepareRender();
    neuronWindow.render();
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
      if(e.window.windowID == mapWindow.windowId && mapWindow.isOpen())
        mapWindow.close();
      if(e.window.windowID == neuronWindow.windowId && neuronWindow.isOpen())
        neuronWindow.close();
      break;
    case SDL_WINDOWEVENT_SIZE_CHANGED:
      if(e.window.windowID == mapWindow.windowId && mapWindow.isOpen()){
        mapWindow.resizeWindow(e.window.data2, e.window.data1);
        mapWindow.prepareRender();
        mapWindow.render();
      }
      if(e.window.windowID == neuronWindow.windowId && neuronWindow.isOpen()){
        neuronWindow.resizeWindow(e.window.data2, e.window.data1);
        neuronWindow.prepareRender();
        neuronWindow.render();
      }
      break;
    case SDL_WINDOWEVENT_EXPOSED:
      if(e.window.windowID == mapWindow.windowId && mapWindow.isOpen())
        mapWindow.render();
      if(e.window.windowID == neuronWindow.windowId && neuronWindow.isOpen())
        neuronWindow.render();
      break;
    case SDL_WINDOWEVENT_FOCUS_GAINED:
      if(e.window.windowID == mapWindow.windowId && mapWindow.isOpen())
        mapWindow.keyFocus = true;
      if(e.window.windowID == neuronWindow.windowId && neuronWindow.isOpen())
        neuronWindow.keyFocus = true;
      break;
    case SDL_WINDOWEVENT_FOCUS_LOST:
      if(e.window.windowID == mapWindow.windowId && mapWindow.isOpen())
        mapWindow.keyFocus = false;
      if(e.window.windowID == neuronWindow.windowId && neuronWindow.isOpen())
        neuronWindow.keyFocus = false;
      break;
  }
}

void Hub::handleKeyEvents(SDL_Event& e){
  switch((int)e.key.keysym.sym)
  {
    case SDLK_q:
      if(mapWindow.isOpen() && mapWindow.keyFocus && mapWindow.mapRef->runManual<100)
        mapWindow.mapRef->runManual++;
      if(neuronWindow.isOpen() && neuronWindow.keyFocus)
        neuronWindow.changeAnimalType(false);
      break;
    case SDLK_w:
      if(mapWindow.isOpen() && mapWindow.keyFocus && mapWindow.mapRef->runManual<100)
        mapWindow.mapRef->runManual+=10;
      if(neuronWindow.isOpen() && neuronWindow.keyFocus)
        neuronWindow.changeAnimalType(true);
      break;
    case SDLK_a:
      if(neuronWindow.isOpen() && neuronWindow.keyFocus)
        neuronWindow.changeAnimal(false);
      break;
    case SDLK_s:
      if(neuronWindow.isOpen() && neuronWindow.keyFocus)
        neuronWindow.changeAnimal(true);
      break;
    case SDLK_p:
      if(mapWindow.isOpen() && mapWindow.keyFocus)
        mapWindow.mapRef->pause = !mapWindow.mapRef->pause;
      break;
  }
}

void Hub::runSimulations(){
  for(SimulationJob& job:_jobs){
    if(!job.m->pause || job.m->runManual>0){
      if(job.m->runManual>0)
        job.m->runManual--;
      bool generationDone = job.m->oneTick();
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

void Hub::createMap(vector<int> args){
  cout << "Creating map " << _maps.size() << "..." << endl;
  _maps.push_back(new Map);
  cout << "Map " << _maps.size()-1 << " created" << endl;
}

void Hub::initMap(vector<int> args){
  Map* m;
  int i=-1;
  if(args.size()>0)
    i=args[0];
  if(!(m=getMap(i)))
    return;
  cout << "Initializing map " << i << "..." << endl;
  m->init();
  cout << "Map " << i << " initialized" << endl;
}

void Hub::deleteMap(vector<int> args){
  Map* m;
  int i=-1;
  if(args.size()>0)
    i=args[0];
  if(!(m=getMap(i)))
    return;
  cout << "Deleting map " << i << "..." << endl;
  m->free();
  delete m;
  _maps.erase(_maps.begin()+i);
  cout << "Map " << i << " deleted" << endl;
}

void Hub::viewMap(vector<int> args){
  Map* m;
  int i=-1;
  if(args.size()>0)
    i=args[0];
  if(!(m=getMap(i)))
    return;
  if(!mapWindow.isOpen()){
    mapWindow.mapRef = m;
    mapWindow.open();
  }
  if(!neuronWindow.isOpen()){
    neuronWindow.mapRef = m;
    neuronWindow.animalType = HERBIVORE_NEURON;
    neuronWindow.animalIndex = 0;
    neuronWindow.open();
  }
  cout << "window for map " << i << " opened" << endl;
}

void Hub::runSimulationSteps(vector<int> args){
  Map* m;
  int i=-1;
  if(args.size()>0)
    i=args[0];
  if(!(m=getMap(i)))
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
  if(!(m=getMap(i)))
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
  if(!(m=getMap(i)))
    return;
  cout << "Copying map " << i << "..." << endl;
  m = m->deepCopy();
  _maps.push_back(m);
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

void Hub::outputMaps(vector<int> args){
  Map* m;
  console.mapId = _maps.size()-1;
  int level = OUTPUT_OVERVIEW;
  if(args.size()>0)
    console.mapId=args[0];
  if(args.size()>1)
    level=args[1];
  if(!(m=getMap(console.mapId))){
    console.mapId=-1;
    return;
  }
  if(level<0 || level > 3){
    cout << level << " is not a valid information level" << endl;
    console.mapId=-1;
    return;
  }
  m->output("", level);
}

void Hub::outputMapsOneline(vector<int> args){
  for(int i=0 ; i<(int)_maps.size(); i++){
    cout << "Map " << i << ": ";
    _maps[i]->output("", OUTPUT_ONELINE);
    cout << endl;
  }
}

void Hub::outputAnimal(vector<int> args){
  if(console.mapId>=(int)_maps.size() || console.mapId<0){
    cout << "Map " << console.mapId << " is no longer available, cannot output animal" << endl;
    console.mapId=-1;
    console.animalId=-1;
    return;
  }
  Map* m=_maps[console.mapId];
  Animal* a;
  vector<Animal*> animals;
  if(console.animalType == "carni")
    animals = m->carnivores();
  else if(console.animalType == "herbi")
    animals = m->herbivores();
  else if(console.animalType == "bestcarni")
    animals = m->bestCarnivores();
  else if(console.animalType == "bestherbi")
    animals = m->bestHerbivores();
  else{
    cout << "Invalid animal group type: " << console.animalType << endl;
    console.animalId=-1;
    return;
  }
  console.animalId = animals.size()-1;
  int level = OUTPUT_OVERVIEW;
  if(args.size()>0)
    console.animalId=args[0];
  if(args.size()>1)
    level=args[1];
  if(console.animalId<0 || console.animalId>=(int)animals.size()){
    cout << console.animalId << " is not a valid id for group: " << console.animalType << endl;
    console.animalId = -1;
    return;
  }
  a = animals[console.animalId];
  if(level<0 || level > 3){
    cout << level << " is not a valid information level" << endl;
    console.animalId = -1;
    return;
  }
  a->output("", level);
}

void Hub::outputNeuron(vector<int> args){
  if(console.mapId>=(int)_maps.size() || console.mapId<0){
    cout << "Map " << console.mapId << " is no longer available, cannot output neuron" << endl;
    console.mapId=-1;
    console.animalId=-1;
    console.neuronId=-1;
    return;
  }
  Map* m=_maps[console.mapId];
  Animal* a;
  vector<Animal*> animals;
  if(console.animalType == "carni")
    animals = m->carnivores();
  else if(console.animalType == "herbi")
    animals = m->herbivores();
  else if(console.animalType == "bestcarni")
    animals = m->bestCarnivores();
  else if(console.animalType == "bestherbi")
    animals = m->bestHerbivores();
  else{
    cout << "Invalid animal group type: " << console.animalType << " cannot output neuron" << endl;
    console.animalId=-1;
    console.neuronId=-1;
    return;
  }
  if(console.animalId<0 || console.animalId>=(int)animals.size()){
    cout << console.animalId << " is not a valid id for group: " << console.animalType << ". Cannot output neuron" << endl;
    console.animalId=-1;
    console.neuronId=-1;
    return;
  }
  a = animals[console.animalId];
  Neuron* n;
  vector<Neuron*> neurons;
  neurons = a->neurons();
  int neuronId = neurons.size()-1;
  int level = OUTPUT_OVERVIEW;
  if(args.size()>0)
    neuronId=args[0];
  if(args.size()>1)
    level=args[1];
  if(neuronId<0 || neuronId>=(int)neurons.size()){
    cout << neuronId << " is not a valid id" << endl;
    console.neuronId=-1;
    return;
  }
  n = neurons[neuronId];
  if(level<0 || level > 3){
    cout << level << " is not a valid information level" << endl;
    console.neuronId=-1;
    return;
  }
  n->output("", level);
}

void Hub::mutateNeurons(vector<int> args){
  if(console.mapId>=(int)_maps.size() || console.mapId<0){
    cout << "Map " << console.mapId << " is no longer available, cannot mutate neurons" << endl;
    console.mapId=-1;
    console.animalId=-1;
    console.neuronId=-1;
    return;
  }
  Map* m=_maps[console.mapId];
  Animal* a;
  vector<Animal*> animals;
  if(console.animalType == "carni")
    animals = m->carnivores();
  else if(console.animalType == "herbi")
    animals = m->herbivores();
  else if(console.animalType == "bestcarni")
    animals = m->bestCarnivores();
  else if(console.animalType == "bestherbi")
    animals = m->bestHerbivores();
  else{
    cout << "Invalid animal group type: " << console.animalType << " cannot mutate neurons" << endl;
    console.animalId=-1;
    console.neuronId=-1;
    return;
  }
  if(console.animalId<0 || console.animalId>=(int)animals.size()){
    cout << console.animalId << " is not a valid id for group: " << console.animalType << ". Cannot mutate neurons" << endl;
    console.animalId=-1;
    console.neuronId=-1;
    return;
  }
  a = animals[console.animalId];
  cout << "mutating neurons..." << endl;
  a->mutateNeurons();
  cout << "done" << endl;
}

Map* Hub::getMap(int& i){
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
