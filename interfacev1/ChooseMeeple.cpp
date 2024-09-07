#include "ChooseMeeple.h"
#include "qtUtils.h"

ChooseMeeple::ChooseMeeple(Tuile *t, Joueur * j, QWidget *parent):  QFrame(parent),joueur(j),tuile(t)
{
    mainLayout = new QVBoxLayout();
    meeplePicker=new QWidget();
    QVBoxLayout *meeplePickerL =new QVBoxLayout();
    meeplePicker->setLayout(meeplePickerL);
    elementPicker=new QWidget();
    QVBoxLayout *elementPickerL =new QVBoxLayout();
    elementPicker->setLayout(elementPickerL);
    setLayout(mainLayout);
    mainLayout->addWidget(elementPicker);
    mainLayout->addWidget(meeplePicker);
    setFrameShadow(QFrame::Raised);
    setFrameShape(QFrame::Panel);
    for(Element* e : *t){
        if(e->canPoseMeeple(j)){
            QHBoxLayout *elLayout = new QHBoxLayout();
            elLayout->addWidget(new QLabel(e->getNom().c_str()));
            elLayout->addWidget(new QLabel(orientationToString(e->getOrientation()).c_str()));
            QPushButton *addMeeple = new QPushButton();
            addMeeple->setText("poser Meeple");
            elLayout->addWidget(addMeeple);
            connect(addMeeple, &QPushButton::clicked,this, [this, e]{openAddMeeple(e);});
            elementPickerL->addLayout(elLayout);
        }
    }
    for(Meeple* m : joueur->getRetirableMeeples()){
        QPushButton *rmMeeple = new QPushButton();
        rmMeeple->setText(("retirer "+ m->toStr()).c_str());
        connect(rmMeeple, &QPushButton::clicked,this, [this, m, rmMeeple]{retirerMeeple(m, rmMeeple);});
        elementPickerL->addWidget(rmMeeple);
    }

}



ChooseMeeple::~ChooseMeeple()
{
    if(mainLayout!=nullptr){
        remove(elementPicker->layout());
        elementPicker->deleteLater();
        elementPicker=nullptr;
        remove(mainLayout);
        delete mainLayout;
    }
}

void ChooseMeeple::openAddMeeple(Element *e)
{
    selectedEl = e;
    elementPicker->setVisible(false);
    meeplePicker->setVisible(true);

    for(Meeple* m : joueur->getPosableMeeples(e)){
        QPushButton *addMeeple = new QPushButton();
        addMeeple->setText(m->toStr().c_str());
        connect(addMeeple, &QPushButton::clicked,this, [this, m]{poserMeeple(m);});
        meeplePicker->layout()->addWidget(addMeeple);
    }



    QPushButton *retour = new QPushButton();
    retour->setText("Retour");
    connect(retour, &QPushButton::clicked,this, [this]{closeAddMeeple();});
    meeplePicker->layout()->addWidget(retour);
}

void ChooseMeeple::closeAddMeeple()
{
    selectedEl = nullptr;
    elementPicker->setVisible(true);
    meeplePicker->setVisible(false);
    remove(meeplePicker->layout());
}

void ChooseMeeple::poserMeeple(Meeple *m)
{
    m->poser(selectedEl);
    emit meepleActionDone();
}

void ChooseMeeple::retirerMeeple(Meeple *m, QPushButton *rmBtn)
{
    m->retirer();
    rmBtn->deleteLater();
    emit meepleActionDone();
}


