#include "ReadConfigFile.h" 
#include <iostream> 
#include <cmath>
#include <fstream>
#include <TSystem.h>  

// --------------------------------------------------------- 
KLFitter::ReadConfigFile::ReadConfigFile(std::string filename)
{
  DO_ELECTRON = true;
  DO_MUON     = false;
  DO_BATCH    = false;

  FlagBTagging     = false;
  CutBTagging      = 1.e4;
  FlagIntegrate    = false;
  FlagTopMassFixed = false;
  FlagUseJetMass   = false;
  FlagIsSignalMC   = true;
  FlagIs7TeV	   = true;
  FlagIs10TeV	   = false;
  FlagTruthSel     = true;
  FlagAthenaComp   = false;

  MassTop = 172.5;

  input_path="input.root";
  output_path="output.root";

  IsBkg = false;

  ReadConfig(filename);
}


// --------------------------------------------------------- 
KLFitter::ReadConfigFile::ReadConfigFile(std::string filename, bool * validconfig)
{
  DO_ELECTRON = true;
  DO_MUON     = false;
  DO_BATCH    = false;

  FlagBTagging     = false;
  CutBTagging      = 1.e4;
  FlagIntegrate    = false;
  FlagTopMassFixed = false;
  FlagUseJetMass   = false;
  FlagIsSignalMC   = true;
  FlagIs7TeV	   = true;
  FlagIs10TeV	   = false;
  FlagTruthSel     = true;
  FlagAthenaComp   = false;

  MassTop = 172.5;

  input_path="input.root";
  output_path="output.root";

  IsBkg = false;

  if(ReadConfig(filename)!=-1){*validconfig=true;}
  else{*validconfig=false;}
}


// --------------------------------------------------------- 
KLFitter::ReadConfigFile::~ReadConfigFile()
{
}

