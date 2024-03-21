void projectMe(){

  TFile *f1 = TFile::Open("localScans/PYTHIAHYDJET_DiJet_scan_mu5_pThat40_jetFilter_evtReweight.root");

  TH2D *H;

  f1->GetObject("h_recoJetPt_pthat_C0",H);

  double jet_pt_low = 195.0;
  double jet_pt_high = 200.0;

  TH1D *h = (TH1D*) H->ProjectionY("h",H->ProjectionX()->FindBin(jet_pt_low),H->ProjectionX()->FindBin(jet_pt_high));

  h->Draw();

  double running_integral_fraction = 0.0;
  double total_integral = h->Integral();
  double iter_integral = 0.0;
  double value_at_bin = 0.0;
  int number_of_bins = h->GetSize();

  for(int i = 0; i < number_of_bins; i++){
    iter_integral = h->Integral(0,i);
    value_at_bin = h->GetXaxis()->GetBinLowEdge(i);
    running_integral_fraction = iter_integral / total_integral;
    cout << "f(pT = " << value_at_bin << ") = " << running_integral_fraction << endl;
  }

  double margin_offset = 0.15;
  TCanvas *canv_1 = new TCanvas("canv_1","canv_1",700,700);
  canv_1->cd();
  TPad *pad_1 = new TPad("pad_1","pad_1",0,0,1,1);
  pad_1->SetLeftMargin(margin_offset);
  pad_1->SetBottomMargin(margin_offset);
  pad_1->SetRightMargin(margin_offset);
  pad_1->SetTopMargin(margin_offset);
  pad_1->Draw();
  pad_1->cd();
  H->SetTitle("#hat{#font[52]{p}}_{T} vs. #font[52]{p}_{T}^{recoJet}");
  H->GetXaxis()->SetTitle("#font[52]{p}_{T}^{recoJet} [GeV]");
  H->GetYaxis()->SetTitle("#hat{#font[52]{p}}_{T} [GeV]");
  H->SetStats(0);
  H->Draw("colz");
  canv_1->SaveAs("/home/clayton/Documents/nuclear/GroupMeeting/figures/2024-03-19/pThat_pTjet.pdf");

  TCanvas *canv_2 = new TCanvas("canv_2","canv_2",700,700);
  canv_2->cd();
  TPad *pad_2 = new TPad("pad_2","pad_2",0,0,1,1);
  pad_2->SetLeftMargin(margin_offset);
  pad_2->SetBottomMargin(margin_offset);
  pad_2->SetRightMargin(margin_offset);
  pad_2->SetTopMargin(margin_offset);
  pad_2->Draw();
  pad_2->cd();
  h->SetTitle("#hat{#font[52]{p}}_{T} for 195 < #font[52]{p}_{T}^{recoJet} < 200 GeV");
  h->GetXaxis()->SetTitle("#hat{#font[52]{p}}_{T} [GeV]");
  h->GetYaxis()->SetTitle("Entries");
  h->SetStats(0);
  h->Draw();
  canv_2->SaveAs(Form("/home/clayton/Documents/nuclear/GroupMeeting/figures/2024-03-19/pThat_pTjet_%3.0f_%3.0f.pdf",jet_pt_low,jet_pt_high));

  
  
}
