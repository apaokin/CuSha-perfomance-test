cd cusha
./sfBuild.sh
cd ..
cusha/cusha --input $1  --method CW  --output $2
# cusha/cusha --input $1  --method CW  --output out.txt   && tail -10 out.txt
