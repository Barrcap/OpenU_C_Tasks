#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define ACC 0.000001 /* desired accuracy */

double my_sin(double x);

int main () {

 double x;
 printf("Please pick your favorite value between -25 and 25 for X: ");
 scanf("%lf", &x);
 while (x < -25 || x > 25)
 {
	printf("X out of range! please pick a value between -25 and 25:\n");
	scanf("%lf", &x);
 }
 
 printf("\nAccording to my_sin calculations:");
 printf("\nSin(%f) = %f", x, my_sin(x) );
 printf("\nAccording to standart sine library:");
 printf("\nSin(%f) = %f\n", x, sin(x) );

 return 0;
}



double my_sin(double x)
{

 double sinX = 0;
 int i = 1;
 double comp = x; /* comp - component on Tylor Series */
 /* start with first component - x^1/1! */

 while (comp >= ACC || comp <= -ACC)
 {
	sinX += comp;

	comp = comp * x * x; /* x^i => x^(i+2) */
	comp = comp / (i+1) / (i+2); /* i! => (i+2)! */
	i += 2;
	comp *= -1; /* changing sign of next component */

 }

 return sinX;
}
