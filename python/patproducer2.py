
import FWCore.ParameterSet.Config as cms

# Define the process
process = cms.Process("PAT")

# Load the PAT sequences
#process.load("PhysicsTools.PatAlgos.patSequences_cff")

# Load the PAT standalone trigger producer
process.load("PhysicsTools.PatAlgos.triggerLayer1.triggerProducer_cff")

# Define the input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('file:skimmed.root')
)

# Define the path that will run the PAT sequences
process.p = cms.Path(
    process.patDefaultSequence +
    process.patTriggerSequence
)

# Configure the PAT standalone trigger producer
process.patTrigger.standalone = cms.bool(True)
process.patTrigger.processName = cms.string('HLT')
process.patTrigger.triggerResults = cms.InputTag('TriggerResults', '', 'HLT')
process.patTrigger.triggerEvent = cms.InputTag('hltTriggerSummaryAOD', '', 'HLT')

# Define the output
process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('pat.root'),
    outputCommands = cms.untracked.vstring('keep *')
)

# Endpath
process.outpath = cms.EndPath(process.out)

