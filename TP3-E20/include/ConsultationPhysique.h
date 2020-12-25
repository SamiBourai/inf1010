#ifndef CONSULTATIONPHYSIQUE_H
#define CONSULTATIONPHYSIQUE_H

#include <string>
#include"Consultation.h"


class ConsultationPhysique : public Consultation {

public:

	ConsultationPhysique(Medecin& medecin, Patient& patient, const std::string& date);


	const double calculerPrix() const;


	const std::string& getPrescription()const;
	


private: 
	std::string prescription_;
};
#endif // CONSULTATIONPHYSIQUE_H