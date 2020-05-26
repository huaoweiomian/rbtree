#ifndef MYRBTREE_H
#define MYRBTREE_H

enum COLOR{BLACK, RED};
struct mynode{
    mynode(){
        v= 0;
        left = right = parent = nullptr;
    }
    int v;
    mynode* left;
    mynode* right;
    mynode* parent;
    COLOR c;
    bool is_red(){
        return c == RED;
    }
    bool is_black(){
        return c == BLACK;
    }
};

class myrbtree
{
public:
    myrbtree();
    mynode* head;
    void left_rotate(mynode *node);
    void right_rotate(mynode *node);
};

#endif // MYRBTREE_H