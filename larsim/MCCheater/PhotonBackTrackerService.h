////////////////////////////////////////////////////////////////////////
//
// \file: PhotonBackTrackerServiceService_service.cc
//
//jason.stock@mines.sdsmt.edu
//Based on the BackTracker_service by Brian Rebel
//
////////////////////////////////////////////////////////////////////////
#ifndef CHEAT_PHOTONBACKTRACKERSERVICESERVICE_H
#define CHEAT_PHOTONBACKTRACKERSERVICESERVICE_H

//INCLUDES
#include <map>

// Framework includes
#include "fhiclcpp/ParameterSet.h"
#include "art/Framework/Services/Registry/ActivityRegistry.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/View.h"
#include "messagefacility/MessageLogger/MessageLogger.h"

// LArSoft includes
#include "larcorealg/Geometry/GeometryCore.h"
#include "larsim/Simulation/SimListUtils.h"
#include "larsim/MCCheater/PhotonBackTracker.h"
//Larsoft Services
#include "larsim/MCCheater/ParticleInventoryService.h"
#include "larcore/Geometry/Geometry.h"
#include "lardata/DetectorInfoServices/DetectorClocksService.h"


//#include "lardata/Utilities/AssociationUtil.h"
#include "lardataobj/RecoBase/OpHit.h"
//#include "lardataobj/Simulation/sim.h"

namespace cheat{
  class PhotonBackTrackerService: private PhotonBackTracker
  {
    public:
      struct fhiclConfig{
        fhicl::Table <PhotonBackTracker::fhiclConfig> PhotonBackTrackerTable{
          fhicl::Name("PhotonBackTracker"),
            fhicl::Comment("This if the fhicl configuration of the PhotonBackTracker service provider.")
        };
      };

      using provider_type = PhotonBackTracker;
      const provider_type* provider() const
      {return static_cast<provider_type const*>(this);}

      PhotonBackTrackerService(const fhicl::ParameterSet& pSet, art::ActivityRegistry& reg);
      PhotonBackTrackerService(const fhiclConfig& config, art::ActivityRegistry& reg);

      //Temporarily include a rebuild function until the lazy rebuild works.

      void Rebuild( const art::Event& evt);

      ///////////////////////////////////////////////
      /////BackTracking Functions Implimentation/////
      // This section contains the implimentation  //
      // of all PhotonBackTrackerService end user  //
      // functionality                             //
      ///////////////////////////////////////////////


      //----------------------------------------------------------------------
      const std::vector< art::Ptr< sim::OpDetBacktrackerRecord >>& OpDetBTRs() ;
      const std::vector< const sim::SDP* > TrackIdToSimSDPs_Ps(int const& id);
      const std::vector< const sim::SDP* > TrackIdToSimSDPs_Ps(int const& id, geo::View_t const& view);
      const art::Ptr< sim::OpDetBacktrackerRecord > FindOpDetBTR(int const& opDetNum); 
      const std::vector < sim::TrackSDP > OpDetToTrackSDPs( int const& OpDetNum, 
          double const& opHit_start_time, double const& opHit_end_time);
      std::vector<sim::TrackSDP> OpHitToTrackSDPs(art::Ptr<recob::OpHit> const& opHit);
      std::vector<sim::TrackSDP> OpHitToTrackSDPs(recob::OpHit const& opHit);
      const std::vector < int > OpHitToTrackIds(recob::OpHit const& opHit);
      std::vector<sim::TrackSDP> OpHitToEveTrackSDPs(art::Ptr<recob::OpHit> const& opHit);
      std::vector<sim::TrackSDP> OpHitToEveTrackSDPs(recob::OpHit const& opHit);
      const std::vector<art::Ptr<recob::OpHit>> TrackIdToOpHits_Ps(const int& tkId, std::vector<art::Ptr<recob::OpHit>> const& hitsIn);
      const std::vector<std::vector<art::Ptr<recob::OpHit>>> TrackIdsToOpHits_Ps(std::vector<int> const& tkIds, std::vector<art::Ptr<recob::OpHit>> const& hitsIn);
      const std::vector< const sim::SDP* > OpHitToSimSDPs_Ps(recob::OpHit const& opHit) ;
      const std::vector< const sim::SDP* > OpHitToSimSDPs_Ps(art::Ptr<recob::OpHit> const& opHit) ;
      const std::vector< double> SimSDPsToXYZ(std::vector<sim::SDP> const& sdps) const& ;
      const std::vector< double> SimSDPsToXYZ(std::vector<const sim::SDP*> const& sdps);
      const std::vector< double> OpHitToXYZ(const recob::OpHit& opHit);
      const std::vector< double> OpHitToXYZ(art::Ptr<recob::OpHit> const& opHit);
      const std::set< int> GetSetOfEveIds();
      const std::set< int> GetSetOfTrackIds();
      const std::set< int> GetSetOfEveIds(std::vector< art::Ptr<recob::OpHit> > const& opHits);
      const std::set< int> GetSetOfTrackIds(std::vector< art::Ptr<recob::OpHit> > const& opHits);
      const double OpHitCollectionPurity(std::set<int> const& tkIds, 
          std::vector< art::Ptr<recob::OpHit> > const& opHits);
      const double OpHitLightCollectionPurity(std::set<int> const& tkIds, 
          std::vector< art::Ptr<recob::OpHit> > const& opHits);
      const double OpHitCollectionEfficiency(std::set<int> const& tkIds, 
          std::vector< art::Ptr<recob::OpHit> > const& opHits,
          std::vector< art::Ptr<recob::OpHit> > const& opHitsIn,
          geo::View_t const& view);
      const double OpHitCollectionEfficiency(std::set<int> const& tkIds, 
          std::vector< art::Ptr<recob::OpHit> > const& opHits,
          std::vector< art::Ptr<recob::OpHit> > const& opHitsIn);
      const double OpHitLightCollectionEfficiency(std::set<int> const& tkIds, 
          std::vector< art::Ptr<recob::OpHit> > const& opHits,
          std::vector< art::Ptr<recob::OpHit> > const& opHitsIn,
          geo::View_t const& view);
      const double OpHitChargeCollectionEfficiency(std::set<int> const& tkIds, 
          std::vector< art::Ptr<recob::OpHit> > const& opHits,
          std::vector< art::Ptr<recob::OpHit> > const& opHitsIn);

    private:
      //The PhotonBackTrackerService has no parameters.

      void priv_PrepEvent( const art::Event& evt) ;
      void priv_PrepFailed();
      void priv_PrepOpDetBTRs(const art::Event& evt);

      bool priv_CanRun(const art::Event& evt);
      bool priv_OpDetBTRsReady() {return PhotonBackTracker::BTRsReady();}

  }; //Class PhotonBackTrackerService



  //----------------------------------------------------------------------
} // namespace
DECLARE_ART_SERVICE(cheat::PhotonBackTrackerService, LEGACY)

#endif //CHEAT_PHOTONBACKTRACKERSERVICESERVICE_H
