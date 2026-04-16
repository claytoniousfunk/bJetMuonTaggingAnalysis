// general analysis options
int isMC_status = 1;
int AASetup_status = 1;
TString jetTreeString = "jetTree";
TString muonTreeString = "muonTree";
TString hltString = "hltTree";
const int NeventFilters = 2;
std::string eventFilters[NeventFilters] = {"pprimaryVertexFilter", "pclusterCompatibilityFilter"};
// options for systematic studies
bool apply_JER_smear = false;
bool apply_JEU_shift_up = false;
bool apply_JEU_shift_down = false;
// options to skip genParticle loops (for forests with no genParticle info)
bool skipGenParticles = true; // set TRUE for MuJet and BJet datasets
// reweighting functions
bool doHiBinReweight = false;
bool doVzReweight = false;
bool doJetPtReweight = false;
// jet-based filters
bool doGenJetPthatFilter = false;
bool doLeadingXjetDumpFilter = false;
bool doXdumpReweight = false;
bool doJetTrkMaxFilter = true;
bool doRemoveHYDJETjet = false;
bool doEtaPhiMask = false;
bool doBJetEnergyShift = false;
bool doJERCorrection = false;
bool doJESCorrection = false;
bool doHadronPtRelReweight = false;
bool doHadronPtRelReweightToMuon = false;
bool doDRReweight = false;
bool doWeightCut = false;
bool doJetAxisSmearing = false;
bool doWDecayFilter = true;
bool doBJetSpectraReweightToData = false;
bool doPThatCorrelationFilter = false;
// shifting the hiBin distribution by this amount
int hiBinShift = 10;
// jet-alterations for closure
bool doBJetNeutrinoEnergyShift = false;
// experimental filters
bool onlyOneMuonTaggedJetPerEvent = false;
// jet-axis smearing parameters
double mu_phi = 0.0;
double sigma_phi = 0.005;
double mu_eta = 0.0;
double sigma_eta = 0.005;
// stuff for dataset naming
TString generator = "HYDJET";
// jet triggers
bool applyJet60Trigger = false;
bool applyJet80Trigger = false;
bool applyMu12TriggerEfficiencyCorrection = false;
bool fillMu5 = false;
bool fillMu7 = false;
bool fillMu12 = true;
