#include "ReserveTuileW.h"
#include "VueTuile.h"

ReserveTuileW::ReserveTuileW(Controleur * c,QWidget *parent)
    :QWidget{parent}, controleur(c)
{

    mainLayout = new QHBoxLayout();
    mainLayout->setAlignment(Qt::AlignLeft);

    setLayout(mainLayout);
    Joueur *j =controleur->getTour();
    for(auto t:j->getReserve()){
        VueTuile * vt = new VueTuile(t);
        QPushButton *n_btn = new QPushButton();
        QIcon btnIcon(vt->pixmap());
        n_btn->setIcon(btnIcon);
        n_btn->setIconSize(vt->pixmap().rect().size());
        mainLayout->addWidget(n_btn);
        connect(n_btn, &QPushButton::clicked, [this, t, n_btn]{ajouteTuileVuePlateau(t, n_btn);} );
    }
}

ReserveTuileW::~ReserveTuileW()
{
    while(!mainLayout->isEmpty()) {
        QWidget *w = mainLayout->takeAt(0)->widget();
         w->deleteLater();
    }
    mainLayout->deleteLater();

}

void ReserveTuileW::ajouteTuileVuePlateau(Tuile *t, QPushButton* pb)
{
    if(controleur->getVuePlateau()->getNewTuile()==nullptr){
        controleur->getVuePlateau()->ajouteTuile(t);
        controleur->getTour()->removeReserve(t);
        pb->deleteLater();
        emit tuileAjoute();
    }
}
