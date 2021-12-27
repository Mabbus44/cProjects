#include "Day22.h"

void Cube::free(){
  for(Cube* c:children){
    c->free();
    delete c;
  }
  children.clear();
}

void Cube::merge(){
  if(children.size()==0)
    return;
  for(Cube* c:children){
    if((int)(c->children.size())>0)
      c->merge();
  }
  on=children[0]->on;
  for(Cube* c:children){
    if((int)(c->children.size())>0)
      return;
    if(on != c->on)
      return;
  }
  free();
}

int64_t Cube::countCubes(){
  int64_t sum=1;
  for(Cube* c:children)
    sum += c->countCubes();
  return sum;
}

int64_t Cube::getOnCubes(int ix1,int ix2,int iy1,int iy2,int iz1,int iz2){
  if(ix1>x2 || ix2<x1 ||
     iy1>y2 || iy2<y1 ||
     iz1>z2 || iz2<z1)
    return 0;
  if((int)children.size()>0){
    int64_t sum=0;
    for(Cube* c:children)
      sum += c->getOnCubes(ix1,ix2,iy1,iy2,iz1,iz2);
    return sum;
  }
  if(!on)
    return 0;
  int64_t xmin = max(ix1, x1);
  int64_t xmax = min(ix2, x2);
  int64_t ymin = max(iy1, y1);
  int64_t ymax = min(iy2, y2);
  int64_t zmin = max(iz1, z1);
  int64_t zmax = min(iz2, z2);
  if(xmin>xmax || ymin>ymax || zmin>zmax){
    cout << "start" << endl;
    cout << ix1 << "-" << ix2 << " " << iy1 << "-" << iy2 << " " << iz1 << "-" << iz2 << endl;
    cout << x1 << "-" << x2 << " " << y1 << "-" << y2 << " " << z1 << "-" << z2 << endl;
    cout << xmin << "-" << xmax << " " << ymin << "-" << ymax << " " << zmin << "-" << zmax << endl;
    return 0;
  }
  return (xmax-xmin+1)*(ymax-ymin+1)*(zmax-zmin+1);
}

void Cube::load(vector<int>& inst, bool output, string tab){
  if(inst[1]>x2 || inst[2]<x1 ||
     inst[3]>y2 || inst[4]<y1 ||
     inst[5]>z2 || inst[6]<z1){
/*    if(output)
      cout << tab << "not touched" << endl;*/
    return;
  }
  if((int)children.size()>0){
    for(Cube* c:children)
      c->load(inst, output, tab+" ");
    return;
  }
  if(output && false){
    cout << tab<<"load: ";
    this->output("", true);
  }
  vector<int> splitX = {x1};
  vector<int> splitY = {y1};
  vector<int> splitZ = {z1};
  if(inst[1]>x1 && inst[1]<=x2)
    splitX.push_back(inst[1]);
  if(inst[3]>y1 && inst[3]<=y2)
    splitY.push_back(inst[3]);
  if(inst[5]>z1 && inst[5]<=z2)
    splitZ.push_back(inst[5]);

  if(inst[2]>=x1 && inst[2]<x2)
    splitX.push_back(inst[2]+1);  //+1 because we want the first point of a block, not the last
  if(inst[4]>=y1 && inst[4]<y2)
    splitY.push_back(inst[4]+1);
  if(inst[6]>=z1 && inst[6]<z2)
    splitZ.push_back(inst[6]+1);

  splitX.push_back(x2+1); //+1 because we want the first point of a block, not the last
  splitY.push_back(y2+1);
  splitZ.push_back(z2+1);
  if(output && false){
    cout << tab << "splitting (";
    for(int i:splitX)
      cout << i <<", ";
    cout <<"), (";
    for(int i:splitY)
      cout << i <<", ";
    cout <<"), (";
    for(int i:splitZ)
      cout << i <<", ";
    cout <<")" << endl;
  }

  bool inOn = false;
  if(inst[0]==1)
    inOn = true;
  for(int x=0; x<(int)splitX.size()-1; x++){
    for(int y=0; y<(int)splitY.size()-1; y++){
      for(int z=0; z<(int)splitZ.size()-1; z++){
        if(splitX[x]>=inst[1] && splitX[x]<=inst[2] && splitY[y]>=inst[3] && splitY[y]<=inst[4] && splitZ[z]>=inst[5] && splitZ[z]<=inst[6]){
          if(output&&false){
            int64_t xx = (splitX[x+1]-1-splitX[x]);
            int64_t yy = (splitY[y+1]-1-splitY[y]);
            int64_t zz = (splitZ[z+1]-1-splitZ[z]);
            cout << xx*yy*zz << endl;
          }
          children.push_back(new Cube(splitX[x], splitX[x+1]-1, splitY[y], splitY[y+1]-1, splitZ[z], splitZ[z+1]-1, inOn, false, tab+" "));
        }
        else
          children.push_back(new Cube(splitX[x], splitX[x+1]-1, splitY[y], splitY[y+1]-1, splitZ[z], splitZ[z+1]-1, on, false, tab+" "));
      }
    }
  }
}

void Cube::output(string tab, bool oneLine){
  cout << tab << x1 << "-" << x2 << ", " << y1 << "-" << y2 << ", "<< z1 << "-" << z2 << " " << on << endl;
  if(oneLine)
    return;
  for(Cube* c:children)
    c->output(tab+" ");
}

Day22::Day22()
{
  //ctor
}

Day22::~Day22()
{
  //dtor
}

void Day22::part1(string filename){
  InputLoader loader(filename);
  vector<vector<string>> vvs=loader.toVectorStr2d({" x=", "..", ",y=", "..", ",z=", ".."});
  vector<vector<int>> instructions;
  int64_t minX=999999999, minY=999999999, minZ=999999999;
  int64_t maxX=-999999999, maxY=-999999999, maxZ=-999999999;
  for(vector<string> vs:vvs){
    if((int)vs.size()>0){
      vector<int> vi;
      if(vs[0].compare("on")==0)
        vi.push_back(1);
      else
        vi.push_back(0);

      int x1=stoi(vs[1]);
      if(x1<minX)
        minX=x1;
      vi.push_back(x1);

      int x2=stoi(vs[2]);
      if(x2>maxX)
        maxX=x2;
      vi.push_back(x2);

      int y1=stoi(vs[3]);
      if(y1<minY)
        minY=y1;
      vi.push_back(y1);

      int y2=stoi(vs[4]);
      if(y2>maxY)
        maxY=y2;
      vi.push_back(y2);

      int z1=stoi(vs[5]);
      if(z1<minZ)
        minZ=z1;
      vi.push_back(z1);

      int z2=stoi(vs[6]);
      if(z2>maxZ)
        maxZ=z2;
      vi.push_back(z2);

      instructions.push_back(vi);
    }
  }
  Cube* bigCube = new Cube();
  bigCube->x1=minX;
  bigCube->x2=maxX;
  bigCube->y1=minY;
  bigCube->y2=maxY;
  bigCube->z1=minZ;
  bigCube->z2=maxZ;
  bigCube->on = false;
  for(vector<int> instruction:instructions)
    bigCube->load(instruction);
  /*for(int i=0; i<58; i++)
    bigCube->load(instructions[i]);*/
  //bigCube->load(instructions[0]);
  cout << "Part 1: " << bigCube->getOnCubes(-50, 50, -50, 50, -50, 50) << endl;
  cout << "Part 2: " << bigCube->getOnCubes(minX, maxX, minY, maxY, minZ, maxZ) << endl;
}

void Day22::part2(string filename){
}
