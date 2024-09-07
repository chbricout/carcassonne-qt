#pragma once

#include "Extension.h"

class AubergeEtCathedrale : public Extension
{
public:
    AubergeEtCathedrale();
    void setupGame(Controleur *c) override;

    Meeple* meepleFromStr(const std::string& type,const std::string& img_path, const Couleur* c, unsigned int v) override;
    Element* elementFromStr(const std::string& type, Orientation orient) override;//Une extension peut surcharger cette méthode pour rendre de nouveau type de Tuile disponible

};
