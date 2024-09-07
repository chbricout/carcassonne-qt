#include "FenetreNewJoueur.h"
#include "Couleur.h"
#include "Joueur.h"

FenetreNewJoueur::FenetreNewJoueur(Controleur *c) : QWidget(), controleur(c)
{

    layout = new QVBoxLayout(this);
    CouleursHandler* ch = CouleursHandler::GetInstance();
    //Infos du Joueur
    Nom = new QLineEdit;
    couleur = new QComboBox;
    QStringList items;
    for(auto& c : ch->getCouleurs()) items << tr(c.getNom().c_str());
//        items << tr("vert") << tr("Rouge") << tr("Bleu");
    ListeC = new QStringListModel(items, this);

    couleur->setModel(ListeC);

    IA = new QRadioButton;

    Donnee = new QFormLayout;
    Donnee->addRow("Votre Nom", Nom);
    Donnee->addRow("Votre Couleur", couleur);
    Donnee->addRow("Joueur IA ?", IA);

    //Enregistrement du joueur
    QHBoxLayout *btnBar = new QHBoxLayout();
    Enregistrer = new QPushButton("Enregistrer", this);
    Enregistrer->setToolTip("Permet d'enregistrer un nouveau joueur");
    Enregistrer->setCursor(Qt::PointingHandCursor);
    btnBar->addWidget(Enregistrer);
    Annuler = new QPushButton("Annuler", this);
    Annuler->setToolTip("Annuler");
    Annuler->setCursor(Qt::PointingHandCursor);
    btnBar->addWidget(Annuler);

    layout->addLayout(Donnee);
    layout->addLayout(btnBar);
    erreur = new QLabel(this);
    layout->addWidget(erreur);
    QObject::connect(Annuler, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(Enregistrer, SIGNAL(clicked()), this, SLOT(addJoueur()));



    refresh();
}

void FenetreNewJoueur::refresh()
{

    if(joueursL!=nullptr){
        QLayoutItem* layout, *item;
        while ( ( layout = joueursL->takeAt( 0 ) ) != NULL )
        {
            while ((item = layout->layout()->takeAt(0))!= NULL){
                delete item->widget();
                delete item;
            }
            delete layout->widget();
            delete layout;
        }
        delete joueursL;
    }
    joueursL = new QVBoxLayout();
    QHBoxLayout *c_joueur = nullptr;
    QPushButton *c_btn = nullptr;
    for (auto& j : controleur->getJoueurs()){
        c_joueur = new QHBoxLayout();
        c_joueur->addWidget(new QLabel(j->getNom().c_str()));
        c_joueur->addWidget(new QLabel(j->getCouleur()->getNom().c_str()));

        c_btn = new QPushButton("Supprimer", this);
        c_joueur->addWidget(c_btn);
        QString text= j->getNom().c_str();
        QObject::connect(c_btn, &QPushButton::clicked, [this, text]{deleteJoueur(text);});
        joueursL->addLayout(c_joueur);
    }
    layout->addLayout(joueursL);
}

void FenetreNewJoueur::deleteJoueur(const QString &nom)
{
    erreur->setText("");

    try{
           controleur->supprimerJoueur(nom.toStdString());
    }catch(Exception& e){

        //std::cout <<e.getMessage() << std::endl;
        erreur->setText(e.getMessage().c_str());
        erreur->setStyleSheet("QLabel {color: red; }");
    }
        refresh();
}

void FenetreNewJoueur::addJoueur()
{
    erreur->setText("");
    CouleursHandler* ch = CouleursHandler::GetInstance();
    Joueur *j = new Joueur(Nom->text().toStdString(), &ch->getCouleur(couleur->currentText().toStdString()));
    try{
        controleur->ajouterJoueur(j);
    }catch(InitialisationException& e){

        //std::cout <<e.getMessage() << std::endl;
        erreur->setText(e.getMessage().c_str());
        erreur->setStyleSheet("QLabel {color: red; }");
    }

    refresh();

};
