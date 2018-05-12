/***********************************************
 *  Name       : vektor.cpp                     *
 *  Verwendung : Vektorklasse                   *
 *  Autor      :                                *
 *  Datum      :                                *
 ***********************************************/

#include "vektor.h"
#include <iomanip>
#include <cmath>
#include <cstdlib>

// =======================
//      Konstruktoren
// =======================


// ----- Konstruktor -----

Vektor::Vektor(size_t l)
{
#ifndef NDEBUG
    if (l <= 0)
        VekFehler("Nur Vektoren mit positiver Laenge!");
#endif
    
    this->ReDim(l);
}


// ----- Kopierkonstruktor -----

Vektor::Vektor(const Vektor& x):Vek(x.Vek){ }


// ===========================================
//      Vektorelement schreiben und lesen
// ===========================================


// ----- Schreib- und Lesezugriff auf Vektorelemente -----

double& Vektor::operator () (size_t i) {
#ifndef NDEBUG
    if (i >= Vek.size())
        VekFehler("Ungueltiger Index!");
#endif
    
    return Vek[i];
}


// ----- Lesezugriff auf Elemente konstanter Vektoren -----

double Vektor::operator () (size_t i) const {
#ifndef NDEBUG
    if (i >= Vek.size())
        VekFehler("Ungueltiger Index!");
#endif
    
    return Vek[i];
}

// =====================
//      Zuweisungen
// =====================

// ----- Zuweisungsoperator "=" ----

Vektor& Vektor::operator = (const Vektor& x)
{
#ifndef NDEBUG
    if (Vek.size() != x.Laenge())
        VekFehler("Inkompatible Dimensionen fuer 'Vektor = Vektor'!");
#endif
    
    for (size_t i = 0; i < Vek.size(); i++)
        (*this) (i) = x(i);
    
    //oder: this->Vek=x.Vek;
    
    return *this;
}


// ----- Zuweisungsoperator mit Addition "+=" ----

Vektor& Vektor::operator += (const Vektor& x)
{
#ifndef NDEBUG
    if (Vek.size() != x.Laenge())
        VekFehler("Inkompatible Dimensionen fuer 'Vektor += Vektor'!");
#endif
    
    for (size_t i = 0; i < Vek.size(); i++)
        (*this) (i) += x(i);
    
    
    
    return *this;
}


// ----- Zuweisungsoperator mit Subtraktion "-=" ----

Vektor& Vektor::operator -= (const Vektor& x)
{
#ifndef NDEBUG
    if (Vek.size() != x.Laenge())
        VekFehler("Inkompatible Dimensionen fuer 'Vektor -= Vektor'!");
#endif
    
    for (size_t i = 0; i < Vek.size(); i++)
        (*this) (i) -= x(i);
    
    
    
    return *this;
}


// ----- Zuweisungsoperator mit Multiplikation "*=" ----

Vektor& Vektor::operator *= (const double c)
{
    
    for (size_t i = 0; i < Vek.size(); i++)
        (*this) (i) *= c;
    return *this;
}



// ----- Zuweisungsoperator mit Division "/=" ----

Vektor& Vektor::operator /= (const double c)
{
    for (size_t i = 0; i < Vek.size(); i++)
        (*this) (i) /= c;
    return *this;
}


// ==============================
//      Vektorlaenge aendern
// ==============================


// ----- Vektorlaenge aendern -----

Vektor& Vektor::ReDim (size_t l)
{
#ifndef NDEBUG
    if (l <= 0)
        VekFehler("Nur Vektoren mit positiver Laenge!");
#endif
    
    Vek.clear();
    Vek.resize(l,0);
    
    return *this;
}


// ======================
//      Vektornormen
// ======================


// ----- Euklidische Norm -----

double Vektor::Norm2() const
{
    double x = 0;
    for (int i = 0; i < Vek.size(); i++){
        x += (*this)(i)*((*this)(i));
    }
    return sqrt(x);
}


// ----- Maximum-Norm -----

double Vektor::NormMax() const
{
    double max = abs((*this)(0));
    for (int i = 1 ; i < Vek.size(); i++){
        if ( max < abs((*this)(i)))
            max = abs((*this)(i));
    }
    return abs(max);
}


// ==================================
//      arithmetische Operatoren
// ==================================


// ----- Addition "+" -----

