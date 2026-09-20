#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

/* Karatsuba algorithm where n is a power of two.
 * Based on a original code written by François Boulier. */

void allocate_poly(double **A, int n)
{
  *A = (double *) malloc (n * sizeof (double));
}

void free_poly(double *A)
{
  free(A);
}

void init_poly(double *A, int n)
{
    for (int i = 0; i < n; i++)
    {
      /* Tests performed with integer values for simplicity: */
      A[i] = floor (10.0 * drand48 () - 5.0);
    }
}

void print_poly (char *mesg, double *A, int n)
{
  int i;
  printf ("%s ", mesg);
  for (int i = 0; i < n; i++)
    {
      if (i == 0)
        printf ("%ld ", (long) A[i]);
      else if (i == 1)
        printf ("%ld*x ", (long) A[i]);
      else
        printf ("%ld*x^%d ", (long) A[i], i);
    }
  printf ("\n");
}

bool compare_polys(double *A, double *B, int n)
{
  for (int i = 0; i < n; i++)
    {
      if (A[i] != B[i]) return false;
    }
  return true;
}
void add_poly (double *R, double *A, double *B, int n, long *count)
{
    for ( int i =0 ; i<n ; i++) {
        R[i]= A[i] + B[i];
        (*count)++;
        }

}

void sub_poly (double *R, double *A, double *B, int n,  long *count)
{
     for ( int i =0 ; i<n ; i++) {
            R[i]= A[i] - B[i];
            (*count)++;
            }

}

void mul_poly (double *R, double *A, double *B, int n, long *count)
{
     int i, j,comp;


        for (i = 0; i < 2 * n - 1; i++)
            R[i] = 0.0;



        for (i = 0; i < n; i++){
            for (j = 0; j < n; j++){
                R[i + j] += A[i] * B[j];
                (*count)++;
                }


}
}

void Karatsuba (double *R, double *A, double *B, int n, long *count)
{
  int comp;
  double *A0, *A1, *B0, *B1, *R0, *R2;
  int p = n / 2;
  double R1[n], A01[n], B01[n], R02[n], R3[n];
  /*Other temporary polynomials can be defined here */
  int i;
    if (n == 1) {
            R[0] = A[0] * B[0];
            (*count)++;
            return;
        }
  else
  for (i = 0; i < 2 * n - 1; i++)
        R[i] = 0.0;
    {/* General case: */
      /* Decomposing polynomials A and B can be done in constant time  */
      A0 = A;
      A1 = A + p;
      B0 = B;
      B1 = B + p;

      /* Polynomials R0 and R2 are sub-arrays of R (hence avoiding array copies) */
      R0 = R;
      R2 = R + n;

      /* ... todo ... */
    }
Karatsuba(R0,A0,B0,p,count);
Karatsuba(R2,A1,B1,p,count);
add_poly (A01, A0, A1,p,count);
add_poly (B01, B0, B1,p,count);
add_poly (R02, R0, R2,n-1,count);
Karatsuba(R3,A01,B01,p,count);
sub_poly (R1, R3, R02,n-1,count);
for (i = 0; i < n-1; i++){
        R[i + p] += R1[i];
        (*count)++;


}
}


int main (int argc, char **argv)
{
  double *A = NULL;
  double *B = NULL;
  double *R_naive = NULL;
  double *R_K = NULL;
  long countnaive =0;
  long count=0;

  int n = 8;
  if (argc > 1) { n = atoi(argv[1]); }

  srand48 ((long) 42);

  allocate_poly (&A, n);
  allocate_poly (&B, n);
  allocate_poly (&R_naive, 2*n-1);
  allocate_poly (&R_K, 2*n-1);

  init_poly(A, n);
  init_poly(B, n);
  print_poly ("A = ", A, n);
  printf("\n");
  print_poly ("B = ", B, n);
  printf("\n");

  mul_poly (R_naive, A, B, n, &countnaive);
  print_poly ("Naive: A * B = ", R_naive, 2*n-1);
  printf("\n");
  Karatsuba (R_K, A, B, n, &count);
  print_poly ("Karatsuba: A * B = ", R_K, 2*n-1);
  printf("\n");

  if (compare_polys(R_naive, R_K, 2*n-1))
    printf("=> The two results match!\n");
  else
    printf("=> The two results do NOT match!\n");

  free_poly(A);
  free_poly(B);
  free_poly(R_naive);
  free_poly(R_K);
printf("nombre d'operation arithmetique pour la multiplication naive est %ld et nombre pour l'algo de karatsuba est %ld\n", countnaive, count);
}
