
TString getDatasetName(bool doSingleMuonSample = true,
		       bool doMinBiasSample = false,
		       bool doHardProbesSample = false)
{

  TString result = "";
  
  if(doSingleMuonSample) result="/eos/user/c/cbennett/skims/output_PbPb_SingleMuon_withWTA/";
  else if(doMinBiasSample) result="/eos/user/c/cbennett/skims/output_skims_PbPb_HIMinimumBias0/";
  else if(doHardProbesSample) result="/eos/cms/store/group/phys_heavyions/cbennett/skims/output_skims_PbPb_HardProbes_2/";
  else{};

  return result;


}
