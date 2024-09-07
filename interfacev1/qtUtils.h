#pragma once

#include <QLayout>
#include <QWidget>

inline void remove ( QLayout* layout )
{
    QLayoutItem* child;
    while ( layout->count() != 0 ) {
        child = layout->takeAt ( 0 );
        if ( child->layout() != 0 ) {
            remove ( child->layout() );
        } else if ( child->widget() != 0 ) {
            child->widget()->deleteLater();
        }

        delete child;
    }
}
