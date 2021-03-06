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

void myrbtree::rb_insert(mynode za)
{
    mynode* z = new mynode();
    z->v = za.v;
    mynode* y = nullptr;
    mynode* x = head;
    while (x != nullptr){
        y = x;
        if(z->v < x->v){
            x = x->left;
        }else{
            x = x->right;
        }
    }
    x->parent = y;
    if(y == nullptr){
        head = z;
    } else if(z->v < y->v){
        y->left = z;
    }else{
        y->right = z;
    }
    z->c = RED;
    rb_insert_fixup(z);
}

void myrbtree::rb_insert_fixup(mynode *z)
{
    while(z->parent->c == RED){
        if (z->parent == z->parent->parent->left){
            mynode* y = z->parent->parent->right;
            if (y->c == RED){
                z->parent->c = BLACK;
                y->c = BLACK;
                z->parent->parent->c = RED;
                z = z->parent->parent;
            }else if (z == z->parent->right){
                z = z->parent;
                left_rotate(z);
                z->parent->c = BLACK;
                z->parent->parent->c = RED;
                right_rotate(z->parent->parent);
            }
        } else{
            mynode* y = z->parent->parent->left;
            if (y->c == RED){
                z->parent->c = BLACK;
                y->c = BLACK;
                z->parent->parent->c = RED;
                z = z->parent->parent;
            }else if (z == z->parent->left){
                z = z->parent;
                right_rotate(z);
                z->parent->c = BLACK;
                z->parent->parent->c = RED;
                left_rotate(z->parent->parent);
            }
        }
    }
    head->c = BLACK;
}

void myrbtree::rb_delete(mynode *z)
{
    if(z->left == nullptr || z->right == nullptr){

    }
}


