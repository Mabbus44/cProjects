#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

enum NeuronType {SN_GRASS_DIST_N, SN_GRASS_DIST_S, SN_GRASS_DIST_E, SN_GRASS_DIST_W,
  SN_HERBIVORE_DIST_N, SN_HERBIVORE_DIST_S, SN_HERBIVORE_DIST_E, SN_HERBIVORE_DIST_W,
  SN_CARNIVORE_DIST_N, SN_CARNIVORE_DIST_S, SN_CARNIVORE_DIST_E, SN_CARNIVORE_DIST_W,
  LN_OR, LN_AND, LN_GREATER_THAN, LN_ADD,
  ON_MOVE_N, ON_MOVE_S, ON_MOVE_E, ON_MOVE_W,
  ON_EAT,
  NODE_TYPE_COUNT};
enum NeuronFamily {NEURON, LOGIC_NEURON, SENSOR_NEURON, OUTPUT_NEURON};
enum EntityType {CARNIVORE, HERBIVORE, PLANT, BEST_CARNIVORE, BEST_HERBIVORE};
enum Directions {NORTH, SOUTH, EAST, WEST};
enum NeuronMutations {NEW_NEURON, REPLACE_NEURON, REWIRE_NEURON, REROLL_PROPERTIES_NEURON, NEURON_MUTATION_COUNT};
enum SimulationTypes {SIMULATION_STEP, SIMULATION_GENERATION};
enum OutputTypes {OUTPUT_ONELINE, OUTPUT_OVERVIEW, OUTPUT_DEEP, OUTPUT_ALL};
enum DrawNeuronType {CARNIVORE_NEURON, HERBIVORE_NEURON, BEST_CARNIVORE_NEURON, BEST_HERBIVORE_NEURON, DRAW_NEURON_TYPE_COUNT};
enum ConsoleActions {CREATE_MAP, INIT_MAP, DELETE_MAP, VIEW_MAP, RUN_SIMULATION_STEPS, RUN_SIMULATION_GENERATIONS, COPY_MAP, OUTPUT_SIMULATION_STATUS, OUTPUT_MAPS, OUTPUT_MAPS_ONELINE, OUTPUT_ANIMALS, OUTPUT_NEURONS, MUTATE_NEURONS};
const int MAP_WIDTH = 640;
const int MAP_HEIGHT = 480;
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 800;
const int CARNIVORES_PER_SIMULATION = 1;
const int HERBIVORES_PER_SIMULATION = 200;
const int PLANTS_PER_SIMULATION = 2000;
const int SAVE_CARNIVORES = 10;
const int SAVE_HERBIVORES = 10;
const int NEURONS_PER_ANIMAL = 30;
const int NEURON_MUTATIONS_PER_ROUND_MIN = 0;
const int NEURON_MUTATIONS_PER_ROUND_MAX = 3;
const int CHILDREN_PER_NEURON_MIN = 1;
const int CHILDREN_PER_NEURON_MAX = 3;
const int SENSORS_MAX_DIST = 200;
const int NEW_NEURON_MIN = 1;
const int NEW_NEURON_MAX = 3;
const int REPLACE_NEURON_MIN = 1;
const int REPLACE_NEURON_MAX = 3;
const int REWIRE_NEURON_MIN = 1;
const int REWIRE_NEURON_MAX = 3;
const int REWIRE_NEURON_MIN_WIRES = 1;
const int REWIRE_NEURON_MAX_WIRES = 2;
const int HERBIVORE_START_FOOD = 200;
const int CARNIVORE_START_FOOD = 200;
const int HERBIVORE_EAT_FOOD = 50;
const int CARNIVORE_EAT_FOOD = 50;
const int EAT_PLANT_RANGE = 4;
const int EAT_HERBIVORE_RANGE = 2;

#endif // CONSTANTS_H_INCLUDED
