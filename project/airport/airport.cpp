#include "random.h"
#include "runway.h"

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::flush;

void run_idle(int time)
{
	cout << time << ": Runway is idle." << endl;
}

void single_runway()
{
	int end_time;            //  time to run simulation
	size_t queue_limit;         //  size of Runway queues
	int flight_number = 0;
	double arrival_rate, departure_rate;
	cout	<< "This program simulates an airport with only one runway." << endl
			<< "One plane can land or depart in each unit of time." << endl 
			<< "Up to what number of planes can be waiting to land "
			<< "or take off at any time? " << flush;
	cin  >> queue_limit;

	cout << "How many units of time will the simulation run?" << flush;
	cin  >> end_time;

	bool acceptable;
	do {
		cout << "Expected number of arrivals per unit time?" << flush;
		cin  >> arrival_rate;
		cout << "Expected number of departures per unit time?" << flush;
		cin  >> departure_rate;
		if (arrival_rate < 0.0 || departure_rate < 0.0) {
			cerr << "These rates must be nonnegative." << endl;
		}
		else {
			acceptable = true;
		}

		if (acceptable && arrival_rate + departure_rate > 1.0) {
			cerr << "Safety Warning: This airport will become saturated. " << endl;
		}

	} while (!acceptable);
	Random variable;
	Runway small_airport(queue_limit);
	for (int current_time = 0; current_time < end_time; current_time++) {
		int number_arrivals = variable.poisson(arrival_rate);
		for (int i = 0; i < number_arrivals; i++) {
			Plane current_plane(flight_number++, current_time, arriving);
			if (small_airport.can_land(current_plane) != success)
				current_plane.refuse(); }

		int number_departures= variable.poisson(departure_rate);
		for (int j = 0; j < number_departures; j++) {
			Plane current_plane(flight_number++, current_time, departing);
			if (small_airport.can_depart(current_plane) != success)
				current_plane.refuse();
		}

		Plane moving_plane;
		switch (small_airport.activity(current_time, moving_plane)) {
			case land:
				moving_plane.land(current_time);
				break;
			case takeoff:
				moving_plane.fly(current_time);
				break;
			case idle:
				run_idle(current_time);
		}
	}
	small_airport.shut_down(end_time);
}

void strict_dual_runway()
{
    int end_time;            //  time to run simulation
    size_t queue_limit;         //  size of Runway queues
    int flight_number = 0;
    double arrival_rate, departure_rate;
    cout    << "This program simulates an airport with two runways." << endl
            << "One runway is dedicated to takeoffs and the other to landings." << endl 
            << "Up to what number of planes can be waiting to land or take off at any time? " << flush;
    cin  >> queue_limit;

    cout << "How many units of time will the simulation run?" << flush;
    cin  >> end_time;

    bool acceptable;
    do {
        cout << "Expected number of arrivals per unit time?" << flush;
        cin  >> arrival_rate;
        cout << "Expected number of departures per unit time?" << flush;
        cin  >> departure_rate;
        if (arrival_rate < 0.0 || departure_rate < 0.0) {
            cerr << "These rates must be nonnegative." << endl;
        }
        else {
            acceptable = true;
        }

        if (acceptable && arrival_rate + departure_rate > 2.0) {
            cerr << "Safety Warning: The airport will become saturated." << endl;
        }

    } while (!acceptable);

    Random variable;
    Runway takeoff_runway(queue_limit);
    Runway landing_runway(queue_limit);

    for (int current_time = 0; current_time < end_time; current_time++) {
        int number_arrivals = variable.poisson(arrival_rate);
        for (int i = 0; i < number_arrivals; i++) {
            Plane current_plane(flight_number++, current_time, arriving);
            if (landing_runway.can_land(current_plane) != success)
                current_plane.refuse();
        }

        int number_departures = variable.poisson(departure_rate);
        for (int j = 0; j < number_departures; j++) {
            Plane current_plane(flight_number++, current_time, departing);
            if (takeoff_runway.can_depart(current_plane) != success)
                current_plane.refuse();
        }

        Plane landing_plane, takeoff_plane;
        Runway_activity land_activity = landing_runway.activity(current_time, landing_plane);
        Runway_activity takeoff_activity = takeoff_runway.activity(current_time, takeoff_plane);

        switch (land_activity) {
            case land:
                landing_plane.land(current_time);
                break;
            case idle:
                run_idle(current_time);
                break;
            default:
                break;
        }

        switch (takeoff_activity) {
            case takeoff:
                takeoff_plane.fly(current_time);
                break;
            case idle:
                run_idle(current_time);
                break;
            default:
                break;
        }
    }

    landing_runway.shut_down(end_time);
    takeoff_runway.shut_down(end_time);
}

