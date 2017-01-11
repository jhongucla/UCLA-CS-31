#include <iostream>
#include <cassert>
#include "grid.h"
#include <cctype>
using namespace std;

bool isRouteWellFormed(string route);
int navigateSegment(int r, int c, char dir, int maxSteps);
int navigateRoute(int sr, int sc, int er, int ec, string route, int& nsteps);
bool processSegment(int& r, int& c, int& pos, string route, int& nsteps);

bool isRouteWellFormed(string route)
{
    if (isdigit(route[0])) // a route starting with a digit is not well formed
        return false;
    for (int i = 0; i < route.size(); i++)
    {
        if (tolower(route[i]) == 'n' || tolower(route[i]) == 'e' || tolower(route[i]) == 's' || tolower(route[i]) == 'w') // continues if character is a direction
            continue;
        else if (isdigit(route[i]))
        {
            if (i + 1 < route.size() && isdigit(route[i+1]) && isdigit(route[i-1])) // there cannot be three digits in a row
                return false;
            continue;
        }
        return false; // character is not a direction or a digit, so route is not well formed
    }
    return true;
}

int navigateSegment(int r, int c, char dir, int maxSteps)
{
    int steps = 0; // creates variable to count steps
    if (r <= 0 || r > getRows() || c <= 0 || c > getCols() || isWall(r, c) || maxSteps < 0) // checks validity of grid position and maxSteps
        return -1;
    if (!isalpha(dir)) // checks if direction is a letter
        return -1;
    else if (tolower(dir) != 'n' && tolower(dir) != 's' && tolower(dir) != 'w' && tolower(dir) != 'e') // checks if direction is correct
        return -1;
    switch (tolower(dir)) // computes steps based on direction
    {
        case 'n':
        {
            while (r > 0 && !isWall(r, c))
            {
                r--;
                steps++;
            }
            break;
        }
        case 's':
        {
            while (r <= getRows() && !isWall(r, c))
            {
                r++;
                steps++;
            }
            break;
        }
        case 'w':
        {
            while (c > 0 && !isWall(r, c))
            {
                c--;
                steps++;
            }
            break;
        }
        case 'e':
        {
            while (c <= getCols() && !isWall(r, c))
            {
                c++;
                steps++;
            }
            break;
        }
    }
    if (steps - 1 < maxSteps) // returns steps
        return steps - 1;
    else
        return maxSteps;
}

int navigateRoute(int sr, int sc, int er, int ec, string route, int& nsteps)
{
    int r = sr;
    int c = sc;
    int pos = 0;
    if (sr <= 0 || er <= 0 || sr > getRows() || er > getRows() || sc <= 0 || ec <= 0 || sc > getCols() || ec > getCols() || isWall(sr, sc) || isWall(er, ec) || !isRouteWellFormed(route)) // checks if grid positions and route are valid
        return 2;
    nsteps = 0;
    while (pos < route.size()) // loops through route
    {
        if (isalpha(route[pos])) // processes each route segment
        {
            if (!processSegment(r, c, pos, route, nsteps))
                return 3;
        }
        else
            pos++;
    }
    if (r == er && c == ec) // compares position at end of route with end position given
        return 0;
    return 1;
}

bool processSegment(int& r, int& c, int& pos, string route, int& nsteps)
{
    int distance = 0;
    if (isdigit(route[pos+1]))
    {
        if (isdigit(route[pos+2]))
            distance = 10 * (route[pos+1] - '0') + (route[pos+2] - '0'); // computes distance if two digits follow direction
        else
            distance = route[pos+1] - '0'; // computes distance if one digit follows direction
    }
    else
        distance = 1; // if no digits follow direction, distance is 1
    int stepsTaken = navigateSegment(r, c, route[pos], distance);
    if (stepsTaken != distance) // when the robot hits a wall or goes off the grid
    {
        nsteps += stepsTaken; // nsteps is updated and the function returns false to indicate error
        return false;
    }
    else
    {
        switch (tolower(route[pos])) // based on direction, the robot's current position is updated and nsteps is accumulated
        {
            case 'n':
            {
                r -= distance;
                nsteps += distance;
                break;
            }
            case 's':
            {
                r += distance;
                nsteps += distance;
                break;
            }
            case 'e':
            {
                c += distance;
                nsteps += distance;
                break;
            }
            case 'w':
            {
                c -= distance;
                nsteps += distance;
                break;
            }
        }
    }
    pos++;
    return true; // the route segment is processed without error
}

int main()
{
    setSize(5,5);
    setWall(3,4);
    setWall(1,2);
    setWall(4,1);
    setWall(5,4);
    setWall(2,4);
    setWall(3,3);
    int len = -999;
    assert(isRouteWellFormed(""));
    assert(isRouteWellFormed("n"));
    assert(isRouteWellFormed("n"));
    assert(isRouteWellFormed("n1"));
    assert(isRouteWellFormed("n12"));
    assert(isRouteWellFormed("n12e3"));
    assert(isRouteWellFormed("N12e3"));
    assert(isRouteWellFormed("N12Ew3"));
    assert(isRouteWellFormed("N12ENw"));
    assert(!isRouteWellFormed("e1x"));
    assert(!isRouteWellFormed("3S"));
    assert(!isRouteWellFormed("x12"));
    assert(!isRouteWellFormed("N150"));
    assert(!isRouteWellFormed("e4+e7"));
    assert(navigateSegment(1, 5, 'S', 4) == 4);
    assert(navigateSegment(2, 2, 's', 4) == 3);
    assert(navigateSegment(3, 2, 'E', 4) == 0);
    assert(navigateSegment(4, 4, 'w', 2) == 2);
    assert(navigateSegment(3, 4, 'w', 2) == -1);
    assert(navigateSegment(1, 1, 'x', 1) == -1);
    assert(navigateRoute(1, 3, 5, 5, "s01W2s1Ese3S", len) == 0 && len == 10);
    len = -999;
    assert(navigateRoute(1, 3, 5, 5, "s01W2s1Ese3", len) == 1 && len == 9);
    len = -999;
    assert(navigateRoute(1, 3, 5, 5, "3sw", len) == 2 && len == -999);
    len = -999;
    assert(navigateRoute(1, 3, 5, 5, "s01W2s1E2", len) == 3 && len == 5);
    len = -999;
    assert(navigateRoute(1, 3, 5, 5, "s01W2s1W", len) == 3 && len == 4);
    setSize(3,4);
    setWall(1,4);
    setWall(2,2);
    setWall(3,2);
    assert(isRouteWellFormed("n2e1"));
    assert(!isRouteWellFormed("e1x"));
    assert(navigateSegment(3, 1, 'N', 2) == 2);
    len = -999;  // so we can detect whether navigateRoute sets len
    assert(navigateRoute(3,1, 3,4, "N2eE01n0s2e1", len) == 0  &&  len == 7);
    len = -999;  // so we can detect whether navigateRoute sets len
    assert(navigateRoute(3,1, 3,4, "e1x", len) == 2  &&  len == -999);
    len = -999;  // so we can detect whether navigateRoute sets len
    assert(navigateRoute(2,4, 1,1, "w3n1", len) == 3  &&  len == 1);
    cout << "All tests succeeded" << endl;
}
