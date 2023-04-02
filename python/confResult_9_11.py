import FWCore.ParameterSet.Config as cms
import glob

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

#process.source = cms.Source("PoolSource",
                                # replace 'myfile.root' with the source file you want to use
 #                               fileNames = cms.untracked.vstring(
       #   'file:skimmed.root'
#'file:Photon.root'
#'root://cms-xrd-global.cern.ch//store/hidata/HIRun2022A/HITestRaw0/AOD/PromptReco-v1/000/362/318/00000/3fb50183-105d-46d8-9c44-95fd1b2ae44a.root'
#'root://cms-xrd-global.cern.ch//store/user/eshokr/output/HITestRaw9/skimming/230309_202833/0000/skimmed_105.root'
#'file:../output/output_19/skimmed_*.root' 
#'file:../output/output_19/skimmed_{}.root'.format(i) for i in range(1,171)
#'file:../output/HITestRaw{i}/skimming/230309_202747/0000/skimmed_{j}.root'.format(i=i, j=j) for i in range(24) for j in range(1, 172)
#glob.glob('file:/afs/cern.ch/work/e/eshokr/EXOVVNtuplizerRunII/CMSSW_12_5_2_patch1/src/HeavyIonsAnalysis/DemoAnalyzer/output/HITestRaw{i}/skimming/2*/0000/skimmed_{j}.root').format(i=i, j=j) for i in range(24) for j in range(1, 12)
 #        )
  #        )                 

import glob

#process.source = cms.Source("PoolSource",
                                # replace 'myfile.root' with the source file you want to use
 #                               fileNames = cms.untracked.vstring(
  #                                  *[f'file:{f}' for f in glob.glob('/afs/cern.ch/work/e/eshokr/EXOVVNtuplizerRunII/CMSSW_12_5_2_patch1/src/HeavyIonsAnalysis/DemoAnalyzer/output/HITestRaw{i}/skimming/2*/0000/skimmed_{j}.root'.format(i=i, j=j) for i in range(24) for j in range(1, 12))]
   #      )
    #      )

process.source = cms.Source("PoolSource",
                             fileNames = cms.untracked.vstring([
                                 'file:' + f for i in range(9,12) for j in range(1, 171) 
                                 for f in glob.glob('/afs/cern.ch/work/e/eshokr/EXOVVNtuplizerRunII/CMSSW_12_5_2_patch1/src/HeavyIonsAnalysis/DemoAnalyzer/output/HITestRaw{i}/skimming/2*/0000/skimmed_{j}.root'.format(i=i, j=j))
                             ])
                            )


process.muon = cms.EDAnalyzer('DemoAnalyzerMuon',
   muuons    = cms.untracked.InputTag('muons')#standAloneMuons')#'generalTracks')#'globalMuons')#'standAloneMuons')#'globalMuons')#'generalTracks')
                             )

process.track = cms.EDAnalyzer('DemoAnalyzerTrack',
   tracks    = cms.untracked.InputTag('generalTracks')#standAloneMuons')#'generalTracks')#'globalMuons')#'standAloneMuons')#'globalMuons')#'generalTracks')
                             )

process.goodMuons = cms.EDFilter("MuonSelector",
   src = cms.InputTag("muons"),
   cut = cms.string('isTrackerMuon && innerTrack.isNonnull() && innerTrack.isAvailable() && innerTrack.hitPattern.trackerLayersWithMeasurement() > 5 && innerTrack.hitPattern.pixelLayersWithMeasurement() > 0 && innerTrack.quality("highPurity")'),#  && fabs(innerTrack.dxy(primaryVertex.position())) < 0.3'),#  && cms.math.abs(innerTrack.dz(primaryVertex.position())) < 20.'),
   filter = cms.bool(True)
)

process.TFileService = cms.Service("TFileService",
fileName = cms.string("output_9_11.root")
)
          
process.p = cms.Path(process.goodMuons + process.muon +process.track)# + process.track)# + process.demo)
