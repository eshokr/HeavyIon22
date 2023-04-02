 #include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include <iostream>

class MuonTrigger : public edm::EDAnalyzer {
public:
    explicit MuonTrigger(const edm::ParameterSet&);
    virtual ~MuonTrigger() {}
    virtual void analyze(const edm::Event&, const edm::EventSetup&);

private:
    edm::InputTag triggerResultsTag_;
    edm::InputTag triggerEventTag_;
    std::string triggerPath_;
    //unsigned int minNumMuons_;
    TH1F* hNumMuons_;
};

MuonTrigger::MuonTrigger(const edm::ParameterSet& iConfig) :
    triggerResultsTag_(iConfig.getParameter<edm::InputTag>("triggerResults")),
    triggerEventTag_(iConfig.getParameter<edm::InputTag>("triggerEvent")),
    triggerPath_(iConfig.getParameter<std::string>("triggerPath"))
//   minNumMuons_(iConfig.getParameter<unsigned int>("minNumMuons"))
{
    edm::Service<TFileService> fs;
    hNumMuons_ = fs->make<TH1F>("hNumMuons", "Number of muons passing trigger", 10, 0, 10);
}

void MuonTrigger::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    // Get the trigger results
    edm::Handle<edm::TriggerResults> triggerResults;
   iEvent.getByLabel(triggerResultsTag_, triggerResults);

    // Get the trigger event
    edm::Handle<trigger::TriggerEvent> triggerEvent;
    iEvent.getByLabel(triggerEventTag_, triggerEvent);

    // Get the trigger object collection
    const trigger::TriggerObjectCollection& triggerObjects = triggerEvent->getObjects();

    // Get the trigger path index
    const edm::TriggerNames& triggerNames = iEvent.triggerNames(*triggerResults);
    unsigned int triggerIndex = triggerNames.triggerIndex(triggerPath_);

    // Check if the trigger path was passed
    if (triggerIndex < triggerResults->size() && triggerResults->accept(triggerIndex)) {
        // Loop over the trigger objects and count the number of muons
        unsigned int numMuons = 0;
        for (trigger::size_type i = 0; i < triggerObjects.size(); ++i) {
            pat::TriggerObjectStandAlone obj(triggerObjects[i]);
            obj.unpackPathNames(triggerNames);
            if (obj.hasPathName(triggerPath_) && obj.hasTriggerObjectType(trigger::TriggerMuon)) {
                ++numMuons;
            }
        }
        // Fill the histogram with the number of muons passing the trigger
        hNumMuons_->Fill(numMuons);
        std::cout << "Number of muons passing trigger: " << numMuons << std::endl;
 
     }
     
   }



// ------------ method called once each job just before starting event loop  ------------
//void MuonTrigger::beginJob() {}

// ------------ method called once each job just after ending the event loop  ------------
//void MuonTrigger::endJob() {
  // please remove this method if not needed}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
/*void MuonTrigger::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

}*/

//define this as a plug-in
DEFINE_FWK_MODULE(MuonTrigger);



