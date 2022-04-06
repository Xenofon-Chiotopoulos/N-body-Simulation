#include <Eigen/Dense>
#include "nbsimParticle.h"

/*Standard class constructor*/
Particle::Particle()
{
  Eigen::Vector3d origin(0,0,0);
  position_ = origin;
  velocity_ = origin;
}

/*constructor that set the velocity and position*/
Particle::Particle(Eigen::Vector3d &position, Eigen::Vector3d &velocity)
{
  position_ = position;
  velocity_ = velocity;
}

/*base deconstructor*/
Particle::~Particle()
{

}

/*function that can change the postion of the particle*/
void Particle::setPosition(Eigen::Vector3d position)
{
  position_ = position;
}

/*Function that returns the postion */
Eigen::Vector3d Particle::getPosition()
{
  return position_;
}

/*function that can change the velocity*/
void Particle::setVelocity(Eigen::Vector3d velocity)
{
  velocity_ = velocity;
}

/*function that returns the velocity*/
Eigen::Vector3d Particle::getVelocity()
{
  return velocity_;
}

/*function that calcuates the new position and velocity given a time step and acceleration*/
void Particle::integrateTimestep(Eigen::Vector3d &acceleration, double timestep)
{
  
  position_ = position_ + velocity_ * timestep;
  velocity_ = velocity_ + acceleration * timestep;
}