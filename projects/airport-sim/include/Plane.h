#pragma once

#include <climits>

enum Plane_status
{
    null, arriving, departing
};

class Plane
{
public:
    Plane ();

    Plane (int flt, int time, Plane_status status, int fuel = INT_MAX); // default fuel to INT_MAX if not given as parameter

    void refuse () const;

    void land (int time) const;

    void fly (int time) const;

    void crash (int time) const;

    int started () const;

    int getFuelLevel () const
    {
        return fuel_level;
    }

private:
    int flt_num;
    int clock_start;
    int fuel_level;
    Plane_status state;
};