#include "TDatime.h"

TString configureOutputDatasetName(bool doSingleMuonSample,
				   bool doMinBiasSample,
				   bool doHardProbesSample,
				   bool applyJet60Trigger,
				   bool applyJet80Trigger,
				   bool doJetTrkMaxFilter,
				   bool doEtaPhiMask,
				   bool doBJetNeutrinoEnergyShift,
				   bool doJERCorrection,
				   bool apply_JER_smear,
				   bool apply_JEU_shift_up,
				   bool apply_JEU_shift_down)
{

  TString result = "output";
  result.Append("_PbPb");

  TString datasetIndicator = "";
  if(doSingleMuonSample) datasetIndicator = "_SingleMuon";
  else if(doMinBiasSample) datasetIndicator = "_MinBias";
  else if(doHardProbesSample) datasetIndicator = "_HighEGJet";
  else{};
  result.Append(datasetIndicator);

  // general information
  if(applyJet60Trigger) result.Append("_Jet60HLT");
  if(applyJet80Trigger) result.Append("_Jet80HLT");
  result.Append("_mu12_pTmu-14_tight");
	
  // jet-based filters
  if(doJetTrkMaxFilter) result.Append("_jetTrkMaxFilter");
  if(doEtaPhiMask) result.Append("_etaPhiMask");
  if(doBJetNeutrinoEnergyShift) result.Append("_BJetNeutrinoEnergyShift");
  if(doJERCorrection) result.Append("_JERCorrection");
  if(apply_JER_smear) result.Append("_applyJERSmear");
  if(apply_JEU_shift_up) result.Append("_applyJEUShiftUp");
  if(apply_JEU_shift_down) result.Append("_applyJEUShiftDown");
  
  TDatime dt;
  result.Append(Form("_%i-%i-%i",dt.GetYear(),dt.GetMonth(),dt.GetDay()));
  
  return result;

}
