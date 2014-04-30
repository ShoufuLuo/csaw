

#include "bignum.h" 
#include <cmath>


using namespace std; 


unsigned long u_rand() 
{
   int r = rand(); 
   return r > 0 ? r : -r ; 
}




void testprod(int bits, int ntest) 
{
   int t = 0; 
   while( ntest-- ) 
   {
      UBigNum a, b, c, d; 
      a.random(bits); 
      b.random(bits); 
      c.random(bits); 
      d.random(bits); 

      UBigNum e = a + b; 
      UBigNum f = c + d; 

      UBigNum p = e*f; 
      UBigNum q = a*c + a*d + b*c + b*d; 
      assert( p == q ) ; 
      cout << "(a+b)*(c+d) == a*c + a*d + b*c + b*d " << t++ << endl ; 
   }
}




void testmodular(int bits, int ntest) 
{
   int t = 0 ; 
   while( ntest-- ) 
   {
      UBigNum n; 
      n.random(bits); 

      UBigNum a,b,c,d,e,f,g; 
      a.random(bits); a = a%n ; 
      b.random(bits); b = b%n ;
      c = exp( a, b, n ) ;

      d.random(bits); d = d%n ;
      e = b * d; 
      f = exp( a, e, n ) ; 
      g = exp(c, d, n); 
      assert( f == g ) ; 
      cout << "(a^b)^d mod n == a^(b*d) mod n " << t++ << endl ; 
   }
}



void testdivide(int bits, int ntest)
{
   int t = 0 ; 
   while( ntest-- ) 
   {
      UBigNum n; 
      n.random(bits); 

      UBigNum m;
      m.random(bits/2);

      UBigNum q = n/m; 
      UBigNum r = n%m; 
      assert( (m*q + r) == n ); 
      cout << "a/b -> (q,r) then bq+r == a " << t++ << endl ;
   }
}




void testprimegen(int bits, int ntest) 
{
   int t = 0 ; 
   while( ntest-- ) 
   {
      UBigNum p = prime(bits);
      UBigNum q = prime(bits); 

      UBigNum g = gcd( p, q ) ; 
      assert( g == 1 || p == q ) ; 

      cout << " gcd(p,q) == 1 and (inv(p,q) * p) mod q == 1 " << t++ << endl ; 
      p.debug(); 
      q.debug(); 
   }      
}




      

int main() 
{
   int ntests = 1000;
   int bits = 10000; 
   while( ntests-- ) 
   {
      testprod(bits, 1) ;
      testdivide( bits, 1) ; 
      testmodular(bits, 1) ;  
      testprimegen(bits, 1)  ; 
   }
   return 0; 
}


