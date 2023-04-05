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

class DemoAnalyzerMuon2 : public edm::one::EDAnalyzer<edm::one::SharedResources> {
public:
  explicit DemoAnalyzerMuon2(const edm::ParameterSet&);
  ~DemoAnalyzerMuon2() override;

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  void beginJob() override;
  void analyze(const edm::Event&, const edm::EventSetup&) override;
  void endJob() override;

 // edm::EDGetTokenT<MuonCollection> muonsToken_;
    edm::EDGetTokenT<MuonCollection> muonsToken_;
//  edm::EDGetTokenT<TrackCollection> muonsToken_;
   edm::EDGetTokenT<TrackCollection> trracksToken_;
    edm::EDGetTokenT<VertexCollection> verticesToken_;
    edm::EDGetTokenT<reco::BeamSpot> beamspotToken_;      
 //   edm::EDGetTokenT<reco::Track> trracksToken_;

 ///* vector<float> */ double muonPtSoftMuon__SoftMuon_;
 ///* vector<float> */ double muonEtaSoftMuon__SoftMuon_;

int nevents_ =0;
int nEventsDoubleMuon_ =0;

TTree* treeMuon;
std::vector<int> tracksNumber_;

 std::vector<double> tracksEta_;
 std::vector<double> tracksPt_;


// Any Muons
  std::vector<double> muonEtaAnyMuon_;
  std::vector<double> muonPtAnyMuon_;
  std::vector<double> invariantMass2MuonAnyMuon_;
  std::vector<double> deltaPhi2MuonAnyMuon_;

// general Muons
 // std::vector<double> muonEtaTrackerMuon_;
//  std::vector<double> muonPtTrackerMuon_;
//  std::vector<double> invariantMass2MuonStandAloneMuon_;
//  std::vector<double> deltaPhi2MuonGlobalMuon_;


// Soft Muons
 std::vector<double> muonEtaSoftMuon_;
 std::vector<double> muonPtSoftMuon_;
 std::vector<double> invariantMass2MuonSoftMuon_;
 std::vector<double> deltaPhi2MuonSoftMuon_;

 //Soft Trakcer Muons
 std::vector<double> muonEtaSoftTrackerMuon_;
 std::vector<double> muonPtSoftTrackerMuon_;
 std::vector<double> invariantMass2MuonSoftTrackerMuon_;
 std::vector<double> deltaPhi2MuonSoftTrackerMuon_;
 
// Trakcer Muons
 std::vector<double> muonEtaTrackerMuon_;
   std::vector<double> muonPtTrackerMuon_;
    std::vector<double> invariantMass2MuonTrackerMuon_;
     std::vector<double> deltaPhi2MuonTrackerMuon_; 

//std::vector<double> tracksNumberSoftTrackerMuonEta_;
 //std::vector<double> tracksNumberSoftTrackerMuonPt_;

 //Soft StandAlone Muons
 std::vector<double> muonEtaSoftStandAloneMuon_;
 std::vector<double> muonPtSoftStandAloneMuon_;
 std::vector<double> invariantMass2MuonSoftStandAloneMuon_;
 std::vector<double> deltaPhi2MuonSoftStandAloneMuon_;
 //std::vector<double> tracksNumberSoftStandAloneMuonEta_;
 //std::vector<double> tracksNumberSoftStandAloneMuonPt_;

 //StandAlone Muons
  std::vector<double> muonEtaStandAloneMuon_;
   std::vector<double> muonPtStandAloneMuon_;
    std::vector<double> invariantMass2MuonStandAloneMuon_;
     std::vector<double> deltaPhi2MuonStandAloneMuon_;

 //TTree* tree1Muon_SoftStandAloneMuon_;
 //TTree* tree2Muon_SoftStandAloneMuon_;

 //Soft Global Muons
 std::vector<double> muonEtaSoftGlobalMuon_;
 std::vector<double> muonPtSoftGlobalMuon_;
 std::vector<double> invariantMass2MuonSoftGlobalMuon_;
 std::vector<double> deltaPhi2MuonSoftGlobalMuon_;
 
