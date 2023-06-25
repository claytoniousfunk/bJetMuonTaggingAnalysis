from myProcesses.condor.condor_utility import jobManager

jobname = 'PbPb_SingleMuon_scan'

#put the file list here
dblist = '../../../fileNames/fileNames_PbPb_SingleMuon.txt'
#dblist = '../../../fileNames/fileNames_PbPb_MinBias.txt'

exe = 'PbPb_scan.C'

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
