#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <limits>

using namespace std;

class Vehicule {
protected:
    string marque;
    string modele;
    string immatriculation;
    bool disponible;
    double prixJournalier;

public:
    Vehicule(const string& marque, const string& modele, 
             const string& immatriculation, double prixJournalier)
        : marque(marque), modele(modele), immatriculation(immatriculation),
          disponible(true), prixJournalier(prixJournalier) {}
    
    virtual ~Vehicule() = default;
    
    string getMarque() const { return marque; }
    string getModele() const { return modele; }
    string getImmatriculation() const { return immatriculation; }
    bool estDisponible() const { return disponible; }
    double getPrixJournalier() const { return prixJournalier; }
    
    void setDisponible(bool disp) { disponible = disp; }
    
    virtual void afficherDetails() const = 0;
    
    void afficherInfoBase() const {
        cout << "Marque: " << marque << endl;
        cout << "Modele: " << modele << endl;
        cout << "Immatriculation: " << immatriculation << endl;
        cout << "Statut: " << (disponible ? "Disponible" : "Reserve") << endl;
        cout << "Prix journalier: " << prixJournalier << " dirham" << endl;
    }
};

class Voiture : public Vehicule {
private:
    int nombrePlaces;
    string typeCarburant;
    bool climatisation;

public:
    Voiture(const string& marque, const string& modele, 
            const string& immatriculation, double prixJournalier,
            int nombrePlaces, const string& typeCarburant, bool climatisation)
        : Vehicule(marque, modele, immatriculation, prixJournalier),
          nombrePlaces(nombrePlaces), typeCarburant(typeCarburant), climatisation(climatisation) {}
    
    int getNombrePlaces() const { return nombrePlaces; }
    string getTypeCarburant() const { return typeCarburant; }
    bool aClimatisation() const { return climatisation; }
    
    void afficherDetails() const override {
        cout << "\n--- DETAILS VOITURE ---" << endl;
        afficherInfoBase();
        cout << "Nombre de places: " << nombrePlaces << endl;
        cout << "Type de carburant: " << typeCarburant << endl;
        cout << "Climatisation: " << (climatisation ? "Oui" : "Non") << endl;
    }
};

class Camion : public Vehicule {
private:
    double capaciteCharge; // en tonnes
    double volume;         // en m³
    bool hayon;

public:
    Camion(const string& marque, const string& modele, 
           const string& immatriculation, double prixJournalier,
           double capaciteCharge, double volume, bool hayon)
        : Vehicule(marque, modele, immatriculation, prixJournalier),
          capaciteCharge(capaciteCharge), volume(volume), hayon(hayon) {}
    
    double getCapaciteCharge() const { return capaciteCharge; }
    double getVolume() const { return volume; }
    bool aHayon() const { return hayon; }
    
    void afficherDetails() const override {
        cout << "\n--- DETAILS CAMION ---" << endl;
        afficherInfoBase();
        cout << "Capacite de charge: " << capaciteCharge << " tonnes" << endl;
        cout << "Volume: " << volume << " m(3:cube)" << endl;
        cout << "Hayon elevateur: " << (hayon ? "Oui" : "Non") << endl;
    }
};

class Moto : public Vehicule {
private:
    int cylindree; // en cm³
    string type; // sportive, routière, etc.

public:
    Moto(const string& marque, const string& modele, 
         const string& immatriculation, double prixJournalier,
         int cylindree, const string& type)
        : Vehicule(marque, modele, immatriculation, prixJournalier),
          cylindree(cylindree), type(type) {}
    
    int getCylindree() const { return cylindree; }
    string getType() const { return type; }
    
    void afficherDetails() const override {
        cout << "\n--- DETAILS MOTO ---" << endl;
        afficherInfoBase();
        cout << "Cylindree: " << cylindree << " cm(3:cube)" << endl;
        cout << "Type: " << type << endl;
    }
};

