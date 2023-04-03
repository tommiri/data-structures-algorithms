#include <iostream>

#include "../include/Runway.h"

using std::cout, std::endl;

Runway::Runway (int limit)
/*
Post:  The Runway data members are initialized to record no
       prior Runway use and to record the limit on queue sizes.
*/

{
    queue_limit = limit;
    num_land_requests = num_takeoff_requests = 0;
    num_landings = num_takeoffs = 0;
    num_land_refused = num_takeoff_refused = 0;
    num_land_accepted = num_takeoff_accepted = 0;
    land_wait = takeoff_wait = idle_time = 0;
    num_crashed = 0;
}


Error_code Runway::can_land (const Plane &current)
/*
Post:  If possible, the Plane current is added to the
       landing Queue; otherwise, an Error_code of overflow is
       returned. The Runway statistics are updated.
Uses:  class Queue.
*/

{
    Error_code result;
    if (current.getFuelLevel() < landing.size()) // if plane doesnt have enough fuel to wait in queue
    {
        cout << "Fuel level critical!\n";
        Queue temp_queue;
        int landing_size = landing.size();

        for (int i = 0; i < landing_size; i++)
        {
            Plane temp_plane;
            landing.serve_and_retrieve(temp_plane); // empty landing queue

            if (temp_plane.getFuelLevel() <= current.getFuelLevel())
            {   // if first plane in landing queue has less or equal amount of fuel than current, place it back into the queue
                landing.append(temp_plane);
            }
            else
            {
                temp_queue.append(temp_plane); // add planes to temp_queue
            }
        }

        // if fuel level is high enough after completing operations
        if (current.getFuelLevel() >= landing.size())
        {
            cout << "Adjusting position in queue to allow landing.\n";
            landing.append(current); // append current plane to front of landing queue
            while (!temp_queue.empty())
            {
                Plane temp_plane;
                temp_queue.serve_and_retrieve(temp_plane);
                landing.append(temp_plane); // add other planes back to landing queue
            }
            result = success;
        }
        else
        {
            // if landing queue is still too long, plane crashes
            cout << "Could not allow plane to land as others would've crashed.\n";
            result = fatal;
        }
    }
    else
    {
        if (landing.size() < queue_limit)
        {
            result = landing.append(current);
        }
        else
        {
            result = fail;
        }
    }
    num_land_requests++;

    if (result != success)
    {
        result == fatal ? num_crashed++ : num_land_refused++;
    }
    else
    {
        num_land_accepted++;
    }

    return result;
}


Error_code Runway::can_depart (const Plane &current)
/*
Post:  If possible, the Plane current is added to the
       takeoff Queue; otherwise, an Error_code of overflow is
       returned. The Runway statistics are updated.
Uses:  class Queue.
*/

{
    Error_code result;
    if (takeoff.size() < queue_limit)
    {
        result = takeoff.append(current);
    }
    else
    {
        result = fail;
    }
    num_takeoff_requests++;
    if (result != success)
    {
        num_takeoff_refused++;
    }
    else
    {
        num_takeoff_accepted++;
    }

    return result;
}


Runway_activity Runway::activity (int time, Plane &moving)
/*
Post:  If the landing Queue has entries, its front
       Plane is copied to the parameter moving
       and a result  land is returned. Otherwise,
       if the takeoff Queue has entries, its front
       Plane is copied to the parameter moving
       and a result  takeoff is returned. Otherwise,
       idle is returned. Runway statistics are updated.
Uses:  class Queue.
*/

{
    Runway_activity in_progress;
    if (!landing.empty())
    {
        landing.retrieve(moving);
        land_wait += time - moving.started();
        num_landings++;
        in_progress = land;
        landing.serve();
    }

    else if (!takeoff.empty())
    {
        takeoff.retrieve(moving);
        takeoff_wait += time - moving.started();
        num_takeoffs++;
        in_progress = Runway_activity::takeoff;
        takeoff.serve();
    }

    else
    {
        idle_time++;
        in_progress = idle;
    }
    return in_progress;
}

void Runway::shut_down (int time) const
/*
Post: Runway usage statistics are summarized and printed.
*/

{
    cout << "Simulation has concluded after " << time << " time units." << endl
         << "Total number of planes processed "
         << (num_land_requests + num_takeoff_requests) << endl
         << "Total number of planes asking to land "
         << num_land_requests << endl
         << "Total number of planes asking to take off "
         << num_takeoff_requests << endl
         << "Total number of planes accepted for landing "
         << num_land_accepted << endl
         << "Total number of planes accepted for takeoff "
         << num_takeoff_accepted << endl
         << "Total number of planes refused for landing "
         << num_land_refused << endl
         << "Total number of planes refused for takeoff "
         << num_takeoff_refused << endl
         << "Total number of planes that landed "
         << num_landings << endl
         << "Total number of planes that took off "
         << num_takeoffs << endl
         << "Total number of planes that crashed "
         << num_crashed << endl
         << "Total number of planes left in landing queue "
         << landing.size() << endl
         << "Total number of planes left in takeoff queue "
         << takeoff.size() << endl;
    cout << "Percentage of time runway idle "
         << 100.0 * ((float) idle_time) / ((float) time) << "%" << endl;
    cout << "Average wait in landing queue "
         << ((float) land_wait) / ((float) num_landings) << " time units";
    cout << endl << "Average wait in takeoff queue "
         << ((float) takeoff_wait) / ((float) num_takeoffs)
         << " time units" << endl;
    cout << "Average observed rate of planes wanting to land "
         << ((float) num_land_requests) / ((float) time)
         << " per time unit" << endl;
    cout << "Average observed rate of planes wanting to take off "
         << ((float) num_takeoff_requests) / ((float) time)
         << " per time unit" << endl;
}