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
  async(&ConsoleHandler::run, &console);
  while(true){

  }
}

void Hub::parseConsoleInstruction(){
  if(console.instructions.size()>0){
    switch(console.instructions[0].inst){
      case CREATE_MAP:
        createMap();
        break;
      case INIT_MAP:
        initMap();
        break;
      case DELETE_MAP:
        deleteMap();
        break;
      case VIEW_MAP:
        viewMap();
        break;
      case RUN_SIMULATION_STEPS:
        runSimulationSteps();
        break;
      case RUN_SIMULATION_GENERATIONS:
        runSimulationGenerations();
        break;
      case COPY_MAP:
        copyMap();
        break;
      case OUTPUT_MAPS:
        outputMaps();
        break;
      case OUTPUT_ANIMALS:
        outputAnimal();
        break;
      case OUTPUT_NEURONS:
        outputNeuron();
        break;
    }
    console.instructions.erase(console.instructions.begin());
  }
}

void Hub::createMap(){
  cout << "Creating map " << _maps.size() << "..." << endl;
  _maps.push_back(new Map);
  cout << "Map " << _maps.size()-1 << " created" << endl;
}

void Hub::initMap(){
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

void Hub::deleteMap(){
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

void Hub::viewMap(){
  Map* m;
  int i=-1;
  if(args.size()>0)
    i=args[0];
  if(!(m=getMap(i)))
    return;
  if(mapWindow.isOpen()){
    cout << "mapwindow already open" << endl;
    return;
  }
  mapWindowRet = async(&MapWindow::drawMap, &mapWindow, m);
  neuronWindowRet = async(&NeuronsWindow::drawNeuron, &neuronWindow, m);
  cout << "window for map " << i << " opened" << endl;
}

void Hub::runSimulationSteps(){
  cout << "NOT YET IMPLEMENTED" << endl;
}

void Hub::runSimulationGenerations(){
  Map* m;
  int i=-1;
  if(args.size()>0)
    i=args[0];
  if(!(m=getMap(i)))
    return;
  int steps = 1;
  if(args.size()>1 && args[1]>0)
    steps=args[1];
  cout << "Running simulation map " << i << " for " << steps << " generation(s)..." << endl;
  runSimulation(m, steps);
  cout << "Simulation complete" << endl;
}

void Hub::copyMap(){
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

void Hub::outputMaps(){
  Map* m;
  int mapId = _maps.size()-1;
  int level = OUTPUT_OVERVIEW;
  if(args.size()>0)
    mapId=args[0];
  if(args.size()>1)
    level=args[1];
  if(!(m=getMap(mapId)))
    return;
  if(level<0 || level > 3){
    cout << level << " is not a valid information level" << endl;
    return;
  }
  m->output("", level);
}

void Hub::outputAnimal(){

  Animal* a;
  vector<Animal*> animals;
  if(type == "carni")
    animals = m->carnivores();
  else if(type == "herbi")
    animals = m->herbivores();
  else if(type == "bestcarni")
    animals = m->bestCarnivores();
  else if(type == "bestherbi")
    animals = m->bestHerbivores();
  else{
    cout << "Invalid animal group type: " << type << endl;
    return;
  }
  int animalId = animals.size()-1;
  int level = OUTPUT_OVERVIEW;
  if(args.size()>0)
    animalId=args[0];
  if(args.size()>1)
    level=args[1];
  if(animalId<0 || animalId>=(int)animals.size()){
    cout << animalId << " is not a valid id for group: " << type << endl;
    return;
  }
  a = animals[animalId];
  if(level<0 || level > 3){
    cout << level << " is not a valid information level" << endl;
    return;
  }
  a->output("", level);
}

void Hub::outputNeuron(){
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
