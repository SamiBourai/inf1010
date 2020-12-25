#ifndef PATIENT_H
#define PATIENT_H

#include <string>


class Patient
{
public:
    Patient() = default;

   
    Patient(const std::string& nom, const std::string& dateDeNaissance, const std::string& numeroAssuranceMaladie, const tm& dateAdhesion); // Modifier le constructeur pour prendre en considération l'attribut ajouté

    bool operator==(const std::string& numeroAssuranceMaladie) const;
    friend bool operator==(const std::string& nom, const Patient& patient);

    virtual void afficher(std::ostream& stream) const;

    const std::string& getNom() const;
    const std::string& getNumeroAssuranceMaladie() const;
    const std::string& getDateDeNaissance() const;
    const tm& getDateAdhesion()const;

    void setNom(const std::string& nom);
    void setNumeroAssuranceMaladie(const std::string& numeroAssuranceMaladie);
    void setDateDeNaissance(const std::string& dateDeNaissance);

protected:
    std::string nom_;
    std::string numeroAssuranceMaladie_;
    std::string dateDeNaissance_;
    tm dateAdhesion_;           // Ajouter attribut  de type tm

};
   

#endif // PATIENT_H