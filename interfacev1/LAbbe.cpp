#include "LAbbe.h"
#include "Meeple.h"
LAbbe::LAbbe():Extension("","../extensions/labbe/labbe_meeples.xml","")
{
    nom="L'Abbe";
    dir_path = "../extensions/labbe/";
    tuiles_file = "";
    meeples_file = "labbe_meeples.xml";
    couleurs_file = "";
    addTuileBeforeShuffle=false;
}

void LAbbe::setupGame(Controleur *c)
{

    c->ajouterMeeples(meeples);

}

Meeple *LAbbe::meepleFromStr(const std::string &type,const std::string& img_path, const Couleur *c, unsigned int v)
{
    Meeple* m = Extension::meepleFromStr(type,img_path, c, v);
    if(!m){
     if(type=="ABBE"){
        m = new Abbe(img_path,c, v);
     }
    }
    return m;
}
