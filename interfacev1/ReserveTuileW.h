#pragma once
#include <QWidget>
#include <QHBoxLayout>
#include <vector>
#include "Tuile.h"
#include "Joueur.h"
#include "Controleur.h"
#include <QPushButton>

class ReserveTuileW : public QWidget
{
    Q_OBJECT
private:
    QHBoxLayout* mainLayout=nullptr;
    Controleur * controleur=nullptr;
    Tuile* tuile=nullptr;

public:
    explicit ReserveTuileW(Controleur * c,QWidget *parent = nullptr);
    ~ReserveTuileW();
signals:
    void tuileAjoute();
public slots:
    void ajouteTuileVuePlateau(Tuile *t, QPushButton* pb);

};