class Client {
private:
    int id;
    string nom;
    string prenom;
    string telephone;
    string email;
    string numeroPermis;

public:
    Client(int id, const string& nom, const string& prenom, 
           const string& telephone, const string& email,
           const string& numeroPermis = "")
        : id(id), nom(nom), prenom(prenom), telephone(telephone), 
          email(email), numeroPermis(numeroPermis) {}
    
    int getId() const { return id; }
    string getNom() const { return nom; }
    string getPrenom() const { return prenom; }
    string getTelephone() const { return telephone; }
    string getEmail() const { return email; }
    string getNumeroPermis() const { return numeroPermis; }
    
    void setNumeroPermis(const string& num) { numeroPermis = num; }
    
    void afficherInfos() const {
        cout << "Client #" << id << ": " << prenom << " " << nom << endl;
        cout << "Telephone: " << telephone << ", Email: " << email << endl;
        if (!numeroPermis.empty()) {
            cout << "Numero de permis: " << numeroPermis << endl;
        }
    }
};

class DateReservation {
private:
    int jour;
    int mois;
    int annee;

public:
    DateReservation(int j, int m, int a) : jour(j), mois(m), annee(a) {
        // Vérification simple de la validité de la date
        if (jour < 1 || jour > 31 || mois < 1 || mois > 12 || annee < 2022) {
            throw invalid_argument("Date invalide");
        }
    }
    
    string toString() const {
        return to_string(jour) + "/" + to_string(mois) + "/" + to_string(annee);
    }
    
    // Pour comparer les dates (simplifié)
    bool operator<(const DateReservation& other) const {
        if (annee < other.annee) return true;
        if (annee > other.annee) return false;
        if (mois < other.mois) return true;
        if (mois > other.mois) return false;
        return jour < other.jour;
    }
    
    bool operator==(const DateReservation& other) const {
        return jour == other.jour && mois == other.mois && annee == other.annee;
    }
    
    // Calcul du nombre de jours entre deux dates (simplifié)
    int joursEntre(const DateReservation& other) const {
        // Très simplifié, ne prend pas en compte les jours par mois
        int jours = (other.annee - annee) * 365;
        jours += (other.mois - mois) * 30;
        jours += (other.jour - jour);
        return jours > 0 ? jours : 0;
    }
};

class Reservation {
private:
    int id;
    shared_ptr<Client> client;
    shared_ptr<Vehicule> vehicule;
    DateReservation dateDebut;
    DateReservation dateFin;
    double montantTotal;
    bool estConfirmee;
    string commentaire;

public:
    Reservation(int id, shared_ptr<Client> client, shared_ptr<Vehicule> vehicule, 
                const DateReservation& debut, const DateReservation& fin)
        : id(id), client(client), vehicule(vehicule), dateDebut(debut), dateFin(fin), 
          estConfirmee(false), commentaire("") {
            
        if (!vehicule->estDisponible()) {
            throw runtime_error("Le vehicule n'est pas disponible pour cette periode");
        }
        
        // Calcul du montant basé sur le nombre de jours
        int nombreJours = debut.joursEntre(fin);
        if (nombreJours == 0) nombreJours = 1; // Minimum 1 jour
        montantTotal = vehicule->getPrixJournalier() * nombreJours;
    }
    
    void confirmer() {
        estConfirmee = true;
        vehicule->setDisponible(false);
    }
    
    void annuler() {
        estConfirmee = false;
        vehicule->setDisponible(true);
    }
    
    void ajouterCommentaire(const string& com) {
        commentaire = com;
    }
    
    void afficherDetails() const {
        cout << "\n--- DETAILS RESERVATION #" << id << " ---" << endl;
        cout << "Statut: " << (estConfirmee ? "Confirmee" : "En attente") << endl;
        cout << "Periode: Du " << dateDebut.toString() << " au " << dateFin.toString() << endl;
        cout << "Montant total: " << montantTotal << " dirham" << endl;
        if (!commentaire.empty()) {
            cout << "Commentaire: " << commentaire << endl;
        }
        cout << "Informations client:" << endl;
        client->afficherInfos();
        cout << "Vehicule reserve:" << endl;
        vehicule->afficherDetails();
    }
    
