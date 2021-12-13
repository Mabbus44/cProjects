#include "Graphics/ConsoleHandler.h"

using namespace std;

ConsoleHandler::ConsoleHandler(){
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
  if( TTF_Init() == -1 )
    cout << "Warning: SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
}

ConsoleHandler::~ConsoleHandler(){
	SDL_Quit();
}

void ConsoleHandler::run(){
  string ans;
  string ans2;
  vector<string> argSplit;
  vector<int> args;
  createMap({});
  initMap({});
  while(ans2!="y"){
    while(ans!="q"){
      cout << "\n\n\n\n----------Maps----------" << endl;
      outputMapsOneline();
      cout << "\n----------Main menu----------" << endl;
      cout << "create \t\tceates new map" << endl;
      cout << "delete i\tdeletes map with id i" << endl;
      cout << "init i \t\tinitializes map with id i" << endl;
      cout << "viewmap i \tshows graphics for map i" << endl;
      cout << "runstep i j \truns map with id i for j simulation steps" << endl;
      cout << "rungen i j \truns map with id i for j simulation generations" << endl;
      cout << "rungencopy i j \truns copy of map with id i for j simulation generations" << endl;
      cout << "output i j \toutputs information about map i, j=(0-3, ONELINE, OVERVIEW, DEEP, ALL)" << endl;
      cout << "q \t\tquits any menu" << endl;
      cout << "run: ";
      getline(cin, ans);
      cout << endl;
      argSplit = argsTostr(ans);
      args.clear();
      if(argSplit.size()>0)
        args = argsToInt(argSplit[1]);
      if(argSplit[0] == "create") instructions.push_back(Instruction(CREATE_MAP, args));
      if(argSplit[0] == "delete") instructions.push_back(Instruction(DELETE_MAP, args));
      if(argSplit[0] == "init") instructions.push_back(Instruction(INIT_MAP, args));
      if(argSplit[0] == "viewmap") instructions.push_back(Instruction(VIEW_MAP, args));
      if(argSplit[0] == "runstep") instructions.push_back(Instruction(RUN_SIMULATION_STEPS, args));
      if(argSplit[0] == "rungen") instructions.push_back(Instruction(RUN_SIMULATION_GENERATIONS, args));
      if(argSplit[0] == "rungencopy") instructions.push_back(Instruction(CREATE_MAP, args));
      if(argSplit[0] == "output") outputMaps(argsToInt(argSplit[1]));
      cout << "viewmap done" << endl;
    }
    cout << "Are you sure? (y/n)";
    getline(cin, ans2);
    ans="";
  }
}

void ConsoleHandler::createMap(vector<int> args){
  cout << "Creating map " << _maps.size() << "..." << endl;
  _maps.push_back(new Map);
  cout << "Map " << _maps.size()-1 << " created" << endl;
}

