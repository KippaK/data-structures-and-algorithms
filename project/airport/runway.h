#pragma once

#include "utility.h"
#include "plane.h"
#include "queue.h"

enum Runway_activity {idle, land, takeoff};

class Runway {
public:
	Runway(int limit);
	Error_code can_land(Plane current);
	Error_code can_depart(Plane current);
	Runway_activity activity(int time, Plane &moving);
	void shut_down(int time) const;
	size_t landing_queue_size() const;
	size_t takeoff_queue_size() const;

private:
	Queue<Plane> landingQ;
	Queue<Plane> takeoffQ;
	size_t queue_limit;
	size_t num_land_requests;        //  number of planes asking to land
	size_t num_takeoff_requests;     //  number of planes asking to take off
	size_t num_landings;             //  number of planes that have landed
	size_t num_takeoffs;             //  number of planes that have taken off
	size_t num_land_accepted;        //  number of planes queued to land
	size_t num_takeoff_accepted;     //  number of planes queued to take off
	size_t num_land_refused;         //  number of landing planes refused
	size_t num_takeoff_refused;      //  number of departing planes refused
	size_t land_wait;                //  total time of planes waiting to land
	size_t takeoff_wait;             //  total time of planes waiting to take off
	size_t idle_time;                //  total time runway is idle
};
