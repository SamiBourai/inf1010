//! Class Consultation
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 05 juin 2020

#ifndef CONSULTATION_H
#define CONSULTATION_H

#include <string>
#include "Medecin.h"
#include "Patient.h"

class Consultation
{
public:
    Consultation() = default;
    Consultation(Medecin& medecin, Patient& patient, const std::string& date);

    Medecin* getMedecin() const;
    Patient* getPatient() const;
    const std::string& getDate() const;

    void afficher(std::ostream& os) const;

    virtual const double calculerPrix() const = 0;

    static constexpr  double PRIX_DE_BASE = 50;

protected:
    Medecin* medecin_;
    Patient* patient_;
    std::string date_;
    double prix_;
};

#endif // CONSULTATION_H