void ConsoleHandler::deleteMap(vector<int> args){
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

void ConsoleHandler::initMap(vector<int> args){
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

void ConsoleHandler::runSimulationSteps(vector<int> args){
  cout << "NOT YET IMPLEMENTED" << endl;
}

void ConsoleHandler::viewMap(vector<int> args){
/*  Map* m;
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
  while(true){}
*/}

void ConsoleHandler::runSimulationGenerations(vector<int> args, bool copyMap){
  Map* m;
  int i=-1;
  if(args.size()>0)
    i=args[0];
  if(!(m=getMap(i)))
    return;
  int steps = 1;
  if(args.size()>1 && args[1]>0)
    steps=args[1];
  if(copyMap){
    cout << "Copying map " << i << "..." << endl;
    m = m->deepCopy();
    _maps.push_back(m);
    i = _maps.size()-1;
    cout << "Done" << endl;
  }
  cout << "Running simulation map " << i << " for " << steps << " generation(s)..." << endl;
  runSimulation(m, steps);
  cout << "Simulation complete" << endl;
}

Map* ConsoleHandler::getMap(int& i){
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

vector<int> ConsoleHandler::argsToInt(string args){
  vector<int> ret;
  int pos;
  while ((pos = args.find(" ")) != (int)string::npos) {
    try{
      ret.push_back(stoi(args.substr(0, pos)));
    }catch(...){
      ret.push_back(0);
    }
    args.erase(0, pos + 1);
  }
  if(args.length()>0){
    try{
      ret.push_back(stoi(args));
    }catch(...){
      ret.push_back(0);
    }
  }
  return ret;
}

vector<string> ConsoleHandler::argsTostr(string args){
  vector<string> ret;
  int pos;
  if((pos = args.find(" ")) == (int)string::npos) {
    ret.push_back(args);
    ret.push_back("");
  }else{
    ret.push_back(args.substr(0, pos));
    ret.push_back(args.substr(pos+1, args.length()-pos-1));
  }
  return ret;
}

void ConsoleHandler::runSimulation(Map* m, int steps){
/*  m->runningLogic = true;
  m->allowDrawMap = true;
  m->allowDrawNeurons = true;
  while(steps>0){
    cout << "Generations left: " << steps << endl;
    bool done=false;
    while(!done){
      while((m->mapDrawnBy == &mapWindow && m->allowDrawMap==true) || (m->neuronsDrawnBy == &neuronWindow && m->allowDrawNeurons==true)){}
      done = !m->oneTick();
      m->allowDrawMap = true;
      m->allowDrawNeurons = true;
    }
    steps--;
  }
  m->runningLogic = false;
*/}

void ConsoleHandler::outputMapsOneline(){
  for(int i=0 ; i<(int)_maps.size(); i++){
    cout << "Map " << i << ": ";
    _maps[i]->output("", OUTPUT_ONELINE);
    cout << endl;
  }
}

void ConsoleHandler::outputMaps(vector<int> args){
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
  string ans;
  vector<string> argSplit;
  m->output("", level);
  while(ans!="q"){
    cout << "\n----------Map menu----------(map " << mapId << ")" << endl;
    cout << "carni i j \toutputs information about carnivore i, j=(0-3, ONELINE, OVERVIEW, DEEP, ALL)" << endl;
    cout << "herbi i j \toutputs information about herbivore i, j=(0-3, ONELINE, OVERVIEW, DEEP, ALL)" << endl;
    cout << "bestcarni i j \toutputs information about best carnivore i, j=(0-3, ONELINE, OVERVIEW, DEEP, ALL)" << endl;
    cout << "bestherbi i j \toutputs information about best herbivore i, j=(0-3, ONELINE, OVERVIEW, DEEP, ALL)" << endl;
    cout << "run: ";
    getline(cin, ans);
    cout << endl;
    argSplit = argsTostr(ans);
    if(argSplit[0] == "carni" ||
      argSplit[0] == "herbi" ||
      argSplit[0] == "bestcarni" ||
      argSplit[0] == "bestherbi")outputAnimal(m, argSplit[0], argsToInt(argSplit[1]));
  }
}

void ConsoleHandler::outputAnimal(Map* m, string type, vector<int> args){
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
  string ans;
  vector<string> argSplit;
  a->output("", level);
  while(ans!="q"){
    cout << "\n----------Animal menu----------(" << type << " " << animalId << ")" << endl;
    cout << "neuron i j \toutputs information about neuron i, j=(0-3, ONELINE, OVERVIEW, DEEP, ALL)" << endl;
    cout << "mutate \t\tmutates animals neurons" << endl;
    cout << "run: ";
    getline(cin, ans);
    cout << endl;
    argSplit = argsTostr(ans);
    if(argSplit[0] == "neuron")outputNeuron(a, argsToInt(argSplit[1]));
    if(argSplit[0] == "mutate"){
      cout << "mutating neurons..." << endl;
      a->mutateNeurons();
      cout << "done" << endl;
      a->output("", level);
    }
  }
}

void ConsoleHandler::outputNeuron(Animal* a, vector<int> args){
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
    return;
  }
  n = neurons[neuronId];
  if(level<0 || level > 3){
    cout << level << " is not a valid information level" << endl;
    return;
  }
  string ans;
  vector<string> argSplit;
  n->output("", level);
  while(ans!="q"){
    cout << "\n----------Neuron menu----------(neuron " << neuronId << ")" << endl;
    cout << "(empty menu, write q to quit)" << endl;
    cout << "run: ";
    getline(cin, ans);
    cout << endl;
    argSplit = argsTostr(ans);
  }
}
