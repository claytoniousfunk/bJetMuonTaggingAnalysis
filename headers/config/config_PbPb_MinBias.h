int isMC_status = 0;
int AASetup_status = 0;
TString jetTreeString = "akCs4PFJetAnalyzer";
TString muonTreeString = "ggHiNtuplizer";
TString hltString = "hltanalysis";
const int NeventFilters = 2;
std::string eventFilters[NeventFilters] = {"pprimaryVertexFilter", "pclusterCompatibilityFilter"};
bool doJetTrkMaxFilter = true;
bool doEtaPhiMask = true;

