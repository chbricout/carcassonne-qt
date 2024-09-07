#include "Couleur.h"

CouleursHandler* CouleursHandler::couleurHandler = nullptr;

CouleursHandler* CouleursHandler::GetInstance()
{
    if (couleurHandler == nullptr){
        couleurHandler = new CouleursHandler();
    }
    return couleurHandler;
}

void CouleursHandler::supprimerCouleur(const std::string& nom)
{
    for(size_t i=0; i<couleurs.size(); i++){
        if(couleurs[i].nom == nom){
            couleurs.erase(couleurs.begin()+i);
            return;
        }
    }
    throw CouleurException("suppresion d'une couleur inexistante",1);


}

Couleur& CouleursHandler::getCouleur(const std::string &nom)
{
    for(Couleur& c : couleurs){
        if(c.nom == nom){
            return c;
        }
    }
    throw CouleurException("La couleur n'existe pas",1);
}

Couleur::Couleur(const std::string &nom, const std::string &hex) :nom(nom), color(hex.c_str()) {}

const std::string &Couleur::getNom() const { return nom; }

const QColor &Couleur::getQColor() const { return color; }

void Couleur::afficher(std::ostream &f) const
{
    f<<"Couleur : "<< nom;
}


std::ostream& operator<<(std::ostream& f, const Couleur& c){
    c.afficher(f);
    return f;
}
