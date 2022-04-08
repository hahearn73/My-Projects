/*
 * Implementation of the City class.
 * A City instance has a name and a list of neighboring City names (strings)
 */
#include <iostream>
#include "City.h"

City::City()
{
    name = "";  // A peculiar name for a city!
}

City::City(std::string n)
{
    name = n;
}

City::~City()
{
    //Nothing to do
}

std::vector<std::string> City::get_neighbors()
{
    return neighbors;
}

bool City::operator==(const City &rhs) const
{
    return this->name == rhs.name;
}

bool City::operator!=(const City &rhs) const
{
    return this->name != rhs.name;
}


int City::get_num_neighbors()
{
    return neighbors.size();
}
        
std::string City::get_name()
{
    return name;
}

void City::add_neighbor(std::string city)
{
    neighbors.push_back(city);
}


