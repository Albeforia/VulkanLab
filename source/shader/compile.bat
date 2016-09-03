@echo off
setlocal
set validator=D:/Projects/CG/VulkanSDK/1.0.24.0/Bin32/glslangValidator.exe
%validator% -V shader.vert -o compiled/vert.spv
%validator% -V shader.frag -o compiled/frag.spv
set src=%~dp0compiled
set dst=%~dp0..\..\build\Debug\shader
copy %src% %dst%
pause