#include "nbsimMassiveParticle.h"
#include <memory>
#include <vector>

class RandomGen
{
    public:
    RandomGen();
    ~RandomGen();
    RandomGen(int number);
    double randomRadius();
    double randomTheta();
    std::vector<std::shared_ptr<MassiveParticle>> getList();

    private:
    std::vector<std::shared_ptr<MassiveParticle>> particleList_;
};