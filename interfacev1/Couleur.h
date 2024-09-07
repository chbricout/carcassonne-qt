#pragma once
#include <string>
#include <vector>
#include <QColor>
#include "Exception.h"

class Couleur final
{
private:
	std::string nom;
    QColor color;
    friend class CouleursHandler;
public:
    Couleur(const std::string& nom, const std::string& hex);;
    const std::string& getNom() const;
    const QColor& getQColor() const;
    void afficher(std::ostream& f=std::cout) const;
};

class CouleursHandler final{
private:
	std::vector<Couleur> couleurs;
	CouleursHandler() {};
	static CouleursHandler* couleurHandler;
public:
	CouleursHandler(CouleursHandler& c) = delete;
	void operator=(const CouleursHandler& c) = delete;

	static CouleursHandler* GetInstance();

	void addCouleur(Couleur& c) { couleurs.push_back(c); };
    void addCouleur(const std::string& nom, const std::string& hex) { couleurs.push_back(Couleur(nom, hex)); };
    void supprimerCouleur(const std::string& nom);

    const std::vector<Couleur>& getCouleurs() const { return couleurs; };
    Couleur& getCouleur(const std::string& nom);
    size_t getNbCouleur() const {return couleurs.size();};
};

std::ostream& operator<<(std::ostream& f, const Couleur& c);
