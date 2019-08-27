#!/bin/bash

ver="v8"

for run in "B" "C" "D" "E" "F" "G" "H"
do 
    find /pnfs/iihe/cms/store/user/svanputt/monoHiggs/Electron_Ntuple_2016_monoH_Triggers_$ver/SingleElectron/Run2016${run}_$ver/*/0000/ | grep .root > Electron_Run2016${run}/Electron_Run2016${run}_rootfiles.txt

    #find /pnfs/iihe/cms/store/user/svanputt/monoHiggs/Muon_Ntuple_2016_monoH_Triggers_$ver/SingleMuon/Run2016${run}_$ver/*/0000/ | grep .root > Muon_Run2016${run}/Muon_Run2016${run}_rootfiles.txt
done 
