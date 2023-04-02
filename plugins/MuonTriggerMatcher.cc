#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/PatCandidates/interface/Muon.h"


using pat::MuonCollection;


class MuonTriggerMatcher : public edm::EDAnalyzer {
public:
  explicit MuonTriggerMatcher(const edm::ParameterSet&);
  ~MuonTriggerMatcher();

private:
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  edm::InputTag offlineMuonTag_;
  edm::InputTag triggerMuonTag_;
};

MuonTriggerMatcher::MuonTriggerMatcher(const edm::ParameterSet& iConfig)
{
  offlineMuonTag_ = iConfig.getParameter<edm::InputTag>("offlineMuons");
//  triggerMuonTag_ = iConfig.getParameter<edm::InputTag>("triggerMuons");
}

MuonTriggerMatcher::~MuonTriggerMatcher()
{
}

void MuonTriggerMatcher::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  // Get the offline muons
     edm::Handle<pat::MuonCollection> offlineMuons;
     iEvent.getByLabel(offlineMuonTag_, offlineMuons);
  
  //       // Get the trigger objects
     edm::Handle<trigger::TriggerEvent> triggerEvent;
     iEvent.getByLabel(edm::InputTag("hltTriggerSummaryAOD", "", "HLT"), triggerEvent);
     const trigger::TriggerObjectCollection& triggerObjects = triggerEvent->getObjects();
  
                 // Loop over the offline muons and match them to trigger objects
     for (pat::MuonCollection::const_iterator muon = offlineMuons->begin(); muon != offlineMuons->end(); ++muon) {
                       // Skip non-global muons
     if (!muon->isGlobalMuon()) continue;
  
                               // Match the muon to a trigger object
    double bestDeltaR = 999.0;
    trigger::TriggerObject bestTriggerObject;
    for (size_t i = 0; i < triggerObjects.size(); ++i) {
    const trigger::TriggerObject& triggerObject = triggerObjects[i];
    double deltaR = reco::deltaR(triggerObject.eta(), triggerObject.phi(), muon->eta(), muon->phi());
    if (deltaR < bestDeltaR) {
    bestDeltaR = deltaR;
    bestTriggerObject = triggerObject;
                                                                                   }
                                                                                       }
  
                                                                                // Print the match information
    std::cout << "Muon pT = " << muon->pt() << ", trigger object pT = " << bestTriggerObject.pt() << ", deltaR = " << bestDeltaR << std::endl;
                                                                                                 }
                                                                                                 }
  
   DEFINE_FWK_MODULE(MuonTriggerMatcher);
  
