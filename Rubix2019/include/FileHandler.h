#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#define CUBES_PER_FILE 200
#include <fstream>
#include <vector>
#include "BinaryNodeF.h"
#include "RubixCube20BF.h"

using namespace std;

class FileHandler
{
  public:
    vector<fstream*> nodeFile;
    vector<fstream*> cubeFile;
    fstream statsFile;
    bool openNodeFile(string filename);
    bool openCubeFile(string filename);
    bool openStatsFile(string filename);
    bool createNodeFile(string filename);
    bool createCubeFile(string filename);
    bool createStatsFile(string filename);
    bool saveCube(RubixCube20BF* cube);
    bool saveCubeFirstChild(__int64 adress, __int64 FirstChild);
    bool saveCubeSibling(__int64 adress, __int64 sibling);
    RubixCube20BF* loadCube(__int64 adress);
    bool saveNode(BinaryNodeF* node);
    BinaryNodeF* loadNode(__int64 adress);
    __int64 loadNodeParent(__int64 adress);
    bool saveNodeParent(__int64 adress, __int64 parent);
    __int64 loadNodeSmallerChild(__int64 adress);
    bool saveNodeSmallerChild(__int64 adress, __int64 SmallerChild);
    __int64 loadNodeBiggerChild(__int64 adress);
    bool saveNodeBiggerChild(__int64 adress, __int64 BiggerChild);
    __int64 loadNodeHeight(__int64 adress);
    bool saveNodeHeight(__int64 adress, __int64 height);
    bool saveStats(__int64 checkingCube, __int64 totalPopulation, __int64 populationUpuntilLastGeneration, __int64 generation);
    void loadStats(__int64* checkingCube, __int64* totalPopulation, __int64* populationUpuntilLastGeneration, __int64* generation, bool print = false);
    FileHandler();
    virtual ~FileHandler();

  protected:

  private:
};

#endif // FILEHANDLER_H
