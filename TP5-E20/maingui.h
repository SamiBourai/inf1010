/*
 * Copyright (C) 2015    Raphaël Beamonte <raphael.beamonte@polymtl.ca>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation  and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright holders nor the names of any
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * This file has been created for the purpose of the INF1010
 * course of École Polytechnique de Montréal.
 */

#ifndef MAINGUI_H
#define MAINGUI_H

#include <QMainWindow>
#include <QListWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QRadioButton>
#include <QPushButton>

#include <list>
#include "Hopital.h"

namespace Ui {
    class MainGui;
}

/**
 * @brief La classe MainGui pour créer l'intérface graphique en utilisant QT
 */
class MainGui : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainGui Le constructeur qui reçoit aucun paramètre ou le widget parent
     * @param parent Widget parent
     */
    explicit MainGui(QWidget *parent = 0);
    /**
     * @brief MainGui Le contructeur reçoit un pointer vers l'hôpital et le widget par s'il exist
     * @param hopital Le pointeur vers hôpital
     * @param parent Widget parent
     */
    explicit MainGui(Hopital* hopital, QWidget *parent = 0);
    /**
     * @brief ~MainGui Destructeur
     */
    ~MainGui();

public slots:
    /**
     * @brief filtrerList Le slot pour filter la liste suivant le paramaètre reçu.
     */
    void filtrerList(int);
    /**
     * @brief selectionnerPersonnel Le slot pour séléctionner un personnel d'un QListWidgetItem
     */
    void selectionnerPersonnel(QListWidgetItem*);
    /**
     * @brief viderAffichage pour vider les champs remplis
     */
    void viderAffichage();
    /**
     * @brief changerTypePersonnel Pour mettre à jour les champs quand un personnel est séléctionné.
     */
    void changerTypePersonnel(int);
    /**
     * @brief licencierToutLeMonde Pour congédier tout le monde
     */
    void licencierToutLeMonde();
    /**
     * @brief licencierPersonnelSelectionne pour congédier le personnel sélectionné
     */
    void licencierPersonnelSelectionne();
    /**
     * @brief creerPersonnel pour créer un personnel localement
     */
    void creerPersonnel();
    /**
     * @brief personnelAjouteAvecSucces Executé quand un personnel est ajouté
     */
    void personnelAjouteAvecSucces(Personnel*);
    /**
     * @brief personnelSupprimeAvecSucces Exécuté quand un personnel est supprimé
     */
    void personnelSupprimeAvecSucces(Personnel*);
    /**
     * @brief validerAjoutPersonnel Valider les entrées avant d'ajouter le personnel
     */
    void validerAjoutPersonnel(const std::string&);

private:
    /**
     * @brief setup Pour intialiser la GUI
     */
    void setup();
    /**
     * @brief setMenu Pour préparer le menu d'en haut de GUI
     */
    void setMenu();
    /**
     * @brief setUI Pour préaprer le contenu de la GUI
     */
    void setUI();
    /**
     * @brief chargerPersonnel pour charger la liste des personnels dans QListWidget
     */
    void chargerPersonnel();
    /**
     * @brief filterCacher fonction pour cacher ou non un personnel
     * @param personnel personnel à cacher
     */
    bool filterCacher(Personnel* personnel);

    // Attributs
    /**
     * @brief hopital_ Pour stocker l'hôpital utiliser dans la GUI
     */
    Hopital* hopital_;

    /**
     * @brief indexFiltreActuel_ l'index actuel à appliquer sur la liste des personnels
     */
    int indexFiltreActuel_;

    // Les attributes pour QObjects
    /**
     * @brief listePersonnel List graphique pour les personnels
     */
    QListWidget* listePersonnel;
    /**
     * @brief nomEditeur Zone text pour le nom du personnel
     */
    QLineEdit* nomEditeur;
    /**
     * @brief specialiteEditeur La liste des spécialités
     */
    QComboBox* specialiteEditeur;
    /**
     * @brief idEditeur Zone text pour l'id du personnel
     */
    QLineEdit* idEditeur;
    /**
     * @brief dateAdhesionEditeur Zone text pour la date d'adhésion du personnel
     */
    QLineEdit* dateAdhesionEditeur;
    /**
     * @brief dateDeNaissanceEditeur Zone text pour la date de naissance du médecin résident
     */
    QLineEdit* dateDeNaissanceEditeur;
    /**
     * @brief matriculeEditeur Zone text pour le matricule du médecin résident
     */
    QLineEdit* matriculeEditeur;
    /**
     * @brief etablissementEditeur Zone text pour l'établissement du médecin résident
     */
    QLineEdit* etablissementEditeur;
    /**
     * @brief salaireEditeur Zone text pour le salaire du personnel
     */
    QLineEdit* salaireEditeur;
    /**
     * @brief personnelTypeRadioButtons List des boutons radios pour le type de personnel(Médecin - Médecin résident)
     */
    std::list<QRadioButton*> personnelTypeRadioButtons;
    /**
     * @brief licencierButton Le bouton pour congédier un personnel
     */
    QPushButton* licencierButton;
    /**
     * @brief embaucherButton Le bouton pour embaucher un personnel
     */
    QPushButton* embaucherButton;
};

#endif // MAINGUI_H
