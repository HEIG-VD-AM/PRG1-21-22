/*
Nom du fichier : Uint.hpp
But : Fichier header de la classe Uint
Nom : Alexis Martins
Date : 15.12.2021
No. Laboratoire : 31
*/
#ifndef UINT_HPP
#define UINT_HPP

#include <vector>
#include <string>

const uint64_t BASE = 10;   //Base dans laquelle sont exprim�es les nombres
const uint64_t ZERO = 48;   //Code du caract�re ASCII '0'

class Uint
{
    //MUD = Membre Uint de droite
    //MUG = Membre Uint de gauche

    std::vector<uint64_t> nombre;    //Nombre repr�sent� par le Uint

    /// <summary>
    /// G�re le report de la retenu de la case actuelle � la case suivante
    /// </summary>
    void report();

    /// <summary>
    /// Permet de supprimer les �ventuelles z�ros en trop, notamment lors
    /// des entr�es utilisateurs et des op�rations (soustraction)
    /// </summary>
    void enleverZeros();

    /// <summary>
    /// V�rifie si le nombre Uint est un z�ro
    /// </summary>
    /// <returns>Vrai si le Uint est �gal � 0</returns>
    bool egalZero();

    /// <summary>
    /// V�rifie si lors d'op�ration telle que la division 
    /// le diviseur n'est pas �gal � 0
    /// Surcharge prenant un Uint en param�tres
    /// </summary>
    void verifierZero(Uint diviseur);

    /// <summary>
    /// V�rifie si lors d'op�ration telle que la division 
    /// le diviseur n'est pas �gal � 0
    /// Surcharge prenant un uint64_t en param�tres
    /// </summary>
    void verifierZero(uint64_t diviseur);

    /// <summary>
    /// M�thode retournant le r�sultat d'une division, ainsi que son reste
    /// Voir pseudo-code laboratoire 30 pour plus d'informations
    /// </summary>
    /// <param name="dividende">Uint utilis� comme dividende</param>
    /// <param name="diviseur">Uint utilis� commme diviseur</param>
    /// <param name="reste">Reste de la division</param>
    /// <returns></returns>
    Uint divisionReste(const Uint& dividende, const Uint& diviseur, 
                       Uint& reste);

    /// <summary>
    /// Permet de comparer la valeurs de deux Uint (Plus petit, grand ou �gal)
    /// </summary>
    /// <param name="mug">Premi�re valeur de comparaison</param>
    /// <param name="mud">Seconde valeur de comparaison</param>
    /// <returns>-1 si A < B, 0 si A = B et 1 si A > B</returns>
    friend int comp(const Uint& mug, const Uint& mud);

    /// <summary>
    /// Surcharge de l'op�rateur '+', en r�utilisant 
    /// l'op�rateur '+=' pour deux Uints
    /// </summary>
    /// <param name="mug">Premier nombre de l'op�ration</param>
    /// <param name="mud">Second nombre de l'op�ration</param>
    /// <returns>Addition des deux Uints</returns>
    friend Uint operator+(Uint mug, const Uint& mud);

    /// <summary>
    /// Surcharge de l'op�rateur '-', en r�utilisant 
    /// l'op�rateur '-=' pour deux Uints
    /// </summary>
    /// <param name="mug">Premier nombre de l'op�ration</param>
    /// <param name="mud">Second nombre de l'op�ration</param>
    /// <returns>Soustraction des deux Uints</returns>
    friend Uint operator-(Uint mug, const Uint& mud);

    /// <summary>
    /// Surcharge de l'op�rateur '*', en r�utilisant 
    /// l'op�rateur '*=' pour deux Uints
    /// </summary>
    /// <param name="mug">Premier nombre de l'op�ration</param>
    /// <param name="mud">Second nombre de l'op�ration</param>
    /// <returns>Multiplication des deux Uints</returns>
    friend Uint operator*(Uint mug, const Uint& mud);

    /// <summary>
    /// Surcharge de l'op�rateur '*', en r�utilisant 
    /// l'op�rateur '*=' pour un Uint et un scalaire
    /// </summary>
    /// <param name="mug">Premier nombre de l'op�ration</param>
    /// <param name="multiple">Scalaire</param>
    /// <returns>Multiplications de l'Uint et du scalaire</returns>
    friend Uint operator*(Uint mug, const uint64_t& multiple);

    /// <summary>
    /// Surcharge de l'op�rateur '*', en r�utilisant 
    /// l'op�rateur '*=' pour un Uint et un scalaire (autre sens)
    /// </summary>
    /// <param name="multiple">Scalaire</param>
    /// <param name="mug">Premier nombre de l'op�ration</param>
    /// <returns>Multiplications de l'Uint et du scalaire</returns>
    friend Uint operator*(const uint64_t& multiple, Uint mug);

