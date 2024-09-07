#pragma once
#include "Tuile.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
#include <chrono>


class Pioche {
private:
	std::vector<Tuile*> tuiles;
public:
    size_t  getNbTuile() const { return tuiles.size(); };
	bool estvide() const { return tuiles.empty(); };
	void afficher(std::ostream& f=std::cout) const;

	void ajouter(Tuile* t);
    void ajouterTop(Tuile* t);
    void enlever(Tuile* t);
    void shuffle();
    Tuile* pioche();

	Pioche() = default;
	Pioche(std::vector<Tuile*> l) : tuiles(l) {};
	//Pioche(Jeu);
	~Pioche() = default;

	class iterator : public std::vector<Tuile*>::iterator {
	private:
		iterator(std::vector<Tuile*>::iterator it) :std::vector<Tuile*>::iterator(it) {};
		friend class Pioche;
	public:
		Tuile& operator*() const {
			return *std::vector<Tuile*>::iterator::operator*();
		}
	};
	iterator begin()  { return iterator(tuiles.begin()); }
	iterator end()  { return iterator(tuiles.end()); }

};

std::ostream& operator<<(std::ostream& f, const Pioche& p);
