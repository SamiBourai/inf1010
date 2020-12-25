//! Foncteur variés utilisés pour les algorithmes.
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 2020-06-04

#ifndef FONCTEURS_H
#define FONCTEURS_H

#include <memory>
#include <utility>
#include "Personnel.h"

//! Foncteur prédicat binaire comparant les seconds éléments de paires pour déterminer si elles sont en ordre.
//! \tparam T1  Le type du premier élément de la paire
//! \tparam T2  Le type du second élément de la paire
template<typename T1, typename T2>
class ComparateurSecondElementPaire
{
public:
    //! Comparateur retournant true si le premier élément doit être ordonné avant le second.
    //! \param pair1    La première std::pair à comparer
    //! \param pair2    La seconde std::pair à comparer.
    //! \return         True si pair1.second < pair2.second, false sinon.
    bool operator()(const std::pair<T1, T2>& pair1, const std::pair<T1, T2>& pair2)
    {
        return *(pair1.second) < *(pair2.second);
    }
};

//! Foncteur prédicat unaire comparant deux elements avec leurs ids. 
//! Noter que l'element doit definir l'operateur==(const string& id) pour que la comparaison puisse se faire
template<typename T>
class ComparateurEstEgalAvecId
{
public:
    //! Constructeur par paramètres initalisant l'id de la comparaison
    //! \param id  L'identificateur de l'élement
    ComparateurEstEgalAvecId(const std::string& id): id_(id)
    {
    }

    //! Comparateur retournant true si l'élément est égal à l'id.
    //! \param element1    Le premier élément à comparer.
    //! \return            True si element1 == element2, false sinon.
    bool operator()(const std::shared_ptr<T> element1)
    {
        return *element1 == id_;
    }

private:
    std::string id_;
};



//! Foncteur prédicat unaire comparant un type d'objet de Patient à un type donné
template<typename T>
class ComparateurTypePatient
{
public:
    //! Comparateur retournant true si le dynamic cast de l'objet est du type passé
    //! \param patient         shared_ptr vers un patient
    //! \return                True si le patient est du type donné false sinon
    bool operator() (std::shared_ptr<Patient> patient)
    {
        return dynamic_cast<T*>(patient.get());
    }
};

#endif // FONCTEURS_H
