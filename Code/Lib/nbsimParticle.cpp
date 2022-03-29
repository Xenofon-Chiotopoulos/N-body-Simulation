#include <Eigen/Dense>
#include "nbsimParticle.h"

Particle::Particle()
{
  Eigen::Vector3d origin(0,0,0);
  position_ = origin;
  velocity_ = origin;
}

Particle::Particle(Eigen::Vector3d &position, Eigen::Vector3d &velocity)
{
  position_ = position;
  velocity_ = velocity;
}

Particle::~Particle()
{

}


void Particle::setPosition(Eigen::Vector3d position)
{
  position_ = position;
}

Eigen::Vector3d Particle::getPosition()
{
  return position_;
}

void Particle::setVelocity(Eigen::Vector3d velocity)
{
  velocity_ = velocity;
}

Eigen::Vector3d Particle::getVelocity()
{
  return velocity_;
}

void Particle::integrateTimestep(Eigen::Vector3d &acceleration, double timestep)
{
  
  position_ = position_ + velocity_ * timestep;
  velocity_ = velocity_ + acceleration * timestep;
}