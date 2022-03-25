#include "nbsimParticle.h"
#include <memory>

class MassiveParticle :public Particle{
    public:
    MassiveParticle();
    ~MassiveParticle();
    void setMu(double Mu);
    double getMu();
    void addAttractor(std::shared_ptr<MassiveParticle> &hiAttractor);
    void removeAttractor(std::shared_ptr<MassiveParticle> &byeAttractor);
    void calculateAcceleration();
    void integrateTimestep(const double timestep);

    private:
    double Mu_;
    Eigen::Vector3d acceleration;

};