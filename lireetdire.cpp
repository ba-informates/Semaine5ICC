#include <iostream>
using namespace std;

int separer_chiffre_gauche(int& nombre)
{
  int dix(1);
  int temp(nombre);
  while (temp >= 10) {
    dix  *= 10;
    temp /= 10;
  }
  nombre %= dix;
  return temp;
}

/*****************************************************
 * ComplÃ©ter le code Ã  partir d'ici
 *****************************************************/

void ajouter_chiffre_droit(int& nombre, int chiffre)
{
    nombre = (nombre * 10) + chiffre;
}

void dire_chiffre(int& nombre, int repetitions_chiffre, int chiffre)
{
    ajouter_chiffre_droit(nombre, repetitions_chiffre);
    ajouter_chiffre_droit(nombre, chiffre);
}

int lire_et_dire(int nombre_a_traiter) // ex. 11, ou 21, 1221
{
    int temp_chiffre;
    int rep_chiffre_actuel = 0;
    int nombre_output = 0;
    while (nombre_a_traiter > 0) {
        int chiffre_actuel = separer_chiffre_gauche(nombre_a_traiter);
        if (chiffre_actuel == temp_chiffre) {
            rep_chiffre_actuel++;
        } else {
            // le nb a changé !
            if (rep_chiffre_actuel > 0) {
                dire_chiffre(nombre_output, rep_chiffre_actuel, temp_chiffre);
            }
            temp_chiffre = chiffre_actuel;
            rep_chiffre_actuel = 1;
        }
        // si on est arrivé à la fin du nombre à traiter, on ajoute la dernière trouvaille
        if (nombre_a_traiter == 0) {
            dire_chiffre(nombre_output, rep_chiffre_actuel, chiffre_actuel);
        }
    }
    cout << "on sort" << endl;
    cout << nombre_output << endl;
    return nombre_output;
}

/*******************************************
 * Ne rien modifier aprÃ¨s cette ligne.
 *******************************************/

void repeter_lire_et_dire(int& nombre, int fois)
{
  while (fois-- > 0) {
    nombre = lire_et_dire(nombre);
  }
}

int main()
{
  int nombre(1);
  int fois(1);
  cin >> nombre >> fois;
  repeter_lire_et_dire(nombre, fois);
  cout << nombre << endl;
  return 0;
}
