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

#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QStyle>
#include <QKeySequence>
#include <QMessageBox>

#include <QDebug>

#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QComboBox>
#include <QSlider>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLineEdit>
#include <QLabel>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <typeinfo>
#include <string>

#include "maingui.h"

#include "Hopital.h"
#include "Personnel.h"
#include "Medecin.h"
#include "MedecinResident.h"
#include "utils.h"
#include "Erreurs.h"
#include <iostream>

using namespace std;
using namespace utils;
Q_DECLARE_METATYPE(Personnel*)

MainGui::MainGui(QWidget *parent) :
    QMainWindow(parent)
{
    hopital_ = new Hopital("CHUM", "1051 Rue Sanguinet, Montréal, QC H2X 3E4");

    Medecin* medecin = new Medecin("John Laplace","M001", Medecin::Specialite::Cardiologue, utils::convertirStringDate("2019-12-12"));
    MedecinResident* medecinResident = new MedecinResident("Sarah Adams", "1997-02-02", "154564", "Polytechnique",
                                                           "MR001",Medecin::Specialite::Pediatre, utils::convertirStringDate("2019-12-12"));

    hopital_->ajouterPersonnel(*medecin);
    hopital_->ajouterPersonnel(*medecinResident);

    setup();
}

MainGui::~MainGui() {}

void MainGui::setup() {
    indexFiltreActuel_ = 0;

    // On crée notre menu et notre UI
    setMenu();
    setUI();

    /* TODO 1: la connexion des signaux de l'hopital avec leurs slots associés
     * On connecte les signaux de l'hopital aux slots créés localement pour agir suite à ces signaux
     * 1- Connecter le signal  personnelAjoute au slot correspondant
     * 2- Connecter le signal  personnelSupprime au slot correspondant
    */
    connect(hopital_, SIGNAL(personnelAjoute(Personnel*)), this, SLOT(personnelAjouteAvecSucces(Personnel*)));
    connect(hopital_, SIGNAL(personnelSupprime(Personnel*)), this, SLOT(personnelSupprimeAvecSucces(Personnel*)));

    // On charge la liste du personnel actuel
    chargerPersonnel();
}

void MainGui::setMenu() {
    // On crée un bouton 'quitter'
    QAction* quitter = new QAction(tr("&Quitter"), this);
    // On ajoute un raccourci clavier qui simulera l'appui sur ce bouton (Ctrl+Q)
    quitter->setShortcuts(QKeySequence::Quit);
    // On connecte le clic sur ce bouton avec l'action de clore le programme
    connect(quitter, SIGNAL(triggered()), this, SLOT(close()));

    // On crée un nouveau menu 'File'
    QMenu* menuFichier = menuBar()->addMenu(tr("&Fichier"));
    // Dans lequel on ajoute notre bouton 'quitter'
    menuFichier->addAction(quitter);
}

