#!/bin/bash

CMACRO=$1  # TagAndProbe_Ele.C or TagAndProbe_Mu.C
EXEC="tnp"
PWD=`pwd`

if [[ "$CMACRO" =~ "Ele" ]]; then
    LEP="Electron"
fi
if [[ "$CMACRO" =~ "Mu" ]]; then
    LEP="Muon"
fi

ls -d */ | grep $LEP | grep 2016
echo "Enter working & output dir"
read OUT_DIR_tr
OUT_DIR="$(echo $OUT_DIR_tr | sed 's:/$::')"

if [[ ! -d "$OUT_DIR" ]]; then
    mkdir $OUT_DIR
fi

if [[ "$#" -lt 1 ]];
then
    echo " "
    echo "====>>  no argument is passed. Pass either TagAndProbe_Ele.C OR TagAndProbe_Mu.C"
    echo " "
    exit
fi

if [[ "$CMACRO" =~ "Ele" ]]; then
    echo "compiling for electron : $CMACRO" 
    EXEC="tnp_Ele"
    JBN="$(echo $OUT_DIR | sed 's:Electron:Ele:')"
fi
if [[ "$CMACRO" =~ "Mu" ]]; then
    echo " "
    echo "compiling for muon : $CMACRO"
    echo " "
    EXEC="tnp_Mu"
    JBN="$(echo $OUT_DIR | sed 's:Muon:Mu:')"
fi


#echo "g++ Run_TnP.cxx -o $OUT_DIR/$EXEC  -std=c++0x `root-config --libs --cflags` -include $CMACRO"
g++ Run_TnP_16.cxx -o $OUT_DIR/$EXEC  -std=c++0x `root-config --libs --cflags` -include $CMACRO


############  Enter the name of text file in which root files are entered

echo " "
echo "1) Run Interactively : Enter : 0"
echo "2) Run in lxplus batch : Enter : 1"
echo " "

read run
if [[ $run == 0 ]]; then
#ls $OUT_DIR -ltrh *.txt
find "$OUT_DIR" | grep .txt
echo "You are running in interactive mode!!!"
echo "Enter the name of text file having all the root files"
read textFile
FirstFile=`head -1 $textFile`
if [[ "$FirstFile" =~ "root://" ]];   # If your files are present not at cern then access files through xrootd services. That needs to generate a valid proxy.
then
        echo " "
        echo "==== need to generate proxy, since it is going to use xrootd services"
        echo "==== running voms-proxy-init --voms cms first ===="
        echo "==== Enter password to generate proxy ===="
        echo " "
        voms-proxy-init --voms cms --valid 168:00
       echo "-------------------------------"
       echo "---"
       echo "---   now running ./$EXEC $textFile  "
       echo "---"
       echo "-------------------------------"
       ./$EXEC $textFile
else
       echo "-------------------------------"
       echo "---"
       echo "---   now running ./$EXEC $textFile  "
       echo "---"
       echo "-------------------------------"
     ./$EXEC $textFile
  fi
fi

if [[ $run == 1 ]]; then 
#ls $OUT_DIR -ltrh *.txt
find "$OUT_DIR" | grep .txt
echo "You are going to submit jobs on lxplus batch!!!"
echo "Enter the name of text file having all the root files"
read textFile
echo "-------------------------------"
echo "---"
echo "---   now running ./$EXEC TEXT_File_WITH_ALL_ROOT_FILES  "
echo "---"
echo "-------------------------------"
FirstFile=`head -1 $textFile`
echo $FirstFile
if [[ "$FirstFile" =~ "root://" ]];   # If your files are present not at cern then access files through xrootd services. That needs to generate a valid proxy.
then
    if [[ `ls` =~ "x509up" ]]; then  
        TimeLeft=`voms-proxy-info | cut -d ":"  -f 2 | sed 's/ Digital .*//' | tail -c 5`
        echo $TimeLeft
        if [[ $TimeLeft -lt 10 ]]; then
        echo "Having a vaild proxy with less than 10 hours left. Better generate a new proxy again."
        echo "==== running voms-proxy-init --voms cms first ===="
        echo "==== Enter password to generate proxy ===="
        voms-proxy-init --voms cms --valid 168:00
        cp `voms-proxy-info --path` .  ### if ntuple is not at cern eos then proxy is needed
        fi
    else
        echo "==== running voms-proxy-init --voms cms first ===="
        echo "==== Enter password to generate proxy ===="
        voms-proxy-init --voms cms --valid 168:00
        echo "copying the generated proxy file from /tmp to $PWD"
        cp `voms-proxy-info --path` .  ### if ntuple is not at cern eos then proxy is needed
    fi
     echo "Enter the name of File which you want to submit on lxplus batch queue : "
     read batchFileName
     if [[ `ls` =~ $batchFileName ]]; then
         echo "Deleting the existing $batchFileName  and creating a fresh one"
         rm $batchFileName 
     fi
     touch $batchFileName
     echo "#!/bin/bash" >> $batchFileName
     echo "cd $CMSSW_BASE/src/TagAndProbe_Trigger/TagAndProbeMacros" >> $batchFileName
     echo "export X509_USER_PROXY=\`ls x509up*\`" >> $batchFileName
     echo "./$EXEC $textFile" >> $batchFileName
     bsub -q $QUEUE < $batchFileName
