#include "nbsimMassiveParticle.h"
#include <Eigen/Dense>
#include <cmath>
#include <iostream>

MassiveParticle::MassiveParticle()
{
  
}

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

void MassiveParticle::calculateEkinetic()
{
  double temp = 0;
#pragma omp parallel for reduction(+:temp)
  for(int i = 0; i < nbodyList_.size(); ++i)
  {
    auto vel = (nbodyList_[i]->getVelocity()).norm();
    temp += nbodyList_[i]->getMu() * std::pow(vel,2);
  }
  double ownKinetic =  Mu_ * std::pow(getVelocity().norm(),2);
  Ekinetic_ = 0.5 * (temp + ownKinetic);
}

void MassiveParticle::calculateEpotential()
{
  double temp = 0;
  double owntemp = 0;
  std::vector<std::shared_ptr<MassiveParticle>> tempList = nbodyList_;
  auto vel = getVelocity();
  auto pos = getPosition();
  std::shared_ptr<MassiveParticle> currentObj = std::make_shared<MassiveParticle>(getMu(),pos,vel);
  tempList.push_back(currentObj);
  
  for(int i = 0; i < tempList.size(); ++i)
  {
    for(int j = 0; j < tempList.size(); ++j)
    {
      if(i != j)
      {
        auto norm = (tempList[i]->getPosition() - tempList[j]->getPosition()).norm();
        auto MuMu = tempList[i]->getMu()*tempList[j]->getMu();
        if(norm == 0)
        {
          continue;
        }
        else
        {
          temp += MuMu/norm;
        }
      }
    }
  }
  Epotential_ = -0.5*temp;
}

double MassiveParticle::totalEnergy()
{
  calculateEkinetic();
  calculateEpotential();
  Etotal_ = Epotential_ + Ekinetic_;
  return Etotal_;
}

std::vector<std::shared_ptr<MassiveParticle>> MassiveParticle::getNobdyList()
{
  return nbodyList_;
}