int isMC_status = 0;
int AASetup_status = 0;
TString jetTreeString = "jetTree";
TString muonTreeString = "muonTree";
TString hltString = "hltTree";
const int NeventFilters = 5;
std::string eventFilters[NeventFilters] = {"pprimaryVertexFilter", "HBHENoiseFilterResultRun2Loose", "collisionEventSelectionAODv2", "phfCoincFilter2Th4", "pclusterCompatibilityFilter"};
bool doJetTrkMaxFilter = true;
bool doEtaPhiMask = false;
bool applyJet60Trigger = false;
bool applyJet80Trigger = false;
bool applyMinBiasTrigger = false;
// experimental filters
bool onlyOneMuonTaggedJetPerEvent = false;

