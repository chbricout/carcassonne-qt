#pragma once

#include <QtWidgets/QApplication>
#include <QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QStringListModel>
#include <QRadioButton>
#include <QLabel>
#include <QSignalMapper>

#include "Controleur.h"

class FenetreNewJoueur : public QWidget
{
    Q_OBJECT
public:
    FenetreNewJoueur(Controleur * c);
    void refresh();

private:
    Controleur * controleur=nullptr;
    QLineEdit *Nom=nullptr;
    //QLineEdit *Couleur;
    QPushButton *Enregistrer=nullptr;
    QComboBox *couleur=nullptr;
    QPushButton *Annuler=nullptr;
    QFormLayout *Donnee=nullptr;
    QLabel *erreur=nullptr;
    QStringListModel *ListeC=nullptr;
    QRadioButton *IA=nullptr;
    QVBoxLayout *layout=nullptr;
    QVBoxLayout *joueursL = nullptr;



signals:

public slots:
    void deleteJoueur(const QString& nom);
    void addJoueur();
};

