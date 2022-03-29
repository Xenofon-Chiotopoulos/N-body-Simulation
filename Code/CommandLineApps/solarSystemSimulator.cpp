#include <nbsimMyFunctions.h>
#include <nbsimExceptionMacro.h>
#include <iostream>
#include "nbsimMassiveParticle.h"
#include "nbsimSolarSystemData.ipp"

#define _USE_MATH_DEFINES
#include <cmath>
#include <memory>
#include <Eigen/Dense>
#include <unsupported/Eigen/NonLinearOptimization>
#include <map>
#include <cstdlib>

static void show_usage(std::string name)
{
    std::cerr << "Usage Guide for: " << name << "\n" 
              << "This app has two input options\n"
              << "1: Input the step size as an integer \n"
              << "2: Input the time length as an integer \n"
              << std::endl;
}

int main(int argc, char** argv)
{
  for(int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if((arg == "-h") || (arg == "--help"))
        {
            show_usage(argv[0]);
            return 0;
        }
    }

  if(argc == 3)
  {
    long double stepSize = std::atof(argv[1]);
    long double timeLength = std::atof(argv[2]);
    long double timeSteps = timeLength/stepSize;
    std::cout << "Time length is  " << timeLength << '\n' << "Step size is  " << stepSize << '\n' << "iterations number  " << timeSteps << std::endl;

    int ibody = 3;
    std::cout << nbsim::solarSystemData.at(ibody).name << std::endl;
    std::cout << nbsim::solarSystemData.at(ibody).position << std::endl;

    std::map<std::string, std::shared_ptr<MassiveParticle>> map; 
    for(int ibody = 0; ibody < 9; ibody++)
    {
      auto planetName = nbsim::solarSystemData.at(ibody).name;
      std::shared_ptr<MassiveParticle> mp = std::make_shared<MassiveParticle>(nbsim::solarSystemData.at(ibody).mu,nbsim::solarSystemData.at(ibody).position,nbsim::solarSystemData.at(ibody).velocity);
      map[planetName] = mp;
    } 
    for(auto const& [key, val] : map)
    {
      for(auto const& [keyI, valI] : map)
      {
        if(key != keyI)
        {
          val->addAttractor(valI);
        }
      }
    }
    for(int i=0;i<=3650;i++)
    {
      for(auto const& [key, val] : map)
      {
        val->calculateAcceleration();
      }
      for(auto const& [key, val] : map)
      {
        val->integrateTimestep(0.000274);
      }
    }
    for(auto const& [key, val] : map)
    {
      auto pos = val->getPosition();
      std::cout << key << '\n' << "  " << pos << "\n" << std::endl;
    }
  }

  if(argc != 3)
    {
        std::cout << "Wrong number of inputs provided" << std::endl;
        show_usage(argv[0]);
        return 0;
    }
    return 0;

  return 0;
}