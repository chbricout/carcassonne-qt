#pragma once
#include <vector>
#include "Pioche.h"
#include "Plateau.h"
#include "Meeple.h"
#include "Element.h"
#include "Couleur.h"
#include "Controleur.h"
#include <QtXml>
#include <QFile>
#include <algorithm>


class Meeple;
class Controleur;


class Extension
{
protected:
    bool addTuileBeforeShuffle;
    std::string nom;
    std::string dir_path;
    bool isActif=false;
    std::vector<Tuile*> tuiles;
    std::vector<Meeple*> meeples;
    std::vector<Couleur*> colors;
    std::string tuiles_file, meeples_file, couleurs_file;
public:
    Extension()=default;
    Extension(const std::string& t, const std::string& m, const std::string& c): tuiles_file(t), meeples_file(m), couleurs_file(c){};
	inline bool estActif() const { return isActif; };
    inline void activer() { isActif=true; };
    inline void desactiver() { isActif=false; };
    inline const std::string& getNom() const {return nom;};

    virtual void setupGame(Controleur *c) = 0;
    virtual void initVars();
    virtual void deleteVars();
    virtual void createTuiles();
    virtual void createMeeples();
    virtual void createCouleurs();

    virtual Element* elementFromStr(const std::string& type, Orientation orient);//Une extension peut surcharger cette méthode pour rendre de nouveau type de Tuile disponible
    virtual Meeple* meepleFromStr(const std::string& type,const std::string& img_path, const Couleur* c, unsigned int v);

    virtual void afficher(std::ostream& f=std::cout) const {f<<nom<<std::endl;};
    bool ajoutAvantMelange() const {return addTuileBeforeShuffle;};

    virtual ~Extension();
};


class Jeu : public Extension {
public:
    Jeu():Extension()
    {
        nom="Jeu";
        dir_path = "../extensions/jeu/";
        tuiles_file = "jeu_tuiles.xml";
        meeples_file = "jeu_meeples.xml";
        couleurs_file = "jeu_couleurs.xml";
        addTuileBeforeShuffle=true;
    };
    void setupGame(Controleur *c) override ;
};

Orientation stringToOrientation(std::string s);
QDomElement getRoot(std::string filename);
bool compareExtension(const Extension* e1, const Extension* e2);


