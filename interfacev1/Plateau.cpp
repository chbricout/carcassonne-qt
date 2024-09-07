#include "Plateau.h"


void Plateau::ajouter(Tuile* t){
    if(t->getCoord().getX()>basDroite.getX()) basDroite.setX(t->getCoord().getX());
    else if(t->getCoord().getX()<hautGauche.getX()) hautGauche.setX(t->getCoord().getX());

    if(t->getCoord().getY()>basDroite.getY()) basDroite.setY(t->getCoord().getY());
    else if(t->getCoord().getY()<hautGauche.getY()) hautGauche.setY(t->getCoord().getY());
    tuiles.push_back(t);
}

void Plateau::retirer(Tuile* t){
    auto it = find(tuiles.begin(), tuiles.end(), t);
    if(*it==t){
        tuiles.erase(it);
    }
}

Tuile* Plateau::getTuile(const Coordonnee& c){
    for(auto t: tuiles){
        if (t->getCoord() == c){
            return t;
        }
    }
    return nullptr;
}
