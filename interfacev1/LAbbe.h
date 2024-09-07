#pragma once

#include "Extension.h"

class LAbbe : public Extension
{
public:
    LAbbe();
    void setupGame(Controleur *c) override;
    void createTuiles() override {};
    void createCouleurs() override {};
    Meeple* meepleFromStr(const std::string& type,const std::string& img_path, const Couleur* c, unsigned int v) override;
};

