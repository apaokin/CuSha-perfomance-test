for s in 10 11 12 13 14 15 17 18 19 20 21 22 23
do
  for type in RMAT UR SSCA2
  do
    mpisubmit.pl -t 8 -w 00:30 --stdout gen_info_${s}_${type}.txt  generator -- -s $s -e 32 -directed -unweighted -file graph_${s}_${type}.bin -type $type
  done
done
