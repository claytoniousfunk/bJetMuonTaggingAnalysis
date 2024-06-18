void loadFitFxn_PYTHIA_bJetNeutrinoEnergy(){
  fitFxn_PYTHIA_bJetNeutrinoEnergy = new TF1("fitFxn_PYTHIA_bJetNeutrinoEnergy","[0] + [1]*x + [2]*x*x + [3]/x + [4]/(x*x)",0,500);
  fitFxn_PYTHIA_bJetNeutrinoEnergy->SetParameter(0,bJetNeutrinoEnergyFitParam_0);
  fitFxn_PYTHIA_bJetNeutrinoEnergy->SetParameter(1,bJetNeutrinoEnergyFitParam_1);
  fitFxn_PYTHIA_bJetNeutrinoEnergy->SetParameter(2,bJetNeutrinoEnergyFitParam_2);
  fitFxn_PYTHIA_bJetNeutrinoEnergy->SetParameter(3,bJetNeutrinoEnergyFitParam_3);
  fitFxn_PYTHIA_bJetNeutrinoEnergy->SetParameter(4,bJetNeutrinoEnergyFitParam_4);

}
