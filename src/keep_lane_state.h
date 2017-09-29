#ifndef KEEP_LANE_STATE_H
#define KEEP_LANE_STATE_H

#include "planner.h"

namespace ppp {

class KeepLaneState: public PlannerState {

public:
  KeepLaneState(Planner* planner) : PlannerState(planner) {

  }

  KeepLaneState(const KeepLaneState& other) : PlannerState(other) {

  }

  NextAction next_action();
};

};

#endif // KEEP_LANE_STATE_H
