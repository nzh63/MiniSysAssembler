# MiniSysAssembler
一个简单的 MiniSy-1 汇编器

## 支持语句

R型：ADD ADDU SUB SUBU AND OR XOR NOR SIT SITU SLL SRL SRA SLLV SRAV JR

I型：ADDI ADDIU ANDI ORI XORI LUI LW SW BEQ BNE SLTI SLTIU

J型：J JAL

### 自带宏语句

MOV

> MOV Register Register/Immediate

## 用法

```powershell
MiniSysAssembler.exe 输入文件路径 [输出文件夹路径]
```
如：
```powershell
# 输出至当前文件夹
MiniSysAssembler.exe C:\mycode.asm
# 输出至D:\
MiniSysAssembler.exe C:\mycode.asm D:\
```
然后程序会生成dmem32.coe和prgmip32.coe。

## Known Issue

1. 目前不支持自定义段起始地址，换言之`.data 0x0`将会报错，请使用`.data`。
2. 目前不支持在数据段内写汇编指令，也不支持在代码段内定义数据。
3. 数据类型仅支持`.word`。

## TODO

1. 更多的宏语句：POP PUSH...
2. 更友好的错误提示。

