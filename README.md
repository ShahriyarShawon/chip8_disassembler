# Chip 8 Disassembler


This is an attempt at a chip 8 disassembler, it is not ready to be used and has bugs.

Build:
```sh 
make dasm 
```


Test Output

```sh 
$ ./dasm test.ch8 | head 

  ABS  |   Rel  |  OPC   | ASM
0x0000 | 0x0200 | 0xA321 | LD I,0x0321
0x0002 | 0x0202 | 0x6000 | LD V[0x00],0x00
0x0004 | 0x0204 | 0x6100 | LD V[0x01],0x00
0x0006 | 0x0206 | 0x6208 | LD V[0x02],0x08
0x0008 | 0x0208 | 0xD015 | DRW V[0x00],V[0x01],0x05
0x000A | 0x020A | 0xF21E | ADD I,V[0x02]
0x000C | 0x020C | 0x8024 | ADD V[0x00],V[0x02]
0x000E | 0x020E | 0xD015 | DRW V[0x00],V[0x01],0x05
0x0010 | 0x0210 | 0xF21E | ADD I,V[0x02]
```