// --------------------------------------------------------- 
int KLFitter::ReadConfigFile::ReadConfig(std::string filename)
{
  ifstream configfile(filename.c_str(),std::ios::in);
  std::string line;
  bool is_comment=false;
  bool is_whitespace=false;
  bool slash=false;
  int tmp;
  double tmpdouble=0.0;
  std::string tmpstr="";
  size_t found;
  std::string::iterator k;
  std::cout<<"reading "<<filename.c_str()<<"..."<<std::endl;

  if(configfile.is_open())
    {
      //read config
      while (! configfile.eof() )
        {
          getline (configfile,line);
          is_comment=false;
          slash=false;
          is_whitespace=false;
          if(line.size()==0) //ignore any empty lines
            continue;
          //looking for uncommentation
          for(k=line.begin();k<line.end();k++)
            {
              //ignore any white space, unless a slash was found before
              if((*k==std::string(" ") || *k==std::string("\t") || *k==std::string("\n")) && slash==false)
                {
                  is_whitespace=true;
                  continue;
                }
              //a line is a comment, if there is a #, % or // as first non whitespace character
              if(*k==std::string("#") || *k==std::string("%") || (*k==std::string("/") && slash==true))
                {
                  is_comment=true;
                  is_whitespace=false;
                  break;
                }
              else if(*k==std::string("/"))
                {
                  slash=true;
                  is_whitespace=false;
                }
              else
                {
                  break;
                }
            }

          if(is_comment==false)
            {
              found=line.find("DO_ELECTRON");
              if(found!=std::string::npos)
                {
                  found=line.find("=",found);
                  if(found!=std::string::npos)
                    {
                      tmp=GetTrueOrFalse(line,found);
                      if(tmp!=-1)
                        {
                          DO_ELECTRON=(tmp==1);
                        }
                      else
                        {
                          std::cout<<"Warning: Error while reading value of DO_ELECTRON, using standard value"<<std::endl;
                        }
                    }
                }
              else
                {
                  found=line.find("DO_MUON");
                  if(found!=std::string::npos)
                    {
                      found=line.find("=",found);
                      if(found!=std::string::npos)
                        {
                          tmp=GetTrueOrFalse(line,found);
                          if(tmp!=-1)
                            {
                              DO_MUON=(tmp==1);
                            }
                          else
                            {
                              std::cout<<"Warning: Error while reading value of DO_MUON, using standard value"<<std::endl;
                            }
                        }
                    }
		  else
		    {
		      found=line.find("CutBTagging");
		      if(found!=std::string::npos)
			{
			  found=line.find("=",found);
			  if(found!=std::string::npos)
			    {
			      tmp=GetValue(&tmpdouble,line,found);
				if(tmp!=-1)
				  {
				    CutBTagging=(tmp==1);
				  }
				else
				  {
				    std::cout<<"Warning: Error while reading value of CutBTagging, using standard value"<<std::endl;
				  }
			    }
			}
		      else
			{
			  found=line.find("DO_BATCH");
			  if(found!=std::string::npos)
			    {
			      found=line.find("=",found);
			      if(found!=std::string::npos)
				{
				  tmp=GetTrueOrFalse(line,found);
				  if(tmp!=-1)
				    {
				      DO_BATCH=(tmp==1);
				    }
				  else
				    {
				      std::cout<<"Warning: Error while reading value of DO_BATCH, using standard value"<<std::endl;
				    }
				}
			    }
			  else
			    {
			      found=line.find("FlagBTagging");
			      if(found!=std::string::npos)
				{
				  found=line.find("=",found);
				  if(found!=std::string::npos)
				    {
				      tmp=GetTrueOrFalse(line,found);
				      if(tmp!=-1)
					{
					  FlagBTagging=(tmp==1);
					}
				      else
					{
					  std::cout<<"Warning: Error while reading value of FlagBTagging, using standard value"<<std::endl;
					}
				    }
				}
			      else
				{
				  found=line.find("FlagTopMassFixed");
				  if(found!=std::string::npos)
				    {
				      found=line.find("=",found);
				      if(found!=std::string::npos)
					{
					  tmp=GetTrueOrFalse(line,found);
					  if(tmp!=-1){
					    FlagTopMassFixed=(tmp==1);
					  }
					  else
					    {
					      std::cout<<"Warning: Error while reading value of FlagTopMassFixed, using standard value"<<std::endl;
					    }
					}
				    }
				  else
				    {
				      found=line.find("FlagIntegrate");
				      if(found!=std::string::npos)
					{
					  found=line.find("=",found);
					  if(found!=std::string::npos)
					    {
					      tmp=GetTrueOrFalse(line,found);
					      if(tmp!=-1){
						FlagIntegrate=(tmp==1);
					      }
					      else
						{
						  std::cout<<"Warning: Error while reading value of FlagIntegrate, using standard value"<<std::endl;
						}
					    }
					}
				      else
					{
					  found=line.find("FlagUseJetMass");
					  if(found!=std::string::npos)
					    {
					      found=line.find("=",found);
					      if(found!=std::string::npos)
						{
						  tmp=GetTrueOrFalse(line,found);
						  if(tmp!=-1)
						    {
						      FlagUseJetMass=(tmp==1);
						    }
						  else
						    {
						      std::cout<<"Warning: Error while reading value of FlagUseJetMass, using standard value"<<std::endl;
						    }
						}
					    }
					  else
					    {
					      found=line.find("FlagIsSignalMC");
					      if(found!=std::string::npos)
						{
						  found=line.find("=",found);
						  if(found!=std::string::npos)
						    {
						      tmp=GetTrueOrFalse(line,found);
						      if(tmp!=-1)
							{
							  FlagIsSignalMC=(tmp==1);
							}
						      else
							{
							  std::cout<<"Warning: Error while reading value of FlagIsSignalMC, using standard value"<<std::endl;
							}
						    }
						}
					      else
						{
						  found=line.find("FlagIs7TeV");
						  if(found!=std::string::npos)
						    {
						      found=line.find("=",found);
						      if(found!=std::string::npos)
							{
							  tmp=GetTrueOrFalse(line,found);
							  if(tmp!=-1)
							    {
							      FlagIs7TeV=(tmp==1);
							    }
							  else
							    {
							      std::cout<<"Warning: Error while reading value of FlagIs7TeV, using standard value"<<std::endl;
							    }
							}
						    }
						  else
						    {
						      found=line.find("FlagIs10TeV");
						      if(found!=std::string::npos)
							{
							  found=line.find("=",found);
							  if(found!=std::string::npos)
							    {
							      tmp=GetTrueOrFalse(line,found);
							      if(tmp!=-1)
								{
								  FlagIs10TeV=(tmp==1);
								}
							      else
								{
								  std::cout<<"Warning: Error while reading value of FlagIs10TeV, using standard value"<<std::endl;
								}
							    }
							}
						      else
							{
							  found=line.find("MassTop");
							  if(found!=std::string::npos)
							    {
							      found=line.find("=",found);
							      if(found!=std::string::npos)
								{
								  tmp=GetValue(&tmpdouble,line,found);
								  if(tmp!=-1)
								    {
								      MassTop=tmpdouble;
								    }
								  else
								    {
								      std::cout<<"Warning: Error while reading value of MassTop, using standard value"<<std::endl;
								    }
								}
							    }
							  else
							    {
							      found=line.find("PathToInputFile");
							      if(found!=std::string::npos)
								{
								  found=line.find("=",found);
								  if(found!=std::string::npos)
								    {
								      tmp=GetPath(&tmpstr,line,found);
								      if(tmp!=-1)
									{
									  input_path=tmpstr;
									}
								      else
									{
									  std::cout<<"Warning: Error while reading path to input file, using standard path 'input.root'"<<std::endl;
									}
								    }
								}   
							      else
								{
								  found=line.find("PathToOutputFile");
								  if(found!=std::string::npos)
								    {
								      found=line.find("=",found);
								      if(found!=std::string::npos)
									{
									  tmp=GetPath(&tmpstr,line,found);
									  if(tmp!=-1)
									    {
									      output_path=tmpstr;
									    }
									  else
									    {
									      std::cout<<"Warning: Error while reading path to output file, using standard path 'output.root'"<<std::endl;
									    }
									}
								    }
								  else
								    {
								      found=line.find("IsBkg");
								      if(found!=std::string::npos)
									{
									  found=line.find("=",found);
									  if(found!=std::string::npos)
									    {
									      tmp=GetTrueOrFalse(line,found);
									      if(tmp!=-1)
										{
										  IsBkg=(tmp==1);
										}
									      else
										{
										  std::cout<<"Warning: Error while reading value of IsBkg, using standard value"<<std::endl;
										}
									    }
									}
                                                                      else
                                                                        {
                                                                          found=line.find("FlagTruthSel");
                                                                          if(found!=std::string::npos)
                                                                            {
                                                                              found=line.find("=",found);
                                                                              if(found!=std::string::npos)
                                                                                {
                                                                                  tmp=GetTrueOrFalse(line,found);
                                                                                  if(tmp!=-1)
                                                                                    {
                                                                                      FlagTruthSel=(tmp==1);
                                                                                    }
                                                                                  else
                                                                                    {
                                                                                      std::cout<<"Warning: Error while reading value of FlagTruthSel, using standard value"<<std::endl;
                                                                                    }
                                                                                }
                                                                            }
                                                                          else
                                                                            {
                                                                              found=line.find("FlagAthenaComp");
                                                                              if(found!=std::string::npos)
                                                                                {
                                                                                  found=line.find("=",found);
                                                                                  if(found!=std::string::npos)
                                                                                    {
                                                                                      tmp=GetTrueOrFalse(line,found);
                                                                                      if(tmp!=-1)
                                                                                        {
                                                                                          FlagAthenaComp=(tmp==1);
                                                                                        }
                                                                                      else
                                                                                        {
                                                                                          std::cout<<"Warning: Error while reading value of FlagAthenaComp, using standard value"<<std::endl;
                                                                                        }
                                                                                    }
                                                                                }
                                                                              else
                                                                                {
                                                                                  if(is_whitespace==false)
                                                                                    {
                                                                                      std::cout<<"Warning: the line \""<<line.c_str()<<"\" does not match any variable. It is ignored."<<std::endl;
                                                                                    }
                                                                                }
                                                                            }
									}
								    }
								}
							    }
							}
						    }
						}
					    }
					}
				    }
				}
			    }
			}
		    }
		}
	    }
	}
      configfile.close();
    }
  else
    {
      std::cout<<"Couldn't open the file \"";
      std::cout<<filename.c_str();
      std::cout<<"\". Will use standard values."<<std::endl;
    }
  //Print Flag values
  std::cout<<"Flags are set as follows:"<<std::endl;
  std::cout<<"DO_ELECTRON = "<<DO_ELECTRON<<std::endl;
  std::cout<<"DO_MUON = "<<DO_MUON<<std::endl;
  std::cout<< "DO_BATCH = "<<DO_BATCH<<std::endl;
  std::cout<< "FlagBTagging = "<<FlagBTagging<<std::endl;
  std::cout<< "FlagIntegrate = "<<FlagIntegrate<<std::endl;
  std::cout<< "FlagTopMassFixed = "<<FlagTopMassFixed<<std::endl;
  std::cout<< "FlagUseJetMass = "<<FlagUseJetMass<<std::endl;
  std::cout<< "FlagIsSignalMC = "<<FlagIsSignalMC<<std::endl;
  std::cout<< "FlagIs7TeV = "<<FlagIs7TeV<<std::endl;
  std::cout<< "FlagIs10TeV = "<<FlagIs10TeV<<std::endl;
  std::cout<< "MassTop = "<<MassTop<<std::endl;
  std::cout<< "PathToInputFile = " << input_path<<std::endl;
  std::cout<< "PathToOutputFile = " << output_path<<std::endl;
  std::cout << "IsBkg = " << IsBkg << std::endl;
  std::cout << "FlagTruthSel = " << FlagTruthSel << std::endl;
  std::cout << "FlagAthenaComp = " << FlagAthenaComp << std::endl;
  std::cout << std::endl;

  if(CheckIOPath()){ 
	if(FlagIs7TeV && !FlagIs10TeV){ return 0;}
  		else if(!FlagIs7TeV && FlagIs10TeV){ return 0;}
  		else{std::cout<<"KLFitter::ReadConfigFile::ReadConfig(). Error: Ambiguities in the chosen centre-of-mass energy for using the correct transferfunctions! Exactly one flag has to be true!!!"<<std::endl;return -1;}
	}
  else{std::cout<<"KLFitter::ReadConfigFile::ReadConfig(). Error: PathToInputFile==PathToOutputFile! Will not overwrite input file!!!"<<std::endl;return -1;}

}



