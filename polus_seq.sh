for s in 20
do
  for type in RMAT UR SSCA2
  do
    # cusha/cusha --input  graph_${s}_${type}.bin  --method CW  --output cusha_${s}_${type}.bin
    mpisubmit.pl --stdout result_seq_${s}_${type}.txt  ./seq -- --input graph_${s}_${type}.bin  --cusha cusha_${s}_${type}.bin

    # ./generator -s $s -e 32 -directed -unweighted -file graph_${s}_${type}.bin -type $type
  done
done
