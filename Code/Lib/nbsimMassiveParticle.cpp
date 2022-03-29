#include "nbsimMassiveParticle.h"
#include <Eigen/Dense>
#include <cmath>

MassiveParticle::MassiveParticle(double Mu, Eigen::Vector3d &position, Eigen::Vector3d &velocity)
{
  Mu_ = Mu;

  Eigen::Vector3d a(0,0,0);
  acceleration_ = a;

  std::vector<std::shared_ptr<MassiveParticle>> v;
  nbodyList_ = v;

  setPosition(position);
  setVelocity(velocity);
}

MassiveParticle::~MassiveParticle()
{

}

double MassiveParticle::getMu()
{
    return Mu_;
}

void MassiveParticle::addAttractor(std::shared_ptr<MassiveParticle> const& hiAttractor)
{
  nbodyList_.push_back(std::move(hiAttractor));
}

void MassiveParticle::removeAttractor(std::shared_ptr<MassiveParticle> const& byeAttractor)
{
  nbodyList_.erase(std::remove(nbodyList_.begin(), nbodyList_.end(), byeAttractor), nbodyList_.end());
}

void MassiveParticle::calculateAcceleration()
{
  Eigen::Vector3d origin(0,0,0);
  acceleration_ = origin;
  for(int i = 0; i < nbodyList_.size(); ++i)
  {
    Eigen::Vector3d currentDif = getPosition() - nbodyList_[i]->getPosition();
    double currentDiffNorm = currentDif.norm();
    double currentMu = nbodyList_[i]->getMu();
    acceleration_ += -(currentMu/std::pow(currentDiffNorm,3))*currentDif; 
  }
}

void MassiveParticle::integrateTimestep(const double timestep)
{
  Particle::integrateTimestep(acceleration_, timestep);
}

double MassiveParticle::numberOfAttractors()
{
  return nbodyList_.size();
}

Eigen::Vector3d MassiveParticle::getacceleration()
{
  return acceleration_;
}