#include <iostream>
#include <ctime>

// pour les nombres aléatoires
#include <random>
#include <cstring> // strlen

using namespace std;

// ======================================================================
// Couleur au hasard
std::uniform_int_distribution<int> distribution;
std::default_random_engine generateur(time(NULL)); /* NOT using std::random_device since not
                                                    * all compilers seems to support it :-( */

char tirer_couleur()
{
  static const char* const couleurs = ".RGBCYM";
  static const int nb = strlen(couleurs) - 1;

  return couleurs[distribution(generateur,
                               std::uniform_int_distribution<int>::param_type {0, nb})];
}

// ======================================================================
char poser_question()
{
  char lu(' ');
  cout << "Entrez une couleur : ";
  cin >> lu;
  return lu;
}

// ---- prototype -------------------------------------------------------
bool couleur_valide(char c);

// ======================================================================
char lire_couleur()
{
  char lu(poser_question());
  while (not couleur_valide(lu)) {
    cout << "'" << lu << "' n'est pas une couleur valide." << endl;
    cout << "Les couleurs possibles sont : ., R, G, B, C, Y ou M." << endl;
    lu = poser_question();
  }
  return lu;
}

// ======================================================================
void afficher_couleurs(char c1, char c2, char c3, char c4)
{
  cout << ' ' << c1 << ' ' << c2 << ' ' << c3 << ' ' << c4;
}

// ======================================================================
void afficher(int nb, char c)
{
  while (nb-- > 0) {
    cout << c;
  }
}

// ---- prototype -------------------------------------------------------
void afficher_reponses(char c1, char c2, char c3, char c4,
                       char r1, char r2, char r3, char r4);

// ======================================================================
void afficher_coup(char c1, char c2, char c3, char c4,
                   char r1, char r2, char r3, char r4)
{
  afficher_couleurs(c1, c2, c3, c4);
  cout << " : ";
  afficher_reponses(c1, c2, c3, c4,
                    r1, r2, r3, r4);
  cout << endl;
}

// ======================================================================
void message_gagne(int nb_coups)
{
  cout << "Bravo ! Vous avez trouvé en " << nb_coups << " coups." << endl;
}

// ======================================================================
void message_perdu(char c1, char c2, char c3, char c4)
{
  cout << "Perdu :-(" << endl;
  cout << "La bonne combinaison était : ";
  afficher_couleurs(c1, c2, c3, c4);
  cout << endl;
}

/*****************************************************
 * ComplÃ©ter le code Ã  partir d'ici
 *****************************************************/

// ======================================================================
bool couleur_valide(char c)
{
    return c == '.' || c == 'R' || c == 'G' || c == 'B' || c == 'C' || c == 'Y' || c == 'M';
}

// ======================================================================
bool verifier(char c1, char& c2, int& score)
{
    bool same_color = c1 == c2;
    if (same_color) {
        score = score + 1;
        c2 = 'x';
    }
    return same_color;
}

// ======================================================================
void apparier(char c, char& r1, char& r2, char& r3, int& score)
{
    if (!verifier(c, r1, score)) {
        if (!verifier(c, r2, score)) {
            verifier(c, r3, score);
        }
    }
}

// ======================================================================
void afficher_reponses(char c1, char c2, char c3, char c4,
                       char r1, char r2, char r3, char r4)
{

    int scoreHashtag(0);

    bool c1OK = verifier(c1, r1, scoreHashtag);
    bool c2OK = verifier(c2, r2, scoreHashtag);
    bool c3OK = verifier(c3, r3, scoreHashtag);
    bool c4OK = verifier(c4, r4, scoreHashtag);

    /*
    cout << endl;
    cout << r1 << endl;
    cout << r2 << endl;
    cout << r3 << endl;
    cout << r4 << endl;
    cout << c1 << endl;
    cout << c2 << endl;
    cout << c3 << endl;
    cout << c4 << endl;*/

    afficher(scoreHashtag, '#');

    int scoreMalPlacesMaisOK(0);

    if (!c1OK) apparier(c1, r2, r3, r4, scoreMalPlacesMaisOK);
    if (!c2OK) apparier(c2, r1, r3, r4, scoreMalPlacesMaisOK);
    if (!c3OK) apparier(c3, r1, r2, r4, scoreMalPlacesMaisOK);
    if (!c4OK) apparier(c4, r1, r2, r3, scoreMalPlacesMaisOK);

    afficher(scoreMalPlacesMaisOK, '+');

    int restants = 4 - scoreHashtag - scoreMalPlacesMaisOK;

    afficher(restants, '-');
    
}

// ======================================================================
bool gagne(char c1, char c2, char c3, char c4,
           char r1, char r2, char r3, char r4)
{
    return c1 == r1 && c2 == r2 && c3 == r3 && c4 == r4;
}

// ======================================================================
void jouer(int coups_max = 8)
{
    char r1 = tirer_couleur();
    char r2 = tirer_couleur();
    char r3 = tirer_couleur();
    char r4 = tirer_couleur();

    /*
    char r1 = '.';
    char r2 = '.';
    char r3 = 'M';
    char r4 = '.';*/

    char c1;
    char c2;
    char c3;
    char c4;

    int coups(0);

    do {

        c1 = lire_couleur();
        c2 = lire_couleur();
        c3 = lire_couleur();
        c4 = lire_couleur();

        coups++;

        afficher_coup(c1, c2, c3, c4, r1, r2, r3, r4);

    } while (!gagne(c1, c2, c3, c4, r1, r2, r3, r4) && coups < coups_max);

    // pourquoi le jeu s'est arrêté ? perdu ou gagné ?

    if (gagne(c1, c2, c3, c4, r1, r2, r3, r4)) {
        message_gagne(coups);
    } else {
        message_perdu(r1, r2, r3, r4);
    }
}

/*******************************************
 * Ne rien modifier aprÃ¨s cette ligne.
 *******************************************/

int main()
{
  jouer();
  return 0;
}
