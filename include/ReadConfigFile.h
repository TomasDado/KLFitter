/*!
 * \class KLFitter::ReadConfigFile
 * \brief A class for reading a config file for runKLFitter files
 * \author Sven Ebert
 * \author Johannes Erdmann
 * \version 1.3
 * \date 23.04.2010
 *
 * This class reads a config file with running settings.
 */

// --------------------------------------------------------- 

#ifndef READCONFIGFILE
#define READCONFIGFILE

// --------------------------------------------------------- 

#include <string>

// --------------------------------------------------------- 

/*!
 * \namespace KLFitter
 * \brief The KLFitter namespace
 */
namespace KLFitter
{

  class ReadConfigFile
  {
                
  public: 
                
    /* @} */
    /** \name Constructors and destructors */ 
    /* @{ */ 
                
    /** 
     * The default constructor. 
     */ 
    ReadConfigFile(std::string filename); 
    //Second possible constructor.
    ReadConfigFile(std::string filename, bool * validconfig); 
                
    /**
     * The default destructor.
     */
    virtual ~ReadConfigFile(); 

    /* @} */
    /** \name Member functions (Get)  */
    /* @{ */

    /**
     * Return the DO_ELEcTRON flag
     * @return The flag.
     */ 
    bool GetDO_ELECTRON() { return DO_ELECTRON; }

    /**
     * Return the DO_MUON flag
     * @return The flag.
     */ 
    bool GetDO_MUON() { return DO_MUON; }

    /**
     * Return the DO_BATCH flag
     * @return The flag.
     */ 
    bool GetDO_BATCH() { return DO_BATCH; }

    /**
     * Return FlagBTagging
     * @return The flag.
     */ 
    bool GetFlagBTagging() { return FlagBTagging; }

    /**
     * Return FlagIntegrate
     * @return The flag.
     */ 
    bool GetFlagIntegrate() { return FlagIntegrate; }

    /**
     * Return FlagTopMassFixed
     * @return The flag.
     */ 
    bool GetFlagTopMassFixed() { return FlagTopMassFixed; }

    /**
     * Return FlagUseJetMass
     * @return The flag.
     */ 
    bool GetFlagUseJetMass() { return FlagUseJetMass; }

    /**
     * Return FlagIsSignalMC
     * @return The flag.
     */ 
    bool GetFlagIsSignalMC() { return FlagIsSignalMC; }

    /**
     * Return FlagIsSignalMC
     * @return The flag.
     */ 
    double GetTopMass() { return MassTop; }

    /**
     * Return input_path
     * @return The path.
     */
    std::string GetInputPath() { return input_path; }

    /**
     * Return output_path
     * @return The path.
     */
    std::string GetOutputPath() { return output_path; }

    /**
     * Return IsBkg
     * @return The flag.
     */
    bool GetIsBkg() { return IsBkg; }

  private: 

    int ReadConfig(std::string filename);
    int GetTrueOrFalse(std::string line, size_t found);
    int GetValue(double * ret, std::string line, size_t found);
    int GetPath(std::string * ret, std::string line, size_t found);
    bool IsNumber(std::string::iterator a, int * number);
    bool CheckIOPath();

    /**
     * The DO_ELECTRON flag.
     */ 
    bool DO_ELECTRON;

    /**
     * The DO_MUON flag.
     */ 
    bool DO_MUON;

    /**
     * The DO_BATCH flag.
     */ 
    bool DO_BATCH;

    /**
     * The FlagBTagging.
     */ 
    bool FlagBTagging;

    /**
     * The FlagIntegrate.
     */ 
    bool FlagIntegrate;

    /**
     * The FlagTopMassFixed.
     */ 
    bool FlagTopMassFixed;

    /**
     * The FlagUseJetMass.
     */ 
    bool FlagUseJetMass;

    /**
     * The FlagIsSignalMC.
     */ 
    bool FlagIsSignalMC;

    /**
     * The top mass.
     */ 
    double MassTop;
    /**
     * Path of the inputfile.
     */ 
    std::string input_path;

    /**
     * Path of the outputfile.
     */ 
    std::string output_path;

    /**
     * For background (w/o truth info!)
     */ 
    bool IsBkg;

  }; 

} // namespace KLFitter 

// --------------------------------------------------------- 

#endif 