bool KLFitter::ReadConfigFile::CheckIOPath()
{ 
  if(input_path==output_path)
    {return false;}
  else
    {return true;}
}

int KLFitter::ReadConfigFile::GetValue(double * ret, std::string line, size_t found)
{
  std::string::iterator k;
  bool is_whitespace=true;
  bool is_number=false;
  bool found_point=false;
  int a=0;
  int l=0;
  unsigned int i=0;
  *ret=0;
  if(line.size()<=found)
    {return -1;}
  else
    {

      for(k=line.begin();k<line.end();k++)
        {
          //go forward to the place of "="
          if(i<=found)
            {i++;continue;}
          //ignore any white space unless it is within a number
          if((*k==std::string(" ") || *k==std::string("\t")) && is_number==false)
            {is_whitespace=true;continue;}
          else
            {
              //Is this char a number (0 to 9) ?
              if(IsNumber(k,&a))
                {                                       
                  *ret+=a*pow(10,l);l--; // calculate the whole number. This result has to be corrected by a factor of some power of 10. But this correction is only known when the "." is found or the end of the number
                  is_number=true;
                                                
                }
              else
                {
                  if(*k==std::string(".") && found_point==false) //is this nonumber char the point?
                    {
                      *ret*=pow(10,fabs(l)-1); //if yes and there was no point before, correct the number and set the "l" this way, that it calculates the powers for the coming numbers in the right way
                      l=-1;     
                      found_point=true;                                                    
                    }
                  else
                    {
                      break;
                    }
                }
            }
        }
      if(found_point==false){*ret*=pow(10,fabs(l)-1);} //calculate the correction, if the number ended without a point
      if(is_number==true){return 1;}
      else{return -1;}
    }

}

