#include "./correctionFactorsCalculator.h"

void generateCorrections(){

  cout << endl;
  cout << "[generateCorrections] ##########  GENERATING CORRECTION FACTORS ##############" << endl;
  cout << endl;

  cout << "[generateCorrections]...generating for pp..." << endl;
  correctionFactorsCalculator(1, 0, 0);
  cout << "[generateCorrections]...done!" << endl;

  cout << "[generateCorrections]...generating for PbPb 30-90%..." << endl;
  correctionFactorsCalculator(0, 1, 0);
  cout << "[generateCorrections]...done!" << endl;

  cout << "[generateCorrections]...generating for PbPb 0-30%..." << endl;
  correctionFactorsCalculator(0, 0, 1);
  cout << "[generateCorrections]...done!" << endl;




}
