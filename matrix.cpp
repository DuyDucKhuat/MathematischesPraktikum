//
//  matrix.cpp
//  
//
//  Created by Duc Khuat on 11.05.18.
//

#include "matrix.h"
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include "vektor.h"

// =======================
//      Konstruktoren
// =======================


// ----- Konstruktor -----

Matrix::Matrix(size_t n, size_t m){
    #ifndef NDEBUG
    if( n <= 0 || m <= 0)
        MatFehler("Nur Matrizen mit positiver Dimension!");
    #endif
    this -> ReDim(n,m);
}
Matrix::Matrix(const Matrix& x):Mat(x.Mat){}

// ===========================================
//      Matrixelement schreiben und lesen
// ===========================================


// ----- Schreib- und Lesezugriff auf Matrixelemente -----

double& Matrix::operator () (size_t i, size_t j) {
#ifndef NDEBUG
    if (i >= (this->Zeil))
        MatFehler("Ungueltiger Index!");
#endif
#ifndef NDEBUG
    if (j >= (this->Spalt))
        MatFehler("Ungueltiger Index!");
#endif
    return Mat[i][j];
}
// ----- Lesezugriff auf Elemente konstanter Matrixen -----

double Matrix::operator () (size_t i, size_t j) const {
#ifndef NDEBUG
    if (i >= this->Zeil)
        MatFehler("Ungueltiger Index!");
#endif
#ifndef NDEBUG
    if (j >= this->Spalt)
        MatFehler("Ungueltiger Index!");
#endif
    
    return Mat[i][j];
}

// =====================
//      Zuweisungen
// =====================

// ----- Zuweisungsoperator "=" ----


Matrix& Matrix::operator = (const Matrix& x)
{
 
#ifndef NDEBUG

    if (this->rows() != x.rows() || this->col() != x.col())
        MatFehler("Inkompatible Dimensionen fuer 'Matrix = Matrix'!");
#endif
    
    for (size_t i = 0; i < Mat.size(); i++){
        for (size_t j = 0; j < (*this).Spalt ; j++){
        (*this)(i,j) = x(i,j);
        }
    }

    //this->Mat = x.Mat;

    
    return *this;
}
// ----- Zuweisungsoperator mit Addition "+=" ----

Matrix& Matrix::operator += (const Matrix& x)
{
#ifndef NDEBUG
    if (this->rows() != x.rows() || this->col() != x.col())

        MatFehler("Inkompatible Dimensionen fuer 'Matrix += Matrix'!");
#endif
    
    for (size_t i = 0; i < (*this).Zeil; i++){
        for (size_t j = 0; j < (*this).Spalt ; j++){
            (*this)(i,j) += x(i,j);
        }
    }
    
    
    return *this;
    
}


// ----- Zuweisungsoperator mit Subtraktion "-=" ----

Matrix& Matrix::operator -= (const Matrix& x)
{
#ifndef NDEBUG
    if (this->rows() != x.rows() || this->col() != x.col())
        MatFehler("Inkompatible Dimensionen fuer 'Matrix -= Matrix'!");
#endif
    
    for (size_t i = 0; i < (*this).Zeil; i++){
        for (size_t j = 0; j < (*this).Spalt ; j++){
            (*this) (i,j) -= x(i,j);
        }
    }
    return *this;
}


// ----- Zuweisungsoperator mit Multiplikation "*=" ----

Matrix& Matrix::operator *= (const double c)
{

    for (size_t i = 0; i < (*this).Zeil; i++){
        for (size_t j = 0; j < (*this).Spalt ; j++){
            (*this) (i,j) *= c;
        }
    }
    return *this;
}


// ----- Zuweisungsoperator mit Division "/=" ----

Matrix& Matrix::operator /= (const double c)
{

    for (size_t i = 0; i < (*this).Zeil; i++){
        for (size_t j = 0; j < (*this).Spalt ; j++){
            (*this) (i,j) /= c;
        }
    }
    return *this;
}


// ==============================
//      Matrixdimension aendern
// ==============================


// ----- Matrixdimension aendern -----

Matrix& Matrix::ReDim (size_t m, size_t n)
{
#ifndef NDEBUG
    if (m <= 0 || n <= 0)
        MatFehler("Nur Matrixen mit positiver Zeilen-/ Spaltenanzahl!");
#endif
    
    Mat.clear();
    std::vector<double> vector1(n,0);
    Mat.resize(m,vector1);
    (*this).Zeil= m;
    (*this).Spalt= n;
    
    return *this;
}



// ==========================
//      Fehlerbehandlung
// ==========================


