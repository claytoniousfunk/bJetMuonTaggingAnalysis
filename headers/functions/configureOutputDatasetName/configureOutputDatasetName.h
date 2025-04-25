

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
				   bool doJERCorrection,
				   bool apply_JER_smear,
				   bool apply_JEU_shift_up,
				   bool apply_JEU_shift_down)
{

  TString result = "output";
  result.Append(Form("_%s",generator.Data());

  TString datasetIndicator = "";
  if(doMuJetSample) datasetIndicator = "_MuJet";
  else if(doBJetSample) datasetIndicator = "_BJet";
  else if(doDiJetSample) datasetIndicator = "_DiJet";
  else if(doDiJetSample_batch1) datasetIndicator = "_DiJet_batch1";
  else if(doDiJetSample_batch2) datasetIndicator = "_DiJet_batch2";
  else if(doDiJetSample_batch3) datasetIndicator = "_DiJet_batch3";
  else if(doDiJetSample_batch4) datasetIndicator = "_DiJet_batch4";
  else if(doDiJetSample_batch5) datasetIndicator = "_DiJet_batch5";
  else if(doDiJetSample_batch6) datasetIndicator = "_DiJet_batch6";
  else if(doDiJetSample_batch7) datasetIndicator = "_DiJet_batch7";
  else if(doDiJetSample_batch8) datasetIndicator = "_DiJet_batch8";
  else if(doDiJetSample_batch9) datasetIndicator = "_DiJet_batch9";
  else if(doDiJetSample_batch10) datasetIndicator = "_DiJet_batch10";
  else if(doDiJetSample_batch11) datasetIndicator = "_DiJet_batch11";
  else if(doDiJetSample_batch12) datasetIndicator = "_DiJet_batch12";
  else if(doDiJetSample_batch13) datasetIndicator = "_DiJet_batch13";
  else if(doDiJetSample_batch14) datasetIndicator = "_DiJet_batch14";
  else if(doDiJetSample_batch15) datasetIndicator = "_DiJet_batch15";
  else{};

  result.Append(datasetIndicator);
  result.Append(Form("_pThat-%2.0f",pThat));
  result.Append("_mu12_pTmu-14_tight");
  // event-based reweights
  if(doVzReweight) result.Append("_vzReweight");
  if(doHiBinReweight) result.Append("_hiBinReweight");
  if(doJetPtReweight) result.Append("_jetPtReweight");
  // jet-based filters
  if(doGenJetPthatFilter) result.Append("_genJetPthatFilter");
  if(doLeadingXjetDumpFilter) result.Append("_leadingXjetDumpFilter");
  if(doXdumpReweight) result.Append("_xDumpReweight");
  if(doJetTrkMaxFilter) result.Append("_jetTrkMaxFilter");
  if(doRemoveHYDJETjet) result.Append("_removeHYDJETjet0p45");
  if(doEtaPhiMask) result.Append("_etaPhiMask");
  if(doDRReweight) result.Append("_dRReweight");
  // lesser-likely customizations
  if(doWeightCut) result.Append("_weightCut");
  if(doHadronPtRelReweight) result.Append("_hadronPtRelReweight");
  if(doBJetEnergyShift) result.Append("_bJetEnergyShift");
  if(doJERCorrection) result.Append("_JERCorrection");
  if(apply_JER_smear) result.Append("_applyJERSmear");
  if(apply_JEU_shift_up) result.Append("_applyJEUShiftUp");
  if(apply_JEU_shift_down) result.Append("_applyJEUShiftDown");

  return result;

}
