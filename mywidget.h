#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include "rbtree1.h"
#include<map>
using std::map;
namespace Ui {
class MyWidget;
}
const int elipseWidth = 10, elipseHeight = 20;
class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = nullptr);
    ~MyWidget();
    int max_x,max_y,
        min_x,tree_height;
    map<LinkType, NodeInfo * > treeInfo;
    map<double,HListType * > HNodeInfo;
    void dopaint();
    void create_TreeInfo();
    void clear_TreeInfo();
    void clear_HNodeInfo();
    void set_TreeHeight(size_t height);
    void set_rbtree(TreeType *t);
    TreeType* tree;
    void create_TreeInfo(LinkType node, NodeInfo *parent_NodeInfo, int type);
public slots:
    void paintEvent(QPaintEvent *);
private:
    Ui::MyWidget *ui;
};

#endif // MYWIDGET_H
