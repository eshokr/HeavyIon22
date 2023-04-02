from WMCore.Configuration import Configuration
from CRABClient.UserUtilities import config
from CRABAPI.RawCommand import crabCommand

config = config()

config.General.workArea = 'crab_projects'
config.General.transferOutputs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'confTest.py'

config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 20
#config.Data.lumiMask = 'https://cms-service-dqmdc.web.cern.ch/CAF/certification/Collisions16/13TeV/Cert_271036-275783_13TeV_PromptReco_Collisions16_JSON.txt'
#config.Data.runRange = '275776-275782'
config.Data.publication = True
config.Data.outputDatasetTag = 'skimming'

config.Site.storageSite = 'T3_CH_PSI'
config.JobType.outputFiles = ['skimmed.root']
config.Data.outLFNDirBase = '/store/user/eshokr/output'


datasets = [f"/HITestRaw{i}/HIRun2022A-PromptReco-v1/AOD" for i in range(24)]

for i, dataset in enumerate(datasets):
    request_name = f'skim_{i}'
    config.General.requestName = request_name
    config.Data.inputDataset = dataset
    crabCommand('submit', config=config)

