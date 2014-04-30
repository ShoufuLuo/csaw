

#include "bignum.h" 
#include <cmath>


using namespace std; 


unsigned long u_rand() 
{
   int r = rand(); 
   return r > 0 ? r : -r ; 
}






int main() 
{
   int ntests = 64; 
   int i = 0; 
   UBigNum A, B; 
   while( ntests-- ) 
   {
      unsigned long long aa, bb; 
      UBigNum a(aa = u_rand()); 
      UBigNum b(bb = u_rand()); 
      if( a > b ) 
      {
         UBigNum c = a - b; 
         UBigNum d = a + b; 
         UBigNum e = a * b; 
         UBigNum f = a/b ; 

         A = A + B; 
         B = B + A + f; 

         UBigNum g = gcd( A, B ) ; 

         cout << i++ << endl << endl ; 

         assert( g == gcd( A, B ) ) ; 
         
         assert( c == (aa-bb)); 
         assert( d == (aa+bb)); 
         assert( e == (aa*bb)); 
         assert( f == (aa/bb)); 

         B = B * c; 
         A = A * d;
      }
   }


   A.debug(); 
   B.debug(); 

   cout << "Sample test ... " << endl ;
   UBigNum a(165204056), b(21133333); 
   UBigNum c = a - b; 
   a.debug(); 
   b.debug(); 
   c.debug(); 


   c = a * b ; 
   c.debug(); 

   UBigNum d = c / b ; 
   d.debug();
   cout << d.print(10) << endl ;

   cout << "Sample test ... " << endl ;
   UBigNum x = exp( 11, 11, 12 ); 
   cout << x.print(10) << endl ; 
}
