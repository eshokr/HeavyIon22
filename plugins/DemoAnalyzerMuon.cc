#include <memory>
#include <vector>
#include <iostream>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Utilities/interface/Exception.h"
#include "FWCore/Utilities/interface/transform.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/MuonReco/interface/Muon.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"


// root includes
#include "TH1.h"
#include <TTree.h>
#include <TLorentzVector.h>

using reco::TrackCollection;
using reco::MuonCollection;
using reco::VertexCollection;

using namespace std;

class DemoAnalyzerMuon : public edm::one::EDAnalyzer<edm::one::SharedResources> {
public:
  explicit DemoAnalyzerMuon(const edm::ParameterSet&);
  ~DemoAnalyzerMuon() override;

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  void beginJob() override;
  void analyze(const edm::Event&, const edm::EventSetup&) override;
  void endJob() override;

 // edm::EDGetTokenT<MuonCollection> muonsToken_;
    edm::EDGetTokenT<MuonCollection> muonsToken_;
   edm::EDGetTokenT<TrackCollection> trracksToken_;
    edm::EDGetTokenT<VertexCollection> verticesToken_;
    edm::EDGetTokenT<reco::BeamSpot> beamspotToken_;      
 //   edm::EDGetTokenT<reco::Track> trracksToken_;

 ///* vector<float> */ double muonPtSoftMuon__SoftMuon_;
 ///* vector<float> */ double muonEtaSoftMuon__SoftMuon_;
 /* vector<int> */ //  int muonNumber_;


// Soft Muons
double muonEtaSoftMuon_;
double muonPtSoftMuon_;
double invariantMass2MuonSoftMuon_;
double deltaPhi2MuonSoftMuon_;

int tracksNumber_ =0;
//double tracksEta_;
//double tracksPt_;

TTree* treeMuon;
//TTree* tree1Muon_SoftMuon_;
//TTree* tree2Muon_SoftMuon_;
//
//Trakcer Muons
double muonEtaSoftTrackerMuon_;
double muonPtSoftTrackerMuon_;
double invariantMass2MuonSoftTrackerMuon_;
double deltaPhi2MuonSoftTrackerMuon_;
//double tracksNumberSoftTrackerMuonEta_;
//double tracksNumberSoftTrackerMuonPt_;

//TTree* tree1Muon_SoftTrackerMuon_;
//TTree* tree2Muon_SoftTrackerMuon_;

//StandAlone Muons
double muonEtaSoftStandAloneMuon_;
double muonPtSoftStandAloneMuon_;
double invariantMass2MuonSoftStandAloneMuon_;
double deltaPhi2MuonSoftStandAloneMuon_;
//double tracksNumberSoftStandAloneMuonEta_;
//double tracksNumberSoftStandAloneMuonPt_;

//TTree* tree1Muon_SoftStandAloneMuon_;
//TTree* tree2Muon_SoftStandAloneMuon_;

//Global Muons
double muonEtaSoftGlobalMuon_;
double muonPtSoftGlobalMuon_;
double invariantMass2MuonSoftGlobalMuon_;
double deltaPhi2MuonSoftGlobalMuon_;
//double deltaPhi2MuonSoftGlobalMuonEta_;
//double deltaPhi2MuonSoftGlobalMuonPt_;
//int tracksNumberSoftGlobalMuon_;
//TTree* tree1Muon_SoftGlobalMuon_;
//TTree* tree2Muon_SoftGlobalMuon_;



int nevents_ =0;
int nEventsDoubleMuon_ =0;

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  edm::ESGetToken<SetupData, SetupRecord> setupToken_;
#endif
};

