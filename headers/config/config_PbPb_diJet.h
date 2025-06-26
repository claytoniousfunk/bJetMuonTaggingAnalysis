int isMC_status = 0;
int AASetup_status = 0;
TString jetTreeString = "jetTree";
TString hltString = "hltTree";
TString muonTreeString = "muonTree";
const int NeventFilters = 2;
std::string eventFilters[NeventFilters] = {"pprimaryVertexFilter","pclusterCompatibilityFilter"};
bool doJetTrkMaxFilter = false;
bool doEtaPhiMask = false;
bool applyJet60Trigger = true;
bool applyJet80Trigger = false;
// experimental filters
bool onlyOneMuonTaggedJetPerEvent = false;
