#include "ShowScore.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

ShowScore::ShowScore(Controleur * c, QWidget *parent):  QWidget(parent), controleur(c)
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    QLabel *titre = new QLabel("Score :");
    QFont font = titre->font();
    font.setPointSize(25);
    font.setBold(true);
    titre->setFont(font);
    mainLayout->addWidget(titre);
    for(auto j : controleur->getJoueurs()){
        std::string text = j->getNom()+" : "+std::to_string(j->getPoints());
        QLabel *scoreLabel = new QLabel(text.c_str());
        mainLayout->addWidget(scoreLabel);
    }

}
