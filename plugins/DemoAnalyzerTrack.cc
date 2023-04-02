// -*- C++ -*-
//
// Package:    Demo/DemoAnalyzerTrack
// Class:      DemoAnalyzerTrack
//
/**\class DemoAnalyzerTrack DemoAnalyzerTrack.cc Demo/DemoAnalyzerTrack/plugins/DemoAnalyzerTrack.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Shengquan Tuo
//         Created:  Mon, 27 Sep 2021 15:49:48 GMT
//
//

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "TTree.h"
//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.

using reco::TrackCollection;

class DemoAnalyzerTrack : public edm::one::EDAnalyzer<edm::one::SharedResources> {
public:
  explicit DemoAnalyzerTrack(const edm::ParameterSet&);
  ~DemoAnalyzerTrack();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:

TTree* trackTree_;
double trackPt_;
double trackEta_;
int tracksNumber_;

  void beginJob() override;
  void analyze(const edm::Event&, const edm::EventSetup&) override;
  void endJob() override;

  // ----------member data ---------------------------
  edm::EDGetTokenT<TrackCollection> tracksToken_;  //used to select what tracks to read from configuration file
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  edm::ESGetToken<SetupData, SetupRecord> setupToken_;
#endif
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
DemoAnalyzerTrack::DemoAnalyzerTrack(const edm::ParameterSet& iConfig)
    : tracksToken_(consumes<TrackCollection>(iConfig.getUntrackedParameter<edm::InputTag>("tracks"))) {
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  setupDataToken_ = esConsumes<SetupData, SetupRecord>();
#endif

 // edm::Service<TFileService> fss;
//  trackTree_ = fss->make<TTree>("tracks", "Tree for Tracks");

 // trackTree_ = new TTree("tracks", "Tree for Tracks");
//  trackTree_->Branch("trackPt", &trackPt_, "trackPt_/D");
//  trackTree_->Branch("trackEta", &trackEta_, "trackEta_/D");

 //now do what ever initialization is needed

 // trackTree_ = new TTree("tracksTree", "Tree for Tracks");
 //   trackTree_->Branch("trackPt", &trackPt_, "trackPt_/D");
 //   trackTree_->Branch("trackEta", &trackEta_, "trackEta_/D");

}

DemoAnalyzerTrack::~DemoAnalyzerTrack() {
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  //
  // please remove this method altogether if it would be left empty
}

//
// member functions
//

// ------------ method called for each event  ------------
void DemoAnalyzerTrack::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  using namespace edm;
  using namespace std;

  int nTrack = 0;
  for (const auto& track : iEvent.get(tracksToken_)) 
{if ( /*track.hitPattern().trackerLayersWithMeasurement() > 5 && track.hitPattern().pixelLayersWithMeasurement() > 2 &&*/ 
track.quality(reco::Track::highPurity) && track.numberOfValidHits() > 5 && abs( track.eta()) < 2.4)
{
nTrack++;
trackPt_= track.pt();
trackEta_= track.eta();
}

}
tracksNumber_=nTrack;
if (nTrack > 0) {trackTree_->Fill(); cout<<"The number of general Tracks = "<<nTrack<<endl;}
//  cout<<"The number of general Tracks = "<<nTrack<<endl;
  
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
 
 // if the SetupData is always needed
  auto setup = iSetup.getData(setupToken_);
  // if need the ESHandle to check if the SetupData was there or not
  auto pSetup = iSetup.getHandle(setupToken_);
#endif

}
// ------------ method called once each job just before starting event loop  ------------
void DemoAnalyzerTrack::beginJob() {
  // please remove this method if not needed
   edm::Service<TFileService> fs;
     trackTree_ = fs->make<TTree>("tracksTree", "Tree for Tracks");
     trackTree_->Branch("trackPt", &trackPt_, "trackPt_/D");
     trackTree_->Branch("trackEta", &trackEta_, "trackEta_/D");
     trackTree_->Branch("tracksNumber", &tracksNumber_, "tracksNumber_/I");

}

// ------------ method called once each job just after ending the event loop  ------------
void DemoAnalyzerTrack::endJob() {
  // please remove this method if not needed
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void DemoAnalyzerTrack::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  //descriptions.addWithDefaultLabel(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(DemoAnalyzerTrack);
