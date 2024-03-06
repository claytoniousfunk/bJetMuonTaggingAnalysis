/* 

This function will take in a TH2D where
- the y-axis is the flavor, an integer from -5 to 21
- the x-axis is the mu-pTrel in GeV

input = TH2D
ouput = TH1D (projection) of the desired flavor 
flavor_flag = integer indicating desired flavor projection

*/

TH1D *h_out;
TH1D *bin_finder;
double small_shift;

TH1D* project_flavor(TH2D* H_in, int flavor_flag){

  bin_finder = (TH1D*) H_in->ProjectionY();
  small_shift = 0.01;

  h_out = (TH1D*) H_in->ProjectionX("h_out",bin_finder->FindBin(1.0*flavor_flag + small_shift),bin_finder->FindBin(1.0*(flavor_flag+1) - small_shift));

  return h_out;

}
