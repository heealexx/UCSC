#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#define OPTIONS "sctea"
#define EPSILON 0.00001

// Uses the 14 term Pade Approximant for sin to compute approximant
// Calculates the numerator and denominator seperately, only input is x
long double Sin(double x) {  

  long double x_square = x * x;
  long double numer = 52785432 - (479249 * x_square);
  numer *= x_square;
  numer -= 1640635920;
  numer *= x_square;
  numer += 11511339840;
  numer *= x;
  long double denom = 18361 * x_square + 3177720;
  denom *= x_square;
  denom += 277920720;
  denom *= x_square;
  denom += 11511339840;
  long double ans = numer / denom;

  return ans;
}

// Uses the 14 term Pade Approximant to approximate cos.
long double Cos(double x) {

  long double x_square = x * x;
  long double numer = 1075032 - (14615 * x_square);
  numer *= x_square;
  numer -= 18471600;
  numer *= x_square;
  numer += 39251520;
  long double denom = (127 * x_square) + 16632;
  denom *= x_square;
  denom += 1154160;
  denom *= x_square;
  denom += 39251520;
  long double ans = numer / denom;

  return ans;
}

// Uses a Pade approximant to approximate the value of tan given value between
// -pi/2 and pi/2. Plugs in x to equation and solves for approximate.
long double Tan(long double x) {

  long double x_square = x * x;
  long double numer = x_square - 990;
  numer *= x_square;
  numer += 135135;
  numer *= x_square;
  numer -= 4729725;
  numer *= x_square;
  numer += 34459425;
  numer *= x;
  long double denom = x_square - 308;
  denom *= x_square;
  denom += 21021;
  denom *= x_square;
  denom -= 360360;
  denom *= x_square;
  denom += 765765;
  denom *= 45;
  long double ans = numer / denom;

  return ans;
}

// Prof. Long's beautiful e^x code, from slides, multiplies first term, 1, by the next term, adds to sum, calculating e^x approximate, depending on x.
// term: starting term, always 1
// sum: sum, or answer, where term will be added to
long double Exp(long double x) {

  long double term = 1.0;
  long double sum = term;

  for (long double k = 1.0; fabsl(term) > EPSILON; k += 1.0) {
    term = x / k * term;
    sum += term;
  }

  return sum;
}

// Checks flags typed by user and activates the corresponding functions, changin   g the boolean to true if it was called
// sinf, cosf, tanf, expf: boolean values then when turned true, prints out the    tables
int main(int argc, char **argv) {

  int c = 0;
  bool sinf = false;
  bool cosf = false;
  bool tanf = false;
  bool expf = false;

  while ((c = getopt(argc, argv, OPTIONS)) != -1) {
    switch (c) {
    case 's':
      sinf = true;
      break;
    case 'c':
      cosf = true;
      break;
    case 't':
      tanf = true;
      break;
    case 'e':
      expf = true;
      break;
    case 'a':
      sinf = true;
      cosf = true;
      tanf = true;
      expf = true;
      break;
    }
  }

  if (sinf == true) {
    printf("x\t\tSin\t\tLibrary\t\tDifference\n");
    printf("-\t\t---\t\t-------\t\t----------\n");
    for (long double x = -2.0 * M_PI; x <= 2.0 * M_PI; x += (M_PI / 16.0)) {
      printf("%1.4Lf\t\t%1.8Lf\t%1.8f\t%1.10Lf\n", x, Sin(x), sin(x),
             sin(x) - Sin(x));
    }
  }

  if (cosf == true) {
    printf("x\t\tCos\t\tLibrary\t\tDifference\n");
    printf("-\t\t---\t\t-------\t\t----------\n");
    for (long double x = -2.0 * M_PI; x <= 2.0 * M_PI; x += (M_PI / 16.0)) {
      printf("%1.4Lf\t\t%1.8Lf\t%1.8f\t%1.10Lf\n", x, Cos(x), cos(x),
             cos(x) - Cos(x));
    }
  }

  if (tanf == true) {
    printf("x\t\tTan\t\tLibrary\t\tDifference\n");
    printf("-\t\t---\t\t-------\t\t----------\n");
    for (long double x = -((M_PI / 2.0) - .001); x <= (M_PI / 2.0) - .001;
         x += (M_PI / 16.0)) {
      printf("%1.4Lf\t\t%1.8Lf\t%1.8f\t%1.10Lf\n", x, Tan(x), tan(x),
             tan(x) - Tan(x));
    }
  }

  if (expf == true) {
    printf("x\t\tExp\t\tLibrary\t\tDifference\n");
    printf("-\t\t---\t\t-------\t\t----------\n");
    for (long double x = 0; x <= 10; x += 0.1) {
      printf("%1.4Lf\t\t%1.8Lf\t%1.8f\t%1.10Lf\n", x, Exp(x), exp(x),
             exp(x) - Exp(x));
    }
  }

  return 0;
}
