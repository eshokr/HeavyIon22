
from CRABClient.UserUtilities import config
from CRABAPI.RawCommand import crabCommand
#from WMCore.Configuration import Configuration
import glob
import os

# Define the CMSSW configuration file
config_file = 'confResult.py'

# Define the CRAB configuration
crab_config = config()
crab_config.General.requestName = 'my_crab_job'
crab_config.General.workArea = 'crabFinalResult'

# Configure the output files
crab_config.JobType.pluginName = 'Analysis'
crab_config.JobType.psetName = config_file
crab_config.JobType.outputFiles = ['output.root']

# Configure the storage site and the number of jobs
crab_config.Site.storageSite = 'T3_CH_PSI'
#crab_config.Data.unitsPerJob = 10

# Add the input files
input_files = []
for i in range(24):
    for j in range(1, 12):
        input_files.extend(glob.glob('/afs/cern.ch/work/e/eshokr/EXOVVNtuplizerRunII/CMSSW_12_5_2_patch1/src/HeavyIonsAnalysis/DemoAnalyzer/output/HITestRaw{i}/skimming/2*/0000/skimmed_{j}.root'.format(i=i, j=j)))

crab_config.Data.inputFiles = input_files

# Submit the job
crabCommand('submit', config=crab_config)

