#pragma once
#include <QGraphicsPixmapItem>
#include "Meeple.h"



class VueMeeple : public QGraphicsPixmapItem
{
    friend class VuePlateau;
public:
  VueMeeple(Meeple* m);


private:
    Meeple* meeple=nullptr;

};
