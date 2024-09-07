#pragma once
#include <vector>
#include <algorithm>
#include "Tuile.h"
#include "Coordonnee.h"

class Tuile;

class Plateau{
private:
    std::vector<Tuile*> tuiles;
    Coordonnee hautGauche;
    Coordonnee basDroite;
public:
    Plateau():hautGauche(0,0), basDroite(0,0){};
    Plateau(const Plateau& p):hautGauche(p.hautGauche), basDroite(p.basDroite){
        for(auto t : p.tuiles){
            tuiles.push_back(t);
        }
    };

    inline size_t getNbTuiles() const {return tuiles.size();};
    inline const Coordonnee& getHautGauche() const {return hautGauche;};
    inline const Coordonnee& getBasDroite() const {return basDroite;};
    void ajouter(Tuile* t);
    void retirer(Tuile* t);
    Tuile* getTuile(const Coordonnee& c);

    using iterator = std::vector<Tuile*>::iterator;
    iterator begin(){return tuiles.begin();};
    iterator end(){return tuiles.end();};
};
