/*=============================================================================

  PHAS0100ASSIGNMENT2: PHAS0100 Assignment 2 Gravitational N-body Simulation

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/


#include <nbsimMyFunctions.h>
#include <nbsimExceptionMacro.h>
#include <iostream>
#include "nbsimParticle.h"
#define _USE_MATH_DEFINES
#include <cmath>


// Example, header-only library, included in project for simplicity's sake.
#include <Eigen/Dense>
#include <unsupported/Eigen/NonLinearOptimization>

/**
 * \brief Demo file to check that includes and library linkage is correct.
 */
int main(int argc, char** argv)
{
  Eigen::Vector3d a(0,0,0);
  Eigen::Vector3d p(1,0,0);
  Eigen::Vector3d v(0,1,0);
  Particle p1(p,v);
  for(int i=0;i<=628318;i++){p1.integrateTimestep(a,0.00001);}
  
  
  Eigen::Vector3d testPos = p1.getPosition();
  Eigen::Vector3d testVel = p1.getVelocity();
  std::cout << testPos << "\n" <<testVel << std::endl;
  /*
  int returnStatus = EXIT_FAILURE;

  try
  {

    Eigen::MatrixXd m(2,2);
    std::cout << "Printing 2x2 Eigen::MatrixXd ..." << std::endl << m << std::endl;

    std::cout << "Calculating ... " << nbsim::MyFirstAddFunction(1, 2) << std::endl;

    returnStatus = EXIT_SUCCESS;
  }
  catch (nbsim::Exception& e)
  {
    std::cerr << "Caught nbsim::Exception: " << e.GetDescription() << std::endl;
  }
  catch (std::exception& e)
  {
    std::cerr << "Caught std::exception: " << e.what() << std::endl;
  }
  */
  return 0;
}
