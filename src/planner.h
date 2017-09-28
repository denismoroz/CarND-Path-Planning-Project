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

#define BUFFER_SIZE 32 // m
#define INC_VELOCITY 0.224

class Planner {
  Vehicle* _car;
  Road _road;
  int _desired_lane = 1;

  bool _is_too_close() {

    double prev_size = _car->get_previous_x().size();

    for(auto v: _road.get_vehicles_on_lane(_car->get_lane())) {

       double check_car_s = v.get_s();
       //check_car_s += ((double)prev_size*0.02*v.get_v());

       if((check_car_s > _car->get_s()) && ((check_car_s-_car->get_s()) < 35)) {
            return true;
       }
    }
    return false;
  }

  bool _is_save_to_change_line(double lane) {
    for (auto v: _road.get_vehicles_on_lane(lane)) {
      double distance = v.get_s() - _car->get_s();

      if (distance > 0) {
        if (distance < BUFFER_SIZE)
        {
          return false;
        }
      }
      else {
        distance = std::abs(distance);
        if (distance < 15 && v.get_v() >=_car->get_v()) {
          return false;
        }
      }
    }
    return true;
  }


public:
  Planner(Vehicle* car):
    _car(car)
  {

  }


  NextAction check(const Road& road) {
     _road = road;

     int lane = _car->get_lane();

     if (_desired_lane != lane) {
       return NextAction(_desired_lane, INC_VELOCITY);
     }

     if (!_is_too_close()) {

       if (lane != 1) {
           if (_is_save_to_change_line(1)) {
               _desired_lane = 1;
               return NextAction(1, INC_VELOCITY);
           }
       }
       return NextAction(lane, INC_VELOCITY);
     }
     else {
       if (lane >= 1) {
         if (_is_save_to_change_line(lane - 1)) {
           _desired_lane = lane - 1;
           return NextAction(_desired_lane, INC_VELOCITY);
         }
       }
       if (lane < 2) {
         if (_is_save_to_change_line(lane + 1)) {
             _desired_lane = lane + 1;
            return NextAction(_desired_lane, INC_VELOCITY);
         }
       }
       return NextAction(lane, -INC_VELOCITY);
     }

  }
};


};



#endif // PLANNER_H
