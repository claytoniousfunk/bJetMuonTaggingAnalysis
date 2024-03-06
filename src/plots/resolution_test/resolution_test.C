
/*

  This is some code to test the pTrel-template differences 
  between nominal and WTA axis definitions.

*/


#include "../../../headers/functions/project_flavor.h"
#include "../../../headers/functions/divideByBinwidth.h"
#include "../../../headers/functions/canvas/pad_set_margins.h"

void resolution_test(){

  TFile *f_nom, *f_smear, *f_data;

  f_nom = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/localScans/PYTHIAHYDJET_DiJet_scan_mu5_pThat30_jetFilter_evtReweight.root");
  f_smear = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PYTHIAHYDJET/localScans/PYTHIAHYDJET_DiJet_scan_mu5_pThat30_jetFilter_evtReweight_JERsmear.root");
  f_data = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/scanningOutput/PbPb/localScans/PbPb_SingleMuon_scan_mu5.root");

  TH2D *mu_pTrel_2D_nom, *mu_pTrel_2D_smear;
  TH1D *mu_pTrel_data;

  f_nom->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C0J2",mu_pTrel_2D_nom);
  f_smear->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_flavor_C0J2",mu_pTrel_2D_smear);
  f_data->GetObject("h_muptrel_inclRecoMuonTag_triggerOn_C0J2",mu_pTrel_data);

  TString jet_pt_string = "60 < #it{p}_{T}^{jet} < 80 GeV";
  TString canv_save_string = "/home/clayton/Documents/nuclear/GroupMeeting/figures/2024-03-04/resolution_test_pt_60_80.pdf";

  TH1D *mu_pTrel_b_nom, *mu_pTrel_b_smear; // b/bbar-jets
  TH1D *mu_pTrel_bbar_nom, *mu_pTrel_bbar_smear;
  TH1D *mu_pTrel_c_nom, *mu_pTrel_c_smear; // c/cbar-jets
  TH1D *mu_pTrel_cbar_nom, *mu_pTrel_cbar_smear;
  TH1D *mu_pTrel_u_nom, *mu_pTrel_u_smear; // u/ubar-jets
  TH1D *mu_pTrel_ubar_nom, *mu_pTrel_ubar_smear;
  TH1D *mu_pTrel_d_nom, *mu_pTrel_d_smear; // d/dbar-jets
  TH1D *mu_pTrel_dbar_nom, *mu_pTrel_dbar_smear;
  TH1D *mu_pTrel_s_nom, *mu_pTrel_s_smear; // s/sbar-jets
  TH1D *mu_pTrel_sbar_nom, *mu_pTrel_sbar_smear;
  TH1D *mu_pTrel_g_nom, *mu_pTrel_g_smear; // g-jets

  TH1D *h_get;
  h_get = project_flavor(mu_pTrel_2D_nom, 5);
  mu_pTrel_b_nom = (TH1D*) h_get->Clone("mu_pTrel_b_nom");
  h_get = project_flavor(mu_pTrel_2D_nom, -5);
  mu_pTrel_bbar_nom = (TH1D*) h_get->Clone("mu_pTrel_bbar_nom");
  mu_pTrel_b_nom->Add(mu_pTrel_bbar_nom);
  // project_flavor(mu_pTrel_2D_smear, mu_pTrel_b_smear, 5);
  h_get = project_flavor(mu_pTrel_2D_smear, 5);
  mu_pTrel_b_smear = (TH1D*) h_get->Clone("mu_pTrel_b_smear");
  h_get = project_flavor(mu_pTrel_2D_smear, -5);
  mu_pTrel_bbar_smear = (TH1D*) h_get->Clone("mu_pTrel_bbar_smear");
  mu_pTrel_b_smear->Add(mu_pTrel_bbar_smear);

  h_get = project_flavor(mu_pTrel_2D_nom, 4);
  mu_pTrel_c_nom = (TH1D*) h_get->Clone("mu_pTrel_c_nom");
  h_get = project_flavor(mu_pTrel_2D_nom, -4);
  mu_pTrel_cbar_nom = (TH1D*) h_get->Clone("mu_pTrel_cbar_nom");
  mu_pTrel_c_nom->Add(mu_pTrel_cbar_nom);
  h_get = project_flavor(mu_pTrel_2D_smear, 4);
  mu_pTrel_c_smear = (TH1D*) h_get->Clone("mu_pTrel_c_smear");
  h_get = project_flavor(mu_pTrel_2D_smear, -4);
  mu_pTrel_cbar_smear = (TH1D*) h_get->Clone("mu_pTrel_cbar_smear");
  mu_pTrel_c_smear->Add(mu_pTrel_cbar_smear);

  h_get = project_flavor(mu_pTrel_2D_nom, 1);
  mu_pTrel_u_nom = (TH1D*) h_get->Clone("mu_pTrel_u_nom");
  h_get = project_flavor(mu_pTrel_2D_nom, -1);
  mu_pTrel_ubar_nom = (TH1D*) h_get->Clone("mu_pTrel_ubar_nom");
  mu_pTrel_u_nom->Add(mu_pTrel_ubar_nom);
  h_get = project_flavor(mu_pTrel_2D_smear, 1);
  mu_pTrel_u_smear = (TH1D*) h_get->Clone("mu_pTrel_u_smear");
  h_get = project_flavor(mu_pTrel_2D_smear, -1);
  mu_pTrel_ubar_smear = (TH1D*) h_get->Clone("mu_pTrel_ubar_smear");
  mu_pTrel_u_smear->Add(mu_pTrel_ubar_smear);

  h_get = project_flavor(mu_pTrel_2D_nom, 2);
  mu_pTrel_d_nom = (TH1D*) h_get->Clone("mu_pTrel_d_nom");
  h_get = project_flavor(mu_pTrel_2D_nom, -2);
  mu_pTrel_dbar_nom = (TH1D*) h_get->Clone("mu_pTrel_dbar_nom");
  mu_pTrel_d_nom->Add(mu_pTrel_dbar_nom);
  h_get = project_flavor(mu_pTrel_2D_smear, 2);
  mu_pTrel_d_smear = (TH1D*) h_get->Clone("mu_pTrel_d_smear");
  h_get = project_flavor(mu_pTrel_2D_smear, -2);
  mu_pTrel_dbar_smear = (TH1D*) h_get->Clone("mu_pTrel_dbar_smear");
  mu_pTrel_d_smear->Add(mu_pTrel_dbar_smear);

  h_get = project_flavor(mu_pTrel_2D_nom, 3);
  mu_pTrel_s_nom = (TH1D*) h_get->Clone("mu_pTrel_s_nom");
  h_get = project_flavor(mu_pTrel_2D_nom, -3);
  mu_pTrel_sbar_nom = (TH1D*) h_get->Clone("mu_pTrel_sbar_nom");
  mu_pTrel_s_nom->Add(mu_pTrel_sbar_nom);
  h_get = project_flavor(mu_pTrel_2D_smear, 3);
  mu_pTrel_s_smear = (TH1D*) h_get->Clone("mu_pTrel_s_smear");
  h_get = project_flavor(mu_pTrel_2D_smear, -3);
  mu_pTrel_sbar_smear = (TH1D*) h_get->Clone("mu_pTrel_sbar_smear");
  mu_pTrel_s_smear->Add(mu_pTrel_sbar_smear);

  h_get = project_flavor(mu_pTrel_2D_nom, 21);
  mu_pTrel_g_nom = (TH1D*) h_get->Clone("mu_pTrel_g_nom");
  h_get = project_flavor(mu_pTrel_2D_smear, 21);
  mu_pTrel_g_smear = (TH1D*) h_get->Clone("mu_pTrel_g_smear");
  

  // combine the lights
  TH1D *mu_pTrel_light_nom = (TH1D*) mu_pTrel_u_nom->Clone("mu_pTrel_light_nom");
  mu_pTrel_light_nom->Add(mu_pTrel_d_nom);
  mu_pTrel_light_nom->Add(mu_pTrel_s_nom);
  mu_pTrel_light_nom->Add(mu_pTrel_g_nom);
  TH1D *mu_pTrel_light_smear = (TH1D*) mu_pTrel_u_smear->Clone("mu_pTrel_light_smear");
  mu_pTrel_light_smear->Add(mu_pTrel_d_smear);
  mu_pTrel_light_smear->Add(mu_pTrel_s_smear);
  mu_pTrel_light_smear->Add(mu_pTrel_g_smear);

  TH1D *mu_pTrel_all_nom = (TH1D*) mu_pTrel_u_nom->Clone("mu_pTrel_all_nom");
  mu_pTrel_all_nom->Add(mu_pTrel_d_nom);
  mu_pTrel_all_nom->Add(mu_pTrel_s_nom);
  mu_pTrel_all_nom->Add(mu_pTrel_g_nom);
  mu_pTrel_all_nom->Add(mu_pTrel_c_nom);
  mu_pTrel_all_nom->Add(mu_pTrel_b_nom);
  TH1D *mu_pTrel_all_smear = (TH1D*) mu_pTrel_u_smear->Clone("mu_pTrel_all_smear");
  mu_pTrel_all_smear->Add(mu_pTrel_d_smear);
  mu_pTrel_all_smear->Add(mu_pTrel_s_smear);
  mu_pTrel_all_smear->Add(mu_pTrel_g_smear);
  mu_pTrel_all_smear->Add(mu_pTrel_c_smear);
  mu_pTrel_all_smear->Add(mu_pTrel_b_smear);

  
  
  const int N_edge = 12;
  double new_axis[N_edge] = {0,0.2,0.4,0.6,0.8,1.0,1.3,1.6,2.0,2.5,3.0,4.0};

  TH1D *mu_pTrel_all_nom_R, *mu_pTrel_all_smear_R, *mu_pTrel_all_data_R; // rebinned histograms
  mu_pTrel_all_nom_R = (TH1D*) mu_pTrel_all_nom->Rebin(N_edge-1,"mu_pTrel_all_nom_R",new_axis);
  divideByBinwidth(mu_pTrel_all_nom_R);
  mu_pTrel_all_smear_R = (TH1D*) mu_pTrel_all_smear->Rebin(N_edge-1,"mu_pTrel_all_smear_R",new_axis);
  divideByBinwidth(mu_pTrel_all_smear_R);
  mu_pTrel_all_data_R = (TH1D*) mu_pTrel_data->Rebin(N_edge-1,"mu_pTrel_all_data_R",new_axis);
  divideByBinwidth(mu_pTrel_all_data_R);
  


  // r->Draw();
  TCanvas *canv_all = new TCanvas("canv_all","canv_all",700,700);
  canv_all->cd();
  TPad *pad_all_1 = new TPad("pad_all_1","pad_all_1",0,0.4,1,1);
  TPad *pad_all_2 = new TPad("pad_all_2","pad_all_2",0,0,1,0.4);
  pad_set_margins_bottom(pad_all_2);
  pad_set_margins_top(pad_all_1);
  pad_all_1->Draw();
  pad_all_2->Draw();
  pad_all_1->cd();
  
  mu_pTrel_all_smear_R->GetYaxis()->SetTitle("a.u.");
  mu_pTrel_all_smear_R->SetTitle("");
  mu_pTrel_all_smear_R->SetStats(0);
  
  mu_pTrel_all_nom_R->SetLineColor(kBlue-4);
  mu_pTrel_all_nom_R->SetLineWidth(2);
  mu_pTrel_all_smear_R->SetLineColor(kRed-4);
  mu_pTrel_all_smear_R->SetLineWidth(2);
  mu_pTrel_all_data_R->SetLineColor(kGreen+2);
  mu_pTrel_all_data_R->SetLineWidth(2);

  mu_pTrel_all_smear_R->Scale(1./mu_pTrel_all_smear_R->Integral());
  mu_pTrel_all_nom_R->Scale(1./mu_pTrel_all_nom_R->Integral());
  mu_pTrel_all_data_R->Scale(1./mu_pTrel_all_data_R->Integral());


  TH1D *r1 = (TH1D*) mu_pTrel_all_smear_R->Clone("r");
  r1->Divide(mu_pTrel_all_data_R,mu_pTrel_all_smear_R,1,1,"B");
  TH1D *r2 = (TH1D*) mu_pTrel_all_nom_R->Clone("r");
  r2->Divide(mu_pTrel_all_data_R,mu_pTrel_all_nom_R,1,1,"B");
  

  
  mu_pTrel_all_smear_R->Draw();
  mu_pTrel_all_nom_R->Draw("same");
  mu_pTrel_all_data_R->Draw("same");

  TLegend *leg = new TLegend(0.6,0.65,0.78,0.78);
  leg->SetBorderSize(0);
  leg->AddEntry(mu_pTrel_all_nom_R,"nom. JER");
  leg->AddEntry(mu_pTrel_all_smear_R,"JER-smeared");
  leg->AddEntry(mu_pTrel_all_data_R,"PbPb data");
  leg->Draw();

  TLatex *la = new TLatex();
  la->SetTextSize(0.04);
  la->SetTextFont(42);
  la->DrawLatexNDC(0.6,0.5,"PYTHIA+HYDJET, all-jets");
  la->DrawLatexNDC(0.6,0.4,jet_pt_string);
  la->DrawLatexNDC(0.6,0.3,"#it{p}_{T}^{#mu} > 7 GeV");

  pad_all_2->cd();
  r1->GetXaxis()->SetTitle("muon #it{p}_{T}^{rel} [GeV]");
  r1->GetYaxis()->SetTitle("DATA / MC");
  r1->SetTitle("");
  r1->Draw();
  r2->Draw("same");

  TLine *li = new TLine();
  li->SetLineStyle(7);
  li->DrawLine(0,1,4,1);
  
  canv_all->SaveAs(canv_save_string);
  
  
}


