
TString getDatasetName(bool doSingleMuonSample = true,
		       bool doMinBiasSample = false,
		       bool doHardProbesSample = false)
{

  TString result = "";

  if(doSingleMuonSample) result="/eos/cms/store/group/phys_heavyions/cbennett/skims/output_skims_HISingleMuon_HIRun2018A-04Apr2019-v1_2026-04-28/";
  //if(doSingleMuonSample) result="/eos/cms/store/group/phys_heavyions/cbennett/skims/output_skims_HISingleMuon_HIRun2018A-04Apr2019-v1_2026-05-04/";
  //if(doSingleMuonSample) result="/eos/user/c/cbennett/skims/output_PbPb_SingleMuon_withWTA/";
  //if(doSingleMuonSample) result="/eos/cms/store/group/phys_heavyions/cbennett/skims/output_skims_PbPb_SingleMuon_2026-04-22/";
  else if(doMinBiasSample) result="/eos/user/c/cbennett/skims/output_skims_PbPb_HIMinimumBias0/";
  //else if(doMinBiasSample) result="/eos/cms/store/group/phys_heavyions/cbennett/skims/output_skims_PbPb_MinBias_withMinBiasTrigger/";
  else if(doHardProbesSample) result="/eos/cms/store/group/phys_heavyions/cbennett/skims/output_skims_HIHardProbes_HIRun2018A-04Apr2019-v1_103X_dataRun2_Prompt_fixEcalADCToGeV_v1_2026-05-04/";
  else{};

  return result;


}
