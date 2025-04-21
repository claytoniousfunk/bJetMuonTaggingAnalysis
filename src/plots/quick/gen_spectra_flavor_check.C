#include "../../../headers/functions/divideByBinwidth.h"
#include "../../../headers/systematicsResults.h"
#include "../../../headers/goldenFileNames.h"

void gen_spectra_flavor_check(){

  TString input_PYTHIA;
  input_PYTHIA = goldenFile_PYTHIA_mu12_pThat30;

  TFile *file;
  file = TFile::Open(input_PYTHIA);

  TH2D *H;

  file->GetObject("h_inclGenJetPt_flavor",H);

  TH1D *h_b, *h_c, *h_u, *h_d, *h_s, *h_g;
  TH1D *h_bbar, *h_cbar, *h_ubar, *h_dbar, *h_sbar;
  TH1D *h_bGS;

  TH1D *bf = (TH1D*) H->ProjectionY();
  double ss = 0.1;

  h_b = (TH1D*) H->ProjectionX("h_b",bf->FindBin(5.+ss),bf->FindBin(6.-ss));
  h_c = (TH1D*) H->ProjectionX("h_c",bf->FindBin(4.+ss),bf->FindBin(5.-ss));
  h_d = (TH1D*) H->ProjectionX("h_d",bf->FindBin(1.+ss),bf->FindBin(2.-ss));
  h_u = (TH1D*) H->ProjectionX("h_u",bf->FindBin(2.+ss),bf->FindBin(3.-ss));
  h_s = (TH1D*) H->ProjectionX("h_s",bf->FindBin(3.+ss),bf->FindBin(4.-ss));
  h_g = (TH1D*) H->ProjectionX("h_g",bf->FindBin(21.+ss),bf->FindBin(22.-ss));

  h_bbar = (TH1D*) H->ProjectionX("h_bbar",bf->FindBin(-5.+ss),bf->FindBin(-4.-ss));
  h_cbar = (TH1D*) H->ProjectionX("h_cbar",bf->FindBin(-4.+ss),bf->FindBin(-3.-ss));
  h_dbar = (TH1D*) H->ProjectionX("h_dbar",bf->FindBin(-1.+ss),bf->FindBin(0.-ss));
  h_ubar = (TH1D*) H->ProjectionX("h_ubar",bf->FindBin(-2.+ss),bf->FindBin(-1.-ss));
  h_sbar = (TH1D*) H->ProjectionX("h_sbar",bf->FindBin(-3.+ss),bf->FindBin(-2.-ss));

  h_bGS = (TH1D*) H->ProjectionX("h_bGS",bf->FindBin(-5.+ss),bf->FindBin(-4.-ss));

  h_b->Add(h_bbar); h_b->Add(h_bGS);
  h_c->Add(h_cbar);
  h_d->Add(h_dbar);
  h_u->Add(h_ubar);
  h_s->Add(h_sbar);
  
  h_b->SetLineColor(kRed-4);
  h_c->SetLineColor(kGreen+2);
  h_d->SetLineColor(kMagenta-9);
  h_u->SetLineColor(kBlue-9);
  h_s->SetLineColor(kCyan+2);
  h_g->SetLineColor(kOrange);


  h_b->SetLineWidth(2);
  h_c->SetLineWidth(2);
  h_d->SetLineWidth(2);
  h_u->SetLineWidth(2);
  h_s->SetLineWidth(2);
  h_g->SetLineWidth(2);


  h_b->Scale(1./h_b->Integral());
  h_c->Scale(1./h_c->Integral());
  h_d->Scale(1./h_d->Integral());
  h_u->Scale(1./h_u->Integral());
  h_s->Scale(1./h_s->Integral());
  h_g->Scale(1./h_g->Integral());
  
  TH1D *r_c = (TH1D*) h_c->Clone("r_c");
  TH1D *r_d = (TH1D*) h_d->Clone("r_d");
  TH1D *r_u = (TH1D*) h_u->Clone("r_u");
  TH1D *r_s = (TH1D*) h_s->Clone("r_s");
  TH1D *r_g = (TH1D*) h_g->Clone("r_g");

  r_c->Divide(h_c,h_b,1,1,"");
  r_d->Divide(h_d,h_b,1,1,"");
  r_u->Divide(h_u,h_b,1,1,"");
  r_s->Divide(h_s,h_b,1,1,"");
  r_g->Divide(h_g,h_b,1,1,"");

  // r_c->Draw();
  // r_d->Draw("same");
  // r_u->Draw("same");
  // r_s->Draw("same");
  // r_g->Draw("same");

  h_b->Draw();
  h_c->Draw("same");
  h_d->Draw("same");
  h_u->Draw("same");
  h_s->Draw("same");
  h_g->Draw("same");

}