 //Global Muons
  std::vector<double> muonEtaGlobalMuon_;
   std::vector<double> muonPtGlobalMuon_;
    std::vector<double> invariantMass2MuonGlobalMuon_;
     std::vector<double> deltaPhi2MuonGlobalMuon_;




//std::vector<double> deltaPhi2MuonSoftGlobalMuonEta_;
 //std::vector<double> deltaPhi2MuonSoftGlobalMuonPt_;
 //int tracksNumberSoftGlobalMuon_;
 //TTree* tree1Muon_SoftGlobalMuon_;
 //TTree* tree2Muon_SoftGlobalMuon_;



#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  edm::ESGetToken<SetupData, SetupRecord> setupToken_;
#endif
};

DemoAnalyzerMuon2::DemoAnalyzerMuon2(const edm::ParameterSet& iConfig)
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

DemoAnalyzerMuon2::~DemoAnalyzerMuon2() {
}

void DemoAnalyzerMuon2::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  using namespace edm;

//edm::Handle<reco::BeamSpot> beamspot;
auto beamspot= iEvent.get(beamspotToken_);


std::vector<reco::Muon> GoodAnyMuons;
std::vector<reco::Muon> GoodSoftMuons;
std::vector<reco::Muon> GoodSoftTrackerMuons;
std::vector<reco::Muon> GoodSoftStandAloneMuons;
std::vector<reco::Muon> GoodSoftGlobalMuons;

std::vector<reco::Muon> GoodTrackerMuons;
std::vector<reco::Muon> GoodStandAloneMuons;
std::vector<reco::Muon> GoodGlobalMuons;

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
{if ( track.quality(reco::Track::highPurity) && track.numberOfValidHits() > 5 && abs( track.eta()) < 2.4&&abs(track.dxy(closestVertex.position())) < 0.3 && std::abs(track.dz(closestVertex.position())) < 20)
{
tracksNumberr_ = tracksNumberr_ + 1;

tracksEta_ .push_back(track.eta());
tracksPt_.push_back(track.pt());
cout <<"track founded" << endl;
}
}

if (tracksNumberr_>0){
tracksNumber_.push_back(tracksNumberr_);
cout << " tracksNumberr_" <<tracksNumberr_ << endl;
}
//if (tracksNumberSoftMuon > 0) {trackTree_->Fill(); cout<<"The number of general Tracks = "<<nTrack<<endl;}



