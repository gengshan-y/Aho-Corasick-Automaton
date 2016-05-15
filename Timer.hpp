#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

class Timer{
private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start;

public:
  /*
   * Function called when starting the timer.
   */
  void begin_timer();

  /*
   * Function called when ending the timer. Returns duration in nanoseconds
   * PRECONDITION: begin_timer() must be called before this function
   */
  long long end_timer();
};

#endif  // TIMER_HPP
