#include <Eigen/Dense>

class Particle{

  public:
  Particle();
  Particle(Eigen::Vector3d &position, Eigen::Vector3d &velocity);
  ~Particle();
  void setPosition(Eigen::Vector3d position);
  Eigen::Vector3d getPosition();
  void setVelocity(Eigen::Vector3d velocity);
  Eigen::Vector3d getVelocity();
  void integrateTimestep(Eigen::Vector3d &acceleration, double timestep);
  
  private:
  Eigen::Vector3d position_;
  Eigen::Vector3d velocity_;
};