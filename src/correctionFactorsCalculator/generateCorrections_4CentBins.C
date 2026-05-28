#include "./correctionFactorsCalculator_4CentBins.h"

void generateCorrections_4CentBins(){

  cout << endl;
  cout << "[generateCorrections] ##########  GENERATING CORRECTION FACTORS ##############" << endl;
  cout << endl;

  cout << "[generateCorrections]...generating for pp..." << endl;
  correctionFactorsCalculator(1, 0, 0, 0, 0);
  cout << "[generateCorrections]...done!" << endl;

  cout << "[generateCorrections]...generating for PbPb 50-80%..." << endl;
  correctionFactorsCalculator(0, 1, 0, 0, 0);
  cout << "[generateCorrections]...done!" << endl;
  
  cout << "[generateCorrections]...generating for PbPb 30-50%..." << endl;
  correctionFactorsCalculator(0, 0, 1, 0, 0);
  cout << "[generateCorrections]...done!" << endl;

  cout << "[generateCorrections]...generating for PbPb 10-30%..." << endl;
  correctionFactorsCalculator(0, 0, 0, 1, 0);
  cout << "[generateCorrections]...done!" << endl;

  cout << "[generateCorrections]...generating for PbPb 0-10%..." << endl;
  correctionFactorsCalculator(0, 0, 0, 0, 1);
  cout << "[generateCorrections]...done!" << endl;




}
