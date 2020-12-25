#ifndef HOPITAL_H
#define HOPITAL_H

#include <string>
#include <vector>

#include "Consultation.h"
#include "GestionnairePersonnels.h"
#include "GestionnairePatients.h"

class Hopital
{
public:
    enum class TypeConsultation
    {
        first_ = -1,
        ConsultationEnLigne,
        ConsultationPhysique,
        last_
    };

    Hopital() = default;
    Hopital(const std::string& nom, const std::string& adresse);

   
    bool chargerBaseDeDonnees(const std::string& nomFichierPersonnels, const std::string& nomFichierPatients, const std::string& nomFichierConsultations);

    bool chargerDepuisFichierConsultation(const std::string& nomFichiers);


    double getAncienneteMoyenneDesPersonnels()const;



    std::vector<std::shared_ptr<Consultation>> getCosultationsEntreDates(const tm& date1, const tm& date2) const;

 
    template<typename T>
    bool ajouterConsultation(const T& consultation);
 
 //! Operateur qui ajoute un Personnel à un hopital
//! \param patient Le personnel à ajouter
//! \return        Un bool qui indique si l'opération a bien fonctionnée
   template<typename T>
   bool ajouterPersonnel( Personnel &personnel)
   {
       return gestionnairePersonnels_.ajouterPersonnel<T>(personnel);
   }

  //! Operateur qui ajoute un patient à un hopital
 //! \param patient Le patient à ajouter
 //! \return        Un bool qui indique si l'opération a bien fonctionnée
   template<typename T>
   bool ajouterPatient( Patient& patient)
   {
       return gestionnairePatients_.ajouterPatient<T>(patient);
   }


  

    const std::string& getNom() const;
    const std::string& getAdresse() const;
    GestionnairePersonnels& getGestionnairePersonnels();
    GestionnairePatients& getGestionnairePatients();
    const std::vector<std::shared_ptr<Consultation>>& getConsultations() const;

    void setNom(const std::string& nom);
    void setAdresse(const std::string& adresse);

private:
    bool lireLigneConsultation(const std::string& ligne);

    std::string nom_;
    std::string adresse_;

    GestionnairePersonnels gestionnairePersonnels_;
    GestionnairePatients gestionnairePatients_;
    std::vector<std::shared_ptr<Consultation>> consultations_;
};

#endif // HOPITAL_H