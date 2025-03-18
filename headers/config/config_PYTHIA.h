// general analysis options
int isMC_status = 1;
int AASetup_status = 0;
TString jetTreeString = "jetTree";
TString muonTreeString = "muonTree";
TString hltString = "hltTree";
const int NeventFilters = 3;
std::string eventFilters[NeventFilters] = {"pPAprimaryVertexFilter","HBHENoiseFilterResultRun2Loose","pBeamScrapingFilter"};
// options for systematic studies
bool apply_JER_smear = false;
bool apply_JEU_shift_up = false;
bool apply_JEU_shift_down = false;
// options to skip genParticle loops (for forests with no genParticle info)
bool skipGenParticles = false;
// reweighting functions
bool doVzReweight = true;
bool doJetPtReweight = true;
// jet-based filers
bool doGenJetPthatFilter = false;
bool doLeadingXjetDumpFilter = false;
bool doXdumpReweight = false;
bool doJetTrkMaxFilter = true;
bool doRemoveHYDJETjet = true;
bool doEtaPhiMask = false;
// jet-energy alterations
bool doBJetEnergyShift = false;
bool doBJetNeutrinoEnergyShift = false;
bool doNeutrinoEnergyAddition = false;
bool doInclNeutrinoEnergySubtraction = false;
bool apply_genJetPt_smear = false;
bool doJERCorrection = false;
// muptrel reweight
bool doMuPtRelReweight = false;
bool doHadronPtRelReweight = false;
bool doHadronPtRelReweightToMuon = true;
bool doDRReweight = true;
bool doWeightCut = false;


