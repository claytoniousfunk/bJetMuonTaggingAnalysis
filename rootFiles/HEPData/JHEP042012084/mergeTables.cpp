/*
  This code merges the y-bins from b-to-inclusive-jet-fraction measurement
  in pp collisions at sqrt(s) = 7 TeV.
  Published in JHEP04(2012)084.

*/

TFile *file_y0to0p5, *file_y0p5to1, *file_y1to1p5;
// cross-section and error for y-bins
TH1D *xSec_y0to0p5, *xSec_y0p5to1, *xSec_y1to1p5;
TH1D *err_xSec_y0to0p5, *err_xSec_y0p5to1, *err_xSec_y1to1p5;
// b-fraction and error for y-bins
TH1D *bFrac_y0to0p5, *bFrac_y0p5to1, *bFrac_y1to1p5;
TH1D *err_bFrac_y0to0p5, *err_bFrac_y0p5to1, *err_bFrac_y1to1p5;
TH1D *sys_bFrac_y0to0p5, *sys_bFrac_y0p5to1, *sys_bFrac_y1to1p5;
TH1D *err_sys_bFrac_y0to0p5, *err_sys_bFrac_y0p5to1, *err_sys_bFrac_y1to1p5;
// calculated b-fraction
TH1D *bFrac_tot;
double weight_sum; // for normalization

TString savePath; // for saving the output
TFile *writeFile;

void mergeTables(){
 
  
  // initialize files and directories
  file_y0to0p5 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/HEPData/JHEP042012084/HEPData-ins1089835-v1-Table_4.root");
  TDirectoryFile *dir_y0to0p5 = (TDirectoryFile*) file_y0to0p5->Get("Table 4");
  
  file_y0p5to1 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/HEPData/JHEP042012084/HEPData-ins1089835-v1-Table_5.root");
  TDirectoryFile *dir_y0p5to1 = (TDirectoryFile*) file_y0p5to1->Get("Table 5");
  
  file_y1to1p5 = TFile::Open("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/rootFiles/HEPData/JHEP042012084/HEPData-ins1089835-v1-Table_6.root");
  TDirectoryFile *dir_y1to1p5 = (TDirectoryFile*) file_y1to1p5->Get("Table 6");
  


  // initialize value & error histograms
  xSec_y0to0p5 = (TH1D*) dir_y0to0p5->Get("Hist1D_y1");
  err_xSec_y0to0p5 = (TH1D*) dir_y0to0p5->Get("Hist1D_y1_e2plus");
  bFrac_y0to0p5 = (TH1D*) dir_y0to0p5->Get("Hist1D_y2");
  err_bFrac_y0to0p5 = (TH1D*) dir_y0to0p5->Get("Hist1D_y2_e2plus");
  for(int i = 0; i < xSec_y0to0p5->GetNbinsX()+1; i++){
    xSec_y0to0p5->SetBinError(i,err_xSec_y0to0p5->GetBinContent(i));
    bFrac_y0to0p5->SetBinError(i,err_bFrac_y0to0p5->GetBinContent(i));
    //cout << "err_bFrac(" << i << ") = " << err_bFrac_y0to0p5->GetBinContent(i) << endl;
  }

  xSec_y0p5to1 = (TH1D*) dir_y0p5to1->Get("Hist1D_y1");
  err_xSec_y0p5to1 = (TH1D*) dir_y0p5to1->Get("Hist1D_y1_e2plus");
  bFrac_y0p5to1 = (TH1D*) dir_y0p5to1->Get("Hist1D_y2");
  err_bFrac_y0p5to1 = (TH1D*) dir_y0p5to1->Get("Hist1D_y2_e2plus");
  for(int i = 0; i < xSec_y0p5to1->GetNbinsX()+1; i++){
    xSec_y0p5to1->SetBinError(i,err_xSec_y0p5to1->GetBinContent(i));
    bFrac_y0p5to1->SetBinError(i,err_bFrac_y0p5to1->GetBinContent(i));
    //cout << "err_bFrac(" << i << ") = " << err_bFrac_y0p5to1->GetBinContent(i) << endl;
  }

  xSec_y1to1p5 = (TH1D*) dir_y1to1p5->Get("Hist1D_y1");
  err_xSec_y1to1p5 = (TH1D*) dir_y1to1p5->Get("Hist1D_y1_e2plus");
  bFrac_y1to1p5 = (TH1D*) dir_y1to1p5->Get("Hist1D_y2");
  err_bFrac_y1to1p5 = (TH1D*) dir_y1to1p5->Get("Hist1D_y2_e2plus");
  for(int i = 0; i < xSec_y1to1p5->GetNbinsX()+1; i++){
    xSec_y1to1p5->SetBinError(i,err_xSec_y1to1p5->GetBinContent(i));
    bFrac_y1to1p5->SetBinError(i,err_bFrac_y1to1p5->GetBinContent(i));
    //cout << "err_bFrac(" << i << ") = " << err_bFrac_y1to1p5->GetBinContent(i) << endl;
  }

  // scale the y-binned histograms by the x-section
  bFrac_y0to0p5->Scale(xSec_y0to0p5->Integral());
  bFrac_y0p5to1->Scale(xSec_y0p5to1->Integral());
  bFrac_y1to1p5->Scale(xSec_y1to1p5->Integral());
  weight_sum = xSec_y0to0p5->Integral() + xSec_y0p5to1->Integral() + xSec_y1to1p5->Integral();

  bFrac_tot = (TH1D*) bFrac_y0to0p5->Clone("bFrac_tot");
  bFrac_tot->Add(bFrac_y0p5to1);
  bFrac_tot->Add(bFrac_y1to1p5);
  bFrac_tot->Scale(1./weight_sum);

  bFrac_tot->Draw();

  savePath = "./bFrac.root";
  writeFile = TFile::Open(savePath,"recreate");
  bFrac_tot->Write("bFrac");
  writeFile->Close();
  
  
}
