#include <stdlib.h>
#include <math.h>

float generate_exp_distribution_var(float lambda)
{
    float U = rand()/(float)(RAND_MAX + 1.0);
    return -log(1-U)/lambda;
}

float get_mean_exp_distr(float exp_distribution[1000])
{
  float sum = 0;
  for (int i = 0; i < 1000; ++i) {
     sum += exp_distribution[i];
   }

   return sum/1000;
}

float get_std_dev_exp_distr(float mean, float exp_distribution[1000])
{
  float variance = 0;
  for (int i = 0; i < 1000; ++i) {
     variance += pow((exp_distribution[i] - mean), 2);
   }

   return sqrt(variance/(1000-1));
}
