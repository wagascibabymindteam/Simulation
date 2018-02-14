#!/bin/sh

outdir=`printf "/home/kikawa/scraid1/mc_t2kreweight_pm_new_tio2"`

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

neutfile1=`printf "/export/scbn07/data2/kikawa/neutfile_run2_tio2/11bfluka_nd2_numu_o_${1}.nt"`
geantfile1=`printf "${tmpdir}/pmmc_o_${1}.root"`

neutfile2=`printf "/export/scbn07/data2/kikawa/neutfile_run2_tio2/11bfluka_nd2_numu_ti_${1}.nt"`
geantfile2=`printf "${tmpdir}/pmmc_ti_${1}.root"`

./IngMC -o ${geantfile1} -i ${neutfile1} -m 2 -f 1
mv ${geantfile1} ${outdir}

./IngMC -o ${geantfile2} -i ${neutfile2} -m 2 -f 1
mv ${geantfile2} ${outdir}
