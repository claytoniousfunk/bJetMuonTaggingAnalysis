from myProcesses.condor.condor_utility import jobManager

jobname = 'PbPb_SingleMuon_scan'

#put the file list here
dblist = '/afs/cern.ch/user/c/cbennett/condorSkim/fileNames/fileNames_PbPb_SingleMuon_19Dec22.txt'
#dblist = '/afs/cern.ch/user/c/cbennett/condorSkim/fileNames/fileNames_PbPb_MB_0_20Mar23.txt'
#dblist = '/afs/cern.ch/user/c/cbennett/condorSkim/fileNames/fileNames_PbPb_minBias_collection.txt'

exe = 'PbPb_scan.C'
#exe = 'PbPb_scan_V3p7_JERsmear.C'

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
