Ce programme permet une gestion interactive du parc de véhicules avec des fonctionnalités étendues et une interface conviviale en ligne de commande.
Le programme fonctionne comme un système interactif où l'utilisateur peut naviguer entre différentes options pour gérer le parc de véhicules, les clients et les réservations, avec une expérience proche d'une application de gestion professionnelle en ligne de commande.
Je vais vous expliquer le fonctionnement des principales fonctions du programme de gestion de parc de véhicules,
en expliquant leur logique et utilisation :
### Structure générale du programme
Le programme est construit autour de plusieurs classes qui représentent les différentes entités du système (véhicules, clients, réservations) et une classe centrale `ParcVehicules` qui gère l'ensemble.

### Fonctions principales

**1. La classe `Vehicule` et ses dérivées**
- C'est une classe abstraite avec une méthode virtuelle pure `afficherDetails()`
- Les trois classes dérivées (Voiture, Camion, Moto) héritent de cette classe et implémentent chacune leur propre version de `afficherDetails()`
- La fonction `estDisponible()` permet de vérifier si un véhicule peut être réservé

**2. Gestion des réservations**
- `creerReservation()` : Cette fonction prend un client, un véhicule et des dates, vérifie la disponibilité du véhicule, puis crée une nouvelle réservation
- Si le véhicule est déjà réservé, elle lance une exception
- Une fois la réservation créée, il faut la confirmer avec `confirmer()` qui change le statut du véhicule à "non disponible"

**3. Recherche de véhicules**
- `rechercherVehiculesDisponibles()` : Parcourt tous les véhicules et retourne uniquement ceux qui sont disponibles
- `rechercherVehiculeParType()` : Filtre les véhicules par leur type (voiture, camion, moto) en utilisant le polymorphisme et `dynamic_pointer_cast`
- `trouverVehiculeParImmatriculation()` : Recherche un véhicule spécifique par son immatriculation

**4. Interface utilisateur**
- Le menu principal affiche les options disponibles et récupère le choix de l'utilisateur
- `lireEntier()`, `lireString()`, etc. : Ces fonctions utilitaires gèrent proprement la saisie utilisateur et évitent les problèmes courants (buffer overflow, types incorrects)
- Chaque option du menu appelle une fonction spécifique qui effectue l'action correspondante

**5. Création d'un véhicule**
- L'utilisateur choisit d'abord le type de véhicule
- En fonction du type, le programme demande des informations spécifiques (nombre de places pour une voiture, capacité pour un camion, etc.)
- Un nouvel objet du type approprié est créé avec `make_shared` et ajouté au parc

**6. Gestion des clients**
- `ajouterNouveauClient()` : Demande les informations nécessaires à l'utilisateur et crée un nouveau client
- `trouverClientParId()` : Recherche un client existant par son identifiant

**7. Gestion des statistiques**
- `afficherStatistiques()` : Parcourt les collections de véhicules et de réservations pour calculer des métriques comme le nombre de véhicules disponibles, le revenu total des réservations, etc.

**8. Annulation d'une réservation**
- `supprimerReservation()` : Trouve la réservation par son ID, remet le véhicule associé comme disponible, puis supprime la réservation de la liste

**9. Gestion des dates**
- La classe `DateReservation` encapsule la logique des dates et fournit des méthodes pour comparer des dates et calculer des durées
- `joursEntre()` : Calcule approximativement le nombre de jours entre deux dates pour déterminer le prix total d'une réservation

**10. Gestion des exceptions**
- Toutes les fonctions qui peuvent rencontrer des erreurs sont entourées de blocs try/catch
- Les erreurs communes (véhicule non disponible, dates invalides, etc.) sont capturées et des messages appropriés sont affichés à l'utilisateur