// ----- Ausgabe der Fehlermeldung "str" -----

void Matrix::MatFehler (const std::string& str)
{
    std::cerr << "\nMatrixfehler: " << str << '\n' << std::endl;
    exit(1);
}




// ==================================
//      arithmetische Operatoren
// ==================================


// ----- Addition "+" -----

Matrix operator + (const Matrix& x, const Matrix& y)
{
#ifndef NDEBUG
    if (x.rows() != y.rows() || x.col() != y.col())
        Matrix::MatFehler("Inkompatible Dimensionen fuer 'Matrix + Matrix'!");
#endif
    Matrix z(x.rows(),x.col());

    z = x;
    z += y;

    return z;
}


// ----- Subtraktion "-" -----

Matrix operator - (const Matrix& x, const Matrix& y)
{
#ifndef NDEBUG
    if (x.rows() != y.rows() || x.col() != y.col())
        Matrix::MatFehler("Inkompatible Dimensionen fuer 'Matrix - Matrix'!");
#endif
    
    Matrix z = x;
    z -= y;
    return z;
}


// ----- Vorzeichen wechseln "-" -----

Matrix operator - (const Matrix& x)
{
    Matrix z = x;
    z *= (-1);
    return z;
}


// ----- Matrixmultiplikation -----

Matrix operator * (const Matrix& x, const Matrix& y)
{
    Matrix l = Matrix( x.rows(), y.col());
    if (x.col() != y.rows())
        Matrix::MatFehler("Inkompatible Dimensionen fuer 'Matrix * Matrix'!");
    for (int i = 0; i < x.rows(); i++){
        for( int j = 0 ; j < y.col();j++){
            double a_ij=0.0;
            for( int k= 0 ; k < x.col(); k++){
                a_ij+= x(i,k)*y(k,j);
            }
            l(i,j) = a_ij;
        }
    }
    return l;
    
}


// ----- Multiplikation Skalar*Matrix "*" -----

Matrix operator * (const double c, const Matrix& x)
{
    Matrix z = x;
    z *=c;
    return z;
}


// ----- Multiplikation Matrix*Skalar "*" -----

Matrix operator * (const Matrix& x, const double c)
{
    Matrix z = x;
    z *=c;
    return z;
}


// ----- Division Matrix/Skalar "/" -----

Matrix operator / (const Matrix& x, const double c)
{
    Matrix z = x;
    z /=c;
    return z;
}


// ==============================
//      Vergleichsoperatoren
// ==============================


// ----- Test auf Gleichheit "==" -----

bool operator == (const Matrix& x, const Matrix& y)
{
    if (x.rows() != y.rows() || x.col() != y.col()) return false;
    
    for (size_t i = 0; i < x.rows(); i++){
        for (size_t j = 0; j < x.col(); j++){
            if(x(i,j)!=y(i,j)) return false;
        }
    }
    
    return true;
}


// ----- Test auf Ungleichheit "!=" -----

bool operator != (const Matrix& x, const Matrix& y)
{
    return !(x == y);
}


// ==========================
//      Ein- und Ausgabe
// ==========================


// ----- Ausgabe "<<" -----

std::ostream& operator << (std::ostream& s, const Matrix& x)
{
    s << std::setiosflags(std::ios::right);
    s << "# Dim: (" << x.rows() << ", " << x.col() <<")\n";
    for (size_t i = 0; i <x.rows(); i++){
        for(size_t j = 0; j < x.col();j++){
            s << x(i,j) << " ";
        }
        s << "\n";
    }
    return s << std::endl;
}


// ----- Eingabe ">>" -----

std::istream& operator >> (std::istream& s, Matrix& x)
{
    for(size_t i = 0; i < x.rows(); i++){
        for (size_t j = 0; j < x.col(); j++) {
            s >> x(i,j);
        }
    }
    return s;
}
    
    
/*Vektor operator * (const Matrix& x, const Vektor& v)
{
#ifndef NDEBUG
    if (x.col() != v.Laenge())
        Matrix::MatFehler("Inkompatible Dimensionen fuer 'Matrix * Vektor'!");
#endif
    Vektor w(v.Laenge());
    for (int i = 0 ; i < x.rows();i++){
        double wi = 0.0;
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
        Matrix::MatFehler("Inkompatible Dimensionen fuer 'Matrix * Vektor'!");
#endif
    Vektor w(v.Laenge());
    for (int i = 0 ; i < x.col();i++){
        double wi = 0.0;
        for( int j = 0; j < x.rows(); j++){
            wi += x(j,i)*v(j);
        }
        w(i) = wi;
    }
    return w;
}
*/
