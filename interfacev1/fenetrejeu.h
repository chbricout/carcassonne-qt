#pragma once
#include <QtWidgets/QApplication>
#include <QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QFormLayout>
#include <QMainWindow>

/*
class fenetrejeu : public QWidget
{
public:
    fenetrejeu(QWidget *parent= nullptr);
};

#endif // FENETREJEU_H
*/

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsView>

#include "VuePlateau.h"
#include "VueTuile.h"
#include "Controleur.h"
#include "Plateau.h"
#include "ReserveTuileW.h"
#include "ChooseMeeple.h"
#include "FrameJoueur.h"

class FenetreJeu : public QWidget
{
    Q_OBJECT
public:
    FenetreJeu(Controleur * c, QWidget *parent = nullptr);
    ~FenetreJeu();


public slots: // définir des fonctions visibles par les connections
    void validerTuile();
    void prochainTour();
    void reprendreTuile();
    void reloadReserve();
    void showBtnRecup();

private:
    Controleur * controleur=nullptr;
    QGraphicsView* m_view=nullptr;
    QPushButton* btnRecup=nullptr;
    QPushButton* btnValider=nullptr;
    QPushButton* btnTourSuivant=nullptr;

    QVBoxLayout* mainLayout=nullptr;
    ReserveTuileW* reserve=nullptr;
    QHBoxLayout* vueJeuLayout=nullptr;
    VuePlateau * s_plateau = nullptr;
    QVBoxLayout* actionLayout=nullptr;
    ChooseMeeple* chooseMeeple = nullptr;
    FrameJoueur * frameJoueur = nullptr;
};

