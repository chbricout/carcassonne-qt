#include "LaRiviere.h"
#include "Controleur.h"
#include "Element.h"
#include <algorithm>
#include <random>

Element *LaRiviere::elementFromStr(const std::string &type, Orientation orient)
{
    Element* el = Extension::elementFromStr(type, orient);
    if(!el){
        if(type == "RIVIERE"){
            el = new ERiviere(orient);
        }
    }
    return el;
}
LaRiviere::LaRiviere():Extension()
{
    nom="La Riviere";
    dir_path = "../extensions/riviere/";
    tuiles_file = "riviere_tuiles.xml";
    meeples_file = "";
    couleurs_file = "";
    addTuileBeforeShuffle=false;
}

void LaRiviere::setupGame(Controleur *c)
{
    auto rng = std::default_random_engine (std::chrono::system_clock::now().time_since_epoch().count());
    std::shuffle(++tuiles.begin(), --tuiles.end(), rng);
    c->setPremiereTuile(tuiles[0]);
    c->ajouterTuilesTop(tuiles);
}
