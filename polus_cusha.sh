for s in 10 11
do
  for type in RMAT UR SSCA2
  do
    mpisubmit.pl --gpu --stdout result_cusha_${s}_${type}.txt cusha/cusha -- --input  graph_${s}_${type}.bin  --method CW  --output cusha_${s}_${type}.bin
    # ./generator -s $s -e 32 -directed -unweighted -file graph_${s}_${type}.bin -type $type
  done
done