    int getId() const { return id; }
    shared_ptr<Vehicule> getVehicule() const { return vehicule; }
    shared_ptr<Client> getClient() const { return client; }
    DateReservation getDateDebut() const { return dateDebut; }
    DateReservation getDateFin() const { return dateFin; }
    double getMontantTotal() const { return montantTotal; }
    bool getEstConfirmee() const { return estConfirmee; }
};

class ParcVehicules {
private:
    vector<shared_ptr<Vehicule>> vehicules;
    vector<shared_ptr<Client>> clients;
    vector<shared_ptr<Reservation>> reservations;
    int prochainIdReservation;
    int prochainIdClient;

public:
    ParcVehicules() : prochainIdReservation(1), prochainIdClient(1) {}
    
    void ajouterVehicule(shared_ptr<Vehicule> vehicule) {
        vehicules.push_back(vehicule);
    }
    
    shared_ptr<Client> ajouterClient(const string& nom, const string& prenom, 
                                     const string& telephone, const string& email,
                                     const string& numeroPermis = "") {
        auto client = make_shared<Client>(prochainIdClient++, nom, prenom, telephone, email, numeroPermis);
        clients.push_back(client);
        return client;
    }
    
    vector<shared_ptr<Vehicule>> rechercherVehiculesDisponibles() const {
        vector<shared_ptr<Vehicule>> disponibles;
        for (const auto& v : vehicules) {
            if (v->estDisponible()) {
                disponibles.push_back(v);
            }
        }
        return disponibles;
    }
    
    vector<shared_ptr<Vehicule>> rechercherVehiculeParType(const string& type) const {
        vector<shared_ptr<Vehicule>> resultat;
        for (const auto& v : vehicules) {
            if (type == "voiture" && dynamic_pointer_cast<Voiture>(v) != nullptr) {
                resultat.push_back(v);
            } else if (type == "camion" && dynamic_pointer_cast<Camion>(v) != nullptr) {
                resultat.push_back(v);
            } else if (type == "moto" && dynamic_pointer_cast<Moto>(v) != nullptr) {
                resultat.push_back(v);
            }
        }
        return resultat;
    }
    
    shared_ptr<Reservation> creerReservation(shared_ptr<Client> client, 
                                             shared_ptr<Vehicule> vehicule,
                                             const DateReservation& debut, 
                                             const DateReservation& fin) {
        try {
            auto reservation = make_shared<Reservation>(prochainIdReservation++, client, vehicule, debut, fin);
            reservations.push_back(reservation);
            return reservation;
        } catch (const exception& e) {
            throw runtime_error(string("Erreur lors de la creation de la reservation: ") + e.what());
        }
    }
    
    void afficherTousLesVehicules() const {
        cout << "\n=== LISTE DES VEHICULES ===" << endl;
        if (vehicules.empty()) {
            cout << "Aucun vehicule dans le parc." << endl;
            return;
        }
        
        for (const auto& v : vehicules) {
            v->afficherDetails();
            cout << "-------------------------" << endl;
        }
    }
    
    void afficherToutesLesReservations() const {
        cout << "\n=== LISTE DES RESERVATIONS ===" << endl;
        if (reservations.empty()) {
            cout << "Aucune reservation enregistree." << endl;
            return;
        }
        
        for (const auto& r : reservations) {
            r->afficherDetails();
            cout << "-------------------------" << endl;
        }
    }
    
    void afficherTousLesClients() const {
        cout << "\n=== LISTE DES CLIENTS ===" << endl;
        if (clients.empty()) {
            cout << "Aucun client enregistre." << endl;
            return;
        }
        
        for (const auto& c : clients) {
            c->afficherInfos();
            cout << "-------------------------" << endl;
        }
    }
    
