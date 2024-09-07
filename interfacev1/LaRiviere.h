#pragma once
#include "Extension.h"
#include <chrono>

class Controleur;

class LaRiviere : public Extension{
public:
    LaRiviere();
    void setupGame(Controleur *c) override;
    void createMeeples() override {};
    void createCouleurs() override {};
    Element* elementFromStr(const std::string& type, Orientation orient) override;
};

