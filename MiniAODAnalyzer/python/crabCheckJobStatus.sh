#!/bin/bash

cd crab_projects_2017_Nov14/ 
echo " "
echo $(pwd)

for i in */; 
do 
    echo " "
    echo " "
    echo " "
    echo "%%%%%%%%%%%%%%%%%%%"
    echo " "
    echo " "
    echo " "
    echo "### $i"; 
    #cd "$i/results"
    #echo "------" $(pwd)

#    if [[ $i == *"crab_DYJetsToLL_M-50_HT"* ]]; then
    crab status $i
        #continue
    #fi

#    if [[ $i == *"crab_ZToMuMu_NNPDF30_13TeV-powheg_M"* ]]; then
#	crab getoutput $i
        #continue
#    fi

    #cd ../..
done;

