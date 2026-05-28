
void stylizeHistograms(TH1D *h1, TH1D *h2, TH1D *h3){

  h1->SetStats(0);
  h2->SetStats(0);
  h3->SetStats(0);

  h1->SetTitle("");
  h2->SetTitle("");
  h3->SetTitle("");

  double lineWidth = 2;
  h1->SetLineWidth(lineWidth);
  h2->SetLineWidth(lineWidth);
  h3->SetLineWidth(lineWidth);

  h1->SetLineColor(kBlue-4);
  h2->SetLineColor(kRed-4);
  h3->SetLineColor(kGreen+2);

  h1->SetMarkerColor(kBlue-4);
  h2->SetMarkerColor(kRed-4);
  h3->SetMarkerColor(kGreen+2);

  h1->SetMarkerStyle(24);
  h2->SetMarkerStyle(24);
  h3->SetMarkerStyle(24);

  double markerSize = 2.0;
  h1->SetMarkerSize(markerSize);
  h2->SetMarkerSize(markerSize);
  h3->SetMarkerSize(markerSize);

}


void plotBPurity_matchedVsUnmatched(){

  TFile *f_nom = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/bPurityResults/latest/pp_inclMuons.root");
  TFile *f_matched = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/bPurityResults/latest/pp_matchedMuons.root");
  TFile *f_unmatched = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/bPurityResults/latest/pp_unmatchedMuons.root");

  TH1D *b_nom, *b_matched, *b_unmatched;

  f_nom->GetObject("bFracResults_pp",b_nom);
  f_matched->GetObject("bFracResults_pp",b_matched);
  f_unmatched->GetObject("bFracResults_pp",b_unmatched);

  stylizeHistograms(b_nom,b_matched,b_unmatched);


  TLatex *la = new TLatex();
  la->SetTextFont(42);
  la->SetTextSize(0.04);
  
  TCanvas *canv = new TCanvas("canv","canv",700,700);
  canv->cd();
  TPad *pad = new TPad("pad","pad",0,0,1,1);
  pad->SetLeftMargin(0.15);
  pad->SetBottomMargin(0.15);
  pad->Draw();
  pad->cd();
  b_nom->Draw();
  b_matched->Draw("same");
  b_unmatched->Draw("same");
  la->SetTextColor(kBlack);
  la->DrawLatexNDC(0.2,0.4,"PYTHIA");
  la->SetTextColor(kRed-4);
  la->DrawLatexNDC(0.2,0.34,"incl. light muons");
  la->SetTextColor(kBlue-4);
  la->DrawLatexNDC(0.2,0.28,"matched light muons");
  la->SetTextColor(kGreen+2);
  la->DrawLatexNDC(0.2,0.22,"unmatched light muons");

  canv->SaveAs("../../../figures/bPurity/bPurity_pp_matchedVsUnmatched.pdf");
  



}
