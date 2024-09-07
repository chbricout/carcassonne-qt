#pragma once
#include<iostream>
#include<string>
class Exception 
{
protected:
    const std::string message;
    int numero_err;
public:
    inline Exception(std::string s, const int i) : message(s), numero_err(i) {};
    inline const std::string& getMessage() const { return message; };
    inline const int& getNumero() const { return numero_err; }; 
    virtual ~Exception() = default;
    
};


class InitialisationException final : public Exception 
{
public:
    InitialisationException(std::string s, const int i) : Exception("Erreur d'initialisation "+s, i) { };
    ~InitialisationException() override= default;
};

class PlacementMeepleException final : public Exception 
{
public:
    PlacementMeepleException(std::string s, const int i) : Exception("Erreur de placement Meeple "+s, i) { };
    ~PlacementMeepleException() override= default;
};

class BordException final : public Exception 
{
public:
    BordException(std::string s, int i) : Exception("Erreur de Bord "+s, i) {  };
    ~BordException() override= default;
};

class CoordonneesException final : public Exception 
{
public:
    CoordonneesException(std::string s, int i) : Exception("Erreur de Coordonnees "+s, i) { };
    ~CoordonneesException() override= default;
};

class CouleurException final : public Exception
{
public:
    CouleurException(std::string s,int i) : Exception("Erreur de Couleur "+s, i) {  };
    ~CouleurException() override= default;
};

class ControleurException final : public Exception
{
public:
    ControleurException(std::string s,int i=0) : Exception("Erreur dans controleur : "+s, i) {  };
    ~ControleurException() override= default;
};


class JoueurException final : public Exception
{
public:
    JoueurException(std::string s,int i=0) : Exception("Erreur dans controleur : "+s, i) {  };
    ~JoueurException() override= default;
};
