for s in 10 11
do
  for type in RMAT UR SSCA2
  do
    # cusha/cusha --input  graph_${s}_${type}.bin  --method CW  --output cusha_${s}_${type}.bin
    ./seq --input graph_${s}_${type}.bin  --cusha cusha_${s}_${type}.bin

    # ./generator -s $s -e 32 -directed -unweighted -file graph_${s}_${type}.bin -type $type
  done
done
