#include "VueTuile.h"
#include <QPen>
#include <QFlags>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <cstdlib>
#include "FenetreJeu.h"



VueTuile::VueTuile(Tuile* t): tuile(t)
{
    setPixmap(tuile->getImg().scaled(60,60));
}

void VueTuile::activate()
{
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setOffset(3);
    setGraphicsEffect(shadow);
    setFlag(QGraphicsPixmapItem::ItemIsMovable);
    setFlag(QGraphicsPixmapItem::ItemIsSelectable);
}



void VueTuile::mouseReleaseEvent(QGraphicsSceneMouseEvent *em)
{
    int x= (int) pos().x();
    int y= (int) pos().y();
    int cmpl_gauche_x= (abs(x)%60), cmpl_droite_x=(60-cmpl_gauche_x);

    if(cmpl_gauche_x > cmpl_droite_x){
        if(x>0) x+=cmpl_droite_x;
        else x-=cmpl_droite_x;
    }else{
        if(x>0) x-=cmpl_gauche_x;
        else x+=cmpl_gauche_x;
    }
    int cmpl_gauche_y= (abs(y)%60), cmpl_droite_y=60-cmpl_gauche_y;
    if(cmpl_gauche_y > cmpl_droite_y){
        if(y>0) y+=cmpl_droite_y;
        else y-=cmpl_droite_y;
    }else{
        if(y>0) y-=cmpl_gauche_y;
        else y+=cmpl_gauche_y;
    }
    setPos(x,y);
    QGraphicsPixmapItem::mouseReleaseEvent(em);
}


void VueTuile::mousePressEvent(QGraphicsSceneMouseEvent *event){

    if(event->button() == Qt::RightButton){        if(flags()== (QGraphicsPixmapItem::ItemIsSelectable |QGraphicsPixmapItem::ItemIsMovable) ){
            tuile->rotation();
            setPixmap(tuile->getImg().scaled(60,60));
        }

        //fenetrejeu::tourner_Tuile(this->pixmap());
    }
}
