@echo off
:loop
uva11992_gen
time<nul
uva11992 < uva11992.in >uva11992.out1
time<nul
uva11992_by_LRJ < uva11992.in >uva11992.out2
time<nul
fc uva11992.out1 uva11992.out2
if errorlevel 1 pause
goto loop