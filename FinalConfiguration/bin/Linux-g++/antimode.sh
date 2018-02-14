#!/bin/sh

#if [ ${1} -ge 500 ]
#then

#./IngMC -o /export/scraid1/data/kikawa/mc_t2kreweight_antimode/ingmc_nd3_${1}.root -i /export/scbn07/data2/kikawa/neutfile_antimode/11bfluka_nd3_numu_fe_${1}.nt -m 3 -f 1
./IngMC -o /export/scraid1/data/kikawa/mc_t2kreweight_antimode/ingmc_nd4_${1}.root -i /export/scbn07/data2/kikawa/neutfile_antimode/11bfluka_nd4_numu_fe_${1}.nt -m 4 -f 1

#./IngMC -o /export/scraid1/data/kikawa/mc_t2kreweight_antimode/ingmc_nd3_${1}_bar.root -i /export/scbn07/data2/kikawa/neutfile_antimode/11bfluka_nd3_numubar_fe_${1}.nt -m 3 -f 2
./IngMC -o /export/scraid1/data/kikawa/mc_t2kreweight_antimode/ingmc_nd4_${1}_bar.root -i /export/scbn07/data2/kikawa/neutfile_antimode/11bfluka_nd4_numubar_fe_${1}.nt -m 4 -f 2

#fi
