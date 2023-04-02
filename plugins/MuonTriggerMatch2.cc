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
class MuonTriggerMatch2 : public edm::EDAnalyzer {
public:
  explicit MuonTriggerMatch2(const edm::ParameterSet&);
  virtual ~MuonTriggerMatch2();

  virtual void analyze(const edm::Event&, const edm::EventSetup&);

private:
  edm::EDGetTokenT<trigger::TriggerEvent> triggerEventToken_;
  edm::EDGetTokenT<edm::TriggerResults> triggerResultsToken_;
  edm::EDGetTokenT<MuonCollection> offlineMuonsToken_;
  bool firedpath;

//  using reco::MuonCollection;

  // edm::EDGetTokenT<GlobalObjectMapRecord > objectMapToken_;

//  edm::EDGetTokenT<edm::TriggerResults> triggerResultsToken_;

  // double deltaRThreshold_;

 // void printTriggerCandidates(const trigger::TriggerObjectCollection& triggerObjects) const;
};

MuonTriggerMatch2::MuonTriggerMatch2(const edm::ParameterSet& iConfig) :
  triggerEventToken_(consumes<trigger::TriggerEvent>(iConfig.getParameter<edm::InputTag>("triggerObjectss"))),
  triggerResultsToken_(consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("triggerResultss"))),
  offlineMuonsToken_(consumes<MuonCollection>(iConfig.getParameter<edm::InputTag>("offlineMuons"))) 
// objectMapToken_(consumes<GlobalObjectMapRecord > (iConfig.getParameter<edm::InputTag>("obbjectMap")))
 // offlineMuonsToken_(consumes<std::vector<reco::Muon> >(iConfig.getParameter<edm::InputTag>("offlineMuons")))


 // deltaRThreshold_(iConfig.getParameter<double>("deltaRThreshold"))
{}

MuonTriggerMatch2::~MuonTriggerMatch2()
{}

void MuonTriggerMatch2::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
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

//  auto triggerObjects = triggerEvent->getObjects();
//  const edm::TriggerNames& trigNames = iEvent.triggerNames(*trigResults); 

/*
std::cout << "Trigger names:" << std::endl;
for (unsigned int i = 0; i < trigNames.size(); ++i) {
  std::cout << trigNames.triggerName(i) << std::endl;
} 
*/

//std::string pathName="HLT_HIUPC_SingleMuOpen_NotMBHF2AND_v4";
//bool passTrig=trigResults->accept(trigNames.triggerIndex(pathName));  

/*
std :: cout <<"passed Trigger" << passTrig << std::endl;

  int nTriggerMuons = 0;
  for (size_t i = 0; i < triggerObjects.size(); ++i) {
    if(triggerObjects[i].pt() >0 ) std:: cout <<"trigger obj eta = " << triggerObjects[i].eta() <<" ,obj phi= "<<triggerObjects[i].phi() << " ,obj pt = "<< triggerObjects[i].pt() << " , obj mass=" << triggerObjects[i].mass()<<std::endl; 
     if (triggerObjects[i].id() == trigger::TriggerMuon) {
                  nTriggerMuons++;
                     }
               }
*/

   // std::string pathName =  "HLT_HIZeroBias_v4"; //  "HLT_HIUPC_SingleMuOpen_NotMBHF2AND_v4";
   // bool passTrig = trigResults->accept(trigNames.triggerIndex(pathName));


   /* std::cout << "Trigger names:" << std::endl;
      for (unsigned int i = 0; i < trigNames.size(); ++i) {
      std::cout << trigNames.triggerName(i) << std::endl;
    } */

 // std::vector<std::string> triggerNamesVec;
 // std::cout << "Trigger names:" << std::endl;

  for (unsigned int i = 0; i < trigNames.size(); ++i) {

      std::string triggerName = trigNames.triggerName(i);
      bool passTrig = trigResults->accept(trigNames.triggerIndex(triggerName));
if(passTrig){
      std::cout << "fired trigger name= "<< triggerName << std::endl;
 //     triggerNamesVec.push_back(triggerName);
    }
}


//    std::cout << "Passed Trigger: " << passTrig << std::endl;



// print the number of fired trigger:

//for (unsigned int i = 0; i < trigNames.size(); ++i) {  
//      std::cout << trigNames.triggerName(i) << std::endl;
//    }


