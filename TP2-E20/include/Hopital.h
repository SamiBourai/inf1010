#ifndef HOPITAL_H
#define HOPITAL_H

#include <string>
#include <vector>

#include "Consultation.h"
#include "GestionnaireMedecins.h"
#include "GestionnairePatients.h"

class Hopital
{
public:
    Hopital() = default;
    Hopital(const std::string& nom, const std::string& adresse);

    bool chargerBaseDeDonnees(const std::string& nomFichierMedecins, const std::string& nomFichierPatients);
    bool verifierCondition(Consultation& consultation1);
    
    //TODO : la signature des opérateurs à surcharger
    // opérateur+= qui ajoute une instance de Consultation
    bool operator+=( Consultation& consultation1);
    // opérateur+= qui ajoute une instance de Medecin
    bool operator+=( Medecin& medecin1);
    // opérateur+= qui ajoute une instance de Patient
    bool operator+=( Patient& patient1);

    const std::string& getNom() const;
    const std::string& getAdresse() const;
    GestionnaireMedecins& getGesionnaireMedecins();
    GestionnairePatients& getGestionnairePatients();

    // TODO : la signature de getConsultations()
    const std::vector<std::shared_ptr<Consultation>>& getConsultations() const;


    //methode ajoutee pour alleger code
    bool chargerPatientMedecin(const std::string& nomFichier1, const std::string& nomFichier2);

    void setNom(const std::string& nom);
    void setAdresse(const std::string& adresse);

private:
    std::string nom_;
    std::string adresse_;

    GestionnaireMedecins gestionnaireMedecins_;
    GestionnairePatients gestionnairePatients_;

    //TODO : vecteur de shared_ptr de Consultation consultations_
    std::vector<std::shared_ptr<Consultation>> consultations_;
};

#endif // HOPITAL_H