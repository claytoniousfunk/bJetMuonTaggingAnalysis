int isMC_status = 0;
int AASetup_status = 0;
TString jetTreeString = "jetTree";
TString muonTreeString = "muonTree";
TString hltString = "hltTree";
const int NeventFilters = 2;
std::string eventFilters[NeventFilters] = {"pprimaryVertexFilter", "pclusterCompatibilityFilter"};
bool doJetTrkMaxFilter = false;
bool doEtaPhiMask = false;
bool applyJet60Trigger = false;
bool applyJet80Trigger = false;
bool applyMinBiasTrigger = true;
// experimental filters
bool onlyOneMuonTaggedJetPerEvent = false;
