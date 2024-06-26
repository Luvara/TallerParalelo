#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <immintrin.h>



#include <sys/time.h> // for create thread
#include <time.h>

double now(){
  struct timeval t; double f_t;
  gettimeofday(&t, NULL);
  f_t = t.tv_usec; f_t = f_t/1000000.0; f_t +=t.tv_sec;
  return f_t;
}


void init(float  *V,int N)
{
    for (int i = 0 ; i<N ; i++){
        V[i] = (float)rand()/(float)RAND_MAX;
    }
}

float sum_sqrt(float *a, int N){
  int i;
  float s;
  s = 0;
  for(i = 0; i < N; i++)
    s = s + sqrt(a[i]);
  return s;
}

float vec_sum_sqrt(float *a, int N){
  int i;
  __m256 v;
  __m256 w;
  float s;
  for (int i = 0; i < N; i+=8){
    v = _mm256_load_ps(&a[i]);
    w = _mm256_add_ps(w, _mm256_sqrt_ps(v));
  }
  s = 0;
  for (int i = 0; i < N; i++) 
    s = s + w[i];

  return s;
}

int main() {
    double t0,t1,t;
    int N;
    N = 1000000;
    //float  *U = malloc(N*sizeof(float));
    float U[N] __attribute__((aligned(32)));
    init(U,N);
    
    float s;
    t0 = now();
    s = sum_sqrt(U, N);
    t1 = now();
    t = t1-t0;
    printf("The sum of the square root of the %d elements of U equals to %f\n", N, s);
    printf("The computation was done in %f second(s)\n", t);

    t0 = now();
    s = vec_sum_sqrt(U, N);
    t1 = now();
    t = t1-t0;
    printf("The sum of the square root of the %d elements of U equals to %f\n", N, s);
    printf("The computation was done in %f second(s)\n", t);

}
 