void MainGui::setUI() {
    /* TODO 2: Le sélecteur pour filtrer ce que l'on souhaite dans la liste
     * 1- Créer un pointeur vers un combobox (QComboBox*)  s'appelant afficherCombobox
     * 2- Ajouter les élements "Afficher tout", "Afficher les médecins" et "Afficher les médecins résidents" au combobox
     * 3- Connecter l'evenement du changement de la combobox à l'action correspondante
    */
    QComboBox* afficherCombobox = new QComboBox(this);
    afficherCombobox->addItem("Afficher tout");
    afficherCombobox->addItem("Afficher les médecins");
    afficherCombobox->addItem("Afficher les médecins résidents");
    connect(afficherCombobox, SIGNAL(currentIndexChanged(int)), this, SLOT(filtrerList(int)));

    // La liste du personnel
    listePersonnel = new QListWidget(this);
    listePersonnel->setSortingEnabled(true);
    /* TODO 3:
     * Connecter le signal l'evenement du clique sur un élement de la liste au slot correspondant
    */
    connect(listePersonnel, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(selectionnerPersonnel(QListWidgetItem*)));

    // Le bouton pour congédier tout le monde
    QPushButton* licencierToutLeMondeButton = new QPushButton(this);
    licencierToutLeMondeButton->setText("Licencier tout le monde");
    /* TODO 4:
     * Connecter l'évenement du clique sur le bouton à l'action correspondante
    */

    connect(licencierToutLeMondeButton, SIGNAL(clicked()), this, SLOT(licencierToutLeMonde()));

    /* TODO 5: Le bouton pour embaucher un membre du personnel
     * 1- Créer le bouton embaucherPersonnelButton
     * 2- Modifier son texte au texte "Embaucher personnel"
     * 3- Connecter l'évenement du clique sur le bouton à l'action correspondante
    */
    QPushButton* embaucherPersonnelButton = new QPushButton(this);
    embaucherPersonnelButton->setText("Embaucher personnel");
    connect(embaucherPersonnelButton, SIGNAL(clicked()), this, SLOT(viderAffichage()));      // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    // Le premier layout, pour la colonne de gauche, dans lequel on insère les
    // éléments que l'on veut dans l'ordre dans lequel on veut qu'ils apparaissent
    QVBoxLayout* listLayout = new QVBoxLayout;

    /* TODO 6: Le bouton pour embaucher un personnel
     * 1- ajouter la combobox créée ci-dessus au layout listLayout
     * 2- ajouter listePersonnel créée ci-dessus au layout listLayout
     * 3- ajouter le bouton licencierToutLeMondeButton créé ci-dessus au layout listLayout
     * 4- ajouter le bouton embaucherPersonnelButton créé ci-dessus au layout listLayout
    */
    listLayout->addWidget(afficherCombobox);
    listLayout->addWidget(listePersonnel);
    listLayout->addWidget(licencierToutLeMondeButton);
    listLayout->addWidget(embaucherPersonnelButton);

    // Champ pour le nom
    QLabel* nomLabel = new QLabel;
    nomLabel->setText("Nom:");
    nomEditeur = new QLineEdit;

    QHBoxLayout* nomLayout = new QHBoxLayout;
    nomLayout->addWidget(nomLabel);
    nomLayout->addWidget(nomEditeur);

    /* TODO 7: Champ pour la specialité
     * 1- Créer le label specialiteLabel
     * 2- Modifier son texte au texte "Spécialité:"
     * 3- Créer un pointeur vers un combobox (QComboBox*)  s'appelant specialiteCombobox
     * 4- Ajouter les élements "Généraliste", "Cardiologue", "Dermatologue", "Gynecologue", "Pediatre", "Ophtalmologue" et "Autre" au combobox
     * 5- Affecter le pointeur de la combobox specialiteLabel au specialiteEditeur
     * 6- Créer un layout horizontal QHBoxLayout* nommé specialiteListLayout
     * 7- Ajouter le label specialiteLabel et la combobox specialiteCombobox au layout specialiteListLayout
    */
    QLabel* specialiteLabel = new QLabel;
    specialiteLabel->setText("Spécialité:");

    QComboBox* specialiteCombobox = new QComboBox(this);
    specialiteCombobox->addItem("Généraliste");
    specialiteCombobox->addItem("Cardiologue");
    specialiteCombobox->addItem("Dermatologue");
    specialiteCombobox->addItem("Gynecologue");
    specialiteCombobox->addItem("Pediatre");
    specialiteCombobox->addItem("Ophtalmologue");
    specialiteCombobox->addItem("Autre");

    specialiteEditeur = specialiteCombobox;

    QHBoxLayout* specialiteListLayout = new QHBoxLayout(this);
    specialiteListLayout->addWidget(specialiteLabel);
    specialiteListLayout->addWidget(specialiteCombobox);

    /* TODO 8: Inspirer vous du champs nom pour créer les différents champs réstants dans la UI
     * 1- Créer tous le champs manquants en vous référants aux captures d'écrans fournies avec l'énoncé
     * 2- La selection par défaut du personnel à créer est un médecin donc n'oubliez pas de noircir les champs non nécessaires pour
     * la création d'un médecin
     * 3- Mettez la valeur par défaut du pour le champ du salaire
    */

    // Champ pour l'id
    QLabel* idLabel = new QLabel;
    idLabel->setText("Numéro de licence:");
    idEditeur = new QLineEdit;

   QHBoxLayout* idLayout = new QHBoxLayout;
   idLayout->addWidget(idLabel);
   idLayout->addWidget(idEditeur);

    // Champ pour la date d'adhesion
    QLabel* dateAdhesionLabel = new QLabel;
    dateAdhesionLabel->setText("Date d'adhésion (AAAA-MM-JJ):");
    dateAdhesionEditeur = new QLineEdit;

    QHBoxLayout* dateAdhesionLayout = new QHBoxLayout;
    dateAdhesionLayout->addWidget(dateAdhesionLabel);
    dateAdhesionLayout->addWidget(dateAdhesionEditeur);

    // Champ pour le salaire
    QLabel* salaryLabel = new QLabel;
    salaryLabel->setText("Salaire de base:");
    salaireEditeur = new QLineEdit;
    salaireEditeur->setText(QString::number(Medecin::SALAIRE_DE_BASE_MEDECIN));
    salaireEditeur->setDisabled(true);

    QHBoxLayout* salaryLayout = new QHBoxLayout;
    salaryLayout->addWidget(salaryLabel);
    salaryLayout->addWidget(salaireEditeur);

    //les champs propres au médecin résident
    // Champ pour la date de naissance
    QLabel* dateDeNaissanceLabel = new QLabel;
    dateDeNaissanceLabel->setText("Date de naissance:");
    dateDeNaissanceEditeur = new QLineEdit;
    dateDeNaissanceEditeur->setDisabled(true);

    QHBoxLayout* dateDeNaissanceLayout = new QHBoxLayout;
    dateDeNaissanceLayout->addWidget(dateDeNaissanceLabel);
    dateDeNaissanceLayout->addWidget(dateDeNaissanceEditeur);

    // Champ pour matricule
    QLabel* matriculeLabel = new QLabel;
    matriculeLabel->setText("Matricule:");
    matriculeEditeur = new QLineEdit;
    matriculeEditeur->setDisabled(true);

    QHBoxLayout* matriculeLayout = new QHBoxLayout;
    matriculeLayout->addWidget(matriculeLabel);
    matriculeLayout->addWidget(matriculeEditeur);

    // Champ pour etablissement
    QLabel* etablissementLabel = new QLabel;
    etablissementLabel->setText("Établissement:");
    etablissementEditeur = new QLineEdit;
    etablissementEditeur->setDisabled(true);

    QHBoxLayout* etablissementLayout = new QHBoxLayout;
    etablissementLayout->addWidget(etablissementLabel);
    etablissementLayout->addWidget(etablissementEditeur);


    /* TODO 9: Boutons radio du choix entre médecin et médecin Résident
     * 1- Créer les deux bouton radio de type QRadioButton*
     * 2- Ajouter la sélection par défaut sur le bouton radio du médecin
     * 3- Ajouter les deux boutons au personnelTypeRadioButtons
    */
    QRadioButton* medecinButton = new QRadioButton("&Médecin", this);
    medecinButton->setChecked(true);
    personnelTypeRadioButtons.push_back(medecinButton);

    QRadioButton* medecinResidentButton = new QRadioButton("&Médecin Résident", this);
    personnelTypeRadioButtons.push_back(medecinResidentButton);


    QButtonGroup* personnelTypeButtonGroup = new QButtonGroup;
    /* TODO 10: Ajout des boutons radios au group de boutons
     * 1- Ajouter les deux boutons radios créés ci-dessus au personnelTypeButtonGroup
     * 2- Connecter le signal buttonClicked(int) de personnelTypeButtonGroup à son action associée
     * 3- Créer un layout horizontal
     * 4- Ajouter les deux boutons radios à la layout
    */
    personnelTypeButtonGroup->addButton(medecinButton);
    personnelTypeButtonGroup->addButton(medecinResidentButton);
    connect(personnelTypeButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(changerTypePersonnel(int)));

    QHBoxLayout* radioButtonLayout = new QHBoxLayout;
    radioButtonLayout->addWidget(medecinButton);
    radioButtonLayout->addWidget(medecinResidentButton);

    // Trait horizontal de séparation
    QFrame* horizontalFrameLine = new QFrame;
    horizontalFrameLine->setFrameShape(QFrame::HLine);

    // Bouton pour congédier la ou les personne(s)
    // sélectionnée(s) dans la liste
    licencierButton = new QPushButton(this);
    licencierButton->setText("Licencier");
    licencierButton->setDisabled(true);
    /* TODO 11: Connecter le clique du bouton licencierButton à son action associée
    */
    connect(licencierButton, SIGNAL(clicked()), this, SLOT(licencierPersonnelSelectionne()));

    // Bouton pour embaucher la personne dont on
    // vient d'entrer les informations
    embaucherButton = new QPushButton(this);
    embaucherButton->setText("Embaucher");
    /* TODO 12: Connecter le clique du bouton embaucherButton à son action associée
    */
    connect(embaucherButton, SIGNAL(clicked()), this, SLOT(creerPersonnel()));

    /* TODO 13: Organisation horizontale des boutons licencierButton et embaucherButton
     * 1- Créer un layout horizontal
     * 2- Ajouter les deux boutons à la layout
    */
    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(licencierButton);
    buttonLayout->addWidget(embaucherButton);

    /* TODO 14: Organisation pour la colonne de droite
     * 1- Créer un layout vertical nommé affichageLayout
     * 2- Ajouter le différents layout créées ci-dessus dans le bon ordre au layout vertical
    */

    QVBoxLayout* affichageLayout = new QVBoxLayout;
    affichageLayout->addLayout(specialiteListLayout);
    affichageLayout->addLayout(nomLayout);
    affichageLayout->addLayout(idLayout);
    affichageLayout->addLayout(dateAdhesionLayout);
    affichageLayout->addLayout(salaryLayout);
    affichageLayout->addLayout(dateDeNaissanceLayout);
    affichageLayout->addLayout(matriculeLayout);
    affichageLayout->addLayout(etablissementLayout);
    affichageLayout->addLayout(radioButtonLayout);
    affichageLayout->addWidget(horizontalFrameLine);
    affichageLayout->addLayout(buttonLayout);

    /* TODO 15: Trait vertical de séparation
     * 1- Créer un trait vertical de séparation nommé verticalFrameLine
     * Inspirez-vous de la création du trait horizontal ci-dessus
    */
    QFrame* verticalFrameLine = new QFrame;
    verticalFrameLine->setFrameShape(QFrame::VLine);

    /* TODO 16: Organisation principale
     * 1- Créer une organisation horizontale nommée mainLayout
     * 2- Ajouer en ordre, la layout listLayout, la ligne verticale verticalFrameLine
     * et le layout d'affichage affichageLayout au mainLayout
    */
    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addLayout(listLayout);
    mainLayout->addWidget(verticalFrameLine);
    mainLayout->addLayout(affichageLayout);


    /* TODO 17:
     * 1- Créer un nouveau widget QWidget*, et définissez son layout pour mainLayout
     * 2- Définissez ce widget comme le widget centrale de notre classe
     * et le layout d'affichage affichageLayout au mainLayout
    */
    QWidget* widget = new QWidget;
    widget->setLayout(mainLayout);
    setCentralWidget(widget);

    /* TODO 18: Titre de la fenêtre
     * 1- Mettez à jour le titre de la fenêtre comme celui fourni dans les captures
     * Le nom de l'hopital doit être chargé dynamiquement et pas hardcodé
    */
    string title = "Système de gestion de l'hopital " + hopital_->getNom();
    setWindowTitle(title.c_str());
}

