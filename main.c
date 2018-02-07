#include <stdio.h>
#include <stdlib.h>

int main ()
{
  int N, M, Q; // N is the number of dice, Q is the number of sides of the dice, M is the number of turns of the game
  scanf("%d%d%d", &N, &M, &Q);

  double *Pi = (double *) malloc(N * sizeof(double));  // Possibility which dice would be used in the first turn (N)
  double **A = (double **) malloc(N * sizeof(double *));  // Possibility for a dice to get a certain side (N*Q)
  for (int i = 0; i < N; ++i) {
    A[i] = (double *) malloc(Q * sizeof(double));
  }
  double **B = (double **) malloc(N * sizeof(double *));  // A right stochastic matrix (N*N)
  for (int i = 0; i < N; ++i) {
    B[i] = (double *) malloc(N * sizeof(double));
  }
  int *O = (int *) malloc(M * sizeof(int)); // The result (M)

  for (int i = 0; i < N; ++i) {
    scanf("%lf", &Pi[i]);
  }
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < Q; ++j) {
      scanf("%lf", &A[i][j]);
    }
  }
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      scanf("%lf", &B[i][j]);
    }
  }
  for (int i = 0; i < M; ++i) {
    scanf("%d", &O[i]);
  }

  double **D = (double **) malloc(M * sizeof(double *));  // Possibility of the existence of a certain dice in some turn (M*N)
  for (int i = 0; i < M; ++i) {
    D[i] = (double *) malloc(N * sizeof(double));
  }
  for (int j = 0; j < N; ++j) {
    D[0][j] = Pi[j];
  }
  for (int i = 1; i < M; ++i) {
    for (int j = 0; j < N; ++j) {
      D[i][j] = 0;
      for (int k = 0; k < N; ++k) {
        D[i][j] += D[i - 1][k] * B[k][j];
      }
    }
  }

//  for (int i = 0; i < M; ++i) {
//    for (int j = 0; j < N; ++j) {
//      printf("%f ", D[i][j]);
//    }
//    printf("\n");
//  }

  double p = 1;
  for (int i = 0; i < M; ++i) {
    double q = 0;
    for (int j = 0; j < N; ++j) {
      q += D[i][j] * A[j][O[i]];
    }
//    printf("%f ", q);
    p *= q;
//    printf("%f\n", p);
  }

  printf("%.4lf", p);
  return 0;
}