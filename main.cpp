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

double res (const Vektor& b, const Vektor&x, const Matrix& A){
    Vektor r(b.Laenge());
    double rel= (b - A*x).Norm2()/b.Norm2();
    return rel;
}

// ==========================
//      Jacobi-Verfahren
// ==========================
Vektor Jacobi(const Matrix& A, const Vektor& b, int& k, double tol, const Vektor& x0){
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
    while( i <k && res(b,x,A)>= tol){
        x = D*(b-B*x); 
	i++;
    }
    k = i;
    return x;
}
// =============================
//      Gauß-Seidel-Verfahren
// =============================

Vektor GaussSeidel(const Matrix& A, const Vektor&b, int& k,double tol, const Vektor& x0){
#ifndef NDEBUG
    if (!isDiagZeroFree(A))
        Vektor::VekFehler("Nullen in der Diagonale, Verfahren funktioniert nicht!");
#endif
    int n = A.col();
    
    //Der Algorithmus für k Iterationen.
    Vektor x(n);
    x= x0;
    int l = 0;
    while(k >l && res(b,x,A) >= tol ){
        for ( int i = 0; i < n; i++){
            double sum1 =0;
            double sum2 =0;
            for (int j=0; j < i; j++){sum1 += A(i,j)*x(j);}
            for( int s=i+1; s<n; s++){sum2 += A(i,s)*x(s);}
            x(i) = (b(i)- sum1 -sum2)/A(i,i);
        }
	l++;
    }
    k = l;
    return x;
}

// =============================
//      CG-Methode
// =============================


Vektor CGMethod(const Matrix&A, const Vektor&b, int& k, double eps, const  Vektor& x0){
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
    while(res(b,x,A) >= eps && i < k){
        
        q = A * p;
        alpha = y/dot(q,p);
        x = x + alpha*p;
        r = r - alpha*q;
        y = dot(r,r);
        p = r + (y/y2)*p;
        y2 = y;
        i++;
    }
    k=i;	
    return x;
}

int main(){
    Matrix A;
    Vektor x0;
    Vektor b;
    double tol;
    int maxiter;
    std::ofstream ofs("GaussSeidel.txt", std::ofstream::out);
    for (int i = 1; i < 3; i++){
   	 Start(i,A,x0, b, tol, maxiter);
         Vektor x(A.col());
   	 x = GaussSeidel(A,b,maxiter,tol,x0);
    	 Ergebnis(x, maxiter, 1);
         ofs << res(b,x,A)<< "\n";
     }
    ofs.close();
    std::ofstream ofs1("jacobi.txt", std::ofstream::out);
    for (int i = 1; i < 3; i++){
    	Start(i,A,x0, b, tol, maxiter);
    	Vektor x(A.col());
    	x = Jacobi(A,b,maxiter,tol,x0);
   	Ergebnis(x, maxiter, 0);
	ofs1 << res(b,x,A)<< "\n";
    }
    ofs1.close();
    std::ofstream ofs2("GCMethod.txt", std::ofstream::out);
    for (int i = 1; i < 3; i++){    
	Start(i,A,x0, b, tol, maxiter);
        Vektor x(A.col());
        x = CGMethod(A,b,maxiter,tol,x0);
        Ergebnis(x, maxiter, 2);
	ofs2 << res(b,x,A)<< "\n";
    }
    ofs2.close();
    return 0;
}
