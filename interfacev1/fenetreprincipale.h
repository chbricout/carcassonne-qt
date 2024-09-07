#pragma once

#include <QtWidgets/QApplication>
#include <QWidget>
#include <QtWidgets/QPushButton>
#include "Controleur.h"
#include "FenetreNewJoueur.h"
#include "FenetreChoixExtension.h"
#include "FenetreJeu.h"

class FenetrePrincipale : public QWidget
{
    Q_OBJECT
public:
    FenetrePrincipale();

public slots:
    void AfficherPageNewJoueur();
    void AfficherPageExtensions();
    void AfficherPageJeu();

private:
    Controleur controleur;
    QPushButton *NewJoueur=nullptr;
    QPushButton *ChoixExtensions=nullptr;
    QPushButton *StartPartie=nullptr;
    QPushButton *Quitter=nullptr;

    FenetreNewJoueur *fnj=nullptr;
    FenetreChoixExtension *fce=nullptr;
    FenetreJeu *fj =nullptr;
};