/*
    if (passTrig) {
        std::string firedTrig = "";
        for (unsigned int i = 0; i < trigNames.size(); ++i) {
            if (trigResults->accept(i)) {
                firedTrig = trigNames.triggerName(i);
               break;
            }
        }
        std::cout << "Trigger  " << firedTrig << " fired." << std::endl;
     }
*/

/*
 if (passTrig) {
    std::cout << "Trigger objects:" << std::endl;
    const trigger::TriggerObjectCollection& toc(triggerEvent->getObjects());
    for (size_t i = 0; i < triggerEvent->sizeFilters(); i++) {
      if (triggerEvent->filterTag(i) == pathName) {
        const trigger::Keys& keys = triggerEvent->filterKeys(i);
        for (trigger::Keys::const_iterator keyIt = keys.begin(); keyIt != keys.end(); ++keyIt) {
          trigger::size_type objIndex = (*keyIt);
          std::cout <<"index for object= " << objIndex <<std::endl;
          const trigger::TriggerObject& obj = toc[objIndex];
          std::cout << "Trigger object - pt: " << obj.pt() 
                    << ", eta: " << obj.eta() << ", phi: "
                    << obj.phi() << ", mass: " << obj.mass() << std::endl;
        }
      }
    }
  }
*/

for (unsigned int i = 0; i < trigResults->size(); ++i) {
  std::string pathName = trigNames.triggerName(i);
  bool pathFired = trigResults->accept(i);
firedpath = pathFired;
/*
 if (pathFired) {
 GlobalObjectMap::const_iterator  objs = objectMap.find(pathName);
    if (objs != objectMap.end()) {
    // Loop over the trigger objects and do something with them
    for (size_t j = 0; j < objs->second.size(); ++j) {
    const trigger::TriggerObject& obj = objs->second.at(j).second;
    
     std::cout<< "the trigger object from map method "  
                 << " , eta" << obj.eta()
                 << " , phi: " << obj.phi()
                 << " , pt: " << obj.pt()
                 << " , mass:  " << obj.mass()
                 << " , id:  " << obj.id() << std::endl;
          }
        }
  }*/

//const GlobalObjectMap& objectMap = *objectMapp;
//const GlobalObjectMap& objectMap = objectMapp->gtObjectMap();
/*

   if (pathFired) {
    auto objs = objectMapp.find(pathName);
    if (objs != objectMapp.end()) {
        for (auto it = objs->second.begin(); it != objs->second.end(); ++it) {
            const trigger::TriggerObject& obj = it->second;

            std::cout << "the trigger object from map method "
                      << " , eta" << obj.eta()
                      << " , phi: " << obj.phi()
                      << " , pt: " << obj.pt()
                      << " , mass:  " << obj.mass()
                      << " , id:  " << obj.id() << std::endl;
        }
    }
}
*/

}


//bool passTrig=1;
if (firedpath) {
/*
 GlobalObjectMap::const_iterator objs = objectMap->find(pathName);
    if (objs != objectMap->end()) {
    // Loop over the trigger objects and do something with them
    for (size_t j = 0; j < objs->second.size(); ++j) {
    const trigger::TriggerObject& obj = objs->second.at(j).second;
                       // ...
                 }
                   }
                                  
*/


    // Print trigger object info for objects that pass the trigger
 for (size_t i = 0; i < triggerObjects.size(); ++i) {
 if (triggerObjects[i] .pt() > 0){
//&& triggerObject[i].id() == trigger::TriggerMuon ) { 
//std :: cout << "trigger::TriggerMuon= "<<trigger::TriggerMuon<<" , obj id= "<< triggerObjects[i].id() <<std::endl;
       std::cout << "Trigger obj eta: " << triggerObjects[i].eta() 
                 << ", phi: " << triggerObjects[i].phi()
                 << " , pt: " << triggerObjects[i].pt()
                 << " , mass:  " << triggerObjects[i].mass()
                 << " , id:  " << triggerObjects[i].id() << std::endl;}
                   }
              }

for (size_t j = 0; j < offlineMuons->size(); ++j) { 
     const reco::Muon& offlineMuon = (*offlineMuons)[j];
     std::cout <<"offline Moun Eta= " << offlineMuon.eta()
               << " ,Muon phi= "<<offlineMuon.phi()
               << " ,Muon Pt= " << offlineMuon.pt()
               <<" ,Muon mass" << offlineMuon.mass() << std::endl;
    }

   //  std::cout << "Number of trigger muon candidates: " << nTriggerMuons << std::endl;
  // Loop over all trigger objects
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
}                                             


DEFINE_FWK_MODULE(MuonTriggerMatch2);


