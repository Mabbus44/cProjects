#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <fstream>

using namespace std;

class FileHandler
{
  public:
    fstream nodeFile;
    fstream cubeFile;
    bool openNodeFile(string filename);
    bool openCubeFile(string filename);
    FileHandler();
    virtual ~FileHandler();

  protected:

  private:
};

#endif // FILEHANDLER_H
