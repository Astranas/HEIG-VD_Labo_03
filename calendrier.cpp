/*
  ---------------------------------------------------------------------------
  Fichier     : calendrier.cpp
  Nom du labo : Laboratoire 03
  Auteur(s)   : Flavio Sovilla, Nicolas Benitez
  Date        : 26.10.2020
  But         : Permettre à l'utilisateur d'entrer une date entre 1900
  					 et 2100. Le programme va par la suite ressortir le
  					 calendrier de l'année avec tous les mois et les dates
  					 des différents jours.

  Remarque(s) : Les valeurs de verifications d'une annee bissextile ont ete laissees
                en dur dans le code puisqu'elles proviennent d'une formule. C'est aussi
					 le cas pour la formule du calcul du bon jour du mois de janvier.

                Source pour calcul du jour du 1er Janvier :
                https://cs.uwaterloo.ca/~alopez-o/math-faq/node73.html

                Source pour calcul du nombre de jours dans 1 mois :
                http://www.dispersiondesign.com/articles/time/number_of_days_in_a_month

  Compilateur : MinGW-w64
  ---------------------------------------------------------------------------
*/
#include <cstdlib>  // Pour le EXIT_SUCCESS
#include <iostream> // Pour le flux
#include <limits>   // Pour le numeric_limits<streamsize>
#include <iomanip>  // Pour le setw(...)
#include <cmath>	  // Pour le calcul du jour du 1er Janvier -> fonction floor()

using namespace std;

#define VIDER_BUFFER cin.ignore(numeric_limits<streamsize>::max(),'\n')

