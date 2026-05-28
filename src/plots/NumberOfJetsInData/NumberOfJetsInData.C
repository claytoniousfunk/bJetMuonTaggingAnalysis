
#include "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/headers/goldenFileNames.h"

double integrate(TH1D *h, double x_low, double x_high){

  double result = 0.0;

  double small_shift = 0.001;

  int bin_low = h->GetXaxis()->FindBin(x_low + small_shift);
  int bin_high = h->GetXaxis()->FindBin(x_high - small_shift);

  double S = 0.0; // integral
  double dS = 0.0;
  for(int i = bin_low; i < bin_high+1; i++){
    dS = h->GetBinContent(i);
    S += dS;
  }

  result = S;
  return result;
  
}


void NumberOfJetsInData(double jetPt_low = 80,
			double jetPt_high = 500){

  TFile *f_pp_mu5 = TFile::Open(goldenFile_pp_SingleMuon_mu5);
  TFile *f_pp_mu7 = TFile::Open(goldenFile_pp_SingleMuon_mu7);
  TFile *f_pp_mu12 = TFile::Open(goldenFile_pp_SingleMuon_mu12);

  TFile *f_PbPb_mu5 = TFile::Open(goldenFile_PbPb_SingleMuon_mu5);
  TFile *f_PbPb_mu7 = TFile::Open(goldenFile_PbPb_SingleMuon_mu7);
  TFile *f_PbPb_mu12 = TFile::Open(goldenFile_PbPb_SingleMuon_mu12);

  TH1D *h_muTaggedJets_pp_mu5, *h_muTaggedJets_pp_mu7, *h_muTaggedJets_pp_mu12;
  TH1D *h_muTaggedJets_C4_mu5, *h_muTaggedJets_C4_mu7, *h_muTaggedJets_C4_mu12;
  TH1D *h_muTaggedJets_C3_mu5, *h_muTaggedJets_C3_mu7, *h_muTaggedJets_C3_mu12;
  TH1D *h_muTaggedJets_C2_mu5, *h_muTaggedJets_C2_mu7, *h_muTaggedJets_C2_mu12;
  TH1D *h_muTaggedJets_C1_mu5, *h_muTaggedJets_C1_mu7, *h_muTaggedJets_C1_mu12;

  TH1D *h_muons_pp_mu5, *h_muons_pp_mu7, *h_muons_pp_mu12;
  TH1D *h_muons_C4_mu5, *h_muons_C4_mu7, *h_muons_C4_mu12;
  TH1D *h_muons_C3_mu5, *h_muons_C3_mu7, *h_muons_C3_mu12;
  TH1D *h_muons_C2_mu5, *h_muons_C2_mu7, *h_muons_C2_mu12;
  TH1D *h_muons_C1_mu5, *h_muons_C1_mu7, *h_muons_C1_mu12;

  f_pp_mu5->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn",h_muTaggedJets_pp_mu5);
  f_pp_mu7->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn",h_muTaggedJets_pp_mu7);
  f_pp_mu12->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn",h_muTaggedJets_pp_mu12);

  f_PbPb_mu5->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C4",h_muTaggedJets_C4_mu5);
  f_PbPb_mu7->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C4",h_muTaggedJets_C4_mu7);
  f_PbPb_mu12->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C4",h_muTaggedJets_C4_mu12);

  f_PbPb_mu5->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C3",h_muTaggedJets_C3_mu5);
  f_PbPb_mu7->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C3",h_muTaggedJets_C3_mu7);
  f_PbPb_mu12->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C3",h_muTaggedJets_C3_mu12);

  f_PbPb_mu5->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C2",h_muTaggedJets_C2_mu5);
  f_PbPb_mu7->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C2",h_muTaggedJets_C2_mu7);
  f_PbPb_mu12->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C2",h_muTaggedJets_C2_mu12);

  f_PbPb_mu5->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C1",h_muTaggedJets_C1_mu5);
  f_PbPb_mu7->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C1",h_muTaggedJets_C1_mu7);
  f_PbPb_mu12->GetObject("h_inclRecoJetPt_inclRecoMuonTag_triggerOn_C1",h_muTaggedJets_C1_mu12);

  double Njet_pp_mu5, Njet_pp_mu7, Njet_pp_mu12;
  double Njet_C4_mu5, Njet_C4_mu7, Njet_C4_mu12;
  double Njet_C3_mu5, Njet_C3_mu7, Njet_C3_mu12;
  double Njet_C2_mu5, Njet_C2_mu7, Njet_C2_mu12;
  double Njet_C1_mu5, Njet_C1_mu7, Njet_C1_mu12;
  
  Njet_pp_mu5 = integrate(h_muTaggedJets_pp_mu5,jetPt_low,jetPt_high);
  Njet_pp_mu7 = integrate(h_muTaggedJets_pp_mu7,jetPt_low,jetPt_high);
  Njet_pp_mu12 = integrate(h_muTaggedJets_pp_mu12,jetPt_low,jetPt_high);

  Njet_C4_mu5 = integrate(h_muTaggedJets_C4_mu5,jetPt_low,jetPt_high);
  Njet_C4_mu7 = integrate(h_muTaggedJets_C4_mu7,jetPt_low,jetPt_high);
  Njet_C4_mu12 = integrate(h_muTaggedJets_C4_mu12,jetPt_low,jetPt_high);

  Njet_C3_mu5 = integrate(h_muTaggedJets_C3_mu5,jetPt_low,jetPt_high);
  Njet_C3_mu7 = integrate(h_muTaggedJets_C3_mu7,jetPt_low,jetPt_high);
  Njet_C3_mu12 = integrate(h_muTaggedJets_C3_mu12,jetPt_low,jetPt_high);

  Njet_C2_mu5 = integrate(h_muTaggedJets_C2_mu5,jetPt_low,jetPt_high);
  Njet_C2_mu7 = integrate(h_muTaggedJets_C2_mu7,jetPt_low,jetPt_high);
  Njet_C2_mu12 = integrate(h_muTaggedJets_C2_mu12,jetPt_low,jetPt_high);

  Njet_C1_mu5 = integrate(h_muTaggedJets_C1_mu5,jetPt_low,jetPt_high);
  Njet_C1_mu7 = integrate(h_muTaggedJets_C1_mu7,jetPt_low,jetPt_high);
  Njet_C1_mu12 = integrate(h_muTaggedJets_C1_mu12,jetPt_low,jetPt_high);

  std::cout << "Njet_pp_mu5(" << jetPt_low << " < jet-pT (GeV) < " << jetPt_high << ") = " << Njet_pp_mu5 << "\n";
  std::cout << "Njet_pp_mu7(" << jetPt_low << " < jet-pT (GeV) < " << jetPt_high << ") = " << Njet_pp_mu7 << "\n";
  std::cout << "Njet_pp_mu12(" << jetPt_low << " < jet-pT (GeV) < " << jetPt_high << ") = " << Njet_pp_mu12 << "\n";

  std::cout << "Njet_C4_mu5(" << jetPt_low << " < jet-pT (GeV) < " << jetPt_high << ") = " << Njet_C4_mu5 << "\n";
  std::cout << "Njet_C4_mu7(" << jetPt_low << " < jet-pT (GeV) < " << jetPt_high << ") = " << Njet_C4_mu7 << "\n";
  std::cout << "Njet_C4_mu12(" << jetPt_low << " < jet-pT (GeV) < " << jetPt_high << ") = " << Njet_C4_mu12 << "\n";

  std::cout << "Njet_C3_mu5(" << jetPt_low << " < jet-pT (GeV) < " << jetPt_high << ") = " << Njet_C3_mu5 << "\n";
  std::cout << "Njet_C3_mu7(" << jetPt_low << " < jet-pT (GeV) < " << jetPt_high << ") = " << Njet_C3_mu7 << "\n";
  std::cout << "Njet_C3_mu12(" << jetPt_low << " < jet-pT (GeV) < " << jetPt_high << ") = " << Njet_C3_mu12 << "\n";

  std::cout << "Njet_C2_mu5(" << jetPt_low << " < jet-pT (GeV) < " << jetPt_high << ") = " << Njet_C2_mu5 << "\n";
  std::cout << "Njet_C2_mu7(" << jetPt_low << " < jet-pT (GeV) < " << jetPt_high << ") = " << Njet_C2_mu7 << "\n";
  std::cout << "Njet_C2_mu12(" << jetPt_low << " < jet-pT (GeV) < " << jetPt_high << ") = " << Njet_C2_mu12 << "\n";

  std::cout << "Njet_C1_mu5(" << jetPt_low << " < jet-pT (GeV) < " << jetPt_high << ") = " << Njet_C1_mu5 << "\n";
  std::cout << "Njet_C1_mu7(" << jetPt_low << " < jet-pT (GeV) < " << jetPt_high << ") = " << Njet_C1_mu7 << "\n";
  std::cout << "Njet_C1_mu12(" << jetPt_low << " < jet-pT (GeV) < " << jetPt_high << ") = " << Njet_C1_mu12 << "\n";

  


}