DemoAnalyzerMuon::DemoAnalyzerMuon(const edm::ParameterSet& iConfig)
    : muonsToken_(consumes<MuonCollection>(iConfig.getUntrackedParameter<edm::InputTag>("muuons"))),
      trracksToken_(consumes<TrackCollection>(iConfig.getUntrackedParameter<edm::InputTag>("trraacks"))),
      verticesToken_(consumes<VertexCollection>(iConfig.getUntrackedParameter<edm::InputTag>("veertices"))),  
 //     trracksToken_(consumes<reco::Track>(iConfig.getUntrackedParameter<edm::InputTag>("trraacks"))),    
      beamspotToken_(consumes<reco::BeamSpot>(iConfig.getUntrackedParameter<edm::InputTag>("beeamspot")))
 {
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  setupToken_ = esConsumes<SetupData, SetupRecord>();
#endif
  // now do what ever initialization is needed

//edm::Handle<std::vector<reco::Vertex>> vertices;
//iEvent.getByToken(vertexToken_, vertices);
//edm::Handle<reco::BeamSpot> beamspot;
}

DemoAnalyzerMuon::~DemoAnalyzerMuon() {
}

void DemoAnalyzerMuon::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  using namespace edm;

//edm::Handle<reco::BeamSpot> beamspot;
auto beamspot= iEvent.get(beamspotToken_);

std::vector<reco::Muon> GoodSoftMuons;
std::vector<reco::Muon> GoodSoftTrackerMuons;
std::vector<reco::Muon> GoodSoftStandAloneMuons;
std::vector<reco::Muon> GoodSoftGlobalMuons;

 // int nTrack = 0;
 
// to get the closest vertex to the beamspot
double dzmax=999;
reco::Vertex closestVertex;

for (const auto& vtx : iEvent.get(verticesToken_))
{
if(!vtx.isFake()){
if(abs(vtx.position().z() - beamspot.position().z()) < dzmax) {closestVertex = vtx;}
}
}
cout <<"closest vertex z " << closestVertex.z() << ", closest vertex x " << closestVertex.x() <<", closest vertex y " << closestVertex.y() << endl;


// To calculate the tracks number
//tracksNumberSoftTrackerMuon_ =0;
//tracksNumberSoftStandAloneMuon_ =0;
//tracksNumberSoftGlobalMuon_ =0;


int tracksNumberr_ =0;

 for (const auto& track : iEvent.get(trracksToken_))
{if ( track.quality(reco::Track::highPurity) && track.numberOfValidHits() > 5 && abs( track.eta()) < 2.4)
{
tracksNumberr_ = tracksNumberr_ + 1;

//tracksEta_ =track.eta();
//tracksPt_ =track.pt();
cout <<"track founded" << endl;

}
}

tracksNumber_=tracksNumberr_;

cout << " tracksNumber_" <<tracksNumber_ << endl;

//if (tracksNumberSoftMuon > 0) {trackTree_->Fill(); cout<<"The number of general Tracks = "<<nTrack<<endl;}



for (const auto& muuon : iEvent.get(muonsToken_)) 
{ 


//if(muon::isTightMuon( muuon && needs vertex  ) {
//if (muon::isGoodMuon(muuon, muon::TMOneStationTight) && muuon.innerTrack()->hitPattern().trackerLayersWithMeasurement() > 5 && muuon.innerTrack()->hitPattern().pixelLayersWithMeasurement() > 0 && muuon.innerTrack()->quality(reco::Track::highPurity)){// && muuon.isTrackerMuon() && abs(muuon.innerTrack()->dxy(closestVertex.position())) < 0.3 && std::abs(muuon.innerTrack()->dz(closestVertex.position())) < 20 ){
//nGoodMuons+=1;
if(muon::isSoftMuon(muuon, closestVertex)){


{GoodSoftMuons.push_back(muuon);
muonEtaSoftMuon_= muuon.eta();
muonPtSoftMuon_ = muuon.pt();
//tree1Muon_SoftMuon_->Fill();
}

if(muuon.isTrackerMuon()) {GoodSoftTrackerMuons.push_back(muuon);
muonEtaSoftTrackerMuon_= muuon.eta();
muonPtSoftTrackerMuon_ = muuon.pt();
//tree1Muon_SoftTrackerMuon_->Fill();
}

if(muuon.isStandAloneMuon()) {GoodSoftStandAloneMuons.push_back(muuon);
muonEtaSoftStandAloneMuon_= muuon.eta();
muonPtSoftStandAloneMuon_ = muuon.pt();
//tree1Muon_SoftStandAloneMuon_->Fill();
}

if( muuon.isGlobalMuon()) {GoodSoftGlobalMuons.push_back(muuon);
muonEtaSoftGlobalMuon_= muuon.eta();
muonPtSoftGlobalMuon_ = muuon.pt();
//tree1Muon_SoftGlobalMuon_->Fill();
}

}
}