    shared_ptr<Vehicule> trouverVehiculeParImmatriculation(const string& immat) const {
        for (const auto& v : vehicules) {
            if (v->getImmatriculation() == immat) {
                return v;
            }
        }
        return nullptr;
    }
    
    shared_ptr<Client> trouverClientParId(int id) const {
        for (const auto& c : clients) {
            if (c->getId() == id) {
                return c;
            }
        }
        return nullptr;
    }
    
    shared_ptr<Reservation> trouverReservationParId(int id) const {
        for (const auto& r : reservations) {
            if (r->getId() == id) {
                return r;
            }
        }
        return nullptr;
    }
    
    vector<shared_ptr<Reservation>> trouverReservationsParClient(int clientId) const {
        vector<shared_ptr<Reservation>> resultat;
        for (const auto& r : reservations) {
            if (r->getClient()->getId() == clientId) {
                resultat.push_back(r);
            }
        }
        return resultat;
    }
    
    void supprimerReservation(int id) {
        for (auto it = reservations.begin(); it != reservations.end(); ++it) {
            if ((*it)->getId() == id) {
                // Libérer le véhicule
                (*it)->getVehicule()->setDisponible(true);
                reservations.erase(it);
                cout << "Reservation #" << id << " supprimee avec succes." << endl;
                return;
            }
        }
        throw runtime_error("Reservation non trouvee");
    }
    
    // Statistiques
    void afficherStatistiques() const {
        int nbVoitures = 0, nbCamions = 0, nbMotos = 0;
        int nbDisponibles = 0, nbReserves = 0;
        double revenuTotal = 0.0;
        
        for (const auto& v : vehicules) {
            if (dynamic_pointer_cast<Voiture>(v)) nbVoitures++;
            else if (dynamic_pointer_cast<Camion>(v)) nbCamions++;
            else if (dynamic_pointer_cast<Moto>(v)) nbMotos++;
            
            if (v->estDisponible()) nbDisponibles++;
            else nbReserves++;
        }
        
        for (const auto& r : reservations) {
            if (r->getEstConfirmee()) {
                revenuTotal += r->getMontantTotal();
            }
        }
        
        cout << "\n=== STATISTIQUES DU PARC ===" << endl;
        cout << "Nombre total de vehicules: " << vehicules.size() << endl;
        cout << "  - Voitures: " << nbVoitures << endl;
        cout << "  - Camions: " << nbCamions << endl;
        cout << "  - Motos: " << nbMotos << endl;
        cout << "Vehicules disponibles: " << nbDisponibles << endl;
        cout << "Vehicules reserves: " << nbReserves << endl;
        cout << "Nombre de clients: " << clients.size() << endl;
        cout << "Nombre de reservations: " << reservations.size() << endl;
        cout << "Revenu total des reservations confirmees: " << revenuTotal << " dirham" << endl;
    }
};

// Fonctions utilitaires pour l'interface utilisateur
void afficherMenu() {
    cout << "\n===== GESTION DE PARC AUTOMOBILE =====" << endl;
    cout << "1. Afficher tous les vehicules" << endl;
    cout << "2. Afficher les vehicules disponibles" << endl;
    cout << "3. Rechercher un vehicule par immatriculation" << endl;
    cout << "4. Rechercher des vehicules par type" << endl;
    cout << "5. Ajouter un nouveau client" << endl;
    cout << "6. Afficher tous les clients" << endl;
    cout << "7. Creer une reservation" << endl;
    cout << "8. Afficher toutes les reservations" << endl;
    cout << "9. Rechercher les reservations d'un client" << endl;
    cout << "10. Annuler une reservation" << endl;
    cout << "11. Afficher les statistiques" << endl;
    cout << "12. Ajouter un nouveau vehicule" << endl;
    cout << "0. Quitter" << endl;
    cout << "Votre choix: ";
}

void viderBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int lireEntier() {
    int choix;
    cin >> choix;
    viderBuffer();
    return choix;
}

double lireDouble() {
    double valeur;
    cin >> valeur;
    viderBuffer();
    return valeur;
}

string lireString() {
    string texte;
    getline(cin, texte);
    return texte;
}

bool lireBoolean() {
    string reponse;
    getline(cin, reponse);
    return (reponse == "o" || reponse == "O" || reponse == "oui" || reponse == "Oui");
}

void afficherVehicule(shared_ptr<Vehicule> vehicule) {
    if (!vehicule) {
        cout << "Vehicule non trouve" << endl;
        return;
    }
    vehicule->afficherDetails();
}

void rechercherVehiculeParImmatriculation(const ParcVehicules& parc) {
    cout << "Entrez l'immatriculation: ";
    string immat = lireString();
    auto vehicule = parc.trouverVehiculeParImmatriculation(immat);
    afficherVehicule(vehicule);
}

void rechercherVehiculeParType(const ParcVehicules& parc) {
    cout << "Quel type de vehicule? (voiture, camion, moto): ";
    string type = lireString();
    
    if (type != "voiture" && type != "camion" && type != "moto") {
        cout << "Type non reconnu. Utilisez 'voiture', 'camion' ou 'moto'." << endl;
        return;
    }
    
    auto vehicules = parc.rechercherVehiculeParType(type);
    
    if (vehicules.empty()) {
        cout << "Aucun vehicule de ce type trouve." << endl;
        return;
    }
    
    cout << "\n=== " << type << "S DISPONIBLES ===" << endl;
    for (const auto& v : vehicules) {
        v->afficherDetails();
        cout << "-------------------" << endl;
    }
}

shared_ptr<Client> ajouterNouveauClient(ParcVehicules& parc) {
    cout << "Nom: ";
    string nom = lireString();
    
    cout << "Prenom: ";
    string prenom = lireString();
    
    cout << "Telephone: ";
    string telephone = lireString();
    
    cout << "Email: ";
    string email = lireString();
    
    cout << "Numero de permis: ";
    string permis = lireString();
    
    try {
        auto client = parc.ajouterClient(nom, prenom, telephone, email, permis);
        cout << "Client ajoute avec succes! ID: " << client->getId() << endl;
        return client;
    } catch (const exception& e) {
        cout << "Erreur lors de l'ajout du client: " << e.what() << endl;
        return nullptr;
    }
}

