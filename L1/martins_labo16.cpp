/*
Nom du fichier : martins_labo16
But : Impl�mentation de la m�thode de chiffrement asym�trique RSA
Nom : Alexis Martins
Date : 07.11.2021
No. Laboratoire : 16
*/
#include <iostream>
#include <random>
#include <functional>
#include <limits>

using namespace std;

const int32_t VALEUR_MIN = 1; ///Valeur minimum des chiffres entr�s
const int32_t VALEUR_MAX = numeric_limits<int32_t>::max(); //Valeur max 2^31 -1
const int32_t NBRE_MESSAGES = 10; //Nombres de messages de tests al�atoires
auto genInt = std::bind(std::uniform_int_distribution<int32_t> //Tirage al�atoire
    (1, VALEUR_MAX), std::mt19937(987));


/// <summary>
/// G�n�ration d'un entier al�atoire entre 2 et la limite des int. 
/// Puis, on applique un modulo de la limite maximum voulue pour avoir
/// un nombre compris dans la plage voulue.
/// </summary>
/// <param name="limiteMax">Limite maximum que peut avoir l'entier</param>
/// <returns>Entier al�atoire g�n�r� entre 2 et la limite fournie</returns>
int32_t generationAleatoire(int32_t limiteMax)
{
    /*
    On effectue le modulo ce qui nous donne un chiffre entre 0 et limiteMax - 1
    Puis on y additionne 1 pour que la plage soit entre 1 et limiteMax.
    */
    int32_t nombreAleatoire = genInt() % (limiteMax) + 1;

    return nombreAleatoire;
}

/// <summary>
/// Calcul de l'exponentiation modulaire. 
/// Voir le pseudo-code labo. 15 pour plus d'informations
/// </summary>
/// <param name="base">Premi�re valeur repr�sentant la base du calcul</param>
/// <param name="exposant">Seconde valeur rep�sentant l'exposant</param>
/// <param name="modulo">Modulo utilis� pour le calcul</param>
/// <returns>Entier contenant le r�sultat de l'exponentiation</returns>
int32_t expMod(int64_t base, int32_t exposant, int32_t modulo)
{
    //Resultat en 64_t, car il y'a des risques de d�passement pendant le calcul
    int64_t resultat = 1;
   
    while (exposant > 0)
    {     
        if (exposant % 2 == 0)
        {
            base = (base * base) % modulo;
            exposant /= 2;
        }
        else
        {
            resultat = (resultat * base) % modulo;
            exposant--;
        }
    }
    //On le convertit en 32_t, le r�sultat final ne d�passera pas cette valeur
    return (int32_t) resultat;
}

/// <summary>
/// Test de primalit�, afin de v�rifier si un nombre est probablement premier.
/// Voir le pseudo-code du labo. 16 pour plus d'informations sur ce test.
/// </summary>
/// <param name="nombrePremier">Nombre test� par le test de primalit�</param>
/// <returns>Retourne vrai, si le nombre entr� est premier. 
/// Sinon retourne faux</returns>
bool estPremier(int32_t nombrePremier)
{
    //Si le nombre est plus petit que 2, il n'est pas premier
    if (nombrePremier < 2)
    {
        return false;
    }

    //Si le nombre est �gal � 2, il est forc�ment premier
    if (nombrePremier == 2)
    {
        return true;
    }

    int32_t nombreAleatoire;

    for (int i = 0; i < 10; i++)
    {
        //G�n�ration du nombre al�atoire entre 2 et le nombre premier test�
        nombreAleatoire = generationAleatoire(nombrePremier - 1);

        /*
        On v�rifie que a^(p - 1) mod p soit diff�rent de 1, si
        c'est le cas il n'est pas premier.
        */
        if (expMod(nombreAleatoire, nombrePremier - 1, nombrePremier) != 1)
        {
            return false;
        }

        int32_t expModQ = 1;
        int32_t exposantU = nombrePremier - 1;

        while (exposantU % 2 == 0 && expModQ == 1)
        {
            exposantU /= 2;
            expModQ = expMod(nombreAleatoire, exposantU, nombrePremier);

            if (expModQ != 1 && expModQ != nombrePremier - 1)
            {
                return false;
            }
        }
    }

    /*
    Si aucune des v�rifications ci-dessus n'a abouti,
    le nombre est potentiellement premier
    */
    return true;
}

/// <summary>
/// Algoritme d'Euclide �tendu permettant de calculer le modulo inverse
/// de deux termes. Ce param�tre est pass� par r�f�rence pour le r�cup�rer
/// dans la suite du code 
/// Ainsi que leur PGDC qui est donn� dans le retour pour 
/// pouvoir utiliser la m�thode dans une condition directement
/// Voir le pseudo-code du labo. 16 pour plus d'informations sur l'algorithme
/// </summary>
/// <param name="termeA">Premier terme</param>
/// <param name="termeB">Second terme</param>
/// <param name="moduloInverse">Modulo inverse des 
/// deux termes en parametres</param>
/// <returns>Retourne le PGDC des deux nombres</returns>
int32_t euclideEtendu(int32_t termeA, int32_t termeB, int32_t& moduloInverse)
{
    int32_t r = termeA;
    int32_t rPrime = termeB;
    int32_t d = 0;
    int32_t dPrime = 1;
    int32_t q;
    int32_t rs;
    int32_t ds;

    while (rPrime != 0)
    {
        q = (int32_t) floor(r / rPrime);
        rs = r;
        ds = d;
        r = rPrime;
        d = dPrime;
        rPrime = rs - q * rPrime;
        dPrime = ds - q * dPrime;
    }

    if (d < 0)
    {
        d += termeA;
    }

    //Modulo inverse retourn� ici par r�f�rence
    moduloInverse = d;

    //PGDC retourn� ici en tant que retour de la fonction
    return r;
}

