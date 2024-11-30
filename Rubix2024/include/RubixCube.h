#ifndef RUBIXCUBE_H
#define RUBIXCUBE_H

#include <iomanip>
#include <array>
#include <fstream>
#include <sys/stat.h> //stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exists-using-standard-c-c11-14-17-c
#include "iostream"
enum SEB {SMALLER, EQUALS, BIGGER};
#define NONE -1
#define CUBE_SIZE 20  //20x1byte int
#define NODE_SIZE 52  //20x1byte int + 4x8byte int
#define NO_ACTION -1000000000  //Dont make trees deeper than this :)

class Cube
{
  public:
    Cube(){}
    Cube(std::fstream* file){load(file);}
    Cube(Cube* other){this->_corners = other->_corners; this->_sides = other->_sides;}
    virtual ~Cube(){}
    bool operator==(const Cube& other) const;
    bool operator<(const Cube& other);
    bool operator>(const Cube& other);
    int seb(Cube* other);
    void print();
    void setStartingCube();
    void save(std::fstream* file);
    Cube* returnChild(int move);                  // Rotates one side and returns resulting cube. 12 possible moves.
    Cube* returnRot(int rot);                     // Rotates and turns the cube, switches the colors. 24 possible rotations.
    __int8 turnSide(__int8 side);
    __int8 turnCornerRight(__int8 corner);
    __int8 turnCornerLeft(__int8 corner);
    __int8 replaceSide(__int8 side, int rot);
    __int8 replaceCorner(__int8 corner, int rot);
  protected:

  private:
    void load(std::fstream* file);
    std::array<__int8, 8> _corners;
    std::array<__int8, 12> _sides;
};

class BinaryNode;

class BinaryNodeRef{
  public:
    BinaryNodeRef(){}
    virtual ~BinaryNodeRef(){}
    void nodeRef(BinaryNode* b);
    void id(__int64 id) {if(_id != NONE) std::cout << "Error: Trying to change id on a valid binaryNodeRef" << std::endl; _id = id;}
    BinaryNode* nodeRef();
    __int64 id() {return _id;}
    void createNode(BinaryNode* parent, BinaryNode* smaller, BinaryNode* bigger, Cube* cube);
  protected:
  private:
    BinaryNode* _nodeRef = nullptr;
    __int64 _id = NONE;
};

class BinaryNode
{
  public:
    BinaryNode() = delete;
    BinaryNode(__int64 id) {load(id); std::cout << "Creating BinaryNode: " << id << std::endl;}
    BinaryNode(__int64 id, BinaryNode* solveParent, BinaryNode* parent, BinaryNode* smaller, BinaryNode* bigger, Cube* cube);
    virtual ~BinaryNode(){if(_cube) delete _cube;}
    bool operator==(const BinaryNode& other);
    bool operator<(const BinaryNode& other);
    bool operator>(const BinaryNode& other);
    __int64 id() {return _id;}
    __int64 solveParentId() {return _solveParent.id();}
    __int64 parentId() {return _parent.id();}
    __int64 smallerId() {return _smaller.id();}
    __int64 biggerId() {return _bigger.id();}
    void id(__int64 id) {if(_id != NONE) std::cout << "Error: Trying to change id on a valid binaryNode" << std::endl; _id = id;}
    void save();
    void generateChildren();
    int insertIntoTree(Cube* cube);

  protected:
  private:
    void load(__int64 id);
    __int64 _id = NONE;
    Cube* _cube = nullptr;
    BinaryNodeRef _solveParent; //Parent in solving cube
    BinaryNodeRef _parent;      //Parent in DT-tree
    BinaryNodeRef _smaller;
    BinaryNodeRef _bigger;
};

class CubeSolver{
  public:
    CubeSolver();
    virtual ~CubeSolver(){}
    void run();
    std::fstream* getFileInPos(__int64 id);
    Cube* getSmallestRotation(Cube* cube);
    int insertIntoTree(Cube* cube);
    __int64 useId() {return _nextId++;}
    BinaryNode* testingNode() {return _testingNode;}
  private:
    bool fileExist(const std::string& name);
    void openFile();
    BinaryNode* _topNode = nullptr;
    BinaryNode* _testingNode = nullptr;
    std::string _fileName = "cubes.dat";
    std::fstream _file;
    __int64 _nextId = 0;
};

extern CubeSolver cubeSolver;

#endif // RUBIXCUBE_H