void creerReservation(ParcVehicules& parc) {
    // Vérifier si des véhicules sont disponibles
    auto disponibles = parc.rechercherVehiculesDisponibles();
    if (disponibles.empty()) {
        cout << "Desole, aucun vehicule n'est disponible actuellement." << endl;
        return;
    }
    
    // Choisir un client
    cout << "ID du client (ou 0 pour creer un nouveau client): ";
    int clientId = lireEntier();
    
    shared_ptr<Client> client;
    if (clientId == 0) {
        client = ajouterNouveauClient(parc);
        if (!client) return;
    } else {
        client = parc.trouverClientParId(clientId);
        if (!client) {
            cout << "Client non trouve." << endl;
            return;
        }
    }
    
    // Afficher les véhicules disponibles
    cout << "\n=== VEHICULES DISPONIBLES ===" << endl;
    for (const auto& v : disponibles) {
        cout << "Immatriculation: " << v->getImmatriculation() << " - ";
        cout << v->getMarque() << " " << v->getModele() << " (";
        
        if (dynamic_pointer_cast<Voiture>(v)) cout << "Voiture";
        else if (dynamic_pointer_cast<Camion>(v)) cout << "Camion";
        else if (dynamic_pointer_cast<Moto>(v)) cout << "Moto";
        
        cout << ") - " << v->getPrixJournalier() << " Dh/jour" << endl;
    }
    
    // Choisir un véhicule
    cout << "\nImmatriculation du vehicule a reserver: ";
    string immat = lireString();
    auto vehicule = parc.trouverVehiculeParImmatriculation(immat);
    
    if (!vehicule) {
        cout << "Vehicule non trouve." << endl;
        return;
    }
    
    if (!vehicule->estDisponible()) {
        cout << "Ce vehicule n'est pas disponible." << endl;
        return;
    }
    
    // Dates de réservation
    cout << "Date de debut (jour): ";
    int jour1 = lireEntier();
    
    cout << "Date de debut (mois): ";
    int mois1 = lireEntier();
    
    cout << "Date de debut (annee): ";
    int annee1 = lireEntier();
    
    cout << "Date de fin (jour): ";
    int jour2 = lireEntier();
    
    cout << "Date de fin (mois): ";
    int mois2 = lireEntier();
    
    cout << "Date de fin (annee): ";
    int annee2 = lireEntier();
    
    try {
        DateReservation debut(jour1, mois1, annee1);
        DateReservation fin(jour2, mois2, annee2);
        
        auto reservation = parc.creerReservation(client, vehicule, debut, fin);
        
        cout << "\nReservation creee avec succes!" << endl;
        cout << "Montant total: " << reservation->getMontantTotal() << " dirham" << endl;
        
        cout << "Confirmer la reservation? (o/n): ";
        if (lireBoolean()) {
            reservation->confirmer();
            cout << "Reservation confirmee!" << endl;
        } else {
            cout << "Reservation en attente de confirmation." << endl;
        }
        
    } catch (const exception& e) {
        cout << "Erreur: " << e.what() << endl;
    }
}

void rechercherReservationsClient(const ParcVehicules& parc) {
    cout << "ID du client: ";
    int clientId = lireEntier();
    
    auto client = parc.trouverClientParId(clientId);
    if (!client) {
        cout << "Client non trouve." << endl;
        return;
    }
    
    cout << "\nReservations pour " << client->getPrenom() << " " << client->getNom() << ":" << endl;
    
    auto reservations = parc.trouverReservationsParClient(clientId);
    if (reservations.empty()) {
        cout << "Aucune reservation trouvee pour ce client." << endl;
        return;
    }
    
    for (const auto& r : reservations) {
        r->afficherDetails();
        cout << "-------------------------" << endl;
    }
}

void annulerReservation(ParcVehicules& parc) {
    cout << "ID de la reservation a annuler: ";
    int reservationId = lireEntier();
    
    try {
        parc.supprimerReservation(reservationId);
    } catch (const exception& e) {
        cout << "Erreur: " << e.what() << endl;
    }
}

void ajouterNouveauVehicule(ParcVehicules& parc) {
    cout << "Type de vehicule (1: Voiture, 2: Camion, 3: Moto): ";
    int type = lireEntier();
    
    cout << "Marque: ";
    string marque = lireString();
    
    cout << "Modele: ";
    string modele = lireString();
    
    cout << "Immatriculation: ";
    string immat = lireString();
    
    cout << "Prix journalier (Dh): ";
    double prix = lireDouble();
    
    try {
        shared_ptr<Vehicule> vehicule;
        
        switch (type) {
            case 1: { // Voiture
                cout << "Nombre de places: ";
                int places = lireEntier();
                
                cout << "Type de carburant: ";
                string carburant = lireString();
                
                cout << "Climatisation (o/n): ";
                bool clim = lireBoolean();
                
                vehicule = make_shared<Voiture>(marque, modele, immat, prix, places, carburant, clim);
                break;
            }
            case 2: { // Camion
                cout << "Capacite de charge (tonnes): ";
                double capacite = lireDouble();
                
                cout << "Volume (m cube): ";
                double volume = lireDouble();
                
                cout << "Hayon elevateur (o/n): ";
                bool hayon = lireBoolean();
                
                vehicule = make_shared<Camion>(marque, modele, immat, prix, capacite, volume, hayon);
                break;
            }
            case 3: { // Moto
                cout << "Cylindree (cm cube): ";
                int cylindree = lireEntier();
                
                cout << "Type de moto: ";
                string typeMoto = lireString();
                
                vehicule = make_shared<Moto>(marque, modele, immat, prix, cylindree, typeMoto);
                break;
            }
            default:
                cout << "Type de vehicule non reconnu." << endl;
                return;
        }
        
        parc.ajouterVehicule(vehicule);
        cout << "Vehicule ajoute avec succes!" << endl;
        
    } catch (const exception& e) {
        cout << "Erreur lors de l'ajout du vehicule: " << e.what() << endl;
    }
}

