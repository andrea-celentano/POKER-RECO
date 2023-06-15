#!/bin/tcsh -f

if ($#argv != 1) then
        echo "use: runReconOnET.BDXmini.csh runNumber"
        exit
endif

set runNumber = $1

echo runReconOnET: RunNumber is: $1

#this is the command
#need to connect to the et with the syntax:  ET:sessionName:stationName:host:port


#Local DB
#setenv JANA_CALIB_URL sqlite:///$BDXRECO_ROOT/bdx_sqlite.db

setenv JANA_CALIB_URL mysql://bdxreader@clasdb.jlab.org/BDX

$BDXRECO_ROOT/bin/bdxReco --config=$BDXRECO_ROOT/config/bdx.config.BDXmini.online -PPLUGINS=monitoring_rootspy,monitoring_DAQWaveformsMode1,monitoring_Trigger,monitoring_BDXMiniCalorimeterEnergyCalibration,calibration_BDXMiniCalorimeterEnergyCalibrationHit,monitoring_BDXMiniClusters,monitoring_BDXMiniSlowControls ET:bdxtest:MON:jdaq8:11111

# -PSYSTEM:OUTPUT="root,/work/DST/BDX_MINI_ONLINE/$runNumber.onlineReco.root" ET:bdxtest:DSTMaker:jdaq8:11111

