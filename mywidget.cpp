#include "mywidget.h"
#include "ui_mywidget.h"
#include <QPainter>
#include <QFont>
#include <QResizeEvent>
#include <QMouseEvent>


MyWidget::~MyWidget()
{
    auto j = treeInfo.begin();
    for (; j != treeInfo.end(); ++j)
        delete j->second;
    treeInfo.clear();
    HNodeInfo.clear();
    delete ui;
}




MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),max_x(0),max_y(0),
    min_x(0),tree_height(0),ui(new Ui::MyWidget)
{
 ui->setupUi(this);

}


void MyWidget::dopaint()
{
    QPainter painter(this);
    painter.translate(0,0);
    auto it = treeInfo.begin();
    QFont font("Calibri",12);
    painter.setFont(font);
    for(; it != treeInfo.end(); ++it)
    {
        NodeInfo *p = it->second;
        if (p->color)
        {
            painter.setPen(Qt::black);
            painter.setBrush(Qt::black);
        }
        else
        {
            painter.setPen(Qt::red);
            painter.setBrush(Qt::red);
        }


        painter.translate(0,0);
        painter.drawEllipse(p->x, p->y, elipseWidth, elipseHeight);
        painter.setPen(Qt::white);
        painter.translate(0,0);
        painter.setPen(Qt::yellow);
        painter.drawText(p->x+elipseWidth/4, p->y+elipseWidth/2+4, QString::number(p->value));
        painter.translate(0,0);
        painter.setPen(Qt::black);
        if (p->parent)
            painter.drawLine(p->x+elipseWidth/2, p->y, p->parent->x+elipseWidth/2, p->parent->y+elipseHeight);
    }
}


void MyWidget::paintEvent(QPaintEvent*)
{
    if (tree->empty()) return;
    create_TreeInfo();
    adjust_TreeInfo(true);
    adjust_TreeShape(tree->root());
    adjust_TreeInfo(true);
    dopaint();
}


void MyWidget::set_rbtree(TreeType *t)
{
    tree = t;
}


void MyWidget::create_TreeInfo()
{
    if (tree->empty()) return;
    clear_TreeInfo();
    LinkType root = tree->root();
    if (!root) return;
    auto it = treeInfo.find(root);
    if (it == treeInfo.end())
    {
        auto p = new NodeInfo;
        p->x = 0;
        p->y = elipseHeight;
        p->color = root->color;
        p->value = root->value_field;
        p->parent = 0;
        p->type = NodeInfo::ROOT_TYPE;
        p->node = root;
        treeInfo[root] = p;
        create_TreeInfo(TreeType::left(root), p, NodeInfo::LEFT_TYPE);
        create_TreeInfo(TreeType::right(root), p, NodeInfo::RIGHT_TYPE);
    }


    if (min_x < 0)
        move_Treex(elipseWidth+(0 - min_x) + elipseWidth);
    if (max_x > this->width())
        this->setMinimumWidth(max_x + elipseWidth*10);
    if (max_y > this->height())
        this->setMinimumHeight(max_y + elipseHeight*10);
    return;
}


void MyWidget::create_TreeInfo(LinkType node, NodeInfo *parent_NodeInfo, int type)
{
    if (!node) return;
    NodeInfo *p;
    auto it = treeInfo.find(node);
    if (it == treeInfo.end())
    {
        p = new NodeInfo;
        if (type == NodeInfo::LEFT_TYPE)
            p->x = parent_NodeInfo->x - elipseWidth*1.5;
        else if(type == NodeInfo::RIGHT_TYPE)
            p->x = parent_NodeInfo->x + elipseWidth*1.5;
        p->y = parent_NodeInfo->y + elipseHeight*1.5 + (tree_height - tree->depth(node))*5;
        p->color = node->color;
        p->value = node->value_field;
        p->parent = parent_NodeInfo;
        p->type = type;
        p->node = node;
        treeInfo[node] = p;
        auto j = HNodeInfo.find(p->y);
        if (j == HNodeInfo.end())
        {
            HListType *hlt = new HListType;
            hlt->push_back(p);
            HNodeInfo[p->y] = hlt;
        }
        else
        {
            HNodeInfo[p->y]->push_back(p);
        }
        create_TreeInfo(TreeType::left(node), p, NodeInfo::LEFT_TYPE);
        create_TreeInfo(TreeType::right(node), p, NodeInfo::RIGHT_TYPE);
    }
    else
    {
        p = it->second;
        if (type == NodeInfo::LEFT_TYPE)
            p->x = parent_NodeInfo->x - elipseWidth*1.5;
        else if(type == NodeInfo::RIGHT_TYPE)
            p->x = parent_NodeInfo->x + elipseWidth*1.5;
        if (p->x < min_x) min_x = p->x;
        //p->y = parent_NodeInfo->y + elipseHeight*1.5;
        create_TreeInfo(TreeType::left(node), p, NodeInfo::LEFT_TYPE);
        create_TreeInfo(TreeType::right(node), p, NodeInfo::RIGHT_TYPE);
    }


    if (p->x > max_x) max_x = p->x;
    if (p->y > max_y) max_y = p->y;
    if (p->x < min_x) min_x = p->x;
}


