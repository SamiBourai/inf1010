#ifndef GESTIONNAIREMEDECIN_H
#define GESTIONNAIREMEDECIN_H

#include <memory>
#include "Medecin.h"
#include "GestionnairePatients.h"
#include<vector>


class GestionnaireMedecins
{
public:
    GestionnaireMedecins();
    //TODO : signature de constructeur de copie
    GestionnaireMedecins(const GestionnaireMedecins& gestionnaireMedecins);
    //TODO : signature d'operateur d'affectaion
    GestionnaireMedecins& operator = (const GestionnaireMedecins& gestionnaireMedecins);

    
    Medecin* chercherMedecin(const std::string& numeroLicence);
    bool chargerDepuisFichier(const std::string& nomFichiers);
   

    // TODO : signature des opérateurs à surcharger.
    // opérateur<< qui remplace afficher //void ajouterMedecin(std::shared_ptr<Medecin> medecin);
    friend std::ostream& operator << (std::ostream& display, const GestionnaireMedecins& medecins);

    // opérateur+= qui remplace ajouterMedecin
    bool operator+=(const Medecin& medecin1);

    // opérateur-= qui remplace supprimerMedecin // bool supprimerMedecin(const std::string& numeroLicence);
    bool operator-=(const std::string& numLicence);

    size_t getNbMedecins() const;
    size_t getCapaciteMedecins() const;

    // TODO : signature de getMedecins() retourne une reference constante vers le vecteur medecins_
    const std::vector < std::shared_ptr<Medecin>>& getMedecins()const;

private:
    bool lireLigneMedecin(const std::string& ligne);
    int trouverIndexMedecin(const std::string& numeroLicence);

   
    std::vector < std::shared_ptr<Medecin>> medecins_;
};

#endif // GESTIONNAIREMEDECIN_H