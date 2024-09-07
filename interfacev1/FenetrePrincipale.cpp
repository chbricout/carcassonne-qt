
#include "FenetrePrincipale.h"

#include<QLabel>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMainWindow>
#include "ExtensionHandler.h"

FenetrePrincipale::FenetrePrincipale() : QWidget()
{
    ExtensionHandler::GetInstance();
    setFixedSize(1000, 750);

    NewJoueur = new QPushButton("Joueurs", this);

    NewJoueur->setToolTip("Permet d'ajouter un nouveau joueur");
    NewJoueur->setCursor(Qt::PointingHandCursor);
    NewJoueur->move(50, 125);



    QObject::connect(NewJoueur, SIGNAL(clicked()), this, SLOT(AfficherPageNewJoueur()));

    ChoixExtensions = new QPushButton("Extensions", this);

    ChoixExtensions->setToolTip("Permet de gérer les extensions");
    ChoixExtensions->setCursor(Qt::PointingHandCursor);
    ChoixExtensions->move(50,250);

    QObject::connect(ChoixExtensions, SIGNAL(clicked()), this, SLOT(AfficherPageExtensions()));





    StartPartie = new QPushButton("Démarrer la Partie", this);

    StartPartie->setToolTip("Permet de lancer une partie");
    StartPartie->setCursor(Qt::PointingHandCursor);
    StartPartie->move(50, 375);
    QObject::connect(StartPartie, SIGNAL(clicked()), this, SLOT(AfficherPageJeu()));





    Quitter = new QPushButton("Quitter", this);

    Quitter->setToolTip("Quitte le programme");
    Quitter->setCursor(Qt::PointingHandCursor);
    Quitter->move(50, 500);

    QObject::connect(Quitter, SIGNAL(clicked()), qApp, SLOT(quit()));

}
void FenetrePrincipale::AfficherPageNewJoueur()
{
    if(fnj!=nullptr){
        delete fnj;
    }
    fnj = new FenetreNewJoueur(&controleur);
    fnj->show();
}

void FenetrePrincipale::AfficherPageExtensions()
{
    if(fce!=nullptr){
        delete fce;
    }
    fce = new FenetreChoixExtension(&controleur);
    fce->show();
}

void FenetrePrincipale::AfficherPageJeu()
{
    if(fce!=nullptr){
        delete fce;
    }
    if(fnj!=nullptr){
        delete fnj;
    }
    if(fj!=nullptr){
        delete fj;
    }
    controleur.setupJeu();
    fj = new FenetreJeu(&controleur);
    fj->show();
    this->close();
}
