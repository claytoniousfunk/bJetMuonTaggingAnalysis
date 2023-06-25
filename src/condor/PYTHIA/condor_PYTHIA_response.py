from myProcesses.condor.condor_utility import jobManager

jobname = 'PYTHIA_response'

#put the file list here
dblist = '../../../fileNames/fileNames_PYTHIA_DiJet.txt'

exe = 'PYTHIA_response_bJets.C'

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
