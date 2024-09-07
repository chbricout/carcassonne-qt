#pragma once

#include "Joueur.h"
#include "Tuile.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QPushButton>

class ChooseMeeple : public QFrame
{
    Q_OBJECT
public:
    ChooseMeeple(Tuile *t, Joueur * j, QWidget *parent = nullptr);
    ~ChooseMeeple();

public slots:
    void openAddMeeple(Element* e);
    void closeAddMeeple();
    void poserMeeple(Meeple *m);
    void retirerMeeple(Meeple *m,QPushButton *rmBtn);
signals:
    void meepleActionDone();

private:
    Joueur *joueur=nullptr;
    Element* selectedEl=nullptr;
    Tuile *tuile=nullptr;
    QVBoxLayout *mainLayout=nullptr;
    QWidget *meeplePicker=nullptr;
    QWidget *elementPicker=nullptr;

};

