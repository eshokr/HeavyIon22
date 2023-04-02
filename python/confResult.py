import FWCore.ParameterSet.Config as cms
import glob

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.options = cms.untracked.PSet(
    SkipEvent = cms.untracked.vstring('ProductNotFound')
)

"""process.source = cms.Source("PoolSource",
                                # replace 'myfile.root' with the source file you want to use
                                fileNames = cms.untracked.vstring(
       #   'file:skimmed.root'
#'file:Photon.root'
#'root://cms-xrd-global.cern.ch//store/hidata/HIRun2022A/HITestRaw0/AOD/PromptReco-v1/000/362/318/00000/3fb50183-105d-46d8-9c44-95fd1b2ae44a.root'
#'root://cms-xrd-global.cern.ch//store/user/eshokr/output/HITestRaw9/skimming/230309_202833/0000/skimmed_105.root'
#'file:../output/output_19/skimmed_*.root' 
#'file:/pnfs/psi.ch/cms/trivcat/store/user/eshokr/output/HITestRaw10/skimming/230309_202838/0000/skimmed_{}.root'.format(i) for i in range(1,171)

#'file:/pnfs/psi.ch/cms/trivcat/store/user/eshokr/output/HITestRaw10/skimming/230309_202838/0000/skimmed_{}.root'..format(i=i, j=j) for i in range(24) for j in range(1, 172)


#'file:../output/HITestRaw{i}/skimming/230309_202747/0000/skimmed_{j}.root'.format(i=i, j=j) for i in range(24) for j in range(1, 172)
#glob.glob('file:/afs/cern.ch/work/e/eshokr/EXOVVNtuplizerRunII/CMSSW_12_5_2_patch1/src/HeavyIonsAnalysis/DemoAnalyzer/output/HITestRaw{i}/skimming/2*/0000/skimmed_{j}.root').format(i=i, j=j) for i in range(24) for j in range(1, 12)

glob.glob('file:/pnfs/psi.ch/cms/trivcat/store/user/eshokr/output/HITestRaw{i}/skimming/2*/0000/skimmed_{j}.root').format(i=i, j=j) for i in range(4) for j in range(1, 171)
       
  )
          )  """                 

"""
process.source = cms.Source("PoolSource",
                             fileNames = cms.untracked.vstring([
                                 'file:' + f for i in range(19,21) for j in range(1, 171)
                                 for f in glob.glob('/pnfs/psi.ch/cms/trivcat/store/user/eshokr/output/HITestRaw{i}/skimming/2*/0000/skimmed_{j}.root'.format(i=i, j=j))
                             ])
                            )
"""
process.source = cms.Source("PoolSource",

                            fileNames = cms.untracked.vstring(
#'root://cms-xrd-global.cern.ch//store/hidata/HIRun2022A/HITestRaw0/AOD/PromptReco-v1/000/362/318/00000/3fb50183-105d-46d8-9c44-95fd1b2ae44a.root'

#'root://cms-xrd-global.cern.ch//store/hidata/HIRun2022A/HITestRaw0/AOD/PromptReco-v1/000/362/219/00000/d0a95156-a786-4e2c-8549-2a39e5f293c0.root'

'root://cms-xrd-global.cern.ch//store/hidata/HIRun2018A/HIForward/AOD/04Apr2019-v1/00000/0B11978B-DB98-9A4F-AFC2-6372CB68D9E8.root'

#'root://cms-xrd-global.cern.ch//store/hidata/HIRun2018A/HIForward/MINIAOD/PbPb18_MiniAODv1-v1/100000/01187bcd-b4a9-4bc9-b04c-e4b4bc9f241f.root'
#'file:skimmed.root'
)
                            )

#process.source = cms.Source("PoolSource",
                                # replace 'myfile.root' with the source file you want to use
 #                               fileNames = cms.untracked.vstring(
  #                                  *[f'file:{f}' for f in glob.glob('/afs/cern.ch/work/e/eshokr/EXOVVNtuplizerRunII/CMSSW_12_5_2_patch1/src/HeavyIonsAnalysis/DemoAnalyzer/output/HITestRaw{i}/skimming/2*/0000/skimmed_{j}.root'.format(i=i, j=j) for i in range(24) for j in range(1, 12))]
   #      )
    #      )

#process.source = cms.Source("PoolSource",
#                             fileNames = cms.untracked.vstring([
#                                 'file:' + f for i in range(5) for j in range(1, 171) 
##                                 for f in glob.glob('/afs/cern.ch/work/e/eshokr/EXOVVNtuplizerRunII/CMSSW_12_5_2_patch1/src/HeavyIonsAnalysis/DemoAnalyzer/output/HITestRaw{i}/skimming/2*/0000/skimmed_{j}.root'.format(i=i, j=j))
 #                            ])
  #                          )
