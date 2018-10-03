#ifndef EXP_DISTRIBUTION_H
#define EXP_DISTRIBUTION_H

class MM1_Simulation {
  private:
    const float T;
    const float len;
    const float C;
    const float rho;

  public:
    MM1_Simulation(float t_in, float len_in, float c_in, float rho_in) :
    T(t_in), len(len_in), C(c_in), rho(rho_in) {}

    void run() {
      
    }

};

queue<float> MM1_Simulation :: generate_observation_times(float alpha)
queue<float>* MM1_Simulation :: generate_arrival_times (float lambda, float packet_lambda)
void MM1_Simulation :: arrival_procedure (queue<float> &arrival_times_queue, int &num_of_arrivals)
void MM1_Simulation :: departure_procedure (queue<float> &departure_times_queue, int &num_of_departures)
void MM1_Simulation :: observation_procedure (
  queue<float> &observation_times_queue,
  int &num_of_observations,
  int num_of_arrivals,
  int num_of_departures,
  int &tot_num_packet_in_buffer,
  int &tot_num_idle
)

#endif
