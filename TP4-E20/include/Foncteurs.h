/*
-----------------------------------------------------------------------------------------------------------------------------
EN-TÊTE DU FICHIER
AUTEURS : Sami Bourai  ET Marlys Grace S.Tangni
MATRICULES : 2041659 ET 1986309
DATE : 14-juin-2020
CONTENU DU FICHIER : Contient l'implémentation de la classe Foncteur.h.
-----------------------------------------------------------------------------------------------------------------------------
*/
#ifndef FONCTEURS_H
#define FONCTEURS_H

#include "Consultation.h"
#include "Personnel.h"
#include "Patient.h"
#include <memory>
#include <utility>
#include<utils.h>



/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Foncteur ComparateurSecondElementPaire
* Description : Le template de classe generique qui prend deux paramètres, soit les types T1 et T2 tenus par une paire std::pair<T1, T2>.
* Parametre : L’opérateur() doit prendre en paramètre deux références constantes vers des paires dont les éléments sont de type T1 et T2.
* Retour :  Il retourne true si le second élément de la première paire est strictement inférieur au second élément de la deuxième paire, false sinon.
----------------------------------------------------------------------------------------------------------------------------
*/
template <typename T1, typename T2>
class ComparateurSecondElementPaire {
public:
	ComparateurSecondElementPaire() = default;

	const bool operator()(const std::pair<T1, T2>& x,const std::pair<T1, T2>& y)const  {
		bool correcte = true;
		if (x.second->getSalaireAnnuel()<y.second->getSalaireAnnuel())
		{
			return correcte;
		}
		return !correcte;

	}


};

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :  Foncteur ComparateurEstEgalAvecId
* Description : Le foncteur est une classe générique.
* Parametre : Le template de classe prend un seul paramètre de type T.
* Retour : Il retourne true si l’objet égale à l’id et false
----------------------------------------------------------------------------------------------------------------------------
*/
template <typename T>
class ComparateurEstEgalAvecId {
public:
	ComparateurEstEgalAvecId(const std::string& id): id_(id){}

	constexpr bool operator()(std::shared_ptr<T> typeObjet) {
		bool correcte = true;
		if (typeObjet->getNumeroAssuranceMaladie()==id_)
		{
			return correcte;
		}
		return !correcte;

	}


private:
	std::string id_;

};

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction : Foncteur AccumulateurPeriodePersonnel
* Description : Foncteur qui se charge de l'ajout de la période passée par les personnels à l'hôpital à une somme.
* Parametre : somme de type double,pair de type pair de string et shared_ptr de Personnel
* Retour : Il retourne la somme du paramètre somme et  de l’ancienneté du personnel passé en paramètre.
----------------------------------------------------------------------------------------------------------------------------
*/
class AccumulateurPeriodePersonnel {
public:

	AccumulateurPeriodePersonnel(double somme):somme_(somme){}
	double operator()(double somme, std::pair< const std::string, std::shared_ptr<Personnel>>(personne)) {
		
		tm tempsDebut=personne.second->getDateAdhesion(); 
		tm tempsActuel = getDateCourante();
		bool dateSontBonnes = comparerDate( tempsActuel,tempsDebut);
		double rien =0.0;
		if (!dateSontBonnes)   // verifier que la soustraction des dates ne donne pas un nombre inferieur a 0 - c-a-d (false)
		{
			return rien;		// dans un tel que ca retourne rien
		}
		int i = tempsActuel.tm_year - tempsDebut.tm_year;
		return somme_ = somme + i ;   // somme + l'experience de travail des annes passees
	}


private:

	double somme_;

};


/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :  Foncteur ComparateurTypePatient
* Description : Foncteur prédicat unaire servant à comparer un objet de type Patient à n’importe quel autre objet.
* Parametre : Le template de classe prend un seul paramètre de type T.un pointeur shared_ptr tenant un élément de type Patient
* Retour : Il retourne true si l’objet est de type Patient et false si non.
----------------------------------------------------------------------------------------------------------------------------
*/
template <typename T>
class ComparateurTypePatient {
public:

	bool operator()(const std::shared_ptr<Patient>patient) {
		bool estUnPatient = true;

		if (dynamic_cast<T*>(&*patient) != nullptr)
		{
			return estUnPatient;
		}
		return !estUnPatient; 
	}
};

/*
----------------------------------------------------------------------------------------------------------------------------
* Fonction :  EstDansIntervalleDatesConsultation
* Description : Foncteur prédicat unaire servant à déterminer si une consultation est réalisée entre deux dates.
* Parametre : deux dates debut et fin de consultation
* Retour : return true si la comparaison des date return des vrais sinon false
----------------------------------------------------------------------------------------------------------------------------
*/
class EstDansIntervalleDatesConsultation {

public:

	EstDansIntervalleDatesConsultation(const tm& premierTemps, const tm& dexiemeTemps):temps1_(premierTemps),temps2_(dexiemeTemps){}

	bool operator() (const std::shared_ptr<Consultation>& consultation1){
		
		tm dateConsultation1 = convertirStringDate(consultation1->getDate());
		bool comparerDateconsultationAvecTemps1 = comparerDate(dateConsultation1, temps1_);
		bool comparerDateconsultationAvecTemps2 = comparerDate(dateConsultation1, temps2_);
		if ((comparerDateconsultationAvecTemps1 && !comparerDateconsultationAvecTemps2) || (!comparerDateconsultationAvecTemps1 && comparerDateconsultationAvecTemps2))
		{
			return true;
		}

		return !true;
	}

private :
	tm temps1_;
	tm temps2_;

};






#endif // FONCTEURS_H
