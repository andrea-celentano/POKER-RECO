#!/usr/local/bin/python
# -*- coding: utf-8 -*-

import string,math,os,sys,subprocess
import argparse

#check current working dir
command = "cd "+os.environ['BDXRECO_ROOT']+"/calib ; pwd "
p = subprocess.Popen(command,shell=True,stdout=subprocess.PIPE) 
bdx_fold , err = p.communicate()

command = "pwd"
p = subprocess.Popen(command,shell=True,stdout=subprocess.PIPE) 
cur_fold , err = p.communicate()

if (cur_fold != bdx_fold):
    print "Error, cur folder is ",cur_fold
    print "This script is supposed to run from ",bdx_fold
    sys.exit()

#Chek input arguments
#this should be: -v Variation -min runMin -max runMax
#if variation is not specified, use "default"
#if min and/or max are not specified, used CCDB default behavior



parser = argparse.ArgumentParser(description='Load data in CCDB for given variation / runs')
parser.add_argument('--variation', type=str, default="default", help='If set, set the variation to use. The variation should correspond to a folder with the txt files to upload')
parser.add_argument('--connection', type=str, required=True, help='Connection string')
parser.add_argument('--runMin', type=int,help='If set, set the minimum run number')
parser.add_argument('--runMax', type=int,help='If set, set the maximum run number')

args = parser.parse_args()

variation = args.variation
connection_string = args.connection

if args.runMin== None:
        runMin = -1     
else:                   
        runMin = args.runMin

if args.runMax== None:
        runMax = -1     
else:                   
        runMax = args.runMax

#check if variation folder exists
if (os.path.isdir(variation)==False):
    print "Error, folder",variation,"does not exists"
    sys.exit()

#Proceed with tables loading
#Prepare the command
commandBase = "ccdb -c "+connection_string+" add -v "+variation
if ((runMin != -1)and(runMax != -1)):
    commandBase += " -r "+str(runMin)+"-"+str(runMax)
elif (runMin != -1):
    commandBase += " -r "+str(runMin)+"-"
elif (runMax != -1):
    commandBase += " -r -"+str(runMax)
commandBase +=" "

#Calorimeter
table = "/Calorimeter/sipm_gain "
filen = variation+"/Calorimeter.sipm_gain"
command = commandBase+table+filen
subprocess.call(command,shell=True)

table = "/Calorimeter/Ene "
filen = variation+"/Calorimeter.Ene "
command = commandBase+table+filen
subprocess.call(command,shell=True)

table = "/Calorimeter/thr "
filen = variation+"/Calorimeter.thr "
command = commandBase+table+filen
subprocess.call(command,shell=True)



#InnerVeto
table = "/InnerVeto/sipm_gain "
filen = variation+"/InnerVeto.sipm_gain"
command = commandBase+table+filen
subprocess.call(command,shell=True)

table = "/InnerVeto/sipm_ampl "
filen = variation+"/InnerVeto.sipm_ampl"
command = commandBase+table+filen
subprocess.call(command,shell=True)

#ExtVeto
table = "/ExtVeto/PMT_gain "
filen = variation+"/ExtVeto.PMT_gain"
command = commandBase+table+filen
subprocess.call(command,shell=True)

table = "/ExtVeto/Threshold "
filen = variation+"/ExtVeto.Threshold"
command = commandBase+table+filen
subprocess.call(command,shell=True)

table = "/ExtVeto/Ene "
filen = variation+"/ExtVeto.Ene"
command = commandBase+table+filen
subprocess.call(command,shell=True)

#Paddles
table = "/Paddles/PMT_gain "
filen = variation+"/Paddles.PMT_gain"
command = commandBase+table+filen
subprocess.call(command,shell=True)

table = "/Paddles/Threshold "
filen = variation+"/Paddles.Threshold"
command = commandBase+table+filen
subprocess.call(command,shell=True)

table = "/Paddles/Ene "
filen = variation+"/Paddles.Ene"
command = commandBase+table+filen
subprocess.call(command,shell=True)
