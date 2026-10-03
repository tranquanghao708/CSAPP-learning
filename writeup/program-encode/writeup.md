# CSAPP : Program Encoding

**Mục lục**

- [1.Tổng quan về Program Encoding](#1tổng-quan-về-program-encoding)
	- [1.1 Program Encoding là gì?](#11-program-encoding-là-gì)
	- [1.2 Quá trình từ mã nguồn C tới machine code](#12-quá-trình-từ-mã-nguồn-c-tới-machine-code)
	   - [1.2.1 Preprocessing](#121-preprocessing)
	   - [1.2.2 Compilation](#122-compilation)
	   - [1.2.3 Assembling](#123-assembling)
	   - [1.2.4 Linking](#124-linking)
	   - [1.2.5 CPU thực thi machine code](#125-cpu-thực-thi-machine-code)
	- [1.3. Assembly và Machine Code](#13-assembly-và-machine-code)
       - [1.3.1. Assembly không phải Machine Code](#131-assembly-không-phải-machine-code)
       - [1.3.2. Assembly là dạng biểu diễn gần với Machine Code](#132-assembly-là-dạng-biểu-diễn-gần-với-machine-code)
       - [1.3.3. Một Assembly instruction có thể có độ dài khác nhau](#133-một-assembly-instruction-có-thể-có-độ-dài-khác-nhau)
       - [1.3.4. Disassembler: đi từ Machine Code về Assembly](#134-disassembler-đi-từ-machine-codevề-assembly)
	   - [1.3.5. Phân biệt giữa byte opcode và các byte rác](#135-phân-biệt-giữa-byte-opcode-và-các-byte-rác)
       - [1.3.6. Vì sao Reverse Engineering cần hiểu cả hai?](#136-vì-sao-reverse-engineering-cần-hiểu-cả-hai)
       - [1.3.7. Phân biệt giữa instruction, vaddr instruction, offset và assembly representation của instruction trong gdb](#137-phân-biệt-giữa-instruction-vaddr-instruction-offset-và-assembly-representation-của-instruction-trong-gdb)

- [2.Cấu trúc tổng quát của một Instruction](#2cấu-trúc-tổng-quát-của-một-instruction)
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

## 1.Tổng quan về Program Encoding
### 1.1 Program Encoding là gì?

Khái niệm program encoding ko chỉ là một sản phẩm sau khi thông qua quá trình biên dịch từ ngôn ngữ lập trình sang mã máy mà CPU có thể hiểu được mà là cách chương trình được biểu diễn ở các mức khác nhau, đặc biệt trong ngữ cảnh CSAPP là cách mã nguồn được chuyển thành machine-level representation mà CPU thực thi, nói đơn giản program encoding là mã hóa các ngôn ngữ cho con người có thể đọc được dễ dàng thành ngôn ngữ máy cho máy tính làm việc thông qua các trình biên dịch

### 1.2 Quá trình từ mã nguồn C tới machine code
#### 1.2.1 Preprocessing

Quá trình này là quá trình đầu tiên, khi tiến hành biên dịch từ mã C tới mã máy mà máy tính có thể hiểu được compiler chèn in nguyên cái mã nguồn của các file tiêu đề ví dụ như (stdio.h, string.h v.v.) ở trên đầu logic C. Ví dụ :

```c
#include <stdio.h>

int main(void){
	printf("hello world\n");
	return 0;
}
```

trong khi tiêu đề (stdio.h) có khai báo `printf()`. Giả sử header có khai báo minh họa của `printf()` là :

```header
void printf(int a, int b, int c); //ví dụ minh họa
/*
Các hàm khác
*/
```

thì khi compiler làm việc thực hiện quá trình đầu tiên thì kết quả sẽ như này:

```c
void printf(int a, int b, int c); //ví dụ minh họa
/*
Các hàm khác
*/

int main(void){
	printf("hello world\n");
	return 0;
}
```

Ta thấy, nó chèn in nguyên cái mã nguồn của file tiêu đề vào cái phần `include`, cái ta `import` các thư viện vào để dùng các hàm như `printf()` hay `scanf()`. Ở quy trình đầu tiên preprocessing này nó có thể xử lý các thẻ như :

```c
#include
#define
#if
#ifdef
...
```

preprocessor thực hiện việc include nội dung header theo cơ chế của preprocessor, sau đó tạo ra translation unit đã được xử lý. Để có thể dừng ở phần đầu tiên và dump ra một file có thể cho ta xem toàn bộ quy trình kết quả sau khi preprocessing thực hiện hoàn tất, ta dùng lệnh `gcc -E main.c -o main.i` lệnh này ra lệnh cho compiler là khi thực hiện xong quy trình đầu tiên, thay vì biên dịch ra hay tới các quy trình khác thì hãy lưu kết quả của quy trình preprocessing vào file `main.i`, khi đó `main.i` là nơi chứa sản phẩm sau khi quy trình đầu tiên hoàn tất. Ta có thể truy cập vào file `main.i` để xem sản phẩm

#### 1.2.2 Compilation

Quá trình thứu 2 kế tiếp sau khi thực hiện qua quá trình preprocessing, quá trình này Compiler dịch mã C thành assembly, với cú pháp phụ thuộc vào compiler/option; GCC có thể xuất assembly theo AT&T hoặc Intel syntax. Ví dụ với at&t :

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

lúc này nó vẫn chưa phải mã thực thi, nó vẫn là hợp ngữ cho con người đọc được. Tác dụng nếu ta có thể hiểu sâu về phần này thì chúng ta cũng có thể ra lệnh compiler dump ra dạng mã ở quy trình bước 2 này để debug cũng là một ý tưởng khá hay ta có thể dùng lệnh `gcc -S main.c -o main.s`, lệnh này sẽ cho compiler biên dịch tới quá trình bước 2 ra một file, khi đó ta sẽ thấy được mã hợp ngữ được biên dịch từ C đầu vào qua

#### 1.2.3 Assembling

Quá tình này là quá trình số 3, ở đây Assembler sẽ dịch assembly thành machine-code bytes và tạo object file ở quy tình vừa rồi ở bước 2 sang mã máy vào một file object `(assembly -> .o files)`, file có đuôi `.o` này là một file chưa các mã máy được biên dịch từ hợp ngữ nên, thường là một ELF relocatable object trên Linux x86-64. Ta có thể kiểm tra qua lệnh `file` trên linux

Chúng ta có thể xem file dạng này với lệnh chẳng hạn như `gcc -c main.c -o main.o`, lệnh này ra lệnh cho compiler là thực hiện xong quy trình 3 là biên dịch hợp ngữ ra một file đuôi `.o` chẳng hạn `main.o`, hoặc chúng ta đã có file hợp ngữ như đã dùng lệnh `gcc -S main.c -o main.s` ở bước vừa rồi thì ta dùng lệnh `as main.s -o main.o` để biên dịch chúng ra, khi có file `.o` chẳng hạn `main.o` thì ta có thể dùng `objdump -d main.o` để xem machine code chẳng hạn như :

```
48 89 e5
48 83 ec 10
c7 45 fc 0a 00 00 00
```

Đây mới là những byte machine code tương ứng với các instruction.

#### 1.2.4 Linking

Khi đã biên dịch ra một file `.o` rồi, thì đây là bước 4 kế tiếp, một chương trình thực tế thường ko chỉ chứa code của `main.c` mà nó còn liên kết nhiều thư viện bên ngoài. Nên phần này góp phần để liên kết các nguồn logic bên ngoài ở các thư viện đã được import ở nguồn vào file nhị phân. Sau bước này, chương trình ko chỉ chứa code của `main.c` mà còn liên kết nhiều nguồn code khác như

```
main.o
   │
   ├── reference: printf
   │
   ▼
linker
   │
   ▼
ELF executable
   │
   └── printf@plt
           │
           ▼
      dynamic linker
           │
           ▼
      libc.so
		   │
           ▼
          main (file thực thi hoàn chỉnh)
```

> Với dynamically linked executable

Executable main vẫn chứa machine code, nhưng đồng thời còn có nhiều thành phần khác của ELF như section, symbol, relocation information, dynamic linking information,...

#### 1.2.5 CPU thực thi machine code

Sau khi hoàn tất quy trình bước 4 là linking, thực tế file output là Executable ELF thực thi hoàn chỉnh có thể thực thi được, tuy nhiên ko phải cứ nhập lệnh `./main` là hệ điều hành chọi nguyên dàn mã trong file vô cho CPU xử lý, còn vài bước mà hệ điều hành cần làm để có thể thực thi một file hoàn chỉnh thế này đó là

```
ELF executable
      │
      ▼
OS loader
      |
      |── đọc ELF headers
      |── tạo process address space
      |── map các loadable segments
      |── thiết lập permissions
      |── thiết lập entry point
      │
      ▼
Virtual Address Space
      │
      │   page tables
      │   VPN → PFN
      ▼
CPU bắt đầu tại entry point
      │
      ▼
   Fetch
      ↓
   Decode
      ↓
   Execute
      ↓
	 ...
```

> [!IMPORTANT]
> **Điều quan trọng:** Ở đây, CPU nó ko đọc từng byte,bit trực tiếp trong file nó chỉ thực thi instruction bytes nằm trong memory.

Cho một ví dụ như sau :

```
ELF file:

.text
--------------------------------
b8 3c 00 00 00
bf 01 00 00 00
0f 05
--------------------------------
          ↓ loader
RAM / virtual address space
          ↓
   RIP = 0x401000
          ↓
     CPU fetch:
   b8 3c 00 00 00
          ↓
       decode:
     mov eax, 0x3c
          ↓
       execute
```

Nghĩa là, khi dùng lệnh `./main`, các lệnh trong file ELF vốn đã được cấu trúc `.text, .data, .rodata v.v..` trước đó, nó là sản phẩm compiled, khi chương trình được khởi chạy, OS loader sẽ tạo address space cho process và map các loadable segments của ELF vào virtual address space. Các section như `.text`, `.data`, `.rodata` là khái niệm của ELF, loader chủ yếu làm việc với program headers / loadable segments, không đơn giản nạp từng section vào memory, với kernel thì vùng nhớ này được sắp xếp bởi page table ánh xạ virtual page number (VPN) sang physical frame number (PFN), cùng với các permission/status bits. Sau khi nạp xong vào vmem, CPU sẽ tiến hành xuất phát tại entry point (_start), theo sơ đồ minh họa entry point ở vaddr là `0x401000` và CPU tiến hành tại đây.

Tiếp đến là fetch. Fetch là quá trình CPU lấy các byte của instruction từ memory dựa trên địa chỉ hiện tại trong RIP, đưa chúng vào các thành phần bên trong CPU để tiếp tục xử lý, có thể hình dung thế này :

```
RAM / Virtual Memory
────────────────────────────────
0x401000:  b8
0x401001:  3c
0x401002:  00
0x401003:  00
0x401004:  00
0x401005:  bf
...
────────────────────────────────
                ▲
                │
             Fetch
                │
                │
               CPU
```

Trong reverse, ta cũng đã quen thuộc với RIP là một thanh ghi đặc biệt giữ địa chỉ của instruction tiếp theo mà CPU sẽ thực thi, ở đây như đã nói ở trên thì thanh ghi RIP hiện tại là đang ở vaddr `0x401000`, lúc này CPU biết instruction tiếp theo bắt đầu tại địa chỉ `0x401000`. Nếu `RIP=0x401000` thì CPU sẽ cần phải fetch để lấy instruction trong vmem về phía mình. Có thể hình dung :

```
RIP
 │
 │ 0x401000
 ▼
Memory
0x401000: b8
0x401001: 3c
0x401002: 00
0x401003: 00
0x401004: 00
```

> Để đơn giản hóa mô hình, ta giả sử CPU fetch đủ 5 byte cần thiết cho instruction này.

Nó sẽ đọc các byte trong bộ nhớ ảo (vmem) vào hệ thống CPU, kết quả sẽ là `b8 3c 00 00 00` đó là fetch. Chưa cần phải biết nó biên dịch ra hợp ngữ là sao

> [!IMPORTANT]
> **Điều quan trọng:** `RIP=0x401000` không có nghĩa CPU đọc đúng 5 byte ngay lập tức vì hardware thực tế không nhất thiết thực hiện một memory read đúng 5 byte vì nó biết trước instruction dài 5 byte.
>
> CPU hiện đại thường fetch instruction bytes theo cache lines / fetch blocks lớn hơn nhiều, sau đó instruction decoder xác định boundary của từng instruction.

<details>
	<summary><b>[Câu hỏi]</b> Vì sao CPU cần phải fetch?</summary>
<table>
<tr>
<td>

---


<sub>--đã hết phần giải thích--</sub>

---

</td>
</tr>
</table>
</details>

bước tiếp theo là decode, bước này là bước CPU phân tích chuỗi byte sau khi fetch từ vmem sang với chuỗi `b8 3c 00 00 00` thì CPU decode nó thành đại ý chẳng hạn như `MOV EAX, 0x3c`. Sau quá trình decode là tới quá trình execute, CPU sẽ thực hiện ngữ nghĩa (semantics) của instruction như `EAX <- 0x3c`, sau đó `RAX = 60` và CPU mới tới instruction kế tiếp là `0x401005`, vậy nên tổng quát toàn bộ quá trình là :

```
                  Virtual Memory
                       │
                       │
                 RIP = 0x401000
                       │
                       ▼
              ┌─────────────────┐
FETCH         │ đọc bytes       │
              │ b8 3c 00 00 00  │
              └────────┬────────┘
                       │
                       ▼
              ┌─────────────────┐
DECODE        │ phân tích       │
              │ b8 → MOV        │
              │ 3c → immediate  │
              └────────┬────────┘
                       │
                       ▼
              ┌─────────────────┐
EXECUTE       │ EAX ← 0x3c      │
              └─────────────────┘
```

> [!IMPORTANT]
> **Điểm quan trọng:** Về tổng quát thì ko phải là instruction kế tiếp CPU luôn là `RIP = RIP + instruction_length` mà còn có thể có các lệnh như `jmp`, `je`, `jz` v.v..

### 1.3. Assembly và Machine Code
#### 1.3.1. Assembly không phải Machine Code

Nhiều người thường rất hay nhầm và thường hợp machine code và hợp ngữ lại thành một. Nhưng đó là sai lầm nhầm lẫn tai hại nhất, ta cần phân biệt hợp ngữ `mov rdi, 1` là textual representation và `BF 01 00 00 00` là encode representation, ta phải hiểu hợp ngữ sinh ra là cho con người có thể lập trình, đọc hiểu dễ dàng hơn còn machine code là dành cho CPU để thực hiện các quy trình `fetch -> decode -> execute` sau khi chạy lệnh thực thi `./main`

<details>
	<summary><b>[Câu hỏi]</b> Machine code liệu có phải mã nhị phân 0,1 cho máy tính có thể hiểu được?</summary>
<table>
<tr>
<td>

---

Machine code là tập hợp các byte biểu diễn các instruction dưới dạng encoding mà CPU của một kiến trúc/ISA cụ thể có thể fetch, decode và thực thi. Ở mức thấp nhất, các byte này được cấu thành từ các bit 0 và 1. Vậy nên việc gọi machine code là mã nhị phân là có thể, vì machine code được biểu diễn dưới dạng bit `0/1`.


Tuy nhiên CPU không hiểu một chuỗi 0 và 1 theo nghĩa trừu tượng. Vì CPU có một ISA và các quy tắc instruction encoding. **Ví dụ** với x86-64:

```
10111000 00111100 00000000 00000000 00000000
    │             │
    │             └── immediate = 0x3c
    │
    └── encoding của MOV EAX, imm32
```

CPU dựa vào quy tắc encoding của x86-64 để phân tích chuỗi bit đó thành:

```
b8 3c 00 00 00
       ↓
   MOV EAX, 0x3c
       ↓
   EAX ← 60
```

suy ra cùng là các byte `0/1`, nhưng cách phân chia và diễn giải chúng theo ISA mới quyết định chúng biểu diễn instruction nào.

<sub>--đã hết phần giải thích--</sub>

---

</td>
</tr>
</table>
</details>

#### 1.3.2. Assembly là dạng biểu diễn gần với Machine Code

Hợp ngữ ko phải là ngôn ngữ hoàn toàn độc lập với CPU, với chip `core i3` này hay chip `core i5` khác chẳng hạn, nếu như cùng một loại mã hợp ngữ may mắn chạy được và ổn định trên hai con chip `i3` và `i5` thì ko có nghĩa nó sẽ chạy được trên các con chip điện thoại thường có ngành kiến trúc như `arm` thay vì `amd` , vì thế hợp ngữ nó phụ thuộc rất mạnh vào instruction set architecture (ISA). **Ví dụ**, instruction:

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

Cùng một chương trình C có thể được compiler dịch thành các instruction khác nhau tùy thuộc vào kiến trúc CPU mục tiêu. Điều này giúp ta cũng mang máng rằng `gcc` code dài ko chỉ riêng là xử lý các `optimiziter, compiler, assembler v.v..` mà còn phải làm thế nào để hỗ trợ đa nền tảng sao cho chương trình có thể thực hiện hành vi như ý đồ của C chỉ định

#### 1.3.3. Một Assembly instruction có thể có độ dài khác nhau

Điều rất quan trọng ở phần này rằng, ta ko nên nghĩ `"à, cứ một lệnh thế này sẽ là một length giống nhau"`, sai. Một lệnh instruction ko có nghĩa là một độ dài cùng giống nhau, chúng khác nhau vì nhiều thứ **ví dụ** các instruction khác nhau có thể chiếm số byte khác nhau:

<div align="center">

|Instruction | Machine Code |
|:-|:-:|
| ret                     | C3 |
| nop                     | 90 |
| mov edi, 1               | BF 01 00 00 00 |
| mov eax, 0x12345678     | B8 78 56 34 12 |

</div>

Vì thế CPU nó ko đơn giản là giả định số byte cố định vào một instruction, thay vào đó nó phải xác định ranh giới của từng instruction dựa trên encoding của nó. Đây cũng là một trong những lý do việc phân tích machine code x86-64 có thể phức tạp.