/*!
 * \class KLFitter::ResGauss
 * \brief A class describing a Gaussian resolution. 
 * \author Kevin Kr&ouml;ninger
 * \version 1.3
 * \date 03.12.2009
 *
 * This class offers a simple parameterization of a resolution. The
 * parameterization is a Gaussian with a width of a constant times the
 * square root of the true parameter.
 */

// --------------------------------------------------------- 

#ifndef RESGAUSS
#define RESGAUSS

#include "ResolutionBase.h" 

// --------------------------------------------------------- 

/*!
 * \namespace KLFitter
 * \brief The KLFitter namespace
 */
namespace KLFitter
{

  class ResGauss : public ResolutionBase
  {
                
  public: 
                
    /** \name Constructors and destructors */ 
    /* @{ */ 
                
    /** 
     * The default constructor. 
     */ 
    ResGauss(const char * filename); 

    /** 
     * A constructor. 
     * @param sigma The width of the Gaussian.
     */ 
    ResGauss(double sigma); 
                
    /**
     * The default destructor.
     */
    virtual ~ResGauss(); 

    /* @} */
    /** \name Member functions (Get)  */
    /* @{ */

    /**
     * Return the probability of the true value of x given the
     * measured value, xmeas.
     * @param x The true value of x.
     * @param xmeas The measured value of x.
     * @return The probability. 
     */ 
    double p(double x, double xmeas); 

    /* @} */
    /** \name Member functions (Set)  */
    /* @{ */

    /**
     * Set the width of the Gaussian 
     * @param sigma The width of the Gaussian. 
     */ 
    void SetSigma(double sigma)
    { if (sigma < 0) sigma = - sigma; this -> SetPar(0, sigma); }; 

    /* @} */

  private: 

  }; 
        
} // namespace KLFitter 

// --------------------------------------------------------- 

#endif 

