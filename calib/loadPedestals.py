import string,math,os,sys,subprocess
import argparse,glob

#check current working dir
if ("POKERRECO_ROOT" in os.environ)==0:
    print "POKERRECO_ROOT enviromental variable not defined. Exit"
    sys.exit()

command = "cd "+os.environ['POKERRECO_ROOT']+"/calib ; pwd "
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
parser.add_argument('--variation',type=str, default="default", help='If set, set the variation to use.')
parser.add_argument('--connection',type=str,required=True,help="Connection string to use")
parser.add_argument('--firstRun',type=int,default=1000,help="minimum run to consider in the folder")
parser.add_argument('--lastRun',type=int,default=9999,help="maximum run to consider in the folder")
args = parser.parse_args()

variation = args.variation
connection_string = args.connection
firstRun = args.firstRun
lastRun = args.lastRun
#check if DAQ_pedestals folder exists
if (os.path.isdir("DAQ_pedestals")==False):
    print "Error, folder DAQ_pedestals does not exists"
    sys.exit()     

commandBase = "ccdb -c "+connection_string+" add -v "+variation

print "Loading pedestals for variation ",variation," and run_min: ",firstRun


#Depending on variation:

#In case of default, do nothing
if (variation=="default"):
    outF=open("DAQ_pedestals/tables/default.dat","w")
    for crate in range(0,20):
        for slot in range(0,20):
            for channel in range(0,16):
                outF.write(str(crate)+" "+str(slot)+" "+str(channel)+" 0 0 \n")
    outF.close()
    #at this point, we have the file for run 
    #specify in the command
    command = commandBase+" -r "+str(firstRun)+"-"+str(lastRun)
    command += " /DAQ/pedestals DAQ_pedestals/tables/default.dat"
    print command
    subprocess.Popen(command,shell=True)


#In case of other variations, need to open file with slot1 only
else:
    for fn in glob.glob("DAQ_pedestals/run*.ped"): #this may be variation-dependent
        #fn is in the form: absPath/runxxxxx.ped
        fn=os.path.basename(fn)
        run=fn[3:].split('.')[0]
        if (int(run)<firstRun):
            continue
        if (int(run)>lastRun):
            continue
        outF=open("DAQ_pedestals/tables/run_"+run+".dat","w") #this may be variation-dependent
        if ((variation=="JLabFlux0") or (variation=="JLabFlux0_peds")): #Write slot 0, read 1, then write all the others
            slot = 0
            for channel in range(0,16):
                outF.write("0 "+str(slot)+" "+str(channel)+" 0 0 \n")
            with open("DAQ_pedestals/"+fn) as inF:
                for line in inF:
                    data=line.split()
                    slot=data[0]
                    channel=data[1]
                    ped=data[2]
                    RMS=data[3]
                    outF.write("0 "+str(slot)+" "+str(channel)+" "+str(ped)+" "+str(RMS)+"\n")
            inF.close()
            for slot in range(2,20):
                for channel in range(0,16):
                    outF.write("0 "+str(slot)+" "+str(channel)+" 0 0 \n")
        elif ((variation=="BDXmini") or (variation=="BDXmini_peds")):#Write slot 0, read 1,2,3,4, then write all the others
            slot = 0
            for channel in range(0,16):
                outF.write("0 "+str(slot)+" "+str(channel)+" 0 0 \n")
            with open("DAQ_pedestals/"+fn) as inF:
                for line in inF:
                    data=line.split()
                    slot=data[0]
                    channel=data[1]
                    ped=data[2]
                    RMS=data[3]
                    outF.write("0 "+str(slot)+" "+str(channel)+" "+str(ped)+" "+str(RMS)+"\n")
            inF.close()
            for slot in range(5,20):
                for channel in range(0,16):
                    outF.write("0 "+str(slot)+" "+str(channel)+" 0 0 \n")
        elif ((variation=="POKERINO_2023")):#Write slot 0, read 1, then write all the others
            print("VARIATION POKERINO_2023")
            slot = 0
            for channel in range(0,16):
                outF.write("0 "+str(slot)+" "+str(channel)+" 0 0 \n")
            with open("DAQ_pedestals/"+fn) as inF:
                for line in inF:
                    data=line.split()
                    slot=data[0]
                    channel=data[1]
                    ped=data[2]
                    RMS=data[3]
                    outF.write("0 "+str(slot)+" "+str(channel)+" "+str(ped)+" "+str(RMS)+"\n")
            inF.close()
            for slot in range(2,20):
                for channel in range(0,16):
                    outF.write("0 "+str(slot)+" "+str(channel)+" 0 0 \n") 
        elif ((variation=="BDXminiWaveBrd")):#Write slot 0, read 1,2,3,4 ch0..11, then write all the others
            slot = 0
            for channel in range(0,16):
                outF.write("0 "+str(slot)+" "+str(channel)+" 0 0 \n")
            with open("DAQ_pedestals/"+fn) as inF:
                nl=0
                for line in inF:
                    data=line.split()
                    slot=data[0]
                    channel=data[1]
                    ped=data[2]
                    RMS=data[3]
                    outF.write("0 "+str(slot)+" "+str(channel)+" "+str(ped)+" "+str(RMS)+"\n")
            	    nl=nl+1
		    if (nl==12):
			for channel in range(12,16):
				outF.write("0 "+str(slot)+" "+str(channel)+" 0 0 \n")
			nl=0
		inF.close()
            for slot in range(5,20):
                for channel in range(0,16):
                    outF.write("0 "+str(slot)+" "+str(channel)+" 0 0 \n") 
        else:  #Write slots 1-3, then read 4-10, then write 11-19
            for slot in range(0,4):
                for channel in range(0,16):
                    outF.write("0 "+str(slot)+" "+str(channel)+" 0 0 \n")
            with open("DAQ_pedestals/"+fn) as inF:
                for line in inF:
                    data=line.split()
                    slot=data[0]
                    channel=data[1]
                    ped=data[2]
                    RMS=data[3]
                    outF.write("0 "+str(slot)+" "+str(channel)+" "+str(ped)+" "+str(RMS)+"\n")
            inF.close()
            for slot in range(10,20):
                for channel in range(0,16):
                    outF.write("0 "+str(slot)+" "+str(channel)+" 0 0 \n")
        #All variations write other crates
        for crate in range(1,20):
            for slot in range(0,20):
                for channel in range(0,16):
                    outF.write(str(crate)+" "+str(slot)+" "+str(channel)+" 0 0\n")    
        outF.close()
        #at this point, we have the file for run 
        #specify in the command
        command = commandBase+" -r "+str(run)+"-"
        command += " /DAQ/pedestals DAQ_pedestals/tables/run_"+run+".dat"
        print("HERE")
        print command
        subprocess.Popen(command,shell=True)
