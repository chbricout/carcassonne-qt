#include "Controleur.h"
#include "ExtensionHandler.h"

Controleur::Controleur()
{
    tour = joueurs.begin();
}



void Controleur::setupJeu()
{
    ExtensionHandler* eh = ExtensionHandler::GetInstance();
    for (auto e: eh->getActiveExtensions()){
        e->setupGame(this);
        if(e->ajoutAvantMelange()) shufflePioche();
    }
    if(premiere_tuile!=nullptr)
    {
        posePremTuile(premiere_tuile);
        pioche.enlever(premiere_tuile);
    }

}

void Controleur::ajouterJoueur(Joueur* j)
{
    for (auto c_j: joueurs){
        if(c_j->getCouleur() == j->getCouleur()){
            throw InitialisationException("Le joueur avec cette couleur existe déja", 0);
        }
    }
    joueurs.push_back(j);
    tour = joueurs.begin();
    std::cout << "joueurs ajouté ! (" << joueurs.size() << ")" << std::endl;
}

void Controleur::supprimerJoueur(std::string nom)
{
    Joueur * s_j = getJoueur(nom);
    auto s_it = find(joueurs.begin(), joueurs.end(), s_j);
    joueurs.erase(s_it);

    delete s_j;
}

void Controleur::ajouterMeeples(std::vector<Meeple*> &meeples)
{
    for(Meeple* m : meeples){
        for(auto* j: joueurs){
            if(j->getCouleur()==m->getCouleur()){
                j->addMeeple(m);
                m->distribueJoueur(j);
            }
        }
    }
}

Joueur *Controleur::getJoueur(const Couleur* c)
{
    for(auto& j : joueurs){
        if(j->getCouleur() == c) return j;
    }
    throw ControleurException("pas de joueurs correspondant a la couleur");
}

Joueur *Controleur::getJoueur(const std::string &s)
{
    for(auto& j : joueurs){
        if(j->getNom() == s) return j;
    }
    throw ControleurException("pas de joueurs correspondant au nom");
}


void Controleur::ajouterTuiles(std::vector<Tuile*>& tuiles)
{
    for (size_t i=0; i<tuiles.size();i++ ){
        pioche.ajouter(tuiles[i]);
    }
}

void Controleur::ajouterTuilesTop(std::vector<Tuile*>& tuiles)
{
    //parcours inversé du vector car on ajoute en haut de la pioche
    for(int i=tuiles.size()-1; i>=0;i-- ){
        pioche.ajouterTop(tuiles[i]);
    }
}

void Controleur::shufflePioche()
{
    pioche.shuffle();
}

void Controleur::tourSuivant()
{
    tour++;
    if(tour == joueurs.end()) tour=joueurs.begin();
    Tuile * t = pioche.pioche();
    if(t!=nullptr) (*tour)->addReserve(t);
}

bool Controleur::verifPoseTuile(Tuile *t, Joueur *j, Coordonnee c, bool isFirst)
{
    Tuile* t_test=nullptr;
    bool can_connect_to_all= true;//on verifie la compatibilité avec toute les tuiles
    bool can_connect_to_one=false;//on verifie qu'on se connecte à au moins une tuile
    if(isFirst) can_connect_to_one=true;
    if(*tour == j && plateau.getTuile(c)==nullptr){
        t->setCoordonnee(c);
        std::cout << *t <<std::endl;
        for(auto& a:c){
            if(a.estEnContact(c)){
                t_test=plateau.getTuile(a);
                if(t_test!=nullptr){
                    if(!t->canConnect(*t_test)) can_connect_to_all=false;
                    else if(!can_connect_to_one) can_connect_to_one=true;
                }
            }

        }
    }
    return can_connect_to_all && can_connect_to_one;
}

void Controleur::poseTuile(Tuile *t, Joueur *j, Coordonnee c, bool isFirst)
{
    Tuile* t_test=nullptr;
    if(verifPoseTuile(t,j,c,isFirst)){
        plateau.ajouter(t);
        for(auto& around:c){
            if(around.estEnContact(c)){
                t_test=plateau.getTuile(around);
                if(t_test){
                    t->connect(t_test);
                }
            }else{
                t_test=plateau.getTuile(around);
                if(t_test!=nullptr){
                    for(auto& s : t_test->getStructures()){
                        s->ajouter(*t);
                    }

                }

            }
        }

        t->startStructures(plateau);


    }else{
        t->setCoordonnee(0,0);
        throw CoordonneesException("Placement de tuile invalide !", 0);
    }

}

void Controleur::posePremTuile(Tuile *t)
{
    poseTuile(t, *tour, Coordonnee(0,0), true);
}

bool Controleur::isGameOver()
{
    if(pioche.estvide()){
        for(auto j : joueurs){
            if (j->getReserve().size() > 0){
                return false;
            }
        }
        return true;
    }
    return false;
}
