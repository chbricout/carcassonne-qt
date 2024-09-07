#pragma once

#include <QGraphicsScene>
#include <QObject>
#include <QWidget>

#include "VueTuile.h"
#include "VueMeeples.h"
#include "Plateau.h"

class Tuile;


class VuePlateau : public QGraphicsScene
{
private:
    Plateau* plateau=nullptr;
    VueTuile* newVueTuile=nullptr;

public:
    explicit VuePlateau(Plateau* p, QObject *parent = nullptr);
    //~MaScene();//destuction de la liste par la scène
    void ajouteTuile(Tuile *t);
    VueTuile* getNewTuile();
public slots:
    void removeTuile();
};

