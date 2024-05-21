// general ROOT/C includes
#include <iostream>
#include "TFile.h"
#include "TRandom.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TRandom.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TProfile2D.h"
#include <TF1.h>
#include "assert.h"
#include <fstream>
#include "TMath.h"
#include "TH2F.h"
#include "TH2D.h"
#include "TMath.h"
#include <TNtuple.h>
#include "TChain.h"
#include <TString.h>
#include <TLatex.h>
#include <TCut.h>
#include "TDatime.h"
#include <vector>
#include "TCanvas.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// event map
#include "../../../eventMap/eventMap.h"
// jet corrector
#include "../../../JetEnergyCorrections/JetCorrector.h"
// jet uncertainty
#include "../../../JetEnergyCorrections/JetUncertainty.h"
// general analysis variables
#include "../../../headers/AnalysisSetupV2p1.h"
// vz-fit parameters
//#include "../../../headers/fitParameters/vzFitParams_PYTHIA_mu5.h"
//#include "../../../headers/fitParameters/vzFitParams_PYTHIA_mu7.h"
#include "../../../headers/fitParameters/vzFitParams_PYTHIA_mu12.h"
// jetPt-fit parameters
//#include "../../../headers/fitParameters/jetPtFitParams_PYTHIA_mu5.h"
//#include "../../../headers/fitParameters/jetPtFitParams_PYTHIA_mu7.h"
#include "../../../headers/fitParameters/jetPtFitParams_PYTHIA_mu12.h"
// JESb fit params
//#include "../../../headers/fitParameters/JESbFitParams_PYTHIA_mu7.h"
#include "../../../headers/fitParameters/JESbFitParams_PYTHIA_mu12.h"
TF1 *fitFxn_hiBin, *fitFxn_vz, *fitFxn_jetPt, *fitFxn_PYTHIA_JESb;
// vz-fit function
#include "../../../headers/fitFunctions/fitFxn_vz_PYTHIA.h"
// jetPt-fit function
#include "../../../headers/fitFunctions/fitFxn_jetPt.h"
// JESb-fit function
#include "../../../headers/fitFunctions/fitFxn_PYTHIA_JESb.h"

// eta-phi mask function
#include "../../../headers/functions/etaPhiMask.h"
// getDr function
#include "../../../headers/functions/getDr.h"
// getJetPtBin function
#include "../../../headers/functions/getJetPtBin.h"
// getCentBin function
#include "../../../headers/functions/getCentBin_v2.h"
// getPtRel function
#include "../../../headers/functions/getPtRel.h"
// isQualityMuon_hybridSoft function
#include "../../../headers/functions/isQualityMuon_hybridSoft.h"
// isQualityMuon_tight function
#include "../../../headers/functions/isQualityMuon_tight.h"
// isWDecayMuon function
#include "../../../headers/functions/isWDecayMuon.h"
// triggerIsOn function
#include "../../../headers/functions/triggerIsOn.h"
// pthat filter function
#include "../../../headers/functions/passesLeadingGenJetPthatFilter.h"
// JetTrkMax filter function
#include "../../../headers/functions/jet_filter/passesJetTrkMaxFilter.h"
// print introduction
#include "../../../headers/introductions/printIntroduction_PYTHIA_scan_V3p7.h"
// analysis config
#include "../../../headers/config/config_PYTHIA.h"
// read config
#include "../../../headers/config/readConfig.h"
// remove HYDJET jets function
#include "../../../headers/functions/jet_filter/remove_HYDJET_jet.h"


