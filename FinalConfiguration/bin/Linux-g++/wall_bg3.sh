#!/bin/sh

indir=`printf "/export/scbn07/data2/kikawa/neutfile_nd7"`
outdir=`printf "/home/kikawa/scraid1/MC/bg6/all"`

diskid=`expr ${1} % 4`

tmp=`expr ${1} + 280`

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

srun=0

while [ $srun -le 9 ]
do

run=0

while [ $run -le 5 ]
do

neutfile=`printf "${indir}/11b_nd7_numu_ch_${tmp}_${run}.nt"`
geantfile=`printf "${tmpdir}/ingmc_${tmp}_${run}_${srun}.root"`

./IngMC -o ${geantfile} -i ${neutfile} -m 2 -f 1

mv ${geantfile} ${outdir}

run=`expr $run + 1`
done

srun=`expr $srun + 1`
done