/// <summary>
/// M�thode qui permet de faire toutes les �tapes du chiffrements 
/// au d�chiffrement des messages (calculs et affichages),
/// et v�rifie que le message initial soit �quivalent au message decrypt�
/// </summary>
/// <param name="message">Message que l'on souhait (d�)chiffr�</param>
/// <param name="clePubliqueE">Premi�re partie de la cl� publique</param>
/// <param name="clePubliqueN">Seconde partie de la cl� publique</param>
/// <param name="clePriveeD">Cl� priv�e pour le d�chiffrement</param>
void chiffrementEtDechiffremenet(int32_t message, int32_t clePubliqueE, int32_t clePubliqueN, int32_t clePriveeD)
{
    //Chiffrement du message de Bob avec la cl� publique d'Alice
    int32_t messageCrypte = expMod(message, clePubliqueE, clePubliqueN);
    cout << "Message crypte : " << messageCrypte << endl;

    //D�chiffrement du message avec la cl� priv�e d'Alice
    int32_t messageDecrypte = expMod(messageCrypte, clePriveeD, clePubliqueN);
    cout << "Message decrypte : " << messageDecrypte << endl;


    //V�rifie que le message entr�e est �quivalent au message decrypt�
    if (message == messageDecrypte)
    {
        cout << "Test reussi !" << endl << endl;
    }
    else
    {
        cout << "Test echoue !" << endl << endl;
    }
}

/// <summary>
/// Fonction qui g�n�re 10 messages al�atoirement afin de 
/// tester le fonctionnement du chiffrement
/// </summary>
/// <param name="clePubliqueE">Premi�re partie de la cl� publique</param>
/// <param name="clePubliqueN">Deuxi�me partie de la cl� publique</param>
/// <param name="clePriveeD">Cl� priv�e servant au d�chiffrement</param>
void messagesTest(int32_t clePubliqueE, int32_t clePubliqueN, int32_t clePriveeD)
{
    int32_t message;

    cout << "Generation des messages aleatoires : " << endl;

    for (int i = 1; i <= NBRE_MESSAGES; i++)
    {
        cout << "TEST " << i << endl;

        //G�n�ration du message
        message = generationAleatoire(clePubliqueN - 1);
        cout << "Message de Bob : " << message << endl;

        chiffrementEtDechiffremenet(message, clePubliqueE, clePubliqueN, 
        clePriveeD);
    }
}

/// <summary>
/// V�rifie que l'entr�e utilisateur soit une entier
/// </summary>
/// <param name="entreeAVerifier">Entr�e de l'utilisateur</param>
void verificationEntreeNumerique(int32_t& entreeAVerifier)
{
    if (!(cin >> entreeAVerifier)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main()
{
    int32_t nombrePremierP;
    int32_t nombrePremierQ;

    /*
    L'utilisateur entre deux nombres premiers P et Q.
    V�rification que ceux-ci sont premiers et qu'ils ne sont pas trop grands
    */
    do
    {
        cout << "Entrer un nombre premier P : ";
        verificationEntreeNumerique(nombrePremierP);

        cout << "Entrer un nombre premier Q different de P : ";
        verificationEntreeNumerique(nombrePremierQ);

    /*
    Utilisation d'une division pour �viter le d�passement des int 
    lorsqu'on v�rifie que p*q < 2^31  - 1
    */
    } while (nombrePremierP == nombrePremierQ || nombrePremierP < VALEUR_MIN 
             || nombrePremierQ < VALEUR_MIN 
             || nombrePremierP >= VALEUR_MAX / nombrePremierQ 
             || !estPremier(nombrePremierP) || !estPremier(nombrePremierQ));

    //Calcul de phi qui permettra de calculer la cl� secr�te
    int32_t phi = (nombrePremierP - 1) * (nombrePremierQ - 1);
    int32_t clePubliqueE;
    int32_t clePriveeD;

    /*
    L'utilisateur entre un nombre E qui est une partie de la cl� publique, 
    on v�rifie que la valeur est premi�re avec P et Q (PGDC = 1) 
    et qu'elle n'est pas trop grande
    */
    do
    {
        cout << "Entrer un nombre qui est premier avec " << phi << " et "
             << "plus petit que cette meme valeur : ";

        verificationEntreeNumerique(clePubliqueE);

    } while (clePubliqueE >= phi || clePubliqueE < VALEUR_MIN 
             || clePubliqueE >= VALEUR_MAX 
             || euclideEtendu(phi, clePubliqueE, clePriveeD) != 1);

    //Calcul de la seconde partie de la cl� publique.
    int32_t clePubliqueN = nombrePremierP * nombrePremierQ;

    //Affichage de la paire E et N formant la cl� publique d'Alice
    cout << endl << "Cle publique d'Alice : e = " << clePubliqueE << " n = " 
         << clePubliqueN << endl;
     
    //On affiche la cl� priv�e d'Alice calcul�e dans Euclide etendu
    cout << "Cle secrete : " << clePriveeD << endl << endl;

    int32_t messageManuel;
    
    //Entr�e d'un message manuellement par l'utilisateur entre 1 et N - 1
    do
    {
        cout << "Message de Bob plus petit que " << clePubliqueN << " : ";
        verificationEntreeNumerique(messageManuel);

    } while (messageManuel < VALEUR_MIN || messageManuel > clePubliqueN - 1);


    chiffrementEtDechiffremenet(messageManuel, clePubliqueE, clePubliqueN, 
    clePriveeD);

    //G�n�ration automatique des messages exemples pour faire une v�rification
    messagesTest(clePubliqueE, clePubliqueN, clePriveeD);
}