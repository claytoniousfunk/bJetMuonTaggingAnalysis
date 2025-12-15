


void getEntries(int i = 0){

  TFile *f = TFile::Open(Form("/eos/cms/store/group/phys_heavyions/cbennett/skims/output_skims_pp_HighEGJet_cleanup/pp_skim_output_%i.root",i));
  TTree *t = (TTree*)f->Get("evtTree");
  cout << (t ? t->GetEntries() : 0) << endl;

}