process.calo = cms.EDAnalyzer('DemoAnalyzerCalo',
   #hfTowerLabel    = cms.untracked.InputTag('')#standAloneMuons')#'generalTracks')#'globalMuons')#'standAloneMuons')#'globalMuons')#'generalTracks')
   # hfTowerLabel = cms.InputTag('hcalRecHit:hbhereco'),
    calos = cms.untracked.InputTag('towerMaker'),
   #   tracks    = cms.untracked.InputTag('generalTracks'),
    leadingTowerPtMin = cms.double(20.0),
    leadingTowerEtaMax = cms.double(3.0),
    leadingTowerPhiMin = cms.double(-3.14159),
    leadingTowerPhiMax = cms.double(3.14159)
   # nbins = cms.uint32(100),
   # minBin = cms.double(0.0),
   # maxBin = cms.double(10.0)
 #   outputFileName = cms.string('hf_distribution.root')                            

 )

# Select only events that pass the desired trigger path
process.selectedEvents = cms.EDFilter("TriggerResultsFilter",
    triggerConditions = cms.vstring('HLT_HIUPC_SingleMuOpen_NotMBHF2AND_v4'),
    hltResults = cms.InputTag("TriggerResults", "", "HLT"),
   # l1tResults = cms.InputTag("gtStage2Digis", "", "RECO"),
    throw = cms.bool(False)
)


process.trig = cms.EDAnalyzer('MuonTriggerMatch3',
 #   triggerResults = cms.InputTag("TriggerResults", "", "HLT"),
 #   triggerEvent = cms.InputTag("hltTriggerSummaryAOD", "", "HLT"),
 #  trigPath = cms.untracked.string("HLT_HIUPC_SingleMuOpen_NotMBHF2AND_v4")
offlineMuons= cms.InputTag("muons"),
triggerResultss = cms.InputTag("TriggerResults" , "", "HLT"),
triggerObjectss=cms.InputTag("hltTriggerSummaryAOD") # "", "HLT")
#trigPath = cms.untracked.string("HLT_HIMinimumBias_v2")
)


process.muon = cms.EDAnalyzer('DemoAnalyzerMuon2',
   muuons = cms.untracked.InputTag('muons'),
   trraacks = cms.untracked.InputTag('generalTracks'),
   veertices = cms.untracked.InputTag('offlinePrimaryVertices'), 
   beeamspot = cms.untracked.InputTag('offlineBeamSpot'),

#sandAloneMuons')#'generalTracks')#'globalMuons')#'standAloneMuons')#'globalMuons')#'generalTracks')
                             )

process.track = cms.EDAnalyzer('DemoAnalyzerTrack',
   tracks    = cms.untracked.InputTag('generalTracks')#standAloneMuons')#'generalTracks')#'globalMuons')#'standAloneMuons')#'globalMuons')#'generalTracks')
                             )

"""
process.goodMuons = cms.EDFilter("MuonSelector",
 src = cms.InputTag("muons"),
# cut = cms.string('isTrackerMuon && innerTrack.quality("highPurity") && innerTrack.isNonnull() && innerTrack.isAvailable() && innerTrack.hitPattern.trackerLayersWithMeasurement() > 0 '), #isTrackerMuon &&&& innerTrack.hitPattern.pixelLayersWithMeasurement() > 0 && innerTrack.quality("highPurity")'),#  && fabs(innerTrack.dxy(primaryVertex.position())) < 0.3'),#  && cms.math.abs(innerTrack.dz(primaryVertex.position())) < 20.'),
 cut = cms.string('isGlobalMuon()' ),# 'pt>1'),#'isTrackerMuon && innerTrack.isNonnull() && innerTrack.isAvailable() && innerTrack.hitPattern.trackerLayersWithMeasurement() > 5 && innerTrack.hitPattern.pixelLayersWithMeasurement() > 0 && innerTrack.quality("highPurity")'), 
 cut = cms.string('isTrackerMuon && innerTrack.isNonnull() && innerTrack.isAvailable() && innerTrack.hitPattern.trackerLayersWithMeasurement() > 5 && innerTrack.hitPattern.pixelLayersWithMeasurement() > 0 && innerTrack.quality("highPurity") && muon::isGoodMuon(muon, muon::TMOneStationTight)'),
# cut = cms.string('isTrackerMuon && innerTrack.isNonnull() && innerTrack.isAvailable() && innerTrack.hitPattern.trackerLayersWithMeasurement() > 5 && innerTrack.hitPattern.pixelLayersWithMeasurement() > 0 && innerTrack.quality("highPurity") && muon::isGoodMuon($, muon::TMOneStationTight)'),
  filter = cms.bool(True)
)
"""

process.load("RecoVertex.PrimaryVertexProducer.OfflinePrimaryVertices_cfi")
process.selectedVertices = cms.EDFilter("VertexSelector",
    src = cms.InputTag("offlinePrimaryVertices"),
    cut = cms.string("!isFake && ndof > 0 && abs(z) < 24 && position.Rho < 2"),
    filter = cms.bool(True)
)


process.TFileService = cms.Service("TFileService",
fileName = cms.string("output.root")
)
          
process.p = cms.Path( process.trig + process.calo + process.selectedVertices + process.muon + process.track) # + process.calo)# + process.calo) #goodMuons + process.muon + process.track + process. calo)# + process.calo )# + process.track)# + process.demo)
