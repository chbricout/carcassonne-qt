#include "Joueur.h"
#include "Tuile.h"

void Joueur::addMeeples(std::vector<Meeple> &ms)
{
    for(Meeple& m : ms){
        meeples.push_back(&m);
    }
}

void Joueur::addMeeple(Meeple *m)
{
    meeples.push_back(m);
}

void Joueur::addReserve(Tuile *t)
{
    reserve.push_back(t);
}

void Joueur::removeReserve(Tuile *t)
{
    auto it = find(reserve.begin(), reserve.end(), t);
    if(it==reserve.end()){
        throw JoueurException("tuile inexistante dans la reserve",1);
    }
    reserve.erase(it);
}

std::vector<Meeple *> Joueur::getAvailableMeeples()
{
    std::vector<Meeple*> res;
    for(auto m:meeples){
        if(!m->getEstPose() ){
            res.push_back(m);
        }
    }
    return res;
}

std::vector<Meeple *> Joueur::getPosableMeeples(Element *e)
{
    std::vector<Meeple*> res;
    for(auto m:meeples){
        if(!m->getEstPose() && m->peutEtrePoser(e)){
            res.push_back(m);
        }
    }
    return res;
}

std::vector<Meeple *> Joueur::getRetirableMeeples()
{
    std::vector<Meeple*> res;
    for(auto m:meeples){
        if(m->getEstPose() && m->peutEtreRepris()){
            res.push_back(m);
        }
    }
    return res;
}

std::vector<std::string> Joueur::getNbMeeples()
{
    std::vector<std::string>type;
    std::vector<int>count;
    int i=0, temp_count=0;
    sort(meeples.begin(), meeples.end(),compareMeeples);
    type.push_back(meeples[0]->toStr());
    for(auto* m : getAvailableMeeples()){
        if(m->toStr() != type[i]){
            i++;
            type.push_back(m->toStr());
            count.push_back(temp_count);
            temp_count=1;
        }else{
            temp_count++;
        }
    }
    count.push_back(temp_count);

    std::vector<std::string> res;
    for(int j=0; j<=i; j++){
       res.push_back(type[j] + " : "+  std::to_string(count[j]));
    }
    return res;
}

void Joueur::afficher(std::ostream &f) const
{
    f << "Joueur: " << nom << " ("<<*couleur<<") : " << meeples.size() <<" meeples";
}

std::ostream& operator<<(std::ostream& f, const Joueur& j){
    j.afficher(f);
    return f;
}
bool compareMeeples(const Meeple* e1, const Meeple* e2){
    return e1->toStr() > e2->toStr();
}
