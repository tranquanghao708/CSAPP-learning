# CSAPP : Floating point numbers - IEEE 754 (số thực dấu phẩy động chuẩn IEEE 754)

**mục lục**

- 1.Tổng quan về IEEE 754.

- 1.1.Trường số dấu (signed)

- 1.2.Trường số mũ (Exponent)

- 1.2.1.Độ lệch (Bias)

- 1.3.Trường dãy số sau dấu chấm (Fraction)

- 1.4.Mã lệch

---

## 1.Tổng quan về IEEE 754.

- `Số thực IEEE 754` là quy tắc biểu diễn số thực cho thiết bị nhị phân (máy tính) thế giới. **Formula tổng quan là** $$\Large(-1)^{S} \times 1,m \times 2^{e-b}$$, trong đó :

S : là bit dấu, viết tắt sign

m : là 

e : là mã lệch

b : là độ lệch, viết tắt bias

#### 1.1.Trường số dấu (signed)

- Là trường chỉ tính `MSB = 1` hay `MSB = 0`, quyết định số âm hay dương. Ví dụ cho số thực `19.6875` nó sẽ chuyển thành 0 và 1 trong máy tính, bit dấu biểu diễn là âm hay dương với MSB, điều này đã nói rõ ở [two complement code](https://github.com/tranquanghao708/CSAPP-learning/blob/main/writeup/two-complement-code/two-complement-code.md)

#### 1.2.Trường số mũ (Exponent)

- là 

#### 1.2.1.Độ lệch (Bias)

- dạng có độ chính xác đơn tương ứng 32bit và dạng có độ chính xác kép tương ứng 64bit và kép mở rộng tương đương 80bit