#include "FenetreJeu.h"
#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QProgressBar>
#include <QLCDNumber>
#include <QMessageBox>
#include <QMouseEvent>
#include <QTransform>
#include <QInputDialog>
#include "Tuile.h"
#include "ShowScore.h"

FenetreJeu::FenetreJeu(Controleur * c,QWidget *parent): QWidget(parent), controleur(c) //ma fenetre de jeu a une fentre de jeu parente
{
    setWindowTitle("LO21_Projet");
    setFixedSize(1000, 750);
    mainLayout = new QVBoxLayout();
    vueJeuLayout = new QHBoxLayout();
    actionLayout = new QVBoxLayout();
    actionLayout->setAlignment(Qt::AlignTop);
    m_view= new QGraphicsView(this);
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mainLayout->addLayout(vueJeuLayout);
    setLayout(mainLayout);
    vueJeuLayout->addWidget(m_view);
    vueJeuLayout->addLayout(actionLayout);

    btnRecup=new QPushButton();
    btnValider=new QPushButton();
    btnTourSuivant=new QPushButton();
    reserve = new ReserveTuileW(c);
    s_plateau = new VuePlateau(&c->getPlateau());
    prochainTour();
}

FenetreJeu::~FenetreJeu(){

}

void FenetreJeu::validerTuile()
{
    VueTuile *vt = s_plateau->getNewTuile();
    Coordonnee c(vt->x()/60, vt->y()/60);

    try{controleur->poseTuile(vt->getTuile(), controleur->getTour(), c);}
    catch(Exception& e){
        QMessageBox msgBox;
        msgBox.setText(e.getMessage().c_str());
        msgBox.exec();
        return;
    }

    btnRecup->setVisible(false);
    btnValider->setVisible(false);
    btnTourSuivant->setVisible(true);

    chooseMeeple = new ChooseMeeple(vt->getTuile(),controleur->getTour());
    actionLayout->addWidget(chooseMeeple);
    connect(chooseMeeple, SIGNAL(meepleActionDone()), this,SLOT(prochainTour()));

    vt->setFlag(QGraphicsPixmapItem::ItemIsMovable, false);


}


void FenetreJeu::prochainTour()
{
    VueTuile *vt = s_plateau->getNewTuile();
    if(vt!=nullptr){
        Coordonnee c(vt->x()/60, vt->y()/60);
        for(auto around: c){
            Tuile *t = controleur->getPlateau().getTuile(around);
            if(t!=nullptr) t->checkStructuresComplet();
        }
    }

    if(controleur->isGameOver()){
        for(auto j : controleur->getJoueurs()){
            std::string textLabel = "Point du joueur "+j->getNom()+" ("+j->getCouleur()->getNom()+") :";
            int points = QInputDialog::getInt(this, tr("fin de jeu"), tr(textLabel.c_str()));
            j->addPoints(points);
        }
        ShowScore* ss = new ShowScore(controleur);
        ss->show();
        close();
        deleteLater();
    }else{
        controleur->tourSuivant();
        if(s_plateau != nullptr) s_plateau->deleteLater();
        s_plateau =new VuePlateau(&controleur->getPlateau());
        controleur->setVuePlateau(s_plateau);
        m_view->setScene(s_plateau);


        if(btnRecup!=nullptr){
            btnRecup->deleteLater();
            btnRecup=nullptr;
        }

        if(btnValider!=nullptr) {
            btnValider->deleteLater();
            btnValider=nullptr;
        }
        if(btnTourSuivant!=nullptr){
            btnTourSuivant->deleteLater();
            btnTourSuivant=nullptr;
        }
        if(chooseMeeple!=nullptr) {
            chooseMeeple->deleteLater();
            chooseMeeple = nullptr;
        }
        if(frameJoueur!=nullptr){
            frameJoueur->deleteLater();
            frameJoueur=nullptr;
        }


        btnRecup= new QPushButton(this);
        btnRecup->setText("Recuperer");
        btnRecup->setVisible(false);

        btnValider= new QPushButton(this);
        btnValider->setText("Valider");
        btnValider->setVisible(false);

        btnTourSuivant = new QPushButton(this);
        btnTourSuivant->setText("Tour Suivant");

        actionLayout->addWidget(btnRecup);
        actionLayout->addWidget(btnValider);
        actionLayout->addWidget(btnTourSuivant);

        frameJoueur = new FrameJoueur(controleur->getTour());
        actionLayout->addWidget(frameJoueur);

        reloadReserve();
        connect(btnRecup,SIGNAL(clicked()),this,SLOT(reprendreTuile()));
        connect(btnValider,SIGNAL(clicked()),this,SLOT(validerTuile()));
        connect(btnTourSuivant,SIGNAL(clicked()),this,SLOT(prochainTour()));
        connect(reserve, SIGNAL(tuileAjoute()), this, SLOT(showBtnRecup()));
    }
}

void FenetreJeu::reprendreTuile()
{
    Tuile *t = s_plateau->getNewTuile()->getTuile();
    if(t != nullptr){
        controleur->getTour()->addReserve(t);
        s_plateau->removeTuile();
        btnRecup->setVisible(false);
        btnValider->setVisible(false);
        btnTourSuivant->setVisible(true);

        reloadReserve();
    }
}

void FenetreJeu::reloadReserve()
{
    if(reserve) reserve->deleteLater();
    reserve = new ReserveTuileW(controleur);
    mainLayout->addWidget(reserve);
    connect(reserve, SIGNAL(tuileAjoute()), this, SLOT(showBtnRecup()));

}

void FenetreJeu::showBtnRecup()
{
    if(btnRecup!=nullptr){
        btnRecup->setVisible(true);
        btnValider->setVisible(true);
        btnTourSuivant->setVisible(false);
    }
}
    /*
    void MainWindow::mousePressEvent(QMouseEvent *me){
        if(me->button()==Qt::LeftButton){
            qWarning("clic droit");
        }

    }
    */



/*
    void fenetrejeu::tourner_Tuile(bool b)
    {
         for(auto it = m_scene->items.begin(); it!=m_scene->items.end();it++ )
         {

        }
    }
*/

/*
    void fenetrejeu::tourner_Tuile(bool b)
    {
        QTransform transform;
        transform.rotate(90); // 180 ou 270
        QPixmap p = image.transformed(transform);
    }
*/
