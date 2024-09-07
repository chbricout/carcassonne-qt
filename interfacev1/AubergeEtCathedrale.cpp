#include "AubergeEtCathedrale.h"

AubergeEtCathedrale::AubergeEtCathedrale():Extension("","","")
{
    dir_path = "../extensions/aubergeEtCathedrale/";
    tuiles_file = "aubergeEtCathedrale_tuiles.xml";
    meeples_file = "aubergeEtCathedrale_meeples.xml";
    couleurs_file = "aubergeEtCathedrale_couleurs.xml";
    nom="Auberge et Cathedrale";
    addTuileBeforeShuffle=true;
}
void AubergeEtCathedrale::setupGame(Controleur *c)
{

    c->ajouterTuiles(tuiles);
    c->ajouterMeeples(meeples);

}

Meeple *AubergeEtCathedrale::meepleFromStr(const std::string &type,const std::string& img_path, const Couleur *c, unsigned int v)
{
    Meeple* m = Extension::meepleFromStr(type,img_path, c, v);
    if(!m){
     if(type=="GRANDMEEPLE"){
        m = new GrandMeeple(img_path,c, v);
     }else if(type=="ABBE"){
         m= new Abbe(img_path,c,v);
     }
    }
    return m;
}

Element *AubergeEtCathedrale::elementFromStr(const std::string& type, Orientation orient)
{
    Element* el = Extension::elementFromStr(type, orient);
    if(!el){
     if(type=="AUBERGE"){
        el = new Auberge();
     }else if(type=="CATHEDRALE"){
        el = new Cathedrale();
     }
    }
    return el;
}
