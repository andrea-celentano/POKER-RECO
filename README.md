# POKERReco
reconstruction for POKER experiment

#to launch recon on data:

$POKERRECO_ROOT/bin/pokerReco --config=$POKERRECO_ROOT/bdx.config.CataniaDOWN -PSYSTEM:OUTPUT="root,out.root" --plugin=andrea_Catania /project/Gruppo3/fiber5/celentano/CataniaData/Catania_001158.evio.0* -PTT:XML_FILENAME="tt.xml" --nthreads=10
