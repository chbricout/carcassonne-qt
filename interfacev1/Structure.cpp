
#include "Structure.h"
#include <typeinfo>
#include "Exception.h"

StructureElement::StructureElement(Element &e)
{
    e.ajouteStructure(this);
    elements.push_back(&e);
    extremites.push_back(&e);
    for (auto c : e.getConnexions())
    {
        auto it = find(elements.begin(), elements.end(), c);
        if (it == elements.end())
        {
            c->ajouteStructure(this);
            elements.push_back(c);
            extremites.push_back(c);
        }
    }
}

void StructureElement::fusionner(Structure* s)
{
    StructureElement* se = dynamic_cast<StructureElement*>(s);
    if (se) {
        std::vector<const Element*> extremASupp;
        std::vector<Element*> extAAjouter, elmAAjouter;
        this->afficher();

        for (auto e : se->elements) {
            if (find(elements.begin(), elements.end(), e) == elements.end()) elmAAjouter.push_back(e);
            e->supprimeStructure(s);
            e->ajouteStructure(this);
        }

        for (auto e : se->extremites) {
            auto a_supp= canConnect(*e);
            if (find(extremites.begin(), extremites.end(), e) == extremites.end()) {

                if (a_supp) {
                    extremASupp.push_back(a_supp);
                }
                else {
                    extAAjouter.push_back(e);
                }
            }else if (a_supp){
                    extremASupp.push_back(a_supp);
            }
        }
        for (auto e : elmAAjouter) {
            elements.push_back(e);
        }

        for (auto e : extremASupp) {
            auto it = find(extremites.begin(), extremites.end(), e);
            if(it != extremites.end()) extremites.erase(it);
        }

        for (auto e : extAAjouter) {
            extremites.push_back(e);
        }
    }
}

void StructureElement::checkComplet()
{
    if(estComplet()){
        auto joueurs = getGagnants();
        for(auto j : joueurs){
            j->addPoints(countPoint());
        }
        removeAllMeeples();
    }
}

Chateau::Chateau(Element &e) : StructureElement(e)
{
    if (typeid(e) != typeid(EVille))
    {
        throw BordException("Type de l'element incompatible avec la structure Chateau",0);
    }
}

int Chateau::countPoint()
{
    int res =0;
    for(auto t : getParents(elements)){
        res+=2;
        if (t->hasBlason()){
            res+=2;
        }
    }
    return res;
};

Route::Route(Element &e): StructureElement(e) {
    if (typeid(e) != typeid(ERoute))
    {
        throw BordException("Type de l'element incompatible avec la structure Route",0);
    }
}

int Route::countPoint()
{
    int res =0;
    for(auto t : getParents(elements)){
        res+=1;
    }
    return res;
}

Riviere::Riviere(Element& e) : StructureElement(e) {
    if (typeid(e) != typeid(ERiviere))
    {
        throw BordException("Type de l'element incompatible avec la structure Riviere",0);
    }
};

Champ::Champ(Element& e) : StructureElement(e) {
    if (typeid(e) != typeid(EChamp))
    {
        throw BordException("Type de l'element incompatible avec la structure Champ",0);
    }
}

Abbaye::Abbaye(Element& e): StructureTuile(e) {
    if (typeid(e) != typeid(EAbbaye))
    {
        throw BordException("Type de l'element incompatible avec la structure Abbaye",0);
    }
}

bool Abbaye::canJoin(const Tuile& t) const
{
    return centre->getCoord().estAdjacent(t.getCoord());
}

int Abbaye::countPoint()
{
    return tuiles.size();
}

bool StructureElement::canJoin(const Tuile &t) const
{
    for (auto e : extremites)
    {
        if (e->canConnect(t))
        {
            return true;
        }
    }
    return false;
}

const Element* StructureElement::canConnect(const Element& e) const
{
    for (auto ext : extremites) {
        if (ext->canConnect(e)) {
            return ext;
        }
    }
    return nullptr;
}