int main() {

   // ----------------------------------------------------------------------------
   // Variables constantes
   const int ESPACE_JOURS      =    2,
             ESPACE_ALIGNEMENT =    3,
             NBRE_COLONNES     =    7,
             ANNEE_MIN         = 1900,
             ANNEE_MAX         = 2100,
             MOIS_DEPART       =    1,
             MOIS_FIN          =   12;

   // ----------------------------------------------------------------------------
   // Variables générales
   enum class Mois {
      JANVIER = 1,
      FEVRIER,
      MARS,
      AVRIL,
      MAI,
      JUIN,
      JUILLET,
      AOUT,
      SEPTEMBRE,
      OCTOBRE,
      NOVEMBRE,
      DECEMBRE
   };

   char choixUtilisateur;

   // ----------------------------------------------------------------------------
   // Message de bienvenue
   cout << "ce programme ..." << endl;

   // ----------------------------------------------------------------------------
   // Boucle de recommencement
   do{

      // ----------------------------------------------------------------------------
      // Variables utilisées pour gérer l'entree de l'utilisateur
      int  annee;

      bool verifAnnee = true,
           bissextile = true;

      // ----------------------------------------------------------------------------
      // Boucle Saisie utilisateur pour l'annee
      do {
         cout << "entrer une valeur [" << ANNEE_MIN << "-" << ANNEE_MAX << "] : ";
         cin >> annee;

         if (cin.fail()) {
            cin.clear();
         }
         VIDER_BUFFER;

         if (annee >= ANNEE_MIN && annee <= ANNEE_MAX) {
            verifAnnee = false;
         }
         else {
            cout << "/!\\ recommencer" << endl;
         }
      } while (verifAnnee);
      //FIN - Boucle Saisie utilisateur pour l'annee

      cout << endl;

      // ----------------------------------------------------------------------------
      // Vérification de l'année bissextile
      // Ne pas modifier les valeurs (voir remarques) !
      bissextile = (annee % 400 == 0 || (annee % 4 == 0 && annee % 100 != 0));

      // ----------------------------------------------------------------------------
      // Formule pour calculer le jour de la semaine pour le 1er janvier
      // Ne pas modifier les valeurs (voir remarques) !
      int decennie    = (annee % 100) - 1 ; // les deux derniers chiffres de l'annee
      int siecle 	    =  annee / 100;  	  // les deux premiers chiffres de l'annee
      int premierJanvier = (1
                            + (int)floor((2.6 * 11) - 0.2)
                            + (int)floor(decennie   /   4)
                            + (int)floor(siecle 	 /   4)
                            - 2 * siecle + decennie)
                            % 7;
      // Certains resultats peuvent etre negatifs et fausser le jour, c'est pourquoi
      // nous devons ajouter cette ligne dans le but de parer cette éventualiter
      premierJanvier = premierJanvier < 0 ? premierJanvier + 7 : premierJanvier;

      // Un decalage s'opere sur le 1er Janvier puisque le resultat du calcul precedent
      // se base sur une semaine commencant un dimanche
      // donc Dimanche = 0, Lundi = 1, Mardi = 2, etc...
      int jourDepart =
          premierJanvier == 0 ?
          premierJanvier  + 6 :
          premierJanvier  - 1 ;

      // ----------------------------------------------------------------------------
      // Boucle d'affichage du calendrier
      for (int i = MOIS_DEPART; i <= MOIS_FIN; ++i) {

         int nbreJour = 1;

         switch(i) {
            case (int)Mois::JANVIER:   cout << "JANVIER ";
                                       break;
            case (int)Mois::FEVRIER:   cout << "FEVRIER ";
                                       break;
            case (int)Mois::MARS:      cout << "MARS ";
                                       break;
            case (int)Mois::AVRIL:     cout << "AVRIL ";
                                       break;
            case (int)Mois::MAI:       cout << "MAI ";
                                       break;
            case (int)Mois::JUIN:      cout << "JUIN ";
                                       break;
            case (int)Mois::JUILLET:   cout << "JUILLET ";
                                       break;
            case (int)Mois::AOUT:      cout << "AOUT ";
                                       break;
            case (int)Mois::SEPTEMBRE: cout << "SEPTEMBRE ";
                                       break;
            case (int)Mois::OCTOBRE:   cout << "OCTOBRE ";
                                       break;
            case (int)Mois::NOVEMBRE:  cout << "NOVEMBRE ";
                                       break;
            case (int)Mois::DECEMBRE:  cout << "DECEMBRE ";
                                       break;
            default: break;
         }

         // ----------------------------------------------------------------------------
         // Calcul du nombre de jours d'un mois
         // On remarque un pattern qui se répète tous les 7 mois, dans lequel se trouve
         // un deuxième pattern se repetant tous les 2 mois. Il ne reste plus qu'a gerer
         // le mois de fevrier et les annees bissextiles. Cela donne le calcul suivant
         int nbreJoursMois = (i == 2) ? (28 + bissextile) : 31 - (i - 1) % 7 % 2;


         // ----------------------------------------------------------------------------
         // Affichage des colonnes avec gestion des espaces pour le jour de depart du
         // mois en cours
         cout << annee << endl;
         cout << " L  M  M  J  V  S  D" << endl;

         int sautJours = 0;

         while(jourDepart--) {
            cout << setw(ESPACE_ALIGNEMENT) << " ";

            ++sautJours;

            if (sautJours % NBRE_COLONNES == 0) {
               cout << endl;
            }
         }

         // ----------------------------------------------------------------------------
         // Affichage des jours du mois
         while(nbreJour <= nbreJoursMois){
            cout << setw(ESPACE_JOURS) << nbreJour << " ";

            ++nbreJour;
            ++sautJours;

            if (sautJours % NBRE_COLONNES == 0) {
               cout << endl;
            }
         }
         cout << endl;

         // On recalcule le jour de depart pour le mois suivant
         jourDepart = sautJours % NBRE_COLONNES;

         // On met un saut de ligne s'il n'y en a pas deja un
         if (jourDepart) {
            cout << endl;
         }
      } //FIN - Boucle d'affichage du calendrier

      // ----------------------------------------------------------------------------
      // Boucle Saisie utilisateur pour recommencer avec gestion des entrees erronees
      do{
         cout << "Voulez-vous recommencer [O/N] ? ";
         cin  >> choixUtilisateur;

         if (cin.fail()) {
            cin.clear();
         }
         VIDER_BUFFER;

      }while(choixUtilisateur != 'N' && choixUtilisateur != 'O');
      //FIN - Boucle Saisie utilisateur pour recommencer

   } while(choixUtilisateur == 'O');
   //FIN - Boucle de recommencement

   return EXIT_SUCCESS;
}