#include "../../../headers/goldenFileNames.h"
#include "../../../headers/functions/divideByBinwidth.h"

void ptRel_compare(){

  cout << "running ptRel_compare..." << endl;

  TFile *f1 = TFile::Open(goldenFile_PYTHIAHYDJET_DiJet_mu5_pThat15);
  TFile *f2 = TFile::Open(goldenFile_PYTHIAHYDJET_DiJet_mu5_pThat30);

  TH2D *H1, *H2;
  TH1D *h1, *h2;
  TH1D *b1, *b2;
  TH1D *bGS1, *bGS2;
  TH1D *bbar1, *bbar2;
  TH1D *l1, *l2;
  TH1D *g1, *g2;

  TString histogram_name = "h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J2";

  f1->GetObject(histogram_name,H1);
  f2->GetObject(histogram_name,H2);

  TH1D *binFinder = (TH1D*) H1->ProjectionY();
  double smallShift = 0.01;
  
  h1 = (TH1D*) H1->ProjectionX("h1");
  h2 = (TH1D*) H2->ProjectionX("h2");

  b1 = (TH1D*) H1->ProjectionX("b1",binFinder->FindBin(5.+smallShift),binFinder->FindBin(6.-smallShift));
  bGS1 = (TH1D*) H1->ProjectionX("bGS1",binFinder->FindBin(17.+smallShift),binFinder->FindBin(18.-smallShift));
  bbar1 = (TH1D*) H1->ProjectionX("bbar1",binFinder->FindBin(-5.+smallShift),binFinder->FindBin(-4.-smallShift));

  b1->Add(bbar1);
  b1->Add(bGS1);
  //b1->Draw();

  l1 = (TH1D*) H1->ProjectionX("l1",binFinder->FindBin(-3.+smallShift),binFinder->FindBin(3.-smallShift));
  g1 = (TH1D*) H1->ProjectionX("g1",binFinder->FindBin(21.+smallShift),binFinder->FindBin(22.-smallShift));

  l1->Add(g1);

  l2 = (TH1D*) H2->ProjectionX("l2",binFinder->FindBin(-3.+smallShift),binFinder->FindBin(3.-smallShift));
  g2 = (TH1D*) H2->ProjectionX("g2",binFinder->FindBin(21.+smallShift),binFinder->FindBin(22.-smallShift));

  l2->Add(g2);

  l1->SetLineColor(kGreen+2);
  l2->SetLineColor(kBlue-4);
  l1->SetLineWidth(3);
  l2->SetLineWidth(3);
  l1->SetFillColorAlpha(kGreen+2,0.8);
  l2->SetFillColorAlpha(kBlue-4,0.8);

  l1->Scale(1./l1->Integral());
  l2->Scale(1./l2->Integral());
  
  //l1->Draw();
  //l2->Draw("same");

  TH1D *l1R, *l2R;

  const int Nedge = 12;
  double newAxis[Nedge] = {0.0,0.2,0.4,0.6,0.8,1.0,1.2,1.5,1.8,2.4,3.5,5.0};

  l1R = (TH1D*) l1->Rebin(Nedge-1,"l1R",newAxis);
  l2R = (TH1D*) l2->Rebin(Nedge-1,"l2R",newAxis);

  divideByBinwidth(l1R);
  divideByBinwidth(l2R);

  l1R->SetTitle("Light jets, P+H 0-30%, 60 < #it{p}_{T}^{jet} < 80 GeV");
  l1R->GetXaxis()->SetTitle("muon #it{p}_{T}^{rel} [GeV]");
  l1R->GetYaxis()->SetTitle("a.u.");
  l1R->SetStats(0);

  

  l1R->Draw("e2");
  l2R->Draw("same");
  
  TLatex *la = new TLatex();
  la->SetTextSize(0.05);
  la->SetTextColor(kGreen+2);
  la->DrawLatexNDC(0.4,0.8,"#hat{#it{p}}_{T} > 0.35 #it{p}_{T}^{jet}    (#hat{#it{p}}_{T} > 15 GeV)");

  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.4,0.68,"#hat{#it{p}}_{T}^{leadingXjet} > #hat{#it{p}}_{T}    (#hat{#it{p}_{T}} > 30 GeV)");

  // la->SetTextColor(kBlack);
  // la->SetTextSize(0.04);
 


  
}