void StructureElement::afficher() const
{
    std::cout<<"\n__________________________________________________________________________________"<<std::endl;
    std::cout << "Elements de la structure : \n-----------------------" << std::endl;
    for (auto e : elements)
    {
        std::cout << *e << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Extremites de la structure : \n-----------------------" << std::endl;
    for (auto e : extremites)
    {
        std::cout << *e << std::endl;
    }
    std::cout << "__________________________________________________________________________________\n" << std::endl;

}

void StructureElement::removeAllMeeples()
{
    for(auto e: elements){
       if(e->getMeeple()!=nullptr) e->getMeeple()->retirer();
    }
}

std::vector<Joueur *> StructureElement::getJoueurs()
{
    std::vector<Joueur *> res;
    for(auto e : elements){
        if(e->getMeeple() != nullptr && e->getMeeple()->getJoueur() != nullptr ){
            auto it = find(res.begin(), res.end(), e->getMeeple()->getJoueur());
            if(it==res.end()){
                res.push_back(e->getMeeple()->getJoueur());
            }
        }
    }

    return res;
}

std::vector<Joueur *> StructureElement::getGagnants()
{
    std::map<Joueur*, int> puissance;
    std::vector<Joueur *> res;
    int max=0;
    for(auto e : elements){
        if(e->getMeeple() != nullptr && e->getMeeple()->getJoueur() != nullptr ){
            auto it = puissance.find(e->getMeeple()->getJoueur());
            if(it!=puissance.end()){
                puissance[e->getMeeple()->getJoueur()]+=e->getMeeple()->getValeur();
            }else{
                puissance[e->getMeeple()->getJoueur()]=e->getMeeple()->getValeur();
            }

            if(max < puissance[e->getMeeple()->getJoueur()]){
                max = puissance[e->getMeeple()->getJoueur()];
            }
        }
    }
    for (const auto& [key, value]: puissance){
        if(value==max) res.push_back(key);
    }
    return res;
}

void StructureElement::ajouter(Tuile &t)
{
    Element *e=nullptr;
    Element *new_e=nullptr;
    Structure *already_e=nullptr;
    for (size_t i = 0; i < extremites.size(); i++)
    {
        e = extremites[i];
        new_e = e->canConnect(t);
        if (new_e != nullptr )
        {
            already_e = new_e->getStructureOfType(this);
            if(already_e!=nullptr ){
                fusionner(already_e);
                if(already_e != this) delete already_e;
            }else{
                elements.push_back(new_e);
                new_e->ajouteStructure(this);
                for (auto& c : new_e->getConnexions())
                {
                    auto it_con = find(elements.begin(), elements.end(), c);
                    if (it_con == elements.end())
                    {
                        elements.push_back(c);

                        c->ajouteStructure(this);
                        extremites.push_back(c);
                    }
                }

                auto it = find(extremites.begin(), extremites.end(), e);
                extremites.erase(it);
            }

            break;
        }
    }
}


Jardin::Jardin(Element& e) : StructureTuile(e)
{
    setCentre(e.getParent());
}

bool Jardin::canJoin(const Tuile &t) const
{
    return centre->getCoord().estAdjacent(t.getCoord());
}

bool Jardin::estComplet() const { return tuiles.size() == 9; }

int Jardin::countPoint()
{
    return tuiles.size();
}



StructureTuile::StructureTuile(Element& e)
{
    centreEl = &e;
    e.getParent().ajouteStructure(this);
    e.ajouteStructure(this);
    centre = &e.getParent();
    tuiles.push_back(centre);
}

void StructureTuile::fusionner(Structure* s)
{
    if (typeid(this) == typeid(s)) {
        StructureTuile* st = dynamic_cast<StructureTuile*>(s);
        if (st) {
            for (auto t : *st) {
                if (find(tuiles.begin(), tuiles.end(), t) == tuiles.end()) tuiles.push_back(t);
                t->supprimeStructure(s);
                t->ajouteStructure(this);
            }
        }
    }
}

void StructureTuile::checkComplet()
{
    if(estComplet()){
        if(centreEl->getMeeple() != nullptr) centreEl->getMeeple()->getJoueur()->addPoints(countPoint());
        removeAllMeeples();
    }
}

void StructureTuile::ajouter(Tuile& t)
{
    if (canJoin(t)) {
        auto it = find(tuiles.begin(), tuiles.end(), &t);
        if (it == tuiles.end()) tuiles.push_back(&t);
    }
}



void StructureTuile::afficher() const
{
    std::cout << "\n__________________________________________________________________________________" << std::endl;
    std::cout << "centre de la structure : "<< *centre << std::endl;

    std::cout << std::endl;
    std::cout << "Tuiles de la structure : \n-----------------------" << std::endl;
    for (auto e : tuiles)
    {
        std::cout << *e << std::endl;
    }
    std::cout << "__________________________________________________________________________________\n" << std::endl;
}

void StructureTuile::removeAllMeeples()
{
    if(centreEl->getMeeple()!=nullptr)centreEl->getMeeple()->retirer();
}

std::vector<Joueur *> StructureTuile::getJoueurs()
{
    std::vector<Joueur *> res;
    if(centreEl->getMeeple()->getJoueur() != nullptr){
        res.push_back(centreEl->getMeeple()->getJoueur());
    }
    return res;
}

std::vector<Joueur *> StructureTuile::getGagnants()
{
    if(centreEl->getMeeple()!=nullptr){
        return std::vector<Joueur *>({centreEl->getMeeple()->getJoueur()});
    }
    return std::vector<Joueur *>();
}

std::vector<Tuile*> getParents(std::vector<Element*>elements){
    std::vector<Tuile*> res;
    for(auto e:elements){
        auto it = find(res.begin(), res.end(), &e->getParent());
        if(it==res.end()){
            res.push_back(&e->getParent());
        }
    }
    return res;
}
