import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:myfile.root'
    )
)

process.TFileService = cms.Service("TFileService",
      fileName = cms.string('output.root')
      )

process.fcncKit = cms.EDAnalyzer('MyFCNCkit',
      MCtag = cms.untracked.bool(False),
      muonlabel = cms.InputTag("intermediatePatMuonsPF"),
      eleclabel = cms.InputTag("intermediatePatElectronsPF"),
      pfjetlabel= cms.InputTag("selectedPatJetsPF"),
      metlabel  = cms.InputTag("patMETsPF"),
      genlabel  = cms.InputTag("genParticles"),
      hltlabel  = cms.InputTag("TriggerResults::HLT"),
      pathltlabel = cms.InputTag("patTriggerEvent"),
      offlinePVlabel = cms.InputTag("offlinePrimaryVertices"),
      offlinePVBSlabel = cms.InputTag("offlinePrimaryVerticesWithBS"),
      offlineBSlabel = cms.InputTag("offlineBeamSpot"),
      pixelvtxlabel = cms.InputTag("pixelVertices"),
      genevtlabel = cms.InputTag("generator"),
      gtdigilabel = cms.InputTag("gtDigis"),
#      rhocorrectionlabel = cms.InputTag("kt6PFJetsPFlow","rho"),
#      sigmaLabel = cms.InputTag("kt6PFJetsPFlow","sigma"),
      puInfoLabel = cms.InputTag("addPileupInfo")


)


process.p = cms.Path(process.fcncKit)
