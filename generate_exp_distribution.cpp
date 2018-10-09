#include <stdlib.h>
#include <math.h>

const int distr_size = 1000;

float generate_exp_distribution_var(float lambda)
{
    float U = rand()/(float)(RAND_MAX + 1.0);
    return -log(1-U)/lambda;
}

float get_mean_exp_distr(float exp_distribution[distr_size])
{
  float sum = 0;
  for (int i = 0; i < distr_size; ++i) {
     sum += exp_distribution[i];
   }

   return sum/distr_size;
}

float get_variance_exp_distr(float mean, float exp_distribution[distr_size])
{
  float variance_numerator = 0;
  for (int i = 0; i < distr_size; ++i) {
     variance_numerator += pow((exp_distribution[i] - mean), 2);
   }

   return variance_numerator/distr_size;
}
