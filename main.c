#include <stdio.h>

int main ()
{
  int N, M, Q; // N is the number of dice, Q is the number of sides of the dice, M is the number of turns of the game
  scanf("%d%d%d", &N, &M, &Q);

  int Pi[N];  // Possibility which dice would be used in the first turn
  float A[N][Q];  // Possibility for a dice to get a certain side
  float B[N][N];  // A right stochastic matrix
  int O[M]; // The result

  for (int i = 0; i < N; ++i) {
    scanf("%d", &Pi[i]);
  }
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < Q; ++j) {
      scanf("%f", &A[i][j]);
    }
  }
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      scanf("%f", &B[i][j]);
    }
  }
  for (int i = 0; i < M; ++i) {
    scanf("%d", &O[i]);
  }

  float D[M][N];  // Possibility of the existence of a certain dice in some turn
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

  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < N; ++j) {
      printf("%f ", D[i][j]);
    }
    printf("\n");
  }

  float p = 1;
  for (int i = 0; i < M; ++i) {
    float q = 0;
    for (int j = 0; j < N; ++j) {
      q += D[i][j] * A[j][O[i]];
    }
    printf("%f ", q);
    p *= q;
    printf("%f\n", p);
  }

  printf("%.4f", p);

  return 0;
}