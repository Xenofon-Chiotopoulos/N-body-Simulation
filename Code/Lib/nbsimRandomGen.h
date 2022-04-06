#include "nbsimMassiveParticle.h"
#include <memory>
#include <vector>

/* This class created objects of nbsimMassiveParticle which and randomly initialized 
to with a stable velocity and position and stores a list of those objects. To allow 
for stability there is one massive object at the start of the list and the following 
objects are significalty smaller*/
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