void MainGui::chargerPersonnel() {
    // On s'assure que la liste est vide
    listePersonnel->clear();
    // Puis, pour tous les membres du personnel dans l'hôpital
    for (const auto& pair : hopital_->getGestionnairePersonnels().getPersonnels()) {
        // On récupère le pointeur vers le personnel
        if (pair.second.get() == nullptr) {
            continue;
        }
        // Et on l'ajoute en tant qu'item de la liste:
        // le nom sera affiché, et le pointeur sera contenu
        QListWidgetItem* item = new QListWidgetItem(
            QString::fromStdString(pair.second->getNom()), listePersonnel);
        item->setData(Qt::UserRole, QVariant::fromValue<Personnel*>(pair.second.get()));
        item->setHidden(filterCacher(pair.second.get()));
    }
}

bool MainGui::filterCacher(Personnel* personnel) {
    switch (indexFiltreActuel_) {
    case 1:
        return (typeid(*personnel) != typeid(Medecin));
    case 2:
        return (typeid(*personnel) != typeid(MedecinResident));
    case 0:
    default:
        return false;
    }
}

void MainGui::filtrerList(int index) {
    indexFiltreActuel_ = index;

    for (int i = 0; i < listePersonnel->count(); ++i) {
        QListWidgetItem *item = listePersonnel->item(i);
        Personnel* personnel = item->data(Qt::UserRole).value<Personnel*>();
        item->setHidden(filterCacher(personnel));
    }
}