else
    echo "All files listed in text file either present in local or at cern itself"
    echo "Do you want to run interactively then press y or Y else job will be submit to batch queues"
    read Decision
    if [[ $Decision == y ]] || [[ $Decision == Y ]]; then
        ./$EXEC $textFile
    else
     if [[ ! -d $OUT_DIR/job ]]; then
         mkdir $OUT_DIR/job
     fi
     #echo "Enter the name of File which you want to submit on lxplus batch queue : "
     #read batchFileName #condor_submit
     batchFileName="$(echo $OUT_DIR | sed 's:/:_:')"

     QUEUE="localgrid"
     JDL_FILE=$batchFileName.jdl 
     SH_FILE=$batchFileName.sh
     
     echo "Will create $SH_FILE and submit to creamX.iihe.ac.be"

     OUT_FILE=job/$batchFileName.out 
     ERR_FILE=job/$batchFileName.err 
     LOG_FILE=job/$batchFileName.log 
     
     if [[ -f $OUT_DIR/$SH_FILE ]]; then
         echo "Deleting the existing $OUT_DIR/$SH_FILE  and creating a fresh one"
         rm $OUT_DIR/$SH_FILE
     fi
     touch $OUT_DIR/$SH_FILE
     echo "#!/bin/bash" >> $OUT_DIR/$SH_FILE
     echo "source $VO_CMS_SW_DIR/cmsset_default.sh" >> $OUT_DIR/$SH_FILE
     echo "cd $PWD" >> $OUT_DIR/$SH_FILE
     echo "cd $CMSSW_BASE/src" >> $OUT_DIR/$SH_FILE
     echo "eval \`scram runtime -sh\`" >> $OUT_DIR/$SH_FILE 
     echo "cd \$TEMPDIR" >> $OUT_DIR/$SH_FILE
     #echo "mkdir lite_$OUT_DIR" >> $OUT_DIR/$SH_FILE
     echo "mkdir $OUT_DIR" >> $OUT_DIR/$SH_FILE
     #echo "cd lite_$OUT_DIR" >> $OUT_DIR/$SH_FILE
     echo "cd $OUT_DIR" >> $OUT_DIR/$SH_FILE
     echo "cp $PWD/$OUT_DIR/$EXEC execy" >> $OUT_DIR/$SH_FILE
     #echo "./$OUT_DIR/$EXEC $textFile" >> $OUT_DIR/$SH_FILE
     echo "./execy $PWD/$textFile" >> $OUT_DIR/$SH_FILE
     echo "echo \"-- root files present: \"" >> $OUT_DIR/$SH_FILE
     echo "ls -larth | grep .root" >> $OUT_DIR/$SH_FILE
     echo "mv \"efficiency_TagPt_down.root\" $PWD/$OUT_DIR/." >> $OUT_DIR/$SH_FILE
     echo "mv \"efficiency_TagPt_up.root\" $PWD/$OUT_DIR/." >> $OUT_DIR/$SH_FILE
     echo "mv \"efficiency_Zmass_down.root\" $PWD/$OUT_DIR/." >> $OUT_DIR/$SH_FILE
     echo "mv \"efficiency_Zmass_up.root\" $PWD/$OUT_DIR/." >> $OUT_DIR/$SH_FILE
     echo "mv \"efficiency_nominal.root\" $PWD/$OUT_DIR/." >> $OUT_DIR/$SH_FILE
     echo "echo \"-- root files still present: \"" >> $OUT_DIR/$SH_FILE
     echo "ls -larth | grep .root" >> $OUT_DIR/$SH_FILE

     

     if [[ -f  $OUT_DIR/$JDL_FILE ]]; then
         echo "Deleting the existing $OUT_DIR/$JDL_FILE  and creating a fresh one"
         rm $OUT_DIR/$JDL_FILE
     fi
     touch $OUT_DIR/$JDL_FILE
     echo "universe = vanilla" >> $OUT_DIR/$JDL_FILE
     echo "Executable = $SH_FILE" >> $OUT_DIR/$JDL_FILE
     echo "Output = $OUT_FILE" >> $OUT_DIR/$JDL_FILE
     echo "Error  = $ERR_FILE" >> $OUT_DIR/$JDL_FILE
     echo "Log    = $LOG_FILE" >> $OUT_DIR/$JDL_FILE
     echo "+JobFlavour = \"$QUEUE\"" >> $OUT_DIR/$JDL_FILE
     echo "Queue" >> $OUT_DIR/$JDL_FILE 

     cd $OUT_DIR
     #condor_submit $JDL_FILE
     #echo "Submitting: qsub -o $OUT_FILE -e $ERR_FILE $SH_FILE -q express -N $JBN"
     echo "Submitting: qsub -o $OUT_FILE -e $ERR_FILE $SH_FILE -q $QUEUE -N $JBN"
     #qsub -o $OUT_FILE -e $ERR_FILE $SH_FILE -q express -N $JBN 
     qsub -o $OUT_FILE -e $ERR_FILE $SH_FILE -q $QUEUE -N $JBN 

     #if [[ `ls` =~ $batchFileName ]]; then
     #    echo "Deleting the existing $batchFileName  and creating a fresh one"
     #    rm $batchFileName 
     #fi  
     #touch $batchFileName
     #echo "#!/bin/bash" >> $batchFileName
     #echo "cd $CMSSW_BASE/src/TagAndProbe_Trigger/TagAndProbeMacros" >> $batchFileName
     #echo "./$EXEC $textFile" >> $batchFileName
     #bsub -q $QUEUE < $batchFileName
    fi

 fi  ## check name of root files

fi   ## Run = 1





