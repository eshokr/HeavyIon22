import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
                                # replace 'myfile.root' with the source file you want to use
                                fileNames = cms.untracked.vstring(
       #   'file:skimmed.root'
#'file:Photon.root'
#'root://cms-xrd-global.cern.ch//store/hidata/HIRun2022A/HITestRaw0/AOD/PromptReco-v1/000/362/318/00000/3fb50183-105d-46d8-9c44-95fd1b2ae44a.root'
'/store/user/eshokr/output/HITestRaw9/skimming/230309_202833/0000/skimmed_105.root'
           )
                            )

process.demo = cms.EDAnalyzer('DemoAnalyzer',
   tracks    = cms.untracked.InputTag('muons')#standAloneMuons')#'generalTracks')#'globalMuons')#'standAloneMuons')#'globalMuons')#'generalTracks')
                             )

process.TFileService = cms.Service("TFileService",
fileName = cms.string("output.root")
)

process.p = cms.Path(process.demo)
