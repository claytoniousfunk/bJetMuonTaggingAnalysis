from myProcesses.condor.condor_utility import jobManager

jobname = 'PYTHIAHYDJET_DiJet_scan'

#put the file list here
dblist = '/afs/cern.ch/user/c/cbennett/condorSkim/fileNames/fileNames_PH_DiJet_20Feb23.txt'
#dblist = '/afs/cern.ch/user/c/cbennett/condorSkim/fileNames/fileNames_PH_MuJet_27Feb23.txt'
#dblist = '/afs/cern.ch/user/c/cbennett/condorSkim/fileNames/fileNames_PYTHIAHYDJET_MuJet_5Jun23.txt'
#dblist = '/afs/cern.ch/user/c/cbennett/condorSkim/fileNames/fileNames_PYTHIAHYDJET_DiJet_onlyMuJets_noRecoJetPtCut_5Jun23.txt'
#dblist = '/afs/cern.ch/user/c/cbennett/condorSkim/fileNames/fileNames_PH_BJet_23Feb23.txt'


exe = 'PYTHIAHYDJET_scan.C'
#exe = 'PYTHIAHYDJET_scan_V3p7_JEU.C'
#exe = 'PYTHIAHYDJET_scan_V3p7_JERsmear.C'
#exe = 'PYTHIAHYDJET_scan_response_v2.C'
#exe = 'PYTHIAHYDJET_scan_response_v2_bJets.C'
#exe = 'PYTHIAHYDJET_scan_response_v2_JERsmear.C'
#exe = 'PYTHIAHYDJET_scan_V3p7_noVzWeight_noHiBinWeight.C'
#exe = 'PYTHIAHYDJET_scan_V3p7_noVzWeight.C'
#exe = 'PYTHIAHYDJET_scan_V3p7_mugenfilter_emulation.C'

jm = jobManager(jobSite ='cern', 
	jobname = jobname, 	
	method = 'root',
	executable = exe, 
	runlist = dblist,
	time = '8h',
	output_dir = ''
)

#how many files for each jobs
jm.nsplit = 5 
jm.make_tarball = False
jm.generate_cfg()
jm.submit()
