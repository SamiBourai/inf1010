//! Class Hopital
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 05 juin 2020

#include "Hopital.h"
#include "assert.h"
#include <numeric>
#include "Foncteurs.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <iterator>

//! Constructeur par paramètres de la classe Hopital
//! \param nom      Nom de l'hopital
//! \param adresse  Adresse de l'hopital
Hopital::Hopital(const std::string& nom, const std::string& adresse):nom_(nom), adresse_(adresse)
{
}

void Hopital::ajouterPersonnel(Personnel& personnel)
{
    /* TODO 1:
     * émettre le signal correspondant si l'ajout est réussi
    */
    if (gestionnairePersonnels_.ajouterPersonnel(personnel)) {
        emit personnelAjoute(&personnel);
    }
}

void Hopital::supprimnerPersonnel(const std::string& personnelId) {
    /* TODO 2:
     * émettre le signal correspondant si la suppression est réussie
    */
    if (gestionnairePersonnels_.supprimerPersonnel(personnelId)) {

        emit personnelSupprime(gestionnairePersonnels_.chercherPersonnel(personnelId));
        //emit personnelSupprime(gestionnairePersonnels_.chercherPersonnel(personnelId));
    }
}

//! Méthode qui retourne le nom de l'hopital
//! \return nom_ le nom de l'hopital
const std::string& Hopital::getNom() const
{
    return nom_;
}

//! Méthode qui retourne l'adresse de l'hopital
//! \return adresse_ l'adresse de l'hopital
const std::string& Hopital::getAdresse() const
{
    return adresse_;
}

//! Méthode qui retourne le gestionnaire du personnels
//! \return gestionnairePersonnels_ gestionnaire du personnels
GestionnairePersonnels& Hopital::getGestionnairePersonnels()
{
    return gestionnairePersonnels_;
}

//! Méthode qui permet de mettre à jour le nom de l'hopital
//! \Param nom Le nom de l'hopital
void Hopital::setNom(const std::string& nom)
{
    nom_ = nom;
}

//! Méthode qui permet de mettre à jour l'adresse de l'hopital
//! \Param adresse  l'adresse de l'hopital
void Hopital::setAdresse(const std::string& adresse)
{
    adresse_ = adresse;
}

