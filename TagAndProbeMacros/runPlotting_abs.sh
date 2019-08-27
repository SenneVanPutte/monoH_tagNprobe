#!/bin/bash

AllFiles="/user/svanputt/monoHiggs/TnP/CMSSW_9_4_9/src/TagAndProbe_Trigger/TagAndProbeMacros/AllRootFiles.txt"

if [[ "$#" -lt 1 ]]; 
then
    echo " "
    echo "====>>  no argument is passed. Pass either histNames_Ele.txt OR histNames_Mu.txt"
    echo " "
    exit
fi

if [[ "$#" -lt 2 ]];
then
HistFiles=$1
fi

if [[ "$#" -eq 2 ]];
then
    AllFiles=$1
    HistFiles=$2
fi

PLOT_MAC="/user/svanputt/monoHiggs/TnP/CMSSW_9_4_9/src/TagAndProbe_Trigger/TagAndProbeMacros/plotEfficiency.C"
root -l -b -q "$PLOT_MAC(\"$AllFiles\",\"$HistFiles\")"  
