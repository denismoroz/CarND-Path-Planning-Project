#ifndef PLANNER_H
#define PLANNER_H

#include "vehicle.h"
#include "road.h"

using namespace std;

namespace ppp {

class NextAction {
public:
  int lane;
  double velocity_change;

  NextAction(int l, double v): lane(l), velocity_change(v) {

  }

  NextAction(const NextAction& other) {
    lane = other.lane;
    velocity_change = other.velocity_change;
  }

};

class Planner;

class PlannerState {
protected:
  Planner *_planner;

public:
  PlannerState(Planner* planner) : _planner(planner) {

  }

  PlannerState(const PlannerState& other) {
    _planner = other._planner;
  }

  virtual NextAction next_action() = 0;
};

typedef unique_ptr<PlannerState> PlannerStatePtr;



#define BUFFER_SIZE 32 // m
#define BACK_BUFFER_SIZE 15
#define INC_VELOCITY 0.224
#define FRONT_SAFE_DISTANCE 35

class Planner {

public:
  Vehicle* car;
  Road road;
  PlannerStatePtr state;

  bool is_too_close();

  bool is_save_to_change_line(double lane);

public:
  Planner(Vehicle* car);
  NextAction check(const Road& road);
};

};



#endif // PLANNER_H
