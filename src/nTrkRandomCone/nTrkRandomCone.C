#include "TRandom.h"
#include "../../eventMap/eventMap.h"
#include "../../JetEnergyCorrections/JetCorrector.h"
#include "../../JetEnergyCorrections/JetUncertainty.h"
#include "../../headers/functions/getDr.h"
#include "../../headers/functions/divideByBinwidth.h"

void nTrkRandomCone(){

  std::cout << "running nTrkRandomCone()"  << std::endl;
  ////////////////////////////////////////////////////////////////////////////////////

  double pi = TMath::Pi();
  double trkPtMin = 0.7;
  
  
  TString input_data = "/home/clayton/Analysis/data/PbPb/HiForestMiniAOD_withTracks_1kEvents.root";
  TString input_mc = "/home/clayton/Analysis/data/PYTHIAHYDJET/HiForestAOD_withTracks_1kEvents.root";
  
  TString output_data = "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/nTrkRandomCone/out_data.root";
  TString output_mc = "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/nTrkRandomCone/out_mc.root";

  TFile *f_mc = TFile::Open(input_mc);
  TFile *f_data = TFile::Open(input_data);

  auto em_mc = new eventMap(f_mc);
  auto em_data = new eventMap(f_data);

  em_mc->isMC = true;
  em_data->isMC = false;

  em_mc->AASetup = true;
  em_data->AASetup = true;

  em_mc->init();
  em_data->init();
  
  em_mc->loadJet("akCs4PFJetAnalyzer/t");
  em_data->loadJet("akCs4PFJetAnalyzer/t");

  em_mc->loadTrack("ppTrack/trackTree");
  em_data->loadTrack("PbPbTracks/trackTree");
  

  int nEvents_mc = em_mc->evtTree->GetEntries();
  int nEvents_data = em_data->evtTree->GetEntries();

  std::cout << "nEvents_mc = " << nEvents_mc << std::endl;
  std::cout << "nEvents_data = " << nEvents_data << std::endl;

  std::cout << "configuring parameters" << std::endl;
  TRandom *randomGenerator = new TRandom2();
  double dR_max = 0.4;
  
  int nTrkBins = 30;
  double nTrkLow = 0.;
  double nTrkHigh = 100;

  int nHiBinBins = 200;
  int hiBinLow = 0;
  int hiBinHigh = 200;

  int nEtaBins = 20;
  double etaMin = -2.0;
  double etaMax = 2.0;

  int nPhiBins = 20;
  double phiMin = -pi;
  double phiMax = pi;

  int nPtBins = 60;
  double ptMin = 0.;
  double ptMax = 200;
  
  std::cout << "configuring histograms" << std::endl;
  TH1D *nTrkRandomCone_data = new TH1D("nTrkRandomCone_data","nTrk in random cone (data, r = 0.4); nTrk; Entries",nTrkBins,nTrkLow,nTrkHigh);
  TH1D *nTrkRandomCone_mc = new TH1D("nTrkRandomCone_mc","nTrk in random cone (mc, r = 0.4); nTrk; Entries",nTrkBins,nTrkLow,nTrkHigh);

  TH2D *nTrkRandomCone_hiBin_data = new TH2D("nTrkRandomCone_hiBin_data","nTrk in random cone vs hiBin (data, r = 0.4)",nTrkBins,nTrkLow,nTrkHigh,nHiBinBins,hiBinLow,hiBinHigh);
  TH2D *nTrkRandomCone_hiBin_mc = new TH2D("nTrkRandomCone_hiBin_mc","nTrk in random cone vs hiBin (mc, r = 0.4)",nTrkBins,nTrkLow,nTrkHigh,nHiBinBins,hiBinLow,hiBinHigh);

  TH2D *ptRandomCone_hiBin_data = new TH2D("ptRandomCone_hiBin_data","pT in random cone vs hiBin (data, r = 0.4)", nPtBins,ptMin,ptMax,nHiBinBins,hiBinLow,hiBinHigh);
  TH2D *ptRandomCone_hiBin_mc = new TH2D("ptRandomCone_hiBin_mc","pT in random cone vs hiBin (mc, r = 0.4)", nPtBins,ptMin,ptMax,nHiBinBins,hiBinLow,hiBinHigh);

  TH1D *randEta_mc = new TH1D("randEta_mc","Random #eta; #eta; Entries",nEtaBins,etaMin,etaMax);
  TH1D *randEta_data = new TH1D("randEta_data","Random #eta; #eta; Entries",nEtaBins,etaMin,etaMax);

  TH1D *randPhi_mc = new TH1D("randPhi_mc","Random #phi; #phi; Entries",nPhiBins,phiMin,phiMax);
  TH1D *randPhi_data = new TH1D("randPhi_data","Random #phi; #phi; Entries",nPhiBins,phiMin,phiMax);

  std::cout << "configuring event filters" << std::endl;
  const int NEventFilters_mc = 5;
  std::string eventFilters_mc[NEventFilters_mc] = {"pprimaryVertexFilter", "HBHENoiseFilterResultRun2Loose", "collisionEventSelectionAODv2", "phfCoincFilter2Th4", "pclusterCompatibilityFilter"};
  em_mc->regEventFilter(NEventFilters_mc, eventFilters_mc);

  const int NEventFilters_data = 2;
  std::string eventFilters_data[NEventFilters_data] = {"pprimaryVertexFilter", "pclusterCompatibilityFilter"};
  em_data->regEventFilter(NEventFilters_data,eventFilters_data);

  int N_loop = 3;
  

  std::cout << "starting mc event scan" << std::endl;
  std::cout << "please wait" << std::endl;
  int evi_frac = 0;
  for(int i = 0 ; i < nEvents_mc; i++){

    em_mc->getEvent(i);

    
    
    if((100*i / nEvents_mc) % 20 == 0 && (100*i / nEvents_mc) > evi_frac){
      //std::cout << evi_frac << "% complete" << std::endl;
      std::cout << "..." << std::endl;
    }
    evi_frac = 100*i/nEvents_mc;

    if(em_mc->pthat < 15. && em_mc->pthat > 20.) continue;
    if(fabs(em_mc->vz) > 15.) continue;
    if(em_mc->checkEventFilter()) continue;
    if(em_mc->hiHF > 6000) continue;

    //double w = em_mc->weight;
    double w = 1.;
    int nTrk_i = em_mc->ntrk;

    

    for(int k = 0; k < N_loop; k++){
    
      double randEta_k = 3.2*randomGenerator->Rndm() - 1.6;
      double randPhi_k = 2*pi*randomGenerator->Rndm() - pi;
      randEta_mc->Fill(randEta_k,w);
      randPhi_mc->Fill(randPhi_k,w);
      int nTrkRandomCone_k = 0;
      double ptRandomCone_k = 0.;
    
   
      for(int j = 0; j < nTrk_i; j++){
	double trkPt_j = em_mc->trkpt[j];
	double trkEta_j = em_mc->trketa[j];
	double trkPhi_j = em_mc->trkphi[j];
	double dR_kj = getDr(trkEta_j,trkPhi_j,randEta_k,randPhi_k);
	if(trkPt_j > trkPtMin && dR_kj < dR_max) {

	  nTrkRandomCone_k++;
	  ptRandomCone_k += trkPt_j;
	
	  //std::cout << "event " << i << ", in-random-cone track " << j << " (pt, eta, phi) = (" << trkPt_j << ", " << trkEta_j << ", " << trkPhi_j << ")" << std::endl;
	
	}
      }

      nTrkRandomCone_mc->Fill(nTrkRandomCone_k,w);
      nTrkRandomCone_hiBin_mc->Fill(nTrkRandomCone_k,em_mc->hiBin,w);
      ptRandomCone_hiBin_mc->Fill(ptRandomCone_k,em_mc->hiBin,w);
    
    }
  }
  std::cout << "mc event scan complete" << std::endl;

  std::cout << "starting data event scan" << std::endl;
  std::cout << "please wait" << std::endl;
  evi_frac = 0;
  for(int i = 0 ; i < nEvents_data; i++){

    em_data->getEvent(i);

    if((100*i / nEvents_mc) % 20 == 0 && (100*i / nEvents_mc) > evi_frac){
      std::cout << "..." << std::endl;
    }
    evi_frac = 100*i/nEvents_data;

    if(fabs(em_data->vz) > 15.) continue;
    if(em_data->checkEventFilter()) continue;
    if(em_data->hiHF > 6000) continue;

    double w = 1;
    int nTrk_i = em_data->ntrk;
    
    for(int k = 0; k < N_loop; k++){

      double randEta_k = 3.2*randomGenerator->Rndm() - 1.6;
      double randPhi_k = 2*pi*randomGenerator->Rndm() - pi;
      int nTrkRandomCone_k = 0;
      double ptRandomCone_k = 0.;


      //std::cout << "nTrk = " << nTrk_i << std::endl;
      for(int j = 0; j < nTrk_i; j++){
	double trkPt_j = em_data->trkPt->at(j);
	double trkEta_j = em_data->trkEta->at(j);
	double trkPhi_j = em_data->trkPhi->at(j);
	double dR_kj = getDr(trkEta_j,trkPhi_j,randEta_k,randPhi_k);
      
	if(trkPt_j > trkPtMin && dR_kj < dR_max) {
	  //std::cout << "event " << i << ", in-random-cone track " << j << " (pt, eta, phi) = (" << trkPt_j << ", " << trkEta_j << ", " << trkPhi_j << ")" << std::endl;
	  nTrkRandomCone_k++;
	  ptRandomCone_k += trkPt_j;
	}
      }
    
      nTrkRandomCone_data->Fill(nTrkRandomCone_k,w);
      nTrkRandomCone_hiBin_data->Fill(nTrkRandomCone_k,em_data->hiBin,w);
      ptRandomCone_hiBin_data->Fill(ptRandomCone_k,em_data->hiBin,w);

    }
    
  }
  std::cout << "data event scan complete" << std::endl;

  std::cout << "begin art mode" << std::endl;

  double hiBin_proj_low_data = 0.;
  double hiBin_proj_high_data = 160.;

  double shift = 10;

  double hiBin_proj_low_mc = hiBin_proj_low_data + shift;
  double hiBin_proj_high_mc = hiBin_proj_high_data + shift;
  
  TH1D *draw_mc = (TH1D*) nTrkRandomCone_hiBin_mc->ProjectionX("draw_mc",nTrkRandomCone_hiBin_mc->ProjectionY()->FindBin(hiBin_proj_low_mc),nTrkRandomCone_hiBin_mc->ProjectionY()->FindBin(hiBin_proj_high_mc));
  TH1D *draw_data = (TH1D*) nTrkRandomCone_hiBin_data->ProjectionX("draw_data",nTrkRandomCone_hiBin_data->ProjectionY()->FindBin(hiBin_proj_low_data),nTrkRandomCone_hiBin_data->ProjectionY()->FindBin(hiBin_proj_high_data));

  // TH1D *draw_mc = (TH1D*) ptRandomCone_hiBin_mc->ProjectionX("draw_mc",ptRandomCone_hiBin_mc->ProjectionY()->FindBin(hiBin_proj_low_mc),ptRandomCone_hiBin_mc->ProjectionY()->FindBin(hiBin_proj_high_mc));
  // TH1D *draw_data = (TH1D*) ptRandomCone_hiBin_data->ProjectionX("draw_data",ptRandomCone_hiBin_data->ProjectionY()->FindBin(hiBin_proj_low_data),ptRandomCone_hiBin_data->ProjectionY()->FindBin(hiBin_proj_high_data));

  //draw_mc->SetTitle("pT in random cone (#DeltaR = 0.4)");
  //draw_mc->SetTitle("nTrk in random cone (#DeltaR = 0.4)");
  draw_mc->SetTitle("");
  draw_data->SetTitle("");
  draw_mc->SetStats(0);
  draw_data->SetStats(0);
  
  
  draw_mc->Scale(1./draw_mc->Integral());
  draw_data->Scale(1./draw_data->Integral());

  divideByBinwidth(draw_mc);
  divideByBinwidth(draw_data);

  draw_mc->SetLineColor(kBlue-4);
  draw_data->SetLineColor(kRed-4);

  draw_mc->SetLineWidth(2);
  draw_data->SetLineWidth(2);

  TH1D *r = (TH1D*) draw_data->Clone("r");
  r->Divide(draw_data,draw_mc,1,1,"");

  r->GetYaxis()->SetLabelSize(0.06);
  r->GetXaxis()->SetLabelSize(0.06);
  r->GetYaxis()->SetTitleSize(0.08);
  r->GetXaxis()->SetTitleSize(0.08);

  TLatex *la = new TLatex();
  la->SetTextFont(62);
  la->SetTextSize(0.05);

  TCanvas *canv = new TCanvas("canv","canv",700,700);
  canv->cd();
  //TPad *pad1 = new TPad("pad1","pad1",0,0,1,1);
  TPad *pad1 = new TPad("pad1","pad1",0,0.4,1,1);
  TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.4);
  pad1->SetBottomMargin(0);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  pad1->SetLeftMargin(0.15);
  pad2->SetLeftMargin(0.15);
  pad1->Draw();
  pad2->Draw();
  pad1->cd();
  
  

  draw_mc->GetYaxis()->SetRangeUser(0,0.07);
  draw_mc->GetYaxis()->SetTitle("1/#it{N}^{cone}_{tot} d#it{N}^{cone}/d#it{N}^{trk}_{in-cone}");
  draw_mc->GetYaxis()->SetTitleSize(0.07);
  
  draw_mc->Draw("hist");
  draw_data->Draw("hist same");

  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.6,0.7, Form("PbPb Cent. %2.0f - %2.0f %%",hiBin_proj_low_data/2.,hiBin_proj_high_data/2.));
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.6,0.63,Form("MC Cent.   %2.0f - %2.0f %%",hiBin_proj_low_mc/2.,hiBin_proj_high_mc/2.));
  
  pad2->cd();
  r->GetYaxis()->SetRangeUser(0,2);
  r->GetYaxis()->SetTitle("DATA / MC");
  //r->GetXaxis()->SetTitle("Random Cone p_{T} [GeV]");
  r->GetXaxis()->SetTitle("In-cone tracks, #it{N}^{trk}_{in-cone}");
  r->Draw();
  
  

  //////////////////////////////////////////////////////
  std::cout << "ending nTrkRandomCone()" << std::endl;
  
}
