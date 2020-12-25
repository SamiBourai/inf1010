//! Class Etudiant
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 05 juin 2020

#ifndef ERREURS_H
#define ERREURS_H

#include <exception>
#include <string>

using namespace std;

/**********************************************************************************************
 * Description      : Classe pour catcher les exceptions reliées à des dates invalides
 **********************************************************************************************/
class DateInvalide : public exception
{
public:
    explicit DateInvalide(const std::string& message) {
        message_ += message;
    };

    virtual const char* what() const throw() {
       return message_.c_str();
    };

private:
    std::string message_ = "Erreur date: ";
};

/**********************************************************************************************
 * Description      : Classe pour catcher les exceptions des champs string
 **********************************************************************************************/
class ErreurChamp : public exception
{
public:
    explicit ErreurChamp(const std::string& message) {
        message_ += message;
    };

    virtual const char* what() const throw() {
       return message_.c_str();
    };

private:
    std::string message_ = "Erreur champs: ";
};

#endif // ERREUR_H
