#include "Extension.h"


void Extension::initVars()
{
    if(colors.size()==0 && tuiles.size()==0 && meeples.size()==0){
        createCouleurs();
        createTuiles();
        createMeeples();
    }
}

void Extension::deleteVars()
{
    CouleursHandler* ch= CouleursHandler::GetInstance();
    for(Tuile* t: tuiles){
        delete t;
    }
    for(Meeple* m: meeples){
        delete m;
    }
    tuiles.clear();
    meeples.clear();
    for(Couleur* c : colors){
        try{
            ch->supprimerCouleur(c->getNom());
        }catch(Exception& e){
            std::cout << e.getMessage() << std::endl;
        }
    }
    colors.clear();
}

void Extension::createTuiles()
{
    Tuile *t=nullptr;
    Element *el=nullptr;
    std::string img_path;
    Orientation orient = Orientation::Aucune, from, to;

    QDomElement root=getRoot(dir_path+tuiles_file);
    QDomElement tuileXML = root.firstChild().toElement();
    while (!tuileXML.isNull()){
        int nbDuplicate = tuileXML.attribute("NOMBRE","1").toInt();
        QDomElement elXML = tuileXML.firstChild().toElement();
        img_path=tuileXML.attribute("IMG", "").toStdString();
        t=new Tuile(dir_path+img_path);

        while (!elXML.isNull()){
            std::string orientString = elXML.attribute("ORIENTATION", "AUCUNE").toStdString();
            orient = stringToOrientation(orientString);

            std::string type = elXML.tagName().toStdString();
            el = this->elementFromStr(type, orient);
            if(!el && type=="CONNEXIONS"){
                el=nullptr;
                QDomElement conXML = elXML.firstChild().toElement();
                while(!conXML.isNull()){
                    from = stringToOrientation(conXML.attribute("FROM").toStdString());
                    to = stringToOrientation(conXML.attribute("TO").toStdString());
                    t->getBord(from)->connectTo(t->getBord(to));
                    conXML=conXML.nextSibling().toElement();
                }
            }


            if(el) t->ajouteElement(el);
            elXML = elXML.nextSibling().toElement();
        }
        std::cout << t->getImgPath() << std::endl;
        tuiles.push_back(t);

        for(int i=1; i<nbDuplicate; i++){

            tuiles.push_back(new Tuile(*t));
        }
        tuileXML = tuileXML.nextSibling().toElement();
        t=nullptr;
    }


    std::cout << tuiles.size() <<" tuiles cree !" << std::endl;
}

Element *Extension::elementFromStr(const std::string &type, Orientation orient)
{
    Element* el =nullptr;
    if(type == "VILLE"){
        el=new EVille(orient);
    }else if(type == "CHAMP"){
        el = new EChamp(orient);
    }else if(type == "ROUTE"){
        el = new ERoute(orient);
    }else if(type == "AUBERGE"){
        el = new Auberge();
    }else if(type == "ABBAYE"){
        el = new EAbbaye();
    }else if(type == "CATHEDRALE"){
        el = new Cathedrale();
    }else if(type == "FLEURS"){
        el = new Fleurs();
    }else if(type == "BLASON"){
        el = new Blason();
    }
    return el;
}

Meeple *Extension::meepleFromStr(const std::string &type,const std::string& img_path, const Couleur* c, unsigned int v)
{
    Meeple* m=nullptr;
    if(type=="MEEPLE"){
        m = new Meeple(img_path,c, v);
    }
    return m;
}

Extension::~Extension()
{
    for(Tuile* t: tuiles){
        delete t;
    }
    for(Meeple* m: meeples){
        delete m;
    }
}

void Extension::createCouleurs(){
    CouleursHandler* ch = CouleursHandler::GetInstance();
    std::string nom, hex;
    QDomElement root=getRoot(dir_path+couleurs_file);
    QDomElement couleur = root.firstChild().toElement();

    while (!couleur.isNull()){
        nom = couleur.attribute("NOM").toStdString();
        hex = couleur.attribute("CODE").toStdString();
        ch->addCouleur(nom, hex);

        colors.push_back(&ch->getCouleur(nom));
        couleur= couleur.nextSiblingElement();
    }
    std::cout << colors.size()<< " couleur cree !" <<std::endl;
}

void Extension::createMeeples(){
    CouleursHandler* ch = CouleursHandler::GetInstance();
    Meeple * m=nullptr;
    std::string type;
    const Couleur* c;
    std::string img_path="";
    QDomElement root=getRoot(dir_path+meeples_file);
    QDomElement meepleXML = root.firstChild().toElement();

    while (!meepleXML.isNull()){
        type = meepleXML.tagName().toStdString();
        c = &ch->getCouleur(meepleXML.attribute("COULEUR").toStdString());
        img_path = meepleXML.attribute("IMG").toStdString();

        m = meepleFromStr( type,dir_path+img_path, c, meepleXML.attribute("VALEUR").toUInt());
        meeples.push_back(m);
        for(int i=1; i<meepleXML.attribute("NOMBRE").toInt(); i++){
            meeples.push_back(m->duplicate());
        }
        meepleXML= meepleXML.nextSiblingElement();
    }
    std::cout << meeples.size() << " meeples cree !" <<std::endl;
}

Orientation stringToOrientation(std::string s){
    if(s == "NORD"){
        return Orientation::Nord;
    }else if (s == "SUD"){
        return Orientation::Sud;
    }else if (s == "OUEST"){
        return Orientation::Ouest;
    }else if (s == "EST"){
        return Orientation::Est;
    }else{
        return Orientation::Aucune;
    }
}





QDomElement getRoot(std::string filename){
    QDomDocument xmlDoc;
    // Load xml file as raw data
    QFile f(filename.c_str());
    if (!f.open(QIODevice::ReadOnly ))
    {
        // Error while loading file
        std::cout << "Error while loading file" << std::endl;

    }
    // Set data into the QDomDocument before processing
    xmlDoc.setContent(&f);
    f.close();
    return xmlDoc.documentElement();
}

void Jeu::setupGame(Controleur *c)
{
    c->setPremiereTuile(tuiles[0]);
    c->ajouterTuiles(tuiles);
    c->ajouterMeeples(meeples);
}

bool compareExtension(const Extension *e1, const Extension *e2)
{
    return (e1->ajoutAvantMelange() && !e2->ajoutAvantMelange())|| e1->getNom()=="Jeu";
}
