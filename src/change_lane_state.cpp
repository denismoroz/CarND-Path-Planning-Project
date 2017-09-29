#include "planner.h"
#include "change_lane_state.h"
#include "keep_lane_state.h"


ppp::NextAction ppp::ChangeLaneState::next_action() {
  int lane = _planner->car->get_lane();

   if (_desired_lane == lane) {
     _planner->state = PlannerStatePtr(new KeepLaneState(_planner));
   }
   else {
     if (!_planner->is_save_to_change_line(_desired_lane)) {
         _desired_lane = lane;
     }
   }

   return NextAction(_desired_lane, INC_VELOCITY);
}
//
