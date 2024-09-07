#include "ExtensionHandler.h"
#include "LaRiviere.h"
#include "LAbbe.h"
#include "AubergeEtCathedrale.h"

ExtensionHandler* ExtensionHandler::extensionHandler = nullptr;


ExtensionHandler::ExtensionHandler()
{
    LaRiviere* l = new LaRiviere();
    extensions.push_back(l);
    nom_extensions.push_back(l->getNom());

    Jeu* j = new Jeu();
    extensions.push_back(j);
    activeExtension("Jeu");

    LAbbe* la = new LAbbe();
    extensions.push_back(la);
    nom_extensions.push_back(la->getNom());

    AubergeEtCathedrale* aec = new AubergeEtCathedrale();
    extensions.push_back(aec);
    nom_extensions.push_back(aec->getNom());


}

ExtensionHandler *ExtensionHandler::GetInstance()
{
    if(!extensionHandler){
        extensionHandler = new ExtensionHandler();
    }
    return extensionHandler;
}

void ExtensionHandler::activeExtension(const std::string& nom)
{
    for (auto& e: extensions){
        if(e->getNom()== nom){
            std::cout << "Extensions : "<<nom<<" activee!"<<std::endl;
            e->activer();
            e->initVars();
            break;
        }
    }
    sort(extensions.begin(), extensions.end(), compareExtension);
}

bool ExtensionHandler::isActive(const std::string &nom)
{
    for(auto& e: extensions){
        if(e->estActif() && e->getNom()==nom) return true;
    }
    return false;
}

void ExtensionHandler::desactiveExtension(const std::string &nom)
{
    for (auto& e: extensions){
        if(e->getNom()== nom){
            std::cout << "Extensions : "<<nom<<" desactivee!"<<std::endl;
            e->desactiver();
            e->deleteVars();
            break;
        }
    }
}

std::vector<Extension *> ExtensionHandler::getActiveExtensions()
{
    std::vector<Extension *> res;
    for(size_t i=0; i<extensions.size(); i++){
        if(extensions[i]->estActif()) res.push_back(extensions[i]);
    }
    return res;
}

ExtensionHandler::~ExtensionHandler()
{
    for(size_t i=0; i<extensions.size(); i++){
       delete extensions[i];
    }
}
