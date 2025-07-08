// general analysis options
int isMC_status = 1;
int AASetup_status = 1;
TString jetTreeString = "jetTree";
TString muonTreeString = "muonTree";
TString hltString = "hltTree";
const int NeventFilters = 5;
std::string eventFilters[NeventFilters] = {"pprimaryVertexFilter", "HBHENoiseFilterResultRun2Loose", "collisionEventSelectionAODv2", "phfCoincFilter2Th4", "pclusterCompatibilityFilter"};
// options for systematic studies
bool apply_JER_smear = false;
bool apply_JEU_shift_up = false;
bool apply_JEU_shift_down = false;
// options to skip genParticle loops (for forests with no genParticle info)
bool skipGenParticles = false; // set TRUE for MuJet and BJet datasets
// reweighting functions
bool doHiBinReweight = true;
bool doVzReweight = false;
bool doJetPtReweight = false;
// jet-based filters
bool doGenJetPthatFilter = false;
bool doLeadingXjetDumpFilter = false;
bool doXdumpReweight = false;
bool doJetTrkMaxFilter = true;
bool doRemoveHYDJETjet = true;
bool doEtaPhiMask = false;
bool doBJetEnergyShift = false;
bool doJERCorrection = false;
bool doJESCorrection = false;
bool doHadronPtRelReweight = false;
bool doDRReweight = false;
bool doWeightCut = false;
// shifting the hiBin distribution by this amount
int hiBinShift = 10;
// jet-alterations for closure
bool doBJetNeutrinoEnergyShift = false;
// experimental filters
bool onlyOneMuonTaggedJetPerEvent = false;




// stuff for dataset naming
TString generator = "PYTHIAHYDJET";

// data set
bool doDiJetSample = true;
bool doMuJetSample = false;
bool doBJetSample = false;
bool doDiJetSample_batch1 = false;
bool doDiJetSample_batch2 = false;
bool doDiJetSample_batch3 = false;
bool doDiJetSample_batch4 = false;
bool doDiJetSample_batch5 = false;
bool doDiJetSample_batch6 = false;
bool doDiJetSample_batch7 = false;
bool doDiJetSample_batch8 = false;
bool doDiJetSample_batch9 = false;
bool doDiJetSample_batch10 = false;
bool doDiJetSample_batch11 = false;
bool doDiJetSample_batch12 = false;
bool doDiJetSample_batch13 = false;
bool doDiJetSample_batch14 = false;
bool doDiJetSample_batch15 = false;