    /// <summary>
    /// Surcharge de l'op�rateur '/', en r�utilisant 
    /// l'op�rateur '/=' pour deux Uint
    /// </summary>
    /// <param name="mug">Premier nombre de l'op�ration</param>
    /// <param name="diviseur">Second nombre Uint</param>
    /// <returns>Divison de l'Uint par le second</returns>
    friend Uint operator/(Uint mug, const uint64_t& diviseur);

    /// <summary>
    /// Surcharge de l'op�rateur '%', en r�utilisant 
    /// l'op�rateur '%=' pour deux Uint
    /// </summary>
    /// <param name="mug">Premier nombre de l'op�ration</param>
    /// <param name="diviseur"Second nombre Uint</param>
    /// <returns>Reste de la division</returns>
    friend Uint operator%(Uint mug, const uint64_t& diviseur);

    /// <summary>
    /// Surcharge de l'op�rateur '/', en r�utilisant 
    /// l'op�rateur '%='avec un scalaire
    /// </summary>
    /// <param name="mug">Premier nombre de l'op�ration</param>
    /// <param name="diviseur">Nombre diviseur de notre Uint</param>
    /// <returns>Divison de l'Uint par un nombre entier</returns>
    friend Uint operator/(Uint mug, const Uint& diviseur);

    /// <summary>
    /// Surcharge de l'op�rateur '%', en r�utilisant 
    /// l'op�rateur '%=' avec un scalaire
    /// </summary>
    /// <param name="mug">Premier nombre de l'op�ration</param>
    /// <param name="diviseur">Nombre diviseur de notre Uint</param>
    /// <returns>Reste de la division</returns>
    friend Uint operator%(Uint mug, const Uint& diviseur);

    /// <summary>
    /// Permet d'afficher les informations de nos Uints
    /// </summary>
    /// <param name="flux">R�f�rence au flux de sortie</param>
    /// <param name="mug">Uint � afficher</param>
    /// <returns>Nouveau flux</returns>
    friend std::ostream& operator<<(std::ostream& lhs, const Uint& mug);

    /// <summary>
    /// Permet de d'�crire depuis un flux dans un Uint
    /// </summary>
    /// <param name="is">R�f�rence au flux d'entr�e</param>
    /// <param name="mug">Uint vers lequel est dirig� le flux</param>
    /// <returns>Nouveau flux</returns>
    friend std::istream& operator>>(std::istream& lhs, Uint& mug);

    /// <summary>
    /// Calcul de l'exponentiation modulaire. 
    /// Voir le pseudo-code labo. 15 pour plus d'informations
    /// Nom en snake casee, car le programme rsa.cpp utilisait 
    /// l'expMod avec le nom mod_pow. Je me suis adapt� au rsa.cpp
    /// </summary>
    /// <param name="base">Premi�re valeur repr�sentant la base 
    /// du calcul</param>
    /// <param name="exposant">Seconde valeur rep�sentant l'exposant</param>
    /// <param name="modulo">Modulo utilis� pour le calcul</param>
    /// <returns>Entier contenant le r�sultat de l'exponentiation</returns>
    friend Uint mod_pow(Uint base, Uint exposant, const Uint& modulo);

    /// <summary>
    /// Classe Sint
    /// </summary>
    friend class Sint;

public:

    /// <summary>
    /// Constructeur vide de la classe Uint
    /// </summary>
    Uint() {};

    /// <summary>
    /// Constructeur de la classe Uint � partir d'une string
    /// </summary>
    /// <param name="texte">Nombre � stocker dans dans l'Uint</param>
    Uint(const std::string& texte);

    /// <summary>
    /// Constructeur de la classe Uint � partir d'un uint64_t
    /// </summary>
    /// <param name="nombre">uint64_t</param>
    Uint(const uint64_t& nombre) { *this = std::to_string(nombre); };

    /// <summary>
    /// Permet d'obtenir le nombre de chiffres d'un Uint
    /// </summary>
    /// <returns>Nombre de chiffres</returns>
    size_t getterTaille() const;

    /// <summary>
    /// D�fini si un Uint est pair ou non
    /// </summary>
    /// <returns>vrai si pair, sinon faux</returns>
    bool estPair() const;

    /// <summary>
    /// Surcharge de l'op�rateur '+=' entre deux Uints.
    /// Additionne le second Uint au premier
    /// </summary>
    /// <param name="mud">Second nombre de l'op�ration</param>
    /// <returns>Retourne le premier nombre contenant l'addition</returns>
    Uint& operator+=(const Uint& mud);

    /// <summary>
    /// Surcharge de l'op�rateur '-=' entre deux Uints.
    /// Soustrait le second Uint au premier si c'est possible
    /// </summary>
    /// <param name="mud">Second nombre de l'op�ration</param>
    /// <returns>Retourne le premier nombre contenant la soustraction</returns>
    Uint& operator-=(const Uint& mud);

    /// <summary>
    /// Surcharge de l'op�rateur '*=' entre deux Uints.
    /// </summary>
    /// <param name="mud">Second nombre de l'op�ration</param>
    /// <returns>Retourne le premier nombre contenant 
    /// la multiplication</returns>
    Uint& operator*=(const Uint& mud);

    /// <summary>
    /// Surcharge de l'op�rateur '*=' entre un Uint et un multiple
    /// </summary>
    /// <param name="multiple">Scalaire</param>
    /// <returns>Retourne le premier nombre contenant la multiplication 
    /// avec le scalaire</returns>
    Uint& operator*=(const uint64_t& multiple);

    /// <summary>
    /// Surcharge de l'op�rateur '/=' entre deux Uint
    /// </summary>
    /// <param name="diviseur">Nombre diviseur</param>
    /// <returns>Premier nombre avec le r�sultat de la divison</returns>
    Uint& operator/=(const Uint& diviseur);

    /// <summary>
    /// Surcharge de l'op�rateur '/=' entre deux Uint
    /// </summary>
    /// <param name="diviseur">Nombre diviseur</param>
    /// <returns>Premier nombre avec le reste de la division</returns>
    Uint& operator%=(const Uint& diviseur);

    /// <summary>
    /// Surcharge de l'op�rateur '/=' entre un Uint et un diviseur (nombre)
    /// </summary>
    /// <param name="diviseur">Nombre diviseur de notre Uint</param>
    /// <returns>Retourne le premier nombre contenant la divison</returns>
    Uint& operator/=(const uint64_t& diviseur);

    /// <summary>
    /// Surcharge de l'op�rateur '%=' entre un Uint et un diviseur (nombre)
    /// </summary>
    /// <param name="diviseur">diviseur">Nombre diviseur de notre Uint</param>
    /// <returns>Retourne le premier nombre contenant 
    /// le reste de la divison</returns>
    Uint& operator%=(const uint64_t& diviseur);

    /// <summary>
    /// Op�rateur de cast d'un Uint en uint64_t
    /// </summary>
    explicit operator uint64_t() const;

    /// <summary>
    /// Surcharge de l'op�rateur '++' pr�fix�
    /// </summary>
    /// <returns>Retourne le nombre incr�ment� de 1</returns>
    Uint& operator++();

    /// <summary>
    /// Surcharge de l'op�rateur '++' postfix�
    /// </summary>
    /// <param name="">Int permettant de diff�rencier postfix� 
    /// et pr�fix�</param>
    /// <returns>Retourne le nombre (non-incr�ment�), 
    /// puis l'incr�mente de 1</returns>
    Uint operator++(int);


    /// <summary>
    /// Surcharge de l'op�rateur '--' pr�fix�
    /// </summary>
    /// <returns>Retourne le nombre d�cr�ment� de 1</returns>
    Uint& operator--();

    /// <summary>
    /// Surcharge de l'op�rateur '--' postfix�
    /// </summary>
    /// <param name="">Int permettant de diff�rencier postfix� 
    /// et pr�fix�</param>
    /// <returns>Retourne le nombre (non-d�cr�ment�), 
    /// puis l'd�cr�mente de 1</returns>
    Uint operator--(int);

    /// <summary>
    /// Surcharge de l'op�rateur '>', entre deux Uints
    /// </summary>
    /// <param name="mud">Second nombre de la comparaison</param>
    /// <returns>Retourne vrai si le premier est plus grand que 
    /// le second</returns>
    bool operator>(const Uint& mud) const;

    /// <summary>
    /// Surcharge de l'op�rateur '<', entre deux Uints
    /// </summary>
    /// <param name="mud">Second nombre de la comparaison</param>
    /// <returns>Retourne vrai si le premier est plus petit que 
    /// le second</returns>
    bool operator<(const Uint& mud) const;

    /// <summary>
    /// Surcharge de l'op�rateur '>=', entre deux Uints
    /// </summary>
    /// <param name="mud">Second nombre de la comparaison</param>
    /// <returns>Retourne vrai si le premier est plus grand
    ///  ou �gal au second</returns>
    bool operator>=(const Uint& mud) const;

    /// <summary>
    /// Surcharge de l'op�rateur '<=', entre deux Uints
    /// </summary>
    /// <param name="mud">Second nombre de la comparaison</param>
    /// <returns>Retourne vrai si le premier est plus petit
    ///  ou �gal au second</returns>
    bool operator<=(const Uint& mud) const;

    /// <summary>
    /// Surcharge de l'op�rateur '==', entre deux Uints
    /// </summary>
    /// <param name="mud">Second nombre de la comparaison</param>
    /// <returns>Retourne vrai si le premier est �gal au second</returns>
    bool operator==(const Uint& mud) const;

    /// <summary>
    /// Surcharge de l'op�rateur '!=', entre deux Uints
    /// </summary>
    /// <param name="mud">Second nombre de la comparaison</param>
    /// <returns>Retourne vrai si le premier est diff�rent du second</returns>
    bool operator!=(const Uint& mud) const;
};

#endif
