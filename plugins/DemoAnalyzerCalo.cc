#include <memory>

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/CaloTowers/interface/CaloTower.h"

#include "TFile.h"
#include "TTree.h"
#include "TH2F.h"



class DemoAnalyzerCalo : public edm::EDAnalyzer {
public:
  explicit DemoAnalyzerCalo(const edm::ParameterSet&);
  virtual ~DemoAnalyzerCalo() {}
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  void beginJob() override;

private:
 
   TH2F* h_eta_energy_;
   TH2F* HFPvsHFM_;
  edm::EDGetTokenT<edm::SortedCollection<CaloTower>> hfTowerLabel_;
  double leadingTowerPtMin_;
  double leadingTowerEtaMax_;
  double leadingTowerPhiMin_;
  double leadingTowerPhiMax_;
  double leadingTowerEnergyHFPt_; 

//  TH2F* h_eta_energy_;

 // void beginJob() override;
 // void analyze(const edm::Event&, const edm::EventSetup&) override;
 // void endJob() override;

 // uint32_t nbins_;
 // double minBin_;
 // double maxBin_;
 // std::string outputFileName_;
  TTree* caloTree_;
  double leadingTowerEnergyHF_;
  double leadingTowerEnergyHFP_;
  double leadingTowerEnergyHFM_;
  double leadingTowerEnergyEta_;
  // ----------member data ---------------------------
  //edm::EDGetTokenT<TrackCollection> tracksToken_;  //used to select what tracks to read from configuration file
     #ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  edm::ESGetToken<SetupData, SetupRecord> setupToken_;
       #endif

};

DemoAnalyzerCalo::DemoAnalyzerCalo(const edm::ParameterSet& cfg) :
  hfTowerLabel_(consumes<edm::SortedCollection<CaloTower>>(cfg.getUntrackedParameter<edm::InputTag>("calos"))),
  leadingTowerPtMin_(cfg.getParameter<double>("leadingTowerPtMin")),
  leadingTowerEtaMax_(cfg.getParameter<double>("leadingTowerEtaMax")),
  leadingTowerPhiMin_(cfg.getParameter<double>("leadingTowerPhiMin")),
  leadingTowerPhiMax_(cfg.getParameter<double>("leadingTowerPhiMax"))
//  nbins_(cfg.getParameter<uint32_t>("nbins")),
 // minBin_(cfg.getParameter<double>("minBin")),
//  maxBin_(cfg.getParameter<double>("maxBin"))
{

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  setupDataToken_ = esConsumes<SetupData, SetupRecord>();
#endif

 // edm::Service<TFileService> fsss;
 // caloTree_ = fsss->make<TTree>("HFPcalo", "Tree for Leading Tower Energy");

 // caloTree_ = new TTree("HFPcalo", "Tree for Leading Tower Energy");
 // caloTree_->Branch("leadingTowerEnergy", &leadingTowerEnergyHFP_, "leadingTowerEnergyHFP_/D");
//h_eta_energy_ = fs->make<TH2F>("h_eta_energy", "Eta vs Leading Tower Energy",
  //                                 1000, -10.0, 10.0, 1000, 0.0, 100.0);

}


void DemoAnalyzerCalo::analyze(const edm::Event& event, const edm::EventSetup& setup)
{
  leadingTowerEnergyHF_ = 0;
  leadingTowerEnergyHFP_ = 0;
  leadingTowerEnergyHFM_ = 0;

//double hitEta_ = 0.0;

/* for ( const auto  hit : event.get(hfTowerLabel_) ){
   if (fabs(hit.id().ieta()) > leadingTowerEtaMax_ && hit.energy() > leadingTowerEnergyHFP_) 
 {
  leadingTowerEnergyHFP_ = hit.energy();  
  hitEta_ = hit.id().ieta();
  }
}
*/

for (const auto& tower : event.get(hfTowerLabel_)) {
if (fabs(tower.eta()) > 3 && tower.energy() > leadingTowerEnergyHF_) 
   {
   leadingTowerEnergyHF_ = tower.energy();
   leadingTowerEnergyEta_ = tower.eta();
   leadingTowerEnergyHFPt_ = tower.pt();
   }

if ( tower.eta() > 3 && tower.eta() <5 && tower.energy() > leadingTowerEnergyHFP_)                   
   {
   leadingTowerEnergyHFP_ = tower.energy();
   }

if ( tower.eta() < -3 && tower.eta() > -5 && tower.energy() > leadingTowerEnergyHFM_)
   {
   leadingTowerEnergyHFM_ = tower.energy();
   }

}



if (leadingTowerEnergyHF_ > 0.0) 
{
 caloTree_->Fill();
 std::cout <<" one caleo heres" <<std::endl; 
 h_eta_energy_->Fill(leadingTowerEnergyEta_, leadingTowerEnergyHF_ );
 HFPvsHFM_ ->Fill(leadingTowerEnergyHFM_, leadingTowerEnergyHFP_);
// std::cout <<"hitEta_ " << hitEta_ << ", " << "leadingTowerEnergyHFP_" << leadingTowerEnergyHFP_ <<std::endl;
}

}
/*
for (const auto& tower : event.get(hfTowerLabel_)) {
  if (fabs(tower.eta()) > leadingTowerEtaMax_ && tower.energy() > leadingTowerEnergyHFP_) {
    leadingTowerEnergyHFP_ = tower.energy();
 //   CaloTowerDetId towerId = tower.id();
 //   hitEta_ = towerId.ieta();
    hitEta_ = tower.eta();
  }
}

*/

// ------------ method called once each job just before starting event loop  ------------
 void DemoAnalyzerCalo::beginJob() {
//   // please remove this method if not needed
//     edm::Service<TFileService> fs;
// edm::Service<TFileService> fs;
 //        trackTree_ = fs->make<TTree>("tracksTree", "Tree for Tracks");
//
//             // trackTree_ = new TTree("tracksTree", "Tree for Tracks");
//                  trackTree_->Branch("trackPt", &trackPt_, "trackPt_/D");
//                      trackTree_->Branch("trackEta", &trackEta_, "trackEta_/D");
  edm::Service<TFileService> fs;
 //  TH2F* h_eta_energy_;
 
  h_eta_energy_ = fs->make<TH2F>("h_eta_energy", "Eta vs Leading Tower Energy",
                                   1000, -10.0, 10.0, 1000, 0.0, 100.0);

  HFPvsHFM_ = fs->make<TH2F>("HFPvsHFM", "HFP vs HFP- leading tower energy",
                                   1000, 0.0, 100.0, 1000, 0.0, 100.0);

  caloTree_ = fs->make<TTree>("HFPcalo", "Tree for Leading Tower Energy");
 /// caloTree_ = new TTree("HFPcalo", "Tree for Leading Tower Energy");
  caloTree_->Branch("leadingTowerEnergyHF", &leadingTowerEnergyHF_, "leadingTowerEnergyHF_/D");
  caloTree_->Branch("leadingTowerEnergyHFP", &leadingTowerEnergyHFP_, "leadingTowerEnergyHFP_/D");
  caloTree_->Branch("leadingTowerEnergyHFM", &leadingTowerEnergyHFM_, "leadingTowerEnergyHFM_/D");
  caloTree_->Branch("leadingTowerEnergyEta", &leadingTowerEnergyEta_, "leadingTowerEnergyEta_/D");
  caloTree_->Branch("leadingTowerEnergyHFPt", &leadingTowerEnergyHFPt_, "leadingTowerEnergyHFPt_/D");


//  TH2F* h_eta_energy_;
                                               
                        }


DEFINE_FWK_MODULE(DemoAnalyzerCalo);
