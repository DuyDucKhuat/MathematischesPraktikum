//
//  main.cpp
//  
//
//  Created by Duc Khuat on 12.05.18.
//

#include "main.hpp"
#include "matrix.cpp"
#include "vektor.cpp"
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include "unit.h"
#include <iostream>
#include <fstream>
// =================================
//      Hauptdiagonale-Überprüfer
// =================================

bool isDiagZeroFree( const Matrix&A)
{
    int n = A.col();
    if( A.rows() < A.col()){
        n = A.rows();
    }
    for (int i = 0; i < n ; i++)
        {if(A(i,i)==0) return false;}
    return true;
}

double residuum (const Vektor& b, const Vektor&x, const Matrix& A){
    Vektor r(b.Laenge());
    r= b - A*x;
    return r.Norm2();
}

// ==========================
//      Jacobi-Verfahren
// ==========================
Vektor Jacobi(const Matrix& A, const Vektor&b, int k,const Vektor& x0, double tol){
    #ifndef NDEBUG
    if (!isDiagZeroFree(A))
        Vektor::VekFehler("Nullen in der Diagonale, Verfahren funktioniert nicht!");
    #endif
    
    int n = A.col();
    // Der Algorithmus für k Iterationen.
    Vektor x(n);
    x = x0;
    Vektor prevx(n);
    prevx = x0;
    int i = 0;
    while( i <k && residuum(b,x,A)/b.Norm2()>= tol){
        for ( int j = 0; j < n; j++){
            double xj=0;
            double sum = 0;
            for( int s=0; s < n ; s++){
                if( j!=s) sum += A(j,s)*prevx(j);
            }
            xj = (b(j) -sum) / A(j,j);
            x(j) = xj;
        }
        prevx = x;
        i++;
    }
    return x;
}
// =============================
//      Gauß-Seidel-Verfahren
// =============================

Vektor GaussSeidel(const Matrix& A, const Vektor&b, int k,const Vektor& x0, double tol){
#ifndef NDEBUG
    if (!isDiagZeroFree(A))
        Vektor::VekFehler("Nullen in der Diagonale, Verfahren funktioniert nicht!");
#endif
    int n = A.col();
    
    //Der Algorithmus für k Iterationen.
    Vektor x(n);
    x= x0;
    Vektor prevx(n);
    while(k > 0 && residuum(b,x,A)/b.Norm2()>= tol ){
        for ( int i = 0; i < n; i++){
            double xi = 0;
            double sum1 =0;
            double sum2 =0;
            for (int j=0; j < i; j++){
                sum1 += A(i,j)*x(j);
            }
            for( int s=0; s<n; s++){
                sum2 += A(i,s)*prevx(s);
            }
            xi = (b(i)- sum1 -sum2)/A(i,i);
            prevx=x;
            k--;
        }
    }
    return x;
}

// =============================
//      CG-Methode
// =============================


Vektor CGMethod(const Matrix&A, const Vektor&b, int k, double eps, const Vektor& x0){
    if(!isDiagZeroFree(A)) //todo A is s.p.d.
        Vektor::VekFehler("Nullen in der Diagonale? Das ist keine s.p.d!");
    
    int n = A.col();
    int i =0;
    Vektor x(n);
    x = x0;
    Vektor r(n);
    Vektor p(n);
    Vektor q(n);
    double alpha;
    r = b;
    double y = dot(r,r);
    double y2 = y;
    
    while( r.Norm2()/b.Norm2()> eps && i < k){
        p = r;
        q = A* p;
        alpha = y/dot(q,p);
        x = x + alpha*p;
        r = r - alpha*q;
        y = dot(r,r);
        p = r + + (y/y2)*p;
        y2 = y;
        i++;
    }
    return x;
}

int main(){
    Matrix A;
    Vektor x0;
    Vektor b;
    double tol;
    int maxiter;
    Start(1,A,x0, b, tol, maxiter);
    Vektor x(A.col());
    x = Jacobi(A,b,maxiter,x0,tol);
    
    Ergebnis(x, maxiter, 0);
    std::cout << x << std::endl;
    std::cout << residuum(b,x,A) /b.Norm2()<<std::endl;
    std::ofstream ofs("jacobi.txt", std::ofstream::out);;
    ofs << residuum(b,x,A)/b.Norm2()<< "\n";
    ofs.close();
    return 0;
}
