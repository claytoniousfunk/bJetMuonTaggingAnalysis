TString getInputFileName(bool doSingleMuonSample = true,
			 bool doMinBiasSample = false,
			 bool doHighEGJetSample = false)
{

  TString result = "";
  
  if(doSingleMuonSample) result="pp_SingleMuon_skim_output";
  else if(doMinBiasSample) result="pp_MinBias_skim_output";
  else if(doHighEGJetSample) result="pp_skim_output";
  else{};

  return result;

}
