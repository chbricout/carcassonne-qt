#pragma once
#include "Meeple.h"
#include "Couleur.h"
#include <iostream>
#include "Element.h"

class Meeple;
class Tuile;
class Element;

class Joueur
{
private:
	std::string nom;
	std::vector<Meeple*> meeples;
    std::vector<Tuile*> reserve;
    const Couleur* couleur=nullptr;
	unsigned int points = 0;
public:
    Joueur(std::string n, const Couleur* c):nom(n), couleur(c){};
    Joueur(const Joueur& j) =delete;
	inline void setNom(std::string& n) { nom = n; };
    inline void addPoints(unsigned int n){points+=n;};
    void addMeeples(std::vector<Meeple>& ms);
    void addMeeple(Meeple* m);
    void addReserve(Tuile* t);
    void removeReserve(Tuile* t);

    inline std::vector<Tuile*>& getReserve() { return reserve; };
    inline unsigned int getPoints() const{return points;};
    inline const std::vector<Meeple*>& getMeeples(){return meeples;};
    std::vector<Meeple*> getAvailableMeeples();
    std::vector<Meeple*> getPosableMeeples(Element *e);
    std::vector<Meeple*> getRetirableMeeples();


    std::vector<std::string> getNbMeeples();
    inline const std::string& getNom() const { return nom; };
    inline const Couleur* getCouleur() const { return couleur; };
    void afficher(std::ostream& f=std::cout) const;

};


std::ostream& operator<<(std::ostream& f, const Joueur& j);
bool compareMeeples(const Meeple* e1, const Meeple* e2);
