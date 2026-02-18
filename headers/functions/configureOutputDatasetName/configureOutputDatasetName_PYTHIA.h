#include "TDatime.h"

TString configureOutputDatasetName(TString generator,
				   bool doDiJetSample,
				   double pThat,
				   bool doVzReweight,
				   bool doJetPtReweight,
				   bool doGenJetPthatFilter,
				   bool doLeadingXjetDumpFilter,
				   bool doXdumpReweight,
				   bool doJetTrkMaxFilter,
				   bool doRemoveHYDJETjet,
				   bool doEtaPhiMask,
				   bool doDRReweight,
				   bool doWeightCut,
				   bool doJetAxisSmearing,
				   double mu_phi,
				   double sigma_phi,
				   double mu_eta,
				   double sigma_eta,
				   bool doHadronPtRelReweight,
				   bool doHadronPtRelReweightToMuon,
				   bool doBJetEnergyShift,
				   bool doBJetNeutrinoEnergyShift,
				   bool doJERCorrection,
				   bool doJESCorrection,		   
				   bool apply_JER_smear,
				   bool apply_JEU_shift_up,
				   bool apply_JEU_shift_down,
				   bool applyJet60Trigger,
				   bool applyJet80Trigger,
				   bool applyMu12TriggerEfficiencyCorrection,
				   double muPtCut,
				   double muPtMaxCut,
				   bool fillMu5,
				   bool fillMu7,
				   bool fillMu12)
{

  TString result = "output";
  result.Append(Form("_%s",generator.Data()));

  TString datasetIndicator = "";
  if(doDiJetSample) datasetIndicator = "_DiJet";
  result.Append(datasetIndicator);
  if(applyJet60Trigger) result.Append("_Jet60HLT");
  if(applyJet80Trigger) result.Append("_Jet80HLT");
  // general information
  result.Append(Form("_pThat-%2.0f",pThat));
  if(fillMu5) result.Append(Form("_mu5_pTmu-%1.0fto%1.0f_hybridSoft",muPtCut,muPtMaxCut));
  else if(fillMu7) result.Append(Form("_mu7_pTmu-%1.0fto%2.0f_hybridSoft",muPtCut,muPtMaxCut));
  else if(fillMu12) result.Append(Form("_mu12_pTmu-%2.0fto%3.0f_tight",muPtCut,muPtMaxCut));
  else{};
  if(applyMu12TriggerEfficiencyCorrection) result.Append("_mu12TriggerEfficiencyCorrection");
  // event-based reweights
  if(doVzReweight) result.Append("_vzReweight");
  if(doJetPtReweight) result.Append("_jetPtReweight");
  // jet-based filters
  if(doGenJetPthatFilter) result.Append("_genJetPthatFilter");
  if(doLeadingXjetDumpFilter) result.Append("_leadingXjetDumpFilter");
  if(doXdumpReweight) result.Append("_xDumpReweight");
  if(doJetTrkMaxFilter) result.Append("_jetTrkMaxFilter");
  if(doRemoveHYDJETjet) result.Append("_removeHYDJETjet0p35CutOnGen");
  if(doEtaPhiMask) result.Append("_etaPhiMask");
  if(doDRReweight) result.Append("_dRReweight");
  if(doJetAxisSmearing) result.Append(Form("_jetAxisSmear_muPhi-%1.3f_sigmaPhi-%1.3f_muEta-%1.3f_sigmaEta-%1.3f",mu_phi,sigma_phi,mu_eta,sigma_eta));
  // lesser-likely customizations
  if(doWeightCut) result.Append("_weightCut");
  if(doHadronPtRelReweight) result.Append("_hadronPtRelReweight");
  if(doHadronPtRelReweightToMuon) result.Append("_hadronPtRelReweightToMuon");
  if(doBJetEnergyShift) result.Append("_bJetEnergyShift");
  if(doBJetNeutrinoEnergyShift) result.Append("_BJetNeutrinoEnergyShift");
  if(doJERCorrection) result.Append("_JERCorrection");
  if(doJESCorrection) result.Append("_JESCorrection");
  if(apply_JER_smear) result.Append("_applyJERSmear");
  if(apply_JEU_shift_up) result.Append("_applyJEUShiftUp");
  if(apply_JEU_shift_down) result.Append("_applyJEUShiftDown");
  
  
  TDatime dt;
  result.Append(Form("_%i-%i-%i",dt.GetYear(),dt.GetMonth(),dt.GetDay()));
  
  return result;

}
