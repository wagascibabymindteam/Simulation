#!/bin/sh

./IngMC -o /export/scraid1/data/kikawa/mc_t2kreweight_pm_fsi/pmmc_${1}_pelm.root.root -i /export/scbn05/data1/kikawa/neutfile_fsi/11bfluka_nd2_numu_ch_${1}_pelm.nt -m 2 -f 1
#./IngMC -o /export/scraid1/data/kikawa/mc_t2kreweight_pm_fsi/pmmc_${1}_pelp.root.root -i /export/scbn05/data1/kikawa/neutfile_fsi/11bfluka_nd2_numu_ch_${1}_pelp.nt -m 2 -f 1
./IngMC -o /export/scraid1/data/kikawa/mc_t2kreweight_pm_fsi/pmmc_${1}_pspm.root.root -i /export/scbn05/data1/kikawa/neutfile_fsi/11bfluka_nd2_numu_ch_${1}_pspm.nt -m 2 -f 1
#./IngMC -o /export/scraid1/data/kikawa/mc_t2kreweight_pm_fsi/pmmc_${1}_pspp.root.root -i /export/scbn05/data1/kikawa/neutfile_fsi/11bfluka_nd2_numu_ch_${1}_pspp.nt -m 2 -f 1
./IngMC -o /export/scraid1/data/kikawa/mc_t2kreweight_pm_fsi/pmmc_${1}_pdpm.root.root -i /export/scbn05/data1/kikawa/neutfile_fsi/11bfluka_nd2_numu_ch_${1}_pdpm.nt -m 2 -f 1
#./IngMC -o /export/scraid1/data/kikawa/mc_t2kreweight_pm_fsi/pmmc_${1}_pdpp.root.root -i /export/scbn05/data1/kikawa/neutfile_fsi/11bfluka_nd2_numu_ch_${1}_pdpp.nt -m 2 -f 1
