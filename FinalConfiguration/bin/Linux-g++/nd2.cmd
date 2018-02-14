Universe        = vanilla
Executable      = ./IngMC
Rank            = kflops

Requirements    = (CpuIsBusy == FALSE && \
                  ( Machine == "scbn02.hepnet.scphys.kyoto-u.ac.jp" || \
                   Machine == "scbn03.hepnet.scphys.kyoto-u.ac.jp" || \
                   Machine == "scbn04.hepnet.scphys.kyoto-u.ac.jp" || \
                   Machine == "scbn05.hepnet.scphys.kyoto-u.ac.jp" || \
                   Machine == "scbn06.hepnet.scphys.kyoto-u.ac.jp" || \
                   Machine == "scbn07.hepnet.scphys.kyoto-u.ac.jp" || \
                   Machine == "scbn21.hepnet.scphys.kyoto-u.ac.jp" || \
                   Machine == "scbn22.hepnet.scphys.kyoto-u.ac.jp" || \
                   Machine == "scbn23.hepnet.scphys.kyoto-u.ac.jp" || \
                   Machine == "scbn24.hepnet.scphys.kyoto-u.ac.jp" || \
                   Machine == "scbn25.hepnet.scphys.kyoto-u.ac.jp" || \
                   Machine == "scbn26.hepnet.scphys.kyoto-u.ac.jp" || \
                   Machine == "scbn27.hepnet.scphys.kyoto-u.ac.jp" || \
                   Machine == "scbn28.hepnet.scphys.kyoto-u.ac.jp" || \
                   Machine == "scbn29.hepnet.scphys.kyoto-u.ac.jp" ))

Getenv          = True
Output           = /dev/null
#Output           = ./log$(Process).txt
Error           = /dev/null
#Error           = ./err$(Process).txt
Notification  = Never

#Arguments = -o /export/scbn07/data2/taichiro/mc_water_muid15/B2mc_h2o_$(Process).root -i /export/scbn07/data2/kikawa/neutfile_nd5/11bfluka_nd5_numu_h2o_$(Process).nt -m 5 -f 1

#B2flax
#Arguments = -o /export/scbn07/data2/taichiro/mc_water_muid42/B2mc_h2o_$(Process).root -i /export/scraid2/data/minamino/neut/11b_b2water/11b_b2water_h2o/11b_nd7_numu_h2o_$(Process).nt -m 5 -f 1
Arguments = -o /export/scraid2/data/scbn07_backup2/taichiro/mc_water_muid103/B2mc_h2o_$(Process).root -i /export/scraid2/data/scbn07_backup2/taichiro/neut/data13/ch/11b_nd7_numu_ch_$(Process).nt -m 5 -f 1


#BG1
#Arguments = -o /export/scbn07/data2/taichiro/mc_water_muid30/B2mc_h2o_$(Process).root -i /export/scraid2/data/minamino/neut/11b_b2water/11b_b2water_o/11b_nd8_numu_o_$(Process).nt -m 5 -f 1
#Arguments = -o /export/scraid2/data/scbn07_backup2/taichiro/mc_water_muid92/B2mc_o_1_$(Process).root -i /export/scraid2/data/scbn07_backup2/taichiro/neut/data14/fdid8_1/11b_nd8_numu_o_$(Process).nt -m 5 -f 1
#Arguments = -o /export/scraid2/data/scbn07_backup2/taichiro/mc_water_muid92/B2mc_o_2_$(Process).root -i /export/scraid2/data/scbn07_backup2/taichiro/neut/data14/fdid8_2/11b_nd8_numu_o_$(Process).nt -m 5 -f 1
#Arguments = -o /export/scraid2/data/scbn07_backup2/taichiro/mc_water_muid92/B2mc_o_3_$(Process).root -i /export/scraid2/data/scbn07_backup2/taichiro/neut/data14/fdid8_3/11b_nd8_numu_o_$(Process).nt -m 5 -f 1

#BG2
#Arguments = -o /export/scbn07/data2/taichiro/mc_water_muid31/B2mc_h2o_$(Process).root -i /export/scraid2/data/minamino/neut/11b_b2water/11b_b2water_o/11b_nd9_numu_o_$(Process).nt -m 5 -f 1
#Arguments = -o /export/scraid2/data/scbn07_backup2/taichiro/mc_water_muid96/B2mc_o_1_$(Process).root -i /export/scraid2/data/scbn07_backup2/taichiro/neut/data14/fdid9_1/11b_nd9_numu_o_$(Process).nt -m 5 -f 1
#Arguments = -o /export/scraid2/data/scbn07_backup2/taichiro/mc_water_muid96/B2mc_o_2_$(Process).root -i /export/scraid2/data/scbn07_backup2/taichiro/neut/data14/fdid9_2/11b_nd9_numu_o_$(Process).nt -m 5 -f 1
#Arguments = -o /export/scraid2/data/scbn07_backup2/taichiro/mc_water_muid96/B2mc_o_3_$(Process).root -i /export/scraid2/data/scbn07_backup2/taichiro/neut/data14/fdid9_3/11b_nd9_numu_o_$(Process).nt -m 5 -f 1

#side Fe BG
#Arguments = -o /export/scraid2/data/scbn07_backup2/taichiro/mc_water_muid53/B2mc_h2o_$(Process).root -i /export/scraid2/data/minamino/neut/11b_b2water/11b_b2water_fe/11b_nd7_numu_fe_$(Process).nt -m 6 -f 1
#Arguments = -o /export/scraid2/data/scbn07_backup2/taichiro/mc_water_muid93/B2mc_fe_1_$(Process).root -i /export/scraid2/data/scbn07_backup2/taichiro/neut/data16/11b_nd7_numu_fe_$(Process).nt -m 6 -f 1
#Arguments = -o /export/scraid2/data/scbn07_backup2/taichiro/mc_water_muid94/B2mc_fe_1_$(Process).root -i /export/scraid2/data/scbn07_backup2/taichiro/neut/data16/11b_nd7_numu_fe_$(Process).nt -m 8 -f 1

#downstream Fe BG
#Arguments = -o /export/scraid2/data/scbn07_backup2/taichiro/mc_water_muid54/B2mc_h2o_$(Process).root -i /export/scraid2/data/minamino/neut/11b_b2water/11b_b2water_fe/11b_nd7_numu_fe_$(Process).nt -m 7 -f 1
#Arguments = -o /export/scraid2/data/scbn07_backup2/taichiro/mc_water_muid95/B2mc_fe_1_$(Process).root -i /export/scraid2/data/scbn07_backup2/taichiro/neut/data16/11b_nd7_numu_fe_$(Process).nt -m 7 -f 1



Queue 1000
