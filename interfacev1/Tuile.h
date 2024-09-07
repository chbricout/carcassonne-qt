#pragma once
#include <vector>
#include <iostream>
#include "Element.h"
#include "Coordonnee.h"
#include "Structure.h"
#include "Plateau.h"
#include <algorithm>
#include <QPixmap>

class Structure;
class Element;

class Tuile final
{
private:
    std::string image_path="";
    QPixmap image;
	Coordonnee coord;
	std::vector <Element*> elements;
	std::vector <Structure*> structures;
public:
    Tuile(const std::string& img_path) :  image_path(img_path), image(image_path.c_str()),coord(0, 0)
     {
        image=image.scaled(QSize(60,60));
    };
    Tuile(int x, int y, const std::string& img_path) : image_path(img_path), coord(x,y) {};
    Tuile(const Tuile& t);

	~Tuile();

	void rotation();
	void ajouteElement(Element* e);
	void setCoordonnee(int x, int y);
	void setCoordonnee(const Coordonnee& c);
    std::vector<Structure*> getAllStructures();
    void ajouteStructure(Structure* s) {
        auto it_s = find(structures.begin(), structures.end(), s);
        if(it_s==structures.end()) structures.push_back(s);
    };
    void supprimeStructure(Structure* s) {
        auto it_s = find(structures.begin(), structures.end(), s);

        if (it_s != structures.end()) {
			structures.erase(it_s);
		}
	}


    void printDetail(std::ostream& f=std::cout) const;
    void print(std::ostream& f=std::cout) const;
    inline const std::string& getImgPath(){return image_path;};
    inline QPixmap& getImg(){return image;};

    inline Coordonnee& getCoord()  { return coord; };
    inline const Coordonnee& getCoord() const { return coord; };

	inline size_t getNbElement() const { return elements.size(); };
    inline std::vector <Structure*> getStructures() const { return structures; };
	bool hasBord(Orientation o) const;
    bool hasBlason() const;
	bool a4Bords() const;
	Element* getBord(Orientation o) const;
	std::vector<Element*> get4Bords();
	std::vector<const Element*> get4Bords() const;

	bool canConnect(const Tuile& t) const;
    void connect(Tuile* t) ;
    std::vector<Structure*> startStructures(Plateau& pl);
    void checkStructuresComplet();

	using iterator = std::vector<Element*>::iterator;
	iterator begin(){return elements.begin();};
	iterator end(){return elements.end();};
};

std::ostream& operator<<(std::ostream& f, const Tuile& t);
