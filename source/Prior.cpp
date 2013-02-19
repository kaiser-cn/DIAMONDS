#include "Prior.h"

// Prior::Prior()
//
// PURPOSE:
//      Abstract base class constructor. Sets the dimensions
//      of the parameter space.
//
// INPUT:
//      Ndim : integer containing the number of dimensions, i.e.
//      the number of free parameters of the problem.
//

Prior::Prior(const int Ndimensions, const int Nobjects)
: Ndimensions(Ndimensions), 
  Nobjects(Nobjects)
{

} // END Prior::Prior()







// Prior::~Prior()
//
// PURPOSE:
//      Abstract base class destructor. 
//

Prior::~Prior()
{

} // END Prior::~Prior()







// Prior::getNdimensions()
//
// PURPOSE: 
//      Get function to obtain the protected data member Ndimensions.
//
// OUTPUT:
//      An integer containing the number of dimensions of the parameter space.
//

int Prior::getNdimensions()
{
    return Ndimensions;
} // END Prior::getNdimensions()







// Prior::getNobjects()
//
// PURPOSE: 
//      Get function to obtained the protected data member Nobjects.
//
// OUTPUT:
//      An integer containing the number of nested objects used (i.e.
//      the number of allowed values for each free parameter).
//

int Prior::getNobjects()
{
    return Nobjects;
} // END Prior::getNobjects()