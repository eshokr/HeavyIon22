#include <iostream>
#include <vector>
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/HLTReco/interface/TriggerTypeDefs.h"

#include "DataFormats/L1TGlobal/interface/GlobalObjectMap.h"
#include "DataFormats/L1TGlobal/interface/GlobalObjectMapRecord.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/MuonReco/interface/Muon.h"

using reco::MuonCollection;
class MuonTriggerMatch3 : public edm::EDAnalyzer {
public:
  explicit MuonTriggerMatch3(const edm::ParameterSet&);
  virtual ~MuonTriggerMatch3();

  virtual void analyze(const edm::Event&, const edm::EventSetup&);

private:
  edm::EDGetTokenT<trigger::TriggerEvent> triggerEventToken_;
  edm::EDGetTokenT<edm::TriggerResults> triggerResultsToken_;
  edm::EDGetTokenT<MuonCollection> offlineMuonsToken_;
  bool firedpath;
};

MuonTriggerMatch3::MuonTriggerMatch3(const edm::ParameterSet& iConfig) :
  triggerEventToken_(consumes<trigger::TriggerEvent>(iConfig.getParameter<edm::InputTag>("triggerObjectss"))),
  triggerResultsToken_(consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("triggerResultss"))),
  offlineMuonsToken_(consumes<MuonCollection>(iConfig.getParameter<edm::InputTag>("offlineMuons"))) 
// objectMapToken_(consumes<GlobalObjectMapRecord > (iConfig.getParameter<edm::InputTag>("obbjectMap")))
{}

MuonTriggerMatch3::~MuonTriggerMatch3()
{}

void MuonTriggerMatch3::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::Handle<trigger::TriggerEvent> triggerEvent;
  iEvent.getByToken(triggerEventToken_, triggerEvent);

  edm::Handle<edm::TriggerResults> trigResults;
  iEvent.getByToken(triggerResultsToken_, trigResults);
 
 // edm::Handle<GlobalObjectMapRecord> objectMapp;
 // iEvent.getByToken(objectMapToken_, objectMapp);

  edm::Handle<MuonCollection> offlineMuons;
  iEvent.getByToken(offlineMuonsToken_, offlineMuons);

  auto triggerObjects = triggerEvent->getObjects();
  const edm::TriggerNames& trigNames = iEvent.triggerNames(*trigResults);

/*
std::cout << "Trigger names:" << std::endl;
for (unsigned int i = 0; i < trigNames.size(); ++i) {
  std::cout << trigNames.triggerName(i) << std::endl;
} 
*/

//std::string pathName="HLT_HIUPC_SingleMuOpen_NotMBHF2AND_v4";
//bool passTrig=trigResults->accept(trigNames.triggerIndex(pathName));  

// std::vector<std::string> triggerNamesVec;
// std::cout << "Trigger names:" << std::endl;

  for (unsigned int i = 0; i < trigNames.size(); ++i) {
      std::string triggerName = trigNames.triggerName(i);
      bool passTrig = trigResults->accept(trigNames.triggerIndex(triggerName));
      if(passTrig){
      firedpath = passTrig;
      std::cout << "fired trigger name= "<< triggerName << std::endl;
 //     triggerNamesVec.push_back(triggerName);
    }
}

//bool passTrig=1;
    if (firedpath) {
        
        // Print trigger object info for objects that pass the trigger
        for (size_t i = 0; i < triggerObjects.size(); ++i) {
            if (triggerObjects[i] .pt() > 0){
                
                std::cout << "Trigger obj eta: " << triggerObjects[i].eta()
                << ", phi: " << triggerObjects[i].phi()
                << " , pt: " << triggerObjects[i].pt()
                << " , mass:  " << triggerObjects[i].mass()
                << " , id:  " << triggerObjects[i].id() << std::endl;}
        }
        
        
        for (size_t j = 0; j < offlineMuons->size(); ++j) {
            const reco::Muon& offlineMuon = (*offlineMuons)[j];
            std::cout <<"offline Moun Eta= " << offlineMuon.eta()
            << " ,Muon phi= "<<offlineMuon.phi()
            << " ,Muon Pt= " << offlineMuon.pt()
            <<" ,Muon mass" << offlineMuon.mass() << std::endl;
        }
    }
   //  std::cout << "Number of trigger muon candidates: " << nTriggerMuons << std::endl;
  // Loop over all trigger objects
/*
   for (size_t i = 0; i < triggerObjects.size(); ++i) {
  const trigger::TriggerObject& triggerObject = triggerObjects[i];
  if (triggerObject.id() != trigger::TriggerMuon)
                                             continue;
   // Find the best match among the offline muons
   double bestDeltaR = 999.0; //deltaRThreshold_;
   const reco::Muon* bestMuon = nullptr;
  for (size_t j = 0; j < offlineMuons->size(); ++j) { const reco::Muon& offlineMuon = (*offlineMuons)[j];

//std::cout <<"offline Moun Eta= " << offlineMuon.eta() << ", offline Muon Pt= "<<offlineMuon.pt()<<"offline Muon Phi" <<offlineMuon.phi()<< std::endl; 
            // Calculate deltaR between trigger object and offline muon
  double deltaR = reco::deltaR(triggerObject.eta(),triggerObject.phi(), offlineMuon.eta(), offlineMuon.phi());
  // Update the best match if deltaR is smaller than the current bestDeltaR
   if (deltaR < bestDeltaR) {bestDeltaR = deltaR;
 bestMuon = &offlineMuon;                                                                                                                                            }
}                                                                                                           // Print match information for the best match
  if (bestMuon != nullptr) {
  std::cout << "Trigger muon object matches offline muon with pt=" 
   << bestMuon->pt() << " and eta=" << bestMuon->eta() << std::endl;
                           } 
                    }
    */
    
}                                             


DEFINE_FWK_MODULE(MuonTriggerMatch3);


