// includes
#include "../../../headers/goldenFileNames.h"
#include "../../../headers/functions/divideByBinwidth.h"

// objects
TFile *f1, *f2, *f3;
TH2D *H1, *H2; // muptrel histograms
TH2D *J1, *J2; // jet histograms for matched/incl muon calculation
TH1D *h1, *h2, *h3;
TH1D *g1, *g2, *g3;
TH1D *a1, *a2;
TH1D *b1, *b2;
TH1D *bf; // bf = bin-finder histogram
double ss; // ss = small shift
TH1D *h1R, *h2R;

void lightTemplates(){

  TLatex *la = new TLatex();
  
  ss = 0.1;
  
  f1 = TFile::Open(goldenFile_PYTHIAHYDJET_DiJet_mu12_pThat30);
  f2 = TFile::Open(goldenFile_PYTHIAHYDJET_MuJet_mu12_pThat30);
  f3 = TFile::Open(goldenFile_PYTHIA_mu12_pThat30);

  f1->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J2",H1);
  f2->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J2",H2);
  f1->GetObject("h_inclRecoJetPt_matchedRecoMuonTag_triggerOn_flavor_C1",J1);
  f1->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor_C1",J2);
  //f3->GetObject("h_inclRecoJetPt_matchedRecoMuonTag_triggerOn_flavor",J1);
  //f3->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_flavor",J2);

  bf = (TH1D*) H1->ProjectionY("bf");
  h1 = (TH1D*) H1->ProjectionX("h1",bf->FindBin(-3. + ss),bf->FindBin(3.-ss));
  a1 = (TH1D*) H1->ProjectionX("a1",bf->FindBin(21. + ss),bf->FindBin(22.-ss));
  h2 = (TH1D*) H2->ProjectionX("h2",bf->FindBin(-3. + ss),bf->FindBin(3.-ss));
  a2 = (TH1D*) H2->ProjectionX("a2",bf->FindBin(21. + ss),bf->FindBin(22.-ss));
  h1->Add(a1);
  h2->Add(a2);

  g1 = (TH1D*) J1->ProjectionX("g1",bf->FindBin(-3. + ss),bf->FindBin(3.-ss));
  b1 = (TH1D*) J1->ProjectionX("b1",bf->FindBin(21. + ss),bf->FindBin(22.-ss));
  g2 = (TH1D*) J2->ProjectionX("g2",bf->FindBin(-3. + ss),bf->FindBin(3.-ss));
  b2 = (TH1D*) J2->ProjectionX("b2",bf->FindBin(21. + ss),bf->FindBin(22.-ss));
  g1->Add(b1);
  g2->Add(b2);

  g1->SetLineColor(kBlue);
  g2->SetLineColor(kRed);
  g1->SetLineWidth(2);
  g2->SetLineWidth(2);

  TCanvas *canv_j = new TCanvas("canv_j","",700,700);
  canv_j->cd();
  TPad *pad_j_up = new TPad("pad_j_up","",0,0.4,1,1);
  TPad *pad_j_low = new TPad("pad_j_low","",0,0.0,1,0.4);
  pad_j_up->SetLogy();
  pad_j_up->SetBottomMargin(0);
  pad_j_low->SetTopMargin(0);
  pad_j_low->SetBottomMargin(0.18);
  pad_j_up->Draw();
  pad_j_low->Draw();
  pad_j_up->cd();
  g1->SetTitle("");
  g1->SetStats(0);
  g1->Draw();
  g2->Draw("same");
  la->SetTextFont(42);
  la->SetTextColor(kRed);
  la->SetTextSize(0.042);
  la->DrawLatexNDC(0.5,0.7,"incl-#it{#mu}-tagged");
  la->SetTextColor(kBlue);
  la->DrawLatexNDC(0.5,0.62,"matched-#it{#mu}-tagged");
  pad_j_low->cd();
  TH1D *r_g = (TH1D*) g1->Clone("r_g");
  r_g->Divide(g1,g2,1,1,"B");
  r_g->GetXaxis()->SetTitleSize(0.05);
  r_g->GetXaxis()->SetLabelSize(0.045);
  r_g->GetYaxis()->SetTitleSize(0.05);
  r_g->GetYaxis()->SetLabelSize(0.045);
  r_g->GetXaxis()->SetTitle("#it{p}_{T}^{recoJet} [GeV]");
  r_g->GetYaxis()->SetTitle("ratio");
  r_g->GetYaxis()->SetRangeUser(0,1);
  r_g->Draw();

  cout << "N(matched-mu-tagged-jet) / N(incl-mu-tagged-jet) = " << g1->Integral() / g2->Integral() << endl;
  
  

  h1->Scale(1./h1->Integral());
  h2->Scale(1./h2->Integral());

  const int Nedge = 12;
  double newAxis[Nedge] = {0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.5,1.8,2.4,3.5,5.0};

  h1R = (TH1D*) h1->Rebin(Nedge-1,"h1R",newAxis);
  h2R = (TH1D*) h2->Rebin(Nedge-1,"h2R",newAxis);

  divideByBinwidth(h1R);
  divideByBinwidth(h2R);

  TCanvas *canv_h = new TCanvas("canv_h","",700,700);
  canv_h->cd();
  TPad *pad_h = new TPad("pad_h","",0,0,1,1);
  pad_h->Draw();
  pad_h->cd();
  h1R->Draw();
  h2R->Draw("same");

}