void MainGui::selectionnerPersonnel(QListWidgetItem* item) {
    // Prendre le personnel sélctionner de la liste de séléction
    Personnel* personnel = item->data(Qt::UserRole).value<Personnel*>();
    Medecin* medecin = dynamic_cast<Medecin*>(personnel);

    // Mise à jour des boutons radios
    list<QRadioButton*>::iterator end = personnelTypeRadioButtons.end();
    for (list<QRadioButton*>::iterator it = personnelTypeRadioButtons.begin(); it != end; it++) {
        (*it)->setDisabled(true);

        if ((typeid(*personnel) == typeid(Medecin) && !(*it)->text().contains("Résident",Qt::CaseInsensitive))) {
                (*it)->setChecked(true);
        }
        else if ((typeid(*personnel) == typeid(MedecinResident) && (*it)->text().contains("Résident",Qt::CaseInsensitive))) {
                (*it)->setChecked(true);
        }
    }

    // Mise à jours du reste de la UI
    specialiteEditeur->setDisabled(true);
    Medecin::Specialite specialite = medecin->getSpecialite();
    specialiteEditeur->setCurrentIndex((int)specialite);

    nomEditeur->setDisabled(true);
    nomEditeur->setText(QString::fromStdString(medecin->getNom()));

    /* TODO 19: Completer la mise à jour de la UI en fonction de l'affichage fourni
     * Pour la date d'adhésion, utilisez la méthode convertirTmString du namespace utils
     * pour convertir la date d'un objet tm à string pour l'afficher
    */
    specialiteEditeur->setDisabled(true);
    idEditeur->setDisabled(true);
    idEditeur->setText(QString::fromStdString(medecin->getId()));

    dateAdhesionEditeur->setDisabled(true);
    string strDate = utils::convertirTmString(medecin->getDateAdhesion());
    dateAdhesionEditeur->setText(QString::fromStdString(strDate));

    salaireEditeur->setDisabled(true);
    salaireEditeur->setText(QString::number(medecin->getSalaireAnnuel()));

    dateDeNaissanceEditeur->setDisabled(true);
    dateDeNaissanceEditeur->setText("");

    matriculeEditeur->setDisabled(true);
    matriculeEditeur->setText("");

    etablissementEditeur->setDisabled(true);
    etablissementEditeur->setText("");

    if (typeid(*medecin) == typeid(MedecinResident)) {
        MedecinResident* medecinResident = dynamic_cast<MedecinResident*>(medecin);
        dateDeNaissanceEditeur->setText(QString::fromStdString(medecinResident->getDateDeNaissance()));
        matriculeEditeur->setText(QString::fromStdString(medecinResident->getMatricule()));
        etablissementEditeur->setText(QString::fromStdString(medecinResident->getEtablissement()));
    }

    licencierButton->setDisabled(false);
    embaucherButton->setDisabled(true);
}

