#include "nbsimMassiveParticle.h"
#include <Eigen/Dense>
#include <cmath>
#include <iostream>
#include <omp.h>
#include <vector>

/*base constructor*/
MassiveParticle::MassiveParticle()
{
  
}

/*constructor that takes a value for Mu position and velocity*/
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

/*base deconstructor*/
MassiveParticle::~MassiveParticle()
{

}

/*function that returns value of mu*/
double MassiveParticle::getMu()
{
    return Mu_;
}

/*function that adds an object to a vector storing the objects in the system*/
void MassiveParticle::addAttractor(std::shared_ptr<MassiveParticle> const& hiAttractor)
{
  nbodyList_.push_back(std::move(hiAttractor));
}

/*function that removes an object from nbodylist_ private member function*/
void MassiveParticle::removeAttractor(std::shared_ptr<MassiveParticle> const& byeAttractor)
{
  nbodyList_.erase(std::remove(nbodyList_.begin(), nbodyList_.end(), byeAttractor), nbodyList_.end());
}

/*function that calculates the acceleration using the velocity and position of the other objects in 
nbodylist_*/
void MassiveParticle::calculateAcceleration()
{
  Eigen::Vector3d origin(0,0,0);
  acceleration_ = origin;
  std::vector<Eigen::Vector3d> currentDiff;
  std::vector<double> currentDiffNorm;
  std::vector<double> currentMu;

  for(int i = 0; i < nbodyList_.size(); ++i)
  {
    currentDiff.push_back(getPosition() - nbodyList_[i]->getPosition());
    currentDiffNorm.push_back(currentDiff[i].norm());
    currentMu.push_back(nbodyList_[i]->getMu());
  }
  for(int i = 0; i < nbodyList_.size(); ++i)
  {
    acceleration_ += -(currentMu[i]/std::pow(currentDiffNorm[i],3))*currentDiff[i]; 
  }
}

/*function that calles the parent class integration timestep but with the acceleration 
private member function created in this class*/
void MassiveParticle::integrateTimestep(const double timestep)
{
  Particle::integrateTimestep(acceleration_, timestep);
}

/*returns the number of objects in nbodylist_*/
double MassiveParticle::numberOfAttractors()
{
  return nbodyList_.size();
}

/*retruns the currnt acceleration of the system*/
Eigen::Vector3d MassiveParticle::getacceleration()
{
  return acceleration_;
}

/*calculates the current kinetic energy of all the objects in nobodylist_ 
and the current object as well*/
void MassiveParticle::calculateEkinetic()
{
  double temp = 0;
  #pragma omp parallel for reduction(+:temp) schedule(static) collapse(1)
  for(int i = 0; i < nbodyList_.size(); ++i)
  {
    auto vel = (nbodyList_[i]->getVelocity()).norm();
    temp += nbodyList_[i]->getMu() * std::pow(vel,2);
  }
  #pragma omp nowait
  double ownKinetic =  Mu_ * std::pow(getVelocity().norm(),2);
  Ekinetic_ = 0.5 * (temp + ownKinetic);
}

/*calculates the current potential energy of all the objects in nobodylist_ 
and the current object as well*/
void MassiveParticle::calculateEpotential()
{
  double temp = 0;
  double owntemp = 0;
  std::vector<std::shared_ptr<MassiveParticle>> tempList = nbodyList_;
  auto vel = getVelocity();
  auto pos = getPosition();
  std::shared_ptr<MassiveParticle> currentObj = std::make_shared<MassiveParticle>(getMu(),pos,vel);
  tempList.push_back(currentObj);

  #pragma omp parallel for collapse(2) schedule(static) reduction(+:temp) 
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

/* function that returns the total energy of all the objects in the system, 
these being the obj in nbodylist_ and the current object*/
double MassiveParticle::totalEnergy()
{
  calculateEkinetic();
  calculateEpotential();
  Etotal_ = Epotential_ + Ekinetic_;
  return Etotal_;
}

/*fucntion that returns nbodylist_*/
std::vector<std::shared_ptr<MassiveParticle>> MassiveParticle::getNobdyList()
{
  return nbodyList_;
}