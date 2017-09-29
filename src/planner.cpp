#include <cstdlib>
#include "planner.h"
#include "keep_lane_state.h"

ppp::Planner::Planner(Vehicle* car):
  car(car)
{
    state = PlannerStatePtr(new KeepLaneState(this));
}


ppp::NextAction ppp::Planner::check(const Road& road){
  this->road = road;
  return state->next_action();
}



bool ppp::Planner::is_too_close() {

 double prev_size = car->get_previous_x().size();

 for(auto v: road.get_vehicles_on_lane(car->get_lane())) {

    double check_car_s = v.get_s();
    if((check_car_s > car->get_s()) && ((check_car_s-car->get_s()) < FRONT_SAFE_DISTANCE)) {
         return true;
    }
 }
 return false;
}

bool ppp::Planner::is_save_to_change_line(double lane) {
 for (auto v: road.get_vehicles_on_lane(lane)) {
   double distance = v.get_s() - car->get_s();
   // Checking cars that in front of the car
   if (distance >= 0) {
     if (distance < FRONT_SAFE_DISTANCE)
     {
       return false;
     }
   }
   // checking cars that are on the back of the car
   else {
     distance *= -1;
     if (distance < BACK_BUFFER_SIZE && v.get_v() >= car->get_v()) {
       return false;
     }
   }
 }
 return true;
}
