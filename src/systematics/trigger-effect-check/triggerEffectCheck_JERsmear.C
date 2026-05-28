
TString getSystemString(bool doPP = 1,
			bool doC4 = 0,
			bool doC3 = 0,
			bool doC2 = 0,
			bool doC1 = 0){

  TString result = "";
  if(doPP) result = "pp";
  else if(doC4) result = "C4";
  else if(doC3) result = "C3";
  else if(doC2) result = "C2";
  else if(doC1) result = "C1";

  return result;


}

void triggerEffectCheck_JERsmear(bool doPP = 1,
				 bool doC4 = 0,
				 bool doC3 = 0,
				 bool doC2 = 0,
				 bool doC1 = 0){


  TString systemString = getSystemString(doPP,
					 doC4,
					 doC3,
					 doC2,
					 doC1);
  
  TFile *f_mc = TFile::Open(Form("../../../rootFiles/systematics/JER-smear-spectra/histograms_%s.root",systemString.Data()));
  TFile *f_data = TFile::Open(Form("../../../rootFiles/systematics/JER-smear-spectra-data/histograms_%s.root",systemString.Data()));

  TString saveString = Form("../../../figures/systematics/trigger-effect-check/canv_%s.pdf",systemString.Data());

  TH1D *h_mc, *h_data;
  TH1D *r;

  f_mc->GetObject("F_pp_nom",h_mc);
  f_data->GetObject("F_pp_nom",h_data);

  h_mc->SetLineColor(kRed-4);
  h_data->SetLineColor(kBlue-4);

  
  
  r = (TH1D*) h_data->Clone("r");
  r->Divide(h_data,h_mc,1,1,"");

  TCanvas *canv = new TCanvas("canv","canv",700,700);
  canv->cd();
  TPad *pad = new TPad("pad","pad",0,0,1,1);
  double leftMargin = 0.15;
  double bottomMargin = 0.15;
  pad->SetLeftMargin(leftMargin);
  pad->SetBottomMargin(bottomMargin);
  pad->Draw();
  pad->cd();

  r->GetYaxis()->SetTitleSize(0.04);
  r->GetYaxis()->SetRangeUser(0,2);

  r->GetYaxis()->SetTitle("#it{#mu}-tagged-fraction(data) / #it{#mu}-tagged-fraction(MC)");
  
  //h_mc->Draw();
  //h_data->Draw("same");
  r->Draw();

  TLine *li = new TLine();
  li->SetLineStyle(7);
  li->DrawLine(30,1,500,1);

  canv->SaveAs(saveString);


}
