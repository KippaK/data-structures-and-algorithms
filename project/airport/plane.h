#pragma once
#include <cstddef>

enum Plane_status {null, arriving, departing};

class Plane {
public:
	Plane();
	Plane(int flt, int time, Plane_status status);
	Plane(int flt, int time, Plane_status status, size_t fuel);
	void refuse() const;
	void land(int time) const;
	void fly(int time) const;
	int started() const;
	size_t get_fuel_time() const;

private:
	int flt_num;
	int clock_start;
	Plane_status state;
	size_t fuel_time;
};
