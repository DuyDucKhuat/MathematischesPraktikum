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
// ==========================
//      Jacobi-Verfahren
// ==========================
Vektor Jacobi(const Matrix& A, const Vektor&b, int k){
    #ifndef NDEBUG
    if (!isDiagZeroFree(A))
        Vektor::VekFehler("Nullen in der Diagonale, Verfahren funktioniert nicht!");
    #endif
    
    int n = A.col();
    
    // Der Algorithmus für k Iterationen.
    Vektor x(n);
    Vektor prevx(n);
    for ( int i =0; i <k; i++){
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
    }
    return x;
}
// =============================
//      Gauß-Seidel-Verfahren
// =============================

Vektor GaussSeidel(const Matrix& A, const Vektor&b, int k){
#ifndef NDEBUG
    if (!isDiagZeroFree(A))
        Vektor::VekFehler("Nullen in der Diagonale, Verfahren funktioniert nicht!");
#endif
    int n = A.col();
    
    //Der Algorithmus für k Iterationen.
    Vektor x(n);
    Vektor prevx(n);
    while(k >0){
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

double residuum (const Vektor& b, const Vektor&x, const Matrix& A){
    Vektor r(b.Laenge());
    r= b - A*x;
    return r.Norm2();
}

Vektor CGMethod(const Matrix&A, const Vektor&b, int k, double eps){
    if(!isDiagZeroFree(A) )
        
        
    Vektor x(A.col());
    int i =0;
    while( residuum(b,A,x)/(b.Norm2())> eps && i < k){
        
    }
}

int main(){
    /*Matrix A;
    Vektor x0;
    Vektor b;
    double tol;
    int maxiter;
    Start(1,A,x0, b, tol, maxiter);
    
    Ergebnis(x, Iterationen, Methode);*/
    Matrix A(2,2);
    A(0,0)=2;
    A(1,1)=3;
    
    std::cout << isDiagZeroFree(A)<< std::endl;
    return 0;
}
