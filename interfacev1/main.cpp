#include <QApplication>
#include "FenetrePrincipale.h"
#include "Carcassonne.h"
#include<QLabel>
#include <iostream>


int main(int argc, char* argv[]) {


    QApplication app(argc, argv);
    FenetrePrincipale a;
    a.show();

    return app.exec();

}
