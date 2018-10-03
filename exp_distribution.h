#ifndef EXP_DISTRIBUTION_H
#define EXP_DISTRIBUTION_H

float generate_exp_distribution_var(float lambda);
float get_mean_exp_distr(float exp_distribution[1000]);
float get_std_dev_exp_distr(float mean, float exp_distribution[1000]);

#endif
