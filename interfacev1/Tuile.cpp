#include "Tuile.h"
#include "Exception.h"

std::ostream& operator<<(std::ostream& f, const Tuile& t)
{
	t.print(f);
	return f;
}

Tuile::Tuile(const Tuile& t): coord(0, 0), image_path(t.image_path), image(image_path.c_str())
{
	for (auto e : t.elements) {
		ajouteElement(e->duplicate());
	}
	Element* toConnect = nullptr;
	for (auto e : t.get4Bords()) {
		toConnect = getBord(e->getOrientation());
		for (auto c : e->getConnexions()) {
			toConnect->connectTo(getBord(c->getOrientation()));
		}
	}
}

Tuile::~Tuile()
{
    for (Element* e: elements) {
        delete e;
	}
}

void Tuile::rotation()
{
    for (auto* e : elements) {
        switch(e->getOrientation()) {
		case Orientation::Nord:
            e->setOrientation(Orientation::Est);
			break;
		case Orientation::Est:
            e->setOrientation(Orientation::Sud);
			break;
		case Orientation::Sud:
            e->setOrientation(Orientation::Ouest);
			break;
		case Orientation::Ouest:
            e->setOrientation(Orientation::Nord);
			break;
        case Orientation::Aucune:
            break;
		}
    }
    QTransform trans;
    image = image.transformed(trans.rotate(90));

}

void Tuile::ajouteElement(Element* e)
{
	e->setParent(*this);
	elements.push_back(e);
}

void Tuile::setCoordonnee(int x, int y)
{
	coord.set(x, y);
}

void Tuile::setCoordonnee(const Coordonnee& c)
{
    coord.set(c);
}

std::vector<Structure *> Tuile::getAllStructures()
{
    std::vector<Structure*>res;
    for(auto* t: structures){
        res.push_back(t);
    }
    for(auto* e: elements){
        for(auto* t: e->getStructures()){
            if(find(res.begin(), res.end(), t) == res.end()){
                res.push_back(t);
            }
        }
    }
    return res;
}

void Tuile::printDetail(std::ostream& f) const
{
    f << coord << " elle contient : " << elements.size() << " Elements et " << structures.size() << " structures ("<<image_path <<")\n";
	for (auto it = elements.begin(); it != elements.end(); it++) {
		f << "	- " << **it << "\n";
	}
}

void Tuile::print(std::ostream& f) const
{
	f << coord << std::endl;

}

bool Tuile::hasBord(Orientation o) const
{
	for (auto it = elements.begin(); it <= elements.end(); it++) {
		if ((*it)->getOrientation() == o) {
			return true;
		}
	}
    return false;
}

bool Tuile::hasBlason() const
{
    for(auto e: elements){
        if(typeid(*e)==typeid(Blason)) return true;
    }
    return false;
}

bool Tuile::a4Bords() const
{
	bool bordN = false, bordS = false, bordE = false, bordO = false;
	for (auto it = elements.begin(); it != elements.end(); it++) {
		switch ((*it)->getOrientation()) {
		case Orientation::Nord:
			bordN = true;
			break;
		case Orientation::Sud:
			bordS = true;
			break;
		case Orientation::Est:
			bordE = true;
			break;
		case Orientation::Ouest:
			bordO = true;
			break;
		}
	}
	return bordN && bordS && bordO && bordE;
}



Element* Tuile::getBord(Orientation o) const
{
	for (auto it = elements.begin(); it != elements.end(); it++) {
		if ( (* it)->getOrientation() == o) {
			return *it;
		}
	}
    throw BordException("Bord inexistant!",0);
}

std::vector<Element*> Tuile::get4Bords()
{
	std::vector<Element*> res;
	for (auto e : elements) {
		if (e->getOrientation() != Orientation::Aucune) {
			res.push_back(e);
		}
	}
	return res;
}

std::vector<const Element*> Tuile::get4Bords() const
{
	std::vector<const Element*> res;
	for (auto e : elements) {
		if (e->getOrientation() != Orientation::Aucune) {
			res.push_back(e);
		}
	}
	return res;
}

bool Tuile::canConnect(const Tuile& t) const
{
	switch (coord.getOrientationRel(t.coord)) {
	case Orientation::Nord:
		return getBord(Orientation::Nord)->canConnect(*t.getBord(Orientation::Sud));
		break;
	case Orientation::Sud:
		return  getBord(Orientation::Sud)->canConnect(*t.getBord(Orientation::Nord));
		break;
	case Orientation::Ouest:
		return  getBord(Orientation::Ouest)->canConnect(*t.getBord(Orientation::Est));
		break;
	case Orientation::Est:
		return  getBord(Orientation::Est)->canConnect(*t.getBord(Orientation::Ouest));
		break;
	}
    return false;
}

void Tuile::connect(Tuile *t)
{
    for(auto* s:t->getAllStructures()){
        s->ajouter(*this);
    }
}

std::vector<Structure*> Tuile::startStructures(Plateau& pl)
{
    Structure * s=nullptr;
    std::vector<Structure*>res;

    for(auto* e:elements){
        s=e->startStruct(pl);
        if(s){
            res.push_back(s);
        }
    }
    return res;
}

void Tuile::checkStructuresComplet()
{
    for(auto& s: getAllStructures()){
        s->checkComplet();
    }
}
