#pragma once
#include <vector>
#include <map>
#include "Element.h"
#include "Tuile.h"
#include "Joueur.h"

class Tuile;
class Element;
class EVille;
class Joueur;

class Structure // Interface des Structures
{
public:

    virtual void fusionner(Structure* s) =0;
	virtual bool estComplet() const=0;
    virtual void checkComplet()=0;
	virtual bool canJoin(const Tuile& t) const=0;
	virtual void ajouter(Tuile& t)=0;
	virtual void distribuePoints() =0;
	virtual void afficher() const=0;
    virtual void removeAllMeeples() =0;
    virtual int countPoint(){return 0;};
    virtual std::vector<Joueur*> getJoueurs()=0;
    virtual std::vector<Joueur*> getGagnants()=0;

	virtual ~Structure() = default;
};


class StructureElement : public Structure {
protected:
	std::vector<Element*> elements;
	std::vector<Element*> extremites;
public:
	StructureElement(Element & e);
     void fusionner(Structure*  s) override;
     void checkComplet() override;
    inline  bool estComplet() const override { return extremites.size() == 0; };
     bool canJoin(const Tuile & t) const override;
     const Element* canConnect(const Element& e) const;
     void ajouter(Tuile & t) override;
     void distribuePoints() override {};
     void afficher() const override;
     void removeAllMeeples() override;
     std::vector<Joueur*> getJoueurs() override;
     std::vector<Joueur*> getGagnants() override;


	using iterator = std::vector<Element*>::iterator;
	iterator begin() { return extremites.begin(); };
	iterator end() { return extremites.end(); };
	iterator beginElements() { return elements.begin(); };
	iterator endElements() { return elements.end(); };

	virtual ~StructureElement() = default;
};

class StructureTuile : public Structure {
protected:
    Element* centreEl = nullptr;
	Tuile* centre = nullptr;
	std::vector<Tuile*> tuiles;
	void setCentre(Tuile& t) { centre = &t; };
public:
	StructureTuile(Element& e);
    virtual void fusionner(Structure* s) override;
    inline  bool estComplet() const override =0;
    void checkComplet() override;
    bool canJoin(const Tuile& t) const override=0;
    void ajouter(Tuile& t) override;
    void distribuePoints() override {};
    void afficher() const override;
    void removeAllMeeples() override;
    std::vector<Joueur*> getJoueurs() override;
    std::vector<Joueur*> getGagnants() override;

	using iterator = std::vector<Tuile*>::iterator;
	iterator begin() { return tuiles.begin(); };
	iterator end() { return tuiles.end(); };
	iterator beginElements() { return tuiles.begin(); };
	iterator endElements() { return tuiles.end(); };

	virtual ~StructureTuile() = default;
};

class Chateau final : public StructureElement {
public:
	Chateau(Element& e);
    int countPoint() override;
	~Chateau() override=default;
};

class Route final : public StructureElement {
public:
	Route(Element& e) ;
    int countPoint() override;

	~Route() override = default;


};

class Riviere final : public StructureElement {
public:
	Riviere(Element& e);
	~Riviere() override = default;

};

class Champ final : public StructureElement {
public:
	Champ(Element& e);
    inline  bool estComplet() const override { return false; };// nous n'implémenterons pas la verification des champs
	~Champ() override = default;

};

class Abbaye : public StructureTuile {
public:
	Abbaye(Element& e);
    bool canJoin(const Tuile& t) const override;
    bool estComplet() const override { return tuiles.size() == 9; };
    int countPoint() override;

	~Abbaye() override = default;
};

class Jardin final: public StructureTuile {
public:
	Jardin(Element& e) ;
    bool canJoin(const Tuile& t) const override;
    bool estComplet() const override;
    int countPoint() override;


	~Jardin() override = default;
};

std::vector<Tuile*> getParents(std::vector<Element*>elements);