void dynamic_dual_runway()
{
    int end_time;            //  time to run simulation
    size_t queue_limit;         //  size of Runway queues
    int flight_number = 0;
    double arrival_rate, departure_rate;
    cout    << "This program simulates an airport with two runways." << endl
            << "One runway is usually used for takeoffs and the other for landings." << endl 
            << "Up to what number of planes can be waiting to land or take off at any time? " << flush;
    cin  >> queue_limit;

    cout << "How many units of time will the simulation run?" << flush;
    cin  >> end_time;

    bool acceptable;
    do {
        cout << "Expected number of arrivals per unit time?" << flush;
        cin  >> arrival_rate;
        cout << "Expected number of departures per unit time?" << flush;
        cin  >> departure_rate;
        if (arrival_rate < 0.0 || departure_rate < 0.0) {
            cerr << "These rates must be nonnegative." << endl;
        }
        else {
            acceptable = true;
        }

        if (acceptable && (arrival_rate + departure_rate) > 2.0) {
            cerr << "Safety Warning: The airport will become saturated." << endl;
        }

    } while (!acceptable);

    Random variable;
    Runway takeoff_runway(queue_limit);
    Runway landing_runway(queue_limit);

    for (int current_time = 0; current_time < end_time; current_time++) {
        int number_arrivals = variable.poisson(arrival_rate);
        int number_departures = variable.poisson(departure_rate);

        // Determine if landing queue is full
        bool landing_queue_full = landing_runway.landing_queue_size() >= queue_limit;

        for (int i = 0; i < number_arrivals; i++) {
            Plane current_plane(flight_number++, current_time, arriving);
            if (landing_queue_full && takeoff_runway.takeoff_queue_size() < queue_limit) {
                // If landing queue is full, but takeoff queue has space, land the plane on takeoff runway
                if (takeoff_runway.can_land(current_plane) != success)
                    current_plane.refuse();
            } else {
                // Otherwise, land the plane on landing runway
                if (landing_runway.can_land(current_plane) != success)
                    current_plane.refuse();
            }
        }

        for (int j = 0; j < number_departures; j++) {
            Plane current_plane(flight_number++, current_time, departing);
            // Depart the plane from takeoff runway
            if (takeoff_runway.can_depart(current_plane) != success)
                current_plane.refuse();
        }

        // Runway_activity for both runways
        Plane landing_plane, takeoff_plane;
        Runway_activity land_activity = landing_runway.activity(current_time, landing_plane);
        Runway_activity takeoff_activity = takeoff_runway.activity(current_time, takeoff_plane);

        switch (land_activity) {
            case land:
                landing_plane.land(current_time);
                break;
            case idle:
                run_idle(current_time); 
                break;
            default:
                break;
        }

        switch (takeoff_activity) {
            case takeoff:
                takeoff_plane.fly(current_time);
                break;
            case idle:
                run_idle(current_time);
                break;
            default:
                break;
        }
    }

    landing_runway.shut_down(end_time);
    takeoff_runway.shut_down(end_time);
}

void triple_runway()
{
    int end_time;            //  time to run simulation
    size_t queue_limit;         //  size of Runway queues
    int flight_number = 0;
    double arrival_rate, departure_rate;
    cout    << "This program simulates an airport with three runways." << endl
            << "One runway is always reserved for landing and takeoff." << endl
            << "The third runway is used for landings unless its queue is empty, in which case it can be used for takeoffs." << endl 
            << "Up to what number of planes can be waiting to land or take off at any time? " << flush;
    cin  >> queue_limit;

    cout << "How many units of time will the simulation run?" << flush;
    cin  >> end_time;

    bool acceptable;
    do {
        cout << "Expected number of arrivals per unit time?" << flush;
        cin  >> arrival_rate;
        cout << "Expected number of departures per unit time?" << flush;
        cin  >> departure_rate;
        if (arrival_rate < 0.0 || departure_rate < 0.0) {
            cerr << "These rates must be nonnegative." << endl;
        }
        else {
            acceptable = true;
        }

        if (acceptable && (arrival_rate + departure_rate) > 3.0) {
            cerr << "Safety Warning: The airport will become saturated." << endl;
        }

    } while (!acceptable);

    Random variable;
    Runway main_runway(queue_limit);
    Runway landing_runway(queue_limit);
    Runway additional_runway(queue_limit);

    for (int current_time = 0; current_time < end_time; current_time++) {
        int number_arrivals = variable.poisson(arrival_rate);
        int number_departures = variable.poisson(departure_rate);

        bool landing_queue_empty = landing_runway.landing_queue_size() == 0;

        for (int i = 0; i < number_arrivals; i++) {
            Plane current_plane(flight_number++, current_time, arriving);
            if (landing_queue_empty && additional_runway.landing_queue_size() < queue_limit) {
                // If landing queue is empty, land the plane on additional runway
                if (additional_runway.can_land(current_plane) != success)
                    current_plane.refuse();
            } else {
                // Otherwise, land the plane on landing runway
                if (landing_runway.can_land(current_plane) != success)
                    current_plane.refuse();
            }
        }

        for (int j = 0; j < number_departures; j++) {
            Plane current_plane(flight_number++, current_time, departing);
            // Depart the plane from main runway
            if (main_runway.can_depart(current_plane) != success)
                current_plane.refuse();
        }

        // Runway_activity for all runways
        Plane main_plane, landing_plane, additional_plane;
        Runway_activity main_activity = main_runway.activity(current_time, main_plane);
        Runway_activity landing_activity = landing_runway.activity(current_time, landing_plane);
        Runway_activity additional_activity = additional_runway.activity(current_time, additional_plane);

        switch (main_activity) {
            case land:
                main_plane.land(current_time);
                break;
            case takeoff:
                main_plane.fly(current_time);
                break;
            case idle:
                run_idle(current_time);
                break;
            default:
                break;
        }

        switch (landing_activity) {
            case land:
                landing_plane.land(current_time);
                break;
            case idle:
                run_idle(current_time);
                break;
            default:
                break;
        }

        switch (additional_activity) {
            case land:
                additional_plane.land(current_time);
                break;
            case idle:
                run_idle(current_time);
                break;
            default:
                break;
        }
    }

    main_runway.shut_down(end_time);
    landing_runway.shut_down(end_time);
    additional_runway.shut_down(end_time);
}

