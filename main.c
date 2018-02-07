#include <stdio.h>

int main ()
{
  int N, M, Q; // N is the number of dice, Q is the number of sides of the dice, M is the number of turns of the game
  scanf("%d%d%d", &N, &M, &Q);

  double Pi[N];  // Possibility which dice would be used in the first turn
  double A[N][Q];  // Possibility for a dice to get a certain side
  double B[N][N];  // A right stochastic matrix

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

  double p;
  if (M == 1) {
    int O;  // The result
    scanf("%d", &O);
    p = 0;
    for (int i = 0; i < N; ++i) {
      p += Pi[i] * A[i][O];
    }
  } else {
    int O[M]; // The result
    for (int i = 0; i < M; ++i) {
      scanf("%d", &O[i]);
    }
    double D[M][N];  // Possibility of the existence of a certain dice in some turn
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
    p = 1;
    for (int i = 0; i < M; ++i) {
      double q = 0;
      for (int j = 0; j < N; ++j) {
        q += D[i][j] * A[j][O[i]];
      }
//    printf("%f ", q);
      p *= q;
//    printf("%f\n", p);
    }
  }

  printf("%.4lf", p);
  return 0;
}