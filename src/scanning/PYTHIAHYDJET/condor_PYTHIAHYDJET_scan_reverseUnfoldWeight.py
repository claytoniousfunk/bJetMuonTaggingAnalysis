from myProcesses.condor.condor_utility import jobManager

jobname = 'PYTHIAHYDJET_DiJet_reverseUnfoldWeight_scan'

#put the file list here
dblist = '../../../fileNames/fileNames_PYTHIAHYDJET_DiJet.txt'
#dblist = '../../../fileNames/fileNames_PYTHIAHYDJET_BJet.txt'
#dblist = '../../../fileNames/fileNames_PYTHIAHYDJET_BJet_onlyMuonTaggedJets.txt'
#dblist = '../../../fileNames/fileNames_PYTHIAHYDJET_MuJet.txt'
#dblist = '../../../fileNames/fileNames_PYTHIAHYDJET_DiJet_onlyMuJets_noRecoJetPtCut.txt'



exe = 'PYTHIAHYDJET_scan_reverseUnfoldWeight.C'

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
