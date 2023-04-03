#include <iostream>

#include "../include/helper_functions.h"
#include "../include/Plane.h"
#include "../include/Runway.h"
#include "../include/Random.h"

using std::cout, std::cerr;

void main_1 ();

void main_2 ();

void main_3 ();

void main_4 ();

void main_5 ();

int main ()     //  Airport simulation program
{
    while (true)
    {
        switch (selectVersion())
        {
            case 1:
                main_1();
                break;
            case 2:
                main_2();
                break;
            case 3:
                main_3();
                break;
            case 4:
                main_4();
                break;
            case 5:
                main_5();
                break;
            case 6:
                cout << "Quitting...\n";
                break;
            default:
                cerr << "ERROR: Invalid option, choose between options 1-6\n";
                continue;
        }
        break;
    }

    return EXIT_SUCCESS;
}

void main_1 ()
/*
Pre:  The user must supply the number of time intervals the simulation is to
      run, the expected number of planes arriving, the expected number
      of planes departing per time interval, and the
      maximum allowed size for runway queues.
Post: The program performs a random simulation of the airport, showing
      the status of the runway at each time interval, and prints out a
      summary of airport operation at the conclusion.
Uses: Classes Runway, Plane, Random and functions run_idle, initialize.
*/
{
    cout << "This program simulates an airport with only one runway." << endl
         << "One plane can land or depart in each unit of time." << endl;

    int end_time;            //  time to run simulation
    int queue_limit;         //  size of Runway queues
    int flight_number = 0;
    double arrival_rate, departure_rate;

    initialize(end_time, queue_limit, arrival_rate, departure_rate);

    Random variable;
    Runway small_airport(queue_limit);

    for (int current_time = 0; current_time < end_time; current_time++)
    { //  loop over time intervals
        int number_arrivals = variable.poisson(arrival_rate);  //  current arrival requests
        for (int i = 0; i < number_arrivals; i++)
        {
            Plane current_plane(flight_number++, current_time, arriving);
            if (small_airport.can_land(current_plane) != success)
            {
                current_plane.refuse();
            }
        }

        int number_departures = variable.poisson(departure_rate); //  current departure requests
        for (int j = 0; j < number_departures; j++)
        {
            Plane current_plane(flight_number++, current_time, departing);
            if (small_airport.can_depart(current_plane) != success)
            {
                current_plane.refuse();
            }
        }

        Plane moving_plane;
        switch (small_airport.activity(current_time, moving_plane))
        {
            //  Let at most one Plane onto the Runway at current_time.
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

    cout << "\nSMALL AIRPORT RUNWAY STATS\n"
            "-----------------------------------------------\n";
    small_airport.shut_down(end_time);
}

void main_2 ()
{
    cout << "This program simulates an airport with two runways.\n"
            "One plane can land on the arrivals runway and one plane\n"
            "can depart from the departures runway in each unit of time.\n";

    int end_time;            //  time to run simulation
    int queue_limit;         //  size of Runway queues
    int flight_number = 0;
    double arrival_rate, departure_rate;

    initialize(end_time, queue_limit, arrival_rate, departure_rate);

    Random variable;
    Runway departures(queue_limit);
    Runway arrivals(queue_limit);

    for (int current_time = 0; current_time < end_time; current_time++)
    { //  loop over time intervals
        int number_arrivals = variable.poisson(arrival_rate);  //  current arrival requests
        for (int i = 0; i < number_arrivals; i++)
        {
            Plane current_plane(flight_number++, current_time, arriving);
            if (arrivals.can_land(current_plane) != success)
            {
                current_plane.refuse();
            }
        }

        int number_departures = variable.poisson(departure_rate); //  current departure requests
        for (int j = 0; j < number_departures; j++)
        {
            Plane current_plane(flight_number++, current_time, departing);
            if (departures.can_depart(current_plane) != success)
            {
                current_plane.refuse();
            }
        }

        Plane moving_plane;
        switch (arrivals.activity(current_time, moving_plane))
        {
            //  Let at most one Plane land at current_time.
            case land:
                moving_plane.land(current_time);
                break;
            case takeoff:
                break;
            case idle:
                run_idle(current_time);
        }

        switch (departures.activity(current_time, moving_plane))
        {
            //  Let at most one Plane take off at current_time.
            case land:
                break;
            case takeoff:
                moving_plane.fly(current_time);
                break;
            case idle:
                run_idle(current_time);
        }
    }

    cout << "\nARRIVALS RUNWAY STATS\n"
            "-----------------------------------------------\n";
    arrivals.shut_down(end_time);
    cout << "\nDEPARTURES RUNWAY STATS\n"
            "-----------------------------------------------\n";
    departures.shut_down(end_time);
}

void main_3 ()
{
    cout << "This program simulates an airport with two runways.\n"
            "One plane can land and one plane can takeoff from either\n"
            "runway in each unit of time, given that it's available.\n";

    int end_time;            //  time to run simulation
    int queue_limit;         //  size of Runway queues
    int flight_number = 0;
    double arrival_rate, departure_rate;

    initialize(end_time, queue_limit, arrival_rate, departure_rate);

    Random variable;
    Runway departures(queue_limit);
    Runway arrivals(queue_limit);
    bool arrivalsIsIdle{}, arrivalsIsFull{};

    for (int current_time = 0; current_time < end_time; current_time++)
    { //  loop over time intervals
        arrivalsIsFull = false;
        int number_arrivals = variable.poisson(arrival_rate);  //  current arrival requests
        cout << "\nNumber of arrivals: " << number_arrivals << '\n';
        if (!number_arrivals)
        {
            arrivalsIsIdle = true;
        }

        for (int i = 0; i < number_arrivals; i++)
        {
            arrivalsIsIdle = false;
            Plane current_plane(flight_number++, current_time, arriving);
            if (arrivals.can_land(current_plane) != success)
            {
                arrivalsIsFull = true;
                if (departures.can_land(current_plane) != success)
                {
                    current_plane.refuse();
                }
            }
        }

        int number_departures = variable.poisson(departure_rate); //  current departure requests
        for (int j = 0; j < number_departures; j++)
        {
            Plane current_plane(flight_number++, current_time, departing);
            if (!arrivalsIsFull)
            {
                if (departures.can_depart(current_plane) != success)
                {
                    if (arrivalsIsIdle)
                    {
                        if (arrivals.can_depart(current_plane) != success)
                        {
                            current_plane.refuse();
                        }
                    }
                    current_plane.refuse();
                }
            }
        }

        Plane moving_plane;
        switch (arrivals.activity(current_time, moving_plane))
        {
            //  Let at most one Plane land at current_time.
            case land:
                moving_plane.land(current_time);
                break;
            case takeoff:
                moving_plane.fly(current_time);
                break;
            case idle:
                arrivalsIsIdle = true;
                run_idle(current_time);
                break;
        }

        switch (departures.activity(current_time, moving_plane))
        {
            //  Let at most one Plane take off at current_time.
            case land:
                moving_plane.land(current_time);
                break;
            case takeoff:
                moving_plane.fly(current_time);
                break;
            case idle:
                run_idle(current_time);
                break;
        }
    }

    cout << "\nARRIVALS RUNWAY STATS\n"
            "-----------------------------------------------\n";
    arrivals.shut_down(end_time);
    cout << "\nDEPARTURES RUNWAY STATS\n"
            "-----------------------------------------------\n";
    departures.shut_down(end_time);
}

void main_4 ()
{
    cout << "This program simulates an airport with three runways.\n"
            "Planes can take off from the departures runway and they\n"
            "can land on the arrivals_main runway, while the third runway\n"
            "is reserved for overflowing arrivals_main. However, if there are\n"
            "no arriving flights, it can be used for departures also.\n";

    int end_time;            //  time to run simulation
    int queue_limit;         //  size of Runway queues
    int flight_number = 0;
    double arrival_rate, departure_rate;

    initialize(end_time, queue_limit, arrival_rate, departure_rate);

    Random variable;
    Runway departures(queue_limit);
    Runway arrivals_main(queue_limit);
    Runway arrivals_alt(queue_limit);
    bool arrivalsIsIdle{};

    for (int current_time = 0; current_time < end_time; current_time++)
    { //  loop over time intervals
        int number_arrivals = variable.poisson(arrival_rate);  //  current arrival requests
        if (!number_arrivals)
        {
            arrivalsIsIdle = true;
        }
        for (int i = 0; i < number_arrivals; i++)
        {
            arrivalsIsIdle = false;
            Plane current_plane(flight_number++, current_time, arriving);
            if (arrivals_main.can_land(current_plane) != success)
            {
                if (arrivals_alt.can_land(current_plane) != success)
                {
                    current_plane.refuse();
                }
            }
        }

        int number_departures = variable.poisson(departure_rate); //  current departure requests
        for (int j = 0; j < number_departures; j++)
        {
            Plane current_plane(flight_number++, current_time, departing);
            if (departures.can_depart(current_plane) != success)
            {
                if (arrivalsIsIdle)
                {
                    if (arrivals_alt.can_depart(current_plane) != success)
                    {
                        current_plane.refuse();
                    }
                }
                current_plane.refuse();
            }
        }

        Plane moving_plane;
        switch (arrivals_main.activity(current_time, moving_plane))
        {
            case land:
                moving_plane.land(current_time);
                break;
            case takeoff:
                moving_plane.fly(current_time);
                break;
            case idle:
                arrivalsIsIdle = true;
                run_idle(current_time);
                break;
        }

        switch (arrivals_alt.activity(current_time, moving_plane))
        {
            case land:
                moving_plane.land(current_time);
                break;
            case takeoff:
                moving_plane.fly(current_time);
                break;
            case idle:
                arrivalsIsIdle = true;
                run_idle(current_time);
                break;
        }

        switch (departures.activity(current_time, moving_plane))
        {
            case land:
                moving_plane.land(current_time);
                break;
            case takeoff:
                moving_plane.fly(current_time);
                break;
            case idle:
                run_idle(current_time);
                break;
        }
    }
    cout << "\nMAIN ARRIVALS RUNWAY STATS\n"
            "-----------------------------------------------\n";
    arrivals_main.shut_down(end_time);
    cout << "\nALTERNATIVE ARRIVALS RUNWAY STATS\n"
            "-----------------------------------------------\n";
    arrivals_alt.shut_down(end_time);
    cout << "\nDEPARTURES RUNWAY STATS\n"
            "-----------------------------------------------\n";
    departures.shut_down(end_time);

}

void main_5 ()
{
    /*
Pre:  The user must supply the number of time intervals the simulation is to
      run, the expected number of planes arriving, the expected number
      of planes departing per time interval, and the
      maximum allowed size for runway queues.
Post: The program performs a random simulation of the airport, showing
      the status of the runway at each time interval, and prints out a
      summary of airport operation at the conclusion.
Uses: Classes Runway, Plane, Random and functions run_idle, initialize.
*/
    {
        cout << "This program simulates an airport with only one runway." << endl
             << "One plane can land or depart in each unit of time." << endl;

        int end_time;            //  time to run simulation
        int queue_limit;         //  size of Runway queues
        int flight_number = 0;
        double arrival_rate, departure_rate;

        initialize(end_time, queue_limit, arrival_rate, departure_rate);

        Random variable;
        Runway small_airport(queue_limit);

        for (int current_time = 0; current_time < end_time; current_time++)
        { //  loop over time intervals
            int number_arrivals = variable.poisson(arrival_rate);  //  current arrival requests
            for (int i = 0; i < number_arrivals; i++)
            {
                Plane current_plane(flight_number++, current_time, arriving);
                if (small_airport.can_land(current_plane) != success)
                {
                    current_plane.refuse();
                }
            }

            int number_departures = variable.poisson(departure_rate); //  current departure requests
            for (int j = 0; j < number_departures; j++)
            {
                Plane current_plane(flight_number++, current_time, departing);
                if (small_airport.can_depart(current_plane) != success)
                {
                    current_plane.refuse();
                }
            }

            Plane moving_plane;
            switch (small_airport.activity(current_time, moving_plane))
            {
                //  Let at most one Plane onto the Runway at current_time.
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

        cout << "\nSMALL AIRPORT RUNWAY STATS\n"
                "-----------------------------------------------\n";
        small_airport.shut_down(end_time);
}