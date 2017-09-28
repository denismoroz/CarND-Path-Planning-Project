#ifndef ROAD_H
#define ROAD_H

#include <map>

using namespace std;

#include "vehicle.h"


namespace ppp {

class Road {

  map<int, Vehicles> _vehicles_by_lane;

public:

  Road() {}

  Road(const Road& other) {
    _vehicles_by_lane = other._vehicles_by_lane;
  }

  void clear() {
    _vehicles_by_lane.clear();
  }

  void add(const Vehicle& v) {

    auto it = _vehicles_by_lane.find(v.get_lane());
    if (it == _vehicles_by_lane.end()) {
      Vehicles vehicles;
      vehicles.push_back(v);
      _vehicles_by_lane[v.get_lane()] = vehicles;
    }
    else {
      it->second.push_back(v);
    }
  }

  Vehicles get_vehicles_on_lane(int lane) {
    auto it = _vehicles_by_lane.find(lane);
    if (it == _vehicles_by_lane.end()) {
      return Vehicles();
    }
    else {
      return it->second;
    }
  }

};


};

#endif // ROAD_H