//cout << "The number of good muons in this event = " << nGoodMuons << endl;
cout << "The number of soft muons in this event = " << GoodSoftMuons.size() << endl;
cout << "The number of soft tracker muons in this event = " << GoodSoftTrackerMuons.size() << endl;
cout << "The number of soft standalone muons in this event = " << GoodSoftStandAloneMuons.size() << endl;
cout << "The number of soft global muons in this event = " << GoodSoftGlobalMuons.size() << endl;

//auto GoodMuons= iEvent.get(muonsToken_);
if(GoodSoftMuons.size() ==2)
{

nEventsDoubleMuon_ = nEventsDoubleMuon_+1;

cout << "nEventsDoubleMuon= " <<nEventsDoubleMuon_ << endl;
  TLorentzVector muon1, muon2;
  muon1.SetPxPyPzE(GoodSoftMuons[0].px(), GoodSoftMuons[0].py(), GoodSoftMuons[0].pz(), GoodSoftMuons[0].energy());
  muon2.SetPxPyPzE(GoodSoftMuons[1].px(), GoodSoftMuons[1].py(), GoodSoftMuons[1].pz(), GoodSoftMuons[1].energy());

invariantMass2MuonSoftMuon_=  (muon1+muon2).M();
deltaPhi2MuonSoftMuon_= fabs( muon1.DeltaPhi(muon2));
std::cout << deltaPhi2MuonSoftMuon_ <<" , " << invariantMass2MuonSoftMuon_ << std::endl; 

//if (invariantMass2MuonSoftMuon_ < 200 )
//tree2Muon_SoftMuon_->Fill(); 
}

//auto GoodMuons= iEvent.get(muonsToken_);
if(GoodSoftTrackerMuons.size() ==2)
{
  TLorentzVector muon1, muon2;
    muon1.SetPxPyPzE(GoodSoftTrackerMuons[0].px(), GoodSoftTrackerMuons[0].py(), GoodSoftTrackerMuons[0].pz(), GoodSoftTrackerMuons[0].energy());
      muon2.SetPxPyPzE(GoodSoftTrackerMuons[1].px(), GoodSoftTrackerMuons[1].py(), GoodSoftTrackerMuons[1].pz(), GoodSoftTrackerMuons[1].energy());

      invariantMass2MuonSoftTrackerMuon_=  (muon1+muon2).M();
      deltaPhi2MuonSoftTrackerMuon_= fabs( muon1.DeltaPhi(muon2));
      std::cout << deltaPhi2MuonSoftTrackerMuon_ <<" , " << invariantMass2MuonSoftTrackerMuon_ << std::endl;

 //     if (invariantMass2MuonSoftTrackerMuon_ < 200 )
 //     tree2Muon_SoftTrackerMuon_->Fill();
}

if(GoodSoftStandAloneMuons.size() ==2)
{
 TLorentzVector muon1, muon2;
   muon1.SetPxPyPzE(GoodSoftStandAloneMuons[0].px(), GoodSoftStandAloneMuons[0].py(), GoodSoftStandAloneMuons[0].pz(), GoodSoftStandAloneMuons[0].energy());
   muon2.SetPxPyPzE(GoodSoftStandAloneMuons[1].px(), GoodSoftStandAloneMuons[1].py(), GoodSoftStandAloneMuons[1].pz(), GoodSoftStandAloneMuons[1].energy());

              invariantMass2MuonSoftStandAloneMuon_=  (muon1+muon2).M();
              deltaPhi2MuonSoftStandAloneMuon_= fabs( muon1.DeltaPhi(muon2));
              std::cout << deltaPhi2MuonSoftStandAloneMuon_ <<" , " << invariantMass2MuonSoftStandAloneMuon_ << std::endl;

 //            if (invariantMass2MuonSoftStandAloneMuon_ < 200) 
  //           tree2Muon_SoftStandAloneMuon_->Fill();
}


