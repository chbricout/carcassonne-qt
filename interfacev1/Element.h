#pragma once

#include "Orientation.h"
#include "Coordonnee.h"
#include <vector>
#include <iostream>
#include "Tuile.h"
#include <algorithm>
#include "Meeple.h"
#include "Structure.h"

class Tuile;
class Meeple;
class Structure;
class Plateau;

class Element
{
protected:
	Orientation orient;
	std::vector<Element*> connexions;
    Tuile* parent=nullptr;
    Meeple* meeple=nullptr;
    std::vector <Structure*> structures;
public:
	Element()=default;
	Element(Orientation o);

	inline void setOrientation(Orientation o) { orient = o; };
	void setParent(Tuile& p);

	inline const std::vector<Element*>& getConnexions() const { return connexions; };
    inline std::vector<Structure*>& getStructures(){return structures;};
    Structure *getStructureOfType(const Structure* s_test);
	inline Tuile& getParent() { return *parent; };
    inline Meeple* getMeeple() {if(meeple !=nullptr) return meeple; return nullptr;};
	inline std::vector<Element*>& getConnexions() { return connexions; };
	inline Orientation getOrientation() const { return orient; };
	const Coordonnee& getCoord() const ;

	void connectTo(Element* e);
    virtual bool canPoseMeeple(Joueur *j) const;;
    inline virtual void poserMeeple(Meeple* m) { meeple = m; };
    virtual void retirerMeeple();;
	virtual void print(std::ostream& f) const;
    virtual std::string getNom()const=0;
	virtual bool canConnect(const Element& e) const;
	virtual Element* canConnect(const Tuile& t) const;
    inline void ajouteStructure(Structure* s) {
        auto it_s = find(structures.begin(), structures.end(), s);
        if(it_s==structures.end()) structures.push_back(s);
    };
    inline void supprimeStructure(Structure* s) {
        auto it_s = find(structures.begin(), structures.end(), s);

        if (it_s != structures.end()) {
            structures.erase(it_s);
        }
    }
    virtual Structure* startStruct(Plateau& pl){return nullptr;};

	virtual Element* duplicate()=0;
	virtual ~Element() = default;
};

class EVille final : public Element  {
private:
public:
	EVille(Orientation o) :Element(o) {};
	void print(std::ostream& f) const override ;
	Element* duplicate() override;
    inline std::string getNom()const override{return "Ville";};

    Structure* startStruct(Plateau& pl) override;

	~EVille() override = default;
};

class EChamp final : public Element  {
public:
	EChamp(Orientation o) :Element(o) {};
	void print(std::ostream& f) const override;
	Element* duplicate() override;
    inline std::string getNom()const override{return "Champ";};

    Structure* startStruct(Plateau& pl) override;

	~EChamp() override = default;
};

class ERoute final : public Element {
public:
	ERoute(Orientation o) :Element(o) {};
	void print(std::ostream& f) const override;
	Element* duplicate() override { return new ERoute(orient); };
    inline std::string getNom()const override{return "Route";};

    Structure* startStruct(Plateau& pl) override;

	~ERoute() override = default;
};

class ERiviere final : public Element {
public:
	ERiviere(Orientation o) :Element(o) {};
	void print(std::ostream& f) const override;
	Element* duplicate() override { return new ERiviere(orient); };
    inline std::string getNom()const override{return "Riviere";};
    inline bool canPoseMeeple(Joueur *j) const override{return false;};

    Structure* startStruct(Plateau& pl) override;

	~ERiviere() override = default;
};

class Auberge final: public Element {
public:
	Auberge() :Element(Orientation::Aucune) {};
	void print(std::ostream& f) const override;;
    inline bool canConnect(const Element&) const override { return false; };
	Element* duplicate() override { return new Auberge(); };
    inline std::string getNom()const override{return "Auberge";};
    inline bool canPoseMeeple(Joueur *j) const override{return false;};

	~Auberge() override = default;
};

class Cathedrale final : public Element {
public:
	Cathedrale() :Element(Orientation::Aucune) {};
	void print(std::ostream& f) const override;;
    inline bool canConnect(const Element&) const override { return false; };
	Element* duplicate() override { return new Cathedrale(); };
    inline std::string getNom()const override{return "Cathedrale";};
    inline bool canPoseMeeple(Joueur *j) const override{return false;};

	~Cathedrale() override = default;
};

class EAbbaye final : public Element {
public:
	EAbbaye() :Element(Orientation::Aucune) {};
	void print(std::ostream& f) const override;;
    inline bool canConnect(const Element&) const override { return false; };
	Element* duplicate() override { return new EAbbaye(); };
    inline std::string getNom()const override{return "Abbaye";};

    Structure* startStruct(Plateau& pl) override;

	~EAbbaye() override = default;
};

class Fleurs final: public Element {
public:
	Fleurs() :Element(Orientation::Aucune) {};
	void print(std::ostream& f) const override;;
    inline bool canConnect(const Element&) const override { return false; };
	Element* duplicate() override { return new Fleurs(); };
    inline std::string getNom()const override{return "Fleurs";};
    inline bool canPoseMeeple(Joueur *j) const override;

    Structure* startStruct(Plateau& pl) override;

	~Fleurs() override = default;
};

class Blason final: public Element {
public:
	Blason() :Element(Orientation::Aucune) {};
	void print(std::ostream& f) const override;;
    inline bool canConnect(const Element&) const override { return false; };
	Element* duplicate() override { return new Blason(); };
    inline std::string getNom()const override{return "Blason";};
    inline bool canPoseMeeple(Joueur *j) const override{return false;};

	~Blason() override = default;
};


inline std::ostream& operator<<(std::ostream& f, const Element& e) { e.print(f); return f; };
