from CRABClient.UserUtilities import config
config = config()

config.General.requestName = 'TTbarFCNC_cZpbW_MyFCNCkitMC3'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
#config.JobType.generator = 'lhe'
config.JobType.psetName = 'patRefSel_MC_cfg.py'
#config.JobType.inputFiles = ['dynlo.lhe']
config.Data.ignoreLocality = True
#config.Site.ignoreCrab3blacklist = True
#config.Site.whitelist = ['T2_US*']
#config.Site.whitelist = ['T2_TW_NCHC']
config.Site.whitelist = ['T3_TW_NTU_HEP']
#config.Site.blacklist = ['T2_IT_Legnaro']

config.Data.inputDataset = '/TTbarFCNCcZpbW/yuanchao-MC_PATv2-2t-387ce20ab3250374874491bf136d6c14/USER'
#config.Data.inputDataset = '/TTbarFCNCcZpbW/yuanchao-MC_PATv2-2-387ce20ab3250374874491bf136d6c14/USER'
config.Data.inputDBS = 'phys03'
#config.Data.outputPrimaryDataset = 'TTbarFCNCcZpbW'
#config.Data.splitting = 'EventBased'
#JOB_WALLTIME = 8*3600
#TIME_PER_EVENT = 12.91
##config.Data.unitsPerJob = int(JOB_WALLTIME / TIME_PER_EVENT)
#config.Data.unitsPerJob = 5000
#NJOBS = 20
#config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 5
config.Data.totalUnits = 5
#config.Data.outLFNDirBase = '/store/user/%s/mc1/' % (getUsernameFromSiteDB())
config.Data.outLFNDirBase = '/store/user/yuanchao/mc/'
#config.Data.publication = True
config.Data.publication = False
#config.Data.outputDatasetTag = 'MC_LHE-1'
config.Data.outputDatasetTag = 'MC_Ntuple3'

config.Site.storageSite = 'T3_TW_NTU_HEP'
#config.Site.storageSite = 'T2_TW_NCHC'
