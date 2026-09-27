# CSAPP : Program Encodings

> Ngày viết : 26/9/2026

> Ngày hoàn thành :

**Mục lục**

- [1. Program Encodings](#1-program-encodings)
  - [1.1. Program Encodings là gì?](#11-program-encodings-là-gì)
  - [1.2. Từ mã nguồn C đến Machine Code](#12-từ-mã-nguồn-c-đến-machine-code)
    - [1.2.1. Preprocessing](#121-preprocessing)
    - [1.2.2. Compilation](#122-compilation)
    - [1.2.3. Assembling](#123-assembling)
    - [1.2.4. Linking](#124-linking)
    - [1.2.5. CPU thực thi Machine Code](#125-cpu-thực-thi-machine-code)
  - [1.3. Assembly và Machine Code](#13-assembly-và-machine-code)
    - [1.3.1. Assembly không phải Machine Code](#131-assembly-không-phải-machine-code)
    - [1.3.2. Assembly là dạng biểu diễn gần với Machine Code](#132-assembly-là-dạng-biểu-diễn-gần-với-machine-code)
    - [1.3.3. Một Assembly instruction có thể có độ dài khác nhau](#133-một-assembly-instruction-có-thể-có-độ-dài-khác-nhau)
    - [1.3.4. Disassembler: đi từ Machine Code về Assembly](#134-disassembler-đi-từ-machine-codevề-assembly)
	- [1.3.5. Phân biệt giữa byte opcode và các byte rác](#135-phân-biệt-giữa-byte-opcode-và-các-byte-rác)
    - [1.3.6. Vì sao Reverse Engineering cần hiểu cả hai?](#136-vì-sao-reverse-engineering-cần-hiểu-cả-hai)
    - [1.3.7. Phân biệt giữa instruction, vaddr instrution, offset và assembly representation của instruction trong gdb](#137-phân-biệt-giữa-instruction-vaddr-instruction-offset-và-assembly-representation-của-instruction-trong-gdb)
  - [1.4. Instruction Encoding](#14-instruction-encoding)
  - [1.5. Cấu trúc tổng quát của một Instruction](#15-cấu-trúc-tổng-quát-của-một-instruction)

- [2. x86-64 Instruction Encoding](#2-x86-64-instruction-encoding)
  - [2.1. Opcode](#21-opcode)
  - [2.2. Operand](#22-operand)
  - [2.3. Register Encoding](#23-register-encoding)
  - [2.4. Immediate Value](#24-immediate-value)
  - [2.5. Displacement](#25-displacement)
  - [2.6. Instruction Length](#26-instruction-length)

- [3. REX Prefix](#3-rex-prefix)
  - [3.1. REX Prefix là gì?](#31-rex-prefix-là-gì)
  - [3.2. Cấu trúc byte REX](#32-cấu-trúc-byte-rex)
  - [3.3. W, R, X và B](#33-w-r-x-và-b)
  - [3.4. Ví dụ giải mã REX](#34-ví-dụ-giải-mã-rex)

- [4. ModR/M Byte](#4-modrm-byte)
  - [4.1. ModR/M là gì?](#41-modrm-là-gì)
  - [4.2. Cấu trúc ModR/M](#42-cấu-trúc-modrm)
  - [4.3. Mod Field](#43-mod-field)
  - [4.4. Reg Field](#44-reg-field)
  - [4.5. R/M Field](#45-rm-field)
  - [4.6. Giải mã ModR/M bằng tay](#46-giải-mã-modrm-bằng-tay)

- [5. SIB Byte](#5-sib-byte)
  - [5.1. SIB là gì?](#51-sib-là-gì)
  - [5.2. Cấu trúc SIB](#52-cấu-trúc-sib)
  - [5.3. Scale](#53-scale)
  - [5.4. Index](#54-index)
  - [5.5. Base](#55-base)
  - [5.6. Công thức địa chỉ của SIB](#56-công-thức-địa-chỉ-của-sib)
  - [5.7. Giải mã SIB bằng tay](#57-giải-mã-sib-bằng-tay)

- [6. Ví dụ hoàn chỉnh](#6-ví-dụ-hoàn-chỉnh)
  - [6.1. Register → Register](#61-register--register)
  - [6.2. Register → Memory](#62-register--memory)
  - [6.3. Memory Addressing](#63-memory-addressing)
  - [6.4. Immediate Operand](#64-immediate-operand)
  - [6.5. Instruction có Displacement](#65-instruction-có-displacement)
  - [6.6. Instruction có SIB](#66-instruction-có-sib)
  - [6.7. Tự decode một Instruction hoàn chỉnh](#67-tự-decode-một-instruction-hoàn-chỉnh)

- [7. Từ Machine Code trở lại Assembly](#7-từ-machine-code-trở-lại-assembly)
  - [7.1. Disassembler hoạt động như thế nào?](#71-disassembler-hoạt-động-như-thế-nào)
  - [7.2. objdump](#72-objdump)
  - [7.3. GDB](#73-gdb)
  - [7.4. Ghidra](#74-ghidra)
  - [7.5. Đối chiếu Byte ↔ Assembly](#75-đối-chiếu-byte--assembly)

- [8. Object Code và ELF](#8-object-code-và-elf)
  - [8.1. Object File là gì?](#81-object-file-là-gì)
  - [8.2. Code Section](#82-code-section)
  - [8.3. Relocation](#83-relocation)
  - [8.4. Symbol và Symbol Table](#84-symbol-và-symbol-table)
  - [8.5. Từ Object File đến Executable](#85-từ-object-file-đến-executable)

- [9. Thực hành với Compiler](#9-thực-hành-với-compiler)
  - [9.1. gcc -S](#91-gcc--s)
  - [9.2. gcc -c](#92-gcc--c)
  - [9.3. objdump -d](#93-objdump--d)
  - [9.4. readelf](#94-readelf)
  - [9.5. So sánh Source → Assembly → Machine Code](#95-so-sánh-source--assembly--machine-code)

- [10. Tổng kết](#10-tổng-kết)
  - [10.1. Instruction được encode như thế nào?](#101-instruction-được-encode-như-thế-nào)
  - [10.2. Quy trình Decode một Instruction](#102-quy-trình-decode-một-instruction)
  - [10.3. Những gì cần nhớ](#103-những-gì-cần-nhớ)

---

## 1. Program Encodings
### 1.1. Program Encodings là gì?

Program Encodings có thể hiểu đơn giản là cách một chương trình được biểu diễn dưới dạng machine code, những instruction được CPU giải mã và thực thi.

Ví dụ, ở mức ngôn ngữ C:

```c
#include <stdio.h>

int main(void){
    printf("Hello World\n");
    return 0;
}
```

hoặc ở mức Assembly x86-64:

```asm
section .data
    msg db "hello world", 10

section .text
    global _start

_start:
    mov rax, 1      
    mov rdi, 1      
    mov rsi, msg    
    mov rdx, 11     
    syscall

    mov rax, 60    
    mov rdi, 0 
    syscall
```

CPU không hiểu `stdio.h`, `printf()`, `return`, hay `mov` theo nghĩa mà con người hiểu chúng. CPU thực thi các machine instructions, được biểu diễn bằng các byte trong bộ nhớ.

Ví dụ, một instruction Assembly như:

```asm
mov rdi, 1
```

sẽ được assembler mã hóa thành một chuỗi byte machine code tương ứng. CPU sau đó đọc những byte này, giải mã chúng theo kiến trúc x86-64 và thực hiện thao tác tương ứng.Có thể hình dung quá trình tổng quát:

```text
Source Code
    |
    | Compiler
    v
Assembly
    |
    | Assembler
    v
Machine Code
    |
    v
   CPU
    |
    v
Instruction Decode -> Execute
```

Vì vậy, Program Encoding không đơn giản là dịch C sang binary. Nó tập trung vào cách các instruction của chương trình được mã hóa thành những byte cụ thể mà kiến trúc CPU quy định. **Ví dụ:**

```
Assembly instruction
        |
        v
    mov rdi, 1
        |
        v
 Instruction Encoding
        |
        v
    Machine Code
        |
        v
    CPU Decode
        |
        v
      Execute
```

Đây chính là vấn đề cốt lõi của phần Program Encodings:

> **Tại sao một instruction Assembly cụ thể lại được biểu diễn bởi đúng những byte machine code đó?**

Và theo chiều ngược lại:

> **Nếu nhìn vào một chuỗi machine code, làm thế nào để xác định nó biểu diễn instruction Assembly nào?**

### 1.2. Từ mã nguồn C đến Machine Code

Khi viết một chương trình bằng C, CPU không thể trực tiếp thực thi mã nguồn C. Mã nguồn phải trải qua nhiều bước chuyển đổi trước khi trở thành machine code mà CPU có thể thực thi.

Ví dụ, xét chương trình đơn giản:

```c
#include <stdio.h>

int main(void){
    int a = 10;
    int b = 20;
    return a + b;
}
```

Có thể hình dung quá trình chuyển đổi như sau:

```
|--------------|
|   Source C   |
|    main.c    |
|--------------|
       │
       │ Preprocessor
       v
|--------------|
│ Expanded C   │
|--------------|
       │
       │ Compiler
       v
|--------------|
│   Assembly   │
│    main.s    │
|--------------|
       │
       │ Assembler
       v
|--------------|
│ Object File  │
│    main.o    │
|--------------|
       │
       │ Linker
       v
|--------------|
│  Executable  │
│     main     │
|--------------|
       │
       v
      CPU
```

#### 1.2.1. Preprocessing

Đầu tiên, source code được đưa qua preprocessor.**Ví dụ:**

```c
#include <stdio.h>
```

sẽ được xử lý trước khi compiler thực hiện quá trình biên dịch chính. Các macro, `#include`, `#define`, conditional compilation,... được xử lý ở bước này.

Có thể quan sát kết quả bằng:

```bash
gcc -E main.c -o main.i
```

File `main.i` vẫn là mã nguồn C, nhưng các chỉ thị tiền xử lý đã được xử lý. Cái cách nó xử lý là nó bê nguyên cả mã nguồn header chèn vào luôn

#### 1.2.2. Compilation

Compiler chuyển mã C thành Assembly phù hợp với kiến trúc đích. Ví dụ có thể yêu cầu GCC dừng ở bước Assembly:

```bash
gcc -S main.c -o main.s
```

Kết quả có thể có dạng:

```asm
main:
    pushq   %rbp
    movq    %rsp, %rbp
    movl    $10, -4(%rbp)
    movl    $20, -8(%rbp)
    movl    -4(%rbp), %eax
    addl    -8(%rbp), %eax
    popq    %rbp
    ret
```

Lúc này chương trình vẫn chưa phải machine code. Đây vẫn là Assembly, tức một dạng biểu diễn có thể đọc được bởi con người.

#### 1.2.3. Assembling

Assembler chuyển Assembly thành machine code và đặt nó vào một object file. Với GCC:

```bash
gcc -c main.c -o main.o
```

Hoặc nếu đã có file Assembly:

```bash
as main.s -o main.o
```

Object file `main.o` thường là một ELF relocatable object trên Linux x86-64. Có thể kiểm tra:

```bash
file main.o
```

và xem machine code:

```bash
objdump -d main.o
```

Ví dụ:

```text
48 89 e5
48 83 ec 10
c7 45 fc 0a 00 00 00
```

Đây mới là những byte machine code tương ứng với các instruction.

#### 1.2.4. Linking

Một chương trình thực tế thường không chỉ chứa code của chính file `main.c`. **Ví dụ:**

```c
printf("Hello\n");
```

sử dụng code nằm trong các thư viện khác. Linker có nhiệm vụ kết hợp các object file và thư viện cần thiết thành executable cuối cùng. **Ví dụ:**

```bash
gcc main.o -o main
```

Sau bước này:

```text
main.o
  +
libraries
  +
other object files
  ↓
linker
  ↓
main
```

Executable `main` vẫn chứa machine code, nhưng đồng thời còn có nhiều thành phần khác của ELF như section, symbol, relocation information, dynamic linking information,...

#### 1.2.5. CPU thực thi Machine Code

Khi executable được OS nạp vào bộ nhớ, CPU bắt đầu thực thi các instruction tại entry point thích hợp. Ở mức khái quát:

```text
C source
   ↓
Preprocessor
   ↓
C source đã được mở rộng
   ↓
Compiler
   ↓
Assembly
   ↓
Assembler
   ↓
Machine code
   ↓
Object file
   ↓
Linker
   ↓
Executable ELF
   ↓
OS loader
   ↓
Virtual Memory
   ↓
CPU
   ↓
Fetch → Decode → Execute
```

- **Điểm quan trọng :** là machine code không phải toàn bộ executable. Một ELF executable chứa machine code cùng với metadata và các cấu trúc cần thiết để hệ điều hành có thể load và chạy chương trình.

Vì vậy, khi reverse engineering một binary, ta thường đi theo hướng ngược lại:

```text
Executable ELF
      ↓
Machine Code
      ↓
Disassembler
      ↓
Assembly
      ↓
Control Flow / Data Flow
      ↓
Hiểu chương trình
```

### 1.3. Assembly và Machine Code

Ở phần trước, ta đã thấy quá trình:

```text
C → Assembly → Machine Code
```

Trong đó, Assembly và Machine Code có quan hệ rất gần nhau nhưng không phải là cùng một thứ. Assembly là dạng biểu diễn bằng các mnemonic và operand để con người có thể đọc và viết instruction của CPU. Machine Code là dạng mã hóa nhị phân/byte của những instruction đó theo quy tắc của kiến trúc CPU. **Ví dụ**, với x86-64:

```asm
mov rdi, 1
```

Đây là Assembly instruction. Sau khi được assembler mã hóa, nó trở thành một chuỗi byte machine code tương ứng:

```text
BF 01 00 00 00
```

CPU không đọc chuỗi:

```text
mov rdi, 1
```

mà đọc các byte:

```text
BF 01 00 00 00
```

sau đó giải mã chúng thành instruction mà CPU có thể thực thi. Có thể hình dung:

```text
┌─────────────────────┐
│ Assembly            │
│ mov rdi, 1          │
└──────────┬──────────┘
           │
           │ Assembler
           v
┌─────────────────────┐
│ Machine Code        │
│ BF 01 00 00 00      │
└──────────┬──────────┘
           │
           │ CPU Decode
           v
┌─────────────────────┐
│ Instruction         │
│ MOV rDI, 1          │
└──────────┬──────────┘
           │
           v
        Execute
```

#### 1.3.1. Assembly không phải Machine Code

Một lỗi dễ mắc phải là coi:

```asm
mov rdi, 1
```

và:

```text
BF 01 00 00 00
```

là cùng một thứ. Chúng biểu diễn cùng một instruction, nhưng ở hai dạng khác nhau. Assembly:

```asm
mov rdi, 1
```

là textual representation. Machine code:

```text
BF 01 00 00 00
```

là encoded representation. Assembly tồn tại để con người có thể làm việc với instruction dễ dàng hơn. Machine code là dạng mà CPU thực sự fetch từ memory và decode.

#### 1.3.2. Assembly là dạng biểu diễn gần với Machine Code

Assembly không phải là một ngôn ngữ hoàn toàn độc lập với CPU. Nó phụ thuộc rất mạnh vào instruction set architecture (ISA). **Ví dụ**, instruction:

```asm
mov rdi, 1
```

là instruction của x86-64. Một kiến trúc khác như ARM64 có instruction set và encoding hoàn toàn khác. Điều này có nghĩa:

```text
C
│
├──→ x86-64 Assembly
│        ↓
│    x86-64 Machine Code
│
└──→ ARM64 Assembly
         ↓
     ARM64 Machine Code
```

Cùng một chương trình C có thể được compiler dịch thành các instruction khác nhau tùy thuộc vào kiến trúc CPU mục tiêu.

#### 1.3.3. Một Assembly instruction có thể có độ dài khác nhau

Đây là một đặc điểm quan trọng của x86-64. Machine code của x86-64 sử dụng instruction có độ dài biến đổi. **Ví dụ**, các instruction khác nhau có thể chiếm số byte khác nhau:

```text
Instruction              Machine Code

ret                      C3

nop                      90

mov edi, 1               BF 01 00 00 00

mov eax, 0x12345678      B8 78 56 34 12
```

Vì vậy CPU không thể đơn giản giả định:

```text
1 instruction = 4 bytes
```

Thay vào đó, CPU phải xác định ranh giới của từng instruction dựa trên encoding của nó. Đây cũng là một trong những lý do việc phân tích machine code x86-64 có thể phức tạp.

**Tuy nhiên :** Machine Code không chỉ là một chuỗi số nhị phân ngẫu nhiên. Ví dụ:

```text
BF 01 00 00 00
```

không phải năm byte độc lập. Chúng cùng nhau tạo thành một encoding của instruction:

```asm
mov edi, 1
```

Trong encoding này:

```text
BF
```

đóng vai trò xác định opcode/encoding form, còn:

```text
01 00 00 00
```

biểu diễn immediate value `1` theo little-endian. Do đó, machine code có cấu trúc và quy tắc. Việc học Program Encodings chính là học những quy tắc đó.

#### 1.3.4. Disassembler: đi từ Machine Code về Assembly

Quá trình assembler thực hiện:

```text
Assembly
    ↓
Machine Code
```

thì disassembler thực hiện chiều ngược lại:

```text
Machine Code
    ↓
Assembly
```

Ví dụ:

```bash
objdump -d -Mintel ./asm
```

có thể hiển thị:

```text
40100c:    bf 01 00 00 00    mov edi,0x1
```

Ở đây ta có thể thấy trực tiếp mối quan hệ:

```text
Address
   │
   ▼
40100c:  bf 01 00 00 00  mov edi,0x1
          └──────┬──────┘
             Machine Code
                    │
                    ▼
              Assembly
```

Ghidra, GDB và nhiều công cụ reverse engineering cũng thực hiện quá trình tương tự ở mức độ phức tạp hơn.

### 1.3.5. Phân biệt giữa byte opcode và các byte rác

Khi quan sát một chương trình dưới dạng hexadecimal, ta có thể thấy một chuỗi byte liên tiếp, ví dụ:

```text
bf 01 00 00 00
```

Một cách nhìn sai thường gặp là cho rằng mỗi byte tương ứng với một instruction, hoặc chỉ `bf` mới là mã máy còn `01 00 00 00` là các byte rác. Thực tế toàn bộ chuỗi trên đều là machine code của một instruction:

```asm
mov edi, 1
```

Trong đó:

```text
bf          -> opcode / instruction encoding
01 00 00 00 -> immediate value = 1
```

CPU không nhìn `01 00 00 00` như những byte vô nghĩa. Nó dựa vào encoding của instruction để biết rằng sau opcode `BF` còn phải đọc thêm 4 byte làm giá trị immediate.

Vì vậy, cần phân biệt ba khái niệm:

| Thành phần                                | Ý nghĩa                                                                                        |
| ----------------------------------------- | ---------------------------------------------------------------------------------------------- |
| **Opcode**                                | Phần encoding xác định operation mà CPU phải thực hiện                                         |
| **Operand bytes**                         | Các byte biểu diễn register, immediate, displacement, địa chỉ... tùy instruction               |
| **Padding / dữ liệu không được thực thi** | Các byte tồn tại trong file hoặc vùng nhớ nhưng không thuộc instruction đang được CPU thực thi |

Ví dụ:

```asm
mov edi, 1
```

có thể được encode thành:

```text
BF 01 00 00 00
```

Ta có:

```text
BF
│
└── opcode / opcode form

01 00 00 00
│  │  │  │
└──┴──┴──┴── immediate = 1
```

Ở đây `01 00 00 00` được lưu theo little-endian:

```text
0x00000001
↓
01 00 00 00
```

Tuy nhiên không phải mọi byte trong vùng `.text` đều là opcode. Một file ELF có thể chứa nhiều loại dữ liệu khác nhau. Ví dụ:

```text
.text
    machine code

.rodata
    string, constant...

.data
    biến toàn cục đã khởi tạo

.bss
    dữ liệu chưa khởi tạo

.padding
    các byte dùng để căn chỉnh
```

Ngay cả trong `.text`, không phải cứ nhìn thấy một byte riêng lẻ là có thể kết luận nó là opcode. Ví dụ một instruction có thể dài nhiều byte:

```text
48 89 e5
```

được disassemble thành:

```asm
mov rbp, rsp
```

Ở đây:

```text
48 -> REX prefix
89 -> opcode
e5 -> ModR/M
```

Do đó, gọi `48` hoặc `e5` là byte rác là sai. Chúng đều cần thiết để CPU giải mã instruction.

- **Vậy byte rác thực sự là gì?:** nó là một byte chỉ có thể được gọi là không thuộc code đang xét khi ta có bằng chứng rằng nó không được CPU sử dụng như một phần của instruction tại control flow đó. Ví dụ compiler/linker có thể thêm padding:

  ```text
  90 90 90 90
  ```

  `90` là encoding của:

  ```asm
  nop
  ```

  Các byte này có thể được dùng để căn chỉnh địa chỉ hoặc lấp khoảng trống. Chúng không phải “rác” theo nghĩa dữ liệu vô nghĩa; chúng vẫn có encoding hợp lệ và CPU vẫn có thể thực thi chúng nếu control flow nhảy tới đó. Một trường hợp khác là dữ liệu nằm cạnh code:

  ```text
  .text:
      ... instructions ...

  .rodata:
      "Hello World\n"
  ```

  Chuỗi:

  ```text
  48 65 6c 6c 6f 20 57 6f 72 6c 64
  ```

  không phải opcode chỉ vì nó cũng được biểu diễn dưới dạng hexadecimal. Nó là data.

- **Vì sao disassembler có thể biết byte nào thuộc instruction?:** Disassembler không đơn giản chỉ đọc từng byte rồi gọi byte đó là opcode. Nó đọc instruction theo **instruction encoding của ISA** và xác định instruction có độ dài bao nhiêu. Ví dụ:

  ```text
  BF 01 00 00 00
  ```

  Disassembler đọc:

  ```text
  BF
  ```

  và biết encoding này yêu cầu thêm một immediate 32-bit:

  ```text
  01 00 00 00
  ```

  Sau đó instruction kết thúc tại đây. Byte tiếp theo sẽ được giải mã như instruction tiếp theo:

  ```text
  BF 01 00 00 00 | ...
  └──── instruction ────┘
  ```

  Đây là lý do x86-64 có thể chứa các instruction có độ dài khác nhau:

  ```text
  90                   nop
  bf 01 00 00 00       mov edi, 1
  48 89 e5             mov rbp, rsp
  ```

  Instruction boundary không thể xác định chỉ bằng cách chia chuỗi byte thành từng nhóm có kích thước cố định.

> [!IMPORTANT]
> **Lưu ý quan trọng:** Có những byte có thể được giải mã thành instruction hợp lệ nhưng trong context hiện tại lại không phải code.

Ví dụ dữ liệu:

```text
48 65 6c 6c 6f
```

hoàn toàn có thể khiến một disassembler tạo ra các instruction hợp lệ nếu ta cố tình bảo nó disassemble vùng dữ liệu đó. Vì vậy:

```text
hexadecimal bytes
        ↓
  disassembler
        ↓
possible instructions
```

không đồng nghĩa với:

```text
mọi instruction được disassemble
        =
code thực sự được chương trình thực thi
```

Reverse engineer phải kết hợp `instruction decoding + control flow + section information + references + memory permissions` để xác định byte nào thực sự là code. Đây cũng là lý do việc hiểu Program Encodings quan trọng: ta không chỉ học cách đọc `BF 01 00 00 00` thành `mov edi, 1`, mà còn phải hiểu tại sao CPU biết phải đọc bao nhiêu byte và những byte đó đóng vai trò gì trong encoding của instruction.

#### 1.3.6. Vì sao Reverse Engineering cần hiểu cả hai?

Nếu chỉ biết Assembly:

```asm
mov rdi, 1
syscall
```

ta có thể hiểu chương trình đang làm gì. Nhưng nếu hiểu Machine Code:

```text
BF 01 00 00 00
48 BE ...
48 C7 C2 0B 00 00 00
B8 01 00 00 00
0F 05
```

ta có thể bắt đầu đặt những câu hỏi sâu hơn:

* Byte nào là opcode?
* Operand được encode ở đâu?
* Tại sao instruction này dài 5 byte?
* Vì sao instruction khác lại dài 10 byte?
* Immediate được lưu theo thứ tự byte nào?
* Register được biểu diễn bằng những bit nào?
* Khi nào xuất hiện REX prefix?
* ModR/M và SIB được sử dụng như thế nào?

Đó chính là bước chuyển từ việc đọc Assembly sang việc hiểu instruction encoding. Và đó cũng là mục tiêu chính của phần Program Encodings.

#### 1.3.7. Phân biệt giữa instruction, vaddr instrution, offset và assembly representation của instruction trong gdb

Rất nhiều người nhầm giữ instrution, offset và assembly representation của một instrution ở gdb khi disas nó ra ví dụ một đoạn như sau :

```asm
0x0000555555555151 <+8>:  64 48 8b 04 25 28 00 00 00    mov rax,QWORD PTR fs:0x28
```

Họ khá dễ nhầm `0x0000555555555151` là instrution, thực chất nó là vaddr của instrution đó. Ta có thể biểu diễn nó như sau:

```
0x0000555555555151
        │
        └── địa chỉ ảo (virtual address) của instruction

<+8>
 │
 └── offset của instruction so với đầu hàm main

64 48 8b 04 25 28 00 00 00
│
└── machine-code bytes của instruction

mov rax,QWORD PTR fs:0x28
│
└── assembly representation của instruction đó
```

Trong đó `0x0000555555555151` nó ko phải instrution, mà nó là địa chỉ ảo (vaddr) trỏ tới instruction. `<+8>` nó ko phải con số vô nghĩa, nó là khoảng cách offset từ mốc có thể là (main, _start) đến địa chỉ trỏ tới instruction. Còn dãy `64 48 8b 04 25 28 00 00 00` là byte obcode, machine code của instruction, đây mới gọi là instruction tổng thể, còn `mov rax,QWORD PTR fs:0x28` chính là assembly representation của instruction đây là sản phẩm sau khi qua biên dịch lại thành hợp ngữ mà con người có thể đọc được