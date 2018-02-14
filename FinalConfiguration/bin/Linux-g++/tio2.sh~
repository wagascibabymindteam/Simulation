#!/bin/sh

outdir=`printf "/home/kikawa/scraid1/MC/bg_floor/all"`

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


neutfile1=`printf "/export/scbn07/data2/kikawa/neutfile_run1/11bfluka_nd3_numu_fe_${1}.nt"`
geantfile1=`printf "${tmpdir}/ingmc_${1}_0.root"`

neutfile2=`printf "/export/scbn07/data2/kikawa/neutfile_run2/11bfluka_nd3_numu_fe_${1}.nt"`
geantfile2=`printf "${tmpdir}/ingmc_${1}_1.root"`

neutfile3=`printf "/export/scbn07/data2/kikawa/neutfile_run1_add/11bfluka_nd3_numu_fe_${1}.nt"`
geantfile3=`printf "${tmpdir}/ingmc_${1}_2.root"`

neutfile4=`printf "/export/scbn07/data2/kikawa/neutfile_run2_add/11bfluka_nd3_numu_fe_${1}.nt"`
geantfile4=`printf "${tmpdir}/ingmc_${1}_3.root"`

./IngMC -o ${geantfile1} -i ${neutfile1} -m 3 -f 1
mv ${geantfile1} ${outdir}

./IngMC -o ${geantfile2} -i ${neutfile2} -m 3 -f 1
mv ${geantfile2} ${outdir}

./IngMC -o ${geantfile3} -i ${neutfile3} -m 3 -f 1
mv ${geantfile3} ${outdir}

./IngMC -o ${geantfile4} -i ${neutfile4} -m 3 -f 1
mv ${geantfile4} ${outdir}