void PYTHIA_scan_response(int group = 1){

  TString input = Form("/eos/cms/store/group/phys_heavyions/cbennett/output_PYTHIA_DiJet_noRecoJetPtCut/PYTHIA_DiJet_skim_output_%i.root",group);
  TString output = Form("/eos/cms/store/group/phys_heavyions/cbennett/scanningOutput/output_PYTHIA_mu12_response_doBJetEnergyShift/PYTHIA_DiJet_scan_output_%i.root",group);

  
  //printIntroduction();
  readConfig();

  // JET ENERGY CORRECTIONS
  vector<string> Files;
  
  Files.push_back("../../../JetEnergyCorrections/Spring18_ppRef5TeV_V6_MC_L2Relative_AK4PF.txt"); // LXPLUS

  JetCorrector JEC(Files);

  JetUncertainty JEU("../../../JetEnergyCorrections/Spring18_ppRef5TeV_V6_MC_Uncertainty_AK4PF.txt");

  // WEIGHT FUNCTIONS

  


  //  initialize histograms
  // JETS

  TH2D *h_matchedRecoJetPt_genJetPt;
  TH2D *h_matchedRecoJetPt_genJetPt_var;
  TH2D *h_matchedRecoJetPtOverGenJetPt_genJetPt[7];
  TH2D *h_matchedRecoJetPtOverGenJetPt_genJetEta[7];



  // Define histograms
  const int N1 = 7;
  double ptAxis1[N1] = {50,60,80,120,200,300,500};
  const int N2 = 32;
  double ptAxis2[N2] = {0,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200,210,220,230,240,250,260,270,280,290,300,500};



  

  h_matchedRecoJetPt_genJetPt = new TH2D("h_matchedRecoJetPt_genJetPt","genJetPt vs. matchedRecoJetPt",NPtBins,ptMin,ptMax,NPtBins,ptMin,ptMax);
    
  h_matchedRecoJetPt_genJetPt->Sumw2(); 

  h_matchedRecoJetPt_genJetPt_var = new TH2D("h_matchedRecoJetPt_genJetPt_var","genJetPt vs. matchedRecoJetPt, var bins",N1-1,ptAxis1,N2-1,ptAxis2);
    
  h_matchedRecoJetPt_genJetPt_var->Sumw2();  
		
    
  h_matchedRecoJetPtOverGenJetPt_genJetPt[0] = new TH2D("h_matchedRecoJetPtOverGenJetPt_genJetPt_allJets","matchedRecoJetPt/genJetPt vs genJetPt, all flavors",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedRecoJetPtOverGenJetPt_genJetPt[1] = new TH2D("h_matchedRecoJetPtOverGenJetPt_genJetPt_bJets","matchedRecoJetPt/genJetPt vs genJetPt, bJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedRecoJetPtOverGenJetPt_genJetPt[2] = new TH2D("h_matchedRecoJetPtOverGenJetPt_genJetPt_cJets","matchedRecoJetPt/genJetPt vs genJetPt, cJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedRecoJetPtOverGenJetPt_genJetPt[3] = new TH2D("h_matchedRecoJetPtOverGenJetPt_genJetPt_udJets","matchedRecoJetPt/genJetPt vs genJetPt, udJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedRecoJetPtOverGenJetPt_genJetPt[4] = new TH2D("h_matchedRecoJetPtOverGenJetPt_genJetPt_sJets","matchedRecoJetPt/genJetPt vs genJetPt, sJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedRecoJetPtOverGenJetPt_genJetPt[5] = new TH2D("h_matchedRecoJetPtOverGenJetPt_genJetPt_gJets","matchedRecoJetPt/genJetPt vs genJetPt, gJets",500,0,5,NPtBins,ptMin,ptMax);
  h_matchedRecoJetPtOverGenJetPt_genJetPt[6] = new TH2D("h_matchedRecoJetPtOverGenJetPt_genJetPt_xJets","matchedRecoJetPt/genJetPt vs genJetPt, xJets",500,0,5,NPtBins,ptMin,ptMax);

  h_matchedRecoJetPtOverGenJetPt_genJetEta[0] = new TH2D("h_matchedRecoJetPtOverGenJetPt_genJetEta_allJets","matchedRecoJetPt/genJetPt vs genJetEta, all flavors",500,0,5,NEtaBins,etaMin,etaMax);
  h_matchedRecoJetPtOverGenJetPt_genJetEta[1] = new TH2D("h_matchedRecoJetPtOverGenJetPt_genJetEta_bJets","matchedRecoJetPt/genJetPt vs genJetEta, bJets",500,0,5,NEtaBins,etaMin,etaMax);
  h_matchedRecoJetPtOverGenJetPt_genJetEta[2] = new TH2D("h_matchedRecoJetPtOverGenJetPt_genJetEta_cJets","matchedRecoJetPt/genJetPt vs genJetEta, cJets",500,0,5,NEtaBins,etaMin,etaMax);
  h_matchedRecoJetPtOverGenJetPt_genJetEta[3] = new TH2D("h_matchedRecoJetPtOverGenJetPt_genJetEta_udJets","matchedRecoJetPt/genJetPt vs genJetEta, udJets",500,0,5,NEtaBins,etaMin,etaMax);
  h_matchedRecoJetPtOverGenJetPt_genJetEta[4] = new TH2D("h_matchedRecoJetPtOverGenJetPt_genJetEta_sJets","matchedRecoJetPt/genJetPt vs genJetEta, sJets",500,0,5,NEtaBins,etaMin,etaMax);
  h_matchedRecoJetPtOverGenJetPt_genJetEta[5] = new TH2D("h_matchedRecoJetPtOverGenJetPt_genJetEta_gJets","matchedRecoJetPt/genJetPt vs genJetEta, gJets",500,0,5,NEtaBins,etaMin,etaMax);
  h_matchedRecoJetPtOverGenJetPt_genJetEta[6] = new TH2D("h_matchedRecoJetPtOverGenJetPt_genJetEta_xJets","matchedRecoJetPt/genJetPt vs genJetEta, xJets",500,0,5,NEtaBins,etaMin,etaMax);


      
  h_matchedRecoJetPtOverGenJetPt_genJetPt[0]->Sumw2();
  h_matchedRecoJetPtOverGenJetPt_genJetPt[1]->Sumw2();
  h_matchedRecoJetPtOverGenJetPt_genJetPt[2]->Sumw2();
  h_matchedRecoJetPtOverGenJetPt_genJetPt[3]->Sumw2();
  h_matchedRecoJetPtOverGenJetPt_genJetPt[4]->Sumw2();
  h_matchedRecoJetPtOverGenJetPt_genJetPt[5]->Sumw2();
  h_matchedRecoJetPtOverGenJetPt_genJetPt[6]->Sumw2();

  h_matchedRecoJetPtOverGenJetPt_genJetEta[0]->Sumw2();
  h_matchedRecoJetPtOverGenJetPt_genJetEta[1]->Sumw2();
  h_matchedRecoJetPtOverGenJetPt_genJetEta[2]->Sumw2();
  h_matchedRecoJetPtOverGenJetPt_genJetEta[3]->Sumw2();
  h_matchedRecoJetPtOverGenJetPt_genJetEta[4]->Sumw2();
  h_matchedRecoJetPtOverGenJetPt_genJetEta[5]->Sumw2();
  h_matchedRecoJetPtOverGenJetPt_genJetEta[6]->Sumw2();

 



  TFile *f = TFile::Open(input);
  cout << "	File opened!" << endl;
  auto em = new eventMap(f);
  em->isMC = isMC_status;
  em->AASetup = AASetup_status;
  cout << "	Initializing variables ... " << endl;
  em->init();
  cout << "	Loading jet..." << endl;
  em->loadJet(jetTreeString);
  cout << "	Loading muon..." << endl;
  em->loadMuon(muonTreeString);
  cout << "	Loading muon triggers..." << endl;
  em->loadMuonTrigger(hltString);
  cout << "	Loading tracks..." << endl;
  em->loadTrack();
  cout << "	Loading gen particles..." << endl;
  em->loadGenParticle();
  cout << "	Variables initilized!" << endl << endl ;
  int NEvents = em->evtTree->GetEntries();
  cout << "	Number of events = " << NEvents << endl;


  // define event filters
  em->regEventFilter(NeventFilters, eventFilters);

  TRandom *randomGenerator = new TRandom2();

  // jet-energy resolution fit function
  TF1 *JER_fxn = new TF1("JER_fxn","sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x))",50,300);
  JER_fxn->SetParameter(0,1.26585e-01);
  JER_fxn->SetParameter(1,-9.72986e-01);
  JER_fxn->SetParameter(2,3.67352e-04);


  loadFitFxn_vz();
  loadFitFxn_PYTHIA_JESb();

  // event loop
  int evi_frac = 0;
  for(int evi = 0; evi < NEvents ; evi++){
    //for(int evi = 0; evi < 10 ; evi++){
    if(evi==0) cout << "Processing events..." << endl;

    em->getEvent(evi);

    if((100*evi / NEvents) % 5 == 0 && 100*evi / NEvents > evi_frac) cout << "evt frac: " << evi_frac << "%" << endl;
    evi_frac = 100 * evi/NEvents;

    // global event cuts
    //cout << "Applying global event cuts..." << endl;
    if(em->pthat <= pthatcut) continue;
    if(fabs(em->vz) > 15.0) continue;
    if(em->checkEventFilter()) continue;
    //cout << "Event #" << evi << " passed the global cuts!" << endl;


    double w_reweight_vz = 1.0;
    if(doVzReweight){
      w_reweight_vz = fitFxn_vz->Eval(em->vz);
    }


    
    // apply HLT
    // int triggerDecision = em->HLT_HIL3Mu5_NHitQ10_v1;
    // int triggerDecision_Prescl = em->HLT_HIL3Mu5_NHitQ10_v1_Prescl;

    int triggerDecision = em->HLT_HIL3Mu7_v1;
    int triggerDecision_Prescl = em->HLT_HIL3Mu7_v1_Prescl;

    // int triggerDecision = em->HLT_HIL3Mu12_v1;
    // int triggerDecision_Prescl = em->HLT_HIL3Mu12_v1_Prescl;

    //cout << "triggerDecision = " << triggerDecision << endl;

    
    //if(!triggerIsOn(triggerDecision,triggerDecision_Prescl)) continue;

    //cout << "lets go!" << endl;

    // RECO VARIABLES
	
    int matchFlag[10] = {0,0,0,0,0,0,0,0,0,0};
    
    double w_pthat = em->weight;

    double w = w_pthat * w_reweight_vz;

    // GEN JET LOOP
    for(int i = 0; i < em->ngj ; i++){

      // JET VARIABLES
      double x = em->genjetpt[i];
      double y = em->genjeteta[i];
      double z = em->genjetphi[i];

      double matchedRecoJetPt = 0.0;
      double matchedRawJetPt = 0.0;
			
      if(TMath::Abs(y) > etaMax) continue;
	
      // GET FLAVOR FROM RECO MATCH
      bool hasRecoJetMatch = false;
      bool hasRecoJetMuon = false;
      double minDr = 100.0;
      int recoJetFlavorFlag = 0;
      int jetFlavorInt = 19;
	
      for(int k = 0; k < em->njet; k++){
		
	double dr = getDr(em->jeteta[k],em->jetphi[k],y,z);

	if(dr < minDr){ 

	  minDr = dr;

	  if(minDr < epsilon_mm){
				
	    hasRecoJetMatch = true;
	    recoJetFlavorFlag = k;

	    if(em->mupt[k] > 14.0) hasRecoJetMuon = true;
	    //if(em->mupt[k] > 7.0 && em->mupt[k] < 14.0) hasRecoJetMuon = true;
	    

	    JEC.SetJetPT(em->rawpt[k]);
	    JEC.SetJetEta(em->jeteta[k]);
	    JEC.SetJetPhi(em->jetphi[k]);

	    matchedRecoJetPt = JEC.GetCorrectedPT();
	    //matchedRecoJetPt = em->jetpt[k];
	    matchedRawJetPt = em->rawpt[k];

	    JEU.SetJetPT(matchedRecoJetPt);
	    JEU.SetJetEta(em->jeteta[k]);
	    JEU.SetJetPhi(em->jetphi[k]);

	       
	    // initialize
	    double correctedPt_down = 1.0;
	    double correctedPt_up = 1.0;

	    if(apply_JEU_shift_up){
	      correctedPt_up = matchedRecoJetPt * (1 + JEU.GetUncertainty().second);
	      matchedRecoJetPt = correctedPt_up;
	    }
	    else if(apply_JEU_shift_down){
	      correctedPt_down = matchedRecoJetPt * (1 - JEU.GetUncertainty().first);
	      matchedRecoJetPt = correctedPt_down;
	    }

	    double mu = 1.0;
	    double sigma = 0.2;
	    double smear = 0.0;

	    if(apply_JER_smear){
	      sigma = 0.663*JER_fxn->Eval(matchedRecoJetPt); // apply a 20% smear
	      smear = randomGenerator->Gaus(mu,sigma);
	      matchedRecoJetPt = matchedRecoJetPt * smear;
	    }

	    if(doBJetEnergyShift){
	      matchedRecoJetPt = matchedRecoJetPt * (1.0 / fitFxn_PYTHIA_JESb->Eval(matchedRecoJetPt));
	    }
	    

	  }	
	}

      }

      jetFlavorInt = em->partonFlavor[recoJetFlavorFlag];
     

			
			
      // fill response matrix
      if(hasRecoJetMatch && hasRecoJetMuon) {

	//cout << "matchedRecoJetPt = " << matchedRecoJetPt << endl;
	
	h_matchedRecoJetPt_genJetPt->Fill(matchedRecoJetPt,x,w);
	

	h_matchedRecoJetPt_genJetPt_var->Fill(matchedRecoJetPt,x,w);
	

	h_matchedRecoJetPtOverGenJetPt_genJetPt[0]->Fill(matchedRecoJetPt/x,x,w);
	

	if(x>60){
	  h_matchedRecoJetPtOverGenJetPt_genJetEta[0]->Fill(matchedRecoJetPt/x,y,w);
	  h_matchedRecoJetPtOverGenJetPt_genJetEta[0]->Fill(matchedRecoJetPt/x,y,w);
	}


	if(fabs(jetFlavorInt) == 5){
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[1]->Fill(matchedRecoJetPt/x,x,w);
	  				
	  if(x>60){
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[1]->Fill(matchedRecoJetPt/x,y,w);
	    
	  }
	} 
	if(fabs(jetFlavorInt) == 4){
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[2]->Fill(matchedRecoJetPt/x,x,w);
	  

	  if(x>60){
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[2]->Fill(matchedRecoJetPt/x,y,w);
	  
	  }

	} 
	if(fabs(jetFlavorInt) == 1 || fabs(jetFlavorInt) == 2){
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[3]->Fill(matchedRecoJetPt/x,x,w);
	  
	  if(x>60){
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[3]->Fill(matchedRecoJetPt/x,y,w);
	  
	  }
	} 
	if(fabs(jetFlavorInt) == 3){
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[4]->Fill(matchedRecoJetPt/x,x,w);
	  

	  if(x>60){
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[4]->Fill(matchedRecoJetPt/x,y,w);
	    
	  }

	}  
	if(jetFlavorInt == 21){
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[5]->Fill(matchedRecoJetPt/x,x,w);
	  

	  if(x>60){
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[5]->Fill(matchedRecoJetPt/x,y,w);
	    
	  }

	}  
	if(jetFlavorInt == 0){
	  h_matchedRecoJetPtOverGenJetPt_genJetPt[6]->Fill(matchedRecoJetPt/x,x,w);
	  
	  if(x>60){
	    h_matchedRecoJetPtOverGenJetPt_genJetEta[6]->Fill(matchedRecoJetPt/x,y,w);
	  
	  }

	}
      }
			



		

		




    }
    // END GEN JET LOOP

	

  } // END EVENT LOOP
  delete f;
  // WRITE
  auto wf = TFile::Open(output,"recreate");

  
    
  h_matchedRecoJetPt_genJetPt->Write();
  h_matchedRecoJetPt_genJetPt_var->Write();
    
  h_matchedRecoJetPtOverGenJetPt_genJetPt[0]->Write();
  h_matchedRecoJetPtOverGenJetPt_genJetPt[1]->Write();
  h_matchedRecoJetPtOverGenJetPt_genJetPt[2]->Write();
  h_matchedRecoJetPtOverGenJetPt_genJetPt[3]->Write();
  h_matchedRecoJetPtOverGenJetPt_genJetPt[4]->Write();
  h_matchedRecoJetPtOverGenJetPt_genJetPt[5]->Write();
  h_matchedRecoJetPtOverGenJetPt_genJetPt[6]->Write();

  h_matchedRecoJetPtOverGenJetPt_genJetEta[0]->Write();
  h_matchedRecoJetPtOverGenJetPt_genJetEta[1]->Write();
  h_matchedRecoJetPtOverGenJetPt_genJetEta[2]->Write();
  h_matchedRecoJetPtOverGenJetPt_genJetEta[3]->Write();
  h_matchedRecoJetPtOverGenJetPt_genJetEta[4]->Write();
  h_matchedRecoJetPtOverGenJetPt_genJetEta[5]->Write();
  h_matchedRecoJetPtOverGenJetPt_genJetEta[6]->Write();


  






  wf->Close();
  return;
  // END WRITE



}







