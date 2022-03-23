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

Eigen::Vector3d Particle::getPosition()
{
    return position_;
}

Eigen::Vector3d Particle::getVelocity()
{
    return velocity_;
}

void Particle::integrateTimestep(Eigen::Vector3d &acceleration, double timestep)
{
    velocity_ = velocity_ + acceleration * timestep;
    position_ = position_ + velocity_ * timestep;
    
}