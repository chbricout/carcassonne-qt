#pragma once

#include <QGraphicsItem>
#include <QLabel>
#include <QMouseEvent>
#include <string>
#include <QPixmap>
#include "Tuile.h"

class VueTuile : public QGraphicsPixmapItem//, public QGraphicsPixmapItem
{
public:
    VueTuile(Tuile* t);
    Tuile* getTuile(){return tuile;};
    void activate();

    //QGraphicsPixmapItem* getImage(){return &tuile_image;}

signals:
    void rightClicked();
    void leftClicked();

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *em);
    void mousePressEvent(QGraphicsSceneMouseEvent *em);

private:
    Tuile* tuile=nullptr;
   //QGraphicsPixmapItem tuile_image; //comment afficher ??
   //QGraphicsPolygonItem tuile_fond;

};

