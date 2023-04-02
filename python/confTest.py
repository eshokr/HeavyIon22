import FWCore.ParameterSet.Config as cms

process = cms.Process("SKIM")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(

#'root://cms-xrd-global.cern.ch//store/hidata/HIRun2022A/HITestRaw0/AOD/PromptReco-v1/000/362/318/00000/06d04439-5784-498c-a4af-3fffc3545a96.root',
#'root://cms-xrd-global.cern.ch//store/hidata/HIRun2022A/HITestRaw0/AOD/PromptReco-v1/000/362/318/00000/1077f7d6-e4cc-49cd-8d15-f4d145e9f869.root',
'root://cms-xrd-global.cern.ch//store/hidata/HIRun2022A/HITestRaw0/AOD/PromptReco-v1/000/362/318/00000/22e8fcab-0b8f-4504-8b38-3c99e95bf833.root',
'root://cms-xrd-global.cern.ch//store/hidata/HIRun2022A/HITestRaw0/AOD/PromptReco-v1/000/362/318/00000/3fb50183-105d-46d8-9c44-95fd1b2ae44a.root',


#       '/store/data/Run2018D/JetHT/MINIAOD/12Nov2019_UL2018-v2/260000/FF78C3F3-C3AB-0243-81E6-6805A5DE1A5A.root'
#'root://cms-xrd-global.cern.ch//store/hidata/HIRun2022A/HITestRaw0/AOD/PromptReco-v1/000/362/318/00000/3fb50183-105d-46d8-9c44-95fd1b2ae44a.root',
          #  'file:/afs/cern.ch/cms/Tutorials/workbook_twiki2021/MinBias_pythia8_14TeV_100events.root'

   )
)

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))

process.triggerSelection = cms.EDFilter("TriggerResultsFilter",
    triggerConditions = cms.vstring('HLT_HIUPC_SingleMuOpen_NotMBHF2AND_v4'),#'HLT_HIUPC_SingleMuOpen_OR_SingleMuCosmic_EMTF_NotMBHF2AND_v2'),
    hltResults = cms.InputTag('TriggerResults', '', 'HLT'),
    l1tResults = cms.InputTag(''),
    throw = cms.bool(True)
)

process.skimmedOutput = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('skimmed.root'),
    SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('triggerPath')),
    outputCommands = cms.untracked.vstring('keep *')
)

#########################################################################
# Muon filter
process.goodMuons = cms.EDFilter("MuonSelector",
   src = cms.InputTag("muons"),
   cut = cms.string('pt > 3.0 && ( isGlobalMuon=1 || isTrackerMuon=1)'),
   filter = cms.bool(True)
 )

process.triggerPath = cms.Path(process.triggerSelection)# + process.goodMuons)

process.endPath = cms.EndPath(process.skimmedOutput)

