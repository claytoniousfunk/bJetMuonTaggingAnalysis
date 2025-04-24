TString getInputFileName(bool doDiJetSample = true,
			 bool doMuJetSample = false,
			 bool doBJetSample = false,
			 bool doDiJetSample_batch1 = false,
			 bool doDiJetSample_batch2 = false,
			 bool doDiJetSample_batch3 = false,
			 bool doDiJetSample_batch4 = false,
			 bool doDiJetSample_batch5 = false,
			 bool doDiJetSample_batch6 = false,
			 bool doDiJetSample_batch7 = false,
			 bool doDiJetSample_batch8 = false,
			 bool doDiJetSample_batch9 = false,
			 bool doDiJetSample_batch10 = false,
			 bool doDiJetSample_batch11 = false,
			 bool doDiJetSample_batch12 = false,
			 bool doDiJetSample_batch13 = false,
			 bool doDiJetSample_batch14 = false,
			 bool doDiJetSample_batch15 = false)
{

  TString result = "";
  
  if(doMuJetSample) result = "PYTHIAHYDJET_MuJet_skim_output";
  else if(doBJetSample) result = "PYTHIAHYDJET_BJet_skim_output";
  else result = "PYTHIAHYDJET_DiJet_skim_output";

  return result;

}