// Fonction principale pour tester le système
int main() {
    ParcVehicules parc;
    
    // Ajouter quelques véhicules de démonstration
    parc.ajouterVehicule(make_shared<Voiture>("Renault", "Clio", "AB-123-CD", 45.0, 5, "Essence", true));
    parc.ajouterVehicule(make_shared<Voiture>("Peugeot", "308", "EF-456-GH", 55.0, 5, "Diesel", true));
    parc.ajouterVehicule(make_shared<Camion>("Iveco", "Daily", "IJ-789-KL", 120.0, 3.5, 12.0, true));
    parc.ajouterVehicule(make_shared<Moto>("Honda", "CBR", "MN-012-OP", 75.0, 600, "Sportive"));
    
    // Ajouter quelques clients de démonstration
    parc.ajouterClient("Morjan", "Khalid", "0622837578", "khalidmorjan37@gmail.com", "12345678");
    parc.ajouterClient("Lahraoui", "Anas", "0720434064", "lahraouianas16@gmail.com", "87654321");
    
    int choix;
    bool quitter = false;
    
    cout << "=== SYSTEME DE GESTION DE PARC AUTOMOBILE ===" << endl;
    cout << "Bienvenue dans le systeme de gestion de parc automobile." << endl;
    
    while (!quitter) {
        afficherMenu();
        
        try {
            choix = lireEntier();
            
            switch (choix) {
                case 0:
                    quitter = true;
                    cout << "Au revoir!" << endl;
                    break;
                    
                case 1:
                    parc.afficherTousLesVehicules();
                    break;
                    
                case 2: {
                    auto disponibles = parc.rechercherVehiculesDisponibles();
                    
                    cout << "\n=== VEHICULES DISPONIBLES ===" << endl;
                    if (disponibles.empty()) {
                        cout << "Aucun vehicule disponible." << endl;
                    } else {
                        for (const auto& v : disponibles) {
                            v->afficherDetails();
                            cout << "-------------------------" << endl;
                        }
                    }
                    break;
                }
                
                case 3:
                    rechercherVehiculeParImmatriculation(parc);
                    break;
                    
                case 4:
                    rechercherVehiculeParType(parc);
                    break;
                    
                case 5:
                    ajouterNouveauClient(parc);
                    break;
                    
                case 6:
                    parc.afficherTousLesClients();
                    break;
                    
                case 7:
                    creerReservation(parc);
                    break;
                    
                case 8:
                    parc.afficherToutesLesReservations();
                    break;
                    
                case 9:
                    rechercherReservationsClient(parc);
                    break;
                    
                case 10:
                    annulerReservation(parc);
                    break;
                    
                case 11:
                    parc.afficherStatistiques();
                    break;
                    
                case 12:
                    ajouterNouveauVehicule(parc);
                    break;
                    
                default:
                    cout << "Option non reconnue." << endl;
                    break;
            }
            
        } catch (const exception& e) {
            cout << "Erreur: " << e.what() << endl;
        }
        
        // Pause entre les actions
        if (!quitter) {
            cout << "\nAppuyez sur Entree pour continuer...";
            cin.get();
        }
    }
    
    return 0;
}