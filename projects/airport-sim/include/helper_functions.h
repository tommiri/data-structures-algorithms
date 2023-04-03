#pragma once

#include <iostream>
#include <limits>

using std::cout, std::cerr, std::cin, std::endl, std::flush;

void initialize (int &end_time, int &queue_limit,
                 double &arrival_rate, double &departure_rate)
/*
Pre:  The user specifies the number of time units in the simulation,
      the maximal queue sizes permitted,
      and the expected arrival and departure rates for the airport.
Post: The program prints instructions and initializes the parameters
      end_time, queue_limit, arrival_rate, and departure_rate to
      the specified values.
*/

{
    cout << "Up to what number of planes can be waiting to land "
         << "or take off at any time? " << flush;
    cin >> queue_limit;

    cout << "How many units of time will the simulation run? " << flush;
    cin >> end_time;

    bool acceptable;
    do
    {
        cout << "Expected number of arrivals per unit time? " << flush;
        cin >> arrival_rate;
        cout << "Expected number of departures per unit time? " << flush;
        cin >> departure_rate;
        if (arrival_rate < 0.0 || departure_rate < 0.0)
        {
            cerr << "These rates must be non-negative." << endl;
        }
        else
        {
            acceptable = true;
        }

        if (acceptable && arrival_rate + departure_rate > 1.0)
        {
            cerr << "Safety Warning: This airport will become saturated. " << endl;
        }

    } while (!acceptable);
}

void run_idle (int time)
/*
Post: The specified time is printed with a message that the runway is idle.
*/
{
    cout << time << ": Runway is idle." << endl;
}

int selectVersion ()
{
    int option{};
    bool isValidOption{};

    while (!isValidOption)
    {
        isValidOption = true;
        cout << "\n1.\tRun P1 version of Airport simulator\n"
                "2.\tRun P2 version of Airport simulator\n"
                "3.\tRun P3 version of Airport simulator\n"
                "4.\tRun P4 version of Airport simulator\n"
                "5.\tRun P5 version of Airport simulator\n"
                "6.\tQuit the program\n\n"
                "Your choice: ";

        cin >> option;

        if (cin.fail())
        {
            isValidOption = false;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "ERROR: Option must be an integer\n";
        }
    }

    return option;
}