
/*

  This is some code to test the pTrel-template differences 
  between nominal and WTA axis definitions.

*/


#include "../../../headers/functions/project_flavor.h"

void WTA_diff(){

  TFile *f_nom, *f_wta;

  f_nom = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/localScans/WTA_test/PYTHIAHYDJET_DiJet_scan_mu5_pThat50_jetFilter_evtReweight_nominalAxis.root");
  f_wta = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/localScans/WTA_test/PYTHIAHYDJET_DiJet_scan_mu5_pThat50_jetFilter_evtReweight_wtaAxis.root");

  TH2D *mu_pTrel_2D_nom, *mu_pTrel_2D_wta;

  f_nom->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J4",mu_pTrel_2D_nom);
  f_wta->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C1J4",mu_pTrel_2D_wta);

 

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

  project_flavor(mu_pTrel_2D_nom, mu_pTrel_b_nom, 5);
  project_flavor(mu_pTrel_2D_wta, mu_pTrel_b_wta, 5);
  project_flavor(mu_pTrel_2D_nom, mu_pTrel_bbar_nom, -5);
  project_flavor(mu_pTrel_2D_wta, mu_pTrel_bbar_wta, -5);
  mu_pTrel_b_nom->Add(mu_pTrel_bbar_nom);
  mu_pTrel_b_wta->Add(mu_pTrel_bbar_wta);

  project_flavor(mu_pTrel_2D_nom, mu_pTrel_c_nom, 4);
  project_flavor(mu_pTrel_2D_wta, mu_pTrel_c_wta, 4);
  project_flavor(mu_pTrel_2D_nom, mu_pTrel_cbar_nom, -4);
  project_flavor(mu_pTrel_2D_wta, mu_pTrel_cbar_wta, -4);
  mu_pTrel_c_nom->Add(mu_pTrel_cbar_nom);
  mu_pTrel_c_wta->Add(mu_pTrel_cbar_wta);

  project_flavor(mu_pTrel_2D_nom, mu_pTrel_u_nom, 1);
  project_flavor(mu_pTrel_2D_wta, mu_pTrel_u_wta, 1);
  project_flavor(mu_pTrel_2D_nom, mu_pTrel_ubar_nom, -1);
  project_flavor(mu_pTrel_2D_wta, mu_pTrel_ubar_wta, -1);
  mu_pTrel_u_nom->Add(mu_pTrel_cbar_nom);
  mu_pTrel_u_wta->Add(mu_pTrel_cbar_wta);

  project_flavor(mu_pTrel_2D_nom, mu_pTrel_d_nom, 2);
  project_flavor(mu_pTrel_2D_wta, mu_pTrel_d_wta, 2);
  project_flavor(mu_pTrel_2D_nom, mu_pTrel_dbar_nom, -2);
  project_flavor(mu_pTrel_2D_wta, mu_pTrel_dbar_wta, -2);
  mu_pTrel_d_nom->Add(mu_pTrel_cbar_nom);
  mu_pTrel_d_wta->Add(mu_pTrel_cbar_wta);

  project_flavor(mu_pTrel_2D_nom, mu_pTrel_s_nom, 3);
  project_flavor(mu_pTrel_2D_wta, mu_pTrel_s_wta, 3);
  project_flavor(mu_pTrel_2D_nom, mu_pTrel_sbar_nom, -3);
  project_flavor(mu_pTrel_2D_wta, mu_pTrel_sbar_wta, -3);
  mu_pTrel_s_nom->Add(mu_pTrel_cbar_nom);
  mu_pTrel_s_wta->Add(mu_pTrel_cbar_wta);

  project_flavor(mu_pTrel_2D_nom, mu_pTrel_g_nom, 21);
  project_flavor(mu_pTrel_2D_wta, mu_pTrel_g_wta, 21);
  mu_pTrel_g_nom->Add(mu_pTrel_cbar_nom);
  mu_pTrel_g_wta->Add(mu_pTrel_cbar_wta);

  // combine the lights
  TH1D *mu_pTrel_light_nom = (TH1D*) mu_pTrel_u_nom->Clone("mu_pTrel_light_nom");
  mu_pTrel_light_nom->Add(mu_pTrel_d_nom);
  mu_pTrel_light_nom->Add(mu_pTrel_s_nom);
  mu_pTrel_light_nom->Add(mu_pTrel_g_nom);
  TH1D *mu_pTrel_light_wta = (TH1D*) mu_pTrel_u_wta->Clone("mu_pTrel_light_wta");
  mu_pTrel_light_wta->Add(mu_pTrel_d_wta);
  mu_pTrel_light_wta->Add(mu_pTrel_s_wta);
  mu_pTrel_light_wta->Add(mu_pTrel_g_wta);


  TH1D *mu_pTrel_all_nom = (TH1D*) mu_pTrel_u_nom->Clone("mu_pTrel_all_nom");
  mu_pTrel_all_nom->Add(mu_pTrel_d_nom);
  mu_pTrel_all_nom->Add(mu_pTrel_s_nom);
  mu_pTrel_all_nom->Add(mu_pTrel_g_nom);
  mu_pTrel_all_nom->Add(mu_pTrel_c_nom);
  mu_pTrel_all_nom->Add(mu_pTrel_b_nom);
  TH1D *mu_pTrel_all_wta = (TH1D*) mu_pTrel_u_wta->Clone("mu_pTrel_all_wta");
  mu_pTrel_all_wta->Add(mu_pTrel_d_wta);
  mu_pTrel_all_wta->Add(mu_pTrel_s_wta);
  mu_pTrel_all_wta->Add(mu_pTrel_g_wta);
  mu_pTrel_all_wta->Add(mu_pTrel_c_wta);
  mu_pTrel_all_wta->Add(mu_pTrel_b_wta);

  TCanvas *canv_b = new TCanvas("canv_b","canv_b",700,700);
  canv_b->cd();

  TH1D *r = (TH1D*) mu_pTrel_all_nom->Clone("r");
  r->Divide(mu_pTrel_all_nom,mu_pTrel_all_wta,1,1,"B");
  r->Draw();
  // mu_pTrel_b_nom->Draw();
  // mu_pTrel_b_wta->Draw("same");

}