//auto GoodMuons= iEvent.get(muonsToken_);
if(GoodSoftGlobalMuons.size() ==2)
{
  TLorentzVector muon1, muon2;
      muon1.SetPxPyPzE(GoodSoftGlobalMuons[0].px(), GoodSoftGlobalMuons[0].py(), GoodSoftGlobalMuons[0].pz(), GoodSoftGlobalMuons[0].energy());
      muon2.SetPxPyPzE(GoodSoftGlobalMuons[1].px(), GoodSoftGlobalMuons[1].py(), GoodSoftGlobalMuons[1].pz(), GoodSoftGlobalMuons[1].energy());

                invariantMass2MuonSoftGlobalMuon_=  (muon1+muon2).M();
                deltaPhi2MuonSoftGlobalMuon_= fabs( muon1.DeltaPhi(muon2)) ; 
                std::cout << deltaPhi2MuonSoftGlobalMuon_ <<" , " << invariantMass2MuonSoftGlobalMuon_ << std::endl;

 //              if (invariantMass2MuonSoftGlobalMuon_ < 200 )
 //               tree2Muon_SoftGlobalMuon_->Fill();
}
                                                                                    
  treeMuon ->Fill();
  nevents_++;

/*
 muonEtaSoftMuon_ =0.0;
 muonPtSoftMuon_=0.0;
 invariantMass2MuonSoftMuon_=0.0;
 deltaPhi2MuonSoftMuon_=0.0;

 muonEtaSoftTrackerMuon_=0.0;
 muonPtSoftTrackerMuon_=0.0;
 invariantMass2MuonSoftTrackerMuon_=0.0;
 deltaPhi2MuonSoftTrackerMuon_=0.0;

 muonEtaSoftStandAloneMuon_=0.0;
 muonPtSoftStandAloneMuon_=0.0;
 invariantMass2MuonSoftStandAloneMuon_=0.0;
 deltaPhi2MuonSoftStandAloneMuon_=0.0;

 muonEtaSoftGlobalMuon_=0.0;
 muonPtSoftGlobalMuon_=0.0;
 invariantMass2MuonSoftGlobalMuon_=0.0;
 deltaPhi2MuonSoftGlobalMuon_=0.0;
*/

}

