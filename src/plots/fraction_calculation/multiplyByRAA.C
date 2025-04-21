

void multiplyByRAA(){

  TF1 *fit = new TF1("fit","[0]+[1]*x",80,200);
  fit->SetParameter(0,0.3239);
  fit->SetParameter(1,0.00115291);
  //fit->Draw();

  TFile *file_bFrac = TFile::Open("./bFracRatioSave.root");

  TH1D *bFracRatio;

  file_bFrac->GetObject("R4",bFracRatio);

  //bFracRatio->Draw();

  for(int i = 0; i < bFracRatio->GetSize(); i++){

    cout << "i = " << i << endl;
    bFracRatio->SetBinContent(i,bFracRatio->GetBinContent(i)*fit->Eval(bFracRatio->GetBinCenter(i)));
    bFracRatio->SetBinError(i,bFracRatio->GetBinError(i)*fit->Eval(bFracRatio->GetBinCenter(i)));
    
  }

  bFracRatio->Draw();

}
