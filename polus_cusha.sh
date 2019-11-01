for s in 10 11 12 13 14 15 16 17 18
do
  for type in RMAT UR SSCA2
  do
    mpisubmit.pl --gpu -w 00:30 --stdout block1024_cusha_${s}_${type}.txt cusha/cusha --  --bsize 1024 --input  graph_${s}_${type}.bin  --method CW  --output cusha_${s}_${type}.bin
    mpisubmit.pl --gpu -w 00:30 --stdout block256_cusha_${s}_${type}.txt cusha/cusha -- --bsize 256 --input graph_${s}_${type}.bin  --method CW  --output wwwcusha_${s}_${type}.bin
 
# ./generator -s $s -e 32 -directed -unweighted -file graph_${s}_${type}.bin -type $type
  done
done
