# CSAPP: Accessing Information

**mục lục**

<table>
<tr>
<td>

[1. Machine-Level Programming: Accessing Information](#1-machine-level-programming-accessing-information)
  - [1.1. Introduction to Accessing Information](#11-introduction-to-accessing-information)
    - [1.1.1. Accessing Information là gì?]()
    - [1.1.2. Vai trò của Accessing Information trong Machine-Level Programming](112-vai-trò-của-accessing-information-trong-machine-level-programming)
    - [1.1.3. Accessing Information trong quá trình thực thi chương trình](#113-accessing-information-trong-quá-trình-thực-thi-chương-trình)
    - [1.1.4. Các thành phần liên quan đến Accessing Information](#114-các-thành-phần-liên-quan-đến-accessing-information)
  - [1.2. General-Purpose Registers](#12-general-purpose-registers)
  - [1.3. Register Naming Conventions](#13-register-naming-conventions)
  - [1.4. Data Movement Instructions](#14-data-movement-instructions)
  - [1.5. Operand Specifiers](#15-operand-specifiers)
  - [1.6. Data Movement Examples](#16-data-movement-examples)
  - [1.7. Understanding Data Movement at Machine Level](#17-understanding-data-movement-at-machine-level)
2. Arithmetic and Logical Operations
  - 2.1. Arithmetic Instructions
  - 2.2. Unary Operations
  - 2.3. Binary Operations
  - 2.4. Shift Operations
  - 2.5. Bitwise Logical Operations
  - 2.6. Special Arithmetic Operations
  - 2.7. Condition Codes and Flags
3. Accessing Information in Memory
  - 3.1. Memory Addressing
  - 3.2. Addressing Modes
  - 3.3. Effective Address Calculation
  - 3.4. Memory Operand Access
  - 3.5. Memory Access Examples
  - 3.6. Pointer Dereferencing at Machine Level

</td>
<td>

4. Stack Operations and Procedure Calls
  - 4.1. Runtime Stack
  - 4.2. Stack Pointer (RSP)
  - 4.3. Push and Pop Operations
  - 4.4. Stack Frame Organization
  - 4.5. Procedure Call Mechanism
  - 4.6. Return Address Management
  - 4.7. Function Arguments and Return Values
  - 4.8. Stack-Based Data Access
5. Understanding Machine-Level Data Access
  - 5.1. Register vs Memory Access
  - 5.2. Virtual Address Space
  - 5.3. Memory Layout and Data Representation
  - 5.4. Translating C Expressions into Assembly
  - 5.5. Practical Experiments with GDB and objdump
6. Practical Analysis
  - 6.1. Inspecting General-Purpose Registers with GDB
  - 6.2. Analyzing Data Movement Instructions
  - 6.3. Examining Memory with GDB
  - 6.4. Tracking Stack Operations
  - 6.5. C-to-Assembly Correlation
  - 6.6. Case Studies and Technical Writeups
7. References
  - 7.1. CS:APP – Chapter 3
  - 7.2. Intel 64 and IA-32 Architectures Software Developer's Manual
  - 7.3. System V AMD64 ABI
  - 7.4. GNU GDB Documentation
  - 7.5. GNU Binutils Documentation

</td>
</tr>
</table>

---

## 1. Machine-Level Programming: Accessing Information
### 1.1. Introduction to Accessing Information
#### 1.1.1. Accessing Information là gì?

`Accessing Information (доступ к информации)` là quá trình CPU truy xuất và thao tác với dữ liệu được lưu trữ trong các thành phần của hệ thống máy tính, chủ yếu thông qua các `registers (Регистры)`, `Memory (Память)` và `Machine Instructions (Машинные инструкции)`. Trong kiến trúc x86-64, CPU không trực tiếp thao tác với các biến trong mã nguồn C theo cách mà lập trình viên nhìn thấy. Thay vào đó, `Compiler (Компилятор)` chuyển đổi các biểu thức và thao tác dữ liệu trong `C (код на языке C)` thành những lệnh `Assembly (Код на языке ассемблера)` tương ứng. Các lệnh này xác định:
- Dữ liệu cần truy cập. `(Data need access - Данным нужен доступ)`
- Vị trí lưu trữ dữ liệu. `(Storage location for data - Место хранения данных)`
- Cách di chuyển dữ liệu giữa các thành phần. `(how to move data between components - как передавать данные между компонентами)`
- Cách CPU sử dụng dữ liệu trong quá trình thực thi. `(how to CPU uses data in execute progress - Как центральный процессор использует данные в процессе выполнения операций)`

#### 1.1.2. Vai trò của Accessing Information trong Machine-Level Programming

`Accessing Information (доступ к информации)` đóng vai trò nền tảng trong `Machine-Level Programming (Программирование на машинном уровне)` vì hầu hết các hoạt động tính toán của CPU đều yêu cầu truy xuất dữ liệu từ một hoặc nhiều vị trí lưu trữ. Các hoạt động chính bao gồm:

1. **Register Access - Доступ к регистрам:** Truy cập dữ liệu được lưu trữ trong các thanh ghi của CPU.
2. **Memory Access - Доступ к памяти:** Truy cập dữ liệu được lưu trữ trong bộ nhớ thông qua địa chỉ bộ nhớ.
3. **Data Movement - перемещение данных:** Di chuyển dữ liệu giữa thanh ghi, bộ nhớ và các toán hạng tức thời `(Immediate Operands - Непосредственные операнды)`.
4. **Operand Selection - Выбор операндов:** Xác định toán hạng mà một lệnh Assembly sẽ sử dụng.
5. **Stack Access - Доступ к стеку:** Truy cập dữ liệu trên ngăn xếp trong quá trình thực thi chương trình.

#### 1.1.3. Accessing Information trong quá trình thực thi chương trình

Xét đoạn chương trình C:

```c
int main(void) {
    int a = 10;
    int b = 20;
    int c = a + b;

    return c;
}
```

Ở cấp độ `Machine-Level Programming (Программирование на машинном уровне)`, các biến `a`, `b`, `c` không nhất thiết được lưu trữ tại những vị trí cố định trong RAM. Trình biên dịch có thể phân bổ chúng vào thanh ghi, stack hoặc tối ưu hóa hoàn toàn các biến này. Ví dụ Assembly minh họa:

```asm
movl $10, %eax
movl $20, %edx
addl %edx, %eax
```

Quá trình thực hiện:
- 1. `movl $10, %eax`: Đưa giá trị `10` vào thanh ghi `EAX`.
- 2. `movl $20, %edx`: Đưa giá trị `20` vào thanh ghi `EDX`.
- 3. `addl %edx, %eax`: Cộng giá trị trong `EDX` vào `EAX`.

Sau khi thực hiện, `EAX` chứa giá trị `30`. Ví dụ này cho thấy CPU có thể truy cập và thao tác với dữ liệu trực tiếp thông qua các thanh ghi mà không cần truy cập RAM cho từng phép toán.

#### 1.1.4. Các thành phần liên quan đến Accessing Information

<div align="center">

| Thành phần | Vai trò |
|---|---|
| Registers - Регистры | Lưu trữ dữ liệu tạm thời bên trong CPU |
| Memory - Память | Lưu trữ dữ liệu và chương trình |
| Address - Адрес | Xác định vị trí dữ liệu trong không gian địa chỉ |
| Operands - Операнды | Các toán hạng được sử dụng bởi lệnh máy |
| Machine Instructions - Машинные инструкции | Xác định thao tác mà CPU thực hiện |
| Stack - Куча | Lưu trữ dữ liệu phục vụ quá trình thực thi chương trình |

</div>

### 1.2. General-Purpose Registers
### 1.3. Register Naming Conventions
### 1.4. Data Movement Instructions
### 1.5. Operand Specifiers
### 1.6. Data Movement Examples
### 1.7. Understanding Data Movement at Machine Level