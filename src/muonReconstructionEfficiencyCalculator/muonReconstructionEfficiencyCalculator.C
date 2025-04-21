#include "../../headers/goldenFileNames.h"
#include "../../headers/functions/divideByBinwidth.h"

TFile *f1, *f2;
TH1D *n1, *n2, *n3, *n4, *n0;
TH1D *d1, *d2, *d3, *d4, *d0;
TH1D *N1, *N2, *N3, *N4, *N0;
TH1D *D1, *D2, *D3, *D4, *D0;

void muonReconstructionEfficiencyCalculator(bool doReco       = true,
					    bool doID         = false,
					    bool doRecoPlusID = false){

  TLine *li = new TLine();
  li->SetLineStyle(7);
  
  // f1 = TFile::Open(goldenFile_PYTHIA_muonReco_bJets);
  // f2 = TFile::Open(goldenFile_PYTHIAHYDJET_DiJet_muonReco_bJets);

  TString n_string = "";
  TString d_string = "";
  TString N_string = "";
  TString D_string = "";

  if(doReco){
    n_string = "h_matchedGenMuonPt";
    d_string = "h_inclGenMuonPt";
    N_string = "h_matchedGenMuonEta";
    D_string = "h_inclGenMuonEta";
  }
  else if(doID){
    n_string = "h_tightRecoMuonPt";
    d_string = "h_matchedRecoMuonPt";
    N_string = "h_tightRecoMuonEta";
    D_string = "h_matchedRecoMuonEta";
  }
  else if(doRecoPlusID){
    n_string = "h_tightRecoMuonPt";
    d_string = "h_inclGenMuonPt";
    N_string = "h_tightRecoMuonEta";
    D_string = "h_matchedRecoMuonEta";
  }
  else{};
  
  f1 = TFile::Open(goldenFile_PYTHIA_muonReco);
  f2 = TFile::Open(goldenFile_PYTHIAHYDJET_DiJet_muonReco);

  f1->GetObject(n_string,n0);
  f1->GetObject(d_string,d0);

  f2->GetObject(Form("%s_C1",n_string.Data()),n1);
  f2->GetObject(Form("%s_C1",d_string.Data()),d1);

  f2->GetObject(Form("%s_C2",n_string.Data()),n2);
  f2->GetObject(Form("%s_C2",d_string.Data()),d2);

  f2->GetObject(Form("%s_C3",n_string.Data()),n3);
  f2->GetObject(Form("%s_C3",d_string.Data()),d3);

  f2->GetObject(Form("%s_C4",n_string.Data()),n4);
  f2->GetObject(Form("%s_C4",d_string.Data()),d4);

  f1->GetObject(N_string,N0);
  f1->GetObject(D_string,D0);

  f2->GetObject(Form("%s_C1",N_string.Data()),N1);
  f2->GetObject(Form("%s_C1",D_string.Data()),D1);

  f2->GetObject(Form("%s_C2",N_string.Data()),N2);
  f2->GetObject(Form("%s_C2",D_string.Data()),D2);

  f2->GetObject(Form("%s_C3",N_string.Data()),N3);
  f2->GetObject(Form("%s_C3",D_string.Data()),D3);

  f2->GetObject(Form("%s_C4",N_string.Data()),N4);
  f2->GetObject(Form("%s_C4",D_string.Data()),D4);

  const int NPtEdges = 8;
  double newPtAxis[NPtEdges] = {5,6,7,8,9,12,14,40};

  const int NEtaEdges = 6;
  double newEtaAxis[NEtaEdges] = {-2,-1.2,-0.4,0.4,1.2,2};

  // pt histograms
  TH1D *n0r = (TH1D*) n0->Rebin(NPtEdges-1,"n0r",newPtAxis);
  TH1D *d0r = (TH1D*) d0->Rebin(NPtEdges-1,"d0r",newPtAxis);
  
  TH1D *n1r = (TH1D*) n1->Rebin(NPtEdges-1,"n1r",newPtAxis);
  TH1D *d1r = (TH1D*) d1->Rebin(NPtEdges-1,"d1r",newPtAxis);

  TH1D *n2r = (TH1D*) n2->Rebin(NPtEdges-1,"n2r",newPtAxis);
  TH1D *d2r = (TH1D*) d2->Rebin(NPtEdges-1,"d2r",newPtAxis);

  TH1D *n3r = (TH1D*) n3->Rebin(NPtEdges-1,"n3r",newPtAxis);
  TH1D *d3r = (TH1D*) d3->Rebin(NPtEdges-1,"d3r",newPtAxis);

  TH1D *n4r = (TH1D*) n4->Rebin(NPtEdges-1,"n4r",newPtAxis);
  TH1D *d4r = (TH1D*) d4->Rebin(NPtEdges-1,"d4r",newPtAxis);

  // TH1D *n1r = (TH1D*) n1->Clone("n1r");
  // TH1D *d1r = (TH1D*) d1->Clone("d1r");

  // TH1D *n2r = (TH1D*) n2->Clone("n2r");
  // TH1D *d2r = (TH1D*) d2->Clone("d2r");

  // TH1D *n3r = (TH1D*) n3->Clone("n3r");
  // TH1D *d3r = (TH1D*) d3->Clone("d3r");

  // eta histograms
  TH1D *N0r = (TH1D*) N0->Rebin(NEtaEdges-1,"N0r",newEtaAxis);
  TH1D *D0r = (TH1D*) D0->Rebin(NEtaEdges-1,"D0r",newEtaAxis);

  TH1D *N1r = (TH1D*) N1->Rebin(NEtaEdges-1,"N1r",newEtaAxis);
  TH1D *D1r = (TH1D*) D1->Rebin(NEtaEdges-1,"D1r",newEtaAxis);

  TH1D *N2r = (TH1D*) N2->Rebin(NEtaEdges-1,"N2r",newEtaAxis);
  TH1D *D2r = (TH1D*) D2->Rebin(NEtaEdges-1,"D2r",newEtaAxis);

  TH1D *N3r = (TH1D*) N3->Rebin(NEtaEdges-1,"N3r",newEtaAxis);
  TH1D *D3r = (TH1D*) D3->Rebin(NEtaEdges-1,"D3r",newEtaAxis);

  TH1D *N4r = (TH1D*) N4->Rebin(NEtaEdges-1,"N4r",newEtaAxis);
  TH1D *D4r = (TH1D*) D4->Rebin(NEtaEdges-1,"D4r",newEtaAxis);

  // TH1D *N1r = (TH1D*) N1->Clone("N1r");
  // TH1D *D1r = (TH1D*) D1->Clone("D1r");

  // TH1D *N2r = (TH1D*) N2->Clone("N2r");
  // TH1D *D2r = (TH1D*) D2->Clone("D2r");

  // TH1D *N3r = (TH1D*) N3->Clone("N3r");
  // TH1D *D3r = (TH1D*) D3->Clone("D3r");
  
  divideByBinwidth(n0r);
  divideByBinwidth(d0r);
  divideByBinwidth(n1r);
  divideByBinwidth(d1r);
  divideByBinwidth(n2r);
  divideByBinwidth(d2r);
  divideByBinwidth(n3r);
  divideByBinwidth(d3r);
  divideByBinwidth(n4r);
  divideByBinwidth(d4r);

  divideByBinwidth(N0r);
  divideByBinwidth(D0r);
  divideByBinwidth(N1r);
  divideByBinwidth(D1r);
  divideByBinwidth(N2r);
  divideByBinwidth(D2r);
  divideByBinwidth(N3r);
  divideByBinwidth(D3r);
  divideByBinwidth(N4r);
  divideByBinwidth(D4r);

  TGraphAsymmErrors *g0 = new TGraphAsymmErrors();
  g0->Divide(n0r,d0r,"cl=0.683 b(1,1) mode");

  TGraphAsymmErrors *g1 = new TGraphAsymmErrors();
  g1->Divide(n1r,d1r,"cl=0.683 b(1,1) mode");

  TGraphAsymmErrors *g2 = new TGraphAsymmErrors();
  g2->Divide(n2r,d2r,"cl=0.683 b(1,1) mode");

  TGraphAsymmErrors *g3 = new TGraphAsymmErrors();
  g3->Divide(n3r,d3r,"cl=0.683 b(1,1) mode");

  TGraphAsymmErrors *g4 = new TGraphAsymmErrors();
  g4->Divide(n4r,d4r,"cl=0.683 b(1,1) mode");

  TGraphAsymmErrors *G0 = new TGraphAsymmErrors();
  G0->Divide(N0r,D0r,"cl=0.683 b(1,1) mode");

  TGraphAsymmErrors *G1 = new TGraphAsymmErrors();
  G1->Divide(N1r,D1r,"cl=0.683 b(1,1) mode");

  TGraphAsymmErrors *G2 = new TGraphAsymmErrors();
  G2->Divide(N2r,D2r,"cl=0.683 b(1,1) mode");

  TGraphAsymmErrors *G3 = new TGraphAsymmErrors();
  G3->Divide(N3r,D3r,"cl=0.683 b(1,1) mode");

  TGraphAsymmErrors *G4 = new TGraphAsymmErrors();
  G4->Divide(N4r,D4r,"cl=0.683 b(1,1) mode");


  g0->SetMarkerStyle(20);
  g0->SetMarkerColor(kBlack);
  g0->SetLineColor(kBlack);

  g4->SetMarkerStyle(21);
  g4->SetMarkerColor(kRed-4);
  g4->SetLineColor(kRed-4);

  g3->SetMarkerStyle(22);
  g3->SetMarkerColor(kBlue-4);
  g3->SetLineColor(kBlue-4);

  g2->SetMarkerStyle(23);
  g2->SetMarkerColor(kGreen+2);
  g2->SetLineColor(kGreen+2);

  g1->SetMarkerStyle(34);
  g1->SetMarkerColor(kMagenta-9);
  g1->SetLineColor(kMagenta-9);

  
  G0->SetMarkerStyle(20);
  G0->SetMarkerColor(kBlack);
  G0->SetLineColor(kBlack);

  G4->SetMarkerStyle(21);
  G4->SetMarkerColor(kRed-4);
  G4->SetLineColor(kRed-4);

  G3->SetMarkerStyle(22);
  G3->SetMarkerColor(kBlue-4);
  G3->SetLineColor(kBlue-4);

  G2->SetMarkerStyle(23);
  G2->SetMarkerColor(kGreen+2);
  G2->SetLineColor(kGreen+2);

  G1->SetMarkerStyle(34);
  G1->SetMarkerColor(kMagenta-9);
  G1->SetLineColor(kMagenta-9);

  TMultiGraph *mg_pt = new TMultiGraph();

  mg_pt->Add(g0);
  mg_pt->Add(g1);
  mg_pt->Add(g2);
  mg_pt->Add(g3);
  mg_pt->Add(g4);

  TMultiGraph *mg_eta = new TMultiGraph();

  mg_eta->Add(G0);
  mg_eta->Add(G1);
  mg_eta->Add(G2);
  mg_eta->Add(G3);
  mg_eta->Add(G4);
  
  TString yTitle = "";
  if(doReco) yTitle = "Muon Reco Efficiency, #varepsilon_{reco}";
  else if(doID) yTitle = "Muon ID Efficiency, #varepsilon_{ID}";
  

  TCanvas *c_pt = new TCanvas("c_pt","c_pt",700,700);
  c_pt->cd();
  TPad *p_pt = new TPad("p_pt","p_pt",0,0,1,1);
  p_pt->SetLeftMargin(0.2);
  p_pt->SetBottomMargin(0.2);
  p_pt->Draw();
  p_pt->cd();


  mg_pt->GetXaxis()->SetRangeUser(0,newPtAxis[NPtEdges-1]);
  mg_pt->GetYaxis()->SetRangeUser(0.5,1);
  mg_pt->GetXaxis()->SetTitleSize(0.05);
  mg_pt->GetYaxis()->SetTitleSize(0.05);
  mg_pt->GetXaxis()->SetLabelSize(0.04);
  mg_pt->GetYaxis()->SetLabelSize(0.04);
  mg_pt->GetYaxis()->SetTitle(yTitle);
  mg_pt->GetXaxis()->SetTitle("Muon #font[52]{p}_{T} [GeV]");
  mg_pt->SetTitle("");
  mg_pt->Draw("AP ep");
  li->DrawLine(14,0.5,14,1);
  TLatex *la = new TLatex();
  la->SetTextSize(0.032);
  la->SetTextFont(42);
  TString sampleName = "#scale[1.2]{#font[62]{CMS}} #font[52]{Preliminary}                        #sqrt{s_{NN}} = 5.02 TeV";
  TString muonEtaInfo = "";
  TString muonPtInfo = "";
  if(doReco){
    muonEtaInfo = "#splitline{|#it{#eta}^{#it{#mu}}| < 2.0}{#it{#DeltaR}(reco,gen) < 0.03}";
    muonPtInfo = "#splitline{#it{p}_{T}^{#it{#mu}} > 14 GeV}{#it{#DeltaR}(reco,gen) < 0.03}";
  }
  else if(doID){
    muonEtaInfo = "#splitline{|#it{#eta}^{#it{#mu}}| < 2.0}{Tight Muon ID}";
    muonPtInfo = "#splitline{#it{p}_{T}^{#it{#mu}} > 14 GeV}{Tight Muon ID}";
  }

  
  la->DrawLatexNDC(0.21,0.92,sampleName);
  la->SetTextSize(0.03);

  //la->DrawLatexNDC(0.21,0.9,triggerName);
  la->DrawLatexNDC(0.5,0.5,muonEtaInfo);
  //la->DrawLatexNDC(0.25,0.46,"Tight muon ID");
  //la->DrawLatexNDC(0.25,0.42,"Tagged to #font[52]{b}-jets, #font[52]{p}_{T}^{jet} > 60 GeV, |#eta^{jet}| < 1.6");

  TLegend *leg = new TLegend(0.45,0.25,0.78,0.38);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.032);
  leg->AddEntry(g0,"PYTHIA","p");
  leg->AddEntry(g4,"PYTHIA+HYDJET 50-90%","p");
  leg->AddEntry(g3,"PYTHIA+HYDJET 30-50%","p");
  leg->AddEntry(g2,"PYTHIA+HYDJET 10-30%","p");
  leg->AddEntry(g1,"PYTHIA+HYDJET 0-10%","p");
  leg->Draw();

  TCanvas *c_eta = new TCanvas("c_eta","c_eta",700,700);
  c_eta->cd();
  TPad *p_eta = new TPad("p_eta","p_eta",0,0,1,1);
  p_eta->SetLeftMargin(0.2);
  p_eta->SetBottomMargin(0.2);
  p_eta->Draw();
  p_eta->cd();

  mg_eta->GetXaxis()->SetRangeUser(newEtaAxis[0],newEtaAxis[NEtaEdges-1]);
  mg_eta->GetYaxis()->SetRangeUser(0.5,1);
  mg_eta->GetXaxis()->SetTitleSize(0.05);
  mg_eta->GetYaxis()->SetTitleSize(0.05);
  mg_eta->GetXaxis()->SetLabelSize(0.04);
  mg_eta->GetYaxis()->SetLabelSize(0.04);
  mg_eta->GetYaxis()->SetTitle(yTitle);
  mg_eta->GetXaxis()->SetTitle("Muon #eta");
  mg_eta->SetTitle("");
  mg_eta->Draw("AP ep");
  li->DrawLine(14,0.5,14,1);
  la->SetTextSize(0.032);
  la->DrawLatexNDC(0.21,0.92,sampleName);
  la->SetTextSize(0.03);
  
  //la->DrawLatexNDC(0.21,0.9,triggerName);
  la->DrawLatexNDC(0.5,0.5,muonPtInfo);
  //la->DrawLatexNDC(0.25,0.46,"Tight muon ID");
  //la->DrawLatexNDC(0.25,0.42,"Tagged to #font[52]{b}-jets, #font[52]{p}_{T}^{jet} > 60 GeV, |#eta^{jet}| < 1.6");


  leg->Draw();

  TString ptSaveString = "";
  TString etaSaveString = "";

  if(doReco){
    ptSaveString = "muonPt_reco.pdf";
    etaSaveString = "muonEta_reco.pdf";
  }
  else if(doID){
    ptSaveString = "muonPt_ID.pdf";
    etaSaveString = "muonEta_ID.pdf";
  }

  c_pt->SaveAs(Form("../../figures/muonReconstructionEfficiency/%s",ptSaveString.Data()));
  c_eta->SaveAs(Form("../../figures/muonReconstructionEfficiency/%s",etaSaveString.Data()));


}
