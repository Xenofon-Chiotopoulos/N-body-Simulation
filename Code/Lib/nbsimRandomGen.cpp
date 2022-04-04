#include "nbsimRandomGen.h"
#include <memory>
#include <random>
#include <cmath>
#include <iostream>
#include <Eigen/Dense>

RandomGen::RandomGen()
{

}

RandomGen::~RandomGen()
{
  
}

RandomGen::RandomGen(int num)
{
  Eigen::Vector3d origin(0,0,0);
  std::shared_ptr<MassiveParticle> centerParticle = std::make_shared<MassiveParticle>(1.0, origin, origin);
  particleList_.push_back(centerParticle);

  for(int i = 1; i < num; i++)
  {
    double rX, rY, vX, vY;
    double radius = randomRadius();
    double theta = randomTheta();
    rX = radius * std::sin(theta);
    rY = radius * std::cos(theta);
    vX = -std::cos(theta)/std::sqrt(radius);
    vY = std::sin(theta)/std::sqrt(radius);
    //std::cout << "rX: " << radius << '\n' << "-------------------------" << std::endl;
    //std::cout << "rY: " << theta << '\n' << "-------------------------" << std::endl;
    //std::cout << "vX: " << rX << '\n' << "-------------------------" << std::endl;
    //std::cout << "rY: " << rX << '\n' << "-------------------------" << std::endl;
    Eigen::Vector3d pos(rX,rY,0.0);
    Eigen::Vector3d vel(vX,vY,0.0); 

    std::shared_ptr<MassiveParticle> particle = std::make_shared<MassiveParticle>(0.00001, pos, vel);
    particleList_.push_back(particle);
  }
}

double RandomGen::randomRadius()
{
  std::random_device rd; 
  std::mt19937 e2(rd()); 
  std::uniform_real_distribution<> randiusDist(0.4, 40);
  double radius = randiusDist(e2); 
  return radius;
}

double RandomGen::randomTheta()
{
  std::random_device rd; 
  std::mt19937 e2(rd()); 
  std::uniform_real_distribution<> thetaDist(0, 1);
  double theta = thetaDist(e2); 
  return theta * 2 * M_PI;
}

std::vector<std::shared_ptr<MassiveParticle>> RandomGen::getList()
{
  return particleList_;
}