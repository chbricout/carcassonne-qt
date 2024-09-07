#pragma once

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include "Joueur.h"

class FrameJoueur : public QFrame
{
    Q_OBJECT
public:
    FrameJoueur(Joueur* j, QWidget *parent=nullptr);
    ~FrameJoueur();


private:
    Joueur* joueur=nullptr;
    QVBoxLayout *mainLayout=nullptr;
};

