#ifndef MEDECIN_H
#define MEDECIN_H


#include <memory>
#include <string>
#include "Patient.h"
#include<vector>


class Medecin
{
public:
    enum class Specialite
    {
        first_ = -1,
        Generaliste,
        Cardiologue,
        Dermatologue,
        Gynecologue,
        Pediatre,
        Ophtalmologue,
        Autre,
        last_
    };

    Medecin() = default;
    Medecin(const std::string& nom, const std::string& numeroLicence, Specialite specialite);

   
   
   
    
    // opérateur<< qui remplace afficher // void afficher(std::ostream& stream) const;

    friend std::ostream& operator << (std::ostream& display, const Medecin& medecin1);

    // opérateur+= qui remplace ajouterPatient //void ajouterPatient(Patient patient);
   
    bool operator+=(const Patient& patient1);

    // opérateur-= qui remplace supprimerPatient//bool supprimerPatient(const std::string& numeroAssuranceMaladie);
    bool operator-=(const std::string& numAssuranceMaladie);

    // opérateur== qui compare un string avec le numéro licence du médecin
    // (par exemple, pour medecin == "158795")
    friend bool operator==( const std::string& numLicence,const  Medecin& medecin1);
    
    // opérateur== qui compare un string avec le numéro licence du médecin
    // (par exemple, pour "158795" == medecin)
    bool operator==(const std::string& numLicence);

    Patient* chercherPatient(const std::string& numeroAssuranceMaladie);


    // fonction pour alleger le code
    bool comparaisonLicenceMedecin(const std::string& numLicence)const;

    const std::string& getNom() const;
    const std::string& getNumeroLicence() const;
    bool getEstActif() const;
    const Specialite getSpecialite() const;
    const size_t getCapacitePatientAssocies() const;
    const size_t getNombrePatientsAssocies() const;
    std::vector<Patient*> getPatientsAssocies() const;

    void setNom(const std::string& nom);
    void setNumeroLicence(const std::string& numeroLicence);
    void setEstActif(bool estActif);
    void setSpecialite(Specialite specialite);

private:
    // Attributs
    std::string nom_;
    std::string numeroLicence_;
    Specialite specialite_;
    bool estActif_ = true;

    
    std::vector<Patient*> patientsAssocies_;
  
};

#endif // MEDECIN_H