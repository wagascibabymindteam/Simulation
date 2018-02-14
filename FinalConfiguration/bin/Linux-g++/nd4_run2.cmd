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

Arguments = -o /export/scraid1/data/kikawa/mc_t2kreweight_new/ingmc_nd4_run2_$(Process).root -i /export/scbn07/data2/kikawa/neutfile_run2/11bfluka_nd4_numu_fe_$(Process).nt -m 4 -f 1

Queue 100
