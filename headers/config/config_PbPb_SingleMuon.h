int isMC_status = 0;
int AASetup_status = 0;
TString jetTreeString = "akCs4PFJetAnalyzer";
TString muonTreeString = "ggHiNtuplizerGED";
TString hltString = "hltanalysis";
const int NeventFilters = 5;
std::string eventFilters[NeventFilters] = {"pprimaryVertexFilter","HBHENoiseFilterResultRun2Loose","collisionEventSelectionAODv2","phfCoincFilter3Th4","pclusterCompatibilityFilter"};

