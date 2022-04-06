#include "nbsimParticle.h"
#include <memory>
/*Massive pariticle class that inherites from the particle class and includes added functions 
that can calculate acceleration due to other bodies and store a list of bodies in the system*/
class MassiveParticle :public Particle
{
  public:
  MassiveParticle();
  MassiveParticle(double Mu, Eigen::Vector3d &position, Eigen::Vector3d &velocity);
  ~MassiveParticle();
  void setMu(double Mu);
  double getMu();
  void addAttractor(std::shared_ptr<MassiveParticle> const& hiAttractor);
  void removeAttractor(std::shared_ptr<MassiveParticle> const& byeAttractor);
  void calculateAcceleration();
  void integrateTimestep(const double timestep);
  double numberOfAttractors();
  Eigen::Vector3d getacceleration();
  void calculateEkinetic();
  void calculateEpotential();
  double totalEnergy();
  std::vector<std::shared_ptr<MassiveParticle>> getNobdyList();

  private:
  double Mu_;
  Eigen::Vector3d acceleration_;
  std::vector<std::shared_ptr<MassiveParticle>> nbodyList_;
  double Ekinetic_;
  double Epotential_;
  double Etotal_;
};