int KLFitter::ReadConfigFile::GetPath(std::string * ret, std::string line, size_t found)
{
  std::string::iterator k;
  bool is_whitespace=true;
  bool path_started=false;
  int l=0;
  unsigned int i=0;
  *ret=std::string(""); //clear ret
  if(line.size()<=found)
    {return -1;}        
  else
    {

      for(k=line.begin();k<line.end();k++)
        {
          //go forward to the place of "="
          if(i<=found)
            {i++;continue;}
          //ignore any white space unless the path started
          if((*k==std::string(" ") || *k==std::string("\t")) && path_started==false)
            {is_whitespace=true;continue;}
          else
            {
              if(*k==std::string(" ") || *k==std::string("\t") || *k==std::string("#"))
                {break;}
              *ret+=*k;l++;
              path_started=true;
            }
        }
        
      if(l==0){*ret="";return -1;} //return -1 if path has length 0
      else{return 0;}           
    }

}

// --------------------------------------------------------- 
bool KLFitter::ReadConfigFile::IsNumber(std::string::iterator a, int * number)
{
        
  if(*a==std::string("0")){*number=0;return true;}
  else if (*a==std::string("1")){*number=1;return true;}
  else if (*a==std::string("2")){*number=2;return true;}
  else if (*a==std::string("3")){*number=3;return true;}
  else if (*a==std::string("4")){*number=4;return true;}
  else if (*a==std::string("5")){*number=5;return true;}
  else if (*a==std::string("6")){*number=6;return true;}
  else if (*a==std::string("7")){*number=7;return true;}
  else if (*a==std::string("8")){*number=8;return true;}
  else if (*a==std::string("9")){*number=9;return true;}
  else{return false;*number=-1;}
}


// --------------------------------------------------------- 
int KLFitter::ReadConfigFile::GetTrueOrFalse(std::string line, size_t found)
{
  if(line.size()<=found)
    {return -1;}
  else
    {
      //string to lower case

      for (unsigned int i = 0; i < line.size(); i++)
        {line[i] = tolower(line[i]);}   
      if(line.find("true", found)!=std::string::npos)
        {
          return 1;
        }
      else if(line.find("false", found)!=std::string::npos)
        {
          return 0;
        }
      else
        {return -1;}

    }
}

//<----------- End of reading out config.conf----------------->