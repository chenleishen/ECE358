#include <queue>
using namespace std;

queue<float> generate_observation_times(float alpha) {
  queue<float> observation_times_queue;
  float observation_time = 0;
  do {
    observation_time += generate_exp_distribution_var(alpha);
    // cout << time << endl;
    if (observation_time > T) break;
    observation_times_queue.push (observation_time);
  } while (observation_time < T);

  return observation_times_queue;
}

queue<float>* generate_arrival_times (float lambda, float packet_lambda) {
  queue<float> arrival_times_queue;
  queue<float> packet_len_queue;
  queue<float> departure_times_queue;

  float arrival_time = 0;
  float departure_time;
  float total_service_time = 0;

  do {
    arrival_time += generate_exp_distribution_var(lambda);

    if (arrival_time > T) break;

    arrival_times_queue.push (arrival_time);

    float packet_len = generate_exp_distribution_var(packet_lambda);
    packet_len_queue.push (packet_len);

    float current_packet_service_time = packet_len/C;

    if (arrival_time > 0 && total_service_time < arrival_time ) {
      departure_time = arrival_time + current_packet_service_time;
    } else {
      departure_time = total_service_time + current_packet_service_time;
    }

    total_service_time = departure_time;

    departure_times_queue.push (departure_time);

    // cout << "arrival_time" << endl;
    // cout << arrival_time << endl;
    // cout << "packet_len" << endl;
    // cout << packet_len << endl;
    // cout << "departure_time" << endl;
    // cout << departure_time << endl;

  } while (arrival_time < T);

  queue<float> * queue_array_ptr = new queue<float> [3];
  queue_array_ptr[0] = arrival_times_queue;
  queue_array_ptr[1] = packet_len_queue;
  queue_array_ptr[2] = departure_times_queue;

  return queue_array_ptr;
}

void arrival_procedure (queue<float> &arrival_times_queue, int &num_of_arrivals) {
  arrival_times_queue.pop();
  num_of_arrivals += 1;
}

void departure_procedure (queue<float> &departure_times_queue, int &num_of_departures) {
  departure_times_queue.pop();
  num_of_departures += 1;
}

void observation_procedure (
  queue<float> &observation_times_queue,
  int &num_of_observations,
  int num_of_arrivals,
  int num_of_departures,
  int &tot_num_packet_in_buffer,
  int &tot_num_idle
) {
  observation_times_queue.pop();
  num_of_observations += 1;

  if (num_of_arrivals > num_of_departures)
  {
    tot_num_packet_in_buffer += num_of_arrivals - num_of_departures;
  }

  if (num_of_arrivals <= num_of_departures)
  {
    tot_num_idle += 1;
  }
}