void MainGui::viderAffichage() {

    specialiteEditeur->setDisabled(false);
    specialiteEditeur->setCurrentIndex(0);

    nomEditeur->setDisabled(false);
    nomEditeur->setText("");

    idEditeur->setDisabled(false);
    idEditeur->setText("");

    dateAdhesionEditeur->setDisabled(false);
    dateAdhesionEditeur->setText("");

    salaireEditeur->setDisabled(true);
    salaireEditeur->setText(QString::number(MedecinResident::SALAIRE_DE_BASE_MEDECIN_RESIDENT));

    matriculeEditeur->setText("");
    dateDeNaissanceEditeur->setText("");
    etablissementEditeur->setText("");

    list<QRadioButton*>::iterator end = personnelTypeRadioButtons.end();
    for (list<QRadioButton*>::iterator it = personnelTypeRadioButtons.begin(); it != end; it++) {
        (*it)->setDisabled(false);
        if ((*it)->text().endsWith("Médecin")) {
            (*it)->setChecked(true);
            matriculeEditeur->setDisabled(true);
            dateDeNaissanceEditeur->setDisabled(true);
            etablissementEditeur->setDisabled(true);
            salaireEditeur->setText(QString::number(Medecin::SALAIRE_DE_BASE_MEDECIN));
        }
    }

    listePersonnel->clearSelection();

    licencierButton->setDisabled(true);
    embaucherButton->setDisabled(false);

    nomEditeur->setFocus();
}

