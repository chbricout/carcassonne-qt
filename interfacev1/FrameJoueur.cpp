#include "FrameJoueur.h"

FrameJoueur::FrameJoueur(Joueur* j, QWidget *parent): joueur(j), QFrame(parent)
{
    mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    setFrameShadow(QFrame::Raised);
    setFrameShape(QFrame::Panel);

    QLabel *titre = new QLabel(joueur->getNom().c_str());
    QFont font = titre->font();
    font.setPointSize(20);
    font.setBold(true);
    titre->setFont(font);

    mainLayout->addWidget(titre);
    mainLayout->addWidget(new QLabel(joueur->getCouleur()->getNom().c_str()));
    std::string points = std::to_string(joueur->getPoints());
    mainLayout->addWidget(new QLabel(points.c_str()));


    for(auto& line: joueur->getNbMeeples()){
        mainLayout->addWidget(new QLabel(line.c_str()));
    }


}


FrameJoueur::~FrameJoueur()
{
    while(!mainLayout->isEmpty()) {
        QWidget *w = mainLayout->takeAt(0)->widget();
        w->deleteLater();
    }
    mainLayout->deleteLater();
}
