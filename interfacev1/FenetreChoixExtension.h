#pragma once
#include <QtWidgets/QApplication>
#include <QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QFormLayout>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "Controleur.h"

class FenetreChoixExtension : public QWidget
{
    Q_OBJECT
public:
    FenetreChoixExtension(Controleur * c);

private:
    Controleur * controleur=nullptr;
    std::vector <QCheckBox*> extensionsChecks;
    QVBoxLayout *layout=nullptr;
    QHBoxLayout *layoutBtnBar=nullptr;

    QPushButton *Enregistrer=nullptr;
    QPushButton *Annuler=nullptr;
    //QFormLayout *Donnee;

signals:

public slots:
    void save();
};

