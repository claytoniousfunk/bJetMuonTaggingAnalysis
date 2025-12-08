TString getInputFileName(bool doSingleMuonSample = true,
			 bool doMinBiasSample = false,
			 bool doHardProbesSample = false)
{

  TString result = "";
  
  if(doSingleMuonSample) result="PbPb_SingleMuon_skim_output";
  else if(doMinBiasSample) result="PbPb_MinBias_skim_output";
  else if(doHardProbesSample) result="PbPb_DiJet_skim_output";
  else{};

  return result;

}
