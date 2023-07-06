TH1D* divideByBinwidth(TH1D* h_in){

  for(int k = 0; k < h_in->GetSize(); k++){

    double center = h_in->GetBinContent(k);
    double error = h_in->GetBinError(k);
    double width = h_in->GetBinWidth(k);

    if(width != 0){

      h_in->SetBinContent(k,center/width);
      h_in->SetBinError(k,error/width);

    }

  }

  return h_in;

}
