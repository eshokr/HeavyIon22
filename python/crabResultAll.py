from WMCore.Configuration import Configuration
from CRABClient.UserUtilities import config
from CRABAPI.RawCommand import crabCommand

config = config()

config.General.workArea = 'crab_projects_finalresult'
config.General.transferOutputs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'configurationTestOnMuons.py' #'confTest.py'

config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 20
#config.Data.lumiMask = 'https://cms-service-dqmdc.web.cern.ch/CAF/certification/Collisions16/13TeV/Cert_271036-275783_13TeV_PromptReco_Collisions16_JSON.txt'
#config.Data.runRange = '275776-275782'
config.Data.publication = True
config.Data.outputDatasetTag = 'skimming'

config.Site.storageSite = 'T3_CH_PSI'
config.JobType.outputFiles = ['output.root']
config.Data.outLFNDirBase = '/store/user/eshokr/output'
config.General.requestName = 'outputfinal'


config.Data.inputDataset = '/HITestRaw19/eshokr-skimming-15b9e542cc06e4b19568c2c8102b3fb9/USER'
#for i, dataset in enumerate(datasets):
#    request_name = f'skim_{i}'
#    config.General.requestName = request_name
#    config.Data.inputDataset = dataset
#    crabCommand('submit', config=config)

