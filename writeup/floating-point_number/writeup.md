# CSAPP : Floating point numbers - IEEE 754 (số thực dấu phẩy động chuẩn IEEE 754)

> Ngày bắt đầu viết : 13/7/2026

> Ngày hoàn thành :

**mục lục**

- 1.Tổng quan về IEEE 754.

- 1.1.Chuẩn hóa số thực

- 1.2.Trường dãy số sau dấu chấm (Fraction)

- 1.3.Trường số mũ (Exponent)

- 1.3.1.Độ lệch (Bias)

- 1.4.Trường số dấu (signed)

- 1.5.Thiết lập và đếm bit phân cho S,E,m phù hợp với độ rộng toán hạng

---

## 1.Tổng quan về IEEE 754.

- `Số thực IEEE 754` là quy tắc biểu diễn số thực cho thiết bị nhị phân (máy tính) thế giới. **Formula tổng quan là** $$\Large(-1)^{S} \times 1.m \times 2^{e-b}$$, trong đó :

S : là bit dấu, viết tắt sign

m : hidden bit + fraction là trường dãy số sau dấu chấm, viết tắt Fraction

e : là giá trị của trường exponent

b : là độ lệch, viết tắt bias

- Ta có một structure của cái này như sau:

| S (sign) | E (Exponent) | m (Fraction) |
|----------|--------------|--------------|

#### 1.1.Chuẩn hóa số thực

- **chuẩn hóa là gì?** : giống toán học, **formula =**$$\large1.xxxxx\times2^{N}$$ ví dụ 12345 = $$\large1.2345\times10^{4}$$ hoặc 0.00123 = $$\large1.23\times10^{-3}$$. Đó gọi là dạng chuẩn hóa

IEEE 754 cũng làm thế, cơ mà nó biểu diễn dạng binary và dùng cơ số 2

#### 1.2.Trường dãy số sau dấu chấm (Fraction)

- Là trường số sau dấu chấm ví dụ `13.<m (Fraction)>`

#### 1.3.Trường số mũ (Exponent)

- là 

#### 1.3.1.Độ lệch (Bias)

- dạng có độ chính xác đơn tương ứng 32bit và dạng có độ chính xác kép tương ứng 64bit và kép mở rộng tương đương 80bit

#### 1.4.Trường số dấu (signed)

- Là trường chỉ tính `MSB = 1` hay `MSB = 0`, quyết định số âm hay dương. Ví dụ cho số thực `19.6875` nó sẽ chuyển thành 0 và 1 trong máy tính, bit dấu biểu diễn là âm hay dương với MSB, điều này đã nói rõ ở [two complement code](https://github.com/tranquanghao708/CSAPP-learning/blob/main/writeup/two-complement-code/two-complement-code.md) , ở trường số có dấu này người ta chỉ dùng 1bit để biểu diễn nó với MSB trong đa architecture