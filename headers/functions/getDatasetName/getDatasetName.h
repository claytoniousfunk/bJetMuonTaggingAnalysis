
TString getDatasetName(bool doDiJetSample = true,
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
  
  if(doDiJetSample) result = "/eos/user/c/cbennett/skims/output_PYTHIAHYDJET_DiJet_withGS_withWTA_2/";
  else if(doMuJetSample) result = "/eos/user/c/cbennett/skims/output_PYTHIAHYDJET_MuJet_withGS_withWTA_2/";
  else if(doBJetSample) result = "/eos/user/c/cbennett/skims/output_PYTHIAHYDJET_BJet_withGS_withWTA_2/";
  else if(doDiJetSample_batch1) result = "/eos/cms/store/group/phys_heavyions/cbennett/skims/dripping-tap/output_skim_PH_DiJet_batch1/";
  else if(doDiJetSample_batch2) result = "/eos/cms/store/group/phys_heavyions/cbennett/skims/dripping-tap/output_skim_PH_DiJet_batch2/";
  else if(doDiJetSample_batch3) result = "/eos/cms/store/group/phys_heavyions/cbennett/skims/dripping-tap/output_skim_PH_DiJet_batch3/";
  else if(doDiJetSample_batch4) result = "/eos/cms/store/group/phys_heavyions/cbennett/skims/dripping-tap/output_skim_PH_DiJet_batch4/";
  else if(doDiJetSample_batch5) result = "/eos/cms/store/group/phys_heavyions/cbennett/skims/dripping-tap/output_skim_PH_DiJet_batch5/";
  else if(doDiJetSample_batch6) result = "/eos/cms/store/group/phys_heavyions/cbennett/skims/dripping-tap/output_skim_PH_DiJet_batch6/";
  else if(doDiJetSample_batch7) result = "/eos/cms/store/group/phys_heavyions/cbennett/skims/dripping-tap/output_skim_PH_DiJet_batch7/";
  else if(doDiJetSample_batch8) result = "/eos/cms/store/group/phys_heavyions/cbennett/skims/dripping-tap/output_skim_PH_DiJet_batch8/";
  else if(doDiJetSample_batch9) result = "/eos/cms/store/group/phys_heavyions/cbennett/skims/dripping-tap/output_skim_PH_DiJet_batch9/";
  else if(doDiJetSample_batch10) result = "/eos/cms/store/group/phys_heavyions/cbennett/skims/dripping-tap/output_skim_PH_DiJet_batch10/";
  else if(doDiJetSample_batch11) result = "/eos/cms/store/group/phys_heavyions/cbennett/skims/dripping-tap/output_skim_PH_DiJet_batch11/";
  else if(doDiJetSample_batch12) result = "/eos/cms/store/group/phys_heavyions/cbennett/skims/dripping-tap/output_skim_PH_DiJet_batch12/";
  else if(doDiJetSample_batch13) result = "/eos/cms/store/group/phys_heavyions/cbennett/skims/dripping-tap/output_skim_PH_DiJet_batch13/";
  else if(doDiJetSample_batch14) result = "/eos/cms/store/group/phys_heavyions/cbennett/skims/dripping-tap/output_skim_PH_DiJet_batch14/";
  else if(doDiJetSample_batch15) result = "/eos/cms/store/group/phys_heavyions/cbennett/skims/dripping-tap/output_skim_PH_DiJet_batch15/";
  else{};

  return result;


}
