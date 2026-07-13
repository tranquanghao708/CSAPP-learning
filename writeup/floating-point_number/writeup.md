# CSAPP : Floating point numbers - IEEE 754 (số thực dấu phẩy động chuẩn IEEE 754)

**mục lục**

- 1.Tổng quan về IEEE 754.

- 1.1.Trường số dấu (signed)

- 1.2.Trường số mũ (Exponent)

- 1.2.1.Bias

- 1.3.Trường dãy số sau dấu chấm (Fraction)

---

## 1.Tổng quan về IEEE 754.

- `Số thực IEEE 754` là quy tắc biểu diễn số thực cho thiết bị nhị phân (máy tính) thế giới. Formula tổng quan là $$\Large(-1)^{S} \times 1,m \times 2^{e-b}$$

#### 1.1.Trường số dấu (signed)

- Là trường chỉ tính `MSB = 1` hay `MSB = 0`, quyết định số âm hay dương

#### 1.2.Trường số mũ (Exponent)

- là 