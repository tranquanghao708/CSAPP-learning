# CSAPP : Floating point numbers - IEEE 754 (số thực dấu phẩy động chuẩn IEEE 754)

> Ngày bắt đầu viết : 13/7/2026

> Ngày hoàn thành :

**mục lục**

- 1.Tổng quan về IEEE 754.

- [1.1.Chuẩn hóa số thực](#11Chuẩn-hóa-số-thực)

- 1.2.Trường Fraction (phần trị - significand)

- 1.3.Trường số mũ (Exponent)

- 1.3.1.Độ lệch (Bias)

- 1.4.Trường số dấu (signed)

- 1.5.Thiết lập và đếm bit phân cho S,E,m phù hợp với độ rộng toán hạng

- 2.Chuyển đổi số thực sang hệ nhị phân và chuyển đổi hệ nhị phân sang số thực

- 3.Những lỗi về số thực khi lập trình cấp thấp

- 4.Biểu diễn số thực trong bộ nhớ,sơ đồ

- 5.kết luận

---

## 1.Tổng quan về IEEE 754.

- `Số thực IEEE 754` là quy tắc biểu diễn số thực cho thiết bị nhị phân (máy tính) thế giới. **Formula tổng quan là** $$\Large(-1)^{S} \times 1.m \times 2^{e-b}$$, trong đó :

S : là bit dấu, viết tắt sign

m : hidden bit + fraction là phần trị (trường dãy số sau dấu chấm của số thực sau khi đã chuẩn hóa)

e : là giá trị của trường exponent

b : là độ lệch, viết tắt bias

- Ta có một structure của cái này như sau:

| S (sign) | E (Exponent) | m (Fraction) |
|----------|--------------|--------------|

#### 1.1.Chuẩn hóa số thực

- **chuẩn hóa là gì?** : giống toán học, **formula =**$$\large1.xxxxx\times2^{N}$$ **ví dụ** $$\large12345_{10}$$ = $$\large1.2345_{10}\times10^{4}$$ số mũ là 4 vì dịch dot sang trái 4 lần hoặc $$\large0.00123_{10}$$ = $$\large1.23\times10^{-3}$$ số mũ là -3 vì dịch dot sang phải 3 lần. Đó gọi là dạng chuẩn hóa

IEEE 754 cũng làm thế, cơ mà nó biểu diễn dạng binary và dùng cơ số 2. **Ví dụ**, $$\large13.25_{10} = 1101.01_{2}$$, di chuyển dấu chấm sao cho trước dấu chấm chỉ còn đúng một bit 1 ta có $$\large1.10101_{2}$$ số lần di chuyển là 3 vì :

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
> nếu dịch dot sang trái số mũ là **số dương** và dịch dot sang phải thì số mũ sẽ là **số âm**. Số mũ lớn dần khi số lần di chuyển dot nhiều hơn, lớn theo âm-dương **ví dụ** dương lớn dần sẽ là `1,2,3,4,..` còn âm lớn dần sẽ là `-1,-2,-3,-4,..`
>
> Trong IEEE 754 (đối với các số normalized), sau khi chuẩn hóa, biểu diễn luôn có dạng: $$\large1.xxxxx\times2^{N}$$ .Nghĩa là trước dấu chấm luôn chỉ có đúng một bit 1. Chính vì bit đầu tiên luôn là 1, IEEE 754 không cần lưu bit này vào bộ nhớ (hidden bit), chỉ lưu phần phía sau dấu chấm trong trường Fraction.

<details>
	<summary>tại sao phải chuẩn hóa số thực?</summary>

- Vì nếu ko chuẩn hóa mọi số thực sẽ có cùng value nhưng nhiều cách biểu diễn sẽ khác nhau **ví dụ** $$\large1001.1_{2}\times2^{1}$$, $$\large100.11_{2}\times2^{2}$$, $$\large10.011_{2}\times2^{3}$$, $$\large1.0011_{2}\times2^{4}$$. Cùng giá trị nhưng dịch dot khác biểu diễn. Nên IEEE quy định sử dụng dạng $$\large1.xxxxx\times2^{N}$$ để mỗi số chỉ có một biểu diễn duy nhất. Ngoài ra, vì bit đầu tiên luôn là 1, CPU không cần lưu bit này (gọi là hidden bit hoặc implicit leading 1), nhờ đó tăng thêm một bit độ chính xác cho trường Fraction.

</details>

#### 1.2.Trường Fraction (phần trị - significand)

- Là trường lưu các bit phía sau dấu chấm của số nhị phân sau khi đã chuẩn hóa số thực theo dạng chuẩn hóa $$\large1.xxxxx\times2^{N}$$:

![alt text](image/image0.png)

Trường Fraction quyết định precision (độ chính xác) của số thực. IEEE 754 càng dành nhiều bit cho trường Fraction thì càng biểu diễn được nhiều chữ số có nghĩa hơn. Lúc này, độ chính xác vì thế mà tăng. 

- **Điểm nhiều người nhầm :** Values trong fraction $$\large\neq$$ độ chính xác. Cái quyết định độ chính xác là số lượng bit được cấp cho trường Fraction

#### 1.3.Trường số mũ (Exponent)

- Là trường biểu diễn số mũ của số thực sau khi chuẩn hóa. Số mũ được xác định bằng số lần dịch dấu chấm để đưa số về dạng $$\large1.xxxxx\times2^{N}$$, **ví dụ** $$\large101.00110_{2} = 1.0100110_{2}$$ dịch chuyển dot sang trái 2 lần số mũ = 2 (dương), $$\large0.00110_{2} = 001.00110_{2} = 1.00110_{2}$$ dịch chuyển dot sang phải 3 lần số mũ = -3 (âm), rõ hơn đã nói trước ở [1.1.Chuẩn hóa số thực](#11Chuẩn-hóa-số-thực)

- Exponent đóng vai trò quyết định độ lớn của số thực, **ví dụ** $$\large1.11111_{10}\times2^{2} = 7.75_{10}$$ nhưng đổi giá trị số mũ  $$\large1.11111_{10}\times2^{10} = 1984_{10}$$ giá trị đổi, mặc dù fraction ko đổi

> [!IMPORTANT]
> Exponent quyết định độ lớn của số thực, tùy thuộc vào số mũ lớn nhỏ bao nhiêu
>
> Fraction quyết định chữ số có nghĩa (độ chính xác của số thực), tùy thuộc vào hệ thống cung cấp bao nhiêu bit cho nó
>
> **điều quan trọng** : Exponent quyết định scale (độ lớn) của số thực thông qua lũy thừa $$\large2^{N}$$ . Chỉ cần thay đổi Exponent một lượng nhỏ, giá trị của số thực có thể thay đổi rất lớn. Fraction thiên hướng về quyết định chữ số có nghĩa (độ chính xác của số thực) nhưng khi thay đổi các bit trong trường Fraction sẽ làm thay đổi giá trị của số thực, nhưng mức thay đổi thường nhỏ hơn nhiều so với việc thay đổi Exponent. **Precision (độ chính xác)** không phụ thuộc vào giá trị của Fraction mà phụ thuộc vào số lượng bit được **IEEE 754** cấp cho trường Fraction. **Ví dụ**, double có 52 bit Fraction nên biểu diễn số thực chính xác hơn float với 23 bit Fraction.

- **Điểm nhiều người nhầm :** Trường exponent ko lưu trực tiếp actual exponent (số mũ thực) ký hiệu `N` trong dạng chuẩn hóa $$\large1.xxxxx\times2^{N}$$ , giá trị của trường exponent được tính theo công thưc `Exponent Field = Actual exponent + Bias`.

#### 1.3.1.Độ lệch (Bias)

- dạng có độ chính xác đơn tương ứng 32bit và dạng có độ chính xác kép tương ứng 64bit và kép mở rộng tương đương 80bit

#### 1.4.Trường số dấu (signed)

- Là trường chỉ tính `MSB = 1` hay `MSB = 0`, quyết định số âm hay dương. **Ví dụ** cho số thực $$\large19.6875_{10}$$ nó sẽ chuyển thành 0 và 1 trong máy tính, bit dấu biểu diễn là âm hay dương với MSB, điều này đã nói rõ ở [two complement code](https://github.com/tranquanghao708/CSAPP-learning/blob/main/writeup/two-complement-code/two-complement-code.md) , ở trường số có dấu này người ta chỉ dùng 1bit để biểu diễn nó với MSB trong đa architecture