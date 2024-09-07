#include "VueMeeples.h"





VueMeeple::VueMeeple(Meeple* m)
    :meeple(m)
{
    setPixmap(meeple->getImg().scaled(15,15));
}




