#include <iostream>
#include <queue>
#include "exp_distribution.h"
using namespace std;

const float T = 10;
const float len = 12000.0;
const float alpha = 75.0;
const float C = 1000000.0;
const float rho = 0.25;

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

int main()
{
    float lambda = rho * C / len;
    float avg_num_packets;
    float avg_sojourn_time;
    float p_idle;
    float p_loss;

    cout << "observation" << endl;
    queue<float> observation_times_queue = generate_observation_times(alpha);
    cout << "arrival" << endl;
    queue<float> * arrival_times_and_packet_len = generate_arrival_times(lambda, 1/len);
    queue<float> arrival_times_queue = arrival_times_and_packet_len[0];
    queue<float> packet_len_queue = arrival_times_and_packet_len[1];
    queue<float> departure_times_queue = arrival_times_and_packet_len[2];

    int num_of_arrivals = 0;
    int num_of_departures = 0;
    int num_of_observations = 0;

    cout << "arrival size" << endl;
    cout << arrival_times_queue.size() << endl;
    cout << "observation size" << endl;
    cout << observation_times_queue.size() << endl;
    cout << "departure size" << endl;
    cout << departure_times_queue.size() << endl;

    while (
      !observation_times_queue.empty() ||
      !arrival_times_queue.empty() ||
      !departure_times_queue.empty())
    {
      bool observation_not_empty = !observation_times_queue.empty();
      bool arrival_not_empty = !arrival_times_queue.empty();
      bool departure_not_empty = !departure_times_queue.empty();

      if (observation_not_empty && arrival_not_empty && departure_not_empty)
      {
        float arrival_time = arrival_times_queue.front();
        float observation_time = observation_times_queue.front();
        float departure_time = departure_times_queue.front();

        if (arrival_time < observation_time && arrival_time < departure_time) {
          arrival_times_queue.pop();
          num_of_arrivals += 1;
        } else if (observation_time < arrival_time && observation_time < departure_time) {
          observation_times_queue.pop();
          num_of_observations += 1;
        } else if (departure_time < arrival_time && departure_time < observation_time){
          departure_times_queue.pop();
          num_of_departures += 1;
        }
      }
      else if (observation_not_empty && arrival_not_empty) {
        float arrival_time = arrival_times_queue.front();
        float observation_time = observation_times_queue.front();

        if (arrival_time < observation_time) {
          arrival_times_queue.pop();
          num_of_arrivals += 1;
        } else {
          observation_times_queue.pop();
          num_of_observations += 1;
        }
      } else if (arrival_not_empty && departure_not_empty) {
        float arrival_time = arrival_times_queue.front();
        float departure_time = departure_times_queue.front();

        if (arrival_time < departure_time) {
          arrival_times_queue.pop();
          num_of_arrivals += 1;
        } else {
          departure_times_queue.pop();
          num_of_departures += 1;
        }
      } else if (departure_not_empty && observation_not_empty) {
        float observation_time = observation_times_queue.front();
        float departure_time = departure_times_queue.front();

        if (observation_time < departure_time) {
          observation_times_queue.pop();
          num_of_observations += 1;
        } else {
          departure_times_queue.pop();
          num_of_departures += 1;
        }
      } else if (observation_not_empty) {
        observation_times_queue.pop();
        num_of_observations += 1;
      } else if (departure_not_empty) {
        departure_times_queue.pop();
        num_of_departures += 1;
      } else {
        arrival_times_queue.pop();
        num_of_arrivals += 1;
      }

    }

    cout << "num_of_arrivals" << endl;
    cout << num_of_arrivals << endl;
    cout << "num_of_observations" << endl;
    cout << num_of_observations << endl;
    cout << "num_of_departures" << endl;
    cout << num_of_departures << endl;

    return 0;
}
