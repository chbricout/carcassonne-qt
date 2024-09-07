#include "Meeple.h"

Meeple::Meeple(const Meeple &m): valeur(m.valeur), couleur(m.couleur), image(m.img_path.c_str()), img_path(m.img_path),element(nullptr)
{
}

Meeple::Meeple(const std::string &img_path, const Couleur *c, unsigned int v) :valeur(v),couleur(c), image(img_path.c_str()), img_path(img_path)
{
}

void Meeple::poser(Element* e)
{
    if(e->canPoseMeeple(joueur)){
        element = e;
        e->poserMeeple(this);
        estPose = true;
    }
}

void Meeple::retirer()
{
    element->retirerMeeple();
    element = nullptr;

    estPose = false;
}

Meeple* Meeple::duplicate() const
{
    return new Meeple(*this);
}

bool Meeple::peutEtrePoser(Element *e) {return typeid(*e)!=typeid(Fleurs);}

void Abbe::poser(Element *e)
{
    if (typeid(*e)==typeid(EAbbaye) || typeid(*e)==typeid(Fleurs)){
        Meeple::poser(e);
    }
}

bool Abbe::peutEtrePoser(Element *e) {return typeid(*e)==typeid(EAbbaye) || typeid(*e)==typeid(Fleurs);}

Abbe *Abbe::duplicate() const
{
    return new Abbe(*this);
}

Chariot *Chariot::duplicate() const
{
    return new Chariot(*this);
}

Maire *Maire::duplicate() const
{
    return new Maire(*this);
}

GrandMeeple *GrandMeeple::duplicate() const
{
    return new GrandMeeple(*this);
}
