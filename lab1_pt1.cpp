#include <iostream>
#include "exp_distribution.h"

using namespace std;

// g++ lab1_pt1.cpp generate_exp_distribution.cpp -o lab1_pt1.exe

int main()
{
    int size = 1000;
    float lambda = 75.0;

    float exp_distribution [1000];
    for (int i=0; i<size; i++){
       exp_distribution[i] = generate_exp_distribution_var(lambda);
    }

    float mean = get_mean_exp_distr(exp_distribution);
    float std_dev = get_std_dev_exp_distr(mean, exp_distribution);

    cout << "Mean is " << mean << endl;
    cout << "Standard deviation is " << std_dev << endl;

    return 0;
}
