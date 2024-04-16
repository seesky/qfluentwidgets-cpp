#pragma once

#include "gallery_interface.h"
#include "../common/translator.h"
#include "../../../components/widgets/list_view.h"
#include "../../../components/widgets/tree_view.h"
#include "../../../components/widgets/flip_view.h"

class ViewInterface : public GalleryInterface{
    Q_OBJECT
public:
    ViewInterface(QWidget *parent);
};


class Frame : public QFrame{
    Q_OBJECT
public:
    Frame(QWidget *parent);
    void addWidget(QWidget *widget);
    QHBoxLayout *hBoxLayout;
};


class ListFrame : public Frame{
    Q_OBJECT
public:
    ListFrame(QWidget *parent);

    ListWidget *listWidget;
};


class TreeFrame : public Frame{
    Q_OBJECT
public:
    TreeFrame(QWidget *parent, bool enableCheck);
    TreeWidget *tree;
};


class TableFrame : public TableWidget{
    Q_OBJECT
public:
    TableFrame(QWidget *parent);
};