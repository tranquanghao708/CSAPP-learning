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

- **chuẩn hóa là gì?** : giống toán học, **formula =**$$\large1.xxxxx\times2^{N}$$ ví dụ $$\large12345_{10}$$ = $$\large1.2345_{10}\times10^{4}$$ số mũ là 4 vì dịch dot sang trái 4 lần hoặc $$\large0.00123_{10}$$ = $$\large1.23\times10^{-3}$$ số mũ là -3 vì dịch dot sang phải 3 lần. Đó gọi là dạng chuẩn hóa

IEEE 754 cũng làm thế, cơ mà nó biểu diễn dạng binary và dùng cơ số 2. Ví dụ, $$\large13.25_{10} = 1101.01_{2}$$, di chuyển dấu chấm sao cho trước dấu chấm chỉ còn đúng một bit 1 ta có $$\large1.10101_{2}$$ số lần di chuyển là 3 vì :

```
lúc đầu : 1101.01
di chuyển dot 1 lần : 110.101
di chuyển dot 2 lần : 11.0101
di chuyển dot 3 lần : 1.10101
Tổng cộng dịch dấu chấm 3 lần để trước dấu chấm chỉ còn đúng một bit 1.
```

Vậy nên ta có số mũ là 3, suy ra $$\large1.10101_{2}\times2^{3}$$ và khi tính lại là $$\large1.10101_{2}\times2^{3} = 1101.01_{2}$$ ta thấy nó lại di chuyển về từ đầu. Vậy cho ví dụ khi số mũ âm, cho số $$\large0.1_{2} = 0.5_{10}$$ bây giờ muốn đưa về dạng $$\large1.xxxxx\times2^{N}$$, ta cần phải dịch dấu chấm sang phải một lần, ta có $$\large1.0_{2}$$ lúc này số mũ sẽ là `negative 1 (âm 1)` nên result là $$\large1.0_{2}\times2^{-1}$$

Bây giờ ta có $$\large1.0_{2}\times2^{-1}$$ tính ngược lại ta dùng phép chia, $$\large1.0_{2}\times2^{-1} = 1.0_{2}\div2 = 0.1_{2}$$ và nó đúng với số ban đầu vì sao? Vì $$\large2^{-1}=\frac{1}{2}$$ nên nhân với $$\large2^{-1}$$ tương đương chia cho 2

> [!IMPORTANT]
> nếu số mũ âm $$\large2^{-N}$$ ta dùng phép chia cho $$\large2^{N}$$, nếu số mũ dương $$\large2^{N}$$ ta dùng phép nhân cho $$\large2^{N}$$
>
> nếu dịch dot sang trái số mũ là **số dương** và dịch dot sang phải thì số mũ sẽ là **số âm**. Số mũ lớn dần khi số lần di chuyển dot nhiều hơn, lớn theo âm-dương ví dụ dương lớn dần sẽ là `1,2,3,4,..` còn âm lớn dần sẽ là `-1,-2,-3,-4,..`
>
> Trong IEEE 754 (đối với các số normalized), sau khi chuẩn hóa, biểu diễn luôn có dạng: $$\large1.xxxxx\times2^{N}$$ .Nghĩa là trước dấu chấm luôn chỉ có đúng một bit 1. Chính vì bit đầu tiên luôn là 1, IEEE 754 không cần lưu bit này vào bộ nhớ (hidden bit), chỉ lưu phần phía sau dấu chấm trong trường Fraction.

<details>
	<summary>tại sao phải chuẩn hóa số thực?</summary>

- Vì nếu ko chuẩn hóa mọi số thực sẽ có cùng value nhưng nhiều cách biểu diễn sẽ khác nhau ví dụ $$\large1001.1_{2}\times2^{1}$$, $$\large100.11_{2}\times2^{2}$$, $$\large10.011_{2}\times2^{3}$$, $$\large1.0011_{2}\times2^{4}$$. Cùng giá trị nhưng dịch dot khác biểu diễn. Nên IEEE quy định sử dụng dạng $$\large1.xxxxx\times2^{N}$$ để mỗi số chỉ có một biểu diễn duy nhất. Ngoài ra, vì bit đầu tiên luôn là 1, CPU không cần lưu bit này (gọi là hidden bit hoặc implicit leading 1), nhờ đó tăng thêm một bit độ chính xác cho trường Fraction.

</details>

#### 1.2.Trường dãy số sau dấu chấm (Fraction)

- Là trường số sau dấu chấm ví dụ `1.<m (Fraction)>`, nghĩa là sau khi chuẩn hóa số thực theo dạng IEEE quy định $$\large1.xxxxx\times2^{N}$$ thì sau dấu chấm có một binary strings dài đó gọi là fraction :

![alt text](image/image0.png)

#### 1.3.Trường số mũ (Exponent)

- là 

#### 1.3.1.Độ lệch (Bias)

- dạng có độ chính xác đơn tương ứng 32bit và dạng có độ chính xác kép tương ứng 64bit và kép mở rộng tương đương 80bit

#### 1.4.Trường số dấu (signed)

- Là trường chỉ tính `MSB = 1` hay `MSB = 0`, quyết định số âm hay dương. Ví dụ cho số thực `19.6875` nó sẽ chuyển thành 0 và 1 trong máy tính, bit dấu biểu diễn là âm hay dương với MSB, điều này đã nói rõ ở [two complement code](https://github.com/tranquanghao708/CSAPP-learning/blob/main/writeup/two-complement-code/two-complement-code.md) , ở trường số có dấu này người ta chỉ dùng 1bit để biểu diễn nó với MSB trong đa architecture