void MainGui::changerTypePersonnel(int index) {
    /* TODO 20:
     * Selon l'index récupéré du signal du groupe des boutons radios, désactiver
     * les champs en fonction du type du personnel choisi (comme illustré dans les exemples d'affichage fournis)
    */

    if (index == -2) {
        dateDeNaissanceEditeur->setDisabled(true);
        matriculeEditeur->setDisabled(true);
        etablissementEditeur->setDisabled(true);
        salaireEditeur->setText(QString::number(Medecin::SALAIRE_DE_BASE_MEDECIN));
    } else {
        dateDeNaissanceEditeur->setDisabled(false);
        matriculeEditeur->setDisabled(false);
        etablissementEditeur->setDisabled(false);
        salaireEditeur->setText(QString::number(MedecinResident::SALAIRE_DE_BASE_MEDECIN_RESIDENT));
    }
}

void MainGui::licencierToutLeMonde() {
    vector<Personnel*> aSupprimer;
    for (int i = 0; i < listePersonnel->count(); ++i) {
        QListWidgetItem *item = listePersonnel->item(i);
        aSupprimer.push_back(item->data(Qt::UserRole).value<Personnel*>());
    }

    for (Personnel* p : aSupprimer) {
        hopital_->supprimnerPersonnel(p->getId());
    }
}

void MainGui::licencierPersonnelSelectionne() {
    vector<Personnel*> toDelete;
    for (QListWidgetItem *item : listePersonnel->selectedItems()) {
        toDelete.push_back(item->data(Qt::UserRole).value<Personnel*>());
    }

    for (Personnel* p : toDelete) {
        hopital_->supprimnerPersonnel(p->getId());
    }
}

void MainGui::creerPersonnel() {
    // On va créer un nouveau personnel que l'on placera dans ce pointeur
    Personnel* nouveauPersonnel;

    // On créé le bon type du personnel selon le cas
    QRadioButton* typeSelectionne = 0;
    list<QRadioButton*>::iterator end = personnelTypeRadioButtons.end();
    for (auto it = personnelTypeRadioButtons.begin(); it != end; it++) {
        if ((*it)->isChecked()) {
            typeSelectionne = *it;
            break;
        }
    }

    /* TODO 20: Gérer les exceptions d'invalidité ou le manque d'information fournis lors de l'ajout d'un personnel en utilisant un try catch
     * Les type d'exception sont dans le fichiers Errors.h
     * Pour afficher les messages d'erreur utiliser QMessageBox::critical et afficher le message d'erreur de l'Exception lancée avec la méthode .what()
    */

    // On crée le bon type du personnel selon le cas
    string nom = nomEditeur->text().toStdString();
    string id = idEditeur->text().toStdString();
    string dateAdhesion = dateAdhesionEditeur->text().toStdString();
    string salaire = salaireEditeur->text().toStdString();
    try {
        if (typeSelectionne->text().endsWith("Médecin")) {
            validerAjoutPersonnel("Médecin");
            nouveauPersonnel = new Medecin(nom,
                                      id,
                                      static_cast<Medecin::Specialite>(specialiteEditeur->currentIndex()),

                                        utils::convertirStringDate(dateAdhesion)
                               );
        } else {
            validerAjoutPersonnel("Médecin Résident");
            string dateDeNaissance = dateDeNaissanceEditeur->text().toStdString();
            string matricule = matriculeEditeur->text().toStdString();
            string etablissement = etablissementEditeur->text().toStdString();

            nouveauPersonnel = new MedecinResident(nom,
                                                   dateDeNaissance,
                                                   matricule,
                                                   etablissement,
                                                   id,
                                                   static_cast<Medecin::Specialite>(specialiteEditeur->currentIndex()),
                                                   utils::convertirStringDate(dateAdhesion)
                                            );
        }

        /* TODO 21:
         * 1- Ajouter le nouveau personnel créé à l'hopital
         * 2- Vider l'affichage après l'ajout
        */
        hopital_->ajouterPersonnel(*nouveauPersonnel);
        viderAffichage();
    } catch(ErreurChamp e) {
        QMessageBox::critical(NULL, "Error message", e.what());
    }
    catch(DateInvalide a) {
            QMessageBox::critical(NULL, "Error message", a.what());
        }


}

