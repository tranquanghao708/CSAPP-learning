#CSAPP: Accessing Information

**mục lục**

<table>
<tr>
<td>

[1. Machine-Level Programming: Accessing Information](#1-machine-level-programming-accessing-information)
  - [1.1. Introduction to Accessing Information](#11-introduction-to-accessing-information)
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

`Accessing Information (доступ к информации)` là quá trình CPU truy xuất và thao tác với dữ liệu được lưu trữ trong các thành phần của hệ thống máy tính, chủ yếu thông qua các `registers (Регистры)`, `Memory (Память)` và `Machine Instructions (Машинные инструкции)`. Trong kiến trúc x86-64, CPU không trực tiếp thao tác với các biến trong mã nguồn C theo cách mà lập trình viên nhìn thấy. Thay vào đó, `Compiler (Компилятор)` chuyển đổi các biểu thức và thao tác dữ liệu trong `C (код на языке C)` thành những lệnh `Assembly (Код на языке ассемблера)` tương ứng. Các lệnh này xác định:
- Dữ liệu cần truy cập. `(Data need access - Данным нужен доступ)`
- Vị trí lưu trữ dữ liệu. `(Storage location for data - Место хранения данных)`
- Cách di chuyển dữ liệu giữa các thành phần. `(how to move data between components - как передавать данные между компонентами)`
- Cách CPU sử dụng dữ liệu trong quá trình thực thi. `(how to CPU uses data in execute progress - Как центральный процессор использует данные в процессе выполнения операций)`

### 1.2. General-Purpose Registers
### 1.3. Register Naming Conventions
### 1.4. Data Movement Instructions
### 1.5. Operand Specifiers
### 1.6. Data Movement Examples
### 1.7. Understanding Data Movement at Machine Level