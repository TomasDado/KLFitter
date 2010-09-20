#include "ResGauss.h" 
#include <TMath.h>
#include <iostream>

// --------------------------------------------------------- 
KLFitter::ResGauss::ResGauss(const char * filename) : KLFitter::ResolutionBase(1)
{
  // read parameters from file 
  ReadParameters(filename, 1); 
}

// --------------------------------------------------------- 
KLFitter::ResGauss::ResGauss(double sigma) : KLFitter::ResolutionBase(1)
{
  // set parameter
  SetPar(0, sigma);
}

// --------------------------------------------------------- 
KLFitter::ResGauss::~ResGauss()
{

}

// --------------------------------------------------------- 
double KLFitter::ResGauss::p(double x, double xmeas)
{
  return TMath::Gaus(xmeas, x, fParameters.at(0), true); 
}

// --------------------------------------------------------- 