void MainGui::personnelAjouteAvecSucces(Personnel* personnel) {
    // On ajoute le nouveau personnel comme item de la QListWidget
    QListWidgetItem* item = new QListWidgetItem(
        QString::fromStdString(personnel->getNom()), listePersonnel);
    item->setData(Qt::UserRole, QVariant::fromValue<Personnel*>(personnel));

    // On change la visibilité de notre nouveau personnel selon
    // le filtre actuel
    item->setHidden(filterCacher(personnel));
}

void MainGui::personnelSupprimeAvecSucces(Personnel* personnel) {
    // On cherche dans notre QlistWidget le personnel pour lequel le
    // signal a été envoyé, afin de l'en retirer
    for (int i = 0; i < listePersonnel->count(); ++i) {
        QListWidgetItem *item = listePersonnel->item(i);
        Personnel* p = item->data(Qt::UserRole).value<Personnel*>();
        if (p == personnel) {
            // delete sur un QlistWidget item va automatiquement le retirer de la liste
            delete item;
            // Si le personnel faisait partie de ceux créés localement, on veut le supprimer.
            hopital_->supprimnerPersonnel(personnel->getId());
            // Le personnel ne devrait être qu'une fois dans la liste...
            break;
        }
    }
    // On remet à zéro l'affichage de la colonne de gauche étant
    // donné que les personnels sélectionnés ont été supprimés
    viderAffichage();
}

void MainGui::validerAjoutPersonnel(const std::string& typePersonnel) {
    bool estNonVide = true;
    string nom = nomEditeur->text().toStdString();
    string id = idEditeur->text().toStdString();
    string dateAdhesion = dateAdhesionEditeur->text().toStdString();
    string salaire = salaireEditeur->text().toStdString();
    estNonVide = estNonVide && (nom != "" && id != "" && dateAdhesion != "" && salaire != "");

    if (typePersonnel == ("Médecin Résident")) {
        string dateDeNaissance = dateDeNaissanceEditeur->text().toStdString();
        string matricule = matriculeEditeur->text().toStdString();
        string etablissement = etablissementEditeur->text().toStdString();
        estNonVide = estNonVide && (etablissement != "" && matricule != "" && dateDeNaissance != "");
    }

    if (!estNonVide) {
        throw ErreurChamp("Veuillez remplir tous les champs");
    }


    bool validite1 = utils::validerDate(dateAdhesion);
    if(!validite1){
        throw DateInvalide("La date d'adhesion doit respectée le format AAAA-MM-JJ et doit être valide. Exemple : 1990-01-01");
    }


    /* TODO 22:
     * Lancer les exceptions appropriées en utilisant les exceptions du fichier Erreurs.h
     * Les messages d'erreur doivent correspondre à ceux des captures d'écran
     * hint : deux exceptions à lancer (la deuxième devrait utiliser la fonction validerDate du namespace utils)
    */
}
