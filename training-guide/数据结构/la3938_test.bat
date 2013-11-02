@echo off
:loop
la3938_gen
time<nul
la3938 < la3938.in >la3938.out1
time<nul
la3938_by_LRJ < la3938.in >la3938.out2
time<nul
fc la3938.out1 la3938.out2
if errorlevel 1 pause
goto loop