/*
Nom du fichier : Uint.cpp
But : Implantation d'une classe Uint permettant d'effectuer des opérations
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
    //Ajoute chaque nombre dans le vector en commençait par les unités
    for (auto i = texte.crbegin(); i != texte.crend(); ++i)
    {
        if (isdigit(*i))
        {
            this->nombre.push_back((uint64_t)*i - ZERO);
        }
        else
        {
            throw std::runtime_error("Valeur non-numérique détectée.");
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
        Si le nombre dans la case est supérieur à 9,
        il faut effectuer un report sur la prochaine case
        */
        if (nombre.at(i) > 9)
        {
            //Comme précédemment, on évite un dépassement de capacité
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
    On fait une première vérification au niveau des tailles,
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
        /*Si les vecteurs ont les mêmes tailles, on va itérer à travers 
        ceux-ci pour comparer leurs nombres
        */
        auto i1 = mug.nombre.crbegin();
        auto i2 = mud.nombre.crbegin();

        for (; i1 != mug.nombre.crend(); ++i1, ++i2)
        {
            /*
            Si on trouve une différence dans les nombres composants 
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

        //Si aucune différence n'a été trouvée, les deux Uint sont égaux
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
    //Incrémente les unités et vérife si un report est nécessaire
    nombre.front()++;
    if (nombre.front() > 9)
    {
        report();
    }
    return *this;
}

Uint Uint::operator++(int)
{
    //Utilise l'opérateur préfixé pour l'incrémentation
    Uint temp = *this;
    ++*this;
    return temp;
}

Uint& Uint::operator--()
{
    /*
    Vérifie si on peut simplement décrémenté les unités, 
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
    //Utilise l'opérateur préfixé pour l'décrémentation
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
    //Ajuste la taille du nombre pour éviter le dépassement lors de l'opération
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
    //On stocke le second nombre pour effectuer des opérations desssus
    Uint temp = mud;

    //On vérifie que l'opération ne donne pas un nombre négatif
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

    //Enlève les zéros qui seraient restés lors de la soustraction
    enleverZeros();

    return *this;
}

Uint& Uint::operator*=(const Uint& mud)
{
    //On stocke le second nombre pour effectuer des opérations desssus
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
    Vérifie que ça ne soit pas une division par zéro,
    puis utilise la méthode divisionReste
    */
    verifierZero(diviseur);
    Uint temp;
    *this = divisionReste(*this, diviseur, temp);
    return *this;
}

Uint& Uint::operator%=(const Uint& diviseur)
{
    /*
    Vérifie que ça ne soit pas une division par zéro,
    puis utilise la méthode divisionReste
    */
    verifierZero(diviseur);
    divisionReste(*this, diviseur, *this);
    return *this;
}

Uint& Uint::operator/=(const uint64_t& diviseur)
{
    //Vérifie que ça ne soit pas une division par zéro
    verifierZero(diviseur);

    //Exécution de la division case à case
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
    Vérifie que ça ne soit pas une division par zéro,
    puis réalise le calcul pour le reste de la division
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
    //Affiche chiffre à chiffre tout le nombre
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

    //Permet de créer un Uint à partir d'un flux d'entrée
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
    Test s'il n'y a pas de dépassemeent de capacité pour uint64_t lors de 
    la conversion, en cas d'erreur on crée une erreur
    */
    try
    {
        std::stringstream convert;
        convert << *this;
        return std::stoull(convert.str());
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << " : Nombre supérieur à un uint64_t" << '\n';
        return 0;
    }
}

///////////////////////////// FONCTIONS DE CALCUL /////////////////////////////

Uint mod_pow(Uint base, Uint exposant, const Uint& modulo)
{
    //Resultat en 64_t, car il y'a des risques de dépassement pendant le calcul
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
    //On le convertit en 64_t, le résultat final ne dépassera pas cette valeur
    return resultat;
}