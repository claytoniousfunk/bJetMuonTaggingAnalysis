#include "TDatime.h"

TString configureOutputDatasetName(TString generator,
				   bool doDiJetSample,
				   bool doMuJetSample,
				   bool doBJetSample,
				   bool doDiJetSample_batch1,
				   bool doDiJetSample_batch2,
				   bool doDiJetSample_batch3,
				   bool doDiJetSample_batch4,
				   bool doDiJetSample_batch5,
				   bool doDiJetSample_batch6,
				   bool doDiJetSample_batch7,
				   bool doDiJetSample_batch8,
				   bool doDiJetSample_batch9,
				   bool doDiJetSample_batch10,
				   bool doDiJetSample_batch11,
				   bool doDiJetSample_batch12,
				   bool doDiJetSample_batch13,
				   bool doDiJetSample_batch14,
				   bool doDiJetSample_batch15,
				   double pThat,
				   bool doVzReweight,
				   bool doHiBinReweight,
				   bool doJetPtReweight,
				   bool doGenJetPthatFilter,
				   bool doLeadingXjetDumpFilter,
				   bool doXdumpReweight,
				   bool doJetTrkMaxFilter,
				   bool doRemoveHYDJETjet,
				   bool doEtaPhiMask,
				   bool doDRReweight,
				   bool doWeightCut,				   
				   bool doHadronPtRelReweight,
				   bool doBJetEnergyShift,
				   bool doBJetNeutrinoEnergyShift,				   
				   bool doJERCorrection,
				   bool doJESCorrection,				   
				   bool apply_JER_smear,
				   bool apply_JEU_shift_up,
				   bool apply_JEU_shift_down,
				   int hiBinShift,
				   bool applyJet60Trigger,
				   bool applyJet80Trigger)
{

  TString result = "output";
  result.Append(Form("_%s_response",generator.Data()));

  TString datasetIndicator = "";  
  datasetIndicator = "_DiJet";
  result.Append(datasetIndicator);
  
  result.Append(Form("_pThat-%2.0f",pThat));
  if(applyJet60Trigger) result.Append("_Jet60HLT");
  if(applyJet80Trigger) result.Append("_Jet80HLT");
  result.Append("_mu12_pTmu-14_tight");
  // event-based reweights
  if(doVzReweight) result.Append("_vzReweight");
  if(doHiBinReweight) result.Append("_hiBinReweight");
  result.Append(Form("_hiBinShift-%i",hiBinShift));
  if(doJetPtReweight) result.Append("_jetPtReweight");
  // jet-based filters
  if(doGenJetPthatFilter) result.Append("_genJetPthatFilter");
  if(doLeadingXjetDumpFilter) result.Append("_leadingXjetDumpFilter");
  if(doXdumpReweight) result.Append("_xDumpReweight");
  if(doJetTrkMaxFilter) result.Append("_jetTrkMaxFilter");
  if(doRemoveHYDJETjet) result.Append("_removeHYDJETjet0p35CutOnGen");
  if(doEtaPhiMask) result.Append("_etaPhiMask");
  if(doDRReweight) result.Append("_dRReweight");
  /* if(doJetAxisSmearing) result.Append(Form("_jetAxisSmear_muPhi-%1.3f_sigmaPhi-%1.3f_muEta-%1.3f_sigmaEta-%1.3f",mu_phi,sigma_phi,mu_eta,sigma_eta)); */
  // lesser-likely customizations
  if(doWeightCut) result.Append("_weightCut");
  if(doHadronPtRelReweight) result.Append("_hadronPtRelReweight");
  if(doBJetEnergyShift) result.Append("_bJetEnergyShift");
  if(doJERCorrection) result.Append("_JERCorrection");
  if(doJESCorrection) result.Append("_JESCorrection");
  if(apply_JER_smear) result.Append("_applyJERSmear");
  if(apply_JEU_shift_up) result.Append("_applyJEUShiftUp");
  if(apply_JEU_shift_down) result.Append("_applyJEUShiftDown");
  if(doBJetNeutrinoEnergyShift) result.Append("_BJetNeutrinoEnergyShift");

  
  TDatime dt;
  result.Append(Form("_%i-%i-%i",dt.GetYear(),dt.GetMonth(),dt.GetDay()));
  
  return result;

}