void single_runway_fuel() {
    int end_time;            //  time to run simulation
    size_t queue_limit;      //  size of Runway queues
    int flight_number = 0;
    double arrival_rate, departure_rate;
    cout << "This program simulates an airport with only one runway." << endl
         << "One plane can land or depart in each unit of time." << endl
         << "Up to what number of planes can be waiting to land "
         << "or take off at any time? " << flush;
    cin >> queue_limit;

    cout << "How many units of time will the simulation run?" << flush;
    cin >> end_time;

    bool acceptable;
    do {
        cout << "Expected number of arrivals per unit time?" << flush;
        cin >> arrival_rate;
        cout << "Expected number of departures per unit time?" << flush;
        cin >> departure_rate;
        if (arrival_rate < 0.0 || departure_rate < 0.0) {
            cerr << "These rates must be nonnegative." << endl;
        } else {
            acceptable = true;
        }

        if (acceptable && arrival_rate + departure_rate > 1.0) {
            cerr << "Safety Warning: This airport will become saturated. " << endl;
        }

    } while (!acceptable);

    Random variable;
    Runway small_airport(queue_limit);
    for (int current_time = 0; current_time < end_time; current_time++) {
        int number_arrivals = variable.poisson(arrival_rate);
        for (int i = 0; i < number_arrivals; i++) {
            int fuel_time = variable.random_integer(1, 10); // Generating random fuel time
            Plane current_plane(flight_number++, current_time, arriving, fuel_time); // Adding fuel_time to Plane constructor
            if (current_plane.get_fuel_time() <= small_airport.get_queue_limit() && small_airport.can_land(current_plane) == success) {
                small_airport.can_land(current_plane); // Plane has enough fuel to wait in the queue
            } else {
                current_plane.land(current_time); // Plane doesn't have enough fuel, it lands immediately
            }
        }

        int number_departures = variable.poisson(departure_rate);
        for (int j = 0; j < number_departures; j++) {
            Plane current_plane(flight_number++, current_time, departing);
            if (small_airport.can_depart(current_plane) == success) {
                small_airport.can_depart(current_plane);
            } else {
                current_plane.refuse(); // If unable to depart, refuse the plane
            }
        }
    }
    small_airport.shut_down(end_time);
}

int main()
{
	int choice = 1;
	for (;;) {
		cout << "Choose desired simulation:" << endl;
		for (int i = 1; i <= 5; i++) {
			cout << i << ". Run P" << i << " version of Airport simulator" << endl;
		}
		cout << "6. Quit the program" << endl;
		cout << "Enter choice: ";
		cin >> choice;
		switch (choice) {
		case 1:
			single_runway();
			break;
		case 2:
			strict_dual_runway();
			break;
		case 3:
			dynamic_dual_runway();
			break;
		case 4:
			triple_runway();
			break;
		case 5:
			single_runway_fuel();
			break;
		case 6:
			cout << "Exiting...";
			exit(0);
		default:
			cout << "This choice is not defined" << endl;
		}
		cout << endl;
	}
	return 0;
}
