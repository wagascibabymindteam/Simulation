#!/bin/sh

indir1=`printf "/export/scbn07/data2/kikawa/neutfile_run1_add"`
indir2=`printf "/export/scbn07/data2/kikawa/neutfile_run2_add"`
outdir=`printf "/export/scraid1/data/kikawa/mc_t2kreweight_new_add"`

diskid=`expr ${1} % 4`
tmp=`expr ${1} + 500`

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

neutfile31=`printf "${indir1}/11bfluka_nd3_numu_fe_${tmp}.nt"`
geantfile31=`printf "${tmpdir}/ingmc_nd3_run1_${tmp}.root"`

neutfile41=`printf "${indir1}/11bfluka_nd4_numu_fe_${tmp}.nt"`
geantfile41=`printf "${tmpdir}/ingmc_nd4_run1_${tmp}.root"`

neutfile32=`printf "${indir2}/11bfluka_nd3_numu_fe_${tmp}.nt"`
geantfile32=`printf "${tmpdir}/ingmc_nd3_run2_${tmp}.root"`

neutfile41=`printf "${indir2}/11bfluka_nd4_numu_fe_${tmp}.nt"`
geantfile41=`printf "${tmpdir}/ingmc_nd4_run2_${tmp}.root"`

./IngMC -o ${geantfile31} -i ${neutfile31} -m 3 -f 1
./IngMC -o ${geantfile41} -i ${neutfile41} -m 4 -f 1
./IngMC -o ${geantfile32} -i ${neutfile32} -m 3 -f 1
./IngMC -o ${geantfile42} -i ${neutfile42} -m 4 -f 1

mv ${geantfile31} ${outdir}
mv ${geantfile32} ${outdir}
mv ${geantfile41} ${outdir}
mv ${geantfile42} ${outdir}
