


void templateSwapEffect(){

  TFile *f_nom = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/bPurityResults/latest/nominal_fit.root");
  TFile *f_swap = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/bPurityResults/latest/swapped_fit.root");

  TH1D *h_pp_nom, *h_C4_nom;
  TH1D *h_pp_swap, *h_C4_swap;

  TLine *li = new TLine();
  li->SetLineStyle(7);
  

  f_nom->GetObject("bFracResults_pp",h_pp_nom);
  f_nom->GetObject("bFracResults_C4",h_C4_nom);

  f_swap->GetObject("bFracResults_pp",h_pp_swap);
  f_swap->GetObject("bFracResults_C4",h_C4_swap);

  TH1D *r_pp, *r_C4;

  r_pp = (TH1D*) h_pp_swap->Clone("r_pp");
  r_C4 = (TH1D*) h_C4_swap->Clone("r_C4");

  r_pp->Divide(h_pp_swap,h_pp_nom,1,1,"B");
  r_C4->Divide(h_C4_swap,h_C4_nom,1,1,"B");

  r_pp->SetLineColor(kBlack);
  r_pp->SetLineWidth(2);
  r_pp->SetMarkerColor(kBlack);
  r_pp->SetMarkerStyle(20);
  r_pp->SetMarkerSize(1.4);

  r_C4->SetLineColor(kBlue+1);
  r_C4->SetLineWidth(2);
  r_C4->SetMarkerColor(kBlue+1);
  r_C4->SetMarkerStyle(33);
  r_C4->SetMarkerSize(1.4);

  TLegend *leg = new TLegend(0.6,0.7,0.88,0.88);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->AddEntry(r_pp,"pp");
  leg->AddEntry(r_C4,"PbPb 50-80\%");

  TCanvas *canv = new TCanvas("canv","canv",700,700);
  canv->cd();
  TPad *pad = new TPad("pad","pad",0,0,1,1);
  pad->SetLeftMargin(0.18);
  pad->SetBottomMargin(0.18);
  pad->Draw();
  pad->cd();
  r_pp->GetXaxis()->SetTitle("#it{p}_{T}^{recoJet} [GeV]");
  r_pp->GetYaxis()->SetTitle("Swapped / Nominal");
  r_pp->SetStats(0);
  r_pp->SetTitle("");
  r_pp->GetYaxis()->SetRangeUser(0.8,1.2);
  r_pp->GetYaxis()->SetTitleSize(0.06);
  r_pp->GetXaxis()->SetTitleSize(0.06);
  r_pp->GetYaxis()->SetLabelSize(0.045);
  r_pp->GetXaxis()->SetLabelSize(0.045);
  r_pp->Draw();
  r_C4->Draw("same");
  li->DrawLine(80,1,200,1);
  leg->Draw();

  
}
