#include "keep_lane_state.h"
#include "change_lane_state.h"

using namespace ppp;


ppp::NextAction ppp::KeepLaneState::next_action() {
  int lane = _planner->car->get_lane();

  if (_planner->is_too_close()) {
    if (lane >= 1) {
        if (_planner->is_save_to_change_line(lane-1)) {
            _planner->state = PlannerStatePtr(new ChangeLaneState(lane-1, _planner));
           return NextAction(lane-1, INC_VELOCITY);
        }
    }
    if (lane <= 1) {
       if (_planner->is_save_to_change_line(lane + 1)) {
           _planner->state = PlannerStatePtr(new ChangeLaneState(lane+1, _planner));
           return NextAction(lane+1, INC_VELOCITY);
       }
    }
    return NextAction(lane, -INC_VELOCITY);
  }
  else {
    if (lane != 1) {
      if (_planner->is_save_to_change_line(1)) {
          _planner->state = PlannerStatePtr(new ChangeLaneState(1, _planner));
          return NextAction(1, INC_VELOCITY);
      }
    }
    return NextAction(lane, INC_VELOCITY);
  }

  return NextAction(lane, INC_VELOCITY);
}
