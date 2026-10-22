# CSAPP : Program Encoding

> Ngày bắt đầu viết : 23/9/2026
> Ngày hoàn thành :

**Mục lục**

<table>
<tr>
<td width="50%" valign="top">

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
	   - [1.3.5. Phân biệt giữa byte opcode và các data/padding](#135-phân-biệt-giữa-byte-opcode-và-các-datapadding)
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
  - [3.3. Các nhóm của Prefix ngoài Rex](#33-các-nhóm-của-prefix-ngoài-rex)

</td>

<td width="50%" valign="top">

- [4. ModR/M Byte](#4-modrm-byte)
  - [4.1. ModR/M là gì?](#41-modrm-là-gì)
  - [4.2. Cấu trúc ModR/M](#42-cấu-trúc-modrm)
  - [4.3. Giải mã ModR/M bằng tay](#43-giải-mã-modrm-bằng-tay)

- [5. SIB Byte](#5-sib-byte)
  - [5.1. SIB là gì?](#51-sib-là-gì)
  - [5.2. Cấu trúc SIB](#52-cấu-trúc-sib)
  - [5.3. Giải mã SIB bằng tay](#53-giải-mã-sib-bằng-tay)

- [6. Object Code và ELF](#6-object-code-và-elf)
  - [6.1. Object code là gì?](#61-object-code-là-gì)
  - [6.2. ELF là gì?](#62-elf-là-gì)
  - [6.3. Code Section](#62-code-section)
  - [6.3. Relocation](#63-relocation)
  - [6.4. Symbol và Symbol Table](#64-symbol-và-symbol-table)
  - [6.5. Từ Object File đến Executable](#65-từ-object-file-đến-executable)

- [7. Lập trình byte program]
  - [lập trình tích hợp byte program trên file định dạng C]
  - [lập trình tích hợ byte program trên file định dạng hợp ngữ]
- [10. Tổng kết](#10-tổng-kết)
  - [10.1. Instruction được encode như thế nào?](#101-instruction-được-encode-như-thế-nào)
  - [10.2. Quy trình Decode một Instruction](#102-quy-trình-decode-một-instruction)
  - [10.3. Những gì cần nhớ](#103-những-gì-cần-nhớ)

</td>
</tr>
</table>

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
   │ static linker
   ▼
executable
   │
   ├── PLT
   ├── GOT
   ├── dynamic section
   └── DT_NEEDED → libc.so
                     │
                     ▼
              dynamic linker
                     │
                     ▼
             symbol resolution
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

Nhiều người thường rất hay nhầm và thường hợp machine code và hợp ngữ lại thành một. Nhưng đó là sai lầm nhầm lẫn tai hại nhất, ta cần phân biệt hợp ngữ `mov edi, 1` là textual representation và `BF 01 00 00 00` là encode representation, ta phải hiểu hợp ngữ sinh ra là cho con người có thể lập trình, đọc hiểu dễ dàng hơn còn machine code là dành cho CPU để thực hiện các quy trình `fetch -> decode -> execute` sau khi chạy lệnh thực thi `./main`

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

Hợp ngữ ko phải là ngôn ngữ hoàn toàn độc lập với CPU, với chip `core i3` này hay chip `core i5` khác chẳng hạn, nếu như cùng một loại mã hợp ngữ may mắn chạy được và ổn định trên hai con chip `i3` và `i5` thì ko có nghĩa nó sẽ chạy được trên các con chip điện thoại thường có ngành kiến trúc như `arm` thay vì `amd` , vì thế hợp ngữ nó phụ thuộc rất mạnh vào instruction set architecture (ISA). **Ví dụ**, instruction `mov edi, 1` là instruction của x86-64. Một kiến trúc khác như ARM64 có instruction set và encoding hoàn toàn khác. Điều này có nghĩa:

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

Vì thế CPU nó ko đơn giản là giả định số byte cố định vào một instruction, thay vào đó nó phải xác định ranh giới của từng instruction dựa trên encoding của nó. Đây cũng là một trong những lý do việc phân tích machine code x86-64 có thể phức tạp. Tuy nhiên, Machine Code không chỉ là một chuỗi số nhị phân ngẫu nhiên. **Ví dụ** `BF 01 00 00 00` ko phải là 5 byte độc lập, chúng cùng nhau mã hóa thành một instruction `mov edi, 1`

#### 1.3.4. Disassembler: đi từ Machine Code về Assembly

Disassembler là công cụ chuyển đổi từ mã máy sang hợp ngữ, công cụ nổi tiếng trong giới reverse engineering, cái này đơn giản là nó phân tích các opcode, mã máy có trong file ELF hay các file nhị phân được compiled ra từ trước đó, dựa vào ISA, instrution encoding để cho đầu ra là assembly representation :

```
Machine-code bytes
        │
        ▼
   Disassembler
        │
        │ dựa vào ISA + instruction encoding
        ▼
Assembly representation
```

Cái này chỉ giới thiệu sơ qua vì nó chỉ giới thiệu công cụ disassembler. Các disassembler nổi tiếng như (objdump, gdb, ghidra v.v.) nói chung nó thường tích hợp chung với các IDE reverse để phục vụ soi các hợp ngữ của mã máy trong file

#### 1.3.5. Phân biệt giữa byte opcode và các data/padding

Cái này cực kỳ quan trọng, khi ta reverse hay debug một binary gì đó, ta phải phân biệt được cái byte `0b 00 10 00 00` này và `01 2c 9c 10` kia, nó là data/padding, hay opcode, nếu ko chúng ta rất dễ tốn time và đưa ra kết luận sai hoàn toàn chỉ vì lỗi nghiêm trọng tai hại này. Cách phân biệt buộc ta phải biết các bảng quy định opcode nó luôn có điểm khởi đầu và điểm kết thúc, nếu các byte có giá trị vượt quá điểm kết thúc của ISA quy định thì byte đó chắc chắn ko phải là opcode, mà là có thể là byte khác, có thể là operand, trường khác hoặc byte thuộc vùng miền khác

Tuy nhiên các byte ko nằm trong vùng opcode ko có nghĩa là nó ko thành một instruction mà bỏ đi, nó có thể là thanh ghi, hay là một byte có thể góp phần liên kết vào các opcode để tạo nên một instruction. **Ví dụ** `48 89 e5` ko phải:

```
48 = opcode
89 = rác
e5 = rác
```

mà nó là một instruction hoàn chỉnh `mov rbp, rsp`. Trong đó `48` là REX prefix, `89` là opcode, `e5` là ModR/M. Ngược lại, một byte thực sự nằm trong vùng padding hoặc data thì có thể không phải instruction. Vấn đề của reverse engineering là xác định ranh giới code/data và cách giải mã bytes, chứ không chỉ nhìn một byte rồi phán nó là opcode hay rác.

#### 1.3.6. Vì sao Reverse Engineering cần hiểu cả hai?

Hiểu cả hai hợp ngữ và opcode, giúp reverse egineer có cái nhìn chính xác về rev vì chỉ hiểu hợp ngữ hoàn toàn ko đủ khi rev. Các lý do quan trọng: 

- 1. **Thứ nhất:** hiểu machine code cho ta biết những byte thực sự tồn tại trong binary, còn hiểu hợp ngữ assembly cho ta một cách biểu diễn dễ đọc hơn về ý nghĩa của những byte đó. 

- 2. **Thứ hai:** hiểu machine code giúp ta biết và bypass kỹ thuật làm rối mã thay đổi byte code fake, ko nghe nhầm, ko viễn vông và nó có thật khá lâu ở các mã độc chuyên sâu. Một khi mã độc fake hay can thiệp vào các byte code trong binary chính nó chính các công cụ như `GDB, ghidra, objdump, v.v.` đều phán đoán hợp ngữ sai hoàn toàn, hơn nữa ghidra có decompiler C, một khi hợp ngữ sai thì mã C decompiled ra cũng sai theo dây chuyền

- 3. **Thứ ba:** hiểu machine code giúp phán đoán kiểu dữ liệu khi đọc hợp ngữ, tuy có decompiler nhưng vấn đề nó khá sai xót, đôi khi nó chỉ là `undenifined8` còn lại ta tự đoán, việc hiểu các byte machine code, đếm nó và thêm các kỹ thuật khác như nhìn thanh ghi v.v.. đều góp phần phán đoán chính xác hơn kiểu dữ liệu trong mã. Nếu đoán sai kiểu dữ liệu, hậu quả có thể gây sai sót dây chuyền khi phân tích bit bù hai hay là các hành vi của mã

#### 1.3.7. Phân biệt giữa instruction, vaddr instruction, offset và assembly representation của instruction trong gdb

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

Trong đó `0x0000555555555151` nó ko phải instrution, mà nó là địa chỉ ảo (vaddr) trỏ tới instruction. `<+8>` nó ko phải con số vô nghĩa, nó là khoảng cách offset từ mốc có thể là (main, _start) đến địa chỉ trỏ tới instruction. Còn dãy `64 48 8b 04 25 28 00 00 00` là là instruction encoding / instruction bytes, còn `mov rax,QWORD PTR fs:0x28` chính là assembly representation của instruction đây là sản phẩm sau khi qua biên dịch lại thành hợp ngữ mà con người có thể đọc được

Nói chung, instruction thực sự nó có hai cách biểu diễn, một là byte tổng quát của instrution như `64 48 8b 04 25 28 00 00 00`, theo structure, hai là assembly representation như `mov rax,QWORD PTR fs:0x28` còn `0x0000555555555151` là địa chỉ ảo (vaddr) trỏ tới instruction

---

## 2.Cấu trúc tổng quát của một Instruction

Một instruction ở cấp machine code không nhất thiết chỉ gồm một byte opcode. Đặc biệt với x86-64, một instruction có thể được tạo thành từ nhiều thành phần khác nhau, trong đó mỗi thành phần đảm nhiệm một vai trò nhất định trong việc mô tả instruction.

Một mô hình tổng quát thường được biểu diễn như sau:

```
┌──────────┬────────┬────────┬──────┬──────────────┬──────────────┐
│ Prefixes │ Opcode │ ModR/M │ SIB  │ Displacement │ Immediate    │
└──────────┴────────┴────────┴──────┴──────────────┴──────────────┘
```
Tuy nhiên, không phải instruction nào cũng có đầy đủ tất cả các thành phần trên. Tùy instruction, một hoặc nhiều trường có thể không xuất hiện. **Ví dụ**, `b8 3c 00 00 00`, có thể được disassemble thành `mov eax, 0x3c` Trong trường hợp này, encoding có thể được nhìn đơn giản như:

```
┌────────┬──────────────────────────┐
│ Opcode │ Immediate                │
├────────┼──────────────────────────┤
│   b8   │ 3c 00 00 00              │
└────────┴──────────────────────────┘
```

Trong đó:

```
b8
│
└── Opcode / opcode form

3c 00 00 00
│
└── imm32 = 0x0000003c

```

CPU không nhìn chuỗi này dưới dạng chữ `mov eax, 0x3c`, mà nhận được các instruction bytes `b8 3c 00 00 00`. Sau đó decoder sử dụng quy tắc instruction encoding của ISA để xác định instruction tương ứng.

<details>
	<summary><b>[Câu hỏi]</b> Làm thế nào để nhận biết các byte đó thuộc cấu trúc trường nào của instruction?</summary>
<table>
<tr>
<td>

---

Thoáng qua ta thấy ví dụ bên trên, ta thấy trước ví dụ là một bảng cấu trúc, nhưng ta cũng thấy dòng chữ ko phải cứ instruction nào cũng tuân theo hết các cấu trúc trên. Vậy bây giờ vì sao và làm thế nào để ta biết `b8` là thuộc trường opcode và `3c 00 00 00` là thuộc trường immediate (`imm32`), ta cần hiểu CPU không tự đoán dựa trên hình dạng của byte. Nó dựa vào quy tắc encoding được ISA định nghĩa cho từng instruction form.

Có thể hình dung Instruction Encoding giống như một grammar (ngữ pháp). **Ví dụ**, một encoding form có thể quy định `B8+rd id`. Trong đó:

```
B8+rd → opcode + mã register, là một opcode encoding form
		trong đó rd được mã hóa trong 3 bit thấp của opcode.
id    → immediate 32-bit
```

Khi decoder gặp `b8`, nó tra cứu quy tắc tương ứng và nhận ra rằng byte này thuộc form `B8+rd`, `imm32`, `b8` tương ứng với `B8 + 0`, nên register được chọn là `EAX`. Sau đó quy tắc của encoding cho biết instruction này còn cần một `imm32`. Do đó 4 byte tiếp theo được diễn giải là immediate:

```
b8 | 3c 00 00 00
│       │
│       └── imm32
│
└── opcode/form
```

Vì x86 sử dụng little-endian cho immediate nhiều byte:

```
3c 00 00 00
        ↓
0x0000003c
```

Kết quả là `mov eax, 0x3c`. Điểm quan trọng nằm ở đây:

```
b8
│
│ decode
▼
B8+rd, imm32
│
├── rd   → xác định register
│
└── imm32 → yêu cầu 4 byte tiếp theo
                    │
                    ▼
             3c 00 00 00
```

Tức là byte `3c` không tự nói rằng nó là immediate. Chính instruction form được xác định từ các byte phía trước quy định rằng những byte tiếp theo phải được diễn giải như `imm32`.

<sub>--đã hết phần giải thích--</sub>

---

</td>
</tr>
</table>
</details>

### 2.1. Opcode

Opcode là trường encoding xác định operation/instruction form. Trong x86-64, opcode thường xuất hiện sau các prefix nếu instruction có prefix. Nghĩa là mã nhị phân (hoặc mã hex) dùng để xác định phép toán mà CPU sẽ thực hiện. Bây giờ đơn giản, ta lấy lệnh hợp ngữ làm minh họa, bây giờ ta muốn thực hiện phép cộng với `32bit/6bit`, ta dùng lệnh `add` với hợp ngữ nhưng với opcode nó là `05`. Ta dựa vào đó so sánh như sau :

<div align="center">

| nhu cầu | hợp ngữ | opcode | giải thích lệnh opcode |
|:-|:-:|:-:|:-|
| cộng | `add` | `05` (32/16bits) | `05` là việc cộng accumulator, imm32 |
| trừ | `sub` | `2D id` hoặc `2B /r` | `2D id` là việc trừ giá trị tức thời, còn `2B /r` là trừ nội dung thanh ghi/bộ nhớ vào thanh ghi |
| ... | ... | ... | ... |

</div>

ta thấy, lệnh hợp ngữ khi thao tác các nhu cầu hay hành vi, phép toán của CPU thì điển hành sẽ là lệnh riêng của nó như `add,sub,imul,div,v.v..` còn opcode thì cũng y chang, nhưng cái lệnh của nó sâu hơn và chi tiết hơn hợp ngữ, ví dụ muốn cộng nhưng cộng bao nhiêu bit, muốn cộng `32/16bits` thì dùng `05`, còn muốn trừ thì trừ ở đâu, trừ gía trị gì, trừ nội dung hay trừ gía trị tức thời. Nói chung nếu hợp ngữ sâu hơn C, thì opcode sâu hơn hợp ngữ, thế thì hợp ngữ cũng đâu phải là ác mộng lắm đâu

### 2.2. Operand

Operand là các đối tượng mà instruction thao tác lên, chẳng hạn register, memory operand hoặc immediate. Trong machine-code encoding, thông tin mô tả operand có thể được mã hóa thông qua `ModR/M`, `SIB`, `immediate`, `displacement` và các trường khác, vì vậy operand không nhất thiết tương ứng với một vùng byte riêng nằm ngay sau opcode. Dựa vào đó, ta thấy một lệnh máy thường có cấu trúc :

```
[ Opcode ] + [ Operand 1 ] + [ Operand 2 ] + … (có thể có thêm)
```

và lấy minh họa hợp ngữ, nếu `add` là cộng, CPU hiểu à nó là cộng nhưng nó cần biết thực hiện phép cộng ở phần nào với phần nào, bây giờ ta cập nhật lệnh hợp ngữ thành `add eax, 1` lúc này CPU hiểu `à cộng 1 vào thanh ghi eax`. Thì operand cũng y thế, ví dụ `05` là opcode cộng `32/16bits` thì cần phải cung cấp cộng vào ở các mục tiêu gì, lúc này cập nhật thêm operand để cộng 1 vào thanh ghi `05 01 00 00 00`

Ta lưu ý số bit, thanh ghi rax là 64bits hoàn toàn cao so với `32bits`, ở byte `05 01 00 00 00` chỉ thực hiện tương đương lệnh `add eax, 1` thôi, thực tế ở đây khi dùng opcode `05` là nó đã thêm cái thanh ghi eax rồi, nên `01 00 00 00` là gía trị 1, theo little endian.

<details>
	<summary><b>[Câu hỏi]</b> Vì sao thay vì để riêng 01, thì lại thêm các byte 00 00 00 phía sau?</summary>
<table>
<tr>
<td>

---

Đây đơn giản là lắp đầy cái phần trống của một lệnh với những byte có ý nghĩa, nếu như một `short -> int` qua compiler nó cũng sẽ dùng zero extension hoặc sign extension để lắp đầy phần dư từ `2byte -> 4byte`, thì cái này cũng vậy. Nói cho rõ thì byte `05` là opcode/encoding form của `ADD EAX, imm32`, nó bắt buộc có một trường immediate 32-bit, tức là sau `05` phải có đúng 4 byte immediate. Ta thấy `01` là 1 byte, nếu chỉ y nguyên thế này thì `3 byte còn lại tính sao?`, nên hệ thống sẽ thực hiện thêm các byte điển hình 3 null byte như trên `00 00 00` để lắp đầy 32bits.

- **Vì sao lại là null byte?:** Đây ko phải là quy tắc cứng nhắc gì, nó chỉ đơn giản đảm bảo giá trị ban đầu ko bị thay đổi sau khi lắp đầy, ở đây `01 00 00 00` là 32bit/4byte đủ, nhưng hệ thống sẽ đọc theo little endianess (byte có trọng số thấp nhất sẽ đứng trước) như sau `01 00 00 00 -> 00 00 00 01`, giá trị sẽ là `1` nhưng vẫn giữ nguyên đủ 32bits/4byte

  **Lưu ý:** Chúng ta ko nên gọi việc thêm các byte vào như thế là padding, việc gọi như thế là sai. Nó là thêm byte có ý nghĩa mặc dù thêm các null byte (`00`) như đợt vừa rồi thì chả có ý nghĩa gì, nhưng nếu nói `ý nghĩa của nó là lắp đầy độ rộng thì chả phải padding?` thì ta cho **ví dụ** nếu thử đổi `01 00 00 00 -> 01 76 54 32` thì little endianess `01 76 54 32 -> 32 54 76 01` thì nó là các byte có ý nghĩa

  nếu việc nói này là padding thì sai hoàn toàn bản chất padding, vì nó chỉ giữ nguyên một giá trị, còn nhìn ở đây mà xem nó lộn xộn nếu mà nói padding theo bản chất của nó thì sẽ thành ra sai kết quả mất. Đó là lý do vì sao ko nên nói padding trong trường hợp này, dù là các null byte thì phải diễn đạt nó là các byte có ý nghĩa trong việc lắp đầy độ rộng toán hạng

<sub>--đã hết phần giải thích--</sub>

---

</td>
</tr>
</table>
</details>

### 2.3. Register Encoding

Register Encoding là cách mà x86 biến tên thanh ghi như `EAX, ECX, R8, RDI, v..v..` thành các bit/field nằm trong instruction encoding. Điểm quan trọng là CPU không lưu chữ EAX trong instruction. **Ví dụ** cho `mov eax, 1` CPU ko lưu nó như `MOV EAX, 1` mà nó lưu `B8 + register_code | imm32`, trong đó `eax` có register code là `000` và `B8 + 000 = B8` nên `B8 01 00 00 00`. Dựa vào đó ta có bảng `REG values` như sau :

<div align="center">

| REG values | 8bits | 16bits | 32bits |
|-|-|-|-|
| 000 | al | ax | eax |
| 001 | cl | cx | ecx |
| 010 | dl | dx | edx |
| 011 | bl | bx | ebx |
| 100 | ah | sp | esp |
| 101 | ch | bp | ebp |
| 110 | dh | si | esi |
| 111 | bh | di | edi |

</div>

> [!IMPORTANT]
> Register code không phải địa chỉ của register. mã định danh thanh ghi trong encoding, không phải `edi = địa chỉ a`, `eax = địa chỉ b`, mà nó kiểu `edi = mã số` và opcode cộng mã số đó để thực hiện lệnh với thanh ghi có mã số đó
>
> Với các thanh ghi 8-bit mã `100–111`, ý nghĩa phụ thuộc vào việc instruction có REX prefix hay không, không có REX thì tương ứng `AH/CH/DH/BH` có REX thì tương ứng `SPL/BPL/SIL/DIL`.

Ngoài các encode cộng các mã thanh ghi vào opcode, còn có các chế độ mà Intel định nghĩa một encoding form kiểu `B8+rd ib/iw/id/iq`, trong đó `rd` đại diện cho mã thanh ghi đích. Bây giờ cho các ví dụ :

```
mov ecx, 1 -> B8 + 001 = B9 => B9 01 00 00 00
mov edx, 1 -> B8 + 010 = BA => BA 01 00 00 00
mov ebx, 1 -> B8 + 011 = BB => BB 01 00 00 00
mov esp, 1 -> B8 + 100 = BC => BC 01 00 00 00
mov ebp, 1 -> B8 + 101 = BD => BD 01 00 00 00
mov esi, 1 -> B8 + 110 = BE => BE 01 00 00 00
mov edi, 1 -> B8 + 111 = BF => BF 01 00 00 00
```

Nhưng x86 không phải lúc nào cũng encode register trong opcode lý giải chi tiết tại chương [4. ModR/M Byte](#4-modrm-byte). Cho **Ví dụ**, `mov eax, ebx` lệnh này không dùng kiểu `B8+rd` như `mov eax, imm32`. Nó có dạng `opcode | ModR/M` và encoding là `89 D8` và ta chuyển `D8` thành binary là `11011000`. ModR/M có cấu trúc như sau:

```
┌──────┬───────┬───────┐
│ mod  │ reg   │ r/m   │
│  2b  │  3b   │  3b   │
└──────┴───────┴───────┘
```

với `11011000` ta có :

```
11 | 011 | 000
│     │     │
│     │     └── r/m = 000 → EAX
│     └──────── reg = 011 → EBX
└────────────── mod = 11 → register
```

vì thế `89 D8` được encode thành `mov eax, ebx`. Ở đây register encoding nằm trong `ModR/M`, chứ không nằm trực tiếp trong opcode. `ModR/M` sẽ đươc nói rõ ở chương dưới

- **Vậy khi nào register code được mã hóa trong opcode, và khi nào được mã hóa trong ModR/M?:** Vị trí mã hóa thanh ghi phụ thuộc vào encoding form mà ISA x86 định nghĩa cho instruction, không chỉ phụ thuộc vào hành vi của lệnh. **Ví dụ**, với `mov eax, 1`, instruction sử dụng encoding form `B8+rd id`. Trong dạng này, mã thanh ghi đích được gắn vào opcode, với `EAX`, register code là `000`, vì vậy opcode là `B8`. Immediate 32-bit có giá trị `1` được mã hóa thành `01 00 00 00`, tạo thành instruction `B8 01 00 00 00`.

  Ngược lại, với `mov eax, ebx`, instruction sử dụng opcode `89` cùng một byte ModR/M. Trường `reg` biểu diễn thanh ghi nguồn `EBX`, còn trường `r/m` biểu diễn thanh ghi đích `EAX`. Vì vậy, encoding là `89 D8`. Không phải mọi instruction có immediate đều mã hóa register code trong opcode, cũng không phải mọi instruction thao tác giữa hai thanh ghi đều bắt buộc dùng ModR/M theo cùng một cách. Chẳng hạn, `add eax, 1` có thể dùng opcode `05` với thanh ghi tích lũy `EAX` được ngầm định, trong khi `add ecx, 1` có thể dùng opcode `83` và ModR/M để biểu diễn toán hạng đích `ECX`.

  Do đó, khi reverse engineering, cần xác định encoding form của instruction trước, sau đó mới phân tích cách các trường opcode, ModR/M, SIB, displacement và immediate biểu diễn toán hạng cụ thể.


### 2.4. Immediate Value

Immediate value (giá trị tức thời) là một giá trị hằng được mã hóa trực tiếp trong instruction, thay vì được lấy từ một thanh ghi hoặc đọc từ một địa chỉ bộ nhớ do toán hạng chỉ định. **Ví dụ** xét instruction sau `mov eax,1`, ý nghĩa này là gắn giá trị `1` vào thanh ghi `eax`, trong đó `1` là giá trị tức thời (immediate values) và `eax` là thanh ghi đích.

Đối với các instruction ecode như `b8 01 00 00 00`, ta thấy và có thể phân tích `b8` là opcode của encoding form `MOV r32, imm32` khi mã thanh ghi đích là `EAX`, dạng tổng quát được mô tả là `B8+rd id`, trong đó `rd` mã hóa thanh ghi đích và `01 00 00 00` là Immediate 32-bit có giá trị số học là 1, được mã hóa theo little-endian

Điều này cho thấy CPU không lưu chuỗi văn bản `mov eax, 1` trong instruction. Thay vào đó, instruction được biểu diễn bằng các byte mã máy, trong đó immediate value được mã hóa thành một trường dữ liệu của instruction. Tuy nhiên, immediate ko phải là thanh ghi hay bộ nhớ cao siêu gì, ta cần phân biệt rõ ba loại toán hạng sau :

```asm
mov eax, 1 
mov eax, ebx 
mov eax, DWORD PTR [rbx]
```

Trong đó :

- `mov eax, 1`: có loại toán hạng nguồn là immediate, có tác dụng là gán giá trị `1` vào thanh ghi `eax`.
- `mov eax, ebx`: có loại toán hạng nguồn là register, có tác dụng là lấy giá trị hiện tại của thanh ghi `ebx` gán vào thanh ghi `eax`
- `mov eax, DWORD PTR [rbx]`: có loại toán hạng nguồn là memory, có tác dụng là đọc 4 byte từ địa chỉ bộ nhớ được chứa trong `RBX` và gán vào thanh ghi `eax`

Ta thấy, trong trường hợp đầu tiên, giá trị 1 được chứa trong encoding của instruction. Trong trường hợp thứ hai, giá trị nguồn được lấy từ thanh ghi. Trong trường hợp thứ ba, CPU truy cập bộ nhớ để lấy dữ liệu. Vì vậy, immediate value là một phần của encoding, chứ bản thân nó không phải tên thanh ghi hay địa chỉ bộ nhớ.

Immediate value có thể được mã hóa bằng các kích thước khác nhau, tùy thuộc vào encoding form và instruction cụ thể. Các kích thước thường gặp gồm `8 bit`, `16 bit`, `32 bit` và trong một số encoding form là `64 bit`. **Ví dụ** `mov eax, 1` ta biết instruction encoding của nó là `b8 01 00 00 00` immediate `01 00 00 00` được mã hóa bằng `32bits` nghĩa giá trị số học của trường này là `0x00000001`, do x86 sử dụng little-endian cho các trường số nhiều byte, byte ít quan trọng nhất được lưu trước

Một **ví dụ khác**, ta cho `add ecx, 1` có thể được mã hóa thành `83 C1 01`, trong encoding của form này `83` là opcode, `C1` là byte `ModR/M`, xác định toán hạng thanh ghi và phép toán theo encoding form, `01` là immediate `8bits`. Ta thấy cùng giá trị là `1` gán vào thanh ghi nhưng lệnh `mov eax, 1` là `32bits` nhưng với `add ecx, 1` nó lại là `8bits`, chênh lệch khá lớn, như vậy cùng một giá trị số học 1 có thể được biểu diễn bằng số lượng byte khác nhau tùy theo encoding form. Không thể xác định kích thước immediate chỉ dựa vào giá trị số học của nó.

Một số instruction encoding sử dụng immediate có kích thước nhỏ hơn toán hạng đích. Khi đó, kiến trúc x86 có thể quy định sign extension mở rộng dấu để chuyển immediate sang kích thước cần thiết. **Ví dụ** trong `64bits` ta có `add rax, -1`, ta thấy một encoding có thể sử dụng dạng `REX.W + 83 /0 ib`, trong đó immediate là `8bits`. Giá trị `-1` được biểu diễn ở dạng bù hai `8bits` là `FF`, khi sign extension lên `64bits` giá trị sẽ thành `0xFFFFFFFFFFFFFFFF`. Ta cần phân biệt:

- **Immediate field:** các byte thực sự có trong instruction encoding.
- **Sign extension:** cách CPU mở rộng giá trị immediate theo quy tắc của instruction.
- **Zero extension:** mở rộng bằng các bit 0; chỉ áp dụng khi ngữ nghĩa của instruction quy định như vậy.

Tuy nhiên không phải mọi immediate đều được sign-extend. Cách diễn giải phụ thuộc vào instruction và encoding form cụ thể.

### 2.5. Displacement

Trong x86-64, displacement là một giá trị được mã hóa trực tiếp trong instruction, dùng làm độ lệch khi tính địa chỉ hiệu dụng của toán hạng bộ nhớ. Nó thường được cộng với địa chỉ cơ sở (base) hoặc địa chỉ chỉ số (index) đã được nhân với hệ số (scale).

<details>
	<summary><b>[Câu hỏi]</b> Địa chỉ cơ sở, địa chỉ chỉ số, hệ số là gì?</summary>
<table>
<tr>
<td>

---

Trong x86-64, base, index và scale là ba thành phần có thể phối hợp để tính địa chỉ bộ nhớ hiệu dụng (effective address). Ta sẽ gặp chúng khi giải mã byte SIB trong các instruction như `mov eax, [rbx + rcx*4 + 8]`. Trong đó :
- **Base:** Hay còn được gọi là thanh ghi cơ sở dùng để chứa địa chỉ nền để tính địa chỉ cần truy cập. Ví dụ, `RBX = 0x1000`.
- **Index:** Hay còn được gọi là thanh ghi chỉ số dùng để chứa giá trị chỉ số hoặc độ lệch dùng để xác định vị trí dữ liệu. Ví dụ, `RCX = 3`.
- **Scale:** Hay còn được gọi là hệ số nhân dùng để nhân giá trị index với `1`, `2`, `4` hoặc `8` trước khi cộng vào địa chỉ cơ sở. Các hệ số này thuận tiện khi truy cập phần tử có kích thước tương ứng.

Ngoài ba thành phần đó, địa chỉ còn có thể cộng thêm displacement, là một hằng số được mã hóa trực tiếp trong instruction. Từ đó suy ra công thức tương ứng là `EA = Base + Index x Scale + Displacement` và `EA` là effective address công thức này sẽ chi tiết tại phần [5. SIB Byte](#5-sib-byte), tức địa chỉ hiệu dụng được tính ra. Không phải instruction nào cũng cần cả bốn thành phần. Ví dụ cụ thể với `mov eax, [rbx + rcx*4 + 8]`

Giả sử hai thanh ghi `rbx` và `rcx` có giá trị lần lượt là `0x1000` và `3` và xét instruction `mov eax, DWORD PTR [rbx + rcx*4 + 8]`, lúc này quy tắc sẽ tính địa chỉ là như sau:

<p align="center">
	<img src="image/image7.png" alt="tính địa chỉ">
</p>

**Chú ý:** `RCX = 3` là giá trị chỉ số, không phải địa chỉ `0x3`. Sau khi nhân với scale `4`, nó tạo độ lệch `12` byte. Đó là lý do scale hữu ích khi truy cập mảng.

- **Vì sao cần scale?:** Giả sử một mảng gồm các phần tử 32-bit, mỗi phần tử chiếm 4 byte:

  <p align="center">
    <img src="image/image8.png" alt="sơ đồ mảng 4byte">
  </p>

  Để truy cập `A[3]` chương trình sẽ thực hiện `EA = 0x1000 + 3 x 4 = 0x100C` nhưng hợp ngữ lại có cách biểu diễn bằng `mov eax, DWORD PTR [rbx + rcx*4]` với `RBX = 0x1000`, `RCX = 3`. Nếu phần tử là 64-bit, mỗi phần tử chiếm 8 byte, nên scale có thể là 8. Với phần tử 8-bit, scale thường là 1

<sub>--đã hết phần giải thích--</sub>

---

</td>
</tr>
</table>
</details>

> [!IMPORTANT]
> displacement không phải bản thân địa chỉ bộ nhớ. Nó là một thành phần có thể được CPU dùng để tính địa chỉ cần truy cập.

**Ví dụ** xét instruction `mov eax, DWORD PTR [rbx + 8]` ý nghĩa của nó là đọc 4 byte từ địa chỉ `RBX + 8`, sau đó ghi dữ liệu vào `EAX`. Bây giờ giả sử ta cho địa chỉ cơ sở là `0x1000` thì `+8` là displacement, suy ra ta có `0x1000 + 8 = 0x1008` và kết quả địa chỉ `0x1008` chính là địa chỉ mà CPU truy cập để lấy 4byte trong đó

- **Displacement xuất hiện như thế nào trong machine code?:** Nó sẽ thành thế này `8B 43 08` và instruction encode này là của `mov eax, DWORD PTR [rbx + 8]`. Bây giờ ta bật GDB lên thực chiến luôn, vì cái câu hỏi này sẽ dễ hiểu hơn khi ta thực chiến. Ta cho code hợp ngữ sau:

  ```asm
   section .text
	global _start
  _start:
	  mov eax, dword [rbx + 8]
	  mov eax, 60
	  mov rdi, 1
	  syscall
  ```

  > nasm -f elf64 asm.asm ; ld asm.o -o asm ; gdb -q ./asm

  khi vào gdb ta ấn start và ta `disas /r 0x401000` là vaddr của `_start` ko chắc đó có phải là vaddr gốc ko vì địa chỉ `_start` phụ thuộc vào linker và PIE. Với binary không PIE (như ld mặc định cũ) có thể là `0x401000`, nhưng hiện nay hầu hết binary là PIE thì địa chỉ sẽ là kiểu `0x555555554000 + offset`:

  <p align="center">
  	<img src="image/image1.png"/>
  </p>

  ta thấy, với gdb instruction encode là `8B 43 08`, trong đó :

  - `8B` : là opcode ý nghĩa của nó là xác định dạng lệnh `MOV r32, r/m32` nghĩa là đưa giá trị 32-bit từ thanh ghi hoặc toán hạng bộ nhớ vào thanh ghi 32-bit.
  - `43` : đây là [modR/M byte](#4-modrm-byte), cụ thể `43 = 01000011` khi dịch ra nhị phân :
    - `mod = 01`: toán hạng bộ nhớ sử dụng displacement 8-bit.
    - `reg = 000`: thanh ghi đích là `eax`
    - `r/m = 011`: thanh ghi cơ sở `RBX` trong dạng địa chỉ này
  - `08` : đây là displacement 8bit, giá trị `08` trong hệ hex là `8` trong hệ thập phân. CPU sử dụng nó làm độ lệch cộng với địa chỉ cơ sở RBX.

> [!IMPORTANT]
> **Điểm quan trọng:** 08 không phải địa chỉ bộ nhớ hoàn chỉnh. Nó chỉ là độ lệch được mã hóa trong instruction. Với assembly representation của instruction encoding trên là `mov eax, DWORD PTR [rbx + 0x8]`, đây là cách displacement xuất hiện như thế nào trong machine code, nó chỉ là byte `8B 43 08`.
- **Phân biệt giữa immediate byte và displacement:** Đây là phần quan trọng, vì nếu ko biết phân biệt được thì dễ chết trong biển rừng machine code vì nó ko có function, variable, bây giờ nhìn ảnh :

  <p align="center">
  	<img src="image/image2.png"/>
  </p>

  ta thấy, displacement và immediate khác nhau khá nhiều. Ở đây, ta soi byte displacement `8b 43 08` và byte immediate `b8 3c 00 00 00` và `bf 01 00 00 00`, ta thấy các byte immediate thường có `xx 3c 00 00 00` và `xx 01 00 00 00` (lấy từ ảnh) vì nó chỉ transmit gía trị tức thời như số vào trong thanh ghi ngoài ra còn có `8bit`,`16bit`,`32bit`, tùy instruction. Còn byte displacement `8b 43 08` nó dùng truy cập bộ nhớ ,nhưng `displacement = 8` và cpu sử dụng nó làm độ lệch cộng với địa chỉ cơ sở `RBX`.

> [!IMPORTANT]
> Displacement và Immediate hoàn toàn khác nhau, displacement là giá trị để làm độ lệch khi truy cập bộ nhớ còn immediate là giá trị gán trực tiếp vào một thanh ghi, hay cái gì đó

### 2.6. Instruction Length

Instruction length là độ dài của một instruction sau khi được mã hóa thành machine code, được tính bằng byte. Trong kiến trúc x86-64, các instruction có độ dài thay đổi (variable-length instruction encoding). Một instruction có thể chỉ dài 1 byte, nhưng cũng có thể dài nhiều byte tùy vào opcode, prefix, ModR/M, SIB, displacement và immediate mà instruction đó sử dụng.

Đối với x86-64, độ dài tối đa của một instruction là 15 byte. Nếu quá trình giải mã gặp một instruction cần nhiều hơn 15 byte, nó không được xem là một instruction hợp lệ theo quy tắc mã hóa x86-64. Ví dụ các độ dài của instruction :

<div align="center">

| Instruction | machine code | instruction length |
|-|-|-|
| `mov eax, 1` | `B8 01 00 00 00` | 5byte |
| `nop` | `90` | 1byte |
| `mov eax, [rbx + 8]` | `8B 43 08` | 3byte |

</div>

Lý do độ dài khác nhau là mỗi instruction sử dụng dạng mã hóa khác nhau. `nop` chỉ cần một byte. `mov eax, 1` cần opcode và `immediate 32-bit`. Trong khi đó, `mov eax, [rbx + 8]` cần opcode, `ModR/M` và `displacement 8-bit`. Vì vậy, không thể xác định độ dài instruction chỉ bằng cách nhìn vào tên lệnh assembly hoặc giá trị toán hạng. Ta phải dựa vào encoding cụ thể của instruction.

<details>
	<summary><b>[Câu hỏi]</b> vì sao reverse engineering cần phải hiểu instruction length?</summary>
<table>
<tr>
<td>

---

Khi phân tích một binary, ta thường nhìn thấy một dãy byte liên tục trong vùng mã thực thi. Những byte này không tự mang theo ranh giới instruction theo cách mà con người có thể nhìn thấy trực tiếp. Disassembler phải giải mã dãy byte theo kiến trúc instruction set để xác định instruction bắt đầu ở đâu, kết thúc ở đâu và instruction tiếp theo nằm tại địa chỉ nào.

**Ví dụ**, nếu một instruction dài 5 byte nhưng bị diễn giải nhầm thành instruction dài 3 byte, các byte còn lại có thể bị giải mã thành những instruction khác. Điều này có thể dẫn đến một luồng disassembly khác với luồng mà ta dự định phân tích. Vì vậy, hiểu Instruction Length giúp ta đọc kết quả từ GDB, objdump hoặc Ghidra chính xác hơn, đồng thời hiểu được một phần cơ sở của các kỹ thuật như linear disassembly, recursive traversal và anti-disassembly.

<sub>--đã hết phần giải thích--</sub>

---

</td>
</tr>
</table>
</details>

## 3. REX Prefix
### 3.1. REX Prefix là gì?

Trong x86-64, REX Prefix là một byte prefix đứng trước opcode, được dùng để mở rộng khả năng mã hóa instruction, đặc biệt là hỗ trợ thanh ghi `64-bit`, thanh ghi tổng quát `R8–R15` và các toán hạng `8-bit` bổ sung như `SPL`, `BPL`, `SIL`, `DIL`. Để biết Rex prefix xuất hiện thế nào, ta xét hai instruction :

```asm
mov eax, 1 ; B8 01 00 00 00
mov rax, 1 ; 48 C7 C0 01 00 00 00
```

Ở ví dụ thứ hai, `48` là REX prefix (`REX.W = 1`), báo rằng instruction sử dụng kích thước toán hạng `64-bit` trong encoding này. Immediate vẫn là `32-bit` và được sign-extend thành `64-bit` khi thực thi.

- **Lưu ý:** `mov rax, 1` có nhiều encoding hợp lệ. **Ví dụ** trên dùng dạng `48 C7 C0 01 00 00 00`, một dạng khác dùng `48 B8 01 00 00 00 00 00 00 00`, với immediate `64-bit`. Vì vậy, không nên kết luận rằng mọi instruction `mov rax, 1` đều có cùng machine code.

### 3.2. Cấu trúc byte REX

Rex prefix có cấu trúc như sau

<p align="center">
	<img src="image/image3.png" alt="ảnh cấu trúc rex prefix">
</p>

**Trong đó:**
- `W`: Thường chọn kích thước toán hạng `64-bit` khi bằng `1`, tùy instruction.
- `R`: Mở rộng trường `reg` của `ModR/M`, cho phép mã hóa thêm thanh ghi.
- `X`: Mở rộng trường `index` của `SIB`.
- `B`: Mở rộng trường `base` của `SIB` hoặc trường `r/m` của `ModR/M`, cũng có thể mở rộng thanh ghi được mã hóa trong opcode.

ví dụ với `48`:

```
48 = 0100 1 0 0 0
       |  | | | |
     0100 W R X B
          | | | |
          1 0 0 0
```

Ta thấy, lấy 4bit cho trường `fixed bit` và 4bit còn lại cho các trường `WRXB`, ở đây byte `48` tương ứng với `REX.W = 1`, còn `R`, `X`, `B` đều bằng `0`. Lưu ý, `48` là byte lầ machine code, chứ ko phải là số nguyên hệ cơ số 2

- **REX Prefix giúp mở rộng thanh ghi như thế nào?:**
  - **Trường hợp A. Chọn toán hạng 64-bit:** Xét các đoạn code assembly như sau:

    ```asm
	    mov eax, ebx
	    mov rax, rbx
    ```

    một instruction điển hình cho từng lệnh ta có :

    ```asm
	    mov eax, ebx ; 89 D8
	    mov rax, rbx ; 48 89 D8
    ```

    ta thấy, với lệnh đầu tiên là `mov eax, ebx` có instruction byte `89 D8` và lệnh này 32bit, nhưng với lệnh `mov rax, rbx` ta lại thấy nó có `48 89 D8` và byte `48` là byte `REX.W = 1` mà chúng ta vừa phân tích ở trên, nó chọn toán hạng 64bit cho dạng `MOV` này

  - **Trường hợp B. Sử dụng thanh ghi R8–R15:** Xét các đoạn code assembly như sau:

    ```asm
	    mov r8d, eax ; 41 89 C0
    ```

    Ở đây, `41 = 01000001`, tức `REX.B = 1`. Bit mở rộng cho phép mã hóa `R8D` thay vì chỉ các thanh ghi thuộc nhóm `EAX–EDI`

    - **Vậy nếu là REX.W = 1, thì với hệ thống hay cận cảnh Debugger nó thực sự được kéo rộng ra 64bit cao hơn như thế nào?:** nó không tự kéo giãn dữ liệu bên trong file hay CPU. Nó làm thay đổi cách chương trình/CPU thực thi instruction, từ đó chọn phép toán có độ rộng toán hạng 64 bit thay vì 32 bit. Ta cho instruction encode byte `89 D8` và `48 89 D8` :

      <p align="center">
	    <img src="image/image4.png" alt="ảnh cấu trúc rex prefix">
	  </p>

      Hai instruction có cùng opcode `89` và cùng byte `ModR/M D8`. Khác biệt là instruction thứ hai có thêm byte `48`, tức `REX.W = 1`. Debbuger không nhìn thấy chuỗi ký tự `mov rax, rbx` như con người. Nó đọc byte instruction, giải mã các trường mã hóa, rồi xác định độ rộng toán hạng mà instruction yêu cầu. Từ đây suy ra debugger nó ko đọc từng byte, mà nó đọc một cụm byte, length hay chiều dài rộng byte tùy thuộc vào instruction và cũng đồng nghĩa ta có thể suy ra là CPU đã được thay đổi cách thực thi sang 64bit
	- **Nhưng vấn đề là sao Debugger nó có thể biết để đọc một cụm byte?:** CPU không cần biết trước toàn bộ độ dài. Nó sử dụng cơ chế nhận diện và giải mã tuần tự các trường của instruction để xác định ranh giới instruction. Trong CPU hiện đại, một số bước có thể diễn ra song song hoặc được tối ưu hóa, nhưng về mặt kiến trúc, ta có thể mô hình hóa quá trình như sau vì CPU không thể mặc định mỗi instruction có độ dài cố định, xét ba instruction :

      ```asm
	      nop                 ; 90 -> 1byte
	      mov eax, ebx        ; 89 D8 -> 2byte
	      mov rax, rbx        ; 48 89 D8 -> 3byte
      ```

      Nếu CPU luôn đọc đúng một byte cho mỗi instruction, nó không thể giải mã đầy đủ `89 D8`. Ngược lại, nếu luôn đọc ba byte, instruction `nop` sẽ bị đọc lẫn với byte thuộc instruction tiếp theo. Vì vậy, x86-64 sử dụng instruction encoding có độ dài biến đổi. Một instruction có thể dài từ 1 đến 15 byte trong chế độ 64 bit.
    - **Debugger nhận diện cấu trúc instruction như thế nào?:** để hiểu thì ta mô phỏng quá trình của nó như sau, với instruction encode byte `48 89 D8`.

	  <div align="center">

      | Rex | Opcode | ModR/M |
	  |-|-|-|
	  | 48 | 89 | D8 |

	  </div>

       Bước đầu tiên là nhận diện prefix, CPU nhận ra byte `48` là REX prefix trong chế độ 64 bit. Trường `W=1` yêu cầu dạng toán hạng 64 bit cho instruction này. Bước 2 là giải mã opcode, Opcode `89` xác định dạng `MOV r/m, r` nghĩa là sao chép dữ liệu từ toán hạng thanh ghi nguồn sang toán hạng đích `r/m`. Bước 3 là giải mã [ModR/M](#4-modrm-byte), byte `D8` có giá trị nhị phân `11011000`:

	  <div align="center">

	  | mod | reg | r/m |
	  |-|-|-|
	  | 11 | 011 | 000 |

	  </div>

	    `mod=11` cho biết toán hạng `r/m` là thanh ghi, `reg=011` chỉ `RBX/EBX` tùy độ rộng, còn `r/m=000` chỉ `RAX/EAX` tùy độ rộng. Kết hợp với `REX.W=1`, instruction được giải mã thành `mov rax, rbx`. Lưu ý rằng đây là mô hình giải thích logic giải mã. Nó không khẳng định CPU phải xử lý từng trường bằng các bước tuần tự tách biệt theo đúng thứ tự trên trong phần cứng.

    - **Nhưng Debbuger biết khi nào instruction kết thúc bằng cách nào?:** Instruction x86-64 không có một byte đánh dấu kết thúc chung như `END`. Thay vào đó, cấu trúc mã hóa của instruction quy định trường nào xuất hiện và trường đó dài bao nhiêu. Bộ giải mã xác định các trường bắt buộc dựa trên prefix và opcode. **Ví dụ** `90` là `NOP` và `NOP` được mã hóa bằng một byte, nên instruction kết thúc ngay sau byte đó. Tiếp tục, `89 D8` là dạng `MOV r/m32, r32` cần opcode `89` và byte ModR/M `D8`. Không có trường displacement hoặc immediate trong encoding này, nên instruction dài 2 byte.
> [!IMPORTANT]
> Trong mã hóa x86, việc có REX prefix còn ảnh hưởng đến cách diễn giải một số mã thanh ghi 8-bit:
> - **Không có REX:** mã `100–111` có thể chỉ `AH`, `CH`, `DH`, `BH`.
> - **Có REX:** các mã tương ứng chỉ `SPL`, `BPL`, `SIL`, `DIL`.
>
> Chúng ta gọi cách thức biên dịch sang mã hợp ngữ là do debugger/decompiler thực hiện, thực chất các công cụ như debugger/decompiler nó mới quan trọng và cực đoan hóa các cái instruction length, đọc đâu, in đâu, hay rex prefix nhiêu đó, để cho ra hợp ngữ kết quả chính xác nhất. Nhưng với CPU thực tế, nó ko biết độ dài instruction là gì, nó cũng ko biết instruction là sao luôn, nó chỉ đọc các bit `0` và `1` từ đầu đến cuối và thực thi mù quáng thôi, còn cách nó thực thi thế nào tùy vào bit `0` và `1` biễu diễn theo quy định của cấu trúc ISA. Học program encode là để ta hiểu bit `0` và `1` nó sẽ cho CPU thực thi gì, làm hành vi gì và góp phần hiểu cơ chế của debugger

REX Prefix có mối liên hệ với Instruction Length, REX prefix chiếm đúng 1 byte. Nếu một instruction cần REX prefix, byte này là một phần của instruction encoding và làm tổng độ dài tăng thêm một byte so với cùng dạng encoding không có prefix, nếu các thành phần còn lại giữ nguyên. **Ví dụ :**

```asm
mov eax, ebx  ; 89 D8     -> 2 byte
mov rax, rbx  ; 48 89 D8  -> 3 byte
```

Đây cũng là lý do khi dump machine code, ta không nên mặc định rằng byte đầu tiên luôn là opcode. Nó có thể là một prefix như REX, phải giải mã theo cấu trúc instruction của x86-64. Tóm lại là REX Prefix không phải instruction độc lập. Nó là một byte bổ sung cho phép encoding x86-64 biểu diễn thêm thông tin về kích thước toán hạng và các thanh ghi mở rộng.

### 3.3. Các nhóm của Prefix ngoài Rex

Vừa rồi, ta hiểu rex prefix nhưng rex chỉ là một phần của prefix, thực chất prefix là khái niệm rộng còn nhiều phần tử gộp nên nó. Các nhóm phần tử gồm `Lock`, `REP/REPNE`, `Operand-size override`, `Address-size override`, `Segment override`, `REX` từ đó ta lập thành một bảng như sau :

<div align="center">

| Nhóm |	Byte tiêu biểu |	Chức năng |
|:-|:-|:-|
| Lock |	`F0`	| Yêu cầu ngữ nghĩa khóa cho các instruction hỗ trợ |
| REP / REPNE |	`F3`, `F2` |	Lặp hoặc thay đổi ngữ nghĩa của một số instruction |
| Operand-size override |	`66` |	Thay đổi kích thước toán hạng trong các trường hợp được quy định |
| Address-size override	| `67` |	Thay đổi kích thước địa chỉ |
| Segment override |	`2E`, `36`, `3E`, `26`, `64`, `65` |	Chọn segment override trong những trường hợp áp dụng |
| REX |	`40–4F` |	Mở rộng thanh ghi và điều khiển kích thước toán hạng 64-bit |

</div>

Điểm khác biệt chính là REX có cấu trúc bit riêng để mở rộng encoding, chứ không chỉ là một byte báo thay đổi chung. Bây giờ chúng ta tìm hiểu chi tiết từng nhóm một: 

- **nhóm Lock prefix:** nhóm `lock` dùng để yêu cầu một thao tác đọc–sửa–ghi trên bộ nhớ được thực hiện theo cơ chế atomic, tức là các luồng CPU khác không thể chen vào giữa thao tác đó theo cách làm hỏng tính nguyên tử của phép cập nhật. Nhưng LOCK không dùng được với mọi instruction. Nó chỉ hợp lệ với những dạng instruction hỗ trợ ngữ nghĩa khóa theo kiến trúc x86.

  **Ví dụ:** cho `lock add`. Giả sử một biến `counter` nằm trong bộ nhớ và hai thread cùng tăng nó. Không có atomicity, thao tác tăng có thể tương đương với ba bước:
  - 1.Đọc giá trị `counter` từ bộ nhớ.
  - 2.Cộng `1`.
  - 3.Ghi kết quả về bộ nhớ.
  
  Nếu hai thread cùng đọc giá trị `10` trước khi bên nào ghi kết quả, cả hai có thể ghi `11`. Một lần tăng bị mất. Với `LOCK ADD`, thao tác cộng trên toán hạng bộ nhớ được thực hiện nguyên tử theo các quy tắc của kiến trúc `lock add dword [counter], 1`. Trong NASM, đây là cú pháp minh họa cho một phép cộng atomic vào biến bộ nhớ `counter`.

  - **LOCK hoạt động ở mức phần cứng thế nào?:** Trên CPU hiện đại, LOCK không đơn giản có nghĩa là khóa toàn bộ bus hệ thống trong mọi trường hợp. Nếu vùng nhớ được khóa phù hợp với cơ chế coherence của cache, CPU thường có thể bảo đảm atomicity bằng cơ chế cache locking. Trong các trường hợp đặc biệt như truy cập bộ nhớ không phù hợp hoặc vượt ranh giới cache line, cơ chế mạnh hơn có thể cần thiết và chi phí có thể lớn hơn. Vì thế, cách hiểu đúng là LOCK yêu cầu ngữ nghĩa atomic theo kiến trúc, chứ không phải luôn khóa toàn bộ CPU hoặc toàn bộ bus.

  Ví dụ, `F0` đứng trước `MOV` thông thường không tự động biến nó thành một phép MOV atomic hợp lệ. Nếu instruction không hỗ trợ `LOCK`, CPU có thể phát sinh lỗi `#UD` (Invalid Opcode).

> [!NOTE]
> **Ghi nhớ:** `LOCK` là prefix điều khiển ngữ nghĩa atomic của một số instruction, `REX` là prefix mang các bit mở rộng encoding. Cả hai đều là prefix, nhưng chức năng hoàn toàn khác nhau.

- **nhóm REP / REPNE:** `REP` và `REPNE` là các prefix trong x86 dùng chủ yếu để lặp lại một số instruction xử lý chuỗi. Khác với `LOCK`, chúng không nhằm bảo đảm atomicity, khác với `REX`, chúng không dùng các bit W/R/X/B để mở rộng thanh ghi. Hai byte thường gặp là `F3` cho `REP`, `REPE` hoặc `REPZ`, tùy instruction và `F2` cho `REPNE` hoặc `REPNZ`, tùy instruction.
  Trong đó `REP` là lặp lại instruction và `REPNE` là lặp cho đến khi không còn thỏa điều kiện, ví dụ `REP` cho :

  ```asm
  cld
  mov ecx, 4
  mov esi, source
  mov edi, destination
  rep movsb
  ```

  `MOVSB` sao chép một byte từ địa chỉ `DS:RSI` sang `ES:RDI` trong chế độ 64-bit, với các quy tắc segment tương ứng. `REP MOVSB` lặp thao tác sao chép theo số lần được chỉ định bởi `RCX`. Với `RCX = 4`, CPU thực hiện tối đa bốn lần sao chép byte, cập nhật `RSI`, `RDI` và giảm `RCX` sau mỗi lần lặp. `CLD` đặt Direction Flag về `0` để các con trỏ tăng lên sau mỗi lần xử lý. Và encoding của `rep movsb` là `F3 A4` trong đó `A4` là opcode của `MOVSB` còn `F3` yêu cầu lặp thao tác theo quy tắc của instruction này.
  Ví dụ cho `REPNE` xét :

  ```asm
  cld
  mov ecx, 100
  mov edi, buffer
  xor eax, eax
  repne scasb
  ```

  `SCASB` so sánh giá trị trong `AL` với byte tại địa chỉ `ES:RDI`, đồng thời cập nhật các cờ trạng thái và con trỏ. `REPNE SCASB` lặp khi `RCX` chưa bằng 0 và `ZF = 0`, nghĩa là lần so sánh gần nhất chưa tìm thấy byte bằng `AL`. Trong ví dụ, `AL = 0`, nên đoạn mã tìm byte 0 trong vùng nhớ, tối đa 100 byte. Nó dừng khi tìm thấy byte bằng 0 hoặc khi hết số lần lặp. Encoding của `repne scasb` là `F2 AE` trong đó `F2` là `repne` và `AE` là `scasb`

Phân biệt `REP`, `REPE` và `REPNE` ta có bảng so sánh như sau :

<div align="center">

| Prefix / tên |	Điều kiện lặp |
|:-|:-|
| `REP`	 | Tiếp tục khi bộ đếm khác 0 |
| `REPE` / `REPZ` |	Tiếp tục khi bộ đếm khác 0 và `ZF = 1` |
| `REPNE` / `REPNZ` |	Tiếp tục khi bộ đếm khác 0 và `ZF = 0` |

</div>

`REPE` và `REPZ` là hai tên cho cùng một dạng prefix `F3`, `REPNE` và `REPNZ` tương ứng với `F2`.

> [!NOTE]
> **Điểm cần nhớ:** ý nghĩa chính xác phụ thuộc vào instruction. Với `MOVSB`, `F3` dùng để lặp sao chép, còn với `SCASB`, prefix có thể kết hợp điều kiện dựa trên `ZF`.

Tóm lại, `F0` (LOCK) liên quan đến atomicity, `F2`/`F3` (REP-family) liên quan đến việc lặp và điều kiện lặp của các instruction được hỗ trợ, còn REX (`40–4F`) liên quan đến mở rộng encoding trong x86-64.

## 4. ModR/M Byte
### 4.1. ModR/M là gì?

ModR/M byte là một byte trong instruction encoding của x86/x86-64, dùng để xác định cách chỉ định toán hạng chẳng hạn thanh ghi nào được sử dụng, hoặc toán hạng có nằm trong bộ nhớ hay không. ModR/M là viết tắt của Mod, Register, Memory/Register. Một byte này được chia thành ba trường bit là `mod`, `reg` và `r/m`.

### 4.2. Cấu trúc ModR/M

ModR/M luôn có độ dài 1 byte = 8 bit:

<p align="center">
	<img src="image/image5.png" alt="cấu trúc ModR/M">
</p>

**Trong đó:**
- `mod:` xác định cách diễn giải toán hạng `r/m`, ví dụ dùng thanh ghi trực tiếp hay địa chỉ bộ nhớ.
- `reg:` chỉ định một thanh ghi hoặc một trường opcode mở rộng, tùy instruction.
- `r/m:` chỉ định thanh ghi hoặc toán hạng bộ nhớ, tùy mod và dạng mã hóa.
> [!IMPORTANT]
> **Điểm quan trọng:** `reg` và `r/m` không phải lúc nào cũng chỉ thanh ghi. Ý nghĩa cụ thể còn phụ thuộc vào opcode và các prefix.

### 4.3. Giải mã ModR/M bằng tay

Ở các phần trước, chúng ta đã biết ModR/M byte có nhiệm vụ mã hóa thông tin về toán hạng của instruction. Tuy nhiên, để hiểu cách machine code được diễn giải thành assembly, chúng ta cần thực hành giải mã byte này bằng tay. Quá trình giải mã gồm các bước:
- 1. Xác định opcode và quy tắc encoding của instruction.
- 2. Chuyển ModR/M byte từ hexadecimal sang nhị phân.
- 3. Tách 8 bit thành ba trường mod, reg và r/m.
- 4. Dựa vào opcode, chế độ hoạt động và các prefix để diễn giải từng trường.
- 5. Kết hợp các trường để xác định toán hạng và viết lại instruction assembly.

**Ví dụ:** Giải mã `89 D8`, ta đã biết `89` là opcode của dạng `MOV r/m32, r32` khi không có prefix thay đổi độ rộng toán hạng trong chế độ 64 bit. Byte D8 là ModR/M. Đầu tiên, chuyển nó sang nhị phân $$\large\texttt{D8}_{16}=\texttt{11011000}_2$$ và chúng ta tách 3bit thành 3 trường :

```
D8 =  11     011   000
     ├─┤   ├───┤ ├───┤
     mod    reg   r/m
     |      |     |
     11     011   000
```

- **Bước 1:** là giải mã trường mod, trong đó `mod = 11`, trong ModR/M, `mod = 11` cho biết trường r/m chỉ một thanh ghi thay vì toán hạng bộ nhớ.
- **Bước 2:** là giải mã trường reg, `reg = 011`. Với dạng instruction đang xét và không có REX.R, mã 011 chỉ thanh ghi EBX ở độ rộng 32 bit.
- **Bước 3:** Giải mã trường r/m, ta có  `r/m = 000`, Do `mod = 11`, trường này chỉ thanh ghi EAX ở độ rộng 32 bit
- **Bước 4:** Kết hợp với opcode, Opcode `89` xác định dạng `MOV r/m32, r32`. Trong dạng này, trường reg là toán hạng nguồn, còn trường r/m là toán hạng đích. Vì vậy `mov eax, ebx` là Instruction sao chép 32 bit từ EBX sang EAX. Trong chế độ 64 bit, việc ghi vào EAX đồng thời đặt 32 bit cao của RAX về 0.

## 5. SIB Byte
### 5.1. SIB là gì?

SIB byte (Scale-Index-Base byte) là một byte trong mã máy x86/x86-64, dùng để mã hóa cách truy cập bộ nhớ bằng sự kết hợp của thanh ghi cơ sở (Base), thanh ghi chỉ số (Index) và hệ số nhân (Scale). Nói đơn giản ModR/M cho biết cấu trúc địa chỉ bộ nhớ ở mức cơ bản; khi cần cách tính địa chỉ phức tạp hơn, nó có thể chỉ định thêm một byte SIB

### 5.2. Cấu trúc SIB

SIB gồm 8 bit, chia thành ba trường:

<p align="center">
	<img src="image/image6.png" alt="cấu trúc sib byte">
</p>

Trong đó :
- **trường Scale:** chiếm 2bit. Tác dụng là chọn hệ số nhân của Index: `1`, `2`, `4` hoặc `8`
- **trường Index:**	chiếm 3bit. Tác dụng là mã hóa thanh ghi index
- **trường Base:** chiếm 3bit. Tác dụng là mã hóa thanh ghi base

Công thức địa chỉ tổng quát là `EA = Base + Index x scale + Displacement`. Trong đó EA là effective address (địa chỉ hiệu dụng). Displacement nằm ở trường riêng của instruction nếu encoding yêu cầu, nó không nằm bên trong SIB.

### 5.3. Giải mã SIB bằng tay

Xét instruction sau `mov eax, DWORD PTR [rbx + rcx*4 + 8]`. Một encoding hợp lệ trong x86-64 là `8B 44 8B 08`, trong đó `8B` là opcode, `44` là ModR/M, `8B` là SIB, `08` là displacement. Bây giờ sự vào byte sib là `8B` ta tiến hành giải mã như sau :

```
8B = 10001011
     10 001 011
     ── ─── ───
     SS Index Base
```

Ta thấy `SS = 10` suy ra `Scale = 4`, `Index = 001` suy ra thanh ghi `RCX`, `Base = 011` suy ra thanh ghi `RBX`, cộng thêm byte displacement là `08` vậy giờ ghép lại vào công thức tính địa chỉ ta có `EA = RBX + RCX x 4 + 8` và CPU sử dụng địa chỉ đó để đọc 4 byte vào `EAX`.
- **Nhưng làm sao Debugger biết phải đọc SIB?:** Debugger không nhìn byte `8B` rồi tự đoán rằng byte tiếp theo là SIB. Nó giải mã lần lượt:
  - **Bước 1:** `8B` là dạng `MOV r32, r/m32` trong trường hợp này.
  - **Bước 2:** Ta thấy và cho `ModR/M = 44` từ đó giải mã thành như sau:

    ```
    44 = 01000100
    -------------
      01  000 100
      mod reg r/m
    ```

    **Trong đó:**
      - `mod = 01`: dạng địa chỉ bộ nhớ có displacement 8-bit.
      - `reg = 000`: thanh ghi đích EAX.
      - `r/m = 100`: trong dạng địa chỉ này, báo rằng có byte SIB tiếp theo.
  - **Bước 3:** Ta thấy và cho `SIB = 8B`, Debugger giải mã Base, Index và Scale như ví dụ trên.
  - **Bước 4:** Ta cho `Displacement = 08`. Đọc thêm một byte displacement có dấu, ở đây là `+8`.

  Vì vậy, chuỗi encoding được hiểu như sau

  <p align="center">
    <img src="image/image9.png" alt="chuỗi encoding">
  </p>

> [!IMPORTANT]
> **Điều quan trọng nhất cần thuộc ở giai đoạn này:** ModR/M quyết định có SIB hay không, còn SIB mã hóa cách kết hợp Base, Index và Scale để tính địa chỉ.

## 6. Object Code và ELF

Object code là mã máy được tạo ra từ quá trình biên dịch hoặc lắp ráp, thường đi kèm với thông tin cần thiết để liên kết chương trình. Còn ELF là một định dạng tệp quy định cách tổ chức mã máy và các thông tin liên quan để linker, loader và những công cụ phân tích có thể xử lý.

> [!NOTE]
> **Điểm cần phân biệt:** Object code là khái niệm về nội dung mã, ELF là một định dạng chứa nội dung đó. ELF không đồng nghĩa với mã máy.

### 6.1. Object code là gì?

Object code là mã được tạo ra sau khi mã nguồn được chuyển đổi qua compiler hoặc assembler. Trong ngữ cảnh x86-64, nó thường chứa các byte mã máy, nhưng một object file thực tế còn có thể chứa dữ liệu, symbol, relocation và các metadata khác. **Ví dụ** Assembly:

```asm
global _start

section .text
_start:
    mov eax, 1
    ret
```

Biên dịch bằng NASM `nasm -f elf64 asm.asm -o asm.o`. Tệp `asm.o` là một object file, object Code là mã được tạo ra sau khi mã nguồn được chuyển đổi qua compiler hoặc assembler còn object file là nơi chứa các mã đó. Ta có thể xem các byte trong section `.text` bằng `objdump -d -Mintel asm.o`. **Ví dụ** output:

```asm
0000000000000000 <_start>:
   0: b8 01 00 00 00    mov eax, 1
   5: c3                ret
```

**Ở đây:**

<div align="center">

| Byte	| Instruction	| Ý nghĩa |
|:-|-:|:-|
| `B8 01 00 00 00` |	`mov eax, 1` |	Nạp giá trị 1 vào EAX |
| `C3`	| `ret` |	Trở về địa chỉ trả về trên stack |

</div>

Đó là các byte mã máy. Tuy nhiên, trong object file, địa chỉ và các tham chiếu có thể chưa được linker giải quyết hoàn toàn.

### 6.2. ELF là gì?

ELF là viết tắt của Executable and Linkable Format. Đây là định dạng nhị phân được sử dụng trên nhiều hệ thống Unix-like, bao gồm Linux, cho executable, object file, shared library và một số loại tệp khác. Một tệp ELF không chỉ chứa instruction. Nó có cấu trúc để các công cụ biết dữ liệu nào nằm ở đâu và cần xử lý như thế nào. Nó có cấu trúc :

<p align="center">
<img src="image/image10.png" alt="cấu trúc ELF">
</p>

Một số section chúng ta thường gặp:

<div align="center">

| Section |	Chức năng |
|-|-|
| `.text` |	Thường chứa instruction của chương trình |
| `.rodata` |	Dữ liệu chỉ đọc, chẳng hạn chuỗi hằng |
| `.data` |	Dữ liệu đã khởi tạo, có thể ghi |
| `.bss` | Dữ liệu chưa khởi tạo tường minh, thường được cấp phát và khởi tạo bằng 0 khi chạy |
| `.symtab`	| Bảng symbol phục vụ liên kết và phân tích, nếu có |
| `.rela.text`	| Thông tin relocation liên quan đến section `.text` trên các ELF sử dụng kiểu relocation này |

</div>

Không phải ELF nào cũng có đầy đủ tất cả các section trên. Chẳng hạn, executable đã được strip có thể không còn `.symtab`.

### 6.3. Code Section

Trong ELF, Code Section thường chỉ section chứa mã máy của chương trình, phổ biến nhất là section `.text`. Đây là nơi lưu các instruction mà CPU sẽ thực thi sau khi mã được nạp vào bộ nhớ. Cho **ví dụ:**

```asm
global _start

section .text
_start:
    mov eax, 1
    mov ebx, 0
    ret
```

trong mã nguồn ta thấy có dòng `section .text`, nghĩa là nó yêu cầu NASM đặt các byte được sinh ra từ phần mã tiếp theo vào section `.text`. Sau khi assemble, các instruction được mã hóa thành byte:

```
B8 01 00 00 00    ; mov eax, 1
BB 00 00 00 00    ; mov ebx, 0
C3                ; ret
```

Đó là các byte mã máy nằm trong .text của object file, với điều kiện mã nguồn được assemble đúng như ví dụ.

- **Section .text nằm ở đâu trong ELF?:** Có thể hình dung ELF như một tệp có nhiều vùng dữ liệu được phân loại:

  <p align="center">
    <img src="image/image11.png" alt="vùng dữ liệu được phân loại">
  </p>

  **lưu ý:** `.text` là tên section phổ biến theo quy ước, không phải mọi section chứa mã đều bắt buộc phải mang tên `.text`.

Phân biệt Section với Segment. Đây là điểm quan trọng khi học ELF để reverse engineering. Dựa vào đó, ta có bảng so sánh như sau:

<div align="center">

| Section |	Segment |
|:-|:-|
| Phân loại nội dung phục vụ liên kết và phân tích |	Mô tả các vùng cần ánh xạ khi nạp chương trình |
| Được mô tả trong section header table |	Được mô tả trong program header table |
| **Ví dụ:** `.text`, `.data`, `.rodata` |	**Ví dụ:** `LOAD`, `GNU_STACK`, `DYNAMIC` |

</div>

Một section `.text` có thể nằm bên trong một `PT_LOAD` segment có quyền thực thi. Nhưng section và segment không phải cùng một thứ: segment có thể chứa nhiều section, và loader chủ yếu dựa vào program headers chứ không cần section header table để nạp executable thông thường.

### 6.3. Relocation

Relocation là quá trình điều chỉnh các tham chiếu địa chỉ trong mã máy hoặc dữ liệu khi linker hoặc loader xác định được vị trí mà chúng cần trỏ tới. Trong ELF, relocation còn là tên gọi của cơ chế và các bản ghi mô tả những vị trí cần được điều chỉnh.

Để hiểu tại sao cần relocation, mày hãy tưởng tượng đang viết Assembly và muốn gọi một hàm nằm trong một tệp object khác. Khi NASM tạo `asm.o`, nó có thể chưa biết chính xác địa chỉ cuối cùng của hàm đó. Linker cần xử lý tham chiếu ấy khi ghép các object file lại.

**Vấn đề:** assembler chưa biết địa chỉ cuối cùng, cho hai tệp hợp ngữ như sau:

> main.asm

```asm
global _start
extern hello

section .text
_start:
    call hello
    ret
```

> hello.asm

```asm
global hello

section .text
hello:
    ret
```

Khi assemble `main.asm`, NASM biết rằng call cần gọi `hello`, nhưng `hello` nằm trong object file khác. Địa chỉ cuối cùng của nó còn phụ thuộc vào quá trình liên kết.

Trên x86-64, lệnh `call rel32` thường mã hóa một độ lệch tương đối 32-bit có dấu, tính từ địa chỉ instruction tiếp theo đến đích gọi. Nếu chưa biết đích, assembler chưa thể điền giá trị cuối cùng một cách chính xác. Đây là lúc relocation phát huy tác dụng. Cách relocation hoạt động:

<p align="center">
<img src="image/image12.png" alt="cách relocation hoạt động">
</p>

Một relocation entry thường mô tả những thông tin như:

<div align="center">

| Thành phần |	Ý nghĩa |
|:-|:-|
| Offset |	Vị trí trong section cần được xử lý |
| Type |	Quy tắc tính toán relocation |
| Symbol |	Symbol mà tham chiếu liên quan đến |
| Addend |	Giá trị cộng thêm trong phép tính relocation |

</div>

Không phải mọi relocation entry đều lưu tất cả các trường theo cùng một cách. Chẳng hạn, ELF64 có thể sử dụng `RELA`, trong đó addend được lưu rõ trong relocation entry. Cho **Ví dụ cụ thể** `call hello`, Trên x86-64, call rel32 có dạng mã hóa thông thường là `E8 xx xx xx xx` trong đó `E8` là opcode của near relative call còn bốn byte `xx` là độ lệch tương đối 32-bit có dấu.

CPU tính địa chỉ đích theo công thức `Target = NextRIP + disp32`, trong đó `NextRIP` là địa chỉ ngay sau instruction call còn `disp32` là độ lệch được mã hóa trong bốn byte tiếp theo. Giả sử sau khi liên kết:

```
Địa chỉ call:   0x401000
Địa chỉ kế tiếp: 0x401005
Địa chỉ hello:  0x401020
```

Khi đó nó sẽ tính `disp32 = 0x401020 - 0x401005 = 0x1B`, giống nhưng tính phương trình cơ bản của toán học và Instruction sẽ được mã hóa thành `E8 1B 00 00 00`. Đây là minh họa cho kết quả cuối cùng. Trong thực tế, linker sử dụng relocation type phù hợp để tính giá trị và điền vào đúng vị trí.

> [!NOTE]
> **Lưu ý:** Relocation không nhất thiết có nghĩa là sửa toàn bộ instruction. Trong ví dụ này, linker thường chỉ cần điền bốn byte displacement, giữ nguyên opcode `E8`.

### 6.4. Symbol và Symbol Table

Trong ELF và quá trình liên kết chương trình, Symbol là một mục định danh một thực thể mà chương trình hoặc trình liên kết cần tham chiếu; còn Symbol Table là bảng lưu thông tin về các symbol đó. Để hiểu chính xác, chúng ta nên phân biệt ba thứ: tên trong source code, symbol, và địa chỉ máy.

Symbol (ký hiệu) là một định danh mà assembler, linker hoặc debugger sử dụng để tham chiếu đến một thực thể trong chương trình. **Ví dụ**, viết một file NASM:

```asm
global _start

section .text
_start:
    mov eax, 60
    xor edi, edi
    syscall

hello:
    ret
```

Trong ví dụ này:
- `_start` là symbol đại diện cho vị trí bắt đầu đoạn mã của chương trình.
- `hello` là symbol đại diện cho vị trí của lệnh `ret`.
- `60` và `0` là các giá trị immediate, không phải symbol trong ví dụ này.

Symbol không nhất thiết phải là một hàm. Nó có thể đại diện cho một hàm, biến, nhãn hoặc một đối tượng khác tùy ngữ cảnh. Ví dụ trong C:

```c
int counter = 10;

int add(int a, int b) {
    return a + b;
}
```

Các tên counter và add có thể trở thành symbol trong file object. Tuy nhiên, không phải mọi tên xuất hiện trong source code đều được giữ lại thành symbol trong file đầu ra.

còn Symbol Table (bảng ký hiệu) là bảng chứa các bản ghi mô tả symbol. Trong ELF, một symbol entry có thể chứa các trường như:

<div align="center">

| Trường |	Ý nghĩa |
|:-|:-|
| `st_name`	| Offset đến tên symbol trong string table |
| `st_value`	| Giá trị symbol, thường là địa chỉ hoặc offset tùy loại file và symbol |
| `st_size`	| Kích thước đối tượng được symbol đại diện, nếu xác định được |
| `st_info`	| Thông tin về loại symbol và binding |
| `st_other`	| Thông tin thuộc tính khác |
| `st_shndx`	| Section index liên quan đến symbol |

</div>

> [!NOTE]
> **Điểm cần nhớ:** Symbol Table không đơn giản chỉ là bảng tên hàm. Nó lưu metadata để linker, debugger và các công cụ phân tích hiểu những symbol đó đại diện cho gì.

Cách xem Symbol Table bằng readelf, chúng ta tạo file `symbol.asm` và xét hợp ngữ sau :

```asm
global _start

section .text
_start:
    mov eax, 60
    xor edi, edi
    syscall

hello:
    ret
```

Assemble thành ELF relocatable object `nasm -f elf64 symbol.asm -o symbol.o`. Xem bảng symbol thì ta dùng `readelf -s symbol.o`. Kết quả sẽ có dạng tương tự:

```
Symbol table '.symtab' contains ... entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND
     1: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT    1 _start
     2: 0000000000000009     0 NOTYPE  LOCAL  DEFAULT    1 hello
```

Đây là kết quả minh họa, offset và cách hiển thị cụ thể có thể khác tùy công cụ và file. Cách đọc:
- `Value`: `_start` có giá trị 0 trong section của nó, hello có giá trị 9, tức offset 9 byte tính từ đầu section `.text` trong ví dụ này.
- `Type`: `NOTYPE` có nghĩa loại symbol chưa được chỉ rõ là function hay object. NASM không nhất thiết tự đánh dấu nhãn thành `FUNC`.
- `Bind`: `GLOBAL` cho biết `_start` có global binding, `LOCAL` cho biết `hello` chỉ có phạm vi liên kết cục bộ.
- `Ndx`: 1 ở đây là chỉ số section chứa symbol, thường tương ứng `.text`, `UND` có nghĩa undefined, tức symbol chưa được định nghĩa trong file hiện tại.

> [!NOTE]
> Lưu ý: `Value = 0` ở file `.o` không có nghĩa chương trình sẽ chạy tại địa chỉ 0. Đây là file relocatable nên giá trị thường là offset tương đối với section, địa chỉ cuối cùng còn phụ thuộc quá trình link và cách nạp chương trình.

- **Symbol liên quan thế nào đến Linker và Relocation?:** Xét hai file assembly riêng biệt.
  > main.asm

  ```asm
  global _start
  extern hello

  section .text
  _start:
      call hello
      mov eax, 60
      xor edi, edi
      syscall
  ```

  > hello.asm

  ```asm
  global hello

  section .text
  hello:
      ret
  ```

  Assemble từng file `nasm -f elf64 main.asm -o main.o` và `nasm -f elf64 hello.asm -o hello.o`. Kiểm tra symbol trong `main.o` ta dùng `readelf -s main.o`. Trong `main.o`, symbol `hello` có thể xuất hiện với `Ndx = UND` vì file này biết tên `hello` nhưng chưa chứa định nghĩa của nó.

  <p align="center">
    <img src="image/image13.png" alt="hình ảnh kết quả lệnh readelf -s main.o">
  </p>

  Kiểm tra relocation ta dùng `readelf -r main.o` và `objdump -dr -Mintel main.o`:

  <p align="center">
    <img src="image/image14.png" alt="hình ảnh kết quả lệnh readelf -r main.o và objdump -dr -Mintel main.o">
  </p>

  Ta thấy lệnh `call hello` cần địa chỉ đích để tính displacement tương đối của lệnh `call`. Vì `hello` được định nghĩa trong file khác, assembler có thể để lại một relocation entry để linker xử lý. Sau đó link `ld main.o hello.o -o program`. Lúc này, linker tìm định nghĩa hello trong các object file đầu vào, xác định vị trí cuối cùng và xử lý relocation tương ứng. Quá trình này cho thấy hai cấu trúc có liên quan nhưng khác nhau:
  - **Symbol Table:** cung cấp thông tin về symbol, bao gồm tên, loại, binding và vị trí liên quan.
  - **Relocation Table:** ghi lại những vị trí cần được hiệu chỉnh và thông tin cần thiết để linker hoặc thành phần liên kết tiếp theo thực hiện việc đó.

  Không phải symbol nào cũng cần relocation; relocation chỉ cần khi có tham chiếu cần được xử lý hoặc hiệu chỉnh.

Phân biệt `.symtab` và `.dynsym`. Trong ELF, ta có thể gặp hai bảng symbol thường thấy:

<div align="center">

| Bảng |	Mục đích |
|:-|:-|
| `.symtab`	| Bảng symbol đầy đủ hơn phục vụ liên kết và phân tích, thường có thể bị loại bỏ khi strip |
| `.dynsym`	| Bảng symbol phục vụ liên kết động, chẳng hạn giữa executable và shared libraries |

</div>

Không phải ELF nào cũng có cả hai. Một executable liên kết tĩnh, một object file hoặc một file đã bị strip có thể có cấu trúc khác nhau. Các lệnh hữu ích:

```bash
readelf -S program       # Xem section headers
readelf -s program       # Xem symbol tables
nm -n program            # Liệt kê symbol theo giá trị
objdump -t program       # Hiển thị bảng symbol
```

> [!IMPORTANT]
> Symbol là định danh gắn với một thực thể hoặc vị trí trong chương trình, Symbol Table là cấu trúc dữ liệu lưu metadata của các symbol. Linker sử dụng thông tin này để liên kết các tham chiếu giữa những object file và xử lý các relocation cần thiết.

### 6.5. Từ Object File đến Executable

Trong quy trình biên dịch và liên kết trên Linux x86-64, Object File sang Executable là quá trình biến các file object có thể còn tham chiếu chưa được giải quyết thành một file thực thi có cấu trúc phù hợp để hệ điều hành nạp và chạy. Ta cần hiểu 4 việc chính:

<table>
<tr>
<td>

- **1.Symbol resolution — giải quyết symbol:** xác định symbol được tham chiếu được định nghĩa ở đâu.
- **2.Relocation — hiệu chỉnh tham chiếu:** tính và ghi các giá trị địa chỉ hoặc displacement cần thiết.
- **3.Layout:** sắp xếp các section thành các vùng nhớ và segment phù hợp.
- **4.Executable generation:** tạo file ELF executable với entry point và program headers.
Không phải mọi file đều trải qua các bước giống hệt nhau. Ví dụ dưới đây dùng NASM, ELF64 và GNU ld trên Linux.

</td>

<td>

<p align="center" valign="top">
	<kbd>
  <img src="image/image15.png" alt="hình ảnh object file đến executable" width="1500%" length="1200%">
	<kbd>
</p>

</td>
</tr>
</table>

> [!NOTE]
> **Lưu ý:** linker không chạy chương trình. Linker tạo executable; kernel chịu trách nhiệm nạp chương trình khi mày thực thi nó.