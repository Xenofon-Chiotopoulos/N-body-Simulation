/*=============================================================================

  PHAS0100ASSIGNMENT2: PHAS0100 Assignment 2 Gravitational N-body Simulation

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "catch.hpp"
#include "nbsimCatchMain.h"
#include "nbsimMyFunctions.h"
#include "nbsimRandomGen.h"
#include <iostream>
#include <vector>
#include <Eigen/Dense>

TEST_CASE( "Zero acceleration test", "[Particle class]" ) {
  Eigen::Vector3d a(0,0,0);
  Eigen::Vector3d p(1,0,0);
  Eigen::Vector3d v(1,0,0);

  std::shared_ptr<Particle> p1 = std::make_shared<Particle>(p,v);

  p1->integrateTimestep(a,1);

  Eigen::Vector3d p2(2,0,0);

  REQUIRE( p1->getVelocity() == v );
  REQUIRE( p1->getPosition() == p2);
}

TEST_CASE( "Acceleration constant", "[Particle class]" ) {
  Eigen::Vector3d a(1,0,0);
  Eigen::Vector3d p(1,0,0);
  Eigen::Vector3d v(1,0,0);

  std::shared_ptr<Particle> p1 = std::make_shared<Particle>(p,v);

  p1->integrateTimestep(a,1);

  Eigen::Vector3d v2(2,0,0);
  Eigen::Vector3d p2(2,0,0);

  REQUIRE( p1->getVelocity() == v2);
  REQUIRE( p1->getPosition() == p2);

  p1->integrateTimestep(a,1);

  Eigen::Vector3d v3(3,0,0);
  Eigen::Vector3d p3(4,0,0);

  REQUIRE( p1->getVelocity() == v3);
  REQUIRE( p1->getPosition() == p3);
}

TEST_CASE( "centripital acceleration", "[Particle class]") {
  Eigen::Vector3d p(1,0,0);
  Eigen::Vector3d v(1,0,0);
  Particle p1(p,v);
  for(int i=0;i<=628318;i++){
    Eigen::Vector3d new_p = p1.getPosition(); 
    Eigen::Vector3d a = -new_p;
     p1.integrateTimestep(a,0.00001);
    }
  Eigen::Vector3d testPos = p1.getPosition();
  Eigen::Vector3d testVel = p1.getVelocity();
  
  REQUIRE( p.isApprox(testPos, 0.0001));
  REQUIRE( v.isApprox(testVel, 0.0001));
}

TEST_CASE( "Linear motion", "[MassiveParticle class]") {
  Eigen::Vector3d p(1,0,0);
  Eigen::Vector3d v(1,0,0);
  MassiveParticle p1(1,p,v);
  
  p1.integrateTimestep(1);

  Eigen::Vector3d testPos = p1.getPosition();
  Eigen::Vector3d testVel = p1.getVelocity();

  Eigen::Vector3d p2(2,0,0);
  
  REQUIRE( p2 == testPos);
  REQUIRE( testVel == v);
}

TEST_CASE( "Orbital motion", "[MassiveParticle class]") {
  Eigen::Vector3d p(1,0,0);
  Eigen::Vector3d v(0,0.5,0);
  Eigen::Vector3d p_1(-1,0,0);
  Eigen::Vector3d v_1(0,-0.5,0);

  std::shared_ptr<MassiveParticle> mp1 = std::make_shared<MassiveParticle>(1.0,p,v);
  std::shared_ptr<MassiveParticle> mp2 = std::make_shared<MassiveParticle>(1.0,p_1,v_1);
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
  
  REQUIRE( testPos1[0] - testPos2[0] == 2);
}