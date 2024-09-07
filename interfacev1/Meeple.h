#pragma once
#include "Element.h"
#include "Joueur.h"
#include "Couleur.h"
#include <QPixmap>

class Element;
class Joueur;
class Couleur;

class Meeple {
protected:
	unsigned int valeur;
    const Couleur* couleur=nullptr;
    QPixmap image;
    std::string img_path;
	Element* element = nullptr;
	Joueur* joueur = nullptr;
    bool estPose=false;
public:
    Meeple(const Meeple& m);
    Meeple(const std::string& img_path, const Couleur* c, unsigned int v=1);;

    inline const Couleur* getCouleur() const { return couleur; };
    inline virtual std::string toStr() const {return "Meeple";};
    inline bool getEstPose() const { return estPose; };
    inline QPixmap& getImg(){return image;};
    inline int getValeur(){return valeur;};

    virtual void poser(Element* e);
    virtual void retirer();
    virtual Meeple *duplicate() const;
	inline void distribueJoueur(Joueur* j) { joueur = j; };

    virtual bool peutEtrePoser(Element*e);;
    inline virtual bool peutEtreRepris() {return false;};


	inline Joueur* getJoueur() { return joueur; };

	virtual ~Meeple() = default; // à voir destructeur

};
class Abbe final : public Meeple {
public:
    Abbe(const std::string& img_path,const Couleur* c, unsigned int v) : Meeple(img_path,c, v) {};
    inline std::string toStr() const override {return "Abbe";};
    void poser(Element* e) override;
    bool peutEtrePoser(Element*e) override;;

    inline bool peutEtreRepris() override {return true;};

    Abbe* duplicate() const override;
	~Abbe() override = default;
};
class Chariot final : public Meeple {
public:
    Chariot(const std::string& img_path,const Couleur* c, unsigned int v) : Meeple(img_path,c, v) {};
    Chariot* duplicate() const override;
    inline std::string toStr() const override {return "Chariot";};

	~Chariot() override = default;
};
class Maire final : public Meeple {
public:
    Maire(const std::string& img_path,const Couleur* c, unsigned int v) : Meeple(img_path,c, v) {};
    Maire* duplicate() const override;
    inline std::string toStr() const override {return "Maire";};


	~Maire() override = default;
};
class GrandMeeple final : public Meeple {
public:
    GrandMeeple(const std::string& img_path,const Couleur* c, unsigned int v) : Meeple(img_path,c, v) {};
    GrandMeeple* duplicate() const override;
    inline std::string toStr() const override {return "GrandMeeple";};


	~GrandMeeple() override = default;
};

