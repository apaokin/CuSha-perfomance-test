for s in 10 11
do
  for type in RMAT UR SSCA2
  do
    ./generator -s $s -e 32 -directed -unweighted -file graph_${s}_${type}.bin -type $type
  done
done
