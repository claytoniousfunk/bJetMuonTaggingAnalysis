



void JER_compare(){

  TFile *f_nom = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/JER/JER_C1.root");
  TFile *f_JERSmear = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/JER/JER_JERSmear_C1.root");

  TH1D *h_nom, *h_JERSmear;

  // f_nom->GetObject("JER_result_b",h_nom);
  // f_JERSmear->GetObject("JER_result_b",h_JERSmear);
  f_nom->GetObject("JER_result_i",h_nom);
  f_JERSmear->GetObject("JER_result_i",h_JERSmear);

  
  TCanvas *canv = new TCanvas("canv","canv",700,700);
  canv->cd();
  TPad *pad = new TPad("pad","pad",0,0,1,1);
  double leftMargin = 0.18;
  double bottomMargin = 0.18;
  pad->SetLeftMargin(leftMargin);
  pad->SetBottomMargin(bottomMargin);
  pad->Draw();
  pad->cd();
  
  TH1D *r = (TH1D*) h_nom->Clone("r");
  r->Divide(h_JERSmear,h_nom,1,1,"B");
  r->SetStats(0);
  r->SetTitle("");
  r->GetYaxis()->SetRangeUser(0.9,1.6);
  double titleSize = 0.06;
  double labelSize = 0.05;
  r->GetYaxis()->SetTitleSize(titleSize);
  r->GetYaxis()->SetLabelSize(labelSize);
  r->GetXaxis()->SetTitleSize(titleSize);
  r->GetXaxis()->SetLabelSize(labelSize);
  //r->GetYaxis()->SetTitle("#sigma_{b}(smeared) / #sigma_{b}(nom.)");
  r->GetYaxis()->SetTitle("#sigma(smeared) / #sigma(nom.)");
  r->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  
  r->Draw();
  TLine *li = new TLine();
  li->SetLineStyle(7);
  li->DrawLine(60,1,500,1);

  canv->SaveAs("./figures/JER_compare.pdf");
    


}
