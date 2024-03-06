
/*

  This is some code to test the pTrel-template differences 
  between nominal and WTA axis definitions.

*/


#include "../../../headers/functions/project_flavor.h"
#include "../../../headers/functions/divideByBinwidth.h"
#include "../../../headers/functions/canvas/pad_set_margins.h"

void WTA_test(){

  TFile *f_nom, *f_wta;

  f_nom = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/localScans/WTA_test/PYTHIAHYDJET_DiJet_scan_mu5_pThat50_jetFilter_evtReweight_nominalAxis.root");
  f_wta = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/localScans/WTA_test/PYTHIAHYDJET_DiJet_scan_mu5_pThat50_jetFilter_evtReweight_wtaAxis.root");

  TH2D *mu_pTrel_2D_nom, *mu_pTrel_2D_wta;

  f_nom->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C0J4",mu_pTrel_2D_nom);
  f_wta->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C0J4",mu_pTrel_2D_wta);

 

  TH1D *mu_pTrel_b_nom, *mu_pTrel_b_wta; // b/bbar-jets
  TH1D *mu_pTrel_bbar_nom, *mu_pTrel_bbar_wta;
  TH1D *mu_pTrel_c_nom, *mu_pTrel_c_wta; // c/cbar-jets
  TH1D *mu_pTrel_cbar_nom, *mu_pTrel_cbar_wta;
  TH1D *mu_pTrel_u_nom, *mu_pTrel_u_wta; // u/ubar-jets
  TH1D *mu_pTrel_ubar_nom, *mu_pTrel_ubar_wta;
  TH1D *mu_pTrel_d_nom, *mu_pTrel_d_wta; // d/dbar-jets
  TH1D *mu_pTrel_dbar_nom, *mu_pTrel_dbar_wta;
  TH1D *mu_pTrel_s_nom, *mu_pTrel_s_wta; // s/sbar-jets
  TH1D *mu_pTrel_sbar_nom, *mu_pTrel_sbar_wta;
  TH1D *mu_pTrel_g_nom, *mu_pTrel_g_wta; // g-jets

  TH1D *h_get;
  h_get = project_flavor(mu_pTrel_2D_nom, 5);
  mu_pTrel_b_nom = (TH1D*) h_get->Clone("mu_pTrel_b_nom");
  mu_pTrel_bbar_nom = (TH1D*) h_get->Clone("mu_pTrel_bbar_nom");
  mu_pTrel_b_nom->Add(mu_pTrel_bbar_nom);
  // project_flavor(mu_pTrel_2D_wta, mu_pTrel_b_wta, 5);
  h_get = project_flavor(mu_pTrel_2D_wta, 5);
  mu_pTrel_b_wta = (TH1D*) h_get->Clone("mu_pTrel_b_wta");
  mu_pTrel_bbar_wta = (TH1D*) h_get->Clone("mu_pTrel_bbar_wta");
  mu_pTrel_b_wta->Add(mu_pTrel_bbar_wta);
  
  h_get = project_flavor(mu_pTrel_2D_nom, 4);
  mu_pTrel_c_nom = (TH1D*) h_get->Clone("mu_pTrel_c_nom");
  // project_flavor(mu_pTrel_2D_wta, mu_pTrel_c_wta, 5);
  h_get = project_flavor(mu_pTrel_2D_wta, 4);
  mu_pTrel_c_wta = (TH1D*) h_get->Clone("mu_pTrel_c_wta");

  const int N_edge = 12;
  double new_axis[N_edge] = {0,0.2,0.4,0.6,0.8,1.0,1.3,1.6,2.0,2.5,3.0,4.0};

  TH1D *mu_pTrel_b_nom_R, *mu_pTrel_b_wta_R; // rebinned histograms
  mu_pTrel_b_nom_R = (TH1D*) mu_pTrel_b_nom->Rebin(N_edge-1,"mu_pTrel_b_nom_R",new_axis);
  divideByBinwidth(mu_pTrel_b_nom_R);
  mu_pTrel_b_wta_R = (TH1D*) mu_pTrel_b_wta->Rebin(N_edge-1,"mu_pTrel_b_wta_R",new_axis);
  divideByBinwidth(mu_pTrel_b_wta_R);
  
  // project_flavor(mu_pTrel_2D_wta, mu_pTrel_bbar_wta, -5);
  // mu_pTrel_b_nom->Add(mu_pTrel_bbar_nom);
  // mu_pTrel_b_wta->Add(mu_pTrel_bbar_wta);

  // project_flavor(mu_pTrel_2D_nom, mu_pTrel_c_nom, 4);
  // project_flavor(mu_pTrel_2D_wta, mu_pTrel_c_wta, 4);
  // project_flavor(mu_pTrel_2D_nom, mu_pTrel_cbar_nom, -4);
  // project_flavor(mu_pTrel_2D_wta, mu_pTrel_cbar_wta, -4);
  // mu_pTrel_c_nom->Add(mu_pTrel_cbar_nom);
  // mu_pTrel_c_wta->Add(mu_pTrel_cbar_wta);

  // project_flavor(mu_pTrel_2D_nom, mu_pTrel_u_nom, 1);
  // project_flavor(mu_pTrel_2D_wta, mu_pTrel_u_wta, 1);
  // project_flavor(mu_pTrel_2D_nom, mu_pTrel_ubar_nom, -1);
  // project_flavor(mu_pTrel_2D_wta, mu_pTrel_ubar_wta, -1);
  // mu_pTrel_u_nom->Add(mu_pTrel_cbar_nom);
  // mu_pTrel_u_wta->Add(mu_pTrel_cbar_wta);

  // project_flavor(mu_pTrel_2D_nom, mu_pTrel_d_nom, 2);
  // project_flavor(mu_pTrel_2D_wta, mu_pTrel_d_wta, 2);
  // project_flavor(mu_pTrel_2D_nom, mu_pTrel_dbar_nom, -2);
  // project_flavor(mu_pTrel_2D_wta, mu_pTrel_dbar_wta, -2);
  // mu_pTrel_d_nom->Add(mu_pTrel_cbar_nom);
  // mu_pTrel_d_wta->Add(mu_pTrel_cbar_wta);

  // project_flavor(mu_pTrel_2D_nom, mu_pTrel_s_nom, 3);
  // project_flavor(mu_pTrel_2D_wta, mu_pTrel_s_wta, 3);
  // project_flavor(mu_pTrel_2D_nom, mu_pTrel_sbar_nom, -3);
  // project_flavor(mu_pTrel_2D_wta, mu_pTrel_sbar_wta, -3);
  // mu_pTrel_s_nom->Add(mu_pTrel_cbar_nom);
  // mu_pTrel_s_wta->Add(mu_pTrel_cbar_wta);

  // project_flavor(mu_pTrel_2D_nom, mu_pTrel_g_nom, 21);
  // project_flavor(mu_pTrel_2D_wta, mu_pTrel_g_wta, 21);
  // mu_pTrel_g_nom->Add(mu_pTrel_cbar_nom);
  // mu_pTrel_g_wta->Add(mu_pTrel_cbar_wta);

  // // combine the lights
  // TH1D *mu_pTrel_light_nom = (TH1D*) mu_pTrel_u_nom->Clone("mu_pTrel_light_nom");
  // mu_pTrel_light_nom->Add(mu_pTrel_d_nom);
  // mu_pTrel_light_nom->Add(mu_pTrel_s_nom);
  // mu_pTrel_light_nom->Add(mu_pTrel_g_nom);
  // TH1D *mu_pTrel_light_wta = (TH1D*) mu_pTrel_u_wta->Clone("mu_pTrel_light_wta");
  // mu_pTrel_light_wta->Add(mu_pTrel_d_wta);
  // mu_pTrel_light_wta->Add(mu_pTrel_s_wta);
  // mu_pTrel_light_wta->Add(mu_pTrel_g_wta);


  // TH1D *mu_pTrel_all_nom = (TH1D*) mu_pTrel_u_nom->Clone("mu_pTrel_all_nom");
  // mu_pTrel_all_nom->Add(mu_pTrel_d_nom);
  // mu_pTrel_all_nom->Add(mu_pTrel_s_nom);
  // mu_pTrel_all_nom->Add(mu_pTrel_g_nom);
  // mu_pTrel_all_nom->Add(mu_pTrel_c_nom);
  // mu_pTrel_all_nom->Add(mu_pTrel_b_nom);
  // TH1D *mu_pTrel_all_wta = (TH1D*) mu_pTrel_u_wta->Clone("mu_pTrel_all_wta");
  // mu_pTrel_all_wta->Add(mu_pTrel_d_wta);
  // mu_pTrel_all_wta->Add(mu_pTrel_s_wta);
  // mu_pTrel_all_wta->Add(mu_pTrel_g_wta);
  // mu_pTrel_all_wta->Add(mu_pTrel_c_wta);
  // mu_pTrel_all_wta->Add(mu_pTrel_b_wta);



  TH1D *r = (TH1D*) mu_pTrel_b_nom->Clone("r");
  r->Divide(mu_pTrel_b_nom,mu_pTrel_b_wta,1,1,"B");
  // r->Draw();
  TCanvas *canv_b = new TCanvas("canv_b","canv_b",700,700);
  canv_b->cd();
  TPad *pad_b_1 = new TPad("pad_b_1","pad_b_1",0,0,1,1);
  pad_set_margins(pad_b_1);
  pad_b_1->Draw();
  pad_b_1->cd();
  mu_pTrel_b_wta_R->GetXaxis()->SetTitle("muon #it{p}_{T}^{rel} [GeV]");
  mu_pTrel_b_wta_R->GetYaxis()->SetTitle("a.u.");
  mu_pTrel_b_wta_R->SetTitle("");
  mu_pTrel_b_wta_R->SetStats(0);
  
  mu_pTrel_b_nom_R->SetLineColor(kBlue-4);
  mu_pTrel_b_nom_R->SetLineWidth(2);
  mu_pTrel_b_wta_R->SetLineColor(kRed-4);
  mu_pTrel_b_wta_R->SetLineWidth(2);
  mu_pTrel_b_wta_R->Draw();
  mu_pTrel_b_nom_R->Draw("same");

  TLegend *leg = new TLegend(0.6,0.7,0.88,0.88);
  leg->SetBorderSize(0);
  leg->AddEntry(mu_pTrel_b_wta_R,"WTA axis");
  leg->AddEntry(mu_pTrel_b_nom_R,"nominal axis");
  leg->Draw();

  TLatex *la = new TLatex();
  la->SetTextSize(0.04);
  la->SetTextFont(42);
  la->DrawLatexNDC(0.5,0.5,"PYTHIA+HYDJET, #it{b}-jets");
  la->DrawLatexNDC(0.5,0.4,"120 < #it{p}_{T}^{jet} < 200 GeV");
  la->DrawLatexNDC(0.5,0.3,"#it{p}_{T}^{#mu} > 7 GeV");
  
}


