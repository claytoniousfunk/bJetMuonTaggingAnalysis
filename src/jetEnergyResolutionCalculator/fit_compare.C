

TF1 *fxn1, *fxn2, *r;
TCanvas *canv;
TPad *pad;
TLegend *leg;

void prep_canvas(TCanvas *canvas, TPad *pad){

  


}

void fit_compare(){

  fxn1 = new TF1("fxn1","TMath::Sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x))",0,500);
  fxn2 = new TF1("fxn2","TMath::Sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x))",0,500);
  r = new TF1("r","TMath::Sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x)) / TMath::Sqrt([3]*[3] + [4]*[4]/x + [5]*[5]/(x*x))",0,500);

  double fxn1_params[3] = {0.0485856, 0.938275, 2.28814};
  double fxn2_params[3] = {0.0664565, 1.25245, 0.0631997};

  for(int i = 0; i < 3; i++){

    fxn1->SetParameter(i,fxn1_params[i]);
    fxn2->SetParameter(i,fxn2_params[i]);
    r->SetParameter(i,fxn2_params[i]);
    r->SetParameter(i+3,fxn1_params[i]);
  }


  fxn1->SetLineWidth(2);
  fxn2->SetLineWidth(2);

  fxn1->SetLineColor(kRed-4);
  fxn2->SetLineColor(kBlue-4);

  canv = new TCanvas("canv","canv",700,700);
  canv->cd();
  pad = new TPad("pad","pad",0,0,1,1);
  pad->SetLeftMargin(0.15);
  pad->SetBottomMargin(0.15);
  pad->Draw();
  pad->cd();
  // fxn1->SetTitle("");
  // fxn1->GetYaxis()->SetTitle("#it{#sigma}(#it{p}_{T}^{recoJet}/#it{p}_{T}^{genJet})");
  // fxn1->GetXaxis()->SetTitle("#it{p}_{T}^{genJet} [GeV]");
  // //fxn1->SetStats(0);
  // fxn1->GetXaxis()->SetRangeUser(20,500);
  // fxn1->Draw();
  // fxn2->Draw("same");
  // leg = new TLegend(0.6,0.6,0.8,0.8);
  // leg->SetTextSize(0.04);
  // leg->SetBorderSize(0);
  // leg->AddEntry(fxn1,"incl. jets");
  // leg->AddEntry(fxn2,"#it{#mu}-tagged #it{b}-jets");
  // leg->Draw();

  r->SetTitle("");
  r->GetYaxis()->SetTitle("#it{#sigma}_{#it{b}}^{#it{#mu}-tagged} / #it{#sigma}^{incl}");
  r->GetXaxis()->SetTitle("#it{p}_{T}^{genJet} [GeV]");
  r->GetXaxis()->SetRangeUser(20,500);
  r->Draw();
  

}
