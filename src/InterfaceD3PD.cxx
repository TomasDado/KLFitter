#include "InterfaceD3PD.h" 
#include "Particles.h"

#include <TLorentzVector.h>

#include <TROOT.h>
#include <TTree.h>
#include <TFile.h>

#include <iostream> 
#include <cmath>

// --------------------------------------------------------- 
KLFitter::InterfaceD3PD::InterfaceD3PD()
{
  fTree = 0; 

  EventNumber = 0;
	
	topMu_n = 0;
	topMu_index = 0;
	topMu_use = 0;
	topMu_inTrigger = 0;    
  mu_E = 0;  
  mu_px = 0;  
  mu_py = 0;  
  mu_pz = 0;  
  mu_pt = 0;  
  mu_eta = 0;  
  mu_phi = 0;  

  topEl_n = 0;
  topEl_index = 0;
	topEl_use = 0;
	topEl_inTrigger = 0;    
  el_E = 0;  
  el_px = 0;  
  el_py = 0;  
  el_pz = 0;  
  el_pt = 0;  
  el_eta = 0;  
  el_phi = 0;  

  topJet_n = 0;
  topJet_index = 0;
	topJet_use = 0;
	topJet_inTrigger = 0;   
  jet_E = 0;  
  //jet_px = 0;  
  //jet_py = 0;  
  //jet_pz = 0;  
  jet_pt = 0;  
  jet_eta = 0;  
  jet_phi = 0;  
  jet_flavor_weight_SV0 = 0;  

  topMET_et = 0; 
  topMET_phi = 0; 
  topMET_etx = 0; 
  topMET_ety = 0; 
      
  // needed due to incomplete dictionaries in ROOT (reading vector<bool> from TTree won't work without)
  gROOT->ProcessLine("#include <vector>");
  gROOT->ProcessLine(".L loader.C+");
}

// --------------------------------------------------------- 
KLFitter::InterfaceD3PD::~InterfaceD3PD()
{
}

// --------------------------------------------------------- 
int KLFitter::InterfaceD3PD::NEvents()
{
  if (!fTree)
    return 0; 
        
  else
    return fTree->GetEntries(); 
}

// --------------------------------------------------------- 
int KLFitter::InterfaceD3PD::OpenRootFile(const char* filename, Option_t* opt)
{
  // define error code 
  int err = 1; 

  // open file 
  err *= KLFitter::InterfaceRoot::OpenRootFile(filename, opt); 

  // connect Root tree 
  err *= this ->ConnectTree("physics"); 

  // return error code 
  return err; 
}

// --------------------------------------------------------- 
int KLFitter::InterfaceD3PD::ConnectTree(const char* treename)
{
  // check if file exists 
  if (!fRootFile)
    {
      std::cout << "KLFitter::InterfaceD3PD::ConnectTree(). No Root file defined." << std::endl; 
      return 0; 
    } 

  // check if file is open 
  if (!fRootFile->IsOpen())
    { 
      std::cout << "KLFitter::InterfaceD3PD::ConnectTree(). Root file not open."<< std::endl; 
      return 0; 
    }

  // get tree from file 
  fTree = (TTree *) fRootFile->Get(treename); 

  if (!fTree)
    {
      std::cout << "KLFitter::InterfaceD3PD::ConnectTree(). Tree not found." << std::endl; 
      return 0; 
    }

  return ConnectTree(fTree);
}
// --------------------------------------------------------- 
int KLFitter::InterfaceD3PD::ConnectTree(TTree * fTree)
{
  if (!this->fTree) this->fTree = fTree;
  // set branch adresses
  fTree->SetBranchAddress("EventNumber",  &EventNumber); 
  //fTree->SetBranchAddress("mcevt_weight", &fWeight);
  fTree->SetBranchAddress("mcevt_weight", &mcevt_weight);
		
  fTree->SetBranchAddress("topMu_n",  &topMu_n);
  fTree->SetBranchAddress("topMu_index",  &topMu_index);
  fTree->SetBranchAddress("topMu_use",  &topMu_use);
  fTree->SetBranchAddress("topMu_inTrigger",  &topMu_inTrigger);  
  fTree->SetBranchAddress("mu_E",  &mu_E); 
  fTree->SetBranchAddress("mu_px", &mu_px); 
  fTree->SetBranchAddress("mu_py", &mu_py); 
  fTree->SetBranchAddress("mu_pz", &mu_pz); 
  fTree->SetBranchAddress("mu_pt", &mu_pt); 
  fTree->SetBranchAddress("mu_eta", &mu_eta); 
  fTree->SetBranchAddress("mu_phi", &mu_phi); 
 

  fTree->SetBranchAddress("topEl_n",  &topEl_n); 
  fTree->SetBranchAddress("topEl_index",  &topEl_index);
  fTree->SetBranchAddress("topEl_use",  &topEl_use);
  fTree->SetBranchAddress("topEl_inTrigger",  &topEl_inTrigger);
  fTree->SetBranchAddress("el_E",  &el_E); 
  fTree->SetBranchAddress("el_px", &el_px); 
  fTree->SetBranchAddress("el_py", &el_py); 
  fTree->SetBranchAddress("el_pz", &el_pz); 
  fTree->SetBranchAddress("el_pt", &el_pt); 
  fTree->SetBranchAddress("el_eta", &el_eta); 
  fTree->SetBranchAddress("el_phi", &el_phi); 
  
  fTree->SetBranchAddress("topJet_n",   &topJet_n);
  fTree->SetBranchAddress("topJet_index",   &topJet_index);
  fTree->SetBranchAddress("topJet_use",  &topJet_use);
  fTree->SetBranchAddress("topJet_inTrigger",  &topJet_inTrigger);  
  fTree->SetBranchAddress("jet_E",   &jet_E); 
  //fTree->SetBranchAddress("jet_px",  &jet_px); 
  //fTree->SetBranchAddress("jet_py",  &jet_py); 
  //fTree->SetBranchAddress("jet_pz",  &jet_pz); 
  fTree->SetBranchAddress("jet_pt",  &jet_pt); 
  fTree->SetBranchAddress("jet_eta", &jet_eta); 
  fTree->SetBranchAddress("jet_phi", &jet_phi); 
  fTree->SetBranchAddress("jet_flavor_weight_SV0", &jet_flavor_weight_SV0); 

  fTree->SetBranchAddress("topMET_et",  &topMET_et); 
  fTree->SetBranchAddress("topMET_phi", &topMET_phi); 
  fTree->SetBranchAddress("topMET_etx", &topMET_etx); 
  fTree->SetBranchAddress("topMET_ety", &topMET_ety); 

  // no error 
  return 1;
}

