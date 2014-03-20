@echo off
copy .\NTGraph.ocx	%SYSTEMROOT%\system32
Regsvr32 /s %SYSTEMROOT%\system32\NTGraph.ocx
 