#include "Coordonnee.h"

bool operator==(const Coordonnee& c1, const Coordonnee& c2)
{
    return c1.getX()==c2.getX() && c1.getY()==c2.getY();
}

std::ostream& operator<<(std::ostream& f, const Coordonnee& c)
{
    f << "(" << c.getX() << "," << c.getY() << ")";
    return f;
}

void Coordonnee::calcAround()
{
    around.clear();
    for(int i=x-1; i<=x+1;i++){
        for(int j=y-1; j<=y+1;j++){
            if(i!=x || j!=y) around.push_back(Coordonnee(i,j));
        }
    }
}

void Coordonnee::set(int new_x, int new_y)
{
    x = new_x;
    y = new_y;
}

void Coordonnee::set(const Coordonnee& c)
{
    x = c.x;
    y = c.y;
}

Orientation Coordonnee::getOrientationRel(const Coordonnee& c) const
{
    int diff_x = x - c.x, diff_y = y - c.y;
    if (diff_x==0 && diff_y==1) {
        return Orientation::Nord;
    }
    else if (diff_x == 0 && diff_y == -1) {
        return Orientation::Sud;
    }
    else if (diff_x == 1 && diff_y == 0) {
        return Orientation::Ouest;
    }
    else if (diff_x == -1 && diff_y == 0) {
        return Orientation::Est;
    }
    return Orientation::Aucune;
}

