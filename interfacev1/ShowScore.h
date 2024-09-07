#pragma once
#include <QWidget>
#include "Controleur.h"

class ShowScore: public QWidget
{
    Q_OBJECT
public:
    ShowScore(Controleur * c, QWidget *parent = nullptr);
private:
    Controleur *controleur=nullptr;
};