void MyWidget::adjust_TreeInfo(bool adjust_flag)
{
    if (!adjust_flag)
    {
        clear_HNodeInfo();
        return;
    }
    if (HNodeInfo.empty()) return;
    bool adjust = false;
    auto it = HNodeInfo.begin();
    for (; it != HNodeInfo.end(); ++it)
    {
        auto hlt = it->second;
        int x = 0;
        for (size_t i = 0; i < hlt->size(); ++i)
        {
            if ((*hlt)[i]->x > x)
            {
                x = (*hlt)[i]->x;
                continue;
            }
            else
            {
                adjust = true;
                NodeInfo *pparent = (*hlt)[i]->parent;
                if (pparent->type != NodeInfo::ROOT_TYPE)
                {
                    if (pparent->type == NodeInfo::LEFT_TYPE)
                        pparent->x -= elipseWidth*2.5;
                    else
                        pparent->x += elipseWidth*2.5;
                    create_TreeInfo(TreeType::left(pparent->node), pparent, NodeInfo::LEFT_TYPE);
                    create_TreeInfo(TreeType::right(pparent->node), pparent, NodeInfo::RIGHT_TYPE);
                    break;
                }
                else
                {
                    adjust = false;
                    break;
                }
            }
        }
    }
    return adjust_TreeInfo(adjust);
}


void MyWidget::adjust_TreeShape(LinkType node)
{
    if (!node) return;
    if (treeInfo.empty()) return;
    int left_x;
    int right_x;
    int x;
    if (TreeType::left(node) && TreeType::right(node))
    {
        x = treeInfo[node]->x;
        left_x = treeInfo[TreeType::left(node)]->x;
        right_x = treeInfo[TreeType::right(node)]->x;
        if (x - left_x != right_x - x)
        {
            treeInfo[node]->x = left_x + int((right_x - left_x + 1)/2 + 0.5);
        }
    }
    adjust_TreeShape(TreeType::left(node));
    adjust_TreeShape(TreeType::right(node));
    if (TreeType::left(node) && TreeType::right(node))
    {
        x = treeInfo[node]->x;
        left_x = treeInfo[TreeType::left(node)]->x;
        right_x = treeInfo[TreeType::right(node)]->x;
        if (x - left_x != right_x - x)
        {
            treeInfo[node]->x = left_x + int((right_x - left_x + 1)/2 + 0.5);
        }
    }
}


void MyWidget::move_Treex(int distance)//one step to sky
{
    if (tree->empty()) return;
    if (treeInfo.empty()) return;
    if (treeInfo.end() == treeInfo.find(tree->root())) return;
    LinkType root = tree->root();
    NodeInfo *r = treeInfo[root];
    auto p = new NodeInfo;
    p->x = r->x + distance;
    clear_TreeInfo();
    p->y = elipseHeight;
    p->color = root->color;
    p->value = root->value_field;
    p->parent = 0;
    p->type = NodeInfo::ROOT_TYPE;
    p->node = root;
    treeInfo[root] = p;


    create_TreeInfo(TreeType::left(root), p, NodeInfo::LEFT_TYPE);
    create_TreeInfo(TreeType::right(root), p, NodeInfo::RIGHT_TYPE);
}


void MyWidget::clear_TreeInfo()
{
    auto j = treeInfo.begin();
    for (; j != treeInfo.end(); ++j)
        delete j->second;
    treeInfo.clear();
    clear_HNodeInfo();
}


void MyWidget::clear_HNodeInfo()
{
    auto it = HNodeInfo.begin();
    for (; it != HNodeInfo.end(); ++it)
        delete it->second;
    HNodeInfo.clear();
}


void MyWidget::set_TreeHeight(size_t height)
{
    tree_height = height;
}
