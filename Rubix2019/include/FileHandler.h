#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <fstream>
#include "BinaryNodeF.h"
#include "RubixCube20BF.h"

using namespace std;

class FileHandler
{
  public:
    fstream nodeFile;
    fstream cubeFile;
    fstream statsFile;
    bool openNodeFile(string filename);
    bool openCubeFile(string filename);
    bool openStatsFile(string filename);
    bool createNodeFile(string filename);
    bool createCubeFile(string filename);
    bool createStatsFile(string filename);
    bool saveCube(RubixCube20BF* cube);
    bool saveCubeFirstChild(int adress, __int64 FirstChild);
    bool saveCubeSibling(int adress, __int64 sibling);
    RubixCube20BF* loadCube(int adress);
    bool saveNode(BinaryNodeF* node);
    BinaryNodeF* loadNode(int adress);
    __int64 loadNodeParent(int adress);
    bool saveNodeParent(int adress, __int64 parent);
    __int64 loadNodeSmallerChild(int adress);
    bool saveNodeSmallerChild(int adress, __int64 SmallerChild);
    __int64 loadNodeBiggerChild(int adress);
    bool saveNodeBiggerChild(int adress, __int64 BiggerChild);
    __int64 loadNodeHeight(int adress);
    bool saveNodeHeight(int adress, __int64 height);
    bool saveStats(__int64 checkingCube, __int64 totalPopulation, __int64 populationUpuntilLastGeneration, __int64 generation);
    void loadStats(__int64* checkingCube, __int64* totalPopulation, __int64* populationUpuntilLastGeneration, __int64* generation, bool print = false);
    FileHandler();
    virtual ~FileHandler();

  protected:

  private:
};

#endif // FILEHANDLER_H
