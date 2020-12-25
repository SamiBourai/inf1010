//! Class Medecin
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 05 juin 2020

#ifndef MEDECIN_H
#define MEDECIN_H

#include <memory>
#include <string>
#include "Patient.h"
#include "Personnel.h"
#include <vector>

#include <QObject>

class Medecin : public Personnel, public QObject
{
    #include <QObject>
public:
    enum Specialite
    {
        Generaliste = 0,
        Cardiologue,
        Dermatologue,
        Gynecologue,
        Pediatre,
        Ophtalmologue,
        Autre,
    };
    Q_ENUM(Specialite);

    Medecin();
	Medecin(const std::string& nom, const std::string& numeroLicence, Specialite specialite, const tm& dateAdhesion);

	bool operator+=(Patient* patient);
	bool operator-=(const std::string& numeroAssuranceMaladiePatient);

    Patient* chercherPatient(const std::string& numeroAssuranceMaladie);
    void incrementNombreConsultations();

    virtual double getSalaireAnnuel() const override;

    double getPrixConsultation() const;
    Specialite getSpecialite() const;
    size_t getNombrePatientsAssocies() const;
    size_t getNombreConsultations() const;

    const std::vector<Patient*>& getPatientsAssocies() const;

    void setSpecialite(Specialite specialite);

    static constexpr double SALAIRE_DE_BASE_MEDECIN = 100000;

private:
    int trouverIndexPatient(const std::string& numeroAssuranceMaladie);

protected:
    // Attributs
    Specialite specialite_;
    std::vector<Patient*> patientsAssocies_;
    size_t nombreConsultations_;
};

#endif // MEDECIN_H
