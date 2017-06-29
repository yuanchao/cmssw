import FWCore.ParameterSet.Config as cms

metFiltersMiniAOD =cms.EDFilter(
  "HLTHighLevel"
, TriggerResultsTag  = cms.InputTag( 'TriggerResults::HLT' )
, andOr              = cms.bool( False )
, throw              = cms.bool( False )
, eventSetupPathsKey = cms.string( '' )
, HLTPaths           = cms.vstring( 'Flag_METFilters' )
)
