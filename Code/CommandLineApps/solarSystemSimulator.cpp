#include <nbsimMyFunctions.h>
#include <nbsimExceptionMacro.h>
#include <iostream>
#include "nbsimRandomGen.cpp"

#include "nbsimSolarSystemData.ipp"

#define _USE_MATH_DEFINES
#include <cmath>
#include <memory>
#include <Eigen/Dense>
#include <unsupported/Eigen/NonLinearOptimization>
#include <map>
#include <cstdlib>
#include <ctime>
#include <chrono>

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
    int iterations = timeLength/stepSize;
    std::cout << "Time length is  " << timeLength << '\n' << "Step size is  " << stepSize << '\n' << "iterations number  " << iterations << std::endl;

    int ibody = 3;
    std::cout << nbsim::solarSystemData.at(ibody).name << std::endl;
    std::cout << nbsim::solarSystemData.at(ibody).position << std::endl;

    std::map<std::string, std::shared_ptr<MassiveParticle>> map; 
    for(int ibody = 0; ibody < 9; ibody++)
    {
      auto planetName = nbsim::solarSystemData.at(ibody).name;
      std::shared_ptr<MassiveParticle> mp = std::make_shared<MassiveParticle>(nbsim::solarSystemData.at(ibody).mu, nbsim::solarSystemData.at(ibody).position, nbsim::solarSystemData.at(ibody).velocity);
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

    /*
    for(auto const& [key, val] : map)
    {
      std::vector<std::shared_ptr<MassiveParticle>> vec = val->getNobdyList();
      std::cout << "obj size of " << key << " is: " << vec.size() << '\n' << std::endl;
    }
    */

    auto energy1 = map["Earth"]->totalEnergy();
    std::clock_t c_start = std::clock();
    auto t_start = std::chrono::high_resolution_clock::now();


    for(int i=0;i<=iterations;i++)
    {
      for(auto const& [key, val] : map)
      {
        val->calculateAcceleration();
      }
      for(auto const& [key, val] : map)
      {
        val->integrateTimestep(stepSize);
      }
    }

    std::clock_t c_end = std::clock();
    auto t_end = std::chrono::high_resolution_clock::now();

    std::vector<double> energiesFinal;
    std::vector<std::string> names;
    for(auto const& [key, val] : map)
    {
      auto energy = map[key]->totalEnergy();
      energiesFinal.push_back(energy);
      names.push_back(key);
    }

    auto energy = map["Earth"]->totalEnergy();
    std::cout << "Initial total energy is  " << energy1 << '\n' << std::endl;
    std::cout << "Final total energy is  " << energy << '\n' << std::endl;
    std::cout << "Total error  " << 100*abs(energy1 - energy)/abs(energy1) << "%" << '\n' << std::endl;
    std::cout << "Total time taken is  " << 1000*(c_end - c_start)/CLOCKS_PER_SEC << " ms" << '\n' << std::endl;
    std::cout << "Total wall time taken " << std::chrono::duration<double, std::milli>(t_end - t_start).count() << " ms" <<  '\n' << std::endl;
  }

  
  if(argc = 4)
  {
    long double stepSize = std::atof(argv[1]);
    long double timeLength = std::atof(argv[2]);
    int numberOfParticles = std::atof(argv[3]);
    int iterations = timeLength/stepSize;
    RandomGen Obj(numberOfParticles);
    std::vector<std::shared_ptr<MassiveParticle>> particleList = Obj.getList();

    for(int i = 0; i < particleList.size(); i++)
    {
      for(int j = 0; j < particleList.size(); j++)
      {
        if(i != j)
        {
          particleList[i]->addAttractor(particleList[j]);
        }
      }
    }

    auto energy1 = particleList[1]->totalEnergy();
    std::clock_t c_start = std::clock();
    auto t_start = std::chrono::high_resolution_clock::now();
    for(int i=0;i<=iterations;i++)
    {
      for(int i = 0; i < particleList.size(); i++)
      {
        particleList[i]->calculateAcceleration();
      }
      for(int i = 0; i < particleList.size(); i++)
      {
        particleList[i]->integrateTimestep(stepSize);
      }
    }
    std::clock_t c_end = std::clock();
    auto t_end = std::chrono::high_resolution_clock::now();
    auto energy = particleList[1]->totalEnergy();

    std::cout << "Initial total energy is  " << energy1 << '\n' << std::endl;
    std::cout << "Final total energy is  " << energy << '\n' << std::endl;
    std::cout << "Total error  " << 100*abs(energy1 - energy)/abs(energy1) << "%" << '\n' << std::endl;
    std::cout << "Total time taken is  " << 1000*(c_end - c_start)/CLOCKS_PER_SEC << " ms" << '\n' << std::endl;
    std::cout << "Total wall time taken " << std::chrono::duration<double, std::milli>(t_end - t_start).count() << " ms" <<  '\n' << std::endl;
  }

  if(argc != 3 && argc != 4)
    {
        std::cout << "Wrong number of inputs provided" << std::endl;
        show_usage(argv[0]);
        return 0;
    }
    return 0;

  return 0;
}