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
    Matrix D(n,n);
    Matrix B(n,n);
    B = A;
    for( int l = 0; l < n ; l++){B(l,l)=0;D(l,l)=1/A(l,l);}
    int i = 0;
    while( i <k && residuum(b,x,A)/b.Norm2()>= tol){
        x = D*(b-B*x); 
	i++;
    }
    return x;
}
// =============================
//      Gauß-Seidel-Verfahren
// =============================

Vektor GaussSeidel(const Matrix& A, const Vektor&b, int k,double tol, const Vektor& x0){
#ifndef NDEBUG
    if (!isDiagZeroFree(A))
        Vektor::VekFehler("Nullen in der Diagonale, Verfahren funktioniert nicht!");
#endif
    int n = A.col();
    
    //Der Algorithmus für k Iterationen.
    Vektor x(n);
    x= x0;
    int l = 0;
    while(k >l && (b-A*x).Norm2()/b.Norm2() >= tol ){
        for ( int i = 0; i < n; i++){
            double sum1 =0;
            double sum2 =0;
            for (int j=0; j < i; j++){
                sum1 += A(i,j)*x(j);
            }
            for( int s=i+1; s<n; s++){
                sum2 += A(i,s)*x(s);
            }
            x(i) = (b(i)- sum1 -sum2)/A(i,i);
            l++;
        }
    }
    
    return x;
}

// =============================
//      CG-Methode
// =============================


Vektor CGMethod(const Matrix&A, const Vektor&b, int k,const  Vektor& x0, double eps){
    if(!isDiagZeroFree(A)) //todo A is s.p.d.
        Vektor::VekFehler("Nullen in der Diagonale? Das ist keine s.p.d!");
    
    int n = A.col();
    int i = 0;
    Vektor x(n);
    x = x0;
    Vektor r(n);
    Vektor p(n);
    Vektor q(n);
    double alpha;
    r = b- A*x;
    double y = dot(r,r);
    double y2 = y;
    p = r;
    while(r.Norm2()/b.Norm2()> eps && i < k){
        
        q = A * p;
        alpha = y/dot(q,p);
        x = x + alpha*p;
        r = r - alpha*q;
        y = dot(r,r);
        p = r + (y/y2)*p;
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
    x = GaussSeidel(A,b,maxiter,tol,x0);
    
    Ergebnis(x, maxiter, 1);
    std::ofstream ofs("jacobi.txt", std::ofstream::out);;
    ofs << residuum(b,x,A)/b.Norm2()<< "\n";
    ofs.close();
    return 0;
}
