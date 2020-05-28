copy trainer.ev tmp
awk -f trainer.awk ../../../include/battle/trno_def.h > trainer.ev
awk -f scr_copy.awk tmp >> trainer.ev
awk -f ev_def.awk trainer.ev
del tmp
