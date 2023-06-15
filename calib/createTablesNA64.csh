#!/bin/tcsh -f

#a dummy script to create all the tables

set command = "ccdb -c mysql://ccdb_user@jdaq8/ccdb"

#DAQ
set DAQFolder = "/DAQ"
set DAQIndexes = "crate=int slot=int channel=int"
set DAQPedestalLines = 6400
echo "DAQ peds and parms"
$command mkdir $DAQFolder
$command mktbl $DAQFolder/pedestals -r $DAQPedestalLines $DAQIndexes pedestal=double rms=double "#daq pedestals and RMS in fadc counts"
$command mktbl $DAQFolder/parms -r $DAQPedestalLines $DAQIndexes LSB=double P2=double P3=double P4=double P5=double "#daq LSB and other parms"

#Calorimeter
set CalorimeterFolder = "/Calorimeter"
set CalorimeterIndexes = "sector=int x=int y=int readout=int"
set CalorimeterSipmGainLines = 40000
set CalorimeterEneLines = 8000


echo "Calorimeter"
$command mkdir $CalorimeterFolder
echo "wb_thr"
$command mktbl $CalorimeterFolder/wb_thr -r $CalorimeterSipmGainLines  $CalorimeterIndexes thr=double "#fadc signals THR"
echo "wb_gain"
$command mktbl $CalorimeterFolder/wb_gain -r $CalorimeterSipmGainLines  $CalorimeterIndexes wb_gain=double "#wb gain"
echo "ene"
$command mktbl $CalorimeterFolder/Ene -r $CalorimeterEneLines  $CalorimeterIndexes ene=double ped=double "#energy calibration and pedestal"


exit

#Inner Veto
set InnerVetoFolder = "/InnerVeto"
set InnerVetoIndexes = "sector=int layer=int component=int readout=int"
set InnerVetoSipmGainLines = 8000
set InnerVetoSipmAmplLines = 8000
set InnerVetoEneLines = 1600

echo "InnerVeto"
$command mkdir $InnerVetoFolder
echo "Sipm gain"
$command mktbl $InnerVetoFolder/sipm_gain -r $InnerVetoSipmGainLines $InnerVetoIndexes sipm_gain=double ped=double "#sipm gain and pedestal"
echo "Sipm ampl"
$command mktbl $InnerVetoFolder/sipm_ampl -r $InnerVetoSipmAmplLines $InnerVetoIndexes sipm_ampl=double "#sipm ampl"
#echo "Ene"
#$command mktbl $InnerVetoFolder/Ene -r $InnerVetoEneLines $InnerVetoIndexes sipm_gain=double "#ene readout is always 0"

