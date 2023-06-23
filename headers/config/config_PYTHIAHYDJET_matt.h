int isMC_status = 1;
int AASetup_status = 0;
TString jetTreeString = "akFlowPuCs4PFJetAnalyzer";
TString hltString = "hltanalysis";
const int NeventFilters = 4;
std::string eventFilters[NeventFilters] = {"pprimaryVertexFilter", "collisionEventSelectionAODv2", "pclusterCompatibilityFilter", "pBeamScrapingFilter"};
