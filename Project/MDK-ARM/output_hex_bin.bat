@echo off

@REM 可执行文件 (Hex) 文件名
set HEX_NAME=output

@REM 可执行文件 (Hex) 文件路径
set HEX_PATH=.\Flash\Obj

if not exist Output (mkdir Output)

@REM 定制Hex输出路径
set OUTPUT_PATH=.\Output

@REM 软件版本文件路径
::相对路径设置
set VERSION_FILE_PATH=..\..\User\main.c   
::::绝对路径设置
::set VERSION_FILE_PATH=C:\Users\Administrator\Desktop\111\User\main.c

@REM 软件版本字符串的格式
set SOFTWARE_VERSION="#define SOFTWARE_VERSION"

::设置fromelf.exe位置
set exe_location=C:\Keil_v5\ARM\ARMCC\bin\fromelf.exe

@REM 获取系统日期和时间
set YEAR=%DATE:~2,2%
set MONTH=%DATE:~5,2%
set DAY=%DATE:~8,2%
set HOUR=%TIME:~0,2%
set MINUTE=%TIME:~3,2%
set SECOND=%TIME:~6,2%
set CURRENT_DATE=%YEAR%%MONTH%%DAY%_%HOUR%%MINUTE%%SECOND%

@REM 获取软件版本
for /f "tokens=3 delims= " %%i in ('findstr /C:%SOFTWARE_VERSION% %VERSION_FILE_PATH%') do set SW_Ver=%%i
set SW_Ver=%SW_Ver:~1,-1%

@REM 定制Hex文件名
set output_file_name=%HEX_NAME%_V%SW_Ver%_%CURRENT_DATE%

@REM 显示并复制Hex文件
echo Output hex file: %OUTPUT_PATH%\%output_file_name%.hex
copy %HEX_PATH%\%HEX_NAME%.hex %OUTPUT_PATH%\%output_file_name%.hex

@REM 转换并定制Bin文件名
%exe_location% --bin --output %OUTPUT_PATH%\%output_file_name%.bin %HEX_PATH%\%HEX_NAME%.axf

::@REM 转换并定制elf文件名
::%exe_location% --elf --output %OUTPUT_PATH%\%output_file_name%.elf %HEX_PATH%\%HEX_NAME%.axf

exit