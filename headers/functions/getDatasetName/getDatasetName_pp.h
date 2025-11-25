
TString getDatasetName(bool doSingleMuonSample = true,
		       bool doMinBiasSample = false,
		       bool doHighEGJetSample = false)
{

  TString result = "";
  
  if(doSingleMuonSample) result="/eos/user/c/cbennett/skims/output_pp_SingleMuon/";
  //else if(doMinBiasSample) result="/eos/user/c/cbennett/skims/output_skims_pp_HIZeroBias1_alt/";
  else if(doMinBiasSample) result="/eos/user/c/cbennett/skims/output_skims_pp_HIZeroBias1/";
  else if(doHighEGJetSample) result="/eos/cms/store/group/phys_heavyions/cbennett/skims/output_skims_pp_HighEGJet/";
  else{};

  return result;


}
