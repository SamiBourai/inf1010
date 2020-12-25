//! Class Personnel
//! \authors Ahmed Hammami & Youssef Ben Taleb
//! \date 05 juin 2020

#include "Personnel.h"
#include <iostream>
#include <typeinfo>

//! Constructeur par paramétre  de la classe de base Personnel
//! \param nom Nom du personnel
//! \param id  L'identifiant du personnel
Personnel::Personnel(const std::string& nom, const std::string& id, const tm& dateAdhesion): nom_(nom), id_(id), dateAdhesion_(dateAdhesion)
{
}

//! Opérateur qui compare un string avec l'identifiant du personnel avec un personnel comme opérande de gauche
//! \param id  L'identifiant  avec le quel on veut comparé le personnel
//! \return vrai si  Les identifiants sont identiques, faux sinon
bool Personnel::operator==(const std::string& id) const
{
	return (id_ == id);
}

bool Personnel::operator<(const Personnel& personnel)
{
	return getSalaireAnnuel() < personnel.getSalaireAnnuel();
}

//! Opérateur qui comparel'identifiant du personnel avec l'identifiant opérande de gauche.
//! \param id l'identifiant avec le quel on veut comparé le personnel
//! \param personnel le personne avec lequel on compare  de l'identifiant
bool operator==(const std::string& id, const Personnel& personnel)
{
	return (id == personnel.id_);
}

//! Méthode qui affiche les informations d'un personnel de l'hopital
//! \param stream Le stream dans lequel afficher.
void Personnel::afficher(std::ostream& os) const
{
	std::string typePersonnel = typeid(*this).name();
	os << "Personnel: " << nom_
		<< "\n\tType: " << typePersonnel.substr(6, typePersonnel.length() - 6 + 1)
		<< "\n\tIdentifiant: " << id_
		<< "\n\tStatut: " << (estActif_ ? "Actif" : "Inactif");
}

//! Méthode qui retourne le nom du personnel
//! \return le nom du personnel 
const std::string& Personnel::getNom() const
{

	return nom_;
}


//! Méthode qui retourne l'identifiant du personnel
//! \return id_ l'identifiant du personnel
const std::string& Personnel::getId() const
{

	return id_;
}

//! Méthode qui retourne le status du personnel
//! \return estActif_ le status du personnel
bool Personnel::getEstActif() const
{

	return estActif_;
}

//! Méthode qui retourne la date de l'adhesion du personnel
//! \return dateAdhesion_ la la date de l'adhesion du personnel 
const tm& Personnel::getDateAdhesion() const
{
	return dateAdhesion_;
}


//! Méthode qui met a jours le nom  du personnel
//! \pararm  nom  Le nom du personnel
void Personnel::setNom(const std::string& nom)
{
	nom_ = nom;
}

//! Méthode qui met a jours l'identifiant du personnel
//! \pararm  id  l'identifiant du personnel
void Personnel::setId(const std::string& id)
{
	id_ = id;
}

//! Méthode qui met a jours le statut  du personnel s' il est actif ou non
//! \pararm  boolean indiquant le  nouveau status du personnel
void Personnel::setEstActif(bool estActif)
{
	estActif_ = estActif;
}

//! Méthode qui permet de mettre à jour la date d'adhesion du personnel
//! \Param dateAdhesion La date de l'adhesion du personnel
void Personnel::setDateAdhesion(const tm& dateAdhesion)
{
	dateAdhesion_ = dateAdhesion;
}