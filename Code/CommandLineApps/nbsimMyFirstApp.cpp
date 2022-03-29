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
#include "nbsimMassiveParticle.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <memory>

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
  Eigen::Vector3d v(0,0.5,0);

  Eigen::Vector3d p_1(-1,0,0);
  Eigen::Vector3d v_1(0,-0.5,0);

  //Particle p1(p,v);
  //for(int i=0;i<=628318;i++){Eigen::Vector3d new_p = p1.getPosition(); a = -new_p; p1.integrateTimestep(a,0.00001);}
  
  //Eigen::Vector3d testPos = p1.getPosition();
  //Eigen::Vector3d testVel = p1.getVelocity();
  //std::cout << testPos << "\n" <<testVel << std::endl;

  std::shared_ptr<MassiveParticle> mp1 = std::make_shared<MassiveParticle>(1.0,p,v);
  std::shared_ptr<MassiveParticle> mp2 = std::make_shared<MassiveParticle>(1.0,p_1,v_1);
  std::shared_ptr<MassiveParticle> mp3 = std::make_shared<MassiveParticle>(1.0,p,v);

  mp1->addAttractor(mp2);
  mp2->addAttractor(mp1);

  for(int i=0;i<=628318;i++)
  {
    mp1->calculateAcceleration();
    mp2->calculateAcceleration();
    mp1->integrateTimestep(0.00001);
    mp2->integrateTimestep(0.00001);
  }

  Eigen::Vector3d testPos1 = mp1->getPosition();
  Eigen::Vector3d testPos2 = mp2->getPosition();
  Eigen::Vector3d testVel1 = mp1->getVelocity();
  Eigen::Vector3d testVel2 = mp2->getVelocity();
  std::cout << "MP1" << '\n' << testPos1 << '\n' << testVel1 << '\n' << std::endl;
  std::cout << "MP2" << '\n' << testPos2 << '\n' << testVel2 << '\n' << std::endl;
  //Eigen::Vector3d testMu = mp1->getacceleration();
  //std::cout << testMu << std::endl;

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
