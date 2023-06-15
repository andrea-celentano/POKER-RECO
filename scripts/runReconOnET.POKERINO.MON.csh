#!/bin/tcsh -f

if ($#argv != 1) then
        echo "use: runReconOnET.POKERINO.csh runNumber"
        exit
endif

set runNumber = $1

echo runReconOnET: RunNumber is: $1

#this is the command
#need to connect to the et with the syntax:  ET:sessionName:stationName:host:port


#Local DB
setenv JANA_CALIB_URL mysql://ccdb_user@jdaq8/ccdb

$BDXRECO_ROOT/bin/bdxReco --config=$BDXRECO_ROOT/config/bdx.config.POKERINO.online -PPLUGINS=monitoring_rootspy,monitoring_DAQWaveformsMode1,monitoring_NA64EcalHits,monitoring_Trigger ET:bdxtest:MON:jdaq8:11111
#monitoring_WBHits,
