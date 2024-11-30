#ifndef ARNESTREE_H
#define ARNESTREE_H


class ArnesTree
{
  public:
    ArnesTree();
    virtual ~ArnesTree();

  protected:

  private:
    void leftRot(ArnesNode* t);
    void rightRot(ArnesNode* t);
    void skew(ArnesNode* t);
};

class ArnesNode
{
  public:
    ArnesNode();
    virtual ~ArnesNode();
    int key() {return _key;};
    ArnesNode* left() {return _left;};
    ArnesNode* right() {return _right;};
    void key(int key) { _key = key;};
    void left(ArnesNode* left) {_left = left;}
    void right(ArnesNode* right) {_right = right;}

  protected:

  private:
    int _key;
    ArnesNode* _left;
    ArnesNode* _right;
};

#endif // ARNESTREE_H
