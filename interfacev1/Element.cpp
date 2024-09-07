#include "Element.h"
#include "ExtensionHandler.h"
#include <typeinfo>
#include "Exception.h"


Element::Element(Orientation o) : orient(o)
{
    parent = nullptr;
}


void Element::connectTo(Element* e)
{
    auto it = std::find(connexions.begin(), connexions.end(), e);
    if (getCoord() == e->getCoord()) {
        if (it == connexions.end()){
            connexions.push_back(e);
            e->connectTo(this);
        }
    }
    else {
        throw BordException("Les 2 elements ne sont pas dans la meme tuile",0);
    }
}

bool Element::canPoseMeeple(Joueur *j) const{
    for (auto s :structures){
        std::vector<Joueur*> gagnants = s->getGagnants();
        if(find(gagnants.begin(), gagnants.end(), j) == gagnants.end() && gagnants.size()>0){
            return false;
        }
    }
    return true;
}

void Element::retirerMeeple(){
    if(structures.size()>0){
        for(auto s: structures){
            if(!s->estComplet()){
                if(meeple->getJoueur()!=nullptr){
                    meeple->getJoueur()->addPoints(s->countPoint());
                }
            }
        }
    }
    meeple=nullptr;
}

void Element::setParent(Tuile& p)
{
    parent = &p;
}

void Element::print(std::ostream& f) const
{
    f << parent->getCoord() << " oriente: " << orient << " possedant " << connexions.size() << " connexion(s) et "<<structures.size() <<" structures. ";
    if(structures.size()>0) f <<"("<< structures[0] <<").";
}

bool Element::canConnect(const Element& e) const
{
    if (typeid(*this) == typeid(e)) {
        switch (getCoord().getOrientationRel(e.getCoord())) {
        case Orientation::Nord:
            return orient == Orientation::Nord && e.orient == Orientation::Sud;
            break;
        case Orientation::Sud:
            return orient == Orientation::Sud && e.orient == Orientation::Nord;
            break;
        case Orientation::Ouest:
            return orient == Orientation::Ouest &&  e.orient == Orientation::Est;
            break;
        case Orientation::Est:
            return orient == Orientation::Est && e.orient == Orientation::Ouest;
            break;
        case Orientation::Aucune:
            break;
        }
    }
    return false;
}

Element* Element::canConnect(const Tuile& t) const
{
    switch (getCoord().getOrientationRel(t.getCoord())) {
    case Orientation::Nord:
        if (canConnect(*t.getBord(Orientation::Sud))) {
            return t.getBord(Orientation::Sud);
        }
        break;
    case Orientation::Sud:
        if (canConnect(*t.getBord(Orientation::Nord))) {
            return t.getBord(Orientation::Nord);
        }
        break;
    case Orientation::Ouest:
        if (canConnect(*t.getBord(Orientation::Est))) {
            return t.getBord(Orientation::Est);
        }
        break;
    case Orientation::Est:
        if (canConnect(*t.getBord(Orientation::Ouest))) {
            return t.getBord(Orientation::Ouest);
        }
        break;
    case Orientation::Aucune:
        break;
    }

    return nullptr;
}

Structure *Element::getStructureOfType(const Structure* s_test)
{
    for(auto s : structures){
        if(typeid(*s)==typeid(*s_test)){
            return s;
        }
    }
    return nullptr;
}

const Coordonnee& Element::getCoord() const
{
    if (parent != nullptr) {
        return parent->getCoord();
    }
    throw CoordonneesException("Coordonnée de la tuile parent non trouvée",0);
}

void EVille::print(std::ostream& f) const
{
    f << "Ville : ";
    Element::print(f);
}

Element* EVille::duplicate()
{
    Element* e = new EVille(orient);
    return e;
}

Structure *EVille::startStruct(Plateau& pl)
{
    if(structures.size()==0){
        Chateau * n = new Chateau(*this);
        ajouteStructure(n);
        for(auto c:connexions){
            c->ajouteStructure(n);
        }
        return n;
    }
    return nullptr;
}

void EChamp::print(std::ostream& f) const {
    f << "Champ : ";
    Element::print(f);}

Element* EChamp::duplicate()
{
    return new EChamp(orient);
}

Structure *EChamp::startStruct(Plateau& pl)
{
    if(structures.size()==0){
        Champ * n = new Champ(*this);
        ajouteStructure(n);
        for(auto c:connexions){
            c->ajouteStructure(n);
        }
        return n;
    }
    return nullptr;
}

void ERoute::print(std::ostream& f) const {
    f << "Route : ";
    Element::print(f);
}

Structure *ERoute::startStruct(Plateau& pl)
{
    if(structures.size()==0){
        Route * n = new Route(*this);
        ajouteStructure(n);
        for(auto c:connexions){
            c->ajouteStructure(n);
        }
        return n;
    }
    return nullptr;
}



void ERiviere::print(std::ostream& f) const {
    f << "Riviere : ";
    Element::print(f);
}

Structure *ERiviere::startStruct(Plateau& pl)
{
    if(structures.size()==0){
        Riviere * n = new Riviere(*this);
        ajouteStructure(n);
        for(auto c:connexions){
            c->ajouteStructure(n);
        }
        return n;
    }
    return nullptr;
}

void Auberge::print(std::ostream& f) const {
    f << "Auberge : ";
    Element::print(f);
}

void Cathedrale::print(std::ostream& f) const {
    f << "Cathedrale : ";
    Element::print(f);
}

void EAbbaye::print(std::ostream& f) const {
    f << "Abbaye : ";
    Element::print(f);
}

Structure *EAbbaye::startStruct(Plateau& pl)
{
    if(structures.size()==0){
        Tuile * current = nullptr;
        Abbaye * n = new Abbaye(*this);
        for(auto& a:parent->getCoord()){
            current = pl.getTuile(a);
            if(current!=nullptr) {
                n->ajouter(*current);
            }
        }
        parent->ajouteStructure(n);
        return n;
    }
    return nullptr;
}

void Fleurs::print(std::ostream& f) const {
    f << "Fleur : ";
    Element::print(f);
}

bool Fleurs::canPoseMeeple(Joueur *j) const
{
    ExtensionHandler* eh=ExtensionHandler::GetInstance();
    return eh->isActive("L'Abbe");
}

Structure *Fleurs::startStruct(Plateau& pl)
{
    if(ExtensionHandler::GetInstance()->isActive("L'Abbe") && structures.size()==0){
        Tuile * current = nullptr;
        Jardin * n = new Jardin(*this);
        for(auto& a:parent->getCoord()){
            current = pl.getTuile(a);
            if(current) n->ajouter(*current);
        }
        return n;
    }
    return nullptr;
}

void Blason::print(std::ostream& f) const {
    f << "Blason : ";
    Element::print(f);
}
