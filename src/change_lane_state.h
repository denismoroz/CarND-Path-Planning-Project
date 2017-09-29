#ifndef CHANGE_LANE_STATE_H
#define CHANGE_LANE_STATE_H

#include "planner.h"

namespace ppp {

class ChangeLaneState: public PlannerState {

  int _desired_lane;

public:

  ChangeLaneState(int lane, Planner* planner):
    PlannerState(planner) {
    _desired_lane = lane;
  }

  ChangeLaneState(const ChangeLaneState& other): PlannerState(other) {
    _desired_lane = other._desired_lane;
  }

  NextAction next_action();
};


};



#endif //CHANGE_LANE_STATE_H
