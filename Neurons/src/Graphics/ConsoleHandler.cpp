#include "Graphics/ConsoleHandler.h"
#include <thread>
#include <future>

using namespace std;

ConsoleHandler::ConsoleHandler(){
}

ConsoleHandler::~ConsoleHandler(){
}

void ConsoleHandler::run(){
  string ans;
  string ans2;
  vector<string> argSplit;
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
      cout << "viewmap i \t\tshows graphics for map i" << endl;
      cout << "runstep i j \truns map with id i for j simulation steps" << endl;
      cout << "rungen i j \truns map with id i for j simulation generations" << endl;
      cout << "rungencopy i j \truns copy of map with id i for j simulation generations" << endl;
      cout << "output i j \toutputs information about map i, j=(0-3, ONELINE, OVERVIEW, DEEP, ALL)" << endl;
      cout << "q \t\tquits any menu" << endl;
      cout << "run: ";
      getline(cin, ans);
      cout << endl;
      argSplit = argsTostr(ans);
      if(argSplit[0] == "create") createMap(argsToInt(argSplit[1]));
      if(argSplit[0] == "delete") deleteMap(argsToInt(argSplit[1]));
      if(argSplit[0] == "init") initMap(argsToInt(argSplit[1]));
      if(argSplit[0] == "viewmap") viewMap(argsToInt(argSplit[1]));
      if(argSplit[0] == "runstep") runSimulationSteps(argsToInt(argSplit[1]));
      if(argSplit[0] == "rungen") runSimulationGenerations(argsToInt(argSplit[1]));
      if(argSplit[0] == "rungencopy") runSimulationGenerations(argsToInt(argSplit[1]), true);
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
  Map* m;
  int i=-1;
  if(args.size()>0)
    i=args[0];
  if(!(m=getMap(i)))
    return;
  if(mapWindow.isOpen()){
    cout << "map " << i << " already open" << endl;
    return;
  }
  cout << "starting window for map " << i << endl;
  future<void> ret = async(&SDLWindow::drawMap, &mapWindow, m);
  cout << "started" << endl;
}

void ConsoleHandler::runSimulationGenerations(vector<int> args, bool copyMap){
  Map* m;
  int i=-1;
  bool graphics=true;
  if(args.size()>0)
    i=args[0];
  if(!(m=getMap(i)))
    return;
  int steps = 1;
  if(args.size()>1 && args[1]>0)
    steps=args[1];
  if(args.size()>2)
    graphics=args[2];
  if(copyMap){
    cout << "Copying map " << i << "..." << endl;
    m = m->deepCopy();
    _maps.push_back(m);
    i = _maps.size()-1;
    cout << "Done" << endl;
  }
  cout << "Running simulation map " << i << " for " << steps << " step(s)..." << endl;
  if(graphics){
    future<void> ret = async(&ConsoleHandler::runSimulation, this, m, steps, graphics);
    ret.get();
  }else
    runSimulation(m, steps, graphics);
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

void ConsoleHandler::runSimulation(Map* m, int steps, bool show){
  SDLWindow* w;
  if(show)
    w = new SDLWindow();
  SDL_Event e;
  while(steps>0){
    cout << "Generations left: " << steps << endl;
    while(m->oneTick()){
      if(show)
        m->draw(w);
      SDL_PollEvent(&e);
    }
    steps--;
  }
  if(show){
    vector<Animal*> herbs =  m->bestHerbivores();
    for(Animal* h: herbs){
      h->prepareDrawNeurons();
      SDL_PollEvent(&e);
      while(e.type != SDL_QUIT && e.type != SDL_KEYDOWN){
        SDL_PollEvent(&e);
        h->drawNeurons(w);
      }
    }
    delete w;
  }
}

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
    cout << "draw \t\tdraws current map" << endl;
    cout << "run: ";
    getline(cin, ans);
    cout << endl;
    argSplit = argsTostr(ans);
    if(argSplit[0] == "carni" ||
      argSplit[0] == "herbi" ||
      argSplit[0] == "bestcarni" ||
      argSplit[0] == "bestherbi")outputAnimal(m, argSplit[0], argsToInt(argSplit[1]));
    if(argSplit[0] == "draw"){
      future<void> ret = async(&ConsoleHandler::drawMap, this, m);
      ret.get();
    }
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
    cout << "draw \t\tdraws current map" << endl;
    cout << "mutate \t\tmutates animals neurons" << endl;
    cout << "run: ";
    getline(cin, ans);
    cout << endl;
    argSplit = argsTostr(ans);
    if(argSplit[0] == "neuron")outputNeuron(a, argsToInt(argSplit[1]));
    if(argSplit[0] == "draw"){
      future<void> ret = async(&ConsoleHandler::drawNeurons, this, a);
      ret.get();
    }
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

void ConsoleHandler::drawMap(Map* m){
  SDLWindow w;
  SDL_Event e;
  SDL_PollEvent(&e);
  while(e.type != SDL_QUIT && e.type != SDL_KEYDOWN){
    SDL_PollEvent(&e);
    m->draw(&w);
  }
}

void ConsoleHandler::drawNeurons(Animal* a){
  SDLWindow w;
  SDL_Event e;
  a->prepareDrawNeurons();
  SDL_PollEvent(&e);
  while(e.type != SDL_QUIT && e.type != SDL_KEYDOWN){
    SDL_PollEvent(&e);
    a->drawNeurons(&w);
  }
}
