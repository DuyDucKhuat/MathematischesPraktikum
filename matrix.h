

#ifndef _Matrix_H                         // Matrix.h nicht doppelt benutzen
#define _Matrix_H

#include <iostream>
#include <vector>
#include <string>
#include "vektor.h"

class Vektor;                   // fuer friend Matrix * Matrix etc.

class Matrix
{
private:
    size_t Zeil,Spalt;
    std::vector<std::vector<double> > Mat;              // Daten
    
    
public:
    friend class Vektor;
    explicit Matrix (size_t m=1, size_t n=1);         // Konstruktor mit Laengenangabe
    ~Matrix () {};                        // Destruktor
    Matrix  (const Matrix&);              // Kopierkonstruktor
    
    double& operator () (size_t, size_t);         // Zugriff auf Einträge des Matrixs
    double  operator () (size_t, size_t) const;   // Zugriff auf falls Matrix const
    
    Matrix& operator =  (const Matrix&);  // Zuweisung
    Matrix& operator += (const Matrix&);  // Zuweisungen mit arithm. Operation
    Matrix& operator -= (const Matrix&);
    Matrix& operator *= (const double);
    Matrix& operator /= (const double);
    
    Matrix& ReDim   (size_t, size_t);                   // neue Laenge festlegen
    size_t rows() const {return (*this).Zeil;};
    size_t col()  const {return (*this).Spalt;};

    
    static void MatFehler (const std::string& str);   // Fehlermeldung ausgeben
    
    friend Matrix   operator +  (const Matrix&, const Matrix&); // Addition
    friend Matrix   operator -  (const Matrix&, const Matrix&); // Subtraktion
    friend Matrix   operator -  (const Matrix&);                // Vorzeichen
    friend Matrix   operator * (const Matrix&, const Matrix&);
    friend Matrix   operator *  (const double,  const Matrix&); // Vielfache
    friend Matrix   operator *  (const Matrix&, const double);
    friend Matrix   operator /  (const Matrix&, const double);

    
    friend bool     operator == (const Matrix&, const Matrix&); // Vergleich
    friend bool     operator != (const Matrix&, const Matrix&);
    
    friend std::istream& operator >> (std::istream&, Matrix&);       // Eingabe
    friend std::ostream& operator << (std::ostream&, const Matrix&); // Ausgabe
    
    friend Vektor   operator *  (const Matrix&, const Vektor&); // Matrix-Matrix-
    friend Vektor   operator *  (const Vektor&, const Matrix&); // Multiplikation
};

#endif

