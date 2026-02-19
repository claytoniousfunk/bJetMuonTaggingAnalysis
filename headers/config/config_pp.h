int isMC_status = 0;
int AASetup_status = 0;
TString jetTreeString = "jetTree";
TString muonTreeString = "muonTree";
TString hltString = "hltTree";
// event filters
const int NeventFilters_SingleMuon = 3;
std::string eventFilters_SingleMuon[NeventFilters_SingleMuon] = {"pPAprimaryVertexFilter","HBHENoiseFilterResultRun2Loose","pBeamScrapingFilter"};
const int NeventFilters_MinBias = 1;
std::string eventFilters_MinBias[NeventFilters_MinBias] = {"pprimaryVertexFilter"};
// jet options
bool doJetTrkMaxFilter = true;
bool doEtaPhiMask = false;
bool doWDecayFilter = true;
bool applyJet60Trigger = false;
bool applyJet80Trigger = false;
bool applyJet100Trigger = false;
bool applyMu12TriggerEfficiencyCorrection = false;
bool fillMu5 = false;
bool fillMu7 = false;
bool fillMu12 = true;
// spectra alterations
bool doJESCorrection = false;
bool doBJetNeutrinoEnergyShift = false;
bool doJERCorrection = false;
// options for systematic studies
bool apply_JER_smear = false;
bool apply_JEU_shift_up = false;
bool apply_JEU_shift_down = false;
// select dataset
bool doSingleMuonSample = true;
bool doMinBiasSample = false;
bool doHighEGJetSample = false;

