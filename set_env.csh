#!/bin/tcsh -f

#print only if there is a prompt
alias echo 'if($?prompt) echo \!*  '

echo


if(! $?POKERRECO_ROOT) then
    echo "POKERRECO_ROOT was not set properly"
    exit
endif

echo "POKERRECO_ROOT set to $POKERRECO_ROOT"

#set MYSQLHOST=clasdb.jlab.org
#set MYSQLUSER=bdxreader
#set MYSQLDB=BDX

set MYSQLHOST=jdaq8
set MYSQLUSER=ccdb_user
set MYSQLDB=ccdb

setenv JANA_CALIB_URL mysql://$MYSQLUSER@$MYSQLHOST/$MYSQLDB
setenv JANA_PLUGIN_PATH $POKERRECO_ROOT/lib:$POKERRECO_ROOT/lib/plugins:$POKERRECO_ROOT/lib/users

#a.c. this is a work-around for MAC, where -rpath doens't work!!
#also do this on linux for genoa farm
if (! $?DYLD_LIBRARY_PATH) then       
    setenv DYLD_LIBRARY_PATH ""
endif
if (! $?LD_LIBRARY_PATH) then       
    setenv LD_LIBRARY_PATH ""
endif

setenv DYLD_LIBRARY_PATH ${POKERRECO_ROOT}/lib:${DYLD_LIBRARY_PATH}
setenv LD_LIBRARY_PATH ${POKERRECO_ROOT}/lib:${LD_LIBRARY_PATH}

#This is for cmsg
setenv CMSGROOT ${POKERRECO_ROOT}/src/external/cMsg-3.6/java



echo

unalias echo
