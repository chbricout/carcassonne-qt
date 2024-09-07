#include "FenetreChoixExtension.h"
#include "ExtensionHandler.h"

FenetreChoixExtension::FenetreChoixExtension(Controleur * c) : QWidget(), controleur(c)
{
    layout = new QVBoxLayout(this);
    layoutBtnBar = new QHBoxLayout();

    ExtensionHandler *eh = ExtensionHandler::GetInstance();
    QCheckBox* check = nullptr;

    for(auto& name : eh->getExtensionsNames()){

        check = new QCheckBox(name.c_str(),this);
        check->setChecked(eh->isActive(name));
        check->setCursor(Qt::PointingHandCursor);
        check->setToolTip("Permet de choisir cette extension");
        layout->addWidget(check);
        extensionsChecks.push_back(check);
    }


    Enregistrer = new QPushButton("Enregistrer", this);

    Enregistrer->setToolTip("Permet d'enregistrer un nouveau joueur");
    Enregistrer->setCursor(Qt::PointingHandCursor);
    layoutBtnBar->addWidget(Enregistrer);
// inscrire un joueur
    Annuler = new QPushButton("Annuler", this);

    Annuler->setToolTip("Annuler");
    Annuler->setCursor(Qt::PointingHandCursor);
    layoutBtnBar->addWidget(Annuler);
    layout->addLayout(layoutBtnBar);
    QObject::connect(Annuler, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(Enregistrer, SIGNAL(clicked()), this, SLOT(save()));
}

void FenetreChoixExtension::save()
{
    ExtensionHandler *eh = ExtensionHandler::GetInstance();

    for(auto& check : extensionsChecks){
        if(check->isChecked()) eh->activeExtension(check->text().toStdString());
        else eh->desactiveExtension(check->text().toStdString());
    }
};

