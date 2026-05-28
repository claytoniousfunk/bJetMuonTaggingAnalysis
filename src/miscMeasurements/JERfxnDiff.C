

void JERfxnDiff(){

  TF1 *JER_fxn_pp = new TF1("JER_fxn_pp","sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x))",30,500);
  JER_fxn_pp->SetParameter(0,0.0640995);
  JER_fxn_pp->SetParameter(1,0.917851);
  JER_fxn_pp->SetParameter(2,-0.00211695);

  TF1 *JER_fxn_C4 = new TF1("JER_fxn_C4","sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x))",30,500);
  JER_fxn_C4->SetParameter(0,0.0606347);
  JER_fxn_C4->SetParameter(1,1.08087);
  JER_fxn_C4->SetParameter(2,-0.374138);

  TF1 *JER_fxn_C3 = new TF1("JER_fxn_C3","sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x))",30,500);
  JER_fxn_C3->SetParameter(0,0.0576787);
  JER_fxn_C3->SetParameter(1,1.1762);
  JER_fxn_C3->SetParameter(2,-5.67268);

  TF1 *JER_fxn_C2 = new TF1("JER_fxn_C2","sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x))",30,500);
  JER_fxn_C2->SetParameter(0,0.0547384);
  JER_fxn_C2->SetParameter(1,1.306);
  JER_fxn_C2->SetParameter(2,-11.1249);

  TF1 *JER_fxn_C1 = new TF1("JER_fxn_C1","sqrt([0]*[0] + [1]*[1]/x + [2]*[2]/(x*x))",30,500);
  JER_fxn_C1->SetParameter(0,0.0598659);
  JER_fxn_C1->SetParameter(1,1.30631);
  JER_fxn_C1->SetParameter(2,-16.893);


  

  JER_fxn_pp->SetLineColor(kBlack);
  JER_fxn_C4->SetLineColor(kBlue+1);
  JER_fxn_C3->SetLineColor(kRed-4);
  JER_fxn_C2->SetLineColor(kGreen+2);
  JER_fxn_C1->SetLineColor(kMagenta-9);

  TLegend *leg = new TLegend(0.45,0.6,0.8,0.8);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.033);
  leg->AddEntry(JER_fxn_pp,"PYTHIA");
  leg->AddEntry(JER_fxn_C4,"PYTHIA+HYDJET 50-80%");
  leg->AddEntry(JER_fxn_C3,"PYTHIA+HYDJET 30-50%");
  leg->AddEntry(JER_fxn_C2,"PYTHIA+HYDJET 10-30%");
  leg->AddEntry(JER_fxn_C1,"PYTHIA+HYDJET 0-10%");


  TCanvas *canv = new TCanvas("canv","canv",700,700);
  canv->cd();
  TPad *pad = new TPad("pad","pad",0,0,1,1);
  pad->SetLeftMargin(0.15);
  pad->SetBottomMargin(0.15);
  pad->Draw();
  pad->cd();
  double labelSize = 0.037;
  double titleSize = 0.045;
  JER_fxn_pp->GetXaxis()->SetLabelSize(labelSize);
  JER_fxn_pp->GetXaxis()->SetTitleSize(titleSize);
  JER_fxn_pp->GetXaxis()->SetTitle("Jet #it{p}_{T} [GeV]");
  JER_fxn_pp->GetYaxis()->SetLabelSize(labelSize);
  JER_fxn_pp->GetYaxis()->SetTitleSize(titleSize);
  JER_fxn_pp->GetYaxis()->SetTitle("#it{#sigma}(#it{p}_{T}^{recoJet} / #it{p}_{T}^{genJet})");
  JER_fxn_pp->SetTitle("");
  JER_fxn_pp->GetYaxis()->SetRangeUser(0,0.5);
  
  JER_fxn_pp->Draw();
  JER_fxn_C4->Draw("same");
  JER_fxn_C3->Draw("same");
  JER_fxn_C2->Draw("same");
  JER_fxn_C1->Draw("same");

  leg->Draw();

  canv->SaveAs("../../figures/miscMeasurements/JERfxnDiff/JERfxnDiff.pdf");


  
}
