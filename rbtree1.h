#ifndef RBTREE1_H
#define RBTREE1_H

#include <vector>
using namespace std;
class rbtree1
{
public:
    rbtree1();
};



class LinkType_t{
public:
    int value_field;
    bool color;//true is black;
};
typedef  LinkType_t* LinkType;

struct NodeInfo{
public:
    enum ETreeType{LEFT_TYPE,RIGHT_TYPE,ROOT_TYPE};
    double x,y;
    bool color;//true is black;
    NodeInfo* parent;
    int value;
    LinkType node;
    ETreeType type;
};
typedef  NodeInfo::ETreeType  ETreeType;
typedef vector<NodeInfo *> HListType;

class TreeType{
public:
    bool empty(){return false;}
    LinkType root(){return nullptr;}
    static LinkType left(LinkType root);
    static LinkType right(LinkType root);
    int depth(LinkType node);
};






#endif // RBTREE1_H
