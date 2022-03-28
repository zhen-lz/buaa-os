# Lab1实验报告

## 一、思考题

### Thinking 1.1 请查阅并给出前述 `objdump` 中使用的参数的含义。使用其它体系结 构的编译器（如课程平台的 MIPS 交叉编译器）重复上述各步编译过程，观察并在 实验报告中提交相应的结果。

对于`objdump -DS`指令而言，-D参数表示反汇编**所有部分**的内容*（disassemble the contents of all sections）*，-S参数表示显示与反汇编汇合的**源代码** *（Display source code intermixed with disassembly, if possible.）*

分别执行：

```
/OSLAB/compiler/usr/bin/mips_4KC-gcc -c hello.c
/OSLAB/compiler/usr/bin/mips_4KC-ld hello.o -o hello
/OSLAB/compiler/usr/bin/mips_4KC-objdump -DS hello.o > o.txt
/OSLAB/compiler/usr/bin/mips_4KC-objdump -DS hello > out.txt
```

反汇编.o文件

```
hello.o:     file format elf32-tradbigmips

Disassembly of section .text:

00000000 <main>:
   0:   3c1c0000        lui     gp,0x0
   4:   279c0000        addiu   gp,gp,0
   8:   0399e021        addu    gp,gp,t9
   c:   27bdffe0        addiu   sp,sp,-32
  10:   afbf001c        sw      ra,28(sp)
  14:   afbe0018        sw      s8,24(sp)
  18:   03a0f021        move    s8,sp
  1c:   afbc0010        sw      gp,16(sp)
  20:   8f820000        lw      v0,0(gp)
  24:   24440000        addiu   a0,v0,0
  28:   8f990000        lw      t9,0(gp)
  2c:   0320f809        jalr    t9
  30:   00000000        nop
  34:   8fdc0010        lw      gp,16(s8)
  38:   00001021        move    v0,zero
  3c:   03c0e821        move    sp,s8
  40:   8fbf001c        lw      ra,28(sp)
  44:   8fbe0018        lw      s8,24(sp)
  48:   27bd0020        addiu   sp,sp,32
  4c:   03e00008        jr      ra
  50:   00000000        nop
        ...
Disassembly of section .reginfo:

00000000 <.reginfo>:
   0:   f2000014        0xf2000014
        ...
Disassembly of section .pdr:

00000000 <.pdr>:
   0:   00000000        nop
   4:   c0000000        ll      zero,0(zero)
   8:   fffffffc        sdc3    $31,-4(ra)
        ...
  14:   00000020        add     zero,zero,zero
  18:   0000001e        0x1e
  1c:   0000001f        0x1f
Disassembly of section .rodata:

00000000 <.rodata>:
   0:   48656c6c        0x48656c6c
   4:   6f20576f        0x6f20576f
   8:   726c6421        0x726c6421
   c:   0a000000        j       8000000 <main+0x8000000>
Disassembly of section .comment:

00000000 <.comment>:
   0:   00474343        0x474343
   4:   3a202847        xori    zero,s1,0x2847
   8:   4e552920        c3      0x552920
   c:   342e302e        ori     t6,at,0x302e
  10:   30202844        andi    zero,at,0x2844
  14:   454e5820        0x454e5820
  18:   454c444b        0x454c444b
  1c:   20342e31        addi    s4,at,11825
  20:   20342e30        addi    s4,at,11824
  24:   2e302900        sltiu   s0,s1,10496
```

反汇编.out文件

```
hello:     file format elf32-tradbigmips

Disassembly of section .reginfo:

00400094 <.reginfo>:
  400094:       e0000004        sc      zero,4(zero)
        ...
  4000a8:       10007ff0        b       42006c <main+0x1ffbc>
Disassembly of section .text:

004000b0 <main>:
  4000b0:       27bdffe8        addiu   sp,sp,-24
  4000b4:       afbe0010        sw      s8,16(sp)
  4000b8:       03a0f021        move    s8,sp
  4000bc:       24020001        li      v0,1
  4000c0:       afc20008        sw      v0,8(s8)
  4000c4:       00001021        move    v0,zero
  4000c8:       03c0e821        move    sp,s8
  4000cc:       8fbe0010        lw      s8,16(sp)
  4000d0:       27bd0018        addiu   sp,sp,24
  4000d4:       03e00008        jr      ra
  4000d8:       00000000        nop
  4000dc:       00000000        nop
Disassembly of section .comment:

00000000 <.comment>:
   0:   00474343        0x474343
   4:   3a202847        xori    zero,s1,0x2847
   8:   4e552920        c3      0x552920
   c:   342e302e        ori     t6,at,0x302e
  10:   30202844        andi    zero,at,0x2844
  14:   454e5820        0x454e5820
  18:   454c444b        0x454c444b
  1c:   20342e31        addi    s4,at,11825
  20:   20342e30        addi    s4,at,11824
  24:   2e302900        sltiu   s0,s1,10496
Disassembly of section .pdr:

00000000 <.pdr>:
   0:   004000b0        tge     v0,zero,0x2
   4:   40000000        mfc0    zero,c0_index
   8:   fffffff8        sdc3    $31,-8(ra)
        ...
  14:   00000018        mult    zero,zero
  18:   0000001e        0x1e
  1c:   0000001f        0x1f
```

### Thinking 1.2 也许你会发现我们的 `readelf` 程序是不能解析之前生成的内核文件 (内 核文件是可执行文件) 的，而我们刚才介绍的工具 `readelf` 则可以解析，这是为什么 呢？(提示：尝试使用 readelf -h，观察不同)

`readelf -h testELF`

