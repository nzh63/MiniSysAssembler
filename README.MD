# MiniSysAssembler
一个简单的 MiniSy-1(A) 汇编器

## 支持语句

R型：ADD ADDU SUB SUBU MULT MULTU DIV DIVU MFHI MFLO MTHI MTLO MFC0 MTC0 AND OR XOR NOR SIT SITU SLL SRL SRA SLLV SLAV SRAV JR JALR BREAK SYSCALL ERET

I型：ADDI ADDIU ANDI ORI XORI LUI LB LBU LH LHU LW SB SH SW BEQ BNE BGEZ BGTZ BLEZ BLTZ BGEZAL BLTZAL SLTI SLTIU

J型：J JAL

同时亦支持标号的解析。<del>废话，手算偏移量是会死人的。</del>

### 自带宏语句

MOV

> MOV Register, Register/Memory/Immediate<br>
> MOV Memory, Register

<details>
<summary>例子</summary>

> MOV $1, $2<br>
> MOV $1, 65535<br>
> MOV $1, 0xFFFFFFFF<br>
> MOV $1, ARRAY($0)<br>
> MOV ARRAY($0), $1
</details>

PUSH

> PUSH Register

<details>
<summary>例子</summary>

> PUSH $1
</details>

POP

> POP Register

<details>
<summary>例子</summary>

> POP $1
</details>

NOP

> NOP

<details>
<summary>宏语句细节</summary>

|                          宏语句                          |                                展开为                                 |
| :------------------------------------------------------: | :-------------------------------------------------------------------: |
|                 MOV Register1, Register2                 |                      OR Register1, $0, Register2                      |
| MOV Register, Memory<br>(MOV Register, Offset(Register)) |                     LW Register, Offset(Register)                     |
| MOV Memory, Register<br>(MOV Offset(Register), Register) |                     SW Register, Offset(Register)                     |
|     MOV Register, Immediate<br>(Immediate < 0x10000)     |                      ORI Register, $0, Immediate                      |
|    MOV Register, Immediate<br>(Immediate >= 0x10000)     | LUI Register, Immediate >> 16<br>ORI Register, $0, Immediate & 0xffff |
|                      PUSH Register                       |              ADDI \$SP, \$SP, -4<br>SW Register, 0(\$SP)              |
|                       POP Register                       |              ADDI \$SP, \$SP, 4<br>LW Register, 0(\$SP)               |
|                           NOP                            |                            SLL \$0, \$0, 0                            |
</details>



## 用法

```powershell
MiniSysAssembler.exe [选项] 输入文件路径 [输出文件夹路径]
```
如：
```powershell
# 输出至当前文件夹
MiniSysAssembler.exe C:\mycode.asm
# 输出至D:\
MiniSysAssembler.exe C:\mycode.asm D:\
# 输出至D:\同时生成用于调试的细节信息
MiniSysAssembler.exe --show-details C:\mycode.asm D:\
```
然后程序会生成dmem32.coe和prgmip32.coe。

## Known Issue

1. 目前不支持在数据段内写汇编指令，也不支持在代码段内定义数据。
2. 数据类型仅支持`.byte`、`.half`、`.word`。

## TODO

1. 更多的宏语句.
