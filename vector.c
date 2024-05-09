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


}

int main() {
    double t0,t1,t;
    int N;
    N = 100000;
    float  *U = malloc(N*sizeof(float));
    init(U,N);
    
    float s;
    t0 = now();
    s = sum_sqrt(U, N);
    t1 = now();
    t = t1-t0;
    printf("The sum of the square root of the %d elements of U equals to %f\n", N, s);
    printf("The computation was done in %f second(s)\n", t);

}
 
