

#include "/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/headers/systematicsResults_4CentBins.h"


std::pair<TGraphErrors*, TF1*> combineAndFitHistograms(TH1* hist1, TH1* hist2) {
    // --- Input validation ---
    if (!hist1 || !hist2) {
        std::cerr << "Error: Both histogram pointers must be valid." << std::endl;
        return {nullptr, nullptr};
    }

    // --- Extract data points from the first histogram ---
    std::vector<double> x_values1;
    std::vector<double> y_values1;
    std::vector<double> x_errors1;
    std::vector<double> y_errors1;
    for (int i = 1; i <= hist1->GetNbinsX()-1; ++i) {
        x_values1.push_back(hist1->GetBinCenter(i));
        y_values1.push_back(hist1->GetBinContent(i));
        x_errors1.push_back(hist1->GetBinWidth(i) / 2.0); // Half bin width as x-error
        y_errors1.push_back(hist1->GetBinError(i));
    }

    // --- Extract data points from the second histogram ---
    std::vector<double> x_values2;
    std::vector<double> y_values2;
    std::vector<double> x_errors2;
    std::vector<double> y_errors2;
    for (int i = 1; i <= hist2->GetNbinsX()-1; ++i) {
        x_values2.push_back(hist2->GetBinCenter(i));
        y_values2.push_back(hist2->GetBinContent(i));
        x_errors2.push_back(hist2->GetBinWidth(i) / 2.0); // Half bin width as x-error
        y_errors2.push_back(hist2->GetBinError(i));
    }

    // --- Combine all data points into single vectors ---
    std::vector<double> all_x, all_y, all_x_err, all_y_err;
    all_x.insert(all_x.end(), x_values1.begin(), x_values1.end());
    all_x.insert(all_x.end(), x_values2.begin(), x_values2.end());

    all_y.insert(all_y.end(), y_values1.begin(), y_values1.end());
    all_y.insert(all_y.end(), y_values2.begin(), y_values2.end());

    all_x_err.insert(all_x_err.end(), x_errors1.begin(), x_errors1.end());
    all_x_err.insert(all_x_err.end(), x_errors2.begin(), x_errors2.end());

    all_y_err.insert(all_y_err.end(), y_errors1.begin(), y_errors1.end());
    all_y_err.insert(all_y_err.end(), y_errors2.begin(), y_errors2.end());

    // Check if there are any points to graph
    if (all_x.empty()) {
        std::cerr << "Error: No data points to create a TGraphErrors." << std::endl;
        return {nullptr, nullptr};
    }

    // --- Create TGraphErrors ---
    // TGraphErrors takes C-style arrays, so convert std::vector to C-style array
    double* x_arr = &all_x[0];
    double* y_arr = &all_y[0];
    double* x_err_arr = &all_x_err[0];
    double* y_err_arr = &all_y_err[0];

    TGraphErrors* graph = new TGraphErrors(all_x.size(), x_arr, y_arr, x_err_arr, y_err_arr);
    graph->SetTitle("Combined Histogram Data;X-axis;Y-axis");
    graph->SetMarkerStyle(20); // Circle marker
    graph->SetMarkerSize(1.0);
    graph->SetLineColor(kBlue); // kBlue is a ROOT predefined color constant

    // --- Define the constant fit function (pol0) ---
    // Determine the fit range from the combined data
    double min_x = all_x[0];
    double max_x = all_x[0];
    for (size_t i = 1; i < all_x.size(); ++i) {
        if (all_x[i] < min_x) min_x = all_x[i];
        if (all_x[i] > max_x) max_x = all_x[i];
    }
    // Add a small buffer to the range for fitting robustness
    min_x -= (max_x - min_x) * 0.05;
    max_x += (max_x - min_x) * 0.05;


    TF1* fit_func = new TF1("pol0_fit", "pol0", min_x, max_x);

    // --- Fit the TGraphErrors ---
    // "S" option saves the TFitResultPtr, "Q" for quiet mode (no printout)
    TFitResultPtr fit_result = graph->Fit(fit_func, "SQ");

    // --- Draw the results ---
    TCanvas* canvas = new TCanvas("canvas", "Histogram Combination and Fit", 800, 600);
    graph->Draw("AP"); // "AP" draws axes and points
    fit_func->Draw("same"); // Draw the fit function on the same canvas

    // Update canvas and keep it open (for interactive ROOT sessions)
    canvas->Update();
    canvas->Draw(); // This is needed to display the canvas in a compiled executable

    // The canvas will remain open as long as the application is running.
    // If you're running this in a macro, it will stay open.
    // If you compile an executable, you might need a gApplication->Run() or similar
    // to keep the event loop alive, but for simple visualization, just creating it
    // is often enough until the program exits.
    // For a compiled executable, you might save it instead:
    // canvas->SaveAs("combined_hist_fit.png");

    return {graph, fit_func};
}













