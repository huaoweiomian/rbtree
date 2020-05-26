#include "myrbtree.h"

myrbtree::myrbtree()
{
    head = nullptr;
}

void myrbtree::left_rotate(mynode* x)
{
    mynode* p = x->parent;
    mynode* y = x->right;
    x->right = y->left;
    y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr){
        head = y;
    } else if(p->left == x){
        p->left = y;
    }else{
        p->right = y;
    }
    y->left = x;
    x->parent = y;
}

void myrbtree::right_rotate(mynode *y)
{
    mynode* p = y->parent;
    mynode* x = y->left;
    mynode* xright = x->right;
    y->left = xright;
    xright->parent = y;
    x->parent = p;
    if(p == nullptr){
        head = x;
    }else if (p->right == y){
        p->right = x;
    }else{
        p->left = x;
    }
    x->right = y;
    y->parent = x;
}