void DemoAnalyzerMuon::beginJob() {
  // initialize output TTree
  edm::Service<TFileService> fs;
//  tree1Muon_SoftMuon_ = fs->make<TTree>("SMuonTreeSoftMuon_", "single muon tree Soft Muon ");
//  tree2Muon_SoftMuon_ = fs->make<TTree>("DMuonTreeSoftMuon_", "double muon tree Soft Muon ");
 treeMuon = fs->make<TTree>("MuonTree", "Muon Treee");

 treeMuon->Branch("muonPtSoftMuon", &muonPtSoftMuon_, "muonPtSoftMuon_/D");
 treeMuon->Branch("muonEtaSoftMuon", &muonEtaSoftMuon_, "muonEtaSoftMuon_/D");
 treeMuon->Branch("tracksNumber", &tracksNumber_, "tracksNumber_/I");
 treeMuon->Branch("invariantMass2MuonSoftMuon", &invariantMass2MuonSoftMuon_, "invariantMass2MuonSoftMuon_/D");
 treeMuon->Branch("deltaPhi2MuonSoftMuon",&deltaPhi2MuonSoftMuon_,"deltaPhi2MuonSoftMuon_/D");

 //treeMuon_Soft= fs->make<TTree>("SMuonTreeSoftTrackerMuon_", "single muon tree Soft tracker Muon ");
// treeMuon_SoftTrackerMuon_ = fs->make<TTree>("DMuonTreeSoftTrackerMuon_", "double muon tree Soft tracker Muon ");
// treeMuon->Branch("tracksNumberSoftTrackerMuon", &tracksNumberSoftMuon_, "tracksNumberSoftMuon_/D");
 treeMuon->Branch("muonPtSoftTrackerMuon", &muonPtSoftTrackerMuon_, "muonPtSoftTrackerMuon_/D");
 treeMuon->Branch("muonEtaSoftTrackerMuon", &muonEtaSoftTrackerMuon_, "muonEtaSoftTrackerMuon_/D");
 treeMuon->Branch("invariantMass2MuonSoftTrackerMuon", &invariantMass2MuonSoftTrackerMuon_, "invariantMass2MuonSoftTrackerMuon_/D");
 treeMuon->Branch("deltaPhi2MuonSoftTrackerMuon",&deltaPhi2MuonSoftTrackerMuon_,"deltaPhi2MuonSoftTrackerMuon_/D");

// treeMuon= fs->make<TTree>("SMuonTreeSoftStandAloneMuon_", "single muon tree Soft StandAlone Muon ");
// treeMuon = fs->make<TTree>("DMuonTreeSoftStandAloneMuon_", "double muon tree Soft StandAlone Muon ");
 treeMuon->Branch("muonPtSoftStandAloneMuon", &muonPtSoftStandAloneMuon_, "muonPtSoftStandAloneMuon_/D");
 treeMuon->Branch("muonEtaSoftStandAloneMuon", &muonEtaSoftStandAloneMuon_, "muonEtaSoftStandAloneMuon_/D");
// treeMuon->Branch("tracksNumberSoftStandAloneMuon", &tracksNumberSoftStandAloneMuon_, "tracksNumberSoftStandAloneMuon_/D");
 treeMuon->Branch("invariantMass2MuonSoftStandAloneMuon", &invariantMass2MuonSoftStandAloneMuon_, "invariantMass2MuonSoftStandAloneMuon_/D");
 treeMuon->Branch("deltaPhi2MuonSoftStandAloneMuon",&deltaPhi2MuonSoftStandAloneMuon_,"deltaPhi2MuonSoftStandAloneMuon_/D");

// treeMuon= fs->make<TTree>("SMuonTreeSoftGlobalMuon_", "single muon tree Soft Global Muon ");
// treeMuon = fs->make<TTree>("DMuonTreeSoftGlobalMuon_", "double muon tree Soft Global Muon ");
 treeMuon->Branch("muonPtSoftGlobalMuon", &muonPtSoftGlobalMuon_, "muonPtSoftGlobalMuon_/D");
 treeMuon->Branch("muonEtaSoftGlobalMuon", &muonEtaSoftGlobalMuon_, "muonEtaSoftGlobalMuon_/D");
// treeMuon->Branch("tracksNumberSoftGlobalMuon", &tracksNumberSoftGlobalMuon_, "tracksNumberSoftGlobalMuon_/D");
 treeMuon->Branch("invariantMass2MuonSoftGlobalMuon", &invariantMass2MuonSoftGlobalMuon_, "invariantMass2MuonSoftGlobalMuon_/D");
 treeMuon->Branch("deltaPhi2MuonSoftGlobalMuon",&deltaPhi2MuonSoftGlobalMuon_,"deltaPhi2MuonSoftGlobalMuon_/D");


/*
 tree1Muon_SoftMuon_->Branch("muonPtSoftMuon_", &muonPtSoftMuon_, "muonPtSoftMuon_/D");
 tree1Muon_SoftMuon_->Branch("muonEtaSoftMuon_", &muonEtaSoftMuon_, "muonEtaSoftMuon_/D");
 tree1Muon_SoftMuon_->Branch("tracksNumberSoftMuon_", &tracksNumberSoftMuon_, "tracksNumberSoftMuon_/D");
 tree2Muon_SoftMuon_->Branch("invariantMass2MuonSoftMuon_", &invariantMass2MuonSoftMuon_, "invariantMass2MuonSoftMuon_/D");
 tree2Muon_SoftMuon_->Branch("deltaPhi2MuonSoftMuon_",&deltaPhi2MuonSoftMuon_,"deltaPhi2MuonSoftMuon_/D");

 tree1Muon_SoftTrackerMuon_ = fs->make<TTree>("SMuonTreeSoftTrackerMuon_", "single muon tree Soft tracker Muon ");
 tree2Muon_SoftTrackerMuon_ = fs->make<TTree>("DMuonTreeSoftTrackerMuon_", "double muon tree Soft tracker Muon ");
 tree1Muon_SoftMuon_->Branch("tracksNumberSoftMuon_", &tracksNumberSoftMuon_, "tracksNumberSoftMuon_/D");
 tree1Muon_SoftTrackerMuon_->Branch("muonPtSoftTrackerMuon_", &muonPtSoftTrackerMuon_, "muonPtSoftTrackerMuon_/D");
 tree1Muon_SoftTrackerMuon_->Branch("muonEtaSoftTrackerMuon_", &muonEtaSoftTrackerMuon_, "muonEtaSoftTrackerMuon_/D");
 tree2Muon_SoftTrackerMuon_->Branch("invariantMass2MuonSoftTrackerMuon_", &invariantMass2MuonSoftTrackerMuon_, "invariantMass2MuonSoftTrackerMuon_/D");
 tree2Muon_SoftTrackerMuon_->Branch("deltaPhi2MuonSoftTrackerMuon_",&deltaPhi2MuonSoftTrackerMuon_,"deltaPhi2MuonSoftTrackerMuon_/D");

tree1Muon_SoftStandAloneMuon_ = fs->make<TTree>("SMuonTreeSoftStandAloneMuon_", "single muon tree Soft StandAlone Muon ");
 tree2Muon_SoftStandAloneMuon_ = fs->make<TTree>("DMuonTreeSoftStandAloneMuon_", "double muon tree Soft StandAlone Muon ");
 tree1Muon_SoftStandAloneMuon_->Branch("muonPtSoftStandAloneMuon_", &muonPtSoftStandAloneMuon_, "muonPtSoftStandAloneMuon_/D");
 tree1Muon_SoftStandAloneMuon_->Branch("muonEtaSoftStandAloneMuon_", &muonEtaSoftStandAloneMuon_, "muonEtaSoftStandAloneMuon_/D");
 tree2Muon_SoftStandAloneMuon_->Branch("invariantMass2MuonSoftStandAloneMuon_", &invariantMass2MuonSoftStandAloneMuon_, "invariantMass2MuonSoftStandAloneMuon_/D");
 tree2Muon_SoftStandAloneMuon_->Branch("deltaPhi2MuonSoftStandAloneMuon_",&deltaPhi2MuonSoftStandAloneMuon_,"deltaPhi2MuonSoftStandAloneMuon_/D");

tree1Muon_SoftGlobalMuon_ = fs->make<TTree>("SMuonTreeSoftGlobalMuon_", "single muon tree Soft Global Muon ");
 tree2Muon_SoftGlobalMuon_ = fs->make<TTree>("DMuonTreeSoftGlobalMuon_", "double muon tree Soft Global Muon ");
 tree1Muon_SoftGlobalMuon_->Branch("muonPtSoftGlobalMuon_", &muonPtSoftGlobalMuon_, "muonPtSoftGlobalMuon_/D");
 tree1Muon_SoftGlobalMuon_->Branch("muonEtaSoftGlobalMuon_", &muonEtaSoftGlobalMuon_, "muonEtaSoftGlobalMuon_/D");
 tree2Muon_SoftGlobalMuon_->Branch("invariantMass2MuonSoftGlobalMuon_", &invariantMass2MuonSoftGlobalMuon_, "invariantMass2MuonSoftGlobalMuon_/D");
 tree2Muon_SoftGlobalMuon_->Branch("deltaPhi2MuonSoftGlobalMuon_",&deltaPhi2MuonSoftGlobalMuon_,"deltaPhi2MuonSoftGlobalMuon_/D");
*/ 

}

void DemoAnalyzerMuon::endJob() {
  // please remove this method if not needed
  cout << "The number of events= " << nevents_ << endl;
}

void DemoAnalyzerMuon::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

// define this as a plug-in
DEFINE_FWK_MODULE(DemoAnalyzerMuon);

