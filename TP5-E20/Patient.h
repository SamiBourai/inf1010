//! Class Patient
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 05 juin 2020

#ifndef PATIENT_H
#define PATIENT_H

#include <string>


class Patient
{
public:
    Patient() = default;
	Patient(const std::string& nom, const std::string& dateDeNaissance, const std::string& numeroAssuranceMaladie, const tm& dateAdhesion);

    bool operator==(const std::string& numeroAssuranceMaladie) const;
    friend bool operator==(const std::string& nom, const Patient& patient);

    virtual void afficher(std::ostream& stream) const;

    const std::string& getNom() const;
    const std::string& getNumeroAssuranceMaladie() const;
	const std::string& getDateDeNaissance() const;
    const tm& getDateAdhesion() const;

    void setNom(const std::string& nom);
    void setNumeroAssuranceMaladie(const std::string& numeroAssuranceMaladie);
    void setDateDeNaissance(const std::string& dateDeNaissance);
    void setDateAdhesion(const tm& dateAdhesion);

protected:
    std::string nom_;
    std::string numeroAssuranceMaladie_;
    std::string dateDeNaissance_;
    tm dateAdhesion_;
};

#endif // PATIENT_H