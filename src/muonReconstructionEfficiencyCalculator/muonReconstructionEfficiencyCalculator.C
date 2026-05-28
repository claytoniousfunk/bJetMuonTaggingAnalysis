#include "../../headers/goldenFileNames.h"
#include "../../headers/functions/divideByBinwidth.h"

TFile *f1, *f2;
TH1D *n1, *n2, *n3, *n4, *n0;
TH1D *d1, *d2, *d3, *d4, *d0;
TH1D *N1, *N2, *N3, *N4, *N0;
TH1D *D1, *D2, *D3, *D4, *D0;

void muonReconstructionEfficiencyCalculator(bool doReco       = false,
					    bool doID         = false,
					    bool doRecoPlusID = true){

  TLine *li = new TLine();
  li->SetLineStyle(7);

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
    D_string = "h_inclGenMuonEta";
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

  // const int NPtEdges = 10;
  // double newPtAxis[NPtEdges] = {5,6,7,8,9,10,11,12,15,40};

  // const int NPtEdges = 15;
  // double newPtAxis[NPtEdges] = {15,16,17,18,19,20,21,22,23,24,25,30,40,50,100};

  const int NPtEdges = 3;
  double newPtAxis[NPtEdges] = {0,15,100};

  // const int NPtEdges = 5;
  // double newPtAxis[NPtEdges] = {10,11,12,15,40};

  // const int NPtEdges = 2;
  // double newPtAxis[NPtEdges] = {15,40};

  
  const int NEtaEdges = 6;
  double newEtaAxis[NEtaEdges] = {-2,-1.2,-0.4,0.4,1.2,2};

  // const int NEtaEdges = 2;
  // double newEtaAxis[NEtaEdges] = {-2,2};

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
  
  // divideByBinwidth(n0r);
  // divideByBinwidth(d0r);
  // divideByBinwidth(n1r);
  // divideByBinwidth(d1r);
  // divideByBinwidth(n2r);
  // divideByBinwidth(d2r);
  // divideByBinwidth(n3r);
  // divideByBinwidth(d3r);
  // divideByBinwidth(n4r);
  // divideByBinwidth(d4r);

  // divideByBinwidth(N0r);
  // divideByBinwidth(D0r);
  // divideByBinwidth(N1r);
  // divideByBinwidth(D1r);
  // divideByBinwidth(N2r);
  // divideByBinwidth(D2r);
  // divideByBinwidth(N3r);
  // divideByBinwidth(D3r);
  // divideByBinwidth(N4r);
  // divideByBinwidth(D4r);

  

  // for(int i = 0; i < n0r->GetSize(); i++){
  //   //std::cout << "i = " << i << "\n";
  //   // std::cout << "n0r(" << i << ") = " << n0r->GetBinContent(i) << "\n";
  //   // std::cout << "d0r(" << i << ") = " << d0r->GetBinContent(i) << "\n\n";

  //   // std::cout << "n2r(" << i << ") = " << n2r->GetBinContent(i) << "\n";
  //   // std::cout << "d2r(" << i << ") = " << d2r->GetBinContent(i) << "\n\n";

    
  //   if(i==0) {
  //     std::cout << "resetting underflow bin...\n";
  //     n0r->SetBinContent(i,0);
  //     d0r->SetBinContent(i,0);
  //     n1r->SetBinContent(i,0);
  //     d1r->SetBinContent(i,0);
  //     n2r->SetBinContent(i,0);
  //     d2r->SetBinContent(i,0);
  //     n3r->SetBinContent(i,0);
  //     d3r->SetBinContent(i,0);
  //     n4r->SetBinContent(i,0);
  //     d4r->SetBinContent(i,0);
  //     N0r->SetBinContent(i,0);
  //     D0r->SetBinContent(i,0);
  //     N1r->SetBinContent(i,0);
  //     D1r->SetBinContent(i,0);
  //     N2r->SetBinContent(i,0);
  //     D2r->SetBinContent(i,0);
  //     N3r->SetBinContent(i,0);
  //     D3r->SetBinContent(i,0);
  //     N4r->SetBinContent(i,0);
  //     D4r->SetBinContent(i,0);
  //     // std::cout << "n0r(" << i << ") = " << n0r->GetBinContent(i) << "\n";
  //     // std::cout << "d0r(" << i << ") = " << d0r->GetBinContent(i) << "\n\n";
  //     std::cout << "n2r(" << i << ") = " << n2r->GetBinContent(i) << "\n";
  //     std::cout << "d2r(" << i << ") = " << d2r->GetBinContent(i) << "\n\n";
  //   }

    
  // }
  
  // TGraphAsymmErrors *g0 = new TGraphAsymmErrors();
  // g0->Divide(n0r,d0r,"cl=0.683 b(1,1) mode");

  // g0->Draw();

  // n2r->SetLineColor(kRed-4);
  // d2r->SetLineColor(kBlue-4);
  // d2r->Draw();
  // n2r->Draw("same");

  
  /////////////////////////////////////////////////////////////////////
  
  // TGraphAsymmErrors *g0 = new TGraphAsymmErrors();
  // g0->Divide(n0r,d0r,"cl=0.683 b(1,1) mode");

  // TGraphAsymmErrors *g1 = new TGraphAsymmErrors();
  // g1->Divide(n1r,d1r,"cl=0.683 b(1,1) mode");

  // TGraphAsymmErrors *g2 = new TGraphAsymmErrors();
  // g2->Divide(n2r,d2r,"cl=0.683 b(1,1) mode");

  // TGraphAsymmErrors *g3 = new TGraphAsymmErrors();
  // g3->Divide(n3r,d3r,"cl=0.683 b(1,1) mode");

  // TGraphAsymmErrors *g4 = new TGraphAsymmErrors();
  // g4->Divide(n4r,d4r,"cl=0.683 b(1,1) mode");

  // TGraphAsymmErrors *G0 = new TGraphAsymmErrors();
  // G0->Divide(N0r,D0r,"cl=0.683 b(1,1) mode");

  // TGraphAsymmErrors *G1 = new TGraphAsymmErrors();
  // G1->Divide(N1r,D1r,"cl=0.683 b(1,1) mode");

  // TGraphAsymmErrors *G2 = new TGraphAsymmErrors();
  // G2->Divide(N2r,D2r,"cl=0.683 b(1,1) mode");

  // TGraphAsymmErrors *G3 = new TGraphAsymmErrors();
  // G3->Divide(N3r,D3r,"cl=0.683 b(1,1) mode");

  // TGraphAsymmErrors *G4 = new TGraphAsymmErrors();
  // G4->Divide(N4r,D4r,"cl=0.683 b(1,1) mode");

  /////////////////////////////////////////////////////////////////////

  TH1D *g0 = (TH1D*) n0r->Clone("g0");
  n0r->SetBinContent(1,-1);
  g0->Divide(n0r,d0r,1,1,"B");

  TH1D *g1 = (TH1D*) n1r->Clone("g1");
  g1->Divide(n1r,d1r,1,1,"B");

  TH1D *g2 = (TH1D*) n2r->Clone("g2");
  g2->Divide(n2r,d2r,1,1,"B");

  TH1D *g3 = (TH1D*) n3r->Clone("g3");
  g3->Divide(n3r,d3r,1,1,"B");

  TH1D *g4 = (TH1D*) n4r->Clone("g4");
  g4->Divide(n4r,d4r,1,1,"B");

  TH1D *G0 = (TH1D*) N0r->Clone("G0");
  G0->Divide(N0r,D0r,1,1,"B");

  TH1D *G1 = (TH1D*) N1r->Clone("G1");
  G1->Divide(N1r,D1r,1,1,"B");

  TH1D *G2 = (TH1D*) N2r->Clone("G2");
  G2->Divide(N2r,D2r,1,1,"B");

  TH1D *G3= (TH1D*) N3r->Clone("G3");
  G3->Divide(N3r,D3r,1,1,"B");

  TH1D *G4= (TH1D*) N4r->Clone("G4");
  G4->Divide(N4r,D4r,1,1,"B");

  ////////////////////////////////////////////////////////////////////

  int lastBin = n0r->GetSize()-2;
  std::cout << "integrated efficiency (pT > 15): \n";
  std::cout << "  pp = " << n0r->GetBinContent(lastBin)/d0r->GetBinContent(lastBin) << "\n";
  std::cout << "  C4 = " << n4r->GetBinContent(lastBin)/d4r->GetBinContent(lastBin) << "\n";
  std::cout << "  C3 = " << n3r->GetBinContent(lastBin)/d3r->GetBinContent(lastBin) << "\n";
  std::cout << "  C2 = " << n2r->GetBinContent(lastBin)/d2r->GetBinContent(lastBin) << "\n";
  std::cout << "  C1 = " << n1r->GetBinContent(lastBin)/d1r->GetBinContent(lastBin) << "\n";
  



  ////////////////////////////////////////////////////////////////////

  g0->SetMarkerStyle(24);
  g0->SetMarkerColor(kBlack);
  g0->SetLineColor(kBlack);

  g4->SetMarkerStyle(33);
  g4->SetMarkerColor(kBlack);
  g4->SetLineColor(kBlack);

  g3->SetMarkerStyle(21);
  g3->SetMarkerColor(kBlue-4);
  g3->SetLineColor(kBlue-4);

  g2->SetMarkerStyle(34);
  g2->SetMarkerColor(kGreen+2);
  g2->SetLineColor(kGreen+2);

  g1->SetMarkerStyle(47);
  g1->SetMarkerColor(kRed-4);
  g1->SetLineColor(kRed-4);

  
  G0->SetMarkerStyle(24);
  G0->SetMarkerColor(kBlack);
  G0->SetLineColor(kBlack);

  G4->SetMarkerStyle(33);
  G4->SetMarkerColor(kBlack);
  G4->SetLineColor(kBlack);

  G3->SetMarkerStyle(21);
  G3->SetMarkerColor(kBlue-4);
  G3->SetLineColor(kBlue-4);

  G2->SetMarkerStyle(34);
  G2->SetMarkerColor(kGreen+2);
  G2->SetLineColor(kGreen+2);

  G1->SetMarkerStyle(47);
  G1->SetMarkerColor(kRed-4);
  G1->SetLineColor(kRed-4);

  TMultiGraph *mg_pt = new TMultiGraph();

  // mg_pt->Add(g0);
  // mg_pt->Add(g1);
  // mg_pt->Add(g2);
  // mg_pt->Add(g3);
  // mg_pt->Add(g4);

  TMultiGraph *mg_eta = new TMultiGraph();

  // mg_eta->Add(G0);
  // mg_eta->Add(G1);
  // mg_eta->Add(G2);
  // mg_eta->Add(G3);
  // mg_eta->Add(G4);
  
  TString yTitle = "";
  if(doReco) yTitle = "Muon Reco Efficiency, #varepsilon_{reco}";
  else if(doID) yTitle = "Muon ID Efficiency, #varepsilon_{ID}";
  else if(doRecoPlusID) yTitle = "Muon Reco Efficiency, #varepsilon_{reco}";
  

  TCanvas *c_pt = new TCanvas("c_pt","c_pt",700,700);
  c_pt->cd();
  TPad *p_pt = new TPad("p_pt","p_pt",0,0,1,1);
  p_pt->SetLeftMargin(0.2);
  p_pt->SetBottomMargin(0.2);
  p_pt->Draw();
  p_pt->cd();


  g0->GetXaxis()->SetRangeUser(0,newPtAxis[NPtEdges-1]);
  g0->GetYaxis()->SetRangeUser(0.5,1);
  g0->GetXaxis()->SetTitleSize(0.05);
  g0->GetYaxis()->SetTitleSize(0.05);
  g0->GetXaxis()->SetLabelSize(0.04);
  g0->GetYaxis()->SetLabelSize(0.04);
  g0->GetYaxis()->SetTitle(yTitle);
  g0->GetXaxis()->SetTitle("Muon #font[52]{p}_{T} [GeV]");
  g0->SetTitle("");
  g0->SetStats(0);
  g0->Draw();
  g1->Draw(" same");
  g2->Draw(" same");
  g3->Draw(" same");
  g4->Draw(" same");
  li->DrawLine(15,0.5,15,1);
  TLatex *la = new TLatex();
  la->SetTextSize(0.032);
  la->SetTextFont(42);
  TString sampleName = "#scale[1.2]{#font[62]{CMS}} #font[52]{Preliminary}                        #sqrt{s_{NN}} = 5.02 TeV";
  TString muonEtaInfo = "";
  TString muonPtInfo = "";
  if(doReco){
    muonEtaInfo = "#splitline{|#it{#eta}^{#it{#mu}}| < 2.0}{#it{#DeltaR}(reco,gen) < 0.03}";
    muonPtInfo = "#splitline{#it{p}_{T}^{#it{#mu}} > 15 GeV}{#it{#DeltaR}(reco,gen) < 0.03}";
  }
  else if(doID){
    muonEtaInfo = "#splitline{|#it{#eta}^{#it{#mu}}| < 2.0}{Tight Muon ID}";
    muonPtInfo = "#splitline{#it{p}_{T}^{#it{#mu}} > 15 GeV}{Tight Muon ID}";
  }
  else if(doRecoPlusID){
    muonEtaInfo = "#splitline{|#it{#eta}^{#it{#mu}}| < 2.0}{Tight Muon ID}";
    muonPtInfo = "#splitline{#it{p}_{T}^{#it{#mu}} > 15 GeV}{Tight Muon ID}";
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


  /*

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
  li->DrawLine(15,0.5,15,1);
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
  */
  
}
