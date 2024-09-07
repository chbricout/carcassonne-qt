/*
#include "grilledejeu.h"

grilledejeu::grilledejeu(QObject *parent) : QGraphicsScene(parent)
{
    setSceneRect(0,0,1000,1000);

    for (int i = 0; i<10; i++)
    {
        addLine(0,i *50, 450, i*50);
        addLine(i*50, 0, i*90, 45);
    }
}
*/

#include "VuePlateau.h"
#include "VueMeeples.h"

VuePlateau::VuePlateau(Plateau* p,QObject *parent) : plateau(p),QGraphicsScene(parent)
{
    int length = 3+plateau->getBasDroite().getX()-plateau->getHautGauche().getX();
    int height = 3+plateau->getBasDroite().getY()-plateau->getHautGauche().getY();
    int haut = plateau->getHautGauche().getY()-1;
    int gauche = plateau->getHautGauche().getX()-1;
    /* ------ Grille ------  */
    for(int i=0;i<=length;i++)
    {
        addLine(i*60+gauche*60,haut*60,i*60+gauche*60,height*60+haut*60,QPen(Qt::gray));
    }

    for(int i=0; i<=height; i++ ){
        addLine(gauche*60,i*60+haut*60,length*60+gauche*60,i*60+haut*60, QPen(Qt::gray));
    }

    for(Tuile* t: *plateau){
        VueTuile *vt = new VueTuile(t);
        int x = t->getCoord().getX()*60;
        int y = t->getCoord().getY()*60;
        vt->setPos(x, y);
        addItem(vt);
        for(Element* e: *t){
            if(e->getMeeple() !=nullptr){
                VueMeeple *vm = new VueMeeple(e->getMeeple());
                int width = vm->boundingRect().width();
                int height = vm->boundingRect().height();
                switch(e->getOrientation()){
                    case Orientation::Nord:
                        vm->setPos(x+30-width/2, y);
                        break;
                    case Orientation::Sud:
                        vm->setPos(x+30-width/2, y+60-height);
                        break;
                    case Orientation::Est:
                        vm->setPos(x+60-width, y+30-height/2);
                        break;
                    case Orientation::Ouest:
                        vm->setPos(x, y+30-height/2);
                        break;
                    case Orientation::Aucune:
                        vm->setPos(x+30-width/2, y+30-height/2);
                        break;
                }
                addItem(vm);
            }
        }
    }



    /* ------ Création des meeples ------  */
//    rect=new Rectangle();
//    addItem(rect);

}



void VuePlateau::ajouteTuile(Tuile *t)
{
    newVueTuile = new VueTuile(t);
    newVueTuile->activate();
    addItem(newVueTuile);
}

VueTuile *VuePlateau::getNewTuile(){
    return newVueTuile;
}

void VuePlateau::removeTuile()
{
    delete newVueTuile;
    newVueTuile=nullptr;
}