for (const auto& muuon : iEvent.get(muonsToken_)) 
{ 
{GoodAnyMuons.push_back(muuon);
muonEtaAnyMuon_.push_back(muuon.eta());
muonPtAnyMuon_.push_back(muuon.pt());}

//if(muon::isTightMuon( muuon && needs vertex  ) {
//if (muon::isGoodMuon(muuon, muon::TMOneStationTight) && muuon.innerTrack()->hitPattern().trackerLayersWithMeasurement() > 5 && muuon.innerTrack()->hitPattern().pixelLayersWithMeasurement() > 0 && muuon.innerTrack()->quality(reco::Track::highPurity)){// && muuon.isTrackerMuon() && abs(muuon.innerTrack()->dxy(closestVertex.position())) < 0.3 && std::abs(muuon.innerTrack()->dz(closestVertex.position())) < 20 ){
//nGoodMuons+=1;

if(muuon.isTrackerMuon()) {GoodTrackerMuons.push_back(muuon);
muonEtaTrackerMuon_.push_back(muuon.eta());
muonPtTrackerMuon_.push_back(muuon.pt());}

if(muuon.isStandAloneMuon()) {GoodStandAloneMuons.push_back(muuon);
muonEtaStandAloneMuon_.push_back(muuon.eta());
muonPtStandAloneMuon_.push_back(muuon.pt());}


if( muuon.isGlobalMuon()) {GoodGlobalMuons.push_back(muuon);
muonEtaGlobalMuon_.push_back(muuon.eta());
muonPtGlobalMuon_.push_back(muuon.pt());}

if(muon::isSoftMuon(muuon, closestVertex)){
{GoodSoftMuons.push_back(muuon);
muonEtaSoftMuon_.push_back(muuon.eta());
muonPtSoftMuon_.push_back(muuon.pt());
//tree1Muon_SoftMuon_->Fill();
}

if(muuon.isTrackerMuon()) {GoodSoftTrackerMuons.push_back(muuon);
muonEtaSoftTrackerMuon_.push_back(muuon.eta());
muonPtSoftTrackerMuon_.push_back(muuon.pt());
//tree1Muon_SoftTrackerMuon_->Fill();
}

if(muuon.isStandAloneMuon()) {GoodSoftStandAloneMuons.push_back(muuon);
muonEtaSoftStandAloneMuon_.push_back(muuon.eta());
muonPtSoftStandAloneMuon_.push_back(muuon.pt());
//tree1Muon_SoftStandAloneMuon_->Fill();
}

if( muuon.isGlobalMuon()) {GoodSoftGlobalMuons.push_back(muuon);
muonEtaSoftGlobalMuon_.push_back(muuon.eta());
muonPtSoftGlobalMuon_.push_back(muuon.pt());
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
if(GoodAnyMuons.size() ==2)
{

//nEventsDoubleMuon_ = nEventsDoubleMuon_+1;

//cout << "nEventsDoubleMuon= " <<nEventsDoubleMuon_ << endl;
  TLorentzVector muon11, muon12;
  muon11.SetPxPyPzE(GoodAnyMuons[0].px(), GoodAnyMuons[0].py(), GoodAnyMuons[0].pz(), GoodAnyMuons[0].energy());
  muon12.SetPxPyPzE(GoodAnyMuons[1].px(), GoodAnyMuons[1].py(), GoodAnyMuons[1].pz(), GoodAnyMuons[1].energy());

if ((muon11+muon12).M() < 200 ){
      invariantMass2MuonAnyMuon_.push_back( (muon11+muon12).M());
      deltaPhi2MuonAnyMuon_.push_back(fabs( muon11.DeltaPhi(muon12)));
     //std::cout << deltaPhi2MuonSoftMuon_ <<" , " << invariantMass2MuonSoftMuon_ << std::endl; 
}
      //if (invariantMass2MuonSoftMuon_ < 200 )
      //tree2Muon_SoftMuon_->Fill(); 
 }


//auto GoodMuons= iEvent.get(muonsToken_);
if(GoodSoftMuons.size() ==2)
{

nEventsDoubleMuon_ = nEventsDoubleMuon_+1;

cout << "nEventsDoubleMuon= " <<nEventsDoubleMuon_ << endl;
  TLorentzVector muon21, muon22;
  muon21.SetPxPyPzE(GoodSoftMuons[0].px(), GoodSoftMuons[0].py(), GoodSoftMuons[0].pz(), GoodSoftMuons[0].energy());
  muon22.SetPxPyPzE(GoodSoftMuons[1].px(), GoodSoftMuons[1].py(), GoodSoftMuons[1].pz(), GoodSoftMuons[1].energy());

if((muon21+muon22).M() < 200)
{invariantMass2MuonSoftMuon_.push_back( (muon21+muon22).M());
deltaPhi2MuonSoftMuon_.push_back(fabs( muon21.DeltaPhi(muon22)));
//std::cout << deltaPhi2MuonSoftMuon_ <<" , " << invariantMass2MuonSoftMuon_ << std::endl; 
}
//if (invariantMass2MuonSoftMuon_ < 200 )
//tree2Muon_SoftMuon_->Fill(); 
}

//auto GoodMuons= iEvent.get(muonsToken_);
if(GoodSoftTrackerMuons.size() ==2)
{
  TLorentzVector muon31, muon32;
    muon31.SetPxPyPzE(GoodSoftTrackerMuons[0].px(), GoodSoftTrackerMuons[0].py(), GoodSoftTrackerMuons[0].pz(), GoodSoftTrackerMuons[0].energy());
      muon32.SetPxPyPzE(GoodSoftTrackerMuons[1].px(), GoodSoftTrackerMuons[1].py(), GoodSoftTrackerMuons[1].pz(), GoodSoftTrackerMuons[1].energy());

if( (muon31+muon32).M() <200 ){
      invariantMass2MuonSoftTrackerMuon_.push_back((muon31+muon32).M());
      deltaPhi2MuonSoftTrackerMuon_.push_back(fabs( muon31.DeltaPhi(muon32)));
     // std::cout << deltaPhi2MuonSoftTrackerMuon_ <<" , " << invariantMass2MuonSoftTrackerMuon_ << std::endl;
}
 //     if (invariantMass2MuonSoftTrackerMuon_ < 200 )
 //     tree2Muon_SoftTrackerMuon_->Fill();
}

//auto GoodMuons= iEvent.get(muonsToken_);
if(GoodTrackerMuons.size() ==2)
{
  TLorentzVector muon41, muon42;
  muon41.SetPxPyPzE(GoodTrackerMuons[0].px(), GoodTrackerMuons[0].py(), GoodTrackerMuons[0].pz(), GoodTrackerMuons[0].energy());
  muon42.SetPxPyPzE(GoodTrackerMuons[1].px(), GoodTrackerMuons[1].py(), GoodTrackerMuons[1].pz(), GoodTrackerMuons[1].energy());
 
                if ((muon41+muon42).M() < 200) {
                  invariantMass2MuonTrackerMuon_.push_back((muon41+muon42).M());
                  deltaPhi2MuonTrackerMuon_.push_back(fabs( muon41.DeltaPhi(muon42)));
                             // std::cout << deltaPhi2MuonSoftTrackerMuon_ <<" , " << invariantMass2MuonSoftTrackerMuon_ << std::endl;
}
                              //     if (invariantMass2MuonSoftTrackerMuon_ < 200 )
                               //     tree2Muon_SoftTrackerMuon_->Fill();
             }

if(GoodSoftStandAloneMuons.size() ==2)
{
 TLorentzVector muon51, muon52;
   muon51.SetPxPyPzE(GoodSoftStandAloneMuons[0].px(), GoodSoftStandAloneMuons[0].py(), GoodSoftStandAloneMuons[0].pz(), GoodSoftStandAloneMuons[0].energy());
   muon52.SetPxPyPzE(GoodSoftStandAloneMuons[1].px(), GoodSoftStandAloneMuons[1].py(), GoodSoftStandAloneMuons[1].pz(), GoodSoftStandAloneMuons[1].energy());

             if ((muon51+muon52).M() < 200) {
              invariantMass2MuonSoftStandAloneMuon_.push_back( (muon51+muon52).M());
              deltaPhi2MuonSoftStandAloneMuon_.push_back(fabs( muon51.DeltaPhi(muon52)));
                                                            }
 //             std::cout << deltaPhi2MuonSoftStandAloneMuon_ <<" , " << invariantMass2MuonSoftStandAloneMuon_ << std::endl;

 //            if (invariantMass2MuonSoftStandAloneMuon_ < 200) 
  //           tree2Muon_SoftStandAloneMuon_->Fill();
}

if(GoodStandAloneMuons.size() ==2)
{
 TLorentzVector muon61, muon62;
   muon61.SetPxPyPzE(GoodStandAloneMuons[0].px(), GoodStandAloneMuons[0].py(), GoodStandAloneMuons[0].pz(), GoodStandAloneMuons[0].energy());
   muon62.SetPxPyPzE(GoodStandAloneMuons[1].px(), GoodStandAloneMuons[1].py(), GoodStandAloneMuons[1].pz(), GoodStandAloneMuons[1].energy());

            if((muon61+muon62).M() < 200) {
              invariantMass2MuonStandAloneMuon_.push_back( (muon61+muon62).M());
              deltaPhi2MuonStandAloneMuon_.push_back(fabs( muon61.DeltaPhi(muon62)));
                }
  //            std::cout << deltaPhi2MuonSoftStandAloneMuon_ <<" , " << invariantMass2MuonSoftStandAloneMuon_ << std::endl;
 
               //            if (invariantMass2MuonSoftStandAloneMuon_ < 200) 
                 //           tree2Muon_SoftStandAloneMuon_->Fill();
                 }


//auto GoodMuons= iEvent.get(muonsToken_);
if(GoodSoftGlobalMuons.size() ==2)
{
  TLorentzVector muon71, muon72;
      muon71.SetPxPyPzE(GoodSoftGlobalMuons[0].px(), GoodSoftGlobalMuons[0].py(), GoodSoftGlobalMuons[0].pz(), GoodSoftGlobalMuons[0].energy());
      muon72.SetPxPyPzE(GoodSoftGlobalMuons[1].px(), GoodSoftGlobalMuons[1].py(), GoodSoftGlobalMuons[1].pz(), GoodSoftGlobalMuons[1].energy());

           if((muon71+muon72).M() < 200) { 
                invariantMass2MuonSoftGlobalMuon_.push_back((muon71+muon72).M());
                deltaPhi2MuonSoftGlobalMuon_.push_back(fabs( muon71.DeltaPhi(muon72))) ; 
                      }
             // std::cout << deltaPhi2MuonSoftGlobalMuon_ <<" , " << invariantMass2MuonSoftGlobalMuon_ << std::endl;

 //              if (invariantMass2MuonSoftGlobalMuon_ < 200 )
 //               tree2Muon_SoftGlobalMuon_->Fill();
}
 

//auto GoodMuons= iEvent.get(muonsToken_);
if(GoodGlobalMuons.size() ==2)
{
  TLorentzVector muon81, muon82;
  muon81.SetPxPyPzE(GoodGlobalMuons[0].px(), GoodGlobalMuons[0].py(), GoodGlobalMuons[0].pz(), GoodGlobalMuons[0].energy());
  muon82.SetPxPyPzE(GoodGlobalMuons[1].px(), GoodGlobalMuons[1].py(), GoodGlobalMuons[1].pz(), GoodGlobalMuons[1].energy());

    if ((muon81+muon82).M() < 200) { 
      invariantMass2MuonGlobalMuon_.push_back((muon81+muon82).M());
      deltaPhi2MuonGlobalMuon_.push_back(fabs( muon81.DeltaPhi(muon82))); 
                                           }  
            // std::cout << deltaPhi2MuonSoftGlobalMuon_ <<" , " << invariantMass2MuonSoftGlobalMuon_ << std::endl;
             //              if (invariantMass2MuonSoftGlobalMuon_ < 200 )
            //               tree2Muon_SoftGlobalMuon_->Fill();
    }                                                                              
 // treeMuon ->Fill();
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

void DemoAnalyzerMuon2::beginJob() {
  // initialize output TTree
  edm::Service<TFileService> fs;
//  tree1Muon_SoftMuon_ = fs->make<TTree>("SMuonTreeSoftMuon_", "single muon tree Soft Muon ");
//  tree2Muon_SoftMuon_ = fs->make<TTree>("DMuonTreeSoftMuon_", "double muon tree Soft Muon ");
 treeMuon = fs->make<TTree>("MuonTree", "Muon Treee");

 treeMuon->Branch("tracksNumber", &tracksNumber_);
 treeMuon->Branch("tracksPt", &tracksPt_);
 treeMuon->Branch("tracksEta", &tracksEta_);


 treeMuon->Branch("muonPtAnyMuon", &muonPtAnyMuon_);
 treeMuon->Branch("muonEtaAnyMuon", &muonEtaAnyMuon_);
 treeMuon->Branch("invariantMass2MuonAnyMuon", &invariantMass2MuonAnyMuon_);
 treeMuon->Branch("deltaPhi2MuonAnyMuon",&deltaPhi2MuonAnyMuon_);

 treeMuon->Branch("muonPtSoftMuon", &muonPtSoftMuon_);
 treeMuon->Branch("muonEtaSoftMuon", &muonEtaSoftMuon_);
 treeMuon->Branch("invariantMass2MuonSoftMuon", &invariantMass2MuonSoftMuon_);
 treeMuon->Branch("deltaPhi2MuonSoftMuon",&deltaPhi2MuonSoftMuon_);

 //treeMuon_Soft= fs->make<TTree>("SMuonTreeSoftTrackerMuon_", "single muon tree Soft tracker Muon ");
// treeMuon_SoftTrackerMuon_ = fs->make<TTree>("DMuonTreeSoftTrackerMuon_", "double muon tree Soft tracker Muon ");
// treeMuon->Branch("tracksNumberSoftTrackerMuon", &tracksNumberSoftMuon_, "tracksNumberSoftMuon_/D");
 treeMuon->Branch("muonPtSoftTrackerMuon", &muonPtSoftTrackerMuon_);
 treeMuon->Branch("muonEtaSoftTrackerMuon", &muonEtaSoftTrackerMuon_);
 treeMuon->Branch("invariantMass2MuonSoftTrackerMuon", &invariantMass2MuonSoftTrackerMuon_);
 treeMuon->Branch("deltaPhi2MuonSoftTrackerMuon",&deltaPhi2MuonSoftTrackerMuon_);

 treeMuon->Branch("muonPtTrackerMuon", &muonPtTrackerMuon_);
 treeMuon->Branch("muonEtaTrackerMuon", &muonEtaTrackerMuon_);
 treeMuon->Branch("invariantMass2MuonTrackerMuon", &invariantMass2MuonTrackerMuon_);
 treeMuon->Branch("deltaPhi2MuonTrackerMuon",&deltaPhi2MuonTrackerMuon_);

// treeMuon= fs->make<TTree>("SMuonTreeSoftStandAloneMuon_", "single muon tree Soft StandAlone Muon ");
// treeMuon = fs->make<TTree>("DMuonTreeSoftStandAloneMuon_", "double muon tree Soft StandAlone Muon ");
 treeMuon->Branch("muonPtSoftStandAloneMuon", &muonPtSoftStandAloneMuon_);
 treeMuon->Branch("muonEtaSoftStandAloneMuon", &muonEtaSoftStandAloneMuon_);
// treeMuon->Branch("tracksNumberSoftStandAloneMuon", &tracksNumberSoftStandAloneMuon_, "tracksNumberSoftStandAloneMuon_/D");
 treeMuon->Branch("invariantMass2MuonSoftStandAloneMuon", &invariantMass2MuonSoftStandAloneMuon_);
 treeMuon->Branch("deltaPhi2MuonSoftStandAloneMuon",&deltaPhi2MuonSoftStandAloneMuon_);

 treeMuon->Branch("muonPtStandAloneMuon", &muonPtStandAloneMuon_);
 treeMuon->Branch("muonEtaStandAloneMuon", &muonEtaStandAloneMuon_);
// treeMuon->Branch("tracksNumberSoftStandAloneMuon", &tracksNumberSoftStandAloneMuon_, "tracksNumberSoftStandAloneMuon_/D");
  treeMuon->Branch("invariantMass2MuonStandAloneMuon", &invariantMass2MuonStandAloneMuon_);
   treeMuon->Branch("deltaPhi2MuonStandAloneMuon",&deltaPhi2MuonStandAloneMuon_);


// treeMuon= fs->make<TTree>("SMuonTreeSoftGlobalMuon_", "single muon tree Soft Global Muon ");
// treeMuon = fs->make<TTree>("DMuonTreeSoftGlobalMuon_", "double muon tree Soft Global Muon ");
 treeMuon->Branch("muonPtSoftGlobalMuon", &muonPtSoftGlobalMuon_);
 treeMuon->Branch("muonEtaSoftGlobalMuon", &muonEtaSoftGlobalMuon_);
// treeMuon->Branch("tracksNumberSoftGlobalMuon", &tracksNumberSoftGlobalMuon_, "tracksNumberSoftGlobalMuon_/D");
 treeMuon->Branch("invariantMass2MuonSoftGlobalMuon", &invariantMass2MuonSoftGlobalMuon_);
 treeMuon->Branch("deltaPhi2MuonSoftGlobalMuon",&deltaPhi2MuonSoftGlobalMuon_);


 treeMuon->Branch("muonPtGlobalMuon", &muonPtGlobalMuon_);
 treeMuon->Branch("muonEtaGlobalMuon", &muonEtaGlobalMuon_);
// treeMuon->Branch("tracksNumberSoftGlobalMuon", &tracksNumberSoftGlobalMuon_, "tracksNumberSoftGlobalMuon_/D");
  treeMuon->Branch("invariantMass2MuonGlobalMuon", &invariantMass2MuonGlobalMuon_);
   treeMuon->Branch("deltaPhi2MuonGlobalMuon",&deltaPhi2MuonGlobalMuon_);

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

void DemoAnalyzerMuon2::endJob() {
  // please remove this method if not needed
treeMuon ->Fill();
  cout << "The number of events= " << nevents_ << endl;

}

void DemoAnalyzerMuon2::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

// define this as a plug-in
DEFINE_FWK_MODULE(DemoAnalyzerMuon2);