// --------------------------------------------------------- 
int KLFitter::InterfaceD3PD::Event(int index)
{

  // check tree 
  if (!fTree)
    {
      std::cout << "KLFitter::InterfaceD3PD::GetEvent(). Tree not defined." << std::endl; 
      return 0; 
    } 

  // check event number 
  if (index < 0 || index >= fTree->GetEntries())
    {
      std::cout << "KLFitter::InterfaceD3PD::GetEvent(). Event number negative or too large." << std::endl; 
      return 0; 
    } 

  // get event 
  fTree->GetEntry(index); 

  // fill particles 
  if (!this->FillParticles())
    return 0; 

  // no error 
  return 1; 
}

// --------------------------------------------------------- 
int KLFitter::InterfaceD3PD::FillParticles()
{
  // delete old particle container
  if (fParticles) 
    delete fParticles; 

  // create new particle container
  fParticles = new KLFitter::Particles(); 
  
  //set weight
    if (mcevt_weight){
      fWeight = mcevt_weight->at(0);
    } else {
    fWeight=1.0;
    }
  
	// fill jets
	for (int i = 0; i < topJet_n; ++i){
		if ( topJet_use->at(i) ){
  		TLorentzVector * tmp = new TLorentzVector(0,0,0,0);
  		tmp->SetPtEtaPhiE(jet_pt ->at(topJet_index->at(i)) / 1000. , 
  										jet_eta->at(topJet_index->at(i)), 
  										jet_phi->at(topJet_index->at(i)),
  										jet_E  ->at(topJet_index->at(i)) / 1000.);
					
	  	fParticles->AddParticle(tmp, KLFitter::Particles::kParton,"",jet_flavor_weight_SV0->at(topJet_index->at(i)));
 	  }
	} 

	//fill electrons
  for (int i = 0; i < topEl_n; ++i){
  	if ( topEl_use->at(i) && topEl_inTrigger->at(i) ){ 
      fParticles->AddParticle(new TLorentzVector(el_px->at(topEl_index->at(i)) / 1000., 
      																					 el_py->at(topEl_index->at(i)) / 1000., 
      																					 el_pz->at(topEl_index->at(i)) / 1000., 
      																					 el_E ->at(topEl_index->at(i)) / 1000.), 		
      																					 KLFitter::Particles::kElectron);
		}   																					 
	}

  // fill muons
  for (int i = 0; i < topMu_n; ++i){
  	if ( topMu_use->at(i) && topMu_inTrigger->at(i) ){ 
      fParticles->AddParticle(new TLorentzVector(mu_px->at(topMu_index->at(i)) / 1000., mu_py->at(topMu_index->at(i)) / 1000., mu_pz->at(topMu_index->at(i)) / 1000., mu_E->at(topMu_index->at(i)) / 1000.), KLFitter::Particles::kMuon); 
    }
	}
  // no error 
  return 1;
}

// --------------------------------------------------------- 