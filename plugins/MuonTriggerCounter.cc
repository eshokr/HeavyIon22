#include <memory>

#include <vector>
#include <iostream>

#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"

//#include "FWCore/Framework/interface/ESHandle.h"
//#include "FWCore/Framework/interface/ESGetToken.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
// class declaration
class MuonTriggerCounter : public edm::one::EDAnalyzer<edm::one::SharedResources> {
public:
  explicit MuonTriggerCounter(const edm::ParameterSet&);
  ~MuonTriggerCounter();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  void beginJob() override;
  void analyze(const edm::Event&, const edm::EventSetup&) override;
  void endJob() override;
    
  // ----------member data --------------------------
  //  edm::InputTag triggerResultsToken_;
 //   edm::InputTag triggerEventToken_;
    edm::EDGetTokenT<edm::TriggerResults> triggerResultsToken_;
    edm::EDGetTokenT<trigger::TriggerEvent> triggerEventToken_;

    std::string triggerPath_;


   // TH1I* hNumMuons_;
    int allMuonNumber=0;
 
   //used to select what tracks to read from configuration file
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  edm::ESGetToken<SetupData, SetupRecord> setupToken_;
#endif
};
//MuonTriggerCounter::MuonTriggerCounter(const edm::ParameterSet& iConfig)
//    : triggerResultsToken_(consumes<edm::TriggerResults>(iConfig.getUntrackedParameter<edm::InputTag>("trigResults"))),
//      triggerEventToken_(consumes<trigger::TriggerEvent>(iConfig.getUntrackedParameter<edm::InputTag>("trigEvents"))),
 //     triggerPath_(iConfig.getUntrackedParameter<std::string>("trigPath"))
MuonTriggerCounter::MuonTriggerCounter(const edm::ParameterSet& iConfig)
    : //triggerResultsToken_(consumes<edm::TriggerResults>(iConfig.getUntrackedParameter<edm::InputTag>("trigResults"))),
 //     triggerEventToken_(consumes<trigger::TriggerEvent>(iConfig.getUntrackedParameter<edm::InputTag>("trigEvents"))),
    //  triggerPath_(iConfig.getUntrackedParameter<std::string>("trigPath")),
//  triggerResultsToken_ = consumes<edm::TriggerResults>(edm::InputTag("TriggerResults", "", "HLT"))
//  triggerEventToken_= consumes<trigger::TriggerEvent>(edm::InputTag("hltTriggerSummaryAOD", "", "HLT")),
      triggerPath_(iConfig.getUntrackedParameter<std::string>("trigPath"))

{

  triggerResultsToken_ = consumes<edm::TriggerResults>(edm::InputTag("TriggerResults", "", "HLT"));
  triggerEventToken_= consumes<trigger::TriggerEvent>(edm::InputTag("hltTriggerSummaryAOD", "", "HLT"));

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  setupDataToken_ = esConsumes<SetupData, SetupRecord>();
#endif
  //now do what ever initialization is needed
}

MuonTriggerCounter::~MuonTriggerCounter() {
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  //
  // please remove this method altogether if it would be left empty
}

//
// member functions
//

// ------------ method called for each event  ------------
//void MuonTriggerCounter::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
 
/*
void MuonTriggerCounter::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
    // trigger::TriggerObjectCollection& 
auto triggerResults = iEvent.get(triggerResultsToken_); 
auto triggerObjects = iEvent.get(triggerEventToken_).getObjects();
   // const edm::TriggerNames&
auto triggerNames = triggerObjects.triggerNames(*iEvent.get(triggerResultsToken_));
   // const edm::TriggerResults&
//auto triggerResults = iEvent.get(triggerResultsToken_);

    unsigned int triggerIndex = triggerNames.triggerIndex(triggerPath_);
    if (triggerIndex < triggerResults.size() && triggerResults.accept(triggerIndex)) {
        unsigned int numMuons = 0;
        for (trigger::size_type i = 0; i < triggerObjects.size(); ++i) {
            pat::TriggerObjectStandAlone obj(triggerObjects[i]);
            obj.unpackPathNames(triggerNames);
            if (obj.hasPathName(triggerPath_) && obj.hasTriggerObjectType(trigger::TriggerMuon)) {
                ++numMuons;
                ++allMuonNumber;
            }
        }
 //       hNumMuons_->Fill(numMuons);
        std::cout << "number of muons passing trigger: " << numMuons << std::endl;

     }   
    
#ifdef this_is_an_eventsetup_example
  // if the setupdata is always needed
  auto setup = isetup.getdata(setuptoken_);
  // if need the eshandle to check if the setupdata was there or not
  auto psetup = isetup.gethandle(setuptoken_);
#endif
}
*/

void MuonTriggerCounter::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  auto triggerResults = iEvent.get(triggerResultsToken_);
  auto triggerObjects = iEvent.get(triggerEventToken_).getObjects();
  auto triggerNames = iEvent.triggerNames(triggerResults);
  int triggerIndex = triggerNames.triggerIndex(triggerPath_);
  
 // if (triggerIndex < triggerResults.size() && triggerResults.accept(triggerIndex)) {
    int numMuons = 0;
 std :: cout << "triggerObjects size= " <<triggerObjects.size() <<std::endl; 
 
  for (trigger::size_type i = 0; i < triggerObjects.size(); ++i) {
      pat::TriggerObjectStandAlone obj(triggerObjects[i]);
      obj.unpackPathNames(triggerNames);
if (obj.eta() != 0)      std :: cout << "obj eta" << obj.eta() <<std::endl;

      if (/*obj.hasPathName(triggerPath_) &&*/ obj.hasTriggerObjectType(trigger::TriggerTrack)) {
        ++numMuons;
        ++allMuonNumber;
      }
    }
    std::cout << "number of muons passing trigger: " << numMuons << std::endl;
  }
//}


// ------------ method called once each job just before starting event loop  ------------
//void MuonTriggercounter::beginjob() {    }

void MuonTriggerCounter::beginJob() {
//  triggerResultsToken_ = consumes<edm::TriggerResults>(edm::InputTag("TriggerResults", "", "HLT"));
//  triggerEventToken_ = consumes<trigger::TriggerEvent>(edm::InputTag("hltTriggerSummaryAOD", "", "HLT"));
}

// ------------ method called once each job just after ending the event loop  ------------
void MuonTriggerCounter::endJob() {

    std::cout << "The number of trigger muons" << allMuonNumber << std::endl;
  // please remove this method if not needed
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void MuonTriggerCounter::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
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
DEFINE_FWK_MODULE(MuonTriggerCounter);