void systematicsPlots_4CentBins(bool do_mu5  = 0,
				bool do_mu7  = 0,
				bool do_mu12 = 1){

  TLatex *la = new TLatex();
  la->SetTextFont(42);

  TLine *li = new TLine();
  
  // some draw options
  double new_bar_width = 0.3;
  double new_bar_offset = 0.05;


  ///  Calculate total
  const int N_sys_sources = 6;
  // pp

  // -- mu12
  double sys_total_pp_mu12_J1_array[N_sys_sources] = {sys_cFraction_highest_J1,
                                                      sys_lowerBound_pp_mu12_J1,
						      sys_JERsmear_pp_mu12_J1,
						      sys_bGS_highest_J1,
						      sys_JEUShiftCombined_pp_mu12_J1,
						      sys_centShiftCombined_pp_mu12_J1};

  double sys_total_pp_mu12_J2_array[N_sys_sources] = {sys_cFraction_highest_J2,
                                                      sys_lowerBound_pp_mu12_J2,
						      sys_JERsmear_pp_mu12_J2,
						      sys_bGS_highest_J2,
						      sys_JEUShiftCombined_pp_mu12_J2,
						      sys_centShiftCombined_pp_mu12_J2};

  double sys_total_pp_mu12_J3_array[N_sys_sources] = {sys_cFraction_highest_J3,
                                                      sys_lowerBound_pp_mu12_J3,
						      sys_JERsmear_pp_mu12_J3,
						      sys_bGS_highest_J3,
						      sys_JEUShiftCombined_pp_mu12_J3,
						      sys_centShiftCombined_pp_mu12_J3};

  double sys_total_pp_mu12_J4_array[N_sys_sources] = {sys_cFraction_highest_J4,
                                                      sys_lowerBound_pp_mu12_J4,
						      sys_JERsmear_pp_mu12_J4,
						      sys_bGS_highest_J4,
						      sys_JEUShiftCombined_pp_mu12_J4,
						      sys_centShiftCombined_pp_mu12_J4};

  double sys_total_pp_mu12_J5_array[N_sys_sources] = {sys_cFraction_highest_J5,
                                                      sys_lowerBound_pp_mu12_J5,
						      sys_JERsmear_pp_mu12_J5,
						      sys_bGS_highest_J5,
						      sys_JEUShiftCombined_pp_mu12_J5,
						      sys_centShiftCombined_pp_mu12_J5};

  double sys_total_pp_mu12_J6_array[N_sys_sources] = {sys_cFraction_highest_J6,
                                                      sys_lowerBound_pp_mu12_J6,
						      sys_JERsmear_pp_mu12_J6,
						      sys_bGS_highest_J6,
						      sys_JEUShiftCombined_pp_mu12_J6,
						      sys_centShiftCombined_pp_mu12_J6};



  // PbPb 50-80%
  double sys_total_PbPb_mu12_C4_J1_array[N_sys_sources] = {sys_cFraction_highest_J1,
                                                           sys_lowerBound_PbPb_mu12_C4_J1,
							   sys_JERsmear_PbPb_mu12_C4_J1,
							   sys_bGS_highest_J1,
							   sys_JEUShiftCombined_PbPb_mu12_C4_J1,
							   sys_centShiftCombined_PbPb_mu12_C4_J1};

  double sys_total_PbPb_mu12_C4_J2_array[N_sys_sources] = {sys_cFraction_highest_J2,
                                                           sys_lowerBound_PbPb_mu12_C4_J2,
							   sys_JERsmear_PbPb_mu12_C4_J2,
							   sys_bGS_highest_J2,
							   sys_JEUShiftCombined_PbPb_mu12_C4_J2,
							   sys_centShiftCombined_PbPb_mu12_C4_J2};

  double sys_total_PbPb_mu12_C4_J3_array[N_sys_sources] = {sys_cFraction_highest_J3,
                                                           sys_lowerBound_PbPb_mu12_C4_J3,
							   sys_JERsmear_PbPb_mu12_C4_J3,
							   sys_bGS_highest_J3,
							   sys_JEUShiftCombined_PbPb_mu12_C4_J3,
							   sys_centShiftCombined_PbPb_mu12_C4_J3};

  double sys_total_PbPb_mu12_C4_J4_array[N_sys_sources] = {sys_cFraction_highest_J4,
                                                           sys_lowerBound_PbPb_mu12_C4_J4,
							   sys_JERsmear_PbPb_mu12_C4_J4,
							   sys_bGS_highest_J4,
							   sys_JEUShiftCombined_PbPb_mu12_C4_J4,
							   sys_centShiftCombined_PbPb_mu12_C4_J4};

  double sys_total_PbPb_mu12_C4_J5_array[N_sys_sources] = {sys_cFraction_highest_J5,
                                                           sys_lowerBound_PbPb_mu12_C4_J5,
							   sys_JERsmear_PbPb_mu12_C4_J5,
							   sys_bGS_highest_J5,
							   sys_JEUShiftCombined_PbPb_mu12_C4_J5,
							   sys_centShiftCombined_PbPb_mu12_C4_J5};

  double sys_total_PbPb_mu12_C4_J6_array[N_sys_sources] = {sys_cFraction_highest_J6,
                                                           sys_lowerBound_PbPb_mu12_C4_J6,
							   sys_JERsmear_PbPb_mu12_C4_J6,
							   sys_bGS_highest_J6,
							   sys_JEUShiftCombined_PbPb_mu12_C4_J6,
							   sys_centShiftCombined_PbPb_mu12_C4_J6};

  // PbPb 30-50%
  double sys_total_PbPb_mu12_C3_J1_array[N_sys_sources] = {sys_cFraction_highest_J1,
                                                           sys_lowerBound_PbPb_mu12_C3_J1,
							   sys_JERsmear_PbPb_mu12_C3_J1,
							   sys_bGS_highest_J1,
							   sys_JEUShiftCombined_PbPb_mu12_C3_J1,
							   sys_centShiftCombined_PbPb_mu12_C3_J1};

  double sys_total_PbPb_mu12_C3_J2_array[N_sys_sources] = {sys_cFraction_highest_J2,
                                                           sys_lowerBound_PbPb_mu12_C3_J2,
							   sys_JERsmear_PbPb_mu12_C3_J2,
							   sys_bGS_highest_J2,
							   sys_JEUShiftCombined_PbPb_mu12_C3_J2,
							   sys_centShiftCombined_PbPb_mu12_C3_J2};

  double sys_total_PbPb_mu12_C3_J3_array[N_sys_sources] = {sys_cFraction_highest_J3,
                                                           sys_lowerBound_PbPb_mu12_C3_J3,
							   sys_JERsmear_PbPb_mu12_C3_J3,
							   sys_bGS_highest_J3,
							   sys_JEUShiftCombined_PbPb_mu12_C3_J3,
							   sys_centShiftCombined_PbPb_mu12_C3_J3};

  double sys_total_PbPb_mu12_C3_J4_array[N_sys_sources] = {sys_cFraction_highest_J4,
                                                           sys_lowerBound_PbPb_mu12_C3_J4,
							   sys_JERsmear_PbPb_mu12_C3_J4,
							   sys_bGS_highest_J4,
							   sys_JEUShiftCombined_PbPb_mu12_C3_J4,
							   sys_centShiftCombined_PbPb_mu12_C3_J4};

  double sys_total_PbPb_mu12_C3_J5_array[N_sys_sources] = {sys_cFraction_highest_J5,
                                                           sys_lowerBound_PbPb_mu12_C3_J5,
							   sys_JERsmear_PbPb_mu12_C3_J5,
							   sys_bGS_highest_J5,
							   sys_JEUShiftCombined_PbPb_mu12_C3_J5,
							   sys_centShiftCombined_PbPb_mu12_C3_J5};

  double sys_total_PbPb_mu12_C3_J6_array[N_sys_sources] = {sys_cFraction_highest_J6,
                                                           sys_lowerBound_PbPb_mu12_C3_J6,
							   sys_JERsmear_PbPb_mu12_C3_J6,
							   sys_bGS_highest_J6,
							   sys_JEUShiftCombined_PbPb_mu12_C3_J6,
							   sys_centShiftCombined_PbPb_mu12_C3_J6};



  // PbPb 10-30%
  double sys_total_PbPb_mu12_C2_J1_array[N_sys_sources] = {sys_cFraction_highest_J1,
                                                           sys_lowerBound_PbPb_mu12_C2_J1,
							   sys_JERsmear_PbPb_mu12_C2_J1,
							   sys_bGS_highest_J1,
							   sys_JEUShiftCombined_PbPb_mu12_C2_J1,
							   sys_centShiftCombined_PbPb_mu12_C2_J1};

  double sys_total_PbPb_mu12_C2_J2_array[N_sys_sources] = {sys_cFraction_highest_J2,
                                                           sys_lowerBound_PbPb_mu12_C2_J2,
							   sys_JERsmear_PbPb_mu12_C2_J2,
							   sys_bGS_highest_J2,
							   sys_JEUShiftCombined_PbPb_mu12_C2_J2,
							   sys_centShiftCombined_PbPb_mu12_C2_J2};

  double sys_total_PbPb_mu12_C2_J3_array[N_sys_sources] = {sys_cFraction_highest_J3,
                                                           sys_lowerBound_PbPb_mu12_C2_J3,
							   sys_JERsmear_PbPb_mu12_C2_J3,
							   sys_bGS_highest_J3,
							   sys_JEUShiftCombined_PbPb_mu12_C2_J3,
							   sys_centShiftCombined_PbPb_mu12_C2_J3};

  double sys_total_PbPb_mu12_C2_J4_array[N_sys_sources] = {sys_cFraction_highest_J4,
                                                           sys_lowerBound_PbPb_mu12_C2_J4,
							   sys_JERsmear_PbPb_mu12_C2_J4,
							   sys_bGS_highest_J4,
							   sys_JEUShiftCombined_PbPb_mu12_C2_J4,
							   sys_centShiftCombined_PbPb_mu12_C2_J4};

  double sys_total_PbPb_mu12_C2_J5_array[N_sys_sources] = {sys_cFraction_highest_J5,
                                                           sys_lowerBound_PbPb_mu12_C2_J5,
							   sys_JERsmear_PbPb_mu12_C2_J5,
							   sys_bGS_highest_J5,
							   sys_JEUShiftCombined_PbPb_mu12_C2_J5,
							   sys_centShiftCombined_PbPb_mu12_C2_J5};

  double sys_total_PbPb_mu12_C2_J6_array[N_sys_sources] = {sys_cFraction_highest_J6,
                                                           sys_lowerBound_PbPb_mu12_C2_J6,
							   sys_JERsmear_PbPb_mu12_C2_J6,
							   sys_bGS_highest_J6,
							   sys_JEUShiftCombined_PbPb_mu12_C2_J6,
							   sys_centShiftCombined_PbPb_mu12_C2_J6};

  // PbPb 0-10%
  double sys_total_PbPb_mu12_C1_J1_array[N_sys_sources] = {sys_cFraction_highest_J1,
                                                           sys_lowerBound_PbPb_mu12_C1_J1,
							   sys_JERsmear_PbPb_mu12_C1_J1,
							   sys_bGS_highest_J1,
							   sys_JEUShiftCombined_PbPb_mu12_C1_J1,
							   sys_centShiftCombined_PbPb_mu12_C1_J1};

  double sys_total_PbPb_mu12_C1_J2_array[N_sys_sources] = {sys_cFraction_highest_J2,
                                                           sys_lowerBound_PbPb_mu12_C1_J2,
							   sys_JERsmear_PbPb_mu12_C1_J2,
							   sys_bGS_highest_J2,
							   sys_JEUShiftCombined_PbPb_mu12_C1_J2,
							   sys_centShiftCombined_PbPb_mu12_C1_J2};

  double sys_total_PbPb_mu12_C1_J3_array[N_sys_sources] = {sys_cFraction_highest_J3,
                                                           sys_lowerBound_PbPb_mu12_C1_J3,
							   sys_JERsmear_PbPb_mu12_C1_J3,
							   sys_bGS_highest_J3,
							   sys_JEUShiftCombined_PbPb_mu12_C1_J3,
							   sys_centShiftCombined_PbPb_mu12_C1_J3};

  double sys_total_PbPb_mu12_C1_J4_array[N_sys_sources] = {sys_cFraction_highest_J4,
                                                           sys_lowerBound_PbPb_mu12_C1_J4,
							   sys_JERsmear_PbPb_mu12_C1_J4,
							   sys_bGS_highest_J4,
							   sys_JEUShiftCombined_PbPb_mu12_C1_J4,
							   sys_centShiftCombined_PbPb_mu12_C1_J4};

  double sys_total_PbPb_mu12_C1_J5_array[N_sys_sources] = {sys_cFraction_highest_J5,
                                                           sys_lowerBound_PbPb_mu12_C1_J5,
							   sys_JERsmear_PbPb_mu12_C1_J5,
							   sys_bGS_highest_J5,
							   sys_JEUShiftCombined_PbPb_mu12_C1_J5,
							   sys_centShiftCombined_PbPb_mu12_C1_J5};

  double sys_total_PbPb_mu12_C1_J6_array[N_sys_sources] = {sys_cFraction_highest_J6,
                                                           sys_lowerBound_PbPb_mu12_C1_J6,
							   sys_JERsmear_PbPb_mu12_C1_J6,
							   sys_bGS_highest_J6,
							   sys_JEUShiftCombined_PbPb_mu12_C1_J6,
							   sys_centShiftCombined_PbPb_mu12_C1_J6};



  double sys_total_pp_mu12_J1 = 0;
  double sys_total_pp_mu12_J2 = 0;
  double sys_total_pp_mu12_J3 = 0;
  double sys_total_pp_mu12_J4 = 0;
  double sys_total_pp_mu12_J5 = 0;
  double sys_total_pp_mu12_J6 = 0;

  double sys_total_PbPb_mu12_C4_J1 = 0;
  double sys_total_PbPb_mu12_C4_J2 = 0;
  double sys_total_PbPb_mu12_C4_J3 = 0;
  double sys_total_PbPb_mu12_C4_J4 = 0;
  double sys_total_PbPb_mu12_C4_J5 = 0;
  double sys_total_PbPb_mu12_C4_J6 = 0;

  double sys_total_PbPb_mu12_C3_J1 = 0;
  double sys_total_PbPb_mu12_C3_J2 = 0;
  double sys_total_PbPb_mu12_C3_J3 = 0;
  double sys_total_PbPb_mu12_C3_J4 = 0;
  double sys_total_PbPb_mu12_C3_J5 = 0;
  double sys_total_PbPb_mu12_C3_J6 = 0;

  double sys_total_PbPb_mu12_C2_J1 = 0;
  double sys_total_PbPb_mu12_C2_J2 = 0;
  double sys_total_PbPb_mu12_C2_J3 = 0;
  double sys_total_PbPb_mu12_C2_J4 = 0;
  double sys_total_PbPb_mu12_C2_J5 = 0;
  double sys_total_PbPb_mu12_C2_J6 = 0;

  double sys_total_PbPb_mu12_C1_J1 = 0;
  double sys_total_PbPb_mu12_C1_J2 = 0;  
  double sys_total_PbPb_mu12_C1_J3 = 0;
  double sys_total_PbPb_mu12_C1_J4 = 0;
  double sys_total_PbPb_mu12_C1_J5 = 0;
  double sys_total_PbPb_mu12_C1_J6 = 0;  


  // add the squares
  for(int i = 0; i < N_sys_sources; i++){

    // pp
    sys_total_pp_mu12_J1 += sys_total_pp_mu12_J1_array[i]*sys_total_pp_mu12_J1_array[i];
    sys_total_pp_mu12_J2 += sys_total_pp_mu12_J2_array[i]*sys_total_pp_mu12_J2_array[i];
    sys_total_pp_mu12_J3 += sys_total_pp_mu12_J3_array[i]*sys_total_pp_mu12_J3_array[i];
    sys_total_pp_mu12_J4 += sys_total_pp_mu12_J4_array[i]*sys_total_pp_mu12_J4_array[i];
    sys_total_pp_mu12_J5 += sys_total_pp_mu12_J5_array[i]*sys_total_pp_mu12_J5_array[i];
    sys_total_pp_mu12_J6 += sys_total_pp_mu12_J6_array[i]*sys_total_pp_mu12_J6_array[i];    

    // PbPb 50-80%
    sys_total_PbPb_mu12_C4_J1 += sys_total_PbPb_mu12_C4_J1_array[i]*sys_total_PbPb_mu12_C4_J1_array[i];
    sys_total_PbPb_mu12_C4_J2 += sys_total_PbPb_mu12_C4_J2_array[i]*sys_total_PbPb_mu12_C4_J2_array[i];    
    sys_total_PbPb_mu12_C4_J3 += sys_total_PbPb_mu12_C4_J3_array[i]*sys_total_PbPb_mu12_C4_J3_array[i];
    sys_total_PbPb_mu12_C4_J4 += sys_total_PbPb_mu12_C4_J4_array[i]*sys_total_PbPb_mu12_C4_J4_array[i];
    sys_total_PbPb_mu12_C4_J5 += sys_total_PbPb_mu12_C4_J5_array[i]*sys_total_PbPb_mu12_C4_J5_array[i];
    sys_total_PbPb_mu12_C4_J6 += sys_total_PbPb_mu12_C4_J6_array[i]*sys_total_PbPb_mu12_C4_J6_array[i];

    // PbPb 30-50%
    sys_total_PbPb_mu12_C3_J1 += sys_total_PbPb_mu12_C3_J1_array[i]*sys_total_PbPb_mu12_C3_J1_array[i];
    sys_total_PbPb_mu12_C3_J2 += sys_total_PbPb_mu12_C3_J2_array[i]*sys_total_PbPb_mu12_C3_J2_array[i];    
    sys_total_PbPb_mu12_C3_J3 += sys_total_PbPb_mu12_C3_J3_array[i]*sys_total_PbPb_mu12_C3_J3_array[i];
    sys_total_PbPb_mu12_C3_J4 += sys_total_PbPb_mu12_C3_J4_array[i]*sys_total_PbPb_mu12_C3_J4_array[i];
    sys_total_PbPb_mu12_C3_J5 += sys_total_PbPb_mu12_C3_J5_array[i]*sys_total_PbPb_mu12_C3_J5_array[i];
    sys_total_PbPb_mu12_C3_J6 += sys_total_PbPb_mu12_C3_J6_array[i]*sys_total_PbPb_mu12_C3_J6_array[i];    
 
    // PbPb 10-30%
    sys_total_PbPb_mu12_C2_J1 += sys_total_PbPb_mu12_C2_J1_array[i]*sys_total_PbPb_mu12_C2_J1_array[i];
    sys_total_PbPb_mu12_C2_J2 += sys_total_PbPb_mu12_C2_J2_array[i]*sys_total_PbPb_mu12_C2_J2_array[i];    
    sys_total_PbPb_mu12_C2_J3 += sys_total_PbPb_mu12_C2_J3_array[i]*sys_total_PbPb_mu12_C2_J3_array[i];
    sys_total_PbPb_mu12_C2_J4 += sys_total_PbPb_mu12_C2_J4_array[i]*sys_total_PbPb_mu12_C2_J4_array[i];
    sys_total_PbPb_mu12_C2_J5 += sys_total_PbPb_mu12_C2_J5_array[i]*sys_total_PbPb_mu12_C2_J5_array[i];
    sys_total_PbPb_mu12_C2_J6 += sys_total_PbPb_mu12_C2_J6_array[i]*sys_total_PbPb_mu12_C2_J6_array[i];    

    // PbPb 0-10%
    sys_total_PbPb_mu12_C1_J1 += sys_total_PbPb_mu12_C1_J1_array[i]*sys_total_PbPb_mu12_C1_J1_array[i];
    sys_total_PbPb_mu12_C1_J2 += sys_total_PbPb_mu12_C1_J2_array[i]*sys_total_PbPb_mu12_C1_J2_array[i];
    sys_total_PbPb_mu12_C1_J3 += sys_total_PbPb_mu12_C1_J3_array[i]*sys_total_PbPb_mu12_C1_J3_array[i];
    sys_total_PbPb_mu12_C1_J4 += sys_total_PbPb_mu12_C1_J4_array[i]*sys_total_PbPb_mu12_C1_J4_array[i];
    sys_total_PbPb_mu12_C1_J5 += sys_total_PbPb_mu12_C1_J5_array[i]*sys_total_PbPb_mu12_C1_J5_array[i];
    sys_total_PbPb_mu12_C1_J6 += sys_total_PbPb_mu12_C1_J6_array[i]*sys_total_PbPb_mu12_C1_J6_array[i];    

  }

  
  sys_total_pp_mu12_J1 = TMath::Sqrt(sys_total_pp_mu12_J1);
  sys_total_pp_mu12_J2 = TMath::Sqrt(sys_total_pp_mu12_J2);
  sys_total_pp_mu12_J3 = TMath::Sqrt(sys_total_pp_mu12_J3);
  sys_total_pp_mu12_J4 = TMath::Sqrt(sys_total_pp_mu12_J4);
  sys_total_pp_mu12_J5 = TMath::Sqrt(sys_total_pp_mu12_J5);
  sys_total_pp_mu12_J6 = TMath::Sqrt(sys_total_pp_mu12_J6);

  sys_total_PbPb_mu12_C4_J1 = TMath::Sqrt(sys_total_PbPb_mu12_C4_J1);
  sys_total_PbPb_mu12_C4_J2 = TMath::Sqrt(sys_total_PbPb_mu12_C4_J2);
  sys_total_PbPb_mu12_C4_J3 = TMath::Sqrt(sys_total_PbPb_mu12_C4_J3);
  sys_total_PbPb_mu12_C4_J4 = TMath::Sqrt(sys_total_PbPb_mu12_C4_J4);
  sys_total_PbPb_mu12_C4_J5 = TMath::Sqrt(sys_total_PbPb_mu12_C4_J5);
  sys_total_PbPb_mu12_C4_J6 = TMath::Sqrt(sys_total_PbPb_mu12_C4_J6);

  sys_total_PbPb_mu12_C3_J1 = TMath::Sqrt(sys_total_PbPb_mu12_C3_J1);
  sys_total_PbPb_mu12_C3_J2 = TMath::Sqrt(sys_total_PbPb_mu12_C3_J2);
  sys_total_PbPb_mu12_C3_J3 = TMath::Sqrt(sys_total_PbPb_mu12_C3_J3);
  sys_total_PbPb_mu12_C3_J4 = TMath::Sqrt(sys_total_PbPb_mu12_C3_J4);
  sys_total_PbPb_mu12_C3_J5 = TMath::Sqrt(sys_total_PbPb_mu12_C3_J5);
  sys_total_PbPb_mu12_C3_J6 = TMath::Sqrt(sys_total_PbPb_mu12_C3_J6);

  sys_total_PbPb_mu12_C2_J1 = TMath::Sqrt(sys_total_PbPb_mu12_C2_J1);
  sys_total_PbPb_mu12_C2_J2 = TMath::Sqrt(sys_total_PbPb_mu12_C2_J2);
  sys_total_PbPb_mu12_C2_J3 = TMath::Sqrt(sys_total_PbPb_mu12_C2_J3);
  sys_total_PbPb_mu12_C2_J4 = TMath::Sqrt(sys_total_PbPb_mu12_C2_J4);
  sys_total_PbPb_mu12_C2_J5 = TMath::Sqrt(sys_total_PbPb_mu12_C2_J5);
  sys_total_PbPb_mu12_C2_J6 = TMath::Sqrt(sys_total_PbPb_mu12_C2_J6);

  sys_total_PbPb_mu12_C1_J1 = TMath::Sqrt(sys_total_PbPb_mu12_C1_J1);
  sys_total_PbPb_mu12_C1_J2 = TMath::Sqrt(sys_total_PbPb_mu12_C1_J2);
  sys_total_PbPb_mu12_C1_J3 = TMath::Sqrt(sys_total_PbPb_mu12_C1_J3);
  sys_total_PbPb_mu12_C1_J4 = TMath::Sqrt(sys_total_PbPb_mu12_C1_J4);
  sys_total_PbPb_mu12_C1_J5 = TMath::Sqrt(sys_total_PbPb_mu12_C1_J5);
  sys_total_PbPb_mu12_C1_J6 = TMath::Sqrt(sys_total_PbPb_mu12_C1_J6);

  
  const int N_sys = 7;
  string sys_names[N_sys] = {"c-fraction-variation","fit-lower-bound","Jet-energy-resolution","bGS-multiplier","Jet-energy-scale", "Centrality", "Total"};

  // pp
  double sys_pp_mu12_J1_array[N_sys] = {sys_cFraction_pp_mu12_J1, sys_lowerBound_pp_mu12_J1, sys_JERsmear_pp_mu12_J1, sys_bGS_pp_mu12_J1, sys_JEUShiftUp_pp_mu12_J1,sys_centShiftUp_pp_mu12_J1 , sys_total_pp_mu12_J1};
  double sys_pp_mu12_J2_array[N_sys] = {sys_cFraction_pp_mu12_J2, sys_lowerBound_pp_mu12_J2, sys_JERsmear_pp_mu12_J2, sys_bGS_pp_mu12_J2, sys_JEUShiftUp_pp_mu12_J2,sys_centShiftUp_pp_mu12_J2 , sys_total_pp_mu12_J2};
  double sys_pp_mu12_J3_array[N_sys] = {sys_cFraction_pp_mu12_J3, sys_lowerBound_pp_mu12_J3, sys_JERsmear_pp_mu12_J3, sys_bGS_pp_mu12_J3,sys_JEUShiftUp_pp_mu12_J3,sys_centShiftUp_pp_mu12_J3 , sys_total_pp_mu12_J3};
  double sys_pp_mu12_J4_array[N_sys] = {sys_cFraction_pp_mu12_J4, sys_lowerBound_pp_mu12_J4, sys_JERsmear_pp_mu12_J4, sys_bGS_pp_mu12_J4,sys_JEUShiftUp_pp_mu12_J4,sys_centShiftUp_pp_mu12_J4 , sys_total_pp_mu12_J4};
  double sys_pp_mu12_J5_array[N_sys] = {sys_cFraction_pp_mu12_J5, sys_lowerBound_pp_mu12_J5, sys_JERsmear_pp_mu12_J5, sys_bGS_pp_mu12_J5,sys_JEUShiftUp_pp_mu12_J5,sys_centShiftUp_pp_mu12_J5 , sys_total_pp_mu12_J5};
  double sys_pp_mu12_J6_array[N_sys] = {sys_cFraction_pp_mu12_J6, sys_lowerBound_pp_mu12_J6, sys_JERsmear_pp_mu12_J6, sys_bGS_pp_mu12_J6,sys_JEUShiftUp_pp_mu12_J6,sys_centShiftUp_pp_mu12_J6 , sys_total_pp_mu12_J6};  

  // PbPb 50-80%
  double sys_PbPb_mu12_C4_J1_array[N_sys] = {sys_cFraction_PbPb_mu12_C4_J1, sys_lowerBound_PbPb_mu12_C4_J1, sys_JERsmear_PbPb_mu12_C4_J1, sys_bGS_PbPb_mu12_C4_J1, sys_JEUShiftUp_PbPb_mu12_C4_J1,sys_centShiftUp_PbPb_mu12_C4_J1 , sys_total_PbPb_mu12_C4_J1};
  double sys_PbPb_mu12_C4_J2_array[N_sys] = {sys_cFraction_PbPb_mu12_C4_J2, sys_lowerBound_PbPb_mu12_C4_J2, sys_JERsmear_PbPb_mu12_C4_J2, sys_bGS_PbPb_mu12_C4_J2, sys_JEUShiftUp_PbPb_mu12_C4_J2,sys_centShiftUp_PbPb_mu12_C4_J2 , sys_total_PbPb_mu12_C4_J2};
  double sys_PbPb_mu12_C4_J3_array[N_sys] = {sys_cFraction_PbPb_mu12_C4_J3, sys_lowerBound_PbPb_mu12_C4_J3, sys_JERsmear_PbPb_mu12_C4_J3, sys_bGS_PbPb_mu12_C4_J3,sys_JEUShiftUp_PbPb_mu12_C4_J3,sys_centShiftUp_PbPb_mu12_C4_J3 , sys_total_PbPb_mu12_C4_J3};
  double sys_PbPb_mu12_C4_J4_array[N_sys] = {sys_cFraction_PbPb_mu12_C4_J4, sys_lowerBound_PbPb_mu12_C4_J4, sys_JERsmear_PbPb_mu12_C4_J4, sys_bGS_PbPb_mu12_C4_J4,sys_JEUShiftUp_PbPb_mu12_C4_J4,sys_centShiftUp_PbPb_mu12_C4_J4 , sys_total_PbPb_mu12_C4_J4};
  double sys_PbPb_mu12_C4_J5_array[N_sys] = {sys_cFraction_PbPb_mu12_C4_J5, sys_lowerBound_PbPb_mu12_C4_J5, sys_JERsmear_PbPb_mu12_C4_J5, sys_bGS_PbPb_mu12_C4_J5,sys_JEUShiftUp_PbPb_mu12_C4_J5,sys_centShiftUp_PbPb_mu12_C4_J5 , sys_total_PbPb_mu12_C4_J5};
  double sys_PbPb_mu12_C4_J6_array[N_sys] = {sys_cFraction_PbPb_mu12_C4_J6, sys_lowerBound_PbPb_mu12_C4_J6, sys_JERsmear_PbPb_mu12_C4_J6, sys_bGS_PbPb_mu12_C4_J6,sys_JEUShiftUp_PbPb_mu12_C4_J6,sys_centShiftUp_PbPb_mu12_C4_J6 , sys_total_PbPb_mu12_C4_J6};

  // PbPb 30-50%
  double sys_PbPb_mu12_C3_J1_array[N_sys] = {sys_cFraction_PbPb_mu12_C3_J1, sys_lowerBound_PbPb_mu12_C3_J1, sys_JERsmear_PbPb_mu12_C3_J1, sys_bGS_PbPb_mu12_C3_J1, sys_JEUShiftUp_PbPb_mu12_C3_J1,sys_centShiftUp_PbPb_mu12_C3_J1 , sys_total_PbPb_mu12_C3_J1};
  double sys_PbPb_mu12_C3_J2_array[N_sys] = {sys_cFraction_PbPb_mu12_C3_J2, sys_lowerBound_PbPb_mu12_C3_J2, sys_JERsmear_PbPb_mu12_C3_J2, sys_bGS_PbPb_mu12_C3_J2, sys_JEUShiftUp_PbPb_mu12_C3_J2,sys_centShiftUp_PbPb_mu12_C3_J2 , sys_total_PbPb_mu12_C3_J2};
  double sys_PbPb_mu12_C3_J3_array[N_sys] = {sys_cFraction_PbPb_mu12_C3_J3, sys_lowerBound_PbPb_mu12_C3_J3, sys_JERsmear_PbPb_mu12_C3_J3, sys_bGS_PbPb_mu12_C3_J3,sys_JEUShiftUp_PbPb_mu12_C3_J3,sys_centShiftUp_PbPb_mu12_C3_J3 , sys_total_PbPb_mu12_C3_J3};
  double sys_PbPb_mu12_C3_J4_array[N_sys] = {sys_cFraction_PbPb_mu12_C3_J4, sys_lowerBound_PbPb_mu12_C3_J4, sys_JERsmear_PbPb_mu12_C3_J4, sys_bGS_PbPb_mu12_C3_J4,sys_JEUShiftUp_PbPb_mu12_C3_J4,sys_centShiftUp_PbPb_mu12_C3_J4 , sys_total_PbPb_mu12_C3_J4};
  double sys_PbPb_mu12_C3_J5_array[N_sys] = {sys_cFraction_PbPb_mu12_C3_J5, sys_lowerBound_PbPb_mu12_C3_J5, sys_JERsmear_PbPb_mu12_C3_J5, sys_bGS_PbPb_mu12_C3_J5,sys_JEUShiftUp_PbPb_mu12_C3_J5,sys_centShiftUp_PbPb_mu12_C3_J5 , sys_total_PbPb_mu12_C3_J5};
  double sys_PbPb_mu12_C3_J6_array[N_sys] = {sys_cFraction_PbPb_mu12_C3_J6, sys_lowerBound_PbPb_mu12_C3_J6, sys_JERsmear_PbPb_mu12_C3_J6, sys_bGS_PbPb_mu12_C3_J6,sys_JEUShiftUp_PbPb_mu12_C3_J6,sys_centShiftUp_PbPb_mu12_C3_J6 , sys_total_PbPb_mu12_C3_J6};    

  // PbPb 10-30%
  double sys_PbPb_mu12_C2_J1_array[N_sys] = {sys_cFraction_PbPb_mu12_C2_J1, sys_lowerBound_PbPb_mu12_C2_J1, sys_JERsmear_PbPb_mu12_C2_J1, sys_bGS_PbPb_mu12_C2_J1, sys_JEUShiftUp_PbPb_mu12_C2_J1,sys_centShiftUp_PbPb_mu12_C2_J1 , sys_total_PbPb_mu12_C2_J1};
  double sys_PbPb_mu12_C2_J2_array[N_sys] = {sys_cFraction_PbPb_mu12_C2_J2, sys_lowerBound_PbPb_mu12_C2_J2, sys_JERsmear_PbPb_mu12_C2_J2, sys_bGS_PbPb_mu12_C2_J2, sys_JEUShiftUp_PbPb_mu12_C2_J2,sys_centShiftUp_PbPb_mu12_C2_J2 , sys_total_PbPb_mu12_C2_J2};
  double sys_PbPb_mu12_C2_J3_array[N_sys] = {sys_cFraction_PbPb_mu12_C2_J3, sys_lowerBound_PbPb_mu12_C2_J3, sys_JERsmear_PbPb_mu12_C2_J3, sys_bGS_PbPb_mu12_C2_J3,sys_JEUShiftUp_PbPb_mu12_C2_J3,sys_centShiftUp_PbPb_mu12_C2_J3 , sys_total_PbPb_mu12_C2_J3};
  double sys_PbPb_mu12_C2_J4_array[N_sys] = {sys_cFraction_PbPb_mu12_C2_J4, sys_lowerBound_PbPb_mu12_C2_J4, sys_JERsmear_PbPb_mu12_C2_J4, sys_bGS_PbPb_mu12_C2_J4,sys_JEUShiftUp_PbPb_mu12_C2_J4,sys_centShiftUp_PbPb_mu12_C2_J4 , sys_total_PbPb_mu12_C2_J4};
  double sys_PbPb_mu12_C2_J5_array[N_sys] = {sys_cFraction_PbPb_mu12_C2_J5, sys_lowerBound_PbPb_mu12_C2_J5, sys_JERsmear_PbPb_mu12_C2_J5, sys_bGS_PbPb_mu12_C2_J5,sys_JEUShiftUp_PbPb_mu12_C2_J5,sys_centShiftUp_PbPb_mu12_C2_J5 , sys_total_PbPb_mu12_C2_J5};
  double sys_PbPb_mu12_C2_J6_array[N_sys] = {sys_cFraction_PbPb_mu12_C2_J6, sys_lowerBound_PbPb_mu12_C2_J6, sys_JERsmear_PbPb_mu12_C2_J6, sys_bGS_PbPb_mu12_C2_J6,sys_JEUShiftUp_PbPb_mu12_C2_J6,sys_centShiftUp_PbPb_mu12_C2_J6 , sys_total_PbPb_mu12_C2_J6};  
  
  // PbPb 0-10%
  double sys_PbPb_mu12_C1_J1_array[N_sys] = {sys_cFraction_PbPb_mu12_C1_J1, sys_lowerBound_PbPb_mu12_C1_J1, sys_JERsmear_PbPb_mu12_C1_J1, sys_bGS_PbPb_mu12_C1_J1, sys_JEUShiftUp_PbPb_mu12_C1_J1,sys_centShiftUp_PbPb_mu12_C1_J1 , sys_total_PbPb_mu12_C1_J1};
  double sys_PbPb_mu12_C1_J2_array[N_sys] = {sys_cFraction_PbPb_mu12_C1_J2, sys_lowerBound_PbPb_mu12_C1_J2, sys_JERsmear_PbPb_mu12_C1_J2, sys_bGS_PbPb_mu12_C1_J2, sys_JEUShiftUp_PbPb_mu12_C1_J2,sys_centShiftUp_PbPb_mu12_C1_J2 , sys_total_PbPb_mu12_C1_J2};
  double sys_PbPb_mu12_C1_J3_array[N_sys] = {sys_cFraction_PbPb_mu12_C1_J3, sys_lowerBound_PbPb_mu12_C1_J3, sys_JERsmear_PbPb_mu12_C1_J3, sys_bGS_PbPb_mu12_C1_J3,sys_JEUShiftUp_PbPb_mu12_C1_J3,sys_centShiftUp_PbPb_mu12_C1_J3 , sys_total_PbPb_mu12_C1_J3};
  double sys_PbPb_mu12_C1_J4_array[N_sys] = {sys_cFraction_PbPb_mu12_C1_J4, sys_lowerBound_PbPb_mu12_C1_J4, sys_JERsmear_PbPb_mu12_C1_J4, sys_bGS_PbPb_mu12_C1_J4,sys_JEUShiftUp_PbPb_mu12_C1_J4,sys_centShiftUp_PbPb_mu12_C1_J4 , sys_total_PbPb_mu12_C1_J4};
  double sys_PbPb_mu12_C1_J5_array[N_sys] = {sys_cFraction_PbPb_mu12_C1_J5, sys_lowerBound_PbPb_mu12_C1_J5, sys_JERsmear_PbPb_mu12_C1_J5, sys_bGS_PbPb_mu12_C1_J5,sys_JEUShiftUp_PbPb_mu12_C1_J5,sys_centShiftUp_PbPb_mu12_C1_J5 , sys_total_PbPb_mu12_C1_J5};
  double sys_PbPb_mu12_C1_J6_array[N_sys] = {sys_cFraction_PbPb_mu12_C1_J6, sys_lowerBound_PbPb_mu12_C1_J6, sys_JERsmear_PbPb_mu12_C1_J6, sys_bGS_PbPb_mu12_C1_J6,sys_JEUShiftUp_PbPb_mu12_C1_J6,sys_centShiftUp_PbPb_mu12_C1_J6 , sys_total_PbPb_mu12_C1_J6};      

  TCanvas *canv_J1 = new TCanvas("canv_J1","canv_J1",800,800);
  canv_J1->cd();
  TPad *pad_J1 = new TPad("pad_J1","pad_J1",0,0,1,1);
  pad_J1->SetLeftMargin(0.2);
  pad_J1->SetBottomMargin(0.2);
  pad_J1->Draw();
  pad_J1->cd();

  TH1D *h0_sys_J1 = new TH1D("h0_sys_J1","h0_sys_J1",N_sys,0,1.0*N_sys);
  h0_sys_J1->SetFillColor(kOrange);
  h0_sys_J1->SetBarWidth(0.15);
  h0_sys_J1->SetBarOffset(0.05);
  h0_sys_J1->SetStats(0);
  h0_sys_J1->SetMinimum(0.0);
  h0_sys_J1->SetMaximum(0.2);

  for(int i = 1; i <= N_sys; i++){
    h0_sys_J1->SetBinContent(i,sys_pp_mu12_J1_array[i-1]);
    h0_sys_J1->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }


  h0_sys_J1->GetXaxis()->SetTitleSize(0.06);
  // h0_sys_J1->SetBarWidth(new_bar_width);
  // h0_sys_J1->SetBarOffset(new_bar_offset);
  h0_sys_J1->SetTitle("");
  h0_sys_J1->Draw("b");

  //std::cout << sys_cFraction_highest_J1 << "\n";

  li->SetLineStyle(7);
  li->SetLineWidth(2);
  li->SetLineColor(kGray+2);
  double lineShift = 0.05;
  li->DrawLine(0+lineShift,sys_cFraction_highest_J1,1-lineShift,sys_cFraction_highest_J1);
  li->DrawLine(3+lineShift,sys_bGS_highest_J1,4-lineShift,sys_bGS_highest_J1);

  la->SetTextSize(0.035);

  la->DrawLatexNDC(0.535,0.8,"80 GeV < #font[52]{p}_{T}^{jet} < 90 GeV");
  
  TH1D *h1_sys_J1 = new TH1D("h1_sys_J1","h1_sys_J1",N_sys,0,1.0*N_sys);
  h1_sys_J1->SetFillColor(kMagenta-9);
  h1_sys_J1->SetBarWidth(0.15);
  h1_sys_J1->SetBarOffset(0.65);
  h1_sys_J1->SetStats(0);
  h1_sys_J1->SetMinimum(0.0);
  h1_sys_J1->SetMaximum(0.2);

  for(int i = 1; i <= N_sys; i++){
    h1_sys_J1->SetBinContent(i,sys_PbPb_mu12_C1_J1_array[i-1]);
    h1_sys_J1->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  // h1_sys_J1->SetBarWidth(new_bar_width);
  // h1_sys_J1->SetBarOffset(new_bar_offset);
  h1_sys_J1->Draw("b same");

  TH1D *h2_sys_J1 = new TH1D("h2_sys_J1","h2_sys_J1",N_sys,0,1.0*N_sys);
  h2_sys_J1->SetFillColor(kGreen+2);
  h2_sys_J1->SetBarWidth(0.15);
  h2_sys_J1->SetBarOffset(0.50);
  h2_sys_J1->SetStats(0);
  h2_sys_J1->SetMinimum(0.0);
  h2_sys_J1->SetMaximum(0.2);

  for(int i = 1; i <= N_sys; i++){
    h2_sys_J1->SetBinContent(i,sys_PbPb_mu12_C2_J1_array[i-1]);
    h2_sys_J1->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  

  // h2_sys_J1->SetBarWidth(new_bar_width);
  // h2_sys_J1->SetBarOffset(new_bar_offset);
  h2_sys_J1->Draw("b same");

  TH1D *h3_sys_J1 = new TH1D("h3_sys_J1","h3_sys_J1",N_sys,0,1.0*N_sys);
  h3_sys_J1->SetFillColor(kRed-4);
  h3_sys_J1->SetBarWidth(0.15);
  h3_sys_J1->SetBarOffset(0.35);
  h3_sys_J1->SetStats(0);
  h3_sys_J1->SetMinimum(0.0);
  h3_sys_J1->SetMaximum(0.2);

  for(int i = 1; i <= N_sys; i++){
    h3_sys_J1->SetBinContent(i,sys_PbPb_mu12_C3_J1_array[i-1]);
    h3_sys_J1->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  h3_sys_J1->Draw("b same");

  
  TH1D *h4_sys_J1 = new TH1D("h4_sys_J1","h4_sys_J1",N_sys,0,1.0*N_sys);
  h4_sys_J1->SetFillColor(kBlue+1);
  h4_sys_J1->SetBarWidth(0.15);
  h4_sys_J1->SetBarOffset(0.2);
  h4_sys_J1->SetStats(0);
  h4_sys_J1->SetMinimum(0.0);
  h4_sys_J1->SetMaximum(0.2);

  for(int i = 1; i <= N_sys; i++){
    h4_sys_J1->SetBinContent(i,sys_PbPb_mu12_C4_J1_array[i-1]);
    h4_sys_J1->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  h4_sys_J1->Draw("b same");
  
  TLegend *leg = new TLegend(0.22,0.65,0.4,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->AddEntry(h0_sys_J1,"pp","f");
  leg->AddEntry(h4_sys_J1,"PbPb 50-80%","f");
  leg->AddEntry(h3_sys_J1,"PbPb 30-50%","f");
  leg->AddEntry(h2_sys_J1,"PbPb 10-30%","f");
  leg->AddEntry(h1_sys_J1,"PbPb 0-10%","f");
  leg->Draw();
  


  TCanvas *canv_J2 = new TCanvas("canv_J2","canv_J2",800,800);
  canv_J2->cd();
  TPad *pad_J2 = new TPad("pad_J2","pad_J2",0,0,1,1);
  pad_J2->SetLeftMargin(0.2);
  pad_J2->SetBottomMargin(0.2);
  pad_J2->Draw();
  pad_J2->cd();

  TH1D *h0_sys_J2 = new TH1D("h0_sys_J2","h0_sys_J2",N_sys,0,1.0*N_sys);
  h0_sys_J2->SetFillColor(kOrange);
  h0_sys_J2->SetBarWidth(0.15);
  h0_sys_J2->SetBarOffset(0.05);
  h0_sys_J2->SetStats(0);
  h0_sys_J2->SetMinimum(0.0);
  h0_sys_J2->SetMaximum(0.2);

  for(int i = 1; i <= N_sys; i++){
    h0_sys_J2->SetBinContent(i,sys_pp_mu12_J2_array[i-1]);
    h0_sys_J2->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }


  h0_sys_J2->GetXaxis()->SetTitleSize(0.06);
  // h0_sys_J2->SetBarWidth(new_bar_width);
  // h0_sys_J2->SetBarOffset(new_bar_offset);
  h0_sys_J2->SetTitle("");
  h0_sys_J2->Draw("b");

  li->DrawLine(0+lineShift,sys_cFraction_highest_J2,1-lineShift,sys_cFraction_highest_J2);
  li->DrawLine(3+lineShift,sys_bGS_highest_J2,4-lineShift,sys_bGS_highest_J2);

  la->SetTextSize(0.035);

  la->DrawLatexNDC(0.535,0.8,"90 GeV < #font[52]{p}_{T}^{jet} < 100 GeV");
  
  TH1D *h1_sys_J2 = new TH1D("h1_sys_J2","h1_sys_J2",N_sys,0,1.0*N_sys);
  h1_sys_J2->SetFillColor(kMagenta-9);
  h1_sys_J2->SetBarWidth(0.15);
  h1_sys_J2->SetBarOffset(0.65);
  h1_sys_J2->SetStats(0);
  h1_sys_J2->SetMinimum(0.0);
  h1_sys_J2->SetMaximum(0.2);

  for(int i = 1; i <= N_sys; i++){
    h1_sys_J2->SetBinContent(i,sys_PbPb_mu12_C1_J2_array[i-1]);
    h1_sys_J2->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  // h1_sys_J2->SetBarWidth(new_bar_width);
  // h1_sys_J2->SetBarOffset(new_bar_offset);
  h1_sys_J2->Draw("b same");

  TH1D *h2_sys_J2 = new TH1D("h2_sys_J2","h2_sys_J2",N_sys,0,1.0*N_sys);
  h2_sys_J2->SetFillColor(kGreen+2);
  h2_sys_J2->SetBarWidth(0.15);
  h2_sys_J2->SetBarOffset(0.50);
  h2_sys_J2->SetStats(0);
  h2_sys_J2->SetMinimum(0.0);
  h2_sys_J2->SetMaximum(0.2);

  for(int i = 1; i <= N_sys; i++){
    h2_sys_J2->SetBinContent(i,sys_PbPb_mu12_C2_J2_array[i-1]);
    h2_sys_J2->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  // h2_sys_J2->SetBarWidth(new_bar_width);
  // h2_sys_J2->SetBarOffset(new_bar_offset);
  h2_sys_J2->Draw("b same");


  TH1D *h3_sys_J2 = new TH1D("h3_sys_J2","h3_sys_J2",N_sys,0,1.0*N_sys);
  h3_sys_J2->SetFillColor(kRed-4);
  h3_sys_J2->SetBarWidth(0.15);
  h3_sys_J2->SetBarOffset(0.35);
  h3_sys_J2->SetStats(0);
  h3_sys_J2->SetMinimum(0.0);
  h3_sys_J2->SetMaximum(0.2);

  for(int i = 1; i <= N_sys; i++){
    h3_sys_J2->SetBinContent(i,sys_PbPb_mu12_C3_J2_array[i-1]);
    h3_sys_J2->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  // h3_sys_J2->SetBarWidth(new_bar_width);
  // h3_sys_J2->SetBarOffset(new_bar_offset);
  h3_sys_J2->Draw("b same");

  TH1D *h4_sys_J2 = new TH1D("h4_sys_J2","h4_sys_J2",N_sys,0,1.0*N_sys);
  h4_sys_J2->SetFillColor(kBlue+1);
  h4_sys_J2->SetBarWidth(0.15);
  h4_sys_J2->SetBarOffset(0.2);
  h4_sys_J2->SetStats(0);
  h4_sys_J2->SetMinimum(0.0);
  h4_sys_J2->SetMaximum(0.2);

  for(int i = 1; i <= N_sys; i++){
    h4_sys_J2->SetBinContent(i,sys_PbPb_mu12_C4_J2_array[i-1]);
    h4_sys_J2->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  h4_sys_J2->Draw("b same");


  
  leg->Draw();

  

  // ------------------------------------------------------------------------------------------------------

  TCanvas *canv_J3 = new TCanvas("canv_J3","canv_J3",800,800);
  canv_J3->cd();
  TPad *pad_J3 = new TPad("pad_J3","pad_J3",0,0,1,1);
  pad_J3->SetLeftMargin(0.2);
  pad_J3->SetBottomMargin(0.2);
  pad_J3->Draw();
  pad_J3->cd();

  TH1D *h0_sys_J3 = new TH1D("h0_sys_J3","h0_sys_J3",N_sys,0,1.0*N_sys);
  h0_sys_J3->SetFillColor(kOrange);
  h0_sys_J3->SetBarWidth(0.15);
  h0_sys_J3->SetBarOffset(0.05);
  h0_sys_J3->SetStats(0);
  h0_sys_J3->SetMinimum(0.0);
  h0_sys_J3->SetMaximum(0.2);

  for(int i = 1; i <= N_sys; i++){
    h0_sys_J3->SetBinContent(i,sys_pp_mu12_J3_array[i-1]);
    h0_sys_J3->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  h0_sys_J3->GetXaxis()->SetTitleSize(0.04);
  h0_sys_J3->SetTitle("");
  // h0_sys_J3->SetBarWidth(new_bar_width);
  // h0_sys_J3->SetBarOffset(new_bar_offset);
  h0_sys_J3->Draw("b");

  li->DrawLine(0+lineShift,sys_cFraction_highest_J3,1-lineShift,sys_cFraction_highest_J3);
  li->DrawLine(3+lineShift,sys_bGS_highest_J3,4-lineShift,sys_bGS_highest_J3);
  
  la->DrawLatexNDC(0.535,0.8,"100 GeV < #font[52]{p}_{T}^{jet} < 120 GeV");
  
  TH1D *h1_sys_J3 = new TH1D("h1_sys_J3","h1_sys_J3",N_sys,0,1.0*N_sys);
  h1_sys_J3->SetFillColor(kMagenta-9);
  h1_sys_J3->SetBarWidth(0.15);
  h1_sys_J3->SetBarOffset(0.65);
  h1_sys_J3->SetStats(0);
  h1_sys_J3->SetMinimum(0.0);
  h1_sys_J3->SetMaximum(0.2);

  for(int i = 1; i <= N_sys; i++){
    h1_sys_J3->SetBinContent(i,sys_PbPb_mu12_C1_J3_array[i-1]);
    h1_sys_J3->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  // h1_sys_J3->SetBarWidth(new_bar_width);
  // h1_sys_J3->SetBarOffset(new_bar_offset);
  h1_sys_J3->Draw("b same");

  TH1D *h2_sys_J3 = new TH1D("h2_sys_J3","h2_sys_J3",N_sys,0,1.0*N_sys);
  h2_sys_J3->SetFillColor(kGreen+2);
  h2_sys_J3->SetBarWidth(0.15);
  h2_sys_J3->SetBarOffset(0.50);
  h2_sys_J3->SetStats(0);
  h2_sys_J3->SetMinimum(0.0);
  h2_sys_J3->SetMaximum(0.2);

  for(int i = 1; i <= N_sys; i++){
    h2_sys_J3->SetBinContent(i,sys_PbPb_mu12_C2_J3_array[i-1]);
    h2_sys_J3->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  // h2_sys_J3->SetBarWidth(new_bar_width);
  // h2_sys_J3->SetBarOffset(new_bar_offset);
  h2_sys_J3->Draw("b same");

  TH1D *h3_sys_J3 = new TH1D("h3_sys_J3","h3_sys_J3",N_sys,0,1.0*N_sys);
  h3_sys_J3->SetFillColor(kRed-4);
  h3_sys_J3->SetBarWidth(0.15);
  h3_sys_J3->SetBarOffset(0.35);
  h3_sys_J3->SetStats(0);
  h3_sys_J3->SetMinimum(0.0);
  h3_sys_J3->SetMaximum(0.2);

  for(int i = 1; i <= N_sys; i++){
    h3_sys_J3->SetBinContent(i,sys_PbPb_mu12_C3_J3_array[i-1]);
    h3_sys_J3->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  // h3_sys_J3->SetBarWidth(new_bar_width);
  // h3_sys_J3->SetBarOffset(new_bar_offset);
  h3_sys_J3->Draw("b same");

  TH1D *h4_sys_J3 = new TH1D("h4_sys_J3","h4_sys_J3",N_sys,0,1.0*N_sys);
  h4_sys_J3->SetFillColor(kBlue+1);
  h4_sys_J3->SetBarWidth(0.15);
  h4_sys_J3->SetBarOffset(0.2);
  h4_sys_J3->SetStats(0);
  h4_sys_J3->SetMinimum(0.0);
  h4_sys_J3->SetMaximum(0.2);

  for(int i = 1; i <= N_sys; i++){
    h4_sys_J3->SetBinContent(i,sys_PbPb_mu12_C4_J3_array[i-1]);
    h4_sys_J3->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  h4_sys_J3->Draw("b same");
  
  leg->Draw();

  // ------------------------------------------------------------------------------------------------------

  TCanvas *canv_J4 = new TCanvas("canv_J4","canv_J4",800,800);
  canv_J4->cd();
  TPad *pad_J4 = new TPad("pad_J4","pad_J4",0,0,1,1);
  pad_J4->SetLeftMargin(0.2);
  pad_J4->SetBottomMargin(0.2);
  pad_J4->Draw();
  pad_J4->cd();

  TH1D *h0_sys_J4 = new TH1D("h0_sys_J4","h0_sys_J4",N_sys,0,1.0*N_sys);
  h0_sys_J4->SetFillColor(kOrange);
  h0_sys_J4->SetBarWidth(0.15);
  h0_sys_J4->SetBarOffset(0.05);
  h0_sys_J4->SetStats(0);
  h0_sys_J4->SetMinimum(0.0);
  h0_sys_J4->SetMaximum(0.2);

  for(int i = 1; i <= N_sys; i++){
    h0_sys_J4->SetBinContent(i,sys_pp_mu12_J4_array[i-1]);
    h0_sys_J4->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  h0_sys_J4->GetXaxis()->SetTitleSize(0.04);
  h0_sys_J4->SetTitle("");
  // h0_sys_J4->SetBarWidth(new_bar_width);
  // h0_sys_J4->SetBarOffset(new_bar_offset);
  h0_sys_J4->Draw("b");

  li->DrawLine(0+lineShift,sys_cFraction_highest_J4,1-lineShift,sys_cFraction_highest_J4);
  li->DrawLine(3+lineShift,sys_bGS_highest_J4,4-lineShift,sys_bGS_highest_J4);

  la->DrawLatexNDC(0.535,0.8,"120 GeV < #font[52]{p}_{T}^{jet} < 150 GeV");
  
  TH1D *h1_sys_J4 = new TH1D("h1_sys_J4","h1_sys_J4",N_sys,0,1.0*N_sys);
  h1_sys_J4->SetFillColor(kMagenta-9);
  h1_sys_J4->SetBarWidth(0.15);
  h1_sys_J4->SetBarOffset(0.65);
  h1_sys_J4->SetStats(0);
  h1_sys_J4->SetMinimum(0.0);
  h1_sys_J4->SetMaximum(0.2);

  for(int i = 1; i <= N_sys; i++){
    h1_sys_J4->SetBinContent(i,sys_PbPb_mu12_C1_J4_array[i-1]);
    h1_sys_J4->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  // h1_sys_J4->SetBarWidth(new_bar_width);
  // h1_sys_J4->SetBarOffset(new_bar_offset);
  h1_sys_J4->Draw("b same");

  TH1D *h2_sys_J4 = new TH1D("h2_sys_J4","h2_sys_J4",N_sys,0,1.0*N_sys);
  h2_sys_J4->SetFillColor(kGreen+2);
  h2_sys_J4->SetBarWidth(0.15);
  h2_sys_J4->SetBarOffset(0.50);
  h2_sys_J4->SetStats(0);
  h2_sys_J4->SetMinimum(0.0);
  h2_sys_J4->SetMaximum(0.2);

  for(int i = 1; i <= N_sys; i++){
    h2_sys_J4->SetBinContent(i,sys_PbPb_mu12_C2_J4_array[i-1]);
    h2_sys_J4->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  // h2_sys_J4->SetBarWidth(new_bar_width);
  // h2_sys_J4->SetBarOffset(new_bar_offset);
  h2_sys_J4->Draw("b same");

  TH1D *h3_sys_J4 = new TH1D("h3_sys_J4","h3_sys_J4",N_sys,0,1.0*N_sys);
  h3_sys_J4->SetFillColor(kRed-4);
  h3_sys_J4->SetBarWidth(0.15);
  h3_sys_J4->SetBarOffset(0.35);
  h3_sys_J4->SetStats(0);
  h3_sys_J4->SetMinimum(0.0);
  h3_sys_J4->SetMaximum(0.2);

  for(int i = 1; i <= N_sys; i++){
    h3_sys_J4->SetBinContent(i,sys_PbPb_mu12_C3_J4_array[i-1]);
    h3_sys_J4->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  // h3_sys_J4->SetBarWidth(new_bar_width);
  // h3_sys_J4->SetBarOffset(new_bar_offset);
  h3_sys_J4->Draw("b same");

  TH1D *h4_sys_J4 = new TH1D("h4_sys_J4","h4_sys_J4",N_sys,0,1.0*N_sys);
  h4_sys_J4->SetFillColor(kBlue+1);
  h4_sys_J4->SetBarWidth(0.15);
  h4_sys_J4->SetBarOffset(0.2);
  h4_sys_J4->SetStats(0);
  h4_sys_J4->SetMinimum(0.0);
  h4_sys_J4->SetMaximum(0.2);

  for(int i = 1; i <= N_sys; i++){
    h4_sys_J4->SetBinContent(i,sys_PbPb_mu12_C4_J4_array[i-1]);
    h4_sys_J4->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  h4_sys_J4->Draw("b same");

  
  leg->Draw();


  // ------------------------------------------------------------------------------------------------------

  TCanvas *canv_J5 = new TCanvas("canv_J5","canv_J5",800,800);
  canv_J5->cd();
  TPad *pad_J5 = new TPad("pad_J5","pad_J5",0,0,1,1);
  pad_J5->SetLeftMargin(0.2);
  pad_J5->SetBottomMargin(0.2);
  pad_J5->Draw();
  pad_J5->cd();

  TH1D *h0_sys_J5 = new TH1D("h0_sys_J5","h0_sys_J5",N_sys,0,1.0*N_sys);
  h0_sys_J5->SetFillColor(kOrange);
  h0_sys_J5->SetBarWidth(0.15);
  h0_sys_J5->SetBarOffset(0.05);
  h0_sys_J5->SetStats(0);
  h0_sys_J5->SetMinimum(0.0);
  h0_sys_J5->SetMaximum(0.2);

  for(int i = 1; i <= N_sys; i++){
    h0_sys_J5->SetBinContent(i,sys_pp_mu12_J5_array[i-1]);
    h0_sys_J5->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  h0_sys_J5->GetXaxis()->SetTitleSize(0.04);
  h0_sys_J5->SetTitle("");
  // h0_sys_J5->SetBarWidth(new_bar_width);
  // h0_sys_J5->SetBarOffset(new_bar_offset);
  h0_sys_J5->Draw("b");

  li->DrawLine(0+lineShift,sys_cFraction_highest_J5,1-lineShift,sys_cFraction_highest_J5);
  li->DrawLine(3+lineShift,sys_bGS_highest_J5,4-lineShift,sys_bGS_highest_J5);

  la->DrawLatexNDC(0.535,0.8,"150 GeV < #font[52]{p}_{T}^{jet} < 200 GeV");
  
  TH1D *h1_sys_J5 = new TH1D("h1_sys_J5","h1_sys_J5",N_sys,0,1.0*N_sys);
  h1_sys_J5->SetFillColor(kMagenta-9);
  h1_sys_J5->SetBarWidth(0.15);
  h1_sys_J5->SetBarOffset(0.65);
  h1_sys_J5->SetStats(0);
  h1_sys_J5->SetMinimum(0.0);
  h1_sys_J5->SetMaximum(0.2);

  for(int i = 1; i <= N_sys; i++){
    h1_sys_J5->SetBinContent(i,sys_PbPb_mu12_C1_J5_array[i-1]);
    h1_sys_J5->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  // h1_sys_J5->SetBarWidth(new_bar_width);
  // h1_sys_J5->SetBarOffset(new_bar_offset);
  h1_sys_J5->Draw("b same");

  TH1D *h2_sys_J5 = new TH1D("h2_sys_J5","h2_sys_J5",N_sys,0,1.0*N_sys);
  h2_sys_J5->SetFillColor(kGreen+2);
  h2_sys_J5->SetBarWidth(0.15);
  h2_sys_J5->SetBarOffset(0.50);
  h2_sys_J5->SetStats(0);
  h2_sys_J5->SetMinimum(0.0);
  h2_sys_J5->SetMaximum(0.2);

  for(int i = 1; i <= N_sys; i++){
    h2_sys_J5->SetBinContent(i,sys_PbPb_mu12_C2_J5_array[i-1]);
    h2_sys_J5->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  // h2_sys_J5->SetBarWidth(new_bar_width);
  // h2_sys_J5->SetBarOffset(new_bar_offset);
  h2_sys_J5->Draw("b same");

  TH1D *h3_sys_J5 = new TH1D("h3_sys_J5","h3_sys_J5",N_sys,0,1.0*N_sys);
  h3_sys_J5->SetFillColor(kRed-4);
  h3_sys_J5->SetBarWidth(0.15);
  h3_sys_J5->SetBarOffset(0.35);
  h3_sys_J5->SetStats(0);
  h3_sys_J5->SetMinimum(0.0);
  h3_sys_J5->SetMaximum(0.2);

  for(int i = 1; i <= N_sys; i++){
    h3_sys_J5->SetBinContent(i,sys_PbPb_mu12_C3_J5_array[i-1]);
    h3_sys_J5->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  // h3_sys_J5->SetBarWidth(new_bar_width);
  // h3_sys_J5->SetBarOffset(new_bar_offset);
  h3_sys_J5->Draw("b same");

  TH1D *h4_sys_J5 = new TH1D("h4_sys_J5","h4_sys_J5",N_sys,0,1.0*N_sys);
  h4_sys_J5->SetFillColor(kBlue+1);
  h4_sys_J5->SetBarWidth(0.15);
  h4_sys_J5->SetBarOffset(0.2);
  h4_sys_J5->SetStats(0);
  h4_sys_J5->SetMinimum(0.0);
  h4_sys_J5->SetMaximum(0.2);

  for(int i = 1; i <= N_sys; i++){
    h4_sys_J5->SetBinContent(i,sys_PbPb_mu12_C4_J5_array[i-1]);
    h4_sys_J5->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  h4_sys_J5->Draw("b same");

  
  leg->Draw();

  // ------------------------------------------------------------------------------------------------------

  TCanvas *canv_J6 = new TCanvas("canv_J6","canv_J6",800,800);
  canv_J6->cd();
  TPad *pad_J6 = new TPad("pad_J6","pad_J6",0,0,1,1);
  pad_J6->SetLeftMargin(0.2);
  pad_J6->SetBottomMargin(0.2);
  pad_J6->Draw();
  pad_J6->cd();

  TH1D *h0_sys_J6 = new TH1D("h0_sys_J6","h0_sys_J6",N_sys,0,1.0*N_sys);
  h0_sys_J6->SetFillColor(kOrange);
  h0_sys_J6->SetBarWidth(0.15);
  h0_sys_J6->SetBarOffset(0.05);
  h0_sys_J6->SetStats(0);
  h0_sys_J6->SetMinimum(0.0);
  h0_sys_J6->SetMaximum(0.2);

  for(int i = 1; i <= N_sys; i++){
    h0_sys_J6->SetBinContent(i,sys_pp_mu12_J6_array[i-1]);
    h0_sys_J6->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  h0_sys_J6->GetXaxis()->SetTitleSize(0.04);
  h0_sys_J6->SetTitle("");
  // h0_sys_J6->SetBarWidth(new_bar_width);
  // h0_sys_J6->SetBarOffset(new_bar_offset);
  h0_sys_J6->Draw("b");

  li->DrawLine(0+lineShift,sys_cFraction_highest_J6,1-lineShift,sys_cFraction_highest_J6);
  li->DrawLine(3+lineShift,sys_bGS_highest_J6,4-lineShift,sys_bGS_highest_J6);

  la->DrawLatexNDC(0.535,0.8,"200 GeV < #font[52]{p}_{T}^{jet} < 300 GeV");
  
  TH1D *h1_sys_J6 = new TH1D("h1_sys_J6","h1_sys_J6",N_sys,0,1.0*N_sys);
  h1_sys_J6->SetFillColor(kMagenta-9);
  h1_sys_J6->SetBarWidth(0.15);
  h1_sys_J6->SetBarOffset(0.65);
  h1_sys_J6->SetStats(0);
  h1_sys_J6->SetMinimum(0.0);
  h1_sys_J6->SetMaximum(0.2);

  for(int i = 1; i <= N_sys; i++){
    h1_sys_J6->SetBinContent(i,sys_PbPb_mu12_C1_J6_array[i-1]);
    h1_sys_J6->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  // h1_sys_J6->SetBarWidth(new_bar_width);
  // h1_sys_J6->SetBarOffset(new_bar_offset);
  h1_sys_J6->Draw("b same");

  TH1D *h2_sys_J6 = new TH1D("h2_sys_J6","h2_sys_J6",N_sys,0,1.0*N_sys);
  h2_sys_J6->SetFillColor(kGreen+2);
  h2_sys_J6->SetBarWidth(0.15);
  h2_sys_J6->SetBarOffset(0.50);
  h2_sys_J6->SetStats(0);
  h2_sys_J6->SetMinimum(0.0);
  h2_sys_J6->SetMaximum(0.2);

  for(int i = 1; i <= N_sys; i++){
    h2_sys_J6->SetBinContent(i,sys_PbPb_mu12_C2_J6_array[i-1]);
    h2_sys_J6->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  // h2_sys_J6->SetBarWidth(new_bar_width);
  // h2_sys_J6->SetBarOffset(new_bar_offset);
  h2_sys_J6->Draw("b same");

  TH1D *h3_sys_J6 = new TH1D("h3_sys_J6","h3_sys_J6",N_sys,0,1.0*N_sys);
  h3_sys_J6->SetFillColor(kRed-4);
  h3_sys_J6->SetBarWidth(0.15);
  h3_sys_J6->SetBarOffset(0.35);
  h3_sys_J6->SetStats(0);
  h3_sys_J6->SetMinimum(0.0);
  h3_sys_J6->SetMaximum(0.2);

  for(int i = 1; i <= N_sys; i++){
    h3_sys_J6->SetBinContent(i,sys_PbPb_mu12_C3_J6_array[i-1]);
    h3_sys_J6->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  // h3_sys_J6->SetBarWidth(new_bar_width);
  // h3_sys_J6->SetBarOffset(new_bar_offset);
  h3_sys_J6->Draw("b same");

  TH1D *h4_sys_J6 = new TH1D("h4_sys_J6","h4_sys_J6",N_sys,0,1.0*N_sys);
  h4_sys_J6->SetFillColor(kBlue+1);
  h4_sys_J6->SetBarWidth(0.15);
  h4_sys_J6->SetBarOffset(0.2);
  h4_sys_J6->SetStats(0);
  h4_sys_J6->SetMinimum(0.0);
  h4_sys_J6->SetMaximum(0.2);

  for(int i = 1; i <= N_sys; i++){
    h4_sys_J6->SetBinContent(i,sys_PbPb_mu12_C4_J6_array[i-1]);
    h4_sys_J6->GetXaxis()->SetBinLabel(i,sys_names[i-1].c_str());
  }

  h4_sys_J6->Draw("b same");
  
  leg->Draw();

  




  canv_J1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/systematics/nice-plots/J1.pdf");
  canv_J2->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/systematics/nice-plots/J2.pdf");
  canv_J3->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/systematics/nice-plots/J3.pdf");
  canv_J4->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/systematics/nice-plots/J4.pdf");
  canv_J5->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/systematics/nice-plots/J5.pdf");
  canv_J6->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/systematics/nice-plots/J6.pdf");    





  

  /// now create a plot by jetPt
  
  

  // c-fraction-variation
  double input_pp_cFrac_J1 = 0;
  double input_pp_cFrac_J2 = 0;
  double input_pp_cFrac_J3 = 0;
  double input_pp_cFrac_J4 = 0;
  double input_pp_cFrac_J5 = 0;
  double input_pp_cFrac_J6 = 0;

  double input_C4_cFrac_J1 = 0;
  double input_C4_cFrac_J2 = 0;
  double input_C4_cFrac_J3 = 0;
  double input_C4_cFrac_J4 = 0;
  double input_C4_cFrac_J5 = 0;
  double input_C4_cFrac_J6 = 0;

  double input_C3_cFrac_J1 = 0;
  double input_C3_cFrac_J2 = 0;
  double input_C3_cFrac_J3 = 0;
  double input_C3_cFrac_J4 = 0;
  double input_C3_cFrac_J5 = 0;
  double input_C3_cFrac_J6 = 0;

  double input_C2_cFrac_J1 = 0;
  double input_C2_cFrac_J2 = 0;
  double input_C2_cFrac_J3 = 0;
  double input_C2_cFrac_J4 = 0;
  double input_C2_cFrac_J5 = 0;
  double input_C2_cFrac_J6 = 0;

  double input_C1_cFrac_J1 = 0;
  double input_C1_cFrac_J2 = 0;
  double input_C1_cFrac_J3 = 0;
  double input_C1_cFrac_J4 = 0;
  double input_C1_cFrac_J5 = 0;
  double input_C1_cFrac_J6 = 0;

  // fit-lower-bound
  double input_pp_lowerBound_J1 = 0;
  double input_pp_lowerBound_J2 = 0;
  double input_pp_lowerBound_J3 = 0;
  double input_pp_lowerBound_J4 = 0;
  double input_pp_lowerBound_J5 = 0;
  double input_pp_lowerBound_J6 = 0;

  double input_C4_lowerBound_J1 = 0;
  double input_C4_lowerBound_J2 = 0;
  double input_C4_lowerBound_J3 = 0;
  double input_C4_lowerBound_J4 = 0;
  double input_C4_lowerBound_J5 = 0;
  double input_C4_lowerBound_J6 = 0;

  double input_C3_lowerBound_J1 = 0;
  double input_C3_lowerBound_J2 = 0;
  double input_C3_lowerBound_J3 = 0;
  double input_C3_lowerBound_J4 = 0;
  double input_C3_lowerBound_J5 = 0;
  double input_C3_lowerBound_J6 = 0;

  double input_C2_lowerBound_J1 = 0;
  double input_C2_lowerBound_J2 = 0;
  double input_C2_lowerBound_J3 = 0;
  double input_C2_lowerBound_J4 = 0;
  double input_C2_lowerBound_J5 = 0;
  double input_C2_lowerBound_J6 = 0;

  double input_C1_lowerBound_J1 = 0;
  double input_C1_lowerBound_J2 = 0;
  double input_C1_lowerBound_J3 = 0;
  double input_C1_lowerBound_J4 = 0;
  double input_C1_lowerBound_J5 = 0;
  double input_C1_lowerBound_J6 = 0;

  // JER-smear
  double input_pp_JERsmear_J1 = 0;
  double input_pp_JERsmear_J2 = 0;
  double input_pp_JERsmear_J3 = 0;
  double input_pp_JERsmear_J4 = 0;
  double input_pp_JERsmear_J5 = 0;
  double input_pp_JERsmear_J6 = 0;

  double input_C4_JERsmear_J1 = 0;
  double input_C4_JERsmear_J2 = 0;
  double input_C4_JERsmear_J3 = 0;
  double input_C4_JERsmear_J4 = 0;
  double input_C4_JERsmear_J5 = 0;
  double input_C4_JERsmear_J6 = 0;

  double input_C3_JERsmear_J1 = 0;
  double input_C3_JERsmear_J2 = 0;
  double input_C3_JERsmear_J3 = 0;
  double input_C3_JERsmear_J4 = 0;
  double input_C3_JERsmear_J5 = 0;
  double input_C3_JERsmear_J6 = 0;

  double input_C2_JERsmear_J1 = 0;
  double input_C2_JERsmear_J2 = 0;
  double input_C2_JERsmear_J3 = 0;
  double input_C2_JERsmear_J4 = 0;
  double input_C2_JERsmear_J5 = 0;
  double input_C2_JERsmear_J6 = 0;

  double input_C1_JERsmear_J1 = 0;
  double input_C1_JERsmear_J2 = 0;  
  double input_C1_JERsmear_J3 = 0;
  double input_C1_JERsmear_J4 = 0;
  double input_C1_JERsmear_J5 = 0;
  double input_C1_JERsmear_J6 = 0;

  // gluon-splitting b fraction
  double input_pp_bGS_J1 = 0;
  double input_pp_bGS_J2 = 0;
  double input_pp_bGS_J3 = 0;
  double input_pp_bGS_J4 = 0;
  double input_pp_bGS_J5 = 0;
  double input_pp_bGS_J6 = 0;

  double input_C4_bGS_J1 = 0;
  double input_C4_bGS_J2 = 0;  
  double input_C4_bGS_J3 = 0;
  double input_C4_bGS_J4 = 0;
  double input_C4_bGS_J5 = 0;
  double input_C4_bGS_J6 = 0;

  double input_C3_bGS_J1 = 0;
  double input_C3_bGS_J2 = 0;  
  double input_C3_bGS_J3 = 0;
  double input_C3_bGS_J4 = 0;
  double input_C3_bGS_J5 = 0;
  double input_C3_bGS_J6 = 0;

  double input_C2_bGS_J1 = 0;
  double input_C2_bGS_J2 = 0;  
  double input_C2_bGS_J3 = 0;
  double input_C2_bGS_J4 = 0;
  double input_C2_bGS_J5 = 0;
  double input_C2_bGS_J6 = 0;

  double input_C1_bGS_J1 = 0;
  double input_C1_bGS_J2 = 0;
  double input_C1_bGS_J3 = 0;
  double input_C1_bGS_J4 = 0;
  double input_C1_bGS_J5 = 0;
  double input_C1_bGS_J6 = 0;

  // JEU shift-up
  double input_pp_JEUShiftUp_J1 = 0;
  double input_pp_JEUShiftUp_J2 = 0;
  double input_pp_JEUShiftUp_J3 = 0;
  double input_pp_JEUShiftUp_J4 = 0;
  double input_pp_JEUShiftUp_J5 = 0;
  double input_pp_JEUShiftUp_J6 = 0;

  double input_C4_JEUShiftUp_J1 = 0;
  double input_C4_JEUShiftUp_J2 = 0;
  double input_C4_JEUShiftUp_J3 = 0;
  double input_C4_JEUShiftUp_J4 = 0;
  double input_C4_JEUShiftUp_J5 = 0;
  double input_C4_JEUShiftUp_J6 = 0;

  double input_C3_JEUShiftUp_J1 = 0;
  double input_C3_JEUShiftUp_J2 = 0;
  double input_C3_JEUShiftUp_J3 = 0;
  double input_C3_JEUShiftUp_J4 = 0;
  double input_C3_JEUShiftUp_J5 = 0;
  double input_C3_JEUShiftUp_J6 = 0;

  double input_C2_JEUShiftUp_J1 = 0;
  double input_C2_JEUShiftUp_J2 = 0;
  double input_C2_JEUShiftUp_J3 = 0;
  double input_C2_JEUShiftUp_J4 = 0;
  double input_C2_JEUShiftUp_J5 = 0;
  double input_C2_JEUShiftUp_J6 = 0;

  double input_C1_JEUShiftUp_J1 = 0;
  double input_C1_JEUShiftUp_J2 = 0;
  double input_C1_JEUShiftUp_J3 = 0;
  double input_C1_JEUShiftUp_J4 = 0;
  double input_C1_JEUShiftUp_J5 = 0;
  double input_C1_JEUShiftUp_J6 = 0;

  // JEU shift-down
  double input_pp_JEUShiftDown_J1 = 0;
  double input_pp_JEUShiftDown_J2 = 0;
  double input_pp_JEUShiftDown_J3 = 0;
  double input_pp_JEUShiftDown_J4 = 0;
  double input_pp_JEUShiftDown_J5 = 0;
  double input_pp_JEUShiftDown_J6 = 0;

  double input_C4_JEUShiftDown_J1 = 0;
  double input_C4_JEUShiftDown_J2 = 0;
  double input_C4_JEUShiftDown_J3 = 0;
  double input_C4_JEUShiftDown_J4 = 0;
  double input_C4_JEUShiftDown_J5 = 0;
  double input_C4_JEUShiftDown_J6 = 0;

  double input_C3_JEUShiftDown_J1 = 0;
  double input_C3_JEUShiftDown_J2 = 0;
  double input_C3_JEUShiftDown_J3 = 0;
  double input_C3_JEUShiftDown_J4 = 0;
  double input_C3_JEUShiftDown_J5 = 0;
  double input_C3_JEUShiftDown_J6 = 0;

  double input_C2_JEUShiftDown_J1 = 0;
  double input_C2_JEUShiftDown_J2 = 0;
  double input_C2_JEUShiftDown_J3 = 0;
  double input_C2_JEUShiftDown_J4 = 0;
  double input_C2_JEUShiftDown_J5 = 0;
  double input_C2_JEUShiftDown_J6 = 0;

  double input_C1_JEUShiftDown_J1 = 0;
  double input_C1_JEUShiftDown_J2 = 0;
  double input_C1_JEUShiftDown_J3 = 0;
  double input_C1_JEUShiftDown_J4 = 0;
  double input_C1_JEUShiftDown_J5 = 0;
  double input_C1_JEUShiftDown_J6 = 0;

  // JEU shift combined
  double input_pp_JEUShiftCombined_J1 = 0;
  double input_pp_JEUShiftCombined_J2 = 0;
  double input_pp_JEUShiftCombined_J3 = 0;
  double input_pp_JEUShiftCombined_J4 = 0;
  double input_pp_JEUShiftCombined_J5 = 0;
  double input_pp_JEUShiftCombined_J6 = 0;

  double input_C4_JEUShiftCombined_J1 = 0;
  double input_C4_JEUShiftCombined_J2 = 0;
  double input_C4_JEUShiftCombined_J3 = 0;
  double input_C4_JEUShiftCombined_J4 = 0;
  double input_C4_JEUShiftCombined_J5 = 0;
  double input_C4_JEUShiftCombined_J6 = 0;

  double input_C3_JEUShiftCombined_J1 = 0;
  double input_C3_JEUShiftCombined_J2 = 0;
  double input_C3_JEUShiftCombined_J3 = 0;
  double input_C3_JEUShiftCombined_J4 = 0;
  double input_C3_JEUShiftCombined_J5 = 0;
  double input_C3_JEUShiftCombined_J6 = 0;

  double input_C2_JEUShiftCombined_J1 = 0;
  double input_C2_JEUShiftCombined_J2 = 0;
  double input_C2_JEUShiftCombined_J3 = 0;
  double input_C2_JEUShiftCombined_J4 = 0;
  double input_C2_JEUShiftCombined_J5 = 0;
  double input_C2_JEUShiftCombined_J6 = 0;

  double input_C1_JEUShiftCombined_J1 = 0;
  double input_C1_JEUShiftCombined_J2 = 0;
  double input_C1_JEUShiftCombined_J3 = 0;
  double input_C1_JEUShiftCombined_J4 = 0;
  double input_C1_JEUShiftCombined_J5 = 0;
  double input_C1_JEUShiftCombined_J6 = 0;


  // cent shift-up
  double input_pp_centShiftUp_J1 = 0;
  double input_pp_centShiftUp_J2 = 0;
  double input_pp_centShiftUp_J3 = 0;
  double input_pp_centShiftUp_J4 = 0;
  double input_pp_centShiftUp_J5 = 0;
  double input_pp_centShiftUp_J6 = 0;

  double input_C4_centShiftUp_J1 = 0;
  double input_C4_centShiftUp_J2 = 0;
  double input_C4_centShiftUp_J3 = 0;
  double input_C4_centShiftUp_J4 = 0;
  double input_C4_centShiftUp_J5 = 0;
  double input_C4_centShiftUp_J6 = 0;

  double input_C3_centShiftUp_J1 = 0;
  double input_C3_centShiftUp_J2 = 0;
  double input_C3_centShiftUp_J3 = 0;
  double input_C3_centShiftUp_J4 = 0;
  double input_C3_centShiftUp_J5 = 0;
  double input_C3_centShiftUp_J6 = 0;

  double input_C2_centShiftUp_J1 = 0;
  double input_C2_centShiftUp_J2 = 0;
  double input_C2_centShiftUp_J3 = 0;
  double input_C2_centShiftUp_J4 = 0;
  double input_C2_centShiftUp_J5 = 0;
  double input_C2_centShiftUp_J6 = 0;

  double input_C1_centShiftUp_J1 = 0;
  double input_C1_centShiftUp_J2 = 0;
  double input_C1_centShiftUp_J3 = 0;
  double input_C1_centShiftUp_J4 = 0;
  double input_C1_centShiftUp_J5 = 0;
  double input_C1_centShiftUp_J6 = 0;

  // cent shift-down
  double input_pp_centShiftDown_J1 = 0;
  double input_pp_centShiftDown_J2 = 0;
  double input_pp_centShiftDown_J3 = 0;
  double input_pp_centShiftDown_J4 = 0;
  double input_pp_centShiftDown_J5 = 0;
  double input_pp_centShiftDown_J6 = 0;

  double input_C4_centShiftDown_J1 = 0;
  double input_C4_centShiftDown_J2 = 0;
  double input_C4_centShiftDown_J3 = 0;
  double input_C4_centShiftDown_J4 = 0;
  double input_C4_centShiftDown_J5 = 0;
  double input_C4_centShiftDown_J6 = 0;

  double input_C3_centShiftDown_J1 = 0;
  double input_C3_centShiftDown_J2 = 0;
  double input_C3_centShiftDown_J3 = 0;
  double input_C3_centShiftDown_J4 = 0;
  double input_C3_centShiftDown_J5 = 0;
  double input_C3_centShiftDown_J6 = 0;

  double input_C2_centShiftDown_J1 = 0;
  double input_C2_centShiftDown_J2 = 0;
  double input_C2_centShiftDown_J3 = 0;
  double input_C2_centShiftDown_J4 = 0;
  double input_C2_centShiftDown_J5 = 0;
  double input_C2_centShiftDown_J6 = 0;

  double input_C1_centShiftDown_J1 = 0;
  double input_C1_centShiftDown_J2 = 0;
  double input_C1_centShiftDown_J3 = 0;
  double input_C1_centShiftDown_J4 = 0;
  double input_C1_centShiftDown_J5 = 0;
  double input_C1_centShiftDown_J6 = 0;

  // cent shift-up
  double input_pp_centShiftCombined_J1 = 0;
  double input_pp_centShiftCombined_J2 = 0;
  double input_pp_centShiftCombined_J3 = 0;
  double input_pp_centShiftCombined_J4 = 0;
  double input_pp_centShiftCombined_J5 = 0;
  double input_pp_centShiftCombined_J6 = 0;

  double input_C4_centShiftCombined_J1 = 0;
  double input_C4_centShiftCombined_J2 = 0;
  double input_C4_centShiftCombined_J3 = 0;
  double input_C4_centShiftCombined_J4 = 0;
  double input_C4_centShiftCombined_J5 = 0;
  double input_C4_centShiftCombined_J6 = 0;

  double input_C3_centShiftCombined_J1 = 0;
  double input_C3_centShiftCombined_J2 = 0;
  double input_C3_centShiftCombined_J3 = 0;
  double input_C3_centShiftCombined_J4 = 0;
  double input_C3_centShiftCombined_J5 = 0;
  double input_C3_centShiftCombined_J6 = 0;

  double input_C2_centShiftCombined_J1 = 0;
  double input_C2_centShiftCombined_J2 = 0;
  double input_C2_centShiftCombined_J3 = 0;
  double input_C2_centShiftCombined_J4 = 0;
  double input_C2_centShiftCombined_J5 = 0;
  double input_C2_centShiftCombined_J6 = 0;

  double input_C1_centShiftCombined_J1 = 0;
  double input_C1_centShiftCombined_J2 = 0;
  double input_C1_centShiftCombined_J3 = 0;
  double input_C1_centShiftCombined_J4 = 0;
  double input_C1_centShiftCombined_J5 = 0;
  double input_C1_centShiftCombined_J6 = 0;

 
  // total
  double input_pp_total_J1 = 0;
  double input_pp_total_J2 = 0;
  double input_pp_total_J3 = 0;
  double input_pp_total_J4 = 0;
  double input_pp_total_J5 = 0;
  double input_pp_total_J6 = 0;

  double input_C4_total_J1 = 0;
  double input_C4_total_J2 = 0;
  double input_C4_total_J3 = 0;
  double input_C4_total_J4 = 0;
  double input_C4_total_J5 = 0;
  double input_C4_total_J6 = 0;

  double input_C3_total_J1 = 0;
  double input_C3_total_J2 = 0;
  double input_C3_total_J3 = 0;
  double input_C3_total_J4 = 0;
  double input_C3_total_J5 = 0;
  double input_C3_total_J6 = 0;

  double input_C2_total_J1 = 0;
  double input_C2_total_J2 = 0;
  double input_C2_total_J3 = 0;
  double input_C2_total_J4 = 0;
  double input_C2_total_J5 = 0;
  double input_C2_total_J6 = 0;

  double input_C1_total_J1 = 0;
  double input_C1_total_J2 = 0;
  double input_C1_total_J3 = 0;
  double input_C1_total_J4 = 0;
  double input_C1_total_J5 = 0;
  double input_C1_total_J6 = 0;



  // total uncertainty
  input_pp_cFrac_J1 = sys_cFraction_highest_J1;
  input_pp_cFrac_J2 = sys_cFraction_highest_J2;
  input_pp_cFrac_J3 = sys_cFraction_highest_J3;
  input_pp_cFrac_J4 = sys_cFraction_highest_J4;
  input_pp_cFrac_J5 = sys_cFraction_highest_J5;
  input_pp_cFrac_J6 = sys_cFraction_highest_J6;

  input_C4_cFrac_J1 = sys_cFraction_highest_J1;
  input_C4_cFrac_J2 = sys_cFraction_highest_J2;
  input_C4_cFrac_J3 = sys_cFraction_highest_J3;
  input_C4_cFrac_J4 = sys_cFraction_highest_J4;
  input_C4_cFrac_J5 = sys_cFraction_highest_J5;
  input_C4_cFrac_J6 = sys_cFraction_highest_J6;
  
  input_C3_cFrac_J1 = sys_cFraction_highest_J1;
  input_C3_cFrac_J2 = sys_cFraction_highest_J2;
  input_C3_cFrac_J3 = sys_cFraction_highest_J3;
  input_C3_cFrac_J4 = sys_cFraction_highest_J4;
  input_C3_cFrac_J5 = sys_cFraction_highest_J5;
  input_C3_cFrac_J6 = sys_cFraction_highest_J6;

  input_C2_cFrac_J1 = sys_cFraction_highest_J1;
  input_C2_cFrac_J2 = sys_cFraction_highest_J2;
  input_C2_cFrac_J3 = sys_cFraction_highest_J3;
  input_C2_cFrac_J4 = sys_cFraction_highest_J4;
  input_C2_cFrac_J5 = sys_cFraction_highest_J5;
  input_C2_cFrac_J6 = sys_cFraction_highest_J6;

  input_C1_cFrac_J1 = sys_cFraction_highest_J1;
  input_C1_cFrac_J2 = sys_cFraction_highest_J2;
  input_C1_cFrac_J3 = sys_cFraction_highest_J3;
  input_C1_cFrac_J4 = sys_cFraction_highest_J4;
  input_C1_cFrac_J5 = sys_cFraction_highest_J5;
  input_C1_cFrac_J6 = sys_cFraction_highest_J6;

  input_pp_lowerBound_J1 = sys_lowerBound_pp_mu12_J1;
  input_pp_lowerBound_J2 = sys_lowerBound_pp_mu12_J2;
  input_pp_lowerBound_J3 = sys_lowerBound_pp_mu12_J3;
  input_pp_lowerBound_J4 = sys_lowerBound_pp_mu12_J4;
  input_pp_lowerBound_J5 = sys_lowerBound_pp_mu12_J5;
  input_pp_lowerBound_J6 = sys_lowerBound_pp_mu12_J6;

  input_C4_lowerBound_J1 = sys_lowerBound_PbPb_mu12_C4_J1;
  input_C4_lowerBound_J2 = sys_lowerBound_PbPb_mu12_C4_J2;
  input_C4_lowerBound_J3 = sys_lowerBound_PbPb_mu12_C4_J3;
  input_C4_lowerBound_J4 = sys_lowerBound_PbPb_mu12_C4_J4;
  input_C4_lowerBound_J5 = sys_lowerBound_PbPb_mu12_C4_J5;
  input_C4_lowerBound_J6 = sys_lowerBound_PbPb_mu12_C4_J6;

  input_C3_lowerBound_J1 = sys_lowerBound_PbPb_mu12_C3_J1;
  input_C3_lowerBound_J2 = sys_lowerBound_PbPb_mu12_C3_J2;
  input_C3_lowerBound_J3 = sys_lowerBound_PbPb_mu12_C3_J3;
  input_C3_lowerBound_J4 = sys_lowerBound_PbPb_mu12_C3_J4;
  input_C3_lowerBound_J5 = sys_lowerBound_PbPb_mu12_C3_J5;
  input_C3_lowerBound_J6 = sys_lowerBound_PbPb_mu12_C3_J6;

  input_C2_lowerBound_J1 = sys_lowerBound_PbPb_mu12_C2_J1;
  input_C2_lowerBound_J2 = sys_lowerBound_PbPb_mu12_C2_J2;
  input_C2_lowerBound_J3 = sys_lowerBound_PbPb_mu12_C2_J3;
  input_C2_lowerBound_J4 = sys_lowerBound_PbPb_mu12_C2_J4;
  input_C2_lowerBound_J5 = sys_lowerBound_PbPb_mu12_C2_J5;
  input_C2_lowerBound_J6 = sys_lowerBound_PbPb_mu12_C2_J6;

  input_C1_lowerBound_J1 = sys_lowerBound_PbPb_mu12_C1_J1;
  input_C1_lowerBound_J2 = sys_lowerBound_PbPb_mu12_C1_J2;
  input_C1_lowerBound_J3 = sys_lowerBound_PbPb_mu12_C1_J3;
  input_C1_lowerBound_J4 = sys_lowerBound_PbPb_mu12_C1_J4;
  input_C1_lowerBound_J5 = sys_lowerBound_PbPb_mu12_C1_J5;
  input_C1_lowerBound_J6 = sys_lowerBound_PbPb_mu12_C1_J6;  

  input_pp_JERsmear_J1 = sys_JERsmear_pp_mu12_J1;
  input_pp_JERsmear_J2 = sys_JERsmear_pp_mu12_J2;
  input_pp_JERsmear_J3 = sys_JERsmear_pp_mu12_J3;
  input_pp_JERsmear_J4 = sys_JERsmear_pp_mu12_J4;
  input_pp_JERsmear_J5 = sys_JERsmear_pp_mu12_J5;
  input_pp_JERsmear_J6 = sys_JERsmear_pp_mu12_J6;

  input_C4_JERsmear_J1 = sys_JERsmear_PbPb_mu12_C4_J1;
  input_C4_JERsmear_J2 = sys_JERsmear_PbPb_mu12_C4_J2;
  input_C4_JERsmear_J3 = sys_JERsmear_PbPb_mu12_C4_J3;
  input_C4_JERsmear_J4 = sys_JERsmear_PbPb_mu12_C4_J4;
  input_C4_JERsmear_J5 = sys_JERsmear_PbPb_mu12_C4_J5;
  input_C4_JERsmear_J6 = sys_JERsmear_PbPb_mu12_C4_J6;

  input_C3_JERsmear_J1 = sys_JERsmear_PbPb_mu12_C3_J1;
  input_C3_JERsmear_J2 = sys_JERsmear_PbPb_mu12_C3_J2;
  input_C3_JERsmear_J3 = sys_JERsmear_PbPb_mu12_C3_J3;
  input_C3_JERsmear_J4 = sys_JERsmear_PbPb_mu12_C3_J4;
  input_C3_JERsmear_J5 = sys_JERsmear_PbPb_mu12_C3_J5;
  input_C3_JERsmear_J6 = sys_JERsmear_PbPb_mu12_C3_J6;

  input_C2_JERsmear_J1 = sys_JERsmear_PbPb_mu12_C2_J1;
  input_C2_JERsmear_J2 = sys_JERsmear_PbPb_mu12_C2_J2;
  input_C2_JERsmear_J3 = sys_JERsmear_PbPb_mu12_C2_J3;
  input_C2_JERsmear_J4 = sys_JERsmear_PbPb_mu12_C2_J4;
  input_C2_JERsmear_J5 = sys_JERsmear_PbPb_mu12_C2_J5;
  input_C2_JERsmear_J6 = sys_JERsmear_PbPb_mu12_C2_J6;

  input_C1_JERsmear_J1 = sys_JERsmear_PbPb_mu12_C1_J1;
  input_C1_JERsmear_J2 = sys_JERsmear_PbPb_mu12_C1_J2;
  input_C1_JERsmear_J3 = sys_JERsmear_PbPb_mu12_C1_J3;
  input_C1_JERsmear_J4 = sys_JERsmear_PbPb_mu12_C1_J4;
  input_C1_JERsmear_J5 = sys_JERsmear_PbPb_mu12_C1_J5;
  input_C1_JERsmear_J6 = sys_JERsmear_PbPb_mu12_C1_J6;
    
  input_pp_bGS_J1 = sys_bGS_highest_J1;
  input_pp_bGS_J2 = sys_bGS_highest_J2;
  input_pp_bGS_J3 = sys_bGS_highest_J3;
  input_pp_bGS_J4 = sys_bGS_highest_J4;
  input_pp_bGS_J5 = sys_bGS_highest_J5;
  input_pp_bGS_J6 = sys_bGS_highest_J6;

  input_C4_bGS_J1 = sys_bGS_highest_J1;
  input_C4_bGS_J2 = sys_bGS_highest_J2;
  input_C4_bGS_J3 = sys_bGS_highest_J3;
  input_C4_bGS_J4 = sys_bGS_highest_J4;
  input_C4_bGS_J5 = sys_bGS_highest_J5;
  input_C4_bGS_J6 = sys_bGS_highest_J6;

  input_C3_bGS_J1 = sys_bGS_highest_J1;
  input_C3_bGS_J2 = sys_bGS_highest_J2;
  input_C3_bGS_J3 = sys_bGS_highest_J3;
  input_C3_bGS_J4 = sys_bGS_highest_J4;
  input_C3_bGS_J5 = sys_bGS_highest_J5;
  input_C3_bGS_J6 = sys_bGS_highest_J6;

  input_C2_bGS_J1 = sys_bGS_highest_J1;
  input_C2_bGS_J2 = sys_bGS_highest_J2;
  input_C2_bGS_J3 = sys_bGS_highest_J3;
  input_C2_bGS_J4 = sys_bGS_highest_J4;
  input_C2_bGS_J5 = sys_bGS_highest_J5;
  input_C2_bGS_J6 = sys_bGS_highest_J6;

  input_C1_bGS_J1 = sys_bGS_highest_J1;
  input_C1_bGS_J2 = sys_bGS_highest_J2;
  input_C1_bGS_J3 = sys_bGS_highest_J3;
  input_C1_bGS_J4 = sys_bGS_highest_J4;
  input_C1_bGS_J5 = sys_bGS_highest_J5;
  input_C1_bGS_J6 = sys_bGS_highest_J6;

  input_pp_JEUShiftUp_J1 = sys_JEUShiftUp_pp_mu12_J1;
  input_pp_JEUShiftUp_J2 = sys_JEUShiftUp_pp_mu12_J2;
  input_pp_JEUShiftUp_J3 = sys_JEUShiftUp_pp_mu12_J3;
  input_pp_JEUShiftUp_J4 = sys_JEUShiftUp_pp_mu12_J4;
  input_pp_JEUShiftUp_J5 = sys_JEUShiftUp_pp_mu12_J5;
  input_pp_JEUShiftUp_J6 = sys_JEUShiftUp_pp_mu12_J6;

  input_C4_JEUShiftUp_J1 = sys_JEUShiftUp_PbPb_mu12_C4_J1;
  input_C4_JEUShiftUp_J2 = sys_JEUShiftUp_PbPb_mu12_C4_J2;
  input_C4_JEUShiftUp_J3 = sys_JEUShiftUp_PbPb_mu12_C4_J3;
  input_C4_JEUShiftUp_J4 = sys_JEUShiftUp_PbPb_mu12_C4_J4;
  input_C4_JEUShiftUp_J5 = sys_JEUShiftUp_PbPb_mu12_C4_J5;
  input_C4_JEUShiftUp_J6 = sys_JEUShiftUp_PbPb_mu12_C4_J6;

  input_C3_JEUShiftUp_J1 = sys_JEUShiftUp_PbPb_mu12_C3_J1;
  input_C3_JEUShiftUp_J2 = sys_JEUShiftUp_PbPb_mu12_C3_J2;
  input_C3_JEUShiftUp_J3 = sys_JEUShiftUp_PbPb_mu12_C3_J3;
  input_C3_JEUShiftUp_J4 = sys_JEUShiftUp_PbPb_mu12_C3_J4;
  input_C3_JEUShiftUp_J5 = sys_JEUShiftUp_PbPb_mu12_C3_J5;
  input_C3_JEUShiftUp_J6 = sys_JEUShiftUp_PbPb_mu12_C3_J6;

  input_C2_JEUShiftUp_J1 = sys_JEUShiftUp_PbPb_mu12_C2_J1;
  input_C2_JEUShiftUp_J2 = sys_JEUShiftUp_PbPb_mu12_C2_J2;
  input_C2_JEUShiftUp_J3 = sys_JEUShiftUp_PbPb_mu12_C2_J3;
  input_C2_JEUShiftUp_J4 = sys_JEUShiftUp_PbPb_mu12_C2_J4;
  input_C2_JEUShiftUp_J5 = sys_JEUShiftUp_PbPb_mu12_C2_J5;
  input_C2_JEUShiftUp_J6 = sys_JEUShiftUp_PbPb_mu12_C2_J6;

  input_C1_JEUShiftUp_J1 = sys_JEUShiftUp_PbPb_mu12_C1_J1;
  input_C1_JEUShiftUp_J2 = sys_JEUShiftUp_PbPb_mu12_C1_J2;
  input_C1_JEUShiftUp_J3 = sys_JEUShiftUp_PbPb_mu12_C1_J3;
  input_C1_JEUShiftUp_J4 = sys_JEUShiftUp_PbPb_mu12_C1_J4;
  input_C1_JEUShiftUp_J5 = sys_JEUShiftUp_PbPb_mu12_C1_J5;
  input_C1_JEUShiftUp_J6 = sys_JEUShiftUp_PbPb_mu12_C1_J6;

  input_pp_JEUShiftDown_J1 = sys_JEUShiftDown_pp_mu12_J1;
  input_pp_JEUShiftDown_J2 = sys_JEUShiftDown_pp_mu12_J2;
  input_pp_JEUShiftDown_J3 = sys_JEUShiftDown_pp_mu12_J3;
  input_pp_JEUShiftDown_J4 = sys_JEUShiftDown_pp_mu12_J4;
  input_pp_JEUShiftDown_J5 = sys_JEUShiftDown_pp_mu12_J5;
  input_pp_JEUShiftDown_J6 = sys_JEUShiftDown_pp_mu12_J6;

  input_C4_JEUShiftDown_J1 = sys_JEUShiftDown_PbPb_mu12_C4_J1;
  input_C4_JEUShiftDown_J2 = sys_JEUShiftDown_PbPb_mu12_C4_J2;
  input_C4_JEUShiftDown_J3 = sys_JEUShiftDown_PbPb_mu12_C4_J3;
  input_C4_JEUShiftDown_J4 = sys_JEUShiftDown_PbPb_mu12_C4_J4;
  input_C4_JEUShiftDown_J5 = sys_JEUShiftDown_PbPb_mu12_C4_J5;
  input_C4_JEUShiftDown_J6 = sys_JEUShiftDown_PbPb_mu12_C4_J6;

  input_C3_JEUShiftDown_J1 = sys_JEUShiftDown_PbPb_mu12_C3_J1;
  input_C3_JEUShiftDown_J2 = sys_JEUShiftDown_PbPb_mu12_C3_J2;
  input_C3_JEUShiftDown_J3 = sys_JEUShiftDown_PbPb_mu12_C3_J3;
  input_C3_JEUShiftDown_J4 = sys_JEUShiftDown_PbPb_mu12_C3_J4;
  input_C3_JEUShiftDown_J5 = sys_JEUShiftDown_PbPb_mu12_C3_J5;
  input_C3_JEUShiftDown_J6 = sys_JEUShiftDown_PbPb_mu12_C3_J6;

  input_C2_JEUShiftDown_J1 = sys_JEUShiftDown_PbPb_mu12_C2_J1;
  input_C2_JEUShiftDown_J2 = sys_JEUShiftDown_PbPb_mu12_C2_J2;
  input_C2_JEUShiftDown_J3 = sys_JEUShiftDown_PbPb_mu12_C2_J3;
  input_C2_JEUShiftDown_J4 = sys_JEUShiftDown_PbPb_mu12_C2_J4;
  input_C2_JEUShiftDown_J5 = sys_JEUShiftDown_PbPb_mu12_C2_J5;
  input_C2_JEUShiftDown_J6 = sys_JEUShiftDown_PbPb_mu12_C2_J6;

  input_C1_JEUShiftDown_J1 = sys_JEUShiftDown_PbPb_mu12_C1_J1;
  input_C1_JEUShiftDown_J2 = sys_JEUShiftDown_PbPb_mu12_C1_J2;
  input_C1_JEUShiftDown_J3 = sys_JEUShiftDown_PbPb_mu12_C1_J3;
  input_C1_JEUShiftDown_J4 = sys_JEUShiftDown_PbPb_mu12_C1_J4;
  input_C1_JEUShiftDown_J5 = sys_JEUShiftDown_PbPb_mu12_C1_J5;
  input_C1_JEUShiftDown_J6 = sys_JEUShiftDown_PbPb_mu12_C1_J6;

  input_pp_JEUShiftCombined_J1 = sys_JEUShiftCombined_pp_mu12_J1;
  input_pp_JEUShiftCombined_J2 = sys_JEUShiftCombined_pp_mu12_J2;
  input_pp_JEUShiftCombined_J3 = sys_JEUShiftCombined_pp_mu12_J3;
  input_pp_JEUShiftCombined_J4 = sys_JEUShiftCombined_pp_mu12_J4;
  input_pp_JEUShiftCombined_J5 = sys_JEUShiftCombined_pp_mu12_J5;
  input_pp_JEUShiftCombined_J6 = sys_JEUShiftCombined_pp_mu12_J6;

  input_C4_JEUShiftCombined_J1 = sys_JEUShiftCombined_PbPb_mu12_C4_J1;
  input_C4_JEUShiftCombined_J2 = sys_JEUShiftCombined_PbPb_mu12_C4_J2;
  input_C4_JEUShiftCombined_J3 = sys_JEUShiftCombined_PbPb_mu12_C4_J3;
  input_C4_JEUShiftCombined_J4 = sys_JEUShiftCombined_PbPb_mu12_C4_J4;
  input_C4_JEUShiftCombined_J5 = sys_JEUShiftCombined_PbPb_mu12_C4_J5;
  input_C4_JEUShiftCombined_J6 = sys_JEUShiftCombined_PbPb_mu12_C4_J6;

  input_C3_JEUShiftCombined_J1 = sys_JEUShiftCombined_PbPb_mu12_C3_J1;
  input_C3_JEUShiftCombined_J2 = sys_JEUShiftCombined_PbPb_mu12_C3_J2;
  input_C3_JEUShiftCombined_J3 = sys_JEUShiftCombined_PbPb_mu12_C3_J3;
  input_C3_JEUShiftCombined_J4 = sys_JEUShiftCombined_PbPb_mu12_C3_J4;
  input_C3_JEUShiftCombined_J5 = sys_JEUShiftCombined_PbPb_mu12_C3_J5;
  input_C3_JEUShiftCombined_J6 = sys_JEUShiftCombined_PbPb_mu12_C3_J6;

  input_C2_JEUShiftCombined_J1 = sys_JEUShiftCombined_PbPb_mu12_C2_J1;
  input_C2_JEUShiftCombined_J2 = sys_JEUShiftCombined_PbPb_mu12_C2_J2;
  input_C2_JEUShiftCombined_J3 = sys_JEUShiftCombined_PbPb_mu12_C2_J3;
  input_C2_JEUShiftCombined_J4 = sys_JEUShiftCombined_PbPb_mu12_C2_J4;
  input_C2_JEUShiftCombined_J5 = sys_JEUShiftCombined_PbPb_mu12_C2_J5;
  input_C2_JEUShiftCombined_J6 = sys_JEUShiftCombined_PbPb_mu12_C2_J6;

  input_C1_JEUShiftCombined_J1 = sys_JEUShiftCombined_PbPb_mu12_C1_J1;
  input_C1_JEUShiftCombined_J2 = sys_JEUShiftCombined_PbPb_mu12_C1_J2;
  input_C1_JEUShiftCombined_J3 = sys_JEUShiftCombined_PbPb_mu12_C1_J3;
  input_C1_JEUShiftCombined_J4 = sys_JEUShiftCombined_PbPb_mu12_C1_J4;
  input_C1_JEUShiftCombined_J5 = sys_JEUShiftCombined_PbPb_mu12_C1_J5;
  input_C1_JEUShiftCombined_J6 = sys_JEUShiftCombined_PbPb_mu12_C1_J6;

  input_pp_centShiftUp_J1 = sys_centShiftUp_pp_mu12_J1;
  input_pp_centShiftUp_J2 = sys_centShiftUp_pp_mu12_J2;
  input_pp_centShiftUp_J3 = sys_centShiftUp_pp_mu12_J3;
  input_pp_centShiftUp_J4 = sys_centShiftUp_pp_mu12_J4;
  input_pp_centShiftUp_J5 = sys_centShiftUp_pp_mu12_J5;
  input_pp_centShiftUp_J6 = sys_centShiftUp_pp_mu12_J6;

  input_C4_centShiftUp_J1 = sys_centShiftUp_PbPb_mu12_C4_J1;
  input_C4_centShiftUp_J2 = sys_centShiftUp_PbPb_mu12_C4_J2;
  input_C4_centShiftUp_J3 = sys_centShiftUp_PbPb_mu12_C4_J3;
  input_C4_centShiftUp_J4 = sys_centShiftUp_PbPb_mu12_C4_J4;
  input_C4_centShiftUp_J5 = sys_centShiftUp_PbPb_mu12_C4_J5;
  input_C4_centShiftUp_J6 = sys_centShiftUp_PbPb_mu12_C4_J6;

  input_C3_centShiftUp_J1 = sys_centShiftUp_PbPb_mu12_C3_J1;
  input_C3_centShiftUp_J2 = sys_centShiftUp_PbPb_mu12_C3_J2;
  input_C3_centShiftUp_J3 = sys_centShiftUp_PbPb_mu12_C3_J3;
  input_C3_centShiftUp_J4 = sys_centShiftUp_PbPb_mu12_C3_J4;
  input_C3_centShiftUp_J5 = sys_centShiftUp_PbPb_mu12_C3_J5;
  input_C3_centShiftUp_J6 = sys_centShiftUp_PbPb_mu12_C3_J6;

  input_C2_centShiftUp_J1 = sys_centShiftUp_PbPb_mu12_C2_J1;
  input_C2_centShiftUp_J2 = sys_centShiftUp_PbPb_mu12_C2_J2;
  input_C2_centShiftUp_J3 = sys_centShiftUp_PbPb_mu12_C2_J3;
  input_C2_centShiftUp_J4 = sys_centShiftUp_PbPb_mu12_C2_J4;
  input_C2_centShiftUp_J5 = sys_centShiftUp_PbPb_mu12_C2_J5;
  input_C2_centShiftUp_J6 = sys_centShiftUp_PbPb_mu12_C2_J6;

  input_C1_centShiftUp_J1 = sys_centShiftUp_PbPb_mu12_C1_J1;
  input_C1_centShiftUp_J2 = sys_centShiftUp_PbPb_mu12_C1_J2;
  input_C1_centShiftUp_J3 = sys_centShiftUp_PbPb_mu12_C1_J3;
  input_C1_centShiftUp_J4 = sys_centShiftUp_PbPb_mu12_C1_J4;
  input_C1_centShiftUp_J5 = sys_centShiftUp_PbPb_mu12_C1_J5;
  input_C1_centShiftUp_J6 = sys_centShiftUp_PbPb_mu12_C1_J6;

  input_pp_centShiftDown_J1 = sys_centShiftDown_pp_mu12_J1;
  input_pp_centShiftDown_J2 = sys_centShiftDown_pp_mu12_J2;
  input_pp_centShiftDown_J3 = sys_centShiftDown_pp_mu12_J3;
  input_pp_centShiftDown_J4 = sys_centShiftDown_pp_mu12_J4;
  input_pp_centShiftDown_J5 = sys_centShiftDown_pp_mu12_J5;
  input_pp_centShiftDown_J6 = sys_centShiftDown_pp_mu12_J6;

  input_C4_centShiftDown_J1 = sys_centShiftDown_PbPb_mu12_C4_J1;
  input_C4_centShiftDown_J2 = sys_centShiftDown_PbPb_mu12_C4_J2;
  input_C4_centShiftDown_J3 = sys_centShiftDown_PbPb_mu12_C4_J3;
  input_C4_centShiftDown_J4 = sys_centShiftDown_PbPb_mu12_C4_J4;
  input_C4_centShiftDown_J5 = sys_centShiftDown_PbPb_mu12_C4_J5;
  input_C4_centShiftDown_J6 = sys_centShiftDown_PbPb_mu12_C4_J6;

  input_C3_centShiftDown_J1 = sys_centShiftDown_PbPb_mu12_C3_J1;
  input_C3_centShiftDown_J2 = sys_centShiftDown_PbPb_mu12_C3_J2;
  input_C3_centShiftDown_J3 = sys_centShiftDown_PbPb_mu12_C3_J3;
  input_C3_centShiftDown_J4 = sys_centShiftDown_PbPb_mu12_C3_J4;
  input_C3_centShiftDown_J5 = sys_centShiftDown_PbPb_mu12_C3_J5;
  input_C3_centShiftDown_J6 = sys_centShiftDown_PbPb_mu12_C3_J6;

  input_C2_centShiftDown_J1 = sys_centShiftDown_PbPb_mu12_C2_J1;
  input_C2_centShiftDown_J2 = sys_centShiftDown_PbPb_mu12_C2_J2;
  input_C2_centShiftDown_J3 = sys_centShiftDown_PbPb_mu12_C2_J3;
  input_C2_centShiftDown_J4 = sys_centShiftDown_PbPb_mu12_C2_J4;
  input_C2_centShiftDown_J5 = sys_centShiftDown_PbPb_mu12_C2_J5;
  input_C2_centShiftDown_J6 = sys_centShiftDown_PbPb_mu12_C2_J6;

  input_C1_centShiftDown_J1 = sys_centShiftDown_PbPb_mu12_C1_J1;
  input_C1_centShiftDown_J2 = sys_centShiftDown_PbPb_mu12_C1_J2;
  input_C1_centShiftDown_J3 = sys_centShiftDown_PbPb_mu12_C1_J3;
  input_C1_centShiftDown_J4 = sys_centShiftDown_PbPb_mu12_C1_J4;
  input_C1_centShiftDown_J5 = sys_centShiftDown_PbPb_mu12_C1_J5;
  input_C1_centShiftDown_J6 = sys_centShiftDown_PbPb_mu12_C1_J6;

  input_pp_centShiftCombined_J1 = sys_centShiftCombined_pp_mu12_J1;
  input_pp_centShiftCombined_J2 = sys_centShiftCombined_pp_mu12_J2;
  input_pp_centShiftCombined_J3 = sys_centShiftCombined_pp_mu12_J3;
  input_pp_centShiftCombined_J4 = sys_centShiftCombined_pp_mu12_J4;
  input_pp_centShiftCombined_J5 = sys_centShiftCombined_pp_mu12_J5;
  input_pp_centShiftCombined_J6 = sys_centShiftCombined_pp_mu12_J6;

  input_C4_centShiftCombined_J1 = sys_centShiftCombined_PbPb_mu12_C4_J1;
  input_C4_centShiftCombined_J2 = sys_centShiftCombined_PbPb_mu12_C4_J2;
  input_C4_centShiftCombined_J3 = sys_centShiftCombined_PbPb_mu12_C4_J3;
  input_C4_centShiftCombined_J4 = sys_centShiftCombined_PbPb_mu12_C4_J4;
  input_C4_centShiftCombined_J5 = sys_centShiftCombined_PbPb_mu12_C4_J5;
  input_C4_centShiftCombined_J6 = sys_centShiftCombined_PbPb_mu12_C4_J6;

  input_C3_centShiftCombined_J1 = sys_centShiftCombined_PbPb_mu12_C3_J1;
  input_C3_centShiftCombined_J2 = sys_centShiftCombined_PbPb_mu12_C3_J2;
  input_C3_centShiftCombined_J3 = sys_centShiftCombined_PbPb_mu12_C3_J3;
  input_C3_centShiftCombined_J4 = sys_centShiftCombined_PbPb_mu12_C3_J4;
  input_C3_centShiftCombined_J5 = sys_centShiftCombined_PbPb_mu12_C3_J5;
  input_C3_centShiftCombined_J6 = sys_centShiftCombined_PbPb_mu12_C3_J6;

  input_C2_centShiftCombined_J1 = sys_centShiftCombined_PbPb_mu12_C2_J1;
  input_C2_centShiftCombined_J2 = sys_centShiftCombined_PbPb_mu12_C2_J2;
  input_C2_centShiftCombined_J3 = sys_centShiftCombined_PbPb_mu12_C2_J3;
  input_C2_centShiftCombined_J4 = sys_centShiftCombined_PbPb_mu12_C2_J4;
  input_C2_centShiftCombined_J5 = sys_centShiftCombined_PbPb_mu12_C2_J5;
  input_C2_centShiftCombined_J6 = sys_centShiftCombined_PbPb_mu12_C2_J6;

  input_C1_centShiftCombined_J1 = sys_centShiftCombined_PbPb_mu12_C1_J1;
  input_C1_centShiftCombined_J2 = sys_centShiftCombined_PbPb_mu12_C1_J2;
  input_C1_centShiftCombined_J3 = sys_centShiftCombined_PbPb_mu12_C1_J3;
  input_C1_centShiftCombined_J4 = sys_centShiftCombined_PbPb_mu12_C1_J4;
  input_C1_centShiftCombined_J5 = sys_centShiftCombined_PbPb_mu12_C1_J5;
  input_C1_centShiftCombined_J6 = sys_centShiftCombined_PbPb_mu12_C1_J6;


  

  input_pp_total_J1 = sys_total_pp_mu12_J1;
  input_pp_total_J2 = sys_total_pp_mu12_J2;
  input_pp_total_J3 = sys_total_pp_mu12_J3;
  input_pp_total_J4 = sys_total_pp_mu12_J4;
  input_pp_total_J5 = sys_total_pp_mu12_J5;
  input_pp_total_J6 = sys_total_pp_mu12_J6;

  input_C4_total_J1 = sys_total_PbPb_mu12_C4_J1;
  input_C4_total_J2 = sys_total_PbPb_mu12_C4_J2;
  input_C4_total_J3 = sys_total_PbPb_mu12_C4_J3;
  input_C4_total_J4 = sys_total_PbPb_mu12_C4_J4;
  input_C4_total_J5 = sys_total_PbPb_mu12_C4_J5;
  input_C4_total_J6 = sys_total_PbPb_mu12_C4_J6;

  input_C3_total_J1 = sys_total_PbPb_mu12_C3_J1;
  input_C3_total_J2 = sys_total_PbPb_mu12_C3_J2;
  input_C3_total_J3 = sys_total_PbPb_mu12_C3_J3;
  input_C3_total_J4 = sys_total_PbPb_mu12_C3_J4;
  input_C3_total_J5 = sys_total_PbPb_mu12_C3_J5;
  input_C3_total_J6 = sys_total_PbPb_mu12_C3_J6;

  input_C2_total_J1 = sys_total_PbPb_mu12_C2_J1;
  input_C2_total_J2 = sys_total_PbPb_mu12_C2_J2;
  input_C2_total_J3 = sys_total_PbPb_mu12_C2_J3;
  input_C2_total_J4 = sys_total_PbPb_mu12_C2_J4;
  input_C2_total_J5 = sys_total_PbPb_mu12_C2_J5;
  input_C2_total_J6 = sys_total_PbPb_mu12_C2_J6;

  input_C1_total_J1 = sys_total_PbPb_mu12_C1_J1;
  input_C1_total_J2 = sys_total_PbPb_mu12_C1_J2;
  input_C1_total_J3 = sys_total_PbPb_mu12_C1_J3;
  input_C1_total_J4 = sys_total_PbPb_mu12_C1_J4;
  input_C1_total_J5 = sys_total_PbPb_mu12_C1_J5;
  input_C1_total_J6 = sys_total_PbPb_mu12_C1_J6;

  // set to zero for drawing the systematics one-by-one
  // input_pp_total_J1 = 0;
  // input_pp_total_J2 = 0;
  // input_pp_total_J3 = 0;
  // input_pp_total_J4 = 0;
  // input_pp_total_J5 = 0;
  // input_pp_total_J6 = 0;

  // input_C3_total_J1 = 0;
  // input_C3_total_J2 = 0;
  // input_C3_total_J3 = 0;
  // input_C3_total_J4 = 0;
  // input_C3_total_J5 = 0;
  // input_C3_total_J6 = 0;

  // input_C2_total_J1 = 0;
  // input_C2_total_J2 = 0;
  // input_C2_total_J3 = 0;
  // input_C2_total_J4 = 0;
  // input_C2_total_J5 = 0;
  // input_C2_total_J6 = 0;

  // input_C1_total_J1 = 0;
  // input_C1_total_J2 = 0;
  // input_C1_total_J3 = 0;
  // input_C1_total_J4 = 0;
  // input_C1_total_J5 = 0;
  // input_C1_total_J6 = 0;


  
  const int N_jetPtAxisEdges = 7;
  double jetPtAxisEdges[N_jetPtAxisEdges] = {80,90,100,120,150,200,300};

  int line_width = 4;
  double marker_size = 1.0;
  
  
  // pp -------------------------------------------
  TH1D *h_pp_cFraction = new TH1D("h_pp_cFraction","h_pp_cFraction",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_pp_lowerBound = new TH1D("h_pp_lowerBound","h_pp_lowerBound",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_pp_JERsmear = new TH1D("h_pp_JERsmear","h_pp_JERsmear",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_pp_bGS = new TH1D("h_pp_bGS","h_pp_bGS",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_pp_JEUShiftCombined = new TH1D("h_pp_JEUShiftCombined","h_pp_JEUShiftCombined",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_pp_JEUShiftUp = new TH1D("h_pp_JEUShiftUp","h_pp_JEUShiftUp",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_pp_JEUShiftDown = new TH1D("h_pp_JEUShiftDown","h_pp_JEUShiftDown",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_pp_centShiftCombined = new TH1D("h_pp_centShiftCombined","h_pp_centShiftCombined",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_pp_centShiftUp = new TH1D("h_pp_centShiftUp","h_pp_centShiftUp",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_pp_centShiftDown = new TH1D("h_pp_centShiftDown","h_pp_centShiftDown",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_pp_residual = new TH1D("h_pp_residual","h_pp_residual",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_pp_total = new TH1D("h_pp_total","h_pp_total",N_jetPtAxisEdges-1,jetPtAxisEdges);
  
  h_pp_cFraction->SetBinContent(1,input_pp_cFrac_J1);
  h_pp_cFraction->SetBinContent(2,input_pp_cFrac_J2);
  h_pp_cFraction->SetBinContent(3,input_pp_cFrac_J3);
  h_pp_cFraction->SetBinContent(4,input_pp_cFrac_J4);
  h_pp_cFraction->SetBinContent(5,input_pp_cFrac_J5);
  h_pp_cFraction->SetBinContent(6,input_pp_cFrac_J6);

  h_pp_lowerBound->SetBinContent(1,input_pp_lowerBound_J1);
  h_pp_lowerBound->SetBinContent(2,input_pp_lowerBound_J2);
  h_pp_lowerBound->SetBinContent(3,input_pp_lowerBound_J3);
  h_pp_lowerBound->SetBinContent(4,input_pp_lowerBound_J4);
  h_pp_lowerBound->SetBinContent(5,input_pp_lowerBound_J5);
  h_pp_lowerBound->SetBinContent(6,input_pp_lowerBound_J6);

  h_pp_JERsmear->SetBinContent(1,input_pp_JERsmear_J1);
  h_pp_JERsmear->SetBinContent(2,input_pp_JERsmear_J2);
  h_pp_JERsmear->SetBinContent(3,input_pp_JERsmear_J3);
  h_pp_JERsmear->SetBinContent(4,input_pp_JERsmear_J4);
  h_pp_JERsmear->SetBinContent(5,input_pp_JERsmear_J5);
  h_pp_JERsmear->SetBinContent(6,input_pp_JERsmear_J6);

  h_pp_bGS->SetBinContent(1,input_pp_bGS_J1);
  h_pp_bGS->SetBinContent(2,input_pp_bGS_J2);
  h_pp_bGS->SetBinContent(3,input_pp_bGS_J3);
  h_pp_bGS->SetBinContent(4,input_pp_bGS_J4);
  h_pp_bGS->SetBinContent(5,input_pp_bGS_J5);
  h_pp_bGS->SetBinContent(6,input_pp_bGS_J6);
  
  h_pp_JEUShiftCombined->SetBinContent(1,input_pp_JEUShiftCombined_J1);
  h_pp_JEUShiftCombined->SetBinContent(2,input_pp_JEUShiftCombined_J2);
  h_pp_JEUShiftCombined->SetBinContent(3,input_pp_JEUShiftCombined_J3);
  h_pp_JEUShiftCombined->SetBinContent(4,input_pp_JEUShiftCombined_J4);
  h_pp_JEUShiftCombined->SetBinContent(5,input_pp_JEUShiftCombined_J5);
  h_pp_JEUShiftCombined->SetBinContent(6,input_pp_JEUShiftCombined_J6);

  h_pp_JEUShiftUp->SetBinContent(1,input_pp_JEUShiftUp_J1);
  h_pp_JEUShiftUp->SetBinContent(2,input_pp_JEUShiftUp_J2);
  h_pp_JEUShiftUp->SetBinContent(3,input_pp_JEUShiftUp_J3);
  h_pp_JEUShiftUp->SetBinContent(4,input_pp_JEUShiftUp_J4);
  h_pp_JEUShiftUp->SetBinContent(5,input_pp_JEUShiftUp_J5);
  h_pp_JEUShiftUp->SetBinContent(6,input_pp_JEUShiftUp_J6);

  h_pp_JEUShiftDown->SetBinContent(1,input_pp_JEUShiftDown_J1);
  h_pp_JEUShiftDown->SetBinContent(2,input_pp_JEUShiftDown_J2);
  h_pp_JEUShiftDown->SetBinContent(3,input_pp_JEUShiftDown_J3);
  h_pp_JEUShiftDown->SetBinContent(4,input_pp_JEUShiftDown_J4);
  h_pp_JEUShiftDown->SetBinContent(5,input_pp_JEUShiftDown_J5);
  h_pp_JEUShiftDown->SetBinContent(6,input_pp_JEUShiftDown_J6);

  h_pp_centShiftCombined->SetBinContent(1,input_pp_centShiftCombined_J1);
  h_pp_centShiftCombined->SetBinContent(2,input_pp_centShiftCombined_J2);
  h_pp_centShiftCombined->SetBinContent(3,input_pp_centShiftCombined_J3);
  h_pp_centShiftCombined->SetBinContent(4,input_pp_centShiftCombined_J4);
  h_pp_centShiftCombined->SetBinContent(5,input_pp_centShiftCombined_J5);
  h_pp_centShiftCombined->SetBinContent(6,input_pp_centShiftCombined_J6);

  h_pp_centShiftUp->SetBinContent(1,input_pp_centShiftUp_J1);
  h_pp_centShiftUp->SetBinContent(2,input_pp_centShiftUp_J2);
  h_pp_centShiftUp->SetBinContent(3,input_pp_centShiftUp_J3);
  h_pp_centShiftUp->SetBinContent(4,input_pp_centShiftUp_J4);
  h_pp_centShiftUp->SetBinContent(5,input_pp_centShiftUp_J5);
  h_pp_centShiftUp->SetBinContent(6,input_pp_centShiftUp_J6);

  h_pp_centShiftDown->SetBinContent(1,input_pp_centShiftDown_J1);
  h_pp_centShiftDown->SetBinContent(2,input_pp_centShiftDown_J2);
  h_pp_centShiftDown->SetBinContent(3,input_pp_centShiftDown_J3);
  h_pp_centShiftDown->SetBinContent(4,input_pp_centShiftDown_J4);
  h_pp_centShiftDown->SetBinContent(5,input_pp_centShiftDown_J5);
  h_pp_centShiftDown->SetBinContent(6,input_pp_centShiftDown_J6);

  h_pp_total->SetBinContent(1,input_pp_total_J1);
  h_pp_total->SetBinContent(2,input_pp_total_J2);
  h_pp_total->SetBinContent(3,input_pp_total_J3);
  h_pp_total->SetBinContent(4,input_pp_total_J4);
  h_pp_total->SetBinContent(5,input_pp_total_J5);
  h_pp_total->SetBinContent(6,input_pp_total_J6);

  // set style
  h_pp_cFraction->SetMarkerColor(kBlue-4);
  h_pp_lowerBound->SetMarkerColor(kRed-4);
  h_pp_JERsmear->SetMarkerColor(kOrange);
  h_pp_bGS->SetMarkerColor(kBlue-9);
  h_pp_JEUShiftCombined->SetMarkerColor(kGreen-8);
  h_pp_JEUShiftUp->SetMarkerColor(kGreen-8);
  h_pp_JEUShiftDown->SetMarkerColor(kPink+9);
  h_pp_centShiftCombined->SetMarkerColor(kGreen+2);
  h_pp_centShiftUp->SetMarkerColor(kGreen+2);
  h_pp_centShiftDown->SetMarkerColor(kMagenta);
  h_pp_total->SetMarkerColor(kBlack);

  h_pp_cFraction->SetLineColor(kBlue-4);
  h_pp_lowerBound->SetLineColor(kRed-4);
  h_pp_JERsmear->SetLineColor(kOrange);
  h_pp_bGS->SetLineColor(kBlue-9);
  h_pp_JEUShiftCombined->SetLineColor(kGreen-8);
  h_pp_JEUShiftUp->SetLineColor(kGreen-8);
  h_pp_JEUShiftDown->SetLineColor(kPink+9);
  h_pp_centShiftCombined->SetLineColor(kGreen+2);
  h_pp_centShiftUp->SetLineColor(kGreen+2);
  h_pp_centShiftDown->SetLineColor(kMagenta);
  h_pp_total->SetLineColor(kBlack);

  h_pp_cFraction->SetMarkerStyle(25);
  h_pp_lowerBound->SetMarkerStyle(26);
  h_pp_JERsmear->SetMarkerStyle(30);
  h_pp_bGS->SetMarkerStyle(32);
  h_pp_JEUShiftCombined->SetMarkerStyle(33);
  h_pp_JEUShiftUp->SetMarkerStyle(33);
  h_pp_JEUShiftDown->SetMarkerStyle(34);
  h_pp_centShiftCombined->SetMarkerStyle(27);
  h_pp_centShiftUp->SetMarkerStyle(27);
  h_pp_centShiftDown->SetMarkerStyle(28);
  h_pp_total->SetMarkerStyle(24);

  h_pp_cFraction->SetMarkerSize(marker_size);
  h_pp_lowerBound->SetMarkerSize(marker_size);
  h_pp_JERsmear->SetMarkerSize(marker_size);
  h_pp_bGS->SetMarkerSize(marker_size);
  h_pp_JEUShiftCombined->SetMarkerSize(marker_size);
  h_pp_JEUShiftUp->SetMarkerSize(marker_size);
  h_pp_JEUShiftDown->SetMarkerSize(marker_size);
  h_pp_centShiftCombined->SetMarkerSize(marker_size);
  h_pp_centShiftUp->SetMarkerSize(marker_size);
  h_pp_centShiftDown->SetMarkerSize(marker_size);
  h_pp_total->SetMarkerSize(marker_size);

  h_pp_cFraction->SetLineWidth(line_width);
  h_pp_lowerBound->SetLineWidth(line_width);
  h_pp_JERsmear->SetLineWidth(line_width);
  h_pp_bGS->SetLineWidth(line_width);
  h_pp_JEUShiftCombined->SetLineWidth(line_width);
  h_pp_JEUShiftUp->SetLineWidth(line_width);
  h_pp_JEUShiftDown->SetLineWidth(line_width);
  h_pp_centShiftCombined->SetLineWidth(line_width);
  h_pp_centShiftUp->SetLineWidth(line_width);
  h_pp_centShiftDown->SetLineWidth(line_width);
  h_pp_total->SetLineWidth(line_width);

  h_pp_cFraction->SetLineStyle(2);
  h_pp_lowerBound->SetLineStyle(3);
  h_pp_JERsmear->SetLineStyle(6);
  h_pp_bGS->SetLineStyle(7);
  h_pp_JEUShiftCombined->SetLineStyle(8);
  h_pp_JEUShiftUp->SetLineStyle(8);
  h_pp_JEUShiftDown->SetLineStyle(9);
  h_pp_centShiftCombined->SetLineStyle(4);
  h_pp_centShiftUp->SetLineStyle(4);
  h_pp_centShiftDown->SetLineStyle(5);  
  h_pp_total->SetLineStyle(1);

  // C4 -------------------------------------------
  TH1D *h_C4_cFraction = new TH1D("h_C4_cFraction","h_C4_cFraction",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C4_lowerBound = new TH1D("h_C4_lowerBound","h_C4_lowerBound",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C4_JERsmear = new TH1D("h_C4_JERsmear","h_C4_JERsmear",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C4_bGS = new TH1D("h_C4_bGS","h_C4_bGS",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C4_JEUShiftCombined = new TH1D("h_C4_JEUShiftCombined","h_C4_JEUShiftCombined",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C4_JEUShiftUp = new TH1D("h_C4_JEUShiftUp","h_C4_JEUShiftUp",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C4_JEUShiftDown = new TH1D("h_C4_JEUShiftDown","h_C4_JEUShiftDown",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C4_centShiftCombined = new TH1D("h_C4_centShiftCombined","h_C4_centShiftCombined",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C4_centShiftUp = new TH1D("h_C4_centShiftUp","h_C4_centShiftUp",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C4_centShiftDown = new TH1D("h_C4_centShiftDown","h_C4_centShiftDown",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C4_residual = new TH1D("h_C4_residual","h_C4_residual",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C4_total = new TH1D("h_C4_total","h_C4_total",N_jetPtAxisEdges-1,jetPtAxisEdges);
  
  h_C4_cFraction->SetBinContent(1,input_C4_cFrac_J1);
  h_C4_cFraction->SetBinContent(2,input_C4_cFrac_J2);
  h_C4_cFraction->SetBinContent(3,input_C4_cFrac_J3);
  h_C4_cFraction->SetBinContent(4,input_C4_cFrac_J4);
  h_C4_cFraction->SetBinContent(5,input_C4_cFrac_J5);
  h_C4_cFraction->SetBinContent(6,input_C4_cFrac_J6);

  h_C4_lowerBound->SetBinContent(1,input_C4_lowerBound_J1);
  h_C4_lowerBound->SetBinContent(2,input_C4_lowerBound_J2);
  h_C4_lowerBound->SetBinContent(3,input_C4_lowerBound_J3);
  h_C4_lowerBound->SetBinContent(4,input_C4_lowerBound_J4);
  h_C4_lowerBound->SetBinContent(5,input_C4_lowerBound_J5);
  h_C4_lowerBound->SetBinContent(6,input_C4_lowerBound_J6);

  h_C4_JERsmear->SetBinContent(1,input_C4_JERsmear_J1);
  h_C4_JERsmear->SetBinContent(2,input_C4_JERsmear_J2);
  h_C4_JERsmear->SetBinContent(3,input_C4_JERsmear_J3);
  h_C4_JERsmear->SetBinContent(4,input_C4_JERsmear_J4);
  h_C4_JERsmear->SetBinContent(5,input_C4_JERsmear_J5);
  h_C4_JERsmear->SetBinContent(6,input_C4_JERsmear_J6);

  h_C4_bGS->SetBinContent(1,input_C4_bGS_J1);
  h_C4_bGS->SetBinContent(2,input_C4_bGS_J2);
  h_C4_bGS->SetBinContent(3,input_C4_bGS_J3);
  h_C4_bGS->SetBinContent(4,input_C4_bGS_J4);
  h_C4_bGS->SetBinContent(5,input_C4_bGS_J5);
  h_C4_bGS->SetBinContent(6,input_C4_bGS_J6);
  
  h_C4_JEUShiftCombined->SetBinContent(1,input_C4_JEUShiftCombined_J1);
  h_C4_JEUShiftCombined->SetBinContent(2,input_C4_JEUShiftCombined_J2);
  h_C4_JEUShiftCombined->SetBinContent(3,input_C4_JEUShiftCombined_J3);
  h_C4_JEUShiftCombined->SetBinContent(4,input_C4_JEUShiftCombined_J4);
  h_C4_JEUShiftCombined->SetBinContent(5,input_C4_JEUShiftCombined_J5);
  h_C4_JEUShiftCombined->SetBinContent(6,input_C4_JEUShiftCombined_J6);

  h_C4_JEUShiftUp->SetBinContent(1,input_C4_JEUShiftUp_J1);
  h_C4_JEUShiftUp->SetBinContent(2,input_C4_JEUShiftUp_J2);
  h_C4_JEUShiftUp->SetBinContent(3,input_C4_JEUShiftUp_J3);
  h_C4_JEUShiftUp->SetBinContent(4,input_C4_JEUShiftUp_J4);
  h_C4_JEUShiftUp->SetBinContent(5,input_C4_JEUShiftUp_J5);
  h_C4_JEUShiftUp->SetBinContent(6,input_C4_JEUShiftUp_J6);

  h_C4_JEUShiftDown->SetBinContent(1,input_C4_JEUShiftDown_J1);
  h_C4_JEUShiftDown->SetBinContent(2,input_C4_JEUShiftDown_J2);
  h_C4_JEUShiftDown->SetBinContent(3,input_C4_JEUShiftDown_J3);
  h_C4_JEUShiftDown->SetBinContent(4,input_C4_JEUShiftDown_J4);
  h_C4_JEUShiftDown->SetBinContent(5,input_C4_JEUShiftDown_J5);
  h_C4_JEUShiftDown->SetBinContent(6,input_C4_JEUShiftDown_J6);

  h_C4_centShiftCombined->SetBinContent(1,input_C4_centShiftCombined_J1);
  h_C4_centShiftCombined->SetBinContent(2,input_C4_centShiftCombined_J2);
  h_C4_centShiftCombined->SetBinContent(3,input_C4_centShiftCombined_J3);
  h_C4_centShiftCombined->SetBinContent(4,input_C4_centShiftCombined_J4);
  h_C4_centShiftCombined->SetBinContent(5,input_C4_centShiftCombined_J5);
  h_C4_centShiftCombined->SetBinContent(6,input_C4_centShiftCombined_J6);

  h_C4_centShiftUp->SetBinContent(1,input_C4_centShiftUp_J1);
  h_C4_centShiftUp->SetBinContent(2,input_C4_centShiftUp_J2);
  h_C4_centShiftUp->SetBinContent(3,input_C4_centShiftUp_J3);
  h_C4_centShiftUp->SetBinContent(4,input_C4_centShiftUp_J4);
  h_C4_centShiftUp->SetBinContent(5,input_C4_centShiftUp_J5);
  h_C4_centShiftUp->SetBinContent(6,input_C4_centShiftUp_J6);

  h_C4_centShiftDown->SetBinContent(1,input_C4_centShiftDown_J1);
  h_C4_centShiftDown->SetBinContent(2,input_C4_centShiftDown_J2);
  h_C4_centShiftDown->SetBinContent(3,input_C4_centShiftDown_J3);
  h_C4_centShiftDown->SetBinContent(4,input_C4_centShiftDown_J4);
  h_C4_centShiftDown->SetBinContent(5,input_C4_centShiftDown_J5);
  h_C4_centShiftDown->SetBinContent(6,input_C4_centShiftDown_J6);

  h_C4_total->SetBinContent(1,input_C4_total_J1);
  h_C4_total->SetBinContent(2,input_C4_total_J2);
  h_C4_total->SetBinContent(3,input_C4_total_J3);
  h_C4_total->SetBinContent(4,input_C4_total_J4);
  h_C4_total->SetBinContent(5,input_C4_total_J5);
  h_C4_total->SetBinContent(6,input_C4_total_J6);

  // set style
  h_C4_cFraction->SetMarkerColor(kBlue-4);
  h_C4_lowerBound->SetMarkerColor(kRed-4);
  h_C4_JERsmear->SetMarkerColor(kOrange);
  h_C4_bGS->SetMarkerColor(kBlue-9);
  h_C4_JEUShiftCombined->SetMarkerColor(kGreen-8);
  h_C4_JEUShiftUp->SetMarkerColor(kGreen-8);
  h_C4_JEUShiftDown->SetMarkerColor(kPink+9);
  h_C4_centShiftCombined->SetMarkerColor(kGreen+2);
  h_C4_centShiftUp->SetMarkerColor(kGreen+2);
  h_C4_centShiftDown->SetMarkerColor(kMagenta);
  h_C4_total->SetMarkerColor(kBlack);

  h_C4_cFraction->SetLineColor(kBlue-4);
  h_C4_lowerBound->SetLineColor(kRed-4);
  h_C4_JERsmear->SetLineColor(kOrange);
  h_C4_bGS->SetLineColor(kBlue-9);
  h_C4_JEUShiftCombined->SetLineColor(kGreen-8);
  h_C4_JEUShiftUp->SetLineColor(kGreen-8);
  h_C4_JEUShiftDown->SetLineColor(kPink+9);
  h_C4_centShiftCombined->SetLineColor(kGreen+2);
  h_C4_centShiftUp->SetLineColor(kGreen+2);
  h_C4_centShiftDown->SetLineColor(kMagenta);
  h_C4_total->SetLineColor(kBlack);

  h_C4_cFraction->SetMarkerStyle(25);
  h_C4_lowerBound->SetMarkerStyle(26);
  h_C4_JERsmear->SetMarkerStyle(30);
  h_C4_bGS->SetMarkerStyle(32);
  h_C4_JEUShiftCombined->SetMarkerStyle(33);
  h_C4_JEUShiftUp->SetMarkerStyle(33);
  h_C4_JEUShiftDown->SetMarkerStyle(34);
  h_C4_centShiftCombined->SetMarkerStyle(27);
  h_C4_centShiftUp->SetMarkerStyle(27);
  h_C4_centShiftDown->SetMarkerStyle(28);
  h_C4_total->SetMarkerStyle(24);

  h_C4_cFraction->SetMarkerSize(marker_size);
  h_C4_lowerBound->SetMarkerSize(marker_size);
  h_C4_JERsmear->SetMarkerSize(marker_size);
  h_C4_bGS->SetMarkerSize(marker_size);
  h_C4_JEUShiftCombined->SetMarkerSize(marker_size);
  h_C4_JEUShiftUp->SetMarkerSize(marker_size);
  h_C4_JEUShiftDown->SetMarkerSize(marker_size);
  h_C4_centShiftCombined->SetMarkerSize(marker_size);
  h_C4_centShiftUp->SetMarkerSize(marker_size);
  h_C4_centShiftDown->SetMarkerSize(marker_size);
  h_C4_total->SetMarkerSize(marker_size);

  h_C4_cFraction->SetLineWidth(line_width);
  h_C4_lowerBound->SetLineWidth(line_width);
  h_C4_JERsmear->SetLineWidth(line_width);
  h_C4_bGS->SetLineWidth(line_width);
  h_C4_JEUShiftCombined->SetLineWidth(line_width);
  h_C4_JEUShiftUp->SetLineWidth(line_width);
  h_C4_JEUShiftDown->SetLineWidth(line_width);
  h_C4_centShiftCombined->SetLineWidth(line_width);
  h_C4_centShiftUp->SetLineWidth(line_width);
  h_C4_centShiftDown->SetLineWidth(line_width);
  h_C4_total->SetLineWidth(line_width);

  h_C4_cFraction->SetLineStyle(2);
  h_C4_lowerBound->SetLineStyle(3);
  h_C4_JERsmear->SetLineStyle(6);
  h_C4_bGS->SetLineStyle(7);
  h_C4_JEUShiftCombined->SetLineStyle(8);
  h_C4_JEUShiftUp->SetLineStyle(8);
  h_C4_JEUShiftDown->SetLineStyle(9);
  h_C4_centShiftCombined->SetLineStyle(4);
  h_C4_centShiftUp->SetLineStyle(4);
  h_C4_centShiftDown->SetLineStyle(5);  
  h_C4_total->SetLineStyle(1);

  // C3 -------------------------------------------
  TH1D *h_C3_cFraction = new TH1D("h_C3_cFraction","h_C3_cFraction",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C3_lowerBound = new TH1D("h_C3_lowerBound","h_C3_lowerBound",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C3_JERsmear = new TH1D("h_C3_JERsmear","h_C3_JERsmear",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C3_bGS = new TH1D("h_C3_bGS","h_C3_bGS",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C3_JEUShiftCombined = new TH1D("h_C3_JEUShiftCombined","h_C3_JEUShiftCombined",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C3_JEUShiftUp = new TH1D("h_C3_JEUShiftUp","h_C3_JEUShiftUp",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C3_JEUShiftDown = new TH1D("h_C3_JEUShiftDown","h_C3_JEUShiftDown",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C3_centShiftCombined = new TH1D("h_C3_centShiftCombined","h_C3_centShiftCombined",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C3_centShiftUp = new TH1D("h_C3_centShiftUp","h_C3_centShiftUp",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C3_centShiftDown = new TH1D("h_C3_centShiftDown","h_C3_centShiftDown",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C3_residual = new TH1D("h_C3_residual","h_C3_residual",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C3_total = new TH1D("h_C3_total","h_C3_total",N_jetPtAxisEdges-1,jetPtAxisEdges);
  
  h_C3_cFraction->SetBinContent(1,input_C3_cFrac_J1);
  h_C3_cFraction->SetBinContent(2,input_C3_cFrac_J2);
  h_C3_cFraction->SetBinContent(3,input_C3_cFrac_J3);
  h_C3_cFraction->SetBinContent(4,input_C3_cFrac_J4);
  h_C3_cFraction->SetBinContent(5,input_C3_cFrac_J5);
  h_C3_cFraction->SetBinContent(6,input_C3_cFrac_J6);

  h_C3_lowerBound->SetBinContent(1,input_C3_lowerBound_J1);
  h_C3_lowerBound->SetBinContent(2,input_C3_lowerBound_J2);
  h_C3_lowerBound->SetBinContent(3,input_C3_lowerBound_J3);
  h_C3_lowerBound->SetBinContent(4,input_C3_lowerBound_J4);
  h_C3_lowerBound->SetBinContent(5,input_C3_lowerBound_J5);
  h_C3_lowerBound->SetBinContent(6,input_C3_lowerBound_J6);

  h_C3_JERsmear->SetBinContent(1,input_C3_JERsmear_J1);
  h_C3_JERsmear->SetBinContent(2,input_C3_JERsmear_J2);
  h_C3_JERsmear->SetBinContent(3,input_C3_JERsmear_J3);
  h_C3_JERsmear->SetBinContent(4,input_C3_JERsmear_J4);
  h_C3_JERsmear->SetBinContent(5,input_C3_JERsmear_J5);
  h_C3_JERsmear->SetBinContent(6,input_C3_JERsmear_J6);

  h_C3_bGS->SetBinContent(1,input_C3_bGS_J1);
  h_C3_bGS->SetBinContent(2,input_C3_bGS_J2);
  h_C3_bGS->SetBinContent(3,input_C3_bGS_J3);
  h_C3_bGS->SetBinContent(4,input_C3_bGS_J4);
  h_C3_bGS->SetBinContent(5,input_C3_bGS_J5);
  h_C3_bGS->SetBinContent(6,input_C3_bGS_J6);
  
  h_C3_JEUShiftCombined->SetBinContent(1,input_C3_JEUShiftCombined_J1);
  h_C3_JEUShiftCombined->SetBinContent(2,input_C3_JEUShiftCombined_J2);
  h_C3_JEUShiftCombined->SetBinContent(3,input_C3_JEUShiftCombined_J3);
  h_C3_JEUShiftCombined->SetBinContent(4,input_C3_JEUShiftCombined_J4);
  h_C3_JEUShiftCombined->SetBinContent(5,input_C3_JEUShiftCombined_J5);
  h_C3_JEUShiftCombined->SetBinContent(6,input_C3_JEUShiftCombined_J6);

  h_C3_JEUShiftUp->SetBinContent(1,input_C3_JEUShiftUp_J1);
  h_C3_JEUShiftUp->SetBinContent(2,input_C3_JEUShiftUp_J2);
  h_C3_JEUShiftUp->SetBinContent(3,input_C3_JEUShiftUp_J3);
  h_C3_JEUShiftUp->SetBinContent(4,input_C3_JEUShiftUp_J4);
  h_C3_JEUShiftUp->SetBinContent(5,input_C3_JEUShiftUp_J5);
  h_C3_JEUShiftUp->SetBinContent(6,input_C3_JEUShiftUp_J6);

  h_C3_JEUShiftDown->SetBinContent(1,input_C3_JEUShiftDown_J1);
  h_C3_JEUShiftDown->SetBinContent(2,input_C3_JEUShiftDown_J2);
  h_C3_JEUShiftDown->SetBinContent(3,input_C3_JEUShiftDown_J3);
  h_C3_JEUShiftDown->SetBinContent(4,input_C3_JEUShiftDown_J4);
  h_C3_JEUShiftDown->SetBinContent(5,input_C3_JEUShiftDown_J5);
  h_C3_JEUShiftDown->SetBinContent(6,input_C3_JEUShiftDown_J6);

  h_C3_centShiftCombined->SetBinContent(1,input_C3_centShiftCombined_J1);
  h_C3_centShiftCombined->SetBinContent(2,input_C3_centShiftCombined_J2);
  h_C3_centShiftCombined->SetBinContent(3,input_C3_centShiftCombined_J3);
  h_C3_centShiftCombined->SetBinContent(4,input_C3_centShiftCombined_J4);
  h_C3_centShiftCombined->SetBinContent(5,input_C3_centShiftCombined_J5);
  h_C3_centShiftCombined->SetBinContent(6,input_C3_centShiftCombined_J6);

  h_C3_centShiftUp->SetBinContent(1,input_C3_centShiftUp_J1);
  h_C3_centShiftUp->SetBinContent(2,input_C3_centShiftUp_J2);
  h_C3_centShiftUp->SetBinContent(3,input_C3_centShiftUp_J3);
  h_C3_centShiftUp->SetBinContent(4,input_C3_centShiftUp_J4);
  h_C3_centShiftUp->SetBinContent(5,input_C3_centShiftUp_J5);
  h_C3_centShiftUp->SetBinContent(6,input_C3_centShiftUp_J6);

  h_C3_centShiftDown->SetBinContent(1,input_C3_centShiftDown_J1);
  h_C3_centShiftDown->SetBinContent(2,input_C3_centShiftDown_J2);
  h_C3_centShiftDown->SetBinContent(3,input_C3_centShiftDown_J3);
  h_C3_centShiftDown->SetBinContent(4,input_C3_centShiftDown_J4);
  h_C3_centShiftDown->SetBinContent(5,input_C3_centShiftDown_J5);
  h_C3_centShiftDown->SetBinContent(6,input_C3_centShiftDown_J6);

  h_C3_total->SetBinContent(1,input_C3_total_J1);
  h_C3_total->SetBinContent(2,input_C3_total_J2);
  h_C3_total->SetBinContent(3,input_C3_total_J3);
  h_C3_total->SetBinContent(4,input_C3_total_J4);
  h_C3_total->SetBinContent(5,input_C3_total_J5);
  h_C3_total->SetBinContent(6,input_C3_total_J6);

  // set style
  h_C3_cFraction->SetMarkerColor(kBlue-4);
  h_C3_lowerBound->SetMarkerColor(kRed-4);
  h_C3_JERsmear->SetMarkerColor(kOrange);
  h_C3_bGS->SetMarkerColor(kBlue-9);
  h_C3_JEUShiftCombined->SetMarkerColor(kGreen-8);
  h_C3_JEUShiftUp->SetMarkerColor(kGreen-8);
  h_C3_JEUShiftDown->SetMarkerColor(kPink+9);
  h_C3_centShiftCombined->SetMarkerColor(kGreen+2);
  h_C3_centShiftUp->SetMarkerColor(kGreen+2);
  h_C3_centShiftDown->SetMarkerColor(kMagenta);
  h_C3_total->SetMarkerColor(kBlack);

  h_C3_cFraction->SetLineColor(kBlue-4);
  h_C3_lowerBound->SetLineColor(kRed-4);
  h_C3_JERsmear->SetLineColor(kOrange);
  h_C3_bGS->SetLineColor(kBlue-9);
  h_C3_JEUShiftCombined->SetLineColor(kGreen-8);
  h_C3_JEUShiftUp->SetLineColor(kGreen-8);
  h_C3_JEUShiftDown->SetLineColor(kPink+9);
  h_C3_centShiftCombined->SetLineColor(kGreen+2);
  h_C3_centShiftUp->SetLineColor(kGreen+2);
  h_C3_centShiftDown->SetLineColor(kMagenta);
  h_C3_total->SetLineColor(kBlack);

  h_C3_cFraction->SetMarkerStyle(25);
  h_C3_lowerBound->SetMarkerStyle(26);
  h_C3_JERsmear->SetMarkerStyle(30);
  h_C3_bGS->SetMarkerStyle(32);
  h_C3_JEUShiftCombined->SetMarkerStyle(33);
  h_C3_JEUShiftUp->SetMarkerStyle(33);
  h_C3_JEUShiftDown->SetMarkerStyle(34);
  h_C3_centShiftCombined->SetMarkerStyle(27);
  h_C3_centShiftUp->SetMarkerStyle(27);
  h_C3_centShiftDown->SetMarkerStyle(28);
  h_C3_total->SetMarkerStyle(24);

  h_C3_cFraction->SetMarkerSize(marker_size);
  h_C3_lowerBound->SetMarkerSize(marker_size);
  h_C3_JERsmear->SetMarkerSize(marker_size);
  h_C3_bGS->SetMarkerSize(marker_size);
  h_C3_JEUShiftCombined->SetMarkerSize(marker_size);
  h_C3_JEUShiftUp->SetMarkerSize(marker_size);
  h_C3_JEUShiftDown->SetMarkerSize(marker_size);
  h_C3_centShiftCombined->SetMarkerSize(marker_size);
  h_C3_centShiftUp->SetMarkerSize(marker_size);
  h_C3_centShiftDown->SetMarkerSize(marker_size);
  h_C3_total->SetMarkerSize(marker_size);

  h_C3_cFraction->SetLineWidth(line_width);
  h_C3_lowerBound->SetLineWidth(line_width);
  h_C3_JERsmear->SetLineWidth(line_width);
  h_C3_bGS->SetLineWidth(line_width);
  h_C3_JEUShiftCombined->SetLineWidth(line_width);
  h_C3_JEUShiftUp->SetLineWidth(line_width);
  h_C3_JEUShiftDown->SetLineWidth(line_width);
  h_C3_centShiftCombined->SetLineWidth(line_width);
  h_C3_centShiftUp->SetLineWidth(line_width);
  h_C3_centShiftDown->SetLineWidth(line_width);
  h_C3_total->SetLineWidth(line_width);

  h_C3_cFraction->SetLineStyle(2);
  h_C3_lowerBound->SetLineStyle(3);
  h_C3_JERsmear->SetLineStyle(6);
  h_C3_bGS->SetLineStyle(7);
  h_C3_JEUShiftCombined->SetLineStyle(8);
  h_C3_JEUShiftUp->SetLineStyle(8);
  h_C3_JEUShiftDown->SetLineStyle(9);
  h_C3_centShiftCombined->SetLineStyle(4);
  h_C3_centShiftUp->SetLineStyle(4);
  h_C3_centShiftDown->SetLineStyle(5);  
  h_C3_total->SetLineStyle(1);

 
  // C2 -------------------------------------------
  TH1D *h_C2_cFraction = new TH1D("h_C2_cFraction","h_C2_cFraction",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C2_lowerBound = new TH1D("h_C2_lowerBound","h_C2_lowerBound",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C2_JERsmear = new TH1D("h_C2_JERsmear","h_C2_JERsmear",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C2_bGS = new TH1D("h_C2_bGS","h_C2_bGS",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C2_JEUShiftCombined = new TH1D("h_C2_JEUShiftCombined","h_C2_JEUShiftCombined",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C2_JEUShiftUp = new TH1D("h_C2_JEUShiftUp","h_C2_JEUShiftUp",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C2_JEUShiftDown = new TH1D("h_C2_JEUShiftDown","h_C2_JEUShiftDown",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C2_centShiftCombined = new TH1D("h_C2_centShiftCombined","h_C2_centShiftCombined",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C2_centShiftUp = new TH1D("h_C2_centShiftUp","h_C2_centShiftUp",N_jetPtAxisEdges-1,jetPtAxisEdges);  
  TH1D *h_C2_centShiftDown = new TH1D("h_C2_centShiftDown","h_C2_centShiftDown",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C2_residual = new TH1D("h_C2_residual","h_C2_residual",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C2_total = new TH1D("h_C2_total","h_C2_total",N_jetPtAxisEdges-1,jetPtAxisEdges);
  
  h_C2_cFraction->SetBinContent(1,input_C2_cFrac_J1);
  h_C2_cFraction->SetBinContent(2,input_C2_cFrac_J2);
  h_C2_cFraction->SetBinContent(3,input_C2_cFrac_J3);
  h_C2_cFraction->SetBinContent(4,input_C2_cFrac_J4);
  h_C2_cFraction->SetBinContent(5,input_C2_cFrac_J5);
  h_C2_cFraction->SetBinContent(6,input_C2_cFrac_J6);

  h_C2_lowerBound->SetBinContent(1,input_C2_lowerBound_J1);
  h_C2_lowerBound->SetBinContent(2,input_C2_lowerBound_J2);
  h_C2_lowerBound->SetBinContent(3,input_C2_lowerBound_J3);
  h_C2_lowerBound->SetBinContent(4,input_C2_lowerBound_J4);
  h_C2_lowerBound->SetBinContent(5,input_C2_lowerBound_J5);
  h_C2_lowerBound->SetBinContent(6,input_C2_lowerBound_J6);

  h_C2_JERsmear->SetBinContent(1,input_C2_JERsmear_J1);
  h_C2_JERsmear->SetBinContent(2,input_C2_JERsmear_J2);
  h_C2_JERsmear->SetBinContent(3,input_C2_JERsmear_J3);
  h_C2_JERsmear->SetBinContent(4,input_C2_JERsmear_J4);
  h_C2_JERsmear->SetBinContent(5,input_C2_JERsmear_J5);
  h_C2_JERsmear->SetBinContent(6,input_C2_JERsmear_J6);

  h_C2_bGS->SetBinContent(1,input_C2_bGS_J1);
  h_C2_bGS->SetBinContent(2,input_C2_bGS_J2);
  h_C2_bGS->SetBinContent(3,input_C2_bGS_J3);
  h_C2_bGS->SetBinContent(4,input_C2_bGS_J4);
  h_C2_bGS->SetBinContent(5,input_C2_bGS_J5);
  h_C2_bGS->SetBinContent(6,input_C2_bGS_J6);
  
  h_C2_JEUShiftCombined->SetBinContent(1,input_C2_JEUShiftCombined_J1);
  h_C2_JEUShiftCombined->SetBinContent(2,input_C2_JEUShiftCombined_J2);
  h_C2_JEUShiftCombined->SetBinContent(3,input_C2_JEUShiftCombined_J3);
  h_C2_JEUShiftCombined->SetBinContent(4,input_C2_JEUShiftCombined_J4);
  h_C2_JEUShiftCombined->SetBinContent(5,input_C2_JEUShiftCombined_J5);
  h_C2_JEUShiftCombined->SetBinContent(6,input_C2_JEUShiftCombined_J6);

  h_C2_JEUShiftUp->SetBinContent(1,input_C2_JEUShiftUp_J1);
  h_C2_JEUShiftUp->SetBinContent(2,input_C2_JEUShiftUp_J2);
  h_C2_JEUShiftUp->SetBinContent(3,input_C2_JEUShiftUp_J3);
  h_C2_JEUShiftUp->SetBinContent(4,input_C2_JEUShiftUp_J4);
  h_C2_JEUShiftUp->SetBinContent(5,input_C2_JEUShiftUp_J5);
  h_C2_JEUShiftUp->SetBinContent(6,input_C2_JEUShiftUp_J6);

  h_C2_JEUShiftDown->SetBinContent(1,input_C2_JEUShiftDown_J1);
  h_C2_JEUShiftDown->SetBinContent(2,input_C2_JEUShiftDown_J2);
  h_C2_JEUShiftDown->SetBinContent(3,input_C2_JEUShiftDown_J3);
  h_C2_JEUShiftDown->SetBinContent(4,input_C2_JEUShiftDown_J4);
  h_C2_JEUShiftDown->SetBinContent(5,input_C2_JEUShiftDown_J5);
  h_C2_JEUShiftDown->SetBinContent(6,input_C2_JEUShiftDown_J6);

  h_C2_centShiftCombined->SetBinContent(1,input_C2_centShiftCombined_J1);
  h_C2_centShiftCombined->SetBinContent(2,input_C2_centShiftCombined_J2);
  h_C2_centShiftCombined->SetBinContent(3,input_C2_centShiftCombined_J3);
  h_C2_centShiftCombined->SetBinContent(4,input_C2_centShiftCombined_J4);
  h_C2_centShiftCombined->SetBinContent(5,input_C2_centShiftCombined_J5);
  h_C2_centShiftCombined->SetBinContent(6,input_C2_centShiftCombined_J6);

  h_C2_centShiftUp->SetBinContent(1,input_C2_centShiftUp_J1);
  h_C2_centShiftUp->SetBinContent(2,input_C2_centShiftUp_J2);
  h_C2_centShiftUp->SetBinContent(3,input_C2_centShiftUp_J3);
  h_C2_centShiftUp->SetBinContent(4,input_C2_centShiftUp_J4);
  h_C2_centShiftUp->SetBinContent(5,input_C2_centShiftUp_J5);
  h_C2_centShiftUp->SetBinContent(6,input_C2_centShiftUp_J6);

  h_C2_centShiftDown->SetBinContent(1,input_C2_centShiftDown_J1);
  h_C2_centShiftDown->SetBinContent(2,input_C2_centShiftDown_J2);
  h_C2_centShiftDown->SetBinContent(3,input_C2_centShiftDown_J3);
  h_C2_centShiftDown->SetBinContent(4,input_C2_centShiftDown_J4);
  h_C2_centShiftDown->SetBinContent(5,input_C2_centShiftDown_J5);
  h_C2_centShiftDown->SetBinContent(6,input_C2_centShiftDown_J6);

  h_C2_total->SetBinContent(1,input_C2_total_J1);
  h_C2_total->SetBinContent(2,input_C2_total_J2);
  h_C2_total->SetBinContent(3,input_C2_total_J3);
  h_C2_total->SetBinContent(4,input_C2_total_J4);
  h_C2_total->SetBinContent(5,input_C2_total_J5);
  h_C2_total->SetBinContent(6,input_C2_total_J6);

  // set style
  h_C2_cFraction->SetMarkerColor(kBlue-4);
  h_C2_lowerBound->SetMarkerColor(kRed-4);
  h_C2_JERsmear->SetMarkerColor(kOrange);
  h_C2_bGS->SetMarkerColor(kBlue-9);
  h_C2_JEUShiftCombined->SetMarkerColor(kGreen-8);
  h_C2_JEUShiftUp->SetMarkerColor(kGreen-8);
  h_C2_JEUShiftDown->SetMarkerColor(kPink+9);
  h_C2_centShiftCombined->SetMarkerColor(kGreen+2);
  h_C2_centShiftUp->SetMarkerColor(kGreen+2);
  h_C2_centShiftDown->SetMarkerColor(kMagenta);
  h_C2_total->SetMarkerColor(kBlack);

  h_C2_cFraction->SetLineColor(kBlue-4);
  h_C2_lowerBound->SetLineColor(kRed-4);
  h_C2_JERsmear->SetLineColor(kOrange);
  h_C2_bGS->SetLineColor(kBlue-9);
  h_C2_JEUShiftCombined->SetLineColor(kGreen-8);
  h_C2_JEUShiftUp->SetLineColor(kGreen-8);
  h_C2_JEUShiftDown->SetLineColor(kPink+9);
  h_C2_centShiftCombined->SetLineColor(kGreen+2);
  h_C2_centShiftUp->SetLineColor(kGreen+2);
  h_C2_centShiftDown->SetLineColor(kMagenta);
  h_C2_total->SetLineColor(kBlack);

  h_C2_cFraction->SetMarkerStyle(25);
  h_C2_lowerBound->SetMarkerStyle(26);
  h_C2_JERsmear->SetMarkerStyle(30);
  h_C2_bGS->SetMarkerStyle(32);
  h_C2_JEUShiftCombined->SetMarkerStyle(33);
  h_C2_JEUShiftUp->SetMarkerStyle(33);
  h_C2_JEUShiftDown->SetMarkerStyle(34);
  h_C2_centShiftCombined->SetMarkerStyle(27);
  h_C2_centShiftUp->SetMarkerStyle(27);
  h_C2_centShiftDown->SetMarkerStyle(28);
  h_C2_total->SetMarkerStyle(24);

  h_C2_cFraction->SetMarkerSize(marker_size);
  h_C2_lowerBound->SetMarkerSize(marker_size);
  h_C2_JERsmear->SetMarkerSize(marker_size);
  h_C2_bGS->SetMarkerSize(marker_size);
  h_C2_JEUShiftCombined->SetMarkerSize(marker_size);
  h_C2_JEUShiftUp->SetMarkerSize(marker_size);
  h_C2_JEUShiftDown->SetMarkerSize(marker_size);
  h_C2_centShiftCombined->SetMarkerSize(marker_size);
  h_C2_centShiftUp->SetMarkerSize(marker_size);
  h_C2_centShiftDown->SetMarkerSize(marker_size);
  h_C2_total->SetMarkerSize(marker_size);

  h_C2_cFraction->SetLineWidth(line_width);
  h_C2_lowerBound->SetLineWidth(line_width);
  h_C2_JERsmear->SetLineWidth(line_width);
  h_C2_bGS->SetLineWidth(line_width);
  h_C2_JEUShiftCombined->SetLineWidth(line_width);
  h_C2_JEUShiftUp->SetLineWidth(line_width);
  h_C2_JEUShiftDown->SetLineWidth(line_width);
  h_C2_centShiftCombined->SetLineWidth(line_width);
  h_C2_centShiftUp->SetLineWidth(line_width);
  h_C2_centShiftDown->SetLineWidth(line_width);
  h_C2_total->SetLineWidth(line_width);

  h_C2_cFraction->SetLineStyle(2);
  h_C2_lowerBound->SetLineStyle(3);
  h_C2_JERsmear->SetLineStyle(6);
  h_C2_bGS->SetLineStyle(7);
  h_C2_JEUShiftCombined->SetLineStyle(8);
  h_C2_JEUShiftUp->SetLineStyle(8);
  h_C2_JEUShiftDown->SetLineStyle(9);
  h_C2_centShiftCombined->SetLineStyle(4);
  h_C2_centShiftUp->SetLineStyle(4);
  h_C2_centShiftDown->SetLineStyle(5);  
  h_C2_total->SetLineStyle(1);

  // C1 -------------------------------------------
  TH1D *h_C1_cFraction = new TH1D("h_C1_cFraction","h_C1_cFraction",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C1_lowerBound = new TH1D("h_C1_lowerBound","h_C1_lowerBound",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C1_JERsmear = new TH1D("h_C1_JERsmear","h_C1_JERsmear",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C1_bGS = new TH1D("h_C1_bGS","h_C1_bGS",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C1_JEUShiftCombined = new TH1D("h_C1_JEUShiftCombined","h_C1_JEUShiftCombined",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C1_JEUShiftUp = new TH1D("h_C1_JEUShiftUp","h_C1_JEUShiftUp",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C1_JEUShiftDown = new TH1D("h_C1_JEUShiftDown","h_C1_JEUShiftDown",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C1_centShiftCombined = new TH1D("h_C1_centShiftCombined","h_C1_centShiftCombined",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C1_centShiftUp = new TH1D("h_C1_centShiftUp","h_C1_centShiftUp",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C1_centShiftDown = new TH1D("h_C1_centShiftDown","h_C1_centShiftDown",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C1_residual = new TH1D("h_C1_residual","h_C1_residual",N_jetPtAxisEdges-1,jetPtAxisEdges);
  TH1D *h_C1_total = new TH1D("h_C1_total","h_C1_total",N_jetPtAxisEdges-1,jetPtAxisEdges);
  
  h_C1_cFraction->SetBinContent(1,input_C1_cFrac_J1);
  h_C1_cFraction->SetBinContent(2,input_C1_cFrac_J2);
  h_C1_cFraction->SetBinContent(3,input_C1_cFrac_J3);
  h_C1_cFraction->SetBinContent(4,input_C1_cFrac_J4);
  h_C1_cFraction->SetBinContent(5,input_C1_cFrac_J5);
  h_C1_cFraction->SetBinContent(6,input_C1_cFrac_J6);

  h_C1_lowerBound->SetBinContent(1,input_C1_lowerBound_J1);
  h_C1_lowerBound->SetBinContent(2,input_C1_lowerBound_J2);
  h_C1_lowerBound->SetBinContent(3,input_C1_lowerBound_J3);
  h_C1_lowerBound->SetBinContent(4,input_C1_lowerBound_J4);
  h_C1_lowerBound->SetBinContent(5,input_C1_lowerBound_J5);
  h_C1_lowerBound->SetBinContent(6,input_C1_lowerBound_J6);

  h_C1_JERsmear->SetBinContent(1,input_C1_JERsmear_J1);
  h_C1_JERsmear->SetBinContent(2,input_C1_JERsmear_J2);
  h_C1_JERsmear->SetBinContent(3,input_C1_JERsmear_J3);
  h_C1_JERsmear->SetBinContent(4,input_C1_JERsmear_J4);
  h_C1_JERsmear->SetBinContent(5,input_C1_JERsmear_J5);
  h_C1_JERsmear->SetBinContent(6,input_C1_JERsmear_J6);

  h_C1_bGS->SetBinContent(1,input_C1_bGS_J1);
  h_C1_bGS->SetBinContent(2,input_C1_bGS_J2);
  h_C1_bGS->SetBinContent(3,input_C1_bGS_J3);
  h_C1_bGS->SetBinContent(4,input_C1_bGS_J4);
  h_C1_bGS->SetBinContent(5,input_C1_bGS_J5);
  h_C1_bGS->SetBinContent(6,input_C1_bGS_J6);
  
  h_C1_JEUShiftCombined->SetBinContent(1,input_C1_JEUShiftCombined_J1);
  h_C1_JEUShiftCombined->SetBinContent(2,input_C1_JEUShiftCombined_J2);
  h_C1_JEUShiftCombined->SetBinContent(3,input_C1_JEUShiftCombined_J3);
  h_C1_JEUShiftCombined->SetBinContent(4,input_C1_JEUShiftCombined_J4);
  h_C1_JEUShiftCombined->SetBinContent(5,input_C1_JEUShiftCombined_J5);
  h_C1_JEUShiftCombined->SetBinContent(6,input_C1_JEUShiftCombined_J6);

  h_C1_JEUShiftUp->SetBinContent(1,input_C1_JEUShiftUp_J1);
  h_C1_JEUShiftUp->SetBinContent(2,input_C1_JEUShiftUp_J2);
  h_C1_JEUShiftUp->SetBinContent(3,input_C1_JEUShiftUp_J3);
  h_C1_JEUShiftUp->SetBinContent(4,input_C1_JEUShiftUp_J4);
  h_C1_JEUShiftUp->SetBinContent(5,input_C1_JEUShiftUp_J5);
  h_C1_JEUShiftUp->SetBinContent(6,input_C1_JEUShiftUp_J6);

  h_C1_JEUShiftDown->SetBinContent(1,input_C1_JEUShiftDown_J1);
  h_C1_JEUShiftDown->SetBinContent(2,input_C1_JEUShiftDown_J2);
  h_C1_JEUShiftDown->SetBinContent(3,input_C1_JEUShiftDown_J3);
  h_C1_JEUShiftDown->SetBinContent(4,input_C1_JEUShiftDown_J4);
  h_C1_JEUShiftDown->SetBinContent(5,input_C1_JEUShiftDown_J5);
  h_C1_JEUShiftDown->SetBinContent(6,input_C1_JEUShiftDown_J6);

  h_C1_centShiftCombined->SetBinContent(1,input_C1_centShiftCombined_J1);
  h_C1_centShiftCombined->SetBinContent(2,input_C1_centShiftCombined_J2);
  h_C1_centShiftCombined->SetBinContent(3,input_C1_centShiftCombined_J3);
  h_C1_centShiftCombined->SetBinContent(4,input_C1_centShiftCombined_J4);
  h_C1_centShiftCombined->SetBinContent(5,input_C1_centShiftCombined_J5);
  h_C1_centShiftCombined->SetBinContent(6,input_C1_centShiftCombined_J6);

  h_C1_centShiftUp->SetBinContent(1,input_C1_centShiftUp_J1);
  h_C1_centShiftUp->SetBinContent(2,input_C1_centShiftUp_J2);
  h_C1_centShiftUp->SetBinContent(3,input_C1_centShiftUp_J3);
  h_C1_centShiftUp->SetBinContent(4,input_C1_centShiftUp_J4);
  h_C1_centShiftUp->SetBinContent(5,input_C1_centShiftUp_J5);
  h_C1_centShiftUp->SetBinContent(6,input_C1_centShiftUp_J6);

  h_C1_centShiftDown->SetBinContent(1,input_C1_centShiftDown_J1);
  h_C1_centShiftDown->SetBinContent(2,input_C1_centShiftDown_J2);
  h_C1_centShiftDown->SetBinContent(3,input_C1_centShiftDown_J3);
  h_C1_centShiftDown->SetBinContent(4,input_C1_centShiftDown_J4);
  h_C1_centShiftDown->SetBinContent(5,input_C1_centShiftDown_J5);
  h_C1_centShiftDown->SetBinContent(6,input_C1_centShiftDown_J6);

  h_C1_total->SetBinContent(1,input_C1_total_J1);
  h_C1_total->SetBinContent(2,input_C1_total_J2);
  h_C1_total->SetBinContent(3,input_C1_total_J3);
  h_C1_total->SetBinContent(4,input_C1_total_J4);
  h_C1_total->SetBinContent(5,input_C1_total_J5);
  h_C1_total->SetBinContent(6,input_C1_total_J6);

  // set style
  h_C1_cFraction->SetMarkerColor(kBlue-4);
  h_C1_lowerBound->SetMarkerColor(kRed-4);
  h_C1_JERsmear->SetMarkerColor(kOrange);
  h_C1_bGS->SetMarkerColor(kBlue-9);
  h_C1_JEUShiftCombined->SetMarkerColor(kGreen-8);
  h_C1_JEUShiftUp->SetMarkerColor(kGreen-8);
  h_C1_JEUShiftDown->SetMarkerColor(kPink+9);
  h_C1_centShiftCombined->SetMarkerColor(kGreen+2);
  h_C1_centShiftUp->SetMarkerColor(kGreen+2);
  h_C1_centShiftDown->SetMarkerColor(kMagenta);
  h_C1_total->SetMarkerColor(kBlack);

  h_C1_cFraction->SetLineColor(kBlue-4);
  h_C1_lowerBound->SetLineColor(kRed-4);
  h_C1_JERsmear->SetLineColor(kOrange);
  h_C1_bGS->SetLineColor(kBlue-9);
  h_C1_JEUShiftCombined->SetLineColor(kGreen-8);
  h_C1_JEUShiftUp->SetLineColor(kGreen-8);
  h_C1_JEUShiftDown->SetLineColor(kPink+9);
  h_C1_centShiftCombined->SetLineColor(kGreen+2);
  h_C1_centShiftUp->SetLineColor(kGreen+2);
  h_C1_centShiftDown->SetLineColor(kMagenta);
  h_C1_total->SetLineColor(kBlack);

  h_C1_cFraction->SetMarkerStyle(25);
  h_C1_lowerBound->SetMarkerStyle(26);
  h_C1_JERsmear->SetMarkerStyle(30);
  h_C1_bGS->SetMarkerStyle(32);
  h_C1_JEUShiftCombined->SetMarkerStyle(33);
  h_C1_JEUShiftUp->SetMarkerStyle(33);
  h_C1_JEUShiftDown->SetMarkerStyle(34);
  h_C1_centShiftCombined->SetMarkerStyle(27);
  h_C1_centShiftUp->SetMarkerStyle(27);
  h_C1_centShiftDown->SetMarkerStyle(28);
  h_C1_total->SetMarkerStyle(24);

  h_C1_cFraction->SetMarkerSize(marker_size);
  h_C1_lowerBound->SetMarkerSize(marker_size);
  h_C1_JERsmear->SetMarkerSize(marker_size);
  h_C1_bGS->SetMarkerSize(marker_size);
  h_C1_JEUShiftCombined->SetMarkerSize(marker_size);
  h_C1_JEUShiftUp->SetMarkerSize(marker_size);
  h_C1_JEUShiftDown->SetMarkerSize(marker_size);
  h_C1_centShiftCombined->SetMarkerSize(marker_size);
  h_C1_centShiftUp->SetMarkerSize(marker_size);
  h_C1_centShiftDown->SetMarkerSize(marker_size);
  h_C1_total->SetMarkerSize(marker_size);

  h_C1_cFraction->SetLineWidth(line_width);
  h_C1_lowerBound->SetLineWidth(line_width);
  h_C1_JERsmear->SetLineWidth(line_width);
  h_C1_bGS->SetLineWidth(line_width);
  h_C1_JEUShiftCombined->SetLineWidth(line_width);
  h_C1_JEUShiftUp->SetLineWidth(line_width);
  h_C1_JEUShiftDown->SetLineWidth(line_width);
  h_C1_centShiftCombined->SetLineWidth(line_width);
  h_C1_centShiftUp->SetLineWidth(line_width);
  h_C1_centShiftDown->SetLineWidth(line_width);
  h_C1_total->SetLineWidth(line_width);

  h_C1_cFraction->SetLineStyle(2);
  h_C1_lowerBound->SetLineStyle(3);
  h_C1_JERsmear->SetLineStyle(6);
  h_C1_bGS->SetLineStyle(7);
  h_C1_JEUShiftCombined->SetLineStyle(8);
  h_C1_JEUShiftUp->SetLineStyle(8);
  h_C1_JEUShiftDown->SetLineStyle(9);
  h_C1_centShiftCombined->SetLineStyle(4);
  h_C1_centShiftUp->SetLineStyle(4);
  h_C1_centShiftDown->SetLineStyle(5);  
  h_C1_total->SetLineStyle(1);


  // *****************************************************************************

  
  TCanvas *canv_pp = new TCanvas("canv_pp","canv_pp",800,800);
  canv_pp->cd();
  TPad *pad_pp = new TPad("pad_pp","pad_pp",0,0,1,1);
  pad_pp->SetLeftMargin(0.15);
  pad_pp->SetBottomMargin(0.15);
  pad_pp->Draw();
  pad_pp->cd();
  h_pp_total->GetYaxis()->SetRangeUser(0,0.4);
  h_pp_total->GetXaxis()->SetRangeUser(80,300);
  h_pp_total->SetTitle("");
  h_pp_total->SetStats(0);
  h_pp_total->GetXaxis()->SetTitle("#it{p}_{T}^{recoJet} [GeV]");
  h_pp_total->GetYaxis()->SetTitle("Systematic uncertainty");
  h_pp_total->Draw();
  h_pp_cFraction->Draw("same");
  h_pp_lowerBound->Draw("same");
  // h_pp_lowerBound->Fit("pol0");
  h_pp_JERsmear->Draw("same");
  // h_pp_JERsmear->Fit("pol0","M R","N",80,200);
  h_pp_bGS->Draw("same");
  h_pp_JEUShiftCombined->Draw("same");
  //h_pp_JEUShiftUp->Draw("same");
  // h_pp_JEUShiftDown->Draw("same");
  //h_pp_centShiftUp->Draw("same");
  //h_pp_centShiftDown->Draw("same");

  // std::pair<TGraphErrors*, TF1*> results = combineAndFitHistograms(h_pp_JEUShiftUp, h_pp_JEUShiftDown);
  // TGraphErrors* combined_graph = results.first;
  // TF1* fitted_function = results.second;
  // if (combined_graph && fitted_function) {
  //   std::cout << "\n--- Fit Results ---" << std::endl;
  //   std::cout << "Fit Constant (pol0 value): " << fitted_function->GetParameter(0) << std::endl;
  //   std::cout << "Fit Constant Error: " << fitted_function->GetParError(0) << std::endl;
  //   std::cout << "Chi2 / NDF: " << fitted_function->GetChisquare() << " / " << fitted_function->GetNDF() << std::endl;
  // }
  

  TLegend *leg_pp = new TLegend(0.52,0.65,0.78,0.88);
  leg_pp->SetBorderSize(0);
  leg_pp->SetTextSize(0.026);
  leg_pp->AddEntry(h_pp_total,"Total","l");
  leg_pp->AddEntry(h_pp_cFraction,"#it{c}-fraction","l");
  leg_pp->AddEntry(h_pp_lowerBound,"#it{p}_{T}^{rel} lower-bound","l");
  leg_pp->AddEntry(h_pp_JERsmear,"JER uncertainty","l");
  leg_pp->AddEntry(h_pp_bGS,"gluon-splitting uncertainty","l");
  leg_pp->AddEntry(h_pp_JEUShiftCombined,"JES uncertainty","l");
  //leg_pp->AddEntry(h_pp_JEUShiftUp,"JES uncertainty","l");
  //leg_pp->AddEntry(h_pp_JEUShiftDown,"JEU uncertainty \"down\" ","l");
  //leg_pp->AddEntry(h_pp_centShiftUp,"Centrality uncertainty","l");
  //leg_pp->AddEntry(h_pp_centShiftDown,"Centrality uncertainty \"down\" ","l");
  leg_pp->Draw();

  
  la->DrawLatexNDC(0.22,0.92,"#font[62]{CMS}#scale[0.8]{#font[52]{Preliminary}}            pp 5 TeV (301 pb^{-1})");
  

  // #############################################################

  
  TCanvas *canv_C4 = new TCanvas("canv_C4","canv_C4",800,800);
  canv_C4->cd();
  TPad *pad_C4 = new TPad("pad_C4","pad_C4",0,0,1,1);
  pad_C4->SetLeftMargin(0.2);
  pad_C4->SetBottomMargin(0.2);
  pad_C4->Draw();
  pad_C4->cd();
  h_C4_total->GetYaxis()->SetRangeUser(0,0.4);
  h_C4_total->GetXaxis()->SetRangeUser(80,300);
  h_C4_total->SetTitle("");
  h_C4_total->SetStats(0);
  h_C4_total->GetXaxis()->SetTitle("#it{p}_{T}^{recoJet} [GeV]");
  h_C4_total->GetYaxis()->SetTitle("Systematic uncertainty");
  h_C4_total->Draw();
  h_C4_cFraction->Draw("same");
  h_C4_lowerBound->Draw("same");
  // h_C4_lowerBound->Fit("pol0");
  h_C4_JERsmear->Draw("same");
  // h_C4_JERsmear->Fit("pol0","M R","N",80,200);
  h_C4_bGS->Draw("same");
  h_C4_JEUShiftCombined->Draw("same");
  //h_C4_JEUShiftUp->Draw("same");
  // h_C4_JEUShiftDown->Draw("same");
  h_C4_centShiftCombined->Draw("same");
  //h_C4_centShiftUp->Draw("same");
  //h_C4_centShiftDown->Draw("same");

  // std::pair<TGraphErrors*, TF1*> results_C4 = combineAndFitHistograms(h_C4_centShiftUp, h_C4_centShiftDown);
  // TGraphErrors* combined_graph_C4 = results_C4.first;
  // TF1* fitted_function_C4 = results_C4.second;
  // if (combined_graph_C4 && fitted_function_C4) {
  //   std::cout << "\n--- Fit Results ---" << std::endl;
  //   std::cout << "Fit Constant (pol0 value): " << fitted_function_C4->GetParameter(0) << std::endl;
  //   std::cout << "Fit Constant Error: " << fitted_function_C4->GetParError(0) << std::endl;
  //   std::cout << "Chi2 / NDF: " << fitted_function_C4->GetChisquare() << " / " << fitted_function_C4->GetNDF() << std::endl;
  // }


  TLegend *leg_C4 = new TLegend(0.52,0.65,0.78,0.88);
  leg_C4->SetBorderSize(0);
  leg_C4->SetTextSize(0.031);
  leg_C4->AddEntry(h_C4_total,"Total","l");
  leg_C4->AddEntry(h_C4_cFraction,"#it{c}-fraction","l");
  leg_C4->AddEntry(h_C4_lowerBound,"#it{p}_{T}^{rel} lower-bound","l");
  leg_C4->AddEntry(h_C4_JERsmear,"JER uncertainty","l");
  leg_C4->AddEntry(h_C4_bGS,"gluon-splitting uncertainty","l");
  leg_C4->AddEntry(h_C4_JEUShiftCombined,"JES uncertainty","l");
  //leg_C4->AddEntry(h_C4_JEUShiftUp,"JES uncertainty","l");
  //leg_C4->AddEntry(h_C4_JEUShiftDown,"JEU uncertainty \"down\" ","l");
  leg_C4->AddEntry(h_C4_centShiftCombined,"Centrality uncertainty","l");
  //leg_C4->AddEntry(h_C4_centShiftUp,"Centrality uncertainty","l");
  //leg_C4->AddEntry(h_C4_centShiftDown,"Centrality uncertainty \"down\" ","l");
  leg_C4->Draw();
  

  la->DrawLatexNDC(0.22,0.92,"#font[62]{CMS}#scale[0.8]{#font[52]{Preliminary}}    PbPb 50-80% 5 TeV (1.689 nb^{-1})");

  // #############################################################

  
  TCanvas *canv_C3 = new TCanvas("canv_C3","canv_C3",800,800);
  canv_C3->cd();
  TPad *pad_C3 = new TPad("pad_C3","pad_C3",0,0,1,1);
  pad_C3->SetLeftMargin(0.2);
  pad_C3->SetBottomMargin(0.2);
  pad_C3->Draw();
  pad_C3->cd();
  h_C3_total->GetYaxis()->SetRangeUser(0,0.4);
  h_C3_total->GetXaxis()->SetRangeUser(80,300);
  h_C3_total->SetTitle("");
  h_C3_total->SetStats(0);
  h_C3_total->GetXaxis()->SetTitle("#it{p}_{T}^{recoJet} [GeV]");
  h_C3_total->GetYaxis()->SetTitle("Systematic uncertainty");
  h_C3_total->Draw();
  h_C3_cFraction->Draw("same");
  h_C3_lowerBound->Draw("same");
  // h_C3_lowerBound->Fit("pol0");
  h_C3_JERsmear->Draw("same");
  // h_C3_JERsmear->Fit("pol0","M R","N",80,200);
  h_C3_bGS->Draw("same");
  h_C3_JEUShiftCombined->Draw("same");
  //h_C3_JEUShiftUp->Draw("same");
  // h_C3_JEUShiftDown->Draw("same");
  h_C3_centShiftCombined->Draw("same");
  //h_C3_centShiftUp->Draw("same");
  //h_C3_centShiftDown->Draw("same");

  // std::pair<TGraphErrors*, TF1*> results_C3 = combineAndFitHistograms(h_C3_centShiftUp, h_C3_centShiftDown);
  // TGraphErrors* combined_graph_C3 = results_C3.first;
  // TF1* fitted_function_C3 = results_C3.second;
  // if (combined_graph_C3 && fitted_function_C3) {
  //   std::cout << "\n--- Fit Results ---" << std::endl;
  //   std::cout << "Fit Constant (pol0 value): " << fitted_function_C3->GetParameter(0) << std::endl;
  //   std::cout << "Fit Constant Error: " << fitted_function_C3->GetParError(0) << std::endl;
  //   std::cout << "Chi2 / NDF: " << fitted_function_C3->GetChisquare() << " / " << fitted_function_C3->GetNDF() << std::endl;
  // }


  TLegend *leg_C3 = new TLegend(0.52,0.65,0.78,0.88);
  leg_C3->SetBorderSize(0);
  leg_C3->SetTextSize(0.031);
  leg_C3->AddEntry(h_C3_total,"Total","l");
  leg_C3->AddEntry(h_C3_cFraction,"#it{c}-fraction","l");
  leg_C3->AddEntry(h_C3_lowerBound,"#it{p}_{T}^{rel} lower-bound","l");
  leg_C3->AddEntry(h_C3_JERsmear,"JER uncertainty","l");
  leg_C3->AddEntry(h_C3_bGS,"gluon-splitting uncertainty","l");
  leg_C3->AddEntry(h_C3_JEUShiftCombined,"JES uncertainty","l");
  //leg_C3->AddEntry(h_C3_JEUShiftUp,"JES uncertainty","l");
  //leg_C3->AddEntry(h_C3_JEUShiftDown,"JEU uncertainty \"down\" ","l");
  leg_C3->AddEntry(h_C3_centShiftCombined,"Centrality uncertainty","l");
  //leg_C3->AddEntry(h_C3_centShiftUp,"Centrality uncertainty","l");
  //leg_C3->AddEntry(h_C3_centShiftDown,"Centrality uncertainty \"down\" ","l");
  leg_C3->Draw();
  

  la->DrawLatexNDC(0.22,0.92,"#font[62]{CMS}#scale[0.8]{#font[52]{Preliminary}}    PbPb 30-50% 5 TeV (1.689 nb^{-1})");

  

  ///////////////////////////////////////////////////////////////////////////////////////////////////////

  TCanvas *canv_C2 = new TCanvas("canv_C2","canv_C2",800,800);
  canv_C2->cd();
  TPad *pad_C2 = new TPad("pad_C2","pad_C2",0,0,1,1);
  pad_C2->SetLeftMargin(0.2);
  pad_C2->SetBottomMargin(0.2);
  pad_C2->Draw();
  pad_C2->cd();
  h_C2_total->GetYaxis()->SetRangeUser(0,0.4);
  h_C2_total->GetXaxis()->SetRangeUser(80,300);
  h_C2_total->SetTitle("");
  h_C2_total->SetStats(0);
  h_C2_total->GetXaxis()->SetTitle("#it{p}_{T}^{recoJet} [GeV]");
  h_C2_total->GetYaxis()->SetTitle("Systematic uncertainty");
  h_C2_total->Draw();
  h_C2_cFraction->Draw("same");
  h_C2_lowerBound->Draw("same");
  // h_C2_lowerBound->Fit("pol0");
  h_C2_JERsmear->Draw("same");
  // h_C2_JERsmear->Fit("pol0","M R","N",80,200);
  h_C2_bGS->Draw("same");
  h_C2_JEUShiftCombined->Draw("same");
  //h_C2_JEUShiftUp->Draw("same");
  // h_C2_JEUShiftDown->Draw("same");
  h_C2_centShiftCombined->Draw("same");
  //h_C2_centShiftUp->Draw("same");
  //h_C2_centShiftDown->Draw("same");

  // std::pair<TGraphErrors*, TF1*> results_C2 = combineAndFitHistograms(h_C2_centShiftUp, h_C2_centShiftDown);
  // TGraphErrors* combined_graph_C2 = results_C2.first;
  // TF1* fitted_function_C2 = results_C2.second;
  // if (combined_graph_C2 && fitted_function_C2) {
  //   std::cout << "\n--- Fit Results ---" << std::endl;
  //   std::cout << "Fit Constant (pol0 value): " << fitted_function_C2->GetParameter(0) << std::endl;
  //   std::cout << "Fit Constant Error: " << fitted_function_C2->GetParError(0) << std::endl;
  //   std::cout << "Chi2 / NDF: " << fitted_function_C2->GetChisquare() << " / " << fitted_function_C2->GetNDF() << std::endl;
  // }

  TLegend *leg_C2 = new TLegend(0.52,0.65,0.78,0.88);
  leg_C2->SetBorderSize(0);
  leg_C2->SetTextSize(0.031);
  leg_C2->AddEntry(h_C2_total,"Total","l");
  leg_C2->AddEntry(h_C2_cFraction,"#it{c}-fraction","l");
  leg_C2->AddEntry(h_C2_lowerBound,"#it{p}_{T}^{rel} lower-bound","l");
  leg_C2->AddEntry(h_C2_JERsmear,"JER uncertainty","l");
  leg_C2->AddEntry(h_C2_bGS,"gluon-splitting uncertainty","l");
  leg_C2->AddEntry(h_C2_JEUShiftCombined,"JES uncertainty","l");
  //leg_C2->AddEntry(h_C2_JEUShiftUp,"JES uncertainty","l");
  //leg_C2->AddEntry(h_C2_JEUShiftDown,"JEU uncertainty \"down\" ","l");
  leg_C2->AddEntry(h_C2_centShiftCombined,"Centrality uncertainty","l");
  //leg_C2->AddEntry(h_C2_centShiftUp,"Centrality uncertainty","l");
  //leg_C2->AddEntry(h_C2_centShiftDown,"Centrality uncertainty \"down\" ","l");
  leg_C2->Draw();
  

  la->DrawLatexNDC(0.22,0.92,"#font[62]{CMS}#scale[0.8]{#font[52]{Preliminary}}    PbPb 10-30% 5 TeV (1.689 nb^{-1})");


///////////////////////////////////////////////////////////////////////////////////////////////////////

  TCanvas *canv_C1 = new TCanvas("canv_C1","canv_C1",800,800);
  canv_C1->cd();
  TPad *pad_C1 = new TPad("pad_C1","pad_C1",0,0,1,1);
  pad_C1->SetLeftMargin(0.2);
  pad_C1->SetBottomMargin(0.2);
  pad_C1->Draw();
  pad_C1->cd();
  h_C1_total->GetYaxis()->SetRangeUser(0,0.4);
  h_C1_total->GetXaxis()->SetRangeUser(80,300);
  h_C1_total->SetTitle("");
  h_C1_total->SetStats(0);
  h_C1_total->GetXaxis()->SetTitle("#it{p}_{T}^{recoJet} [GeV]");
  h_C1_total->GetYaxis()->SetTitle("Systematic uncertainty");
  h_C1_total->Draw();
  h_C1_cFraction->Draw("same");
  h_C1_lowerBound->Draw("same");
  // h_C1_lowerBound->Fit("pol0");
  h_C1_JERsmear->Draw("same");
  // h_C1_JERsmear->Fit("pol0","M R","N",80,200);
  h_C1_bGS->Draw("same");
  h_C1_JEUShiftCombined->Draw("same");
  //h_C1_JEUShiftUp->Draw("same");
  // h_C1_JEUShiftDown->Draw("same");
  h_C1_centShiftCombined->Draw("same");
  //h_C1_centShiftUp->Draw("same");
  //h_C1_centShiftDown->Draw("same");

  // std::pair<TGraphErrors*, TF1*> results_C1 = combineAndFitHistograms(h_C1_centShiftUp, h_C1_centShiftDown);
  // TGraphErrors* combined_graph_C1 = results_C1.first;
  // TF1* fitted_function_C1 = results_C1.second;
  // if (combined_graph_C1 && fitted_function_C1) {
  //   std::cout << "\n--- Fit Results ---" << std::endl;
  //   std::cout << "Fit Constant (pol0 value): " << fitted_function_C1->GetParameter(0) << std::endl;
  //   std::cout << "Fit Constant Error: " << fitted_function_C1->GetParError(0) << std::endl;
  //   std::cout << "Chi2 / NDF: " << fitted_function_C1->GetChisquare() << " / " << fitted_function_C1->GetNDF() << std::endl;
  // }
  

  TLegend *leg_C1 = new TLegend(0.52,0.65,0.78,0.88);
  leg_C1->SetBorderSize(0);
  leg_C1->SetTextSize(0.031);
  leg_C1->AddEntry(h_C1_total,"Total","l");
  leg_C1->AddEntry(h_C1_cFraction,"#it{c}-fraction","l");
  leg_C1->AddEntry(h_C1_lowerBound,"#it{p}_{T}^{rel} lower-bound","l");
  leg_C1->AddEntry(h_C1_JERsmear,"JER uncertainty","l");
  leg_C1->AddEntry(h_C1_bGS,"gluon-splitting uncertainty","l");
  leg_C1->AddEntry(h_C1_JEUShiftCombined,"JES uncertainty","l");
  //leg_C1->AddEntry(h_C1_JEUShiftUp,"JES uncertainty","l");
  //leg_C1->AddEntry(h_C1_JEUShiftDown,"JEU uncertainty \"down\" ","l");
  leg_C1->AddEntry(h_C1_centShiftCombined,"Centrality uncertainty","l");
  //leg_C1->AddEntry(h_C1_centShiftUp,"Centrality uncertainty","l");
  //leg_C1->AddEntry(h_C1_centShiftDown,"Centrality uncertainty \"down\" ","l");
  leg_C1->Draw();
  

  la->DrawLatexNDC(0.22,0.92,"#font[62]{CMS}#scale[0.8]{#font[52]{Preliminary}}    PbPb 0-10% 5 TeV (1.689 nb^{-1})");


  canv_pp->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/systematics/nice-plots/pp.pdf");
  canv_C4->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/systematics/nice-plots/C4.pdf");
  canv_C3->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/systematics/nice-plots/C3.pdf");
  canv_C2->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/systematics/nice-plots/C2.pdf");
  canv_C1->SaveAs("/home/clayton/Analysis/code/bJetMuonTaggingAnalysis/figures/systematics/nice-plots/C1.pdf");



  

}
