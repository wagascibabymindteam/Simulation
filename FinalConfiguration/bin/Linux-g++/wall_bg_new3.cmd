Universe        = vanilla
Executable      = ./wall_bg3.sh
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

Arguments = $(Process)

Queue 20
