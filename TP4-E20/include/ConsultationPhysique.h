//! Class ConsultationPhysique
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 05 juin 2020

#ifndef CONSULTATIONPHYSIQUE_H
#define CONSULTATIONPHYSIQUE_H

#include <string>
#include "Medecin.h"
#include "Patient.h"
#include "Consultation.h"

class ConsultationPhysique : public Consultation
{
public:
    ConsultationPhysique(Medecin& medecin, Patient& patient, const std::string& date);

    const double calculerPrix() const override;

    const std::string& getPrescription() const;
    void setPrescription(const std::string prescription);

private:
    std::string prescription_;
};

#endif // CONSULTATIONPHYSIQUE_H
