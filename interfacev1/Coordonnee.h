#pragma once
#include <iostream>
#include <cstdlib>
#include "Orientation.h"
#include <vector>

class Coordonnee final
{
private:
	int x;
	int y;
    std::vector<Coordonnee> around;
public:
    Coordonnee(int new_x, int new_y) : x(new_x), y(new_y){};

    void calcAround();

	void set(int x, int y);
    inline void setX(int new_x){x=new_x;};
    inline void setY(int new_y){y=new_y;};

	void set(const Coordonnee& c);
	inline int getX() const { return x; };
	inline int getY() const { return y; };
	inline bool estNord(const Coordonnee& c) const { return x - c.x == 0 && y - c.y == 1; }; // retourn true si c est au nord ET directement à coté de la case
	inline bool estSud(const Coordonnee& c) const { return x - c.x == 0 && y - c.y == -1; }; // retourn true si c est au sud ET directement à coté de la case
	inline bool estOuest(const Coordonnee& c) const { return x - c.x == 1 && y - c.y == 0; }; // retourn true si c est a l'ouest ET directement à coté de la case
	inline bool estEst(const Coordonnee& c) const { return x - c.x == -1 && y - c.y == 0; }; // retourn true si c est a l'est ET directement à coté de la case
    inline bool estAdjacent(const Coordonnee& c) const { return (abs(x - c.x) <= 1 && abs(y - c.y) <= 1); };
    inline bool estEnContact(const Coordonnee& c) const { return (abs(x - c.x) == 0 || abs(y - c.y) ==0); };
    Orientation getOrientationRel(const Coordonnee& c) const;

    using around_iterator = std::vector<Coordonnee>::iterator;
    inline around_iterator begin() {calcAround(); return around.begin();};
    inline around_iterator end() {return around.end();};

};

bool operator==(const Coordonnee& c1, const Coordonnee& c2);
std::ostream& operator<<(std::ostream& f, const Coordonnee& c);