Vektor operator + (const Vektor& x, const Vektor& y)
{
#ifndef NDEBUG
    if (x.Laenge() != y.Laenge())
        Vektor::VekFehler("Inkompatible Dimensionen fuer 'Vektor + Vektor'!");
#endif
    
    Vektor z = x;
    return z += y;
}


// ----- Subtraktion "-" -----

Vektor operator - (const Vektor& x, const Vektor& y)
{
#ifndef NDEBUG
    if (x.Laenge() != y.Laenge())
        Vektor::VekFehler("Inkompatible Dimensionen fuer 'Vektor + Vektor'!");
#endif
    
    Vektor z = x;
    return z -= y;
}


// ----- Vorzeichen wechseln "-" -----

Vektor operator - (const Vektor& x)
{
    Vektor z = x;
    z *= (-1);
    return z;
}


// ----- Skalarprodukt -----

double dot (const Vektor& x, const Vektor& y)
{
    double l = 0;
    if (x.Laenge() != y.Laenge())
        Vektor::VekFehler("Inkompatible Dimensionen fuer 'Vektor + Vektor'!");
    for (int i = 0; i < x.Laenge(); i++){
        l += x(i)*y(i);
    }
    return l;
}
// ----- Multiplikation Skalar*Vektor "*" -----

Vektor operator * (const double c, const Vektor& x)
{
    Vektor z = x;
    z *=c;
    return z;
}


// ----- Multiplikation Vektor*Skalar "*" -----

Vektor operator * (const Vektor& x, const double c)
{
    Vektor z = x;
    z *=c;
    return z;
}


// ----- Division Vektor/Skalar "/" -----

Vektor operator / (const Vektor& x, const double c)
{
    Vektor z = x;
    z /=c;
    return z;
}


// ==============================
//      Vergleichsoperatoren
// ==============================


// ----- Test auf Gleichheit "==" -----

bool operator == (const Vektor& x, const Vektor& y)
{
    if (x.Laenge() !=y.Laenge()) return false;
    
    for (size_t i = 0, xsize = x.Laenge(); i < xsize; i++)
        if (x(i)!=y(i)) return false;
    
    return true;
}


// ----- Test auf Ungleichheit "!=" -----

bool operator != (const Vektor& x, const Vektor& y)
{
    return !(x == y);
}


// ==========================
//      Ein- und Ausgabe
// ==========================


// ----- Ausgabe "<<" -----

std::ostream& operator << (std::ostream& s, const Vektor& x)
{
    s << std::setiosflags(std::ios::right);
    s << "# Laenge: " << x.Laenge() <<"\n";;
    for (size_t i = 0, xsize = x.Laenge(); i < xsize; i++)
        s << "\n" << x(i);
    
    return s << std::endl;
}


// ----- Eingabe ">>" -----

std::istream& operator >> (std::istream& s, Vektor& x)
{
    for (size_t i = 0, xsize = x.Laenge(); i < xsize; i++) {
        s >> x(i);
    }
    return s;
}

Vektor operator * (const Matrix& x, const Vektor& v)
{
#ifndef NDEBUG
    if (x.col() != v.Laenge())
        Vektor::VekFehler("Inkompatible Dimensionen fuer 'Matrix * Vektor'!");
#endif
    Vektor w(v.Laenge());
    for (int i = 0 ; i < x.rows();i++){
        double wi=0.0;
        for( int j= 0; j < x.col(); j++){
            wi += x(i,j)*v(j);
        }
        w(i) = wi;
    }
    return w;
}
Vektor operator * (const Vektor& v, const Matrix& x)
{
#ifndef NDEBUG
    if (x.rows() != v.Laenge())
        Vektor::VekFehler("Inkompatible Dimensionen fuer 'Matrix * Vektor'!");
#endif
    Vektor w(v.Laenge());
    for (int i = 0 ; i < x.col();i++){
        double wi=0.0;
        for( int j= 0; j < x.rows(); j++){
            wi += x(j,i)*v(j);
        }
        w(i) = wi;
    }
    return w;
}


// ==========================
//      Fehlerbehandlung
// ==========================


// ----- Ausgabe der Fehlermeldung "str" -----
void Vektor::VekFehler (const std::string& str)
{
    std::cerr << "\nVektorfehler: " << str << '\n' << std::endl;
    exit(1);
}

