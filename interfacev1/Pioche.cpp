#include "Pioche.h"

void Pioche::afficher(std::ostream& f) const
{
	for (auto t : tuiles) {
		t->printDetail(f);
	}
}

void Pioche::ajouter(Tuile* t)
{
    if(find(tuiles.begin(), tuiles.end(),t) == tuiles.end()) tuiles.push_back(t);
}

void Pioche::ajouterTop(Tuile *t)
{
    tuiles.insert(tuiles.begin(), t);
}

void Pioche::enlever(Tuile *t)
{
    auto it = find(tuiles.begin(), tuiles.end(),t);
    if(*it == t) tuiles.erase(it);
}

void Pioche::shuffle()
{
    auto rng = std::default_random_engine  (std::chrono::system_clock::now().time_since_epoch().count());
    std::shuffle(tuiles.begin(), tuiles.end(), rng);
}

Tuile *Pioche::pioche()
{
    Tuile* t= tuiles[0];
    if(tuiles.size() > 0){
        std::cout<< "reste "<<tuiles.size()-1<<" Tuiles" <<std::endl;
        auto it = find(tuiles.begin(), tuiles.end(), t);
        if(it != tuiles.end()){
            tuiles.erase(it);
        }
        return t;
    }
    return nullptr;
}

std::ostream& operator<<(std::ostream& f, const Pioche& p)
{
	p.afficher(f);
	return f;
}