```vhdl
 ELF Header:
   Magic:   7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00 
   Class:                             ELF32
   Data:                              2's complement, little endian
   Version:                           1 (current)
   OS/ABI:                            UNIX - System V
   ABI Version:                       0
   Type:                              EXEC (Executable file)
   Machine:                           Intel 80386
   Version:                           0x1
   Entry point address:               0x8048490
   Start of program headers:          52 (bytes into file)
   Start of section headers:          4440 (bytes into file)
   Flags:                             0x0
   Size of this header:               52 (bytes)
   Size of program headers:           32 (bytes)
   Number of program headers:         9
   Size of section headers:           40 (bytes)
   Number of section headers:         30
   Section header string table index: 27
```

`readelf -h vmlinux`

```vhdl
 ELF Header:
   Magic:   7f 45 4c 46 01 02 01 00 00 00 00 00 00 00 00 00 
   Class:                             ELF32
   Data:                              2's complement, big endian
   Version:                           1 (current)
   OS/ABI:                            UNIX - System V
   ABI Version:                       0
   Type:                              EXEC (Executable file)
   Machine:                           MIPS R3000
   Version:                           0x1
   Entry point address:               0x80010000
   Start of program headers:          52 (bytes into file)
   Start of section headers:          37164 (bytes into file)
   Flags:                             0x1001, noreorder, o32, mips1
   Size of this header:               52 (bytes)
   Size of program headers:           32 (bytes)
   Number of program headers:         2
   Size of section headers:           40 (bytes)
   Number of section headers:         14
   Section header string table index: 11
```

在data段可以看出，我们生成的`readelf`文件适用于解析小端存储的，而我们的内核`vmlinux`是大端存储的文件，因此无法解析内核。

### Thinking 1.3 在理论课上我们了解到，MIPS 体系结构上电时，启动入口地址为 0xBFC00000（其实启动入口地址是根据具体型号而定的，由硬件逻辑确定，也有可 能不是这个地址，但一定是一个确定的地址），但实验操作系统的内核入口并没有 放在上电启动地址，而是按照内存布局图放置。思考为什么这样放置内核还能保证 内核入口被正确跳转到？

实验操作系统使用`GXemul`仿真器，支持直接加载ELF格式的内核。`BootLoader`中Stage1的功能已经由其提供，此时已经跳到了内核入口，接着就是实现在`boot/start.o`中的代码，设置堆栈，跳转到main函数入口。

### Thinking 1.4 sg_size 和 bin_size 的区别它的开始加载位置并非页对齐，同时 bin_size 的结束位置（va+i）也并非页对齐，最终整个段加载完毕的 sg_size 末尾的位置也 并非页对齐，请思考，为了保证页面不冲突（不重复为同一地址申请多个页，以及 页上数据尽可能减少冲突），这样一个程序段应该怎样加载内存空间中。 彻底并透彻地理解上图能帮助大家在后续实验中节约很多时间。

在加载程序时，避免发生共享页面和冲突页面现象。首先，不同程序段的占用空间不能够有重合，然后，尽量避免一个页面同时被多个程序段所占用。即若前面的程序段末地址所占用的页面地址为v*i*，则后续的程序段首地址应从下一页面v*i+1*开始占用。

### Thinking 1.5 内核入口在什么地方？main 函数在什么地方？我们是怎么让内核进 入到想要的 main 函数的呢？又是怎么进行跨文件调用函数的呢？

内核入口在0x00000000处，main函数在0x80010000处。我们在start.S文件中编写mips汇编代码，设置堆栈后直接跳到main函数中。在跨文件调用函数时，每个函数会有一个固定的地址，调用过程为将需要存储的值进行进栈等保护，再用jal跳转到相应函数的地址。

### Thinking 1.6 查阅《See MIPS Run Linux》一书相关章节，解释 boot/start.S 中下 面几行对 CP0 协处理器寄存器进行读写的意义。具体而言，它们分别读/写了哪些 寄存器的哪些特定位，从而达到什么目的？

```
1 /* Disable interrupts */
2 mtc0 zero, CP0_STATUS
3
4 ......
5
6 /* disable kernel mode cache */
7 mfc0 t0, CP0_CONFIG
8 and t0, ~0x7
9 ori t0, 0x2
10 mtc0 t0, CP0_CONFIG 
```

将宏定义的内容转化为寄存器编号后：

```mipsasm
 mtc0 $0,$12 #将SR寄存器清零
 mfc0 $t0,$16
 and $t0,~0x7 #要清零的位的反码
 ori $t0,0x2 #要置1的位
 mtc0 $t0,$16 #将Config寄存器0号位和2号位置0，将1号位置1
```

上电后，需要设置SR寄存器来使CPU进入工作状态，而硬件通常都是复位后让许多寄存器的位为未定义。

Config寄存器的后三位为可写的，用来决定固定的kseg0区是否经过高速缓存和其确切的行为如何。

## 二、实验难点图示

![image-20220328214326524](C:\Users\leera\AppData\Roaming\Typora\typora-user-images\image-20220328214326524.png)

## 三、体会与感想

在本次的实验中，我觉得最困难的一个地方是在于对实验中各种概念和实验代码的一个理解。例如ELF文件的结构，如果没看`kerelf.h`中的结构体的定义，没看ELF文件结构图，那么就很难真正理解ELF文件的结构特点。但是，当我们逐渐熟悉了这些概念并一步步地理解了项目中代码所表示的实际含义，其本质上的难度还是比较低的。

不过，虽然我已经通过了lab1的课下测试，但是，我对于其中的部分代码和结构，感觉还是比较杂，还是存在着一些疑问，希望能通过接下来的实验，能逐渐理解并回答这些疑问。