#include "TDatime.h"

TString configureOutputDatasetName(bool doSingleMuonSample,
				   bool doMinBiasSample,
				   bool doHighEGJetSample,
				   bool applyJet60Trigger,
				   bool applyJet80Trigger,
				   bool applyJet100Trigger,
				   bool applyMu12TriggerEfficiencyCorrection,
				   bool doJetTrkMaxFilter,
				   bool doEtaPhiMask,
				   bool doWDecayFilter,
				   bool doJESCorrection,
				   bool doBJetNeutrinoEnergyShift,
				   bool doJERCorrection,
				   bool apply_JER_smear,
				   bool apply_JEU_shift_up,
				   bool apply_JEU_shift_down,
				   double muPtCut,
				   double muPtMaxCut,
				   bool fillMu5,
				   bool fillMu7,
				   bool fillMu12)
{

  TString result = "output";
  result.Append("_pp");

  TString datasetIndicator = "";
  if(doSingleMuonSample) datasetIndicator = "_SingleMuon";
  else if(doMinBiasSample) datasetIndicator = "_MinBias";
  else if(doHighEGJetSample) datasetIndicator = "_HighEGJet";
  else{};
  result.Append(datasetIndicator);

  // general information
  if(applyJet60Trigger) result.Append("_Jet60HLT");
  if(applyJet80Trigger) result.Append("_Jet80HLT");
  if(applyJet100Trigger) result.Append("_Jet100HLT");
  if(fillMu5) result.Append(Form("_mu5_pTmu-%1.0fto%1.0f_hybridSoft",muPtCut,muPtMaxCut));
  else if(fillMu7) result.Append(Form("_mu7_pTmu-%1.0fto%2.0f_hybridSoft",muPtCut,muPtMaxCut));
  else if(fillMu12) result.Append(Form("_mu12_pTmu-%2.0fto%3.0f_tight",muPtCut,muPtMaxCut));
  else{};
  if(applyMu12TriggerEfficiencyCorrection) result.Append("_mu12TriggerEfficiencyCorrection");
	
  // jet-based filters
  if(doJetTrkMaxFilter) result.Append("_jetTrkMaxFilter");
  if(doEtaPhiMask) result.Append("_etaPhiMask");
  if(doWDecayFilter) result.Append("_WDecayFilter");
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
