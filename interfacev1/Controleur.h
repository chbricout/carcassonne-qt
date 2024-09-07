#pragma once
#include "Plateau.h"
#include "Pioche.h"
#include "Extension.h"
#include "Joueur.h"
#include "Exception.h"
#include "Structure.h"
#include "Tuile.h"
#include "VuePlateau.h"
#include <vector>
#include <algorithm>
#include <random>

class Extension;
class ExtensionHandler;


class Controleur{
private:
    Plateau plateau;
    VuePlateau *v_plateau=nullptr;
    Pioche pioche;
    std::vector<Joueur*> joueurs;
    std::vector<Joueur*>::iterator tour;
    Tuile * premiere_tuile = nullptr;


public:
    Controleur();
    ~Controleur()=default;

    void setupJeu();

    void ajouterJoueur(Joueur* j);
    void supprimerJoueur(std::string nom);

    void ajouterMeeples(std::vector<Meeple*>& meeples);
    Joueur* getJoueur(const Couleur* c);
    Joueur* getJoueur(const std::string& s);
    inline std::vector<Joueur*> getJoueurs(){return joueurs;};


    void ajouterTuiles(std::vector<Tuile*>& tuiles);
    void ajouterTuilesTop(std::vector<Tuile*>& tuiles);
    inline void setPremiereTuile(Tuile* t){premiere_tuile=t;};
    void shufflePioche();

    void tourSuivant();
    bool verifPoseTuile(Tuile* t, Joueur* j, Coordonnee c, bool isFirst=false);
    void poseTuile(Tuile* t, Joueur* j, Coordonnee c, bool isFirst=false);
    void posePremTuile(Tuile* t);
    bool isGameOver();

    inline void setVuePlateau(VuePlateau* vp){v_plateau=vp;};
    inline VuePlateau* getVuePlateau(){return v_plateau;};

    inline Pioche& getPioche()  {return pioche;};
    inline Plateau& getPlateau()  {return plateau;};
    inline Joueur* getTour()  {return *tour;};
};

