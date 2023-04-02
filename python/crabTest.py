#from WMCore.Configuration import Configuration
from CRABClient.UserUtilities import config
from CRABAPI.RawCommand import crabCommand

config= config()

config.General.requestName = 'skim'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True

config.JobType.pluginName = 'ANALYSIS'
config.JobType.psetName = 'confTest.py'

config.Data.inputDataset = '/HITestRaw0/HIRun2022A-PromptReco-v1/AOD'
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 20
#config.Data.lumiMask = 'https://cms-service-dqmdc.web.cern.ch/CAF/certification/Collisions16/13TeV/Cert_271036-275783_13TeV_PromptReco_Collisions16_JSON.txt'
#config.Data.runRange = '275776-275782'
config.Data.publication = True
config.Data.outputDatasetTag = 'CRAB3_tutorial_Aug2021_Data_analysis'

config.Site.storageSite = 'T3_CH_PSI'
