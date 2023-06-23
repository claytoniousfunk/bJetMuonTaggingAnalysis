from myProcesses.condor.condor_utility import jobManager

jobname = 'pp_scan'

#put the file list here
dblist = '/afs/cern.ch/user/c/cbennett/condorSkim/fileNames/fileNames_pp_SingleMuon_19Dec22.txt'
#dblist = '/afs/cern.ch/user/c/cbennett/condorSkim/fileNames/fileNames_pp_MB_1May23.txt'
#dblist = '/afs/cern.ch/user/c/cbennett/condorSkim/fileNames/fileNames_pp_MB_4_12Jun23.txt'

exe = 'pp_scan.C'

jm = jobManager(jobSite ='cern', 
	jobname = jobname, 	
	method = 'root',
	executable = exe, 
	runlist = dblist,
	time = '8h',
	output_dir = ''
)

#how many files for each jobs
jm.nsplit = 1 
jm.make_tarball = False
jm.generate_cfg()
jm.submit()
