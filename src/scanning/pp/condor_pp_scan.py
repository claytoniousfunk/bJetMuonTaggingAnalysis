from myProcesses.condor.condor_utility import jobManager

jobname = 'pp_SingleMuon_scan'

#put the file list here
dblist = '../../../fileNames/fileNames_pp_SingleMuon_24Oct23.txt'
#dblist = '../../../fileNames/fileNames_pp_MinBias.txt'

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
jm.nsplit = 5 
jm.make_tarball = False
jm.generate_cfg()
jm.submit()
