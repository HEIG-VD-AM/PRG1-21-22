/*
Nom du fichier : Uint.cpp
But : Implantation d'une classe Uint permettant d'effectuer des op�rations
      sur des entiers positifs aribtrairement longs
Nom : Alexis Martins
Date : 15.12.2021
No. Laboratoire : 31
*/
#include "Uint.hpp"
#include <iostream>
#include <sstream>

//MUD = Membre Uint de droite
//MUG = Membre Uint de gauche

/////////////////////////////// CONSTRUCTEURS /////////////////////////////////

Uint::Uint(const std::string& texte)
{
    //Ajoute chaque nombre dans le vector en commen�ait par les unit�s
    for (auto i = texte.crbegin(); i != texte.crend(); ++i)
    {
        if (isdigit(*i))
        {
            this->nombre.push_back((uint64_t)*i - ZERO);
        }
        else
        {
            throw std::runtime_error("Valeur non-num�rique d�tect�e.");
        }
    }

    enleverZeros();
}

////////////////////////////// FONCTIONS AUTRES ///////////////////////////////

void Uint::report()
{
    for (size_t i = 0; i < nombre.size(); i++)
    {
        /*
        Si le nombre dans la case est sup�rieur � 9,
        il faut effectuer un report sur la prochaine case
        */
        if (nombre.at(i) > 9)
        {
            //Comme pr�c�demment, on �vite un d�passement de capacit�
            if (i != nombre.size() - 1)
            {
                //Report sur la prochaine case
                nombre.at(i + 1) += nombre.at(i) / BASE;
            }
            else
            {
                nombre.push_back(nombre.at(i) / BASE);

            }
            nombre.at(i) %= BASE;
        }
    }
}

Uint Uint::divisionReste(const Uint& dividende, const Uint& diviseur, Uint& reste)
{
    Uint puissance2(1), b = diviseur, quotient(0);

    while (b <= dividende)
    {
        puissance2 *= 2;
        b *= 2;
    }

    reste = dividende;

    while (reste >= diviseur)
    {
        b /= 2;
        puissance2 /= 2;

        if (reste >= b)
        {
            quotient += puissance2;
            reste -= b;
        }
    }

    return quotient;
}

void Uint::enleverZeros()
{
    while (nombre.size() > 1 && *(nombre.end() - 1) == 0)
    {
        nombre.erase((nombre.end() - 1));
    }
}

bool Uint::egalZero()
{
    if (nombre.size() == 1 && nombre.at(0) == 0)
    {
        return true;
    }
    return false;
}  

void Uint::verifierZero(Uint diviseur)
{
    if (diviseur.egalZero())
    {
        throw std::runtime_error("Division par zero");
    }
}

void Uint::verifierZero(uint64_t diviseur)
{
    if (diviseur == 0)
    {
        throw std::runtime_error("Division par zero");
    }
}

int comp(const Uint& mug, const Uint& mud)
{
    /*
    On fait une premi�re v�rification au niveau des tailles,
    ce qui permet un premier filtrage
    */
    if (mug.nombre.size() > mud.nombre.size())
    {
        return 1;
    }
    else if (mug.nombre.size() < mud.nombre.size())
    {
        return -1;
    }
    else
    {
        /*Si les vecteurs ont les m�mes tailles, on va it�rer � travers 
        ceux-ci pour comparer leurs nombres
        */
        auto i1 = mug.nombre.crbegin();
        auto i2 = mud.nombre.crbegin();

        for (; i1 != mug.nombre.crend(); ++i1, ++i2)
        {
            /*
            Si on trouve une diff�rence dans les nombres composants 
            les vecteurs, c'est que l'un des deux est soit plus petit, 
            soit plus grand
            */
            if (*i1 < *i2)
            {
                return -1;
            }
            else if (*i1 > *i2)
            {
                return 1;
            }
        }

        //Si aucune diff�rence n'a �t� trouv�e, les deux Uint sont �gaux
        return 0;
    }
}

size_t Uint::getterTaille() const 
{ 
    return nombre.size(); 
}

bool Uint::estPair() const 
{ 
    return !(nombre.front() % 2); 
}

//////////////////////// OPERATEURS D'INCREMENTATION //////////////////////////

Uint& Uint::operator++()
{
    //Incr�mente les unit�s et v�rife si un report est n�cessaire
    nombre.front()++;
    if (nombre.front() > 9)
    {
        report();
    }
    return *this;
}

Uint Uint::operator++(int)
{
    //Utilise l'op�rateur pr�fix� pour l'incr�mentation
    Uint temp = *this;
    ++*this;
    return temp;
}

Uint& Uint::operator--()
{
    /*
    V�rifie si on peut simplement d�cr�ment� les unit�s, 
    sinon utilise la soustraction de la classe
    */
    if (nombre.front() > 0)
    {
        nombre.front()--;
    }
    else
    {
        *this -= 1;
        report();
    }

    return *this;
}

Uint Uint::operator--(int)
{
    //Utilise l'op�rateur pr�fix� pour l'd�cr�mentation
    Uint temp = *this;
    --* this;
    return temp;
}

////////////////////////// OPERATEURS ARITHMETIQUES ///////////////////////////

Uint operator+(Uint mug, const Uint& mud)
{
    return mug += mud;
}

Uint operator-(Uint mug, const Uint& mud)
{
    return mug -= mud;
}

Uint operator*(Uint mug, const Uint& mud)
{
    return mug *= mud;
}

Uint operator*(Uint mug, const uint64_t& multiple)
{
    return mug *= multiple;
}

Uint operator*(const uint64_t& multiple, Uint mug)
{
    return mug * multiple;
}

Uint operator/(Uint mug, const Uint& diviseur)
{
    return mug /= diviseur;
}

Uint operator%(Uint mug, const Uint& diviseur)
{
    return mug %= diviseur;
}

Uint operator/(Uint mug, const uint64_t& diviseur)
{
    return mug /= diviseur;
}

Uint operator%(Uint mug, const uint64_t& diviseur)
{
    return mug %= diviseur;
}

////////////////////// OPERATEURS ARITHMETIQUES COMPOSES //////////////////////

Uint& Uint::operator+=(const Uint& mud)
{
    //Ajuste la taille du nombre pour �viter le d�passement lors de l'op�ration
    if (nombre.size() < mud.nombre.size())
    {
        nombre.resize(mud.nombre.size(), 0);
    }

    //Addition et report
    for (size_t i = 0; i < mud.nombre.size(); i++)
    {
        nombre.at(i) += mud.nombre.at(i);
    }

    report();

    return *this;
}

Uint& Uint::operator-=(const Uint& mud)
{
    //On stocke le second nombre pour effectuer des op�rations desssus
    Uint temp = mud;

    //On v�rifie que l'op�ration ne donne pas un nombre n�gatif
    if (*this >= temp)
    {
        //Ajuste la du second vecteur s'il est plus petit (en taille)
        if (nombre.size() > temp.nombre.size())
        {
            temp.nombre.resize(nombre.size(), 0);
        }

        //Soustraction et emprunt
        for (size_t i = 0; i < nombre.size(); i++)
        {
            if (nombre.at(i) < temp.nombre.at(i))
            {
                nombre.at(i) += BASE;
                temp.nombre.at(i + 1) += 1;
            }

            nombre.at(i) -= temp.nombre.at(i);
        }
    }
    else
    {
        //Gestion de l'erreur
        throw std::runtime_error("L'operation que vous essayez d'effectuer"
                                 " donne un resultat negatif");
    }

    //Enl�ve les z�ros qui seraient rest�s lors de la soustraction
    enleverZeros();

    return *this;
}

Uint& Uint::operator*=(const Uint& mud)
{
    //On stocke le second nombre pour effectuer des op�rations desssus
    Uint temp = 0;

    //Multiplication des nombres
    for (size_t i = 0; i != mud.nombre.size(); i++)
    {
        temp += mud.nombre.at(i) * *this;

        if (i != mud.nombre.size() - 1)
        {
            nombre.insert(nombre.cbegin(), 0);
        }
    }

    *this = temp;

    enleverZeros();

    return *this;
}

Uint& Uint::operator*=(const uint64_t& multiple)
{
    //Multiplie chaque case par le multiple
    for (size_t i = 0; i < nombre.size(); i++)
    {
        nombre.at(i) *= multiple;
    }

    report();

    return *this;
}

Uint& Uint::operator/=(const Uint& diviseur)
{
    /*
    V�rifie que �a ne soit pas une division par z�ro,
    puis utilise la m�thode divisionReste
    */
    verifierZero(diviseur);
    Uint temp;
    *this = divisionReste(*this, diviseur, temp);
    return *this;
}

Uint& Uint::operator%=(const Uint& diviseur)
{
    /*
    V�rifie que �a ne soit pas une division par z�ro,
    puis utilise la m�thode divisionReste
    */
    verifierZero(diviseur);
    divisionReste(*this, diviseur, *this);
    return *this;
}

Uint& Uint::operator/=(const uint64_t& diviseur)
{
    //V�rifie que �a ne soit pas une division par z�ro
    verifierZero(diviseur);

    //Ex�cution de la division case � case
    for (size_t i = nombre.size() - 1; i > 0; i--)
    {
        nombre.at(i - 1) += (nombre.at(i) % diviseur) * BASE;
        nombre.at(i) /= diviseur;
    }

    nombre.at(0) /= diviseur;

    enleverZeros();

    return *this;
}

Uint& Uint::operator%=(const uint64_t& diviseur)
{
    /*
    V�rifie que �a ne soit pas une division par z�ro,
    puis r�alise le calcul pour le reste de la division
    */
    verifierZero(diviseur);
    *this -= (*this / diviseur) * diviseur;

    return *this;
}

////////////////////////// OPERATEURS DE COMPARAISON //////////////////////////

bool Uint::operator>(const Uint& mud)  const
{
    return comp(*this, mud) == 1;
}

bool Uint::operator<(const Uint& mud)  const
{
    return comp(*this, mud) == -1;
}

bool Uint::operator>=(const Uint& mud) const
{
    return comp(*this, mud) != -1;
}

bool Uint::operator<=(const Uint& mud) const
{
    return comp(*this, mud) != 1;
}

bool Uint::operator==(const Uint& mud) const
{
    return comp(*this, mud) == 0;
}

bool Uint::operator!=(const Uint& mud) const
{
    return comp(*this, mud) != 0;
}

////////////////////////////// OPERATEURS DE FLUX /////////////////////////////

std::ostream& operator<<(std::ostream& flux, const Uint& mug)
{
    //Affiche chiffre � chiffre tout le nombre
    for (auto i = mug.nombre.rbegin();
        i != mug.nombre.rend(); i++)
    {
        flux << *i;
    }

    return flux;
}

std::istream& operator>>(std::istream& is, Uint& mug)
{
    std::string temp;

    //Permet de cr�er un Uint � partir d'un flux d'entr�e
    if (is >> temp)
    {
        mug = temp;
    }
    else
    {
        is.clear(std::ios::badbit | is.rdstate());
    }

    return is;
}

////////////////////////////// OPERATEURS DE CAST /////////////////////////////

Uint::operator uint64_t() const
{
    /*
    Test s'il n'y a pas de d�passemeent de capacit� pour uint64_t lors de 
    la conversion, en cas d'erreur on cr�e une erreur
    */
    try
    {
        std::stringstream convert;
        convert << *this;
        return std::stoull(convert.str());
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << " : Nombre sup�rieur � un uint64_t" << '\n';
        return 0;
    }
}

///////////////////////////// FONCTIONS DE CALCUL /////////////////////////////

Uint mod_pow(Uint base, Uint exposant, const Uint& modulo)
{
    //Resultat en 64_t, car il y'a des risques de d�passement pendant le calcul
    Uint resultat = 1;

    while (exposant > 0)
    {
        if (exposant.estPair())
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
    //On le convertit en 64_t, le r�sultat final ne d�passera pas cette valeur
    return resultat;
}