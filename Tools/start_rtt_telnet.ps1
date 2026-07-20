# Telnet 连接 localhost:19021 即可

$JLinkDir = "${env:ProgramFiles}\SEGGER\JLink_V818"
$JLink    = Join-Path $JLinkDir "JLink.exe"
$Port     = 19021

# 生成 J-Link 命令脚本
$CmdFile = Join-Path $env:TEMP "jlink_rtt_telnet.jlink"
@"
device STM32H743XI
si SWD
speed 4000
SetRTTTelnetPort $Port
r
exec SetRTTSearchRanges 0x30000000 0x10000
g
"@ | Set-Content -LiteralPath $CmdFile -Encoding ASCII

Write-Host "RTT Telnet 端口: $Port"

& $JLink -ExitOnError 1 -NoGui 1 -CommandFile $CmdFile
