#!/bin/sh

indir=`printf "/home/kikawa/scraid1/neutfile_nd7"`
outdir=`printf "/home/kikawa/scraid1/MC/bg6/all"`

diskid=`expr ${1} % 4`

case $diskid in
    0)
	tmpdir=`printf "/export/scbn03/data1/kikawa/tmp"`
	;;
    1)
	tmpdir=`printf "/export/scbn04/data1/kikawa/tmp"`
	;;
    2)
	tmpdir=`printf "/export/scbn05/data1/kikawa/tmp"`
	;;
    3)
	tmpdir=`printf "/export/scbn06/data1/kikawa/tmp"`
	;;
esac

run=0

while [ $run -le 9 ]
do

neutfile=`printf "${indir}/10c_nd7_numu_ch_${1}.nt"`
geantfile=`printf "${tmpdir}/ingmc_${1}_${run}.root"`

./IngMC -o ${geantfile} -i ${neutfile} -m 2 -f 1

mv ${geantfile} ${outdir}

run=`expr $run + 1`
done
