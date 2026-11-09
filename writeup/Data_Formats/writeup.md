# Data Formats — x86-64 Machine-Level Representation

**Mục lục**

<table>
<tr>
<td valign="top">

- [1. Tổng quan về Data Formats](#1-tổng-quan-về-data-formats)
  - [1.1. Data Formats là gì?](#11-data-formats-là-gì)
  - [1.2. Vai trò của Data Formats trong Machine-Level Programming](#12-vai-trò-của-data-formats-trong-machine-level-programming)
  - [1.3. Mối quan hệ giữa C Data Types và Machine-Level Data Formats](#13-mối-quan-hệ-giữa-c-data-types-và-machine-level-data-formats)
  - [1.4. Data Width và cách phân loại dữ liệu](#14-data-width-và-cách-phân-loại-dữ-liệu)

- [2. Các định dạng dữ liệu cơ bản trong x86-64](#2-các-định-dạng-dữ-liệu-cơ-bản-trong-x86-64)
  - [2.1. Byte (8-bit)](#21-byte-8-bit)
  - [2.2. Word (16-bit)](#22-word-16-bit)
  - [2.3. Double Word (32-bit)](#23-double-word-32-bit)
  - [2.4. Quad Word (64-bit)](#24-quad-word-64-bit)
  - [2.5. Operand Size và Data Width](#25-operand-size-và-data-width)
  - [2.6. Quy ước kích thước dữ liệu trong AT&T Syntax](#26-quy-ước-kích-thước-dữ-liệu-trong-att-syntax)

- [3. Integer Data Formats](#3-integer-data-formats)
  - [3.1. Integer Representation](#31-integer-representation)
  - [3.2. Unsigned Integer](#32-unsigned-integer)
  - [3.3. Signed Integer](#33-signed-integer)
  - [3.4. Two's Complement Representation](#34-twos-complement-representation)
  - [3.5. Signed và Unsigned Interpretation](#35-signed-và-unsigned-interpretation)
  - [3.6. Integer Range theo Data Width](#36-integer-range-theo-data-width)
  - [3.7. Integer Representation trong Register và Memory](#37-integer-representation-trong-register-và-memory)

- [4. Floating-Point Data Formats](#4-floating-point-data-formats)
  - [4.1. Tổng quan về Floating-Point Representation](#41-tổng-quan-về-floating-point-representation)
  - [4.2. IEEE 754 Standard](#42-ieee-754-standard)
  - [4.3. Single Precision (32-bit)](#43-single-precision-32-bit)
    - [4.3.1. Sign Bit](#431-sign-bit)
    - [4.3.2. Exponent Field](#432-exponent-field)
    - [4.3.3. Fraction Field](#433-fraction-field)
  - [4.4. Double Precision (64-bit)](#44-double-precision-64-bit)
    - [4.4.1. Sign Bit](#441-sign-bit)
    - [4.4.2. Exponent Field](#442-exponent-field)
    - [4.4.3. Fraction Field](#443-fraction-field)
  - [4.5. Normalized và Denormalized Values](#45-normalized-và-denormalized-values)
  - [4.6. Special Values](#46-special-values)
    - [4.6.1. Positive và Negative Zero](#461-positive-và-negative-zero)
    - [4.6.2. Infinity](#462-infinity)
    - [4.6.3. NaN (Not a Number)](#463-nan-not-a-number)
  - [4.7. Floating-Point Precision](#47-floating-point-precision)
  - [4.8. Floating-Point Representation và Machine-Level Operations](#48-floating-point-representation-và-machine-level-operations)

- [5. Data Formats và x86-64 Registers](#5-data-formats-và-x86-64-registers)
  - [5.1. General-Purpose Registers](#51-general-purpose-registers)
  - [5.2. Register Width](#52-register-width)
  - [5.3. Subregister Representation](#53-subregister-representation)
    - [5.3.1. 64-bit Register](#531-64-bit-register)
    - [5.3.2. 32-bit Register](#532-32-bit-register)
    - [5.3.3. 16-bit Register](#533-16-bit-register)
    - [5.3.4. 8-bit Register](#534-8-bit-register)
  - [5.4. Register Aliasing](#54-register-aliasing)
  - [5.5. High-Byte Registers và REX Prefix](#55-high-byte-registers-và-rex-prefix)
  - [5.6. Ảnh hưởng của Operand Width đến Register State](#56-ảnh-hưởng-của-operand-width-đến-register-state)

<td>
<td valign="top">

- [6. Data Formats trong Assembly](#6-data-formats-trong-assembly)
  - [6.1. Data Size Suffix trong AT&T Syntax](#61-data-size-suffix-trong-att-syntax)
  - [6.2. Byte, Word, Long và Quad Operations](#62-byte-word-long-và-quad-operations)
  - [6.3. Integer Operations và Operand Interpretation](#63-integer-operations-và-operand-interpretation)
  - [6.4. Floating-Point Operations](#64-floating-point-operations)
  - [6.5. Signed và Unsigned Instruction Semantics](#65-signed-và-unsigned-instruction-semantics)
  - [6.6. Data Format và cách CPU diễn giải Operand](#66-data-format-và-cách-cpu-diễn-giải-operand)

- [7. Data Formats trong chương trình C](#7-data-formats-trong-chương-trình-c)
  - [7.1. C Data Types và kích thước tương ứng](#71-c-data-types-và-kích-thước-tương-ứng)
  - [7.2. Integer Types](#72-integer-types)
  - [7.3. Floating-Point Types](#73-floating-point-types)
  - [7.4. Signedness và Type Interpretation](#74-signedness-và-type-interpretation)
  - [7.5. Mối quan hệ giữa C Type và Assembly Operand](#75-mối-quan-hệ-giữa-c-type-và-assembly-operand)
  - [7.6. Data Type Conversion ở Machine Level](#76-data-type-conversion-ở-machine-level)

- [8. Thực nghiệm và phân tích Data Formats](#8-thực-nghiệm-và-phân-tích-data-formats)
  - [8.1. Quan sát kích thước dữ liệu trong C](#81-quan-sát-kích-thước-dữ-liệu-trong-c)
  - [8.2. Biểu diễn Integer dưới dạng Hexadecimal](#82-biểu-diễn-integer-dưới-dạng-hexadecimal)
  - [8.3. Phân tích Signed và Unsigned bằng GDB](#83-phân-tích-signed-và-unsigned-bằng-gdb)
  - [8.4. Quan sát Register Width và Subregister](#84-quan-sát-register-width-và-subregister)
  - [8.5. Phân tích Floating-Point bằng GDB](#85-phân-tích-floating-point-bằng-gdb)
  - [8.6. Đối chiếu C Data Types với Assembly](#86-đối-chiếu-c-data-types-với-assembly)
  - [8.7. Kiểm chứng Data Representation bằng `objdump`](#87-kiểm-chứng-data-representation-bằng-objdump)

- [9. Tổng kết và tài liệu tham khảo](#9-tổng-kết-và-tài-liệu-tham-khảo)
  - [9.1. Tổng hợp các Data Formats trong x86-64](#91-tổng-hợp-các-data-formats-trong-x86-64)
  - [9.2. Mối quan hệ giữa Data Type, Data Width và Register](#92-mối-quan-hệ-giữa-data-type-data-width-và-register)
  - [9.3. Những nguyên tắc khi phân tích Data Formats](#93-những-nguyên-tắc-khi-phân-tích-data-formats)
  - [9.4. Tài liệu tham khảo](#94-tài-liệu-tham-khảo)

</td>
</tr>
</table>

---

## 1. Tổng quan về Data Formats
### 1.1. Data Formats là gì?

Data Formats (định dạng dữ liệu) là cách xác định dữ liệu được biểu diễn và lưu trữ như thế nào trong máy tính, đặc biệt là về kích thước (bit-width), kiểu dữ liệu và cách CPU diễn giải dữ liệu đó. Ở mức máy tính, CPU không trực tiếp hiểu các khái niệm như int, char, float hay double theo cách lập trình viên nhìn thấy. CPU xử lý các bit nhị phân. Vì vậy, để thao tác chính xác, chương trình và kiến trúc CPU phải xác định dữ liệu có kích thước bao nhiêu và được diễn giải theo dạng nào.

Ví dụ xét cùng một giá trị như :

```c
int a = 10;
long b = 10;
```

Trên Linux x86-64 sử dụng mô hình dữ liệu LP64:

<div align="center">

| Kiểu dữ liệu | Kích thước | Bit |
|-|-|-|
| char	| 1 byte | 8 bit |
| short	| 2 byte | 16 bit |
| int	| 4 byte | 32 bit |
| long	| 8 byte | 64 bit |
| float	| 4 byte | 32 bit |
| double |	8 byte | 64 bit |

</div>

Mặc dù `a` và `b` cùng mang giá trị `10`, chúng có kích thước lưu trữ khác nhau. Điều này ảnh hưởng đến cách trình biên dịch sinh mã máy và cách CPU thực hiện các thao tác trên dữ liệu. Trong kiến trúc x86-64, kích thước toán hạng thường được thể hiện thông qua các hậu tố của lệnh AT&T:

```asm
movb $10, %al     # 8-bit
movw $10, %ax     # 16-bit
movl $10, %eax    # 32-bit
movq $10, %rax    # 64-bit
```

Các hậu tố `b`, `w`, `l`, `q` lần lượt biểu thị kích thước `8`, `16`, `32` và `64` bit.

### 1.2. Vai trò của Data Formats trong Machine-Level Programming

Trong Machine-Level Programming, Data Formats đóng vai trò xác định CPU sẽ thao tác với dữ liệu theo kích thước nào và dữ liệu đó được diễn giải ra sao trong quá trình thực thi lệnh máy.

Ở cấp độ ngôn ngữ C, lập trình viên có thể khai báo các kiểu dữ liệu như int, long, float hoặc double. Tuy nhiên, khi chương trình được biên dịch thành mã máy, những kiểu dữ liệu này phải được chuyển thành các dạng toán hạng cụ thể mà kiến trúc CPU hỗ trợ. Data Formats giúp kết nối giữa kiểu dữ liệu ở cấp độ ngôn ngữ lập trình và cách CPU xử lý dữ liệu ở cấp độ máy.

Đầu tiên ta nói đến là xác định kích thước toán hạng. Data Formats xác định số bit mà một lệnh máy sẽ đọc, ghi hoặc xử lý. Ví dụ:

```asm
movb $10, %al
movw $10, %ax
movl $10, %eax
movq $10, %rax
```

Mặc dù các lệnh trên đều đưa giá trị 10 vào thanh ghi, kích thước toán hạng của chúng khác nhau:
- `movb`: 8 bit.
- `movw`: 16 bit.
- `movl`: 32 bit.
- `movq`: 64 bit.

Nếu không xác định đúng kích thước toán hạng, chương trình có thể đọc hoặc ghi dữ liệu không đúng với mục đích ban đầu.

Kế tiếp là xác định cách diễn giải dữ liệu (Data Interpretation). Một chuỗi bit không tự mang ý nghĩa duy nhất. Cách diễn giải phụ thuộc vào định dạng dữ liệu và thao tác mà chương trình thực hiện

> Điều này cũng đã được đề cập nhiều ở chương [Two-Complement-Code](https://github.com/tranquanghao708/CSAPP-learning/blob/main/writeup/two-complement-code/two-complement-code.md)

Ví dụ, cùng một mẫu bit 8-bit chẳng hạn như `11111111` Có thể được diễn giải thành:

<div align="center">

| Kiểu diễn giải |	Giá trị |
|:-|:-:|
| Unsigned integer	| 255 |
| Signed integer (Two's Complement) |	-1 |

</div>

Điều này đặc biệt quan trọng trong Machine-Level Programming vì CPU có những lệnh và điều kiện xử lý khác nhau tùy theo việc dữ liệu được xem là số nguyên có dấu hay không dấu. Ví dụ:

```asm
movsx eax, al    ; Sign extension
movzx eax, al    ; Zero extension
```

Hai lệnh trên đều mở rộng dữ liệu 8-bit lên 32-bit, nhưng cách mở rộng khác nhau:
- `movsx`: bảo toàn ý nghĩa số có dấu.
- `movzx`: mở rộng bằng cách thêm các bit 0 ở phía trên.

### 1.3. Mối quan hệ giữa C Data Types và Machine-Level Data Formats

Trong ngôn ngữ C, Data Types (kiểu dữ liệu) xác định cách chương trình khai báo, lưu trữ và thao tác với dữ liệu. Khi chương trình được biên dịch, trình biên dịch phải chuyển những kiểu dữ liệu này thành các dạng dữ liệu và thao tác tương ứng với kiến trúc máy đích. Đây chính là mối quan hệ giữa C Data Types và Machine-Level Data Formats: kiểu dữ liệu C cung cấp ngữ nghĩa ở cấp độ ngôn ngữ lập trình, còn Machine-Level Data Formats thể hiện cách dữ liệu được biểu diễn và thao tác ở cấp độ máy.

Đầu tiên là C data types, kiểu dữ liệu ở cấp độ ngôn ngữ C. C cung cấp nhiều kiểu dữ liệu khác nhau để lập trình viên biểu diễn thông tin:

```c
char a = 10;
short b = 20;
int c = 30;
long d = 40;

float e = 1.5f;
double f = 2.5;
```

Mỗi kiểu dữ liệu có những đặc điểm riêng:
- Kích thước lưu trữ.
- Phạm vi giá trị có thể biểu diễn.
- Cách diễn giải dữ liệu.
- Những phép toán được phép thực hiện.

Tuy nhiên, kích thước của một số kiểu dữ liệu phụ thuộc vào ABI và nền tảng biên dịch. Vì vậy, không thể mặc định rằng long luôn có kích thước 64-bit trên mọi hệ thống.