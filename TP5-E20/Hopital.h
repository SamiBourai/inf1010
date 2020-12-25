//! Class Hopital
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 05 juin 2020

#ifndef HOPITAL_H
#define HOPITAL_H

#include <string>
#include <vector>

#include <QObject>
#include "GestionnairePersonnels.h"


using namespace std;

/*
 * 1- Faire les transformations nécessaires pour pouvoir utiliser l'hopital comme un objet Qt
 * 2- ajouter le signal personnelAjoute qui prend en paramêtere un pointeur brut vers un personnel et qui ne retourne rien
 * et qui serait envoyé lors de l'ajout d'un personnel
 * 3- ajouter le signal personnelSupprime qui prend en paramètre un pointeur brut vers un personnel et qui ne retourne rien
 * et qui serait envoyé lors de la suppression d'un personnel
*/
class Hopital: public QObject
{
    Q_OBJECT

public:

    Hopital() = default;
    Hopital(const std::string& nom, const std::string& adresse);

    void ajouterPersonnel(Personnel& personnel);

    void supprimnerPersonnel(const std::string& personnelId);

    const std::string& getNom() const;
    const std::string& getAdresse() const;
    GestionnairePersonnels& getGestionnairePersonnels();

    void setNom(const std::string& nom);
    void setAdresse(const std::string& adresse);

signals:
    void personnelAjoute(Personnel*);
    void personnelSupprime(Personnel*);

private:
    std::string nom_;
    std::string adresse_;

    GestionnairePersonnels gestionnairePersonnels_;
};

#endif // HOPITAL_H
