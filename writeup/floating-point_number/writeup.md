# CSAPP : Floating point numbers - IEEE 754 (số thực dấu phẩy động chuẩn IEEE 754)

> Ngày bắt đầu viết : 13/7/2026

> Ngày hoàn thành :

**mục lục**

**Phần trọng tâm**

- [1.Tổng quan về IEEE 754](#1tổng-quan-về-ieee-754)

    - [1.1.Chuẩn hóa số thực (normalized)](#11Chuẩn-hóa-số-thực-normalized)

    - [1.2.Khử chuẩn hóa số thực (Denormalized)](#12khử-chuẩn-hóa-số-thực-denormalized)

       - [1.2.1.Khi nào IEEE 754 sử dụng Normalized và Denormalized?](#12k1hi-nào-ieee-754-sử-dụng-normalized-và-denormalized)

    - [1.3.Vô hạn (infinity)](#13vô-hạn-infinity)

    - [1.4.không phải một số (NaN)](#14không-phải-một-số-nan)

       - [1.4.1.Quiet NaN (qNaN)](#141quiet-nan-qnan)

       - [1.4.2.Signaling NaN (sNaN)](#142signaling-nan-snan)

    - [1.5.zero](#15zero)

    - [1.6.scanf và các hàm lệnh đọc khác có thể đọc các chỉ thị nan, infinity](#16scanf-và-các-hàm-lệnh-đọc-khác-có-thể-đọc-các-chỉ-thị-nan-infinity)

    - [1.7.Trường Fraction (phần trị - significand)](#17trường-fraction-phần-trị---significand)

       - [1.7.1.Hidden Bit](#171hidden-bit)

       - [1.7.2.Trường hợp nếu actual exponent lớn hơn độ rộng trường fraction để dịch dấu chấm](#172trường-hợp-nếu-actual-exponent-lớn-hơn-độ-rộng-trường-fraction-để-dịch-dấu-chấm)

    - [1.8.Trường số mũ (Exponent)](#18trường-số-mũ-exponent)

       - [1.8.1.Độ lệch (Bias)](#181độ-lệch-bias)

    - [1.9.Trường số dấu (signed)](#19trường-số-dấu-signed)

- [2.Chuyển đổi số thực sang hệ nhị phân và chuyển đổi hệ nhị phân sang số thực](#2chuyển-đổi-số-thực-sang-hệ-nhị-phân-và-chuyển-đổi-hệ-nhị-phân-sang-số-thực)

    - [2.1.Encode](#21encode)

       - [2.1.1.Chuyển phần nguyên sang nhị phân](#211chuyển-phần-nguyên-sang-nhị-phân)

       - [2.1.2.Chuyển phần thập phân sang nhị phân](#212chuyển-phần-thập-phân-sang-nhị-phân)

       - [2.1.3.Chuẩn hóa số thực](#213chuẩn-hóa-số-thực)

       - [2.1.4.Tính Exponent Field](#214tính-exponent-field)

       - [2.1.5.Lấy Fraction](#215lấy-fraction)

       - [2.1.6.Ghép Sign | Exponent | Fraction](#216ghép-sign--exponent--fraction)

    - [2.2.Decode](#22decode)

       - [2.2.1.Tách Sign | Exponent | Fraction](#221tách-sign--exponent--fraction)

       - [2.2.2.Khôi phục Actual Exponent](#222khôi-phục-actual-exponent)

       - [2.2.3.Khôi phục Hidden Bit](#223khôi-phục-hidden-bit)

       - [2.2.4.Nhân với 2^Exponent](#224nhân-với-2exponent)

       - [2.2.5.Áp dụng Sign](#225áp-dụng-sign)

       - [2.2.6.Phân biệt giữa exponent để tính trọng số bit fraction và exponent biểu thị cho dịch dấu chấm](#226phân-biệt-giữa-exponent-để-tính-trọng-số-bit-fraction-và-exponent-biểu-thị-cho-dịch-dấu-chấm)

    - [2.3.Số thực lớn nhất và tính toán số thực lớn nhất (Largest finite)](#23số-thực-lớn-nhất-và-tính-toán-số-thực-lớn-nhất-largest-finite)

    - [2.4.Số thực chuẩn hóa nhỏ nhất và tính toán số thực chuẩn hóa nhỏ nhất (Smallest normalized)](#24số-thực-chuẩn-hóa-nhỏ-nhất-và-tính-toán-số-thực-chuẩn-hóa-nhỏ-nhất-smallest-normalized)

    - [2.5.Số thực khử chuẩn hóa nhỏ nhất và tính toán số thực khử chuẩn hóa nhỏ nhất (Smallest subnormal)](#25số-thực-khử-chuẩn-hóa-nhỏ-nhất-và-tính-toán-số-thực-khử-chuẩn-hóa-nhỏ-nhất-smallest-subnormal)

    - [2.6.Số thực lớn nhất trong miền khử chuẩn hóa (Largest subnormal)](#26số-thực-lớn-nhất-trong-miền-khử-chuẩn-hóa-largest-subnormal)

---

# Phần trọng tâm

## 1.Tổng quan về IEEE 754.

<p align="center">
	<image alt="alt text" src="image/image1.png" width="680"/>
</p>

> không phải CS:APP, tham khảo từ cuốn kiến trúc máy tính vì tính dễ hiểu về formula

Số thực IEEE 754 là quy tắc biểu diễn số thực cho thiết bị nhị phân (máy tính) thế giới. Công thức tổng quan với số thực chuẩn hóa là:

<div align="center">

$$\Large(-1)^{S} \times 1.m \times 2^{e-b}$$

</div>

- trong đó :

  S : là bit dấu, viết tắt sign

  m : hidden bit + fraction là phần trị (trường dãy số sau dấu chấm của số thực sau khi đã chuẩn hóa)

  e : là giá trị của trường exponent

  b : là độ lệch, viết tắt bias

Ta có một structure của cái này như sau:

<div align="center">

| S (sign) | E (Exponent) | m (Fraction) |
|----------|--------------|--------------|

</div>

### 1.1.Chuẩn hóa số thực (normalized)

<p align="center">
	<image alt="alt text" src="image/image2.png" width="680"/>
</p>

> Trích từ CS:APP

chuẩn hóa giống toán học, nó có công thức:

<div align="center">

$$\Large1.b_{1}b_{2}b_{3}b_{4}b_{5}\times2^{N}$$

</div>

**ví dụ** $$\large12345_{10}$$ = $$\large1.2345_{10}\times10^{4}$$ số mũ là 4 vì dịch dot sang trái 4 lần hoặc $$\large0.00123_{10}$$ = $$\large1.23\times10^{-3}$$ số mũ là -3 vì dịch dot sang phải 3 lần. Đó gọi là dạng chuẩn hóa

IEEE 754 cũng làm thế, cơ mà nó biểu diễn dạng binary và dùng cơ số 2. **Ví dụ**, $$\large13.25_{10} = 1101.01_{2}$$, di chuyển dấu chấm sao cho trước dấu chấm chỉ còn đúng một bit 1 ta có $$\large1.10101_{2}$$ số lần di chuyển là 3 vì :

```
lúc đầu : 1101.01
di chuyển dot 1 lần : 110.101
di chuyển dot 2 lần : 11.0101
di chuyển dot 3 lần : 1.10101
Tổng cộng dịch dấu chấm 3 lần để trước dấu chấm chỉ còn đúng một bit 1.
```

Vậy nên ta có số mũ là 3, suy ra $$\large1.10101_{2}\times2^{3}$$ và khi tính lại là $$\large1.10101_{2}\times2^{3} = 1101.01_{2}$$ ta thấy nó lại di chuyển về từ đầu. Vậy cho ví dụ khi số mũ âm, cho số $$\large0.1_{2} = 0.5_{10}$$ bây giờ muốn đưa về dạng $$\large1.b_{1}b_{2}b_{3}b_{4}b_{5}\times2^{N}$$, ta cần phải dịch dấu chấm sang phải một lần, ta có $$\large1.0_{2}$$ lúc này số mũ sẽ là `negative 1 (âm 1)` nên result là $$\large1.0_{2}\times2^{-1}$$

Bây giờ ta có $$\large1.0_{2}\times2^{-1}$$ tính ngược lại ta dùng phép chia, $$\large1.0_{2}\times2^{-1} = 1.0_{2}\div2 = 0.1_{2}$$ và nó đúng với số ban đầu vì sao? Vì $$\large2^{-1}=\frac{1}{2}$$ nên nhân với $$\large2^{-1}$$ tương đương chia cho 2

> [!IMPORTANT]
> nếu số mũ âm $$\large2^{-N}$$ ta dùng phép chia cho $$\large2^{N}$$, nếu số mũ dương $$\large2^{N}$$ ta dùng phép nhân cho $$\large2^{N}$$
>
> nếu dịch dot sang trái số mũ là **số dương** và dịch dot sang phải thì số mũ sẽ là **số âm**. Độ lớn tuyệt đối của số mũ (|N|) bằng số lần dịch dấu chấm. Dấu của số mũ phụ thuộc vào hướng dịch, nó lớn theo âm-dương **ví dụ** dương lớn dần sẽ là `1,2,3,4,..` còn âm nhỏ dần sẽ là `-1,-2,-3,-4,..`
>
> Trong IEEE 754 (đối với các số normalized), sau khi chuẩn hóa, biểu diễn luôn có dạng: $$\large1.b_{1}b_{2}b_{3}b_{4}b_{5}\times2^{N}$$ .Nghĩa là trước dấu chấm luôn chỉ có đúng một bit 1. Chính vì bit đầu tiên luôn là 1, IEEE 754 không cần lưu bit này vào bộ nhớ (hidden bit), chỉ lưu phần phía sau dấu chấm trong trường Fraction.

<details>
	<summary><b>[Câu hỏi]</b> tại sao phải chuẩn hóa số thực?</summary>

<table>
<tr>
<td>

---

<br>

- Vì nếu không chuẩn hóa mọi số thực sẽ có cùng value nhưng nhiều cách biểu diễn sẽ khác nhau **ví dụ** $$\large1001.1_{2}\times2$$, $$\large100.11_{2}\times2^{1}$$, $$\large10.011_{2}\times2^{2}$$, $$\large1.0011_{2}\times2^{3}$$. Cùng giá trị nhưng dịch dot khác biểu diễn. Nên IEEE quy định sử dụng dạng $$\large1.b_{1}b_{2}b_{3}b_{4}b_{5}\times2^{N}$$ để mỗi số chỉ có một biểu diễn duy nhất. Ngoài ra, vì bit đầu tiên luôn là 1, CPU không cần lưu bit này (gọi là hidden bit hoặc implicit leading 1), nhờ đó tăng thêm một bit độ chính xác cho trường Fraction.

<br>

<sub>— Hết phần giải thích —</sub>

---

</td>
</tr>
</table>
</details>

### 1.2.Khử chuẩn hóa số thực (Denormalized)

<p align="center">
	<image alt="alt text" src="image/image3.png" width="680"/>
</p>

> trích từ CS:APP

Là việc bit đầu tiên là 0 nhưng nó thực hiện phép toán $$\large0.b_{1}b_{2}b_{3}b_{4}b_{5}\times2^{1-bias}$$. **Lúc này** hiddenbit không còn là 1 nữa, nó là 0 và exponent field luôn là 0. Giả sử float (32bits) ta có :

```
Exponent = 00000000
Fraction = 00000000000000000000001
```

thì đây không phải là pattern $$\large1.0000000000_{2}\times2^{-127}$$ mà là $$\large0.0000000000000000000001_{2}\times2^{-126}$$ vì hiddenbit đã bằng 0. Với subnormal này nó có công thức sau:

<div align="center">

$$\Large(-1)^{S}\times0.f\times2^{1-bias}$$

</div>

> [!NOTE]
> **Lưu ý:** `actual exponent = -127` của $$\large1.0000000000_{2}\times2^{-127}$$ là do `actual exponent = E - bias` suy ra `0 - 127 = -127` vì E là viết tắt của exponent field vầ trường hợp này với số chuẩn hóa exponent field là 0. Còn với số khử chuẩn hóa luôn dùng `actual exponent = 1 - bias` nên `1 - 127 = -126` nên mới có biểu thức $$\large0.0000000000000000000001_{2}\times2^{-126}$$

**Vậy vì sao phải làm như vậy?**, ta biết normalized nó sẽ có bit đầu luôn là 1, exponent của nó là dương hay âm tùy thuộc vào cách dịch dấu chấm là trái hay phải ,nhưng điều gì sẽ xảy ra nếu số thực cực kỳ nhỏ **ví dụ** $$\large2^{-150}$$ hay $$\large0.000000000000000000000001_{2}$$, nếu vẫn cố chuẩn hóa về $$\large1.xxxxx\times2^{N}$$ thì kết quả sẽ bị underflow tức là bị làm tròn thành 0

> [!IMPORTANT]
> Đối với normalized numbers, IEEE754 dùng $$\large1.xxxxx\times2^{N}$$ nên số đầu tiên luôn là 1 (hiddenbit = 1)
>
> Còn với Denormalized numbers, IEEE754 dùng $$\large0.xxxxx\times2^{1 - Bias}$$ nên `exponent field = 0` và hiddenbit được xem là 0. Khử chuẩn hóa được thiết kế để biểu diễn với số gần 0 nhất **tránh bị underflow** quá sớm (hiddenbit = 0)

#### 1.2.1.Khi nào IEEE 754 sử dụng Normalized và Denormalized?

- `Normalized` được ưu tiên khi biểu diễn số thực vì dạng này tận dụng hiddenbit, giúp tăng thêm một bit chính xác, dùng cho hầu hết các số thực 

- Nếu `normalized` không biểu diễn được nhưng vẫn còn nằm trong phạm vi **subnormal** mới được chọn tới `denormalized` để biểu diễn các số sát `0` nhất có thể. Tuy nhiên độ chính xác sẽ thấp hơn, dùng cho số rất nhỏ gần sát `0`

> [!IMPORTANT]
> `Normalized` được IEEE ưu tiên vì độ chính xác cao hơn, tận dụng hiddenbit với dạng $$\large1.xxxxx\times2^{N}$$. Nhưng nếu số quá nhỏ cần phải dùng tới `Denormalized` với dạng $$\large0.xxxxx\times2^{1 - bias}$$ , điều này giúp biễu diễn các số sát `0` nhất có thể, tuy nhiên độ chính xác thấp hơn.
>
> Nếu `Denormalized` không thể sử dụng được nữa (nhỏ hơn cả subnormal nhỏ nhất) thì gía trị số thực sẽ bị underflow và kết quả sẽ thành `0`

### 1.3.Vô hạn (infinity)

<p align="center">
	<image alt="alt text" src="image/image4.png" width="680"/>
</p>

> Trích từ CS:APP

- Trong IEEE chuẩn còn định nghĩa là dương vô cực ($$\large+\infty$$) và âm vô cực ($$\large-\infty$$), infinity xuất hiện khi kết quả của một phép tính vượt quá phạm vi biểu diễn của kiểu số thực. **Ví dụ** biểu thức cho float (32bits) $$\large\approx3.4028235\ldots\times10^{38}\times10 = +\infty$$ với giá trị của biểu thức vừa rồi lớn hơn giá trị float lớn nhất (số thực lớn nhất) nên nó sẽ là dương vô cực ($$\large+\infty$$) vì `sign = 0` là số dương. Phần số thực lớn nhất ở mục [2.3.Số thực lớn nhất và tính toán số thực lớn nhất (Largest finite)](#23số-thực-lớn-nhất-và-tính-toán-số-thực-lớn-nhất-largest-finite))

- IEEE 754 quy định Infinity có dạng:

<div align="center">

| Sign | Exponent | Fraction |
|------|----------|----------|
| 0 hoặc 1 | Toàn bộ bit = 1 | Toàn bộ bit = 0 |

</div>

nếu `sign = 0` : dương vô cực $$\large+\infty$$

nếu `sign = 1` : âm vô cực $$\large-\infty$$

> [!IMPORTANT]
>
> Infinity **không phải là số lớn nhất** mà là một giá trị đặc biệt dùng để biểu diễn kết quả vượt quá phạm vi của kiểu số thực.
>
> Điều kiện nhận biết Infinity là:
>
> - Exponent Field = tất cả bit 1.
> - Fraction = tất cả bit 0.

<details>
	<summary><b>[Chi tiết]</b> ví dụ với C</summary>

<table>
<tr>
<td>

---

<br>

- Cho đoạn C sau :

```c
#include <stdio.h>

int main(void){
	float a = 1e39f;
	printf("%f\n",a);
	return 0;
}
```

> gcc -o float_infinity float_infinity.c

khi compiled ra ta thấy compiler nó cảnh baó với info `warning: floating constant exceeds range of ‘float’ [-Woverflow]` đó là chúng ta cần test, bây giờ chạy thử :

<p align="center">
	<image alt="alt text" src="image/image5.png" width="680"/>
</p>

ta thấy hiện `inf` nghĩa là dương vô cực $$\large+\infty$$

<br>

<sub>— Hết phần giải thích —</sub>

---

</td>
</tr>
</table>
</details>

### 1.4.không phải một số (NaN)

#### 1.4.1.Quiet NaN (qNaN)

<p align="center">
	<image alt="alt text" src="image/image6.png" width="680"/>
</p>

> trích từ CS:APP

- là một giá trị đặc biệt, chỉ thị cho không xác định hoặc số đó không phải là số thực $$\large\frac{0}{0} = \text{NaN}$$, $$\large\infty-\infty=\text{NaN}$$, $$\large\sqrt{-1}=\text{NaN}$$ (đối với số thực). IEEE 754 quy định NaN có dạng như :

<div align="center">

| Sign | Exponent | Fraction |
|------|----------|----------|
| 0 hoặc 1 | Toàn bộ bit = 1 | Khác 0 |

</div>

Nghĩa là Exponent phải là tòan bộ bit là một và Fraction phải có ít nhất một bit khác 0 cấu trúc như trong image trên từ CS:APP

> [!IMPORTANT]
> NaN chỉ xảy ra khi exponent toàn bộ bit phải là 1 và fraction $$\large\neq$$ 0
>
> Điểm cần phân biệt :
> - Fraction = 0 : infinity ($$\large+\infty$$, $$\large-\infty$$)
> - Fraction $$\large\neq$$ 0 : NaN

NaN có tính chất đặc biệt là **không bằng bất kỳ giá trị nào kể cả chính nó**, trong dãy fraction phần bit có trọng số cao nhất của dãy bit fraction là `Quiet bit` minh họa với 32bit(float) :

<p align="center">
	<image alt="alt text" src="image/image20.png" width="680"/>
</p>

Trong đó QuietBit là phần có thể là `0` hoặc `1`, khi quiet bit là `1` thì đó gọi là Quiet NaN là cái mà chúng ta đang nói ở chương này, còn khi QuietBit là `0` thì đó gọi là Signaling NaN (sNaN), là cái mà chúng ta sẽ nói ở chương [1.4.2.Signaling NaN (sNaN)](#142signaling-nan-snan) tiếp theo

> [!IMPORTANT]
> Bit có trọng số cao nhất trong dãy fraction luôn là quiet bit (khi toàn bộ bit kế tiếp đều là 1) thỏa điều kiện để xem đó là NaN:
> - nếu quiet bit = 1 đó là qNaN (quiet NaN)
> - nếu quiet bit = 0 đó là sNaN (Signaling NaN)

<details>
	<summary><b>[Chi tiết]</b> Ví dụ với C</summary>

<table>
<tr>
<td>

---

<br>

- Cho đoạn C sau :

```c
#include <math.h>
#include <stdio.h>

int main(void){
	double x = NAN;
	printf("double NaN x == x is : %d\n",x == x); // kết quả là 0
	printf("double NaN x != x is : %d\n",x != x); // kết quả là 1
	printf("double NaN x < x is : %d\n",x < x); // kết quả là 0
	printf("double NaN x > x is : %d\n",x > x); // kết quả là 0
	return 0;
}
```

> gcc -o Double_NaN Double_NaN.c

<p align="center">
	<image alt="alt text" src="image/image7.png" width="680"/>
</p>

**Vì sao nó lại ra 0?:** Theo chuẩn IEEE 754, mọi phép so sánh bằng (==) với NaN đều trả về false, kể cả khi so sánh chính nó. `0` và `1` được xem làm gía trị boolean true false trong việc này. Ở đây so sánh `x == x` vốn dĩ x lại là NaN nên giá trị là `False = 0`. Điều này cũng như vậy với phép so sánh khác như lớn hơn, bé hơn, lớn hơn hoặc bằng và bé hơn hoặc bằng trừ các hàm chuyên biệt như `isnan()`

Điều này khiến việc kiểm tra NaN phải dùng hàm `isnan()` trong `<math.h>` thay vì toán tử `==`.

<br>

<sub>— Hết phần giải thích —</sub>

---

</td>
</tr>
</table>
</details>

Nếu trong condition ta thấy `if(x != x)` thì điều đó chỉ đúng khi `x = NaN` vì NaN là thứ duy nhất giúp `x != x` trả true. Đây là một mẹo thường gặp trong các câu hỏi về C, compiler và IEEE 754. Vì NaN là giá trị duy nhất mà biểu thức `x != x` luôn đúng, một số mã nguồn hoặc trình biên dịch có thể dùng tính chất này để phát hiện NaN.

#### 1.4.2.Signaling NaN (sNaN)

Đây cũng là loại bit đặc biệt NaN chỉ khác với qNaN là nó dùng để báo hiệu rằng chương trình vừa sử dụng một giá trị không hợp lệ hoặc chưa được khởi tạo. Khác với quiet NaN, sNaN không âm thầm lan truyền, mà sẽ cố gắng tạo ra một floating-point invalid exception ngay khi được sử dụng trong phép toán.

IEEE quy định sNaN phải thỏa điều kiện xảy ra NaN là exponent field phải hết tất cả bit đều là 1, và fraction phải khác 0 tuy nhiên sNaN nên quiet bit là 0 đó là điều kiện để xảy ra sNaN.

> [!IMPORTANT]
> sNaN được tạo ra để phát hiện lỗi sớm. Khi CPU hoặc FPU sử dụng sNaN trong một phép toán, chuẩn IEEE 754 cho phép phần cứng phát sinh Invalid Operation Exception. Sau đó, trên nhiều kiến trúc, giá trị này sẽ được chuyển thành Quiet NaN (qNaN) để tiếp tục lan truyền qua các phép tính tiếp theo.

<details>
	<summary><b>[Chi tiết]</b> ví dụ sNaN với C</summary>

<table>
<tr>
<td>

---

<br>

```c
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(void){
    uint32_t raw = 0x7F800001; // sNaN (theo IEEE754)
    float x;
    memcpy(&x, &raw, sizeof(x));
    printf("%f\n", x);
    return 0;
}
```

<p align="center">
	<image alt="alt text" src="image/image21.png" width="680"/>
</p>

Khác với NAN (thường là Quiet NaN), ngôn ngữ C không cung cấp sẵn một hằng Signaling NaN. Muốn tạo sNaN, lập trình viên phải xây dựng trực tiếp mẫu bit IEEE754 (bit pattern) bằng các kỹ thuật như memcpy hoặc union. Tuy nhiên, trên nhiều hệ thống, sNaN sẽ nhanh chóng được phần cứng chuyển thành Quiet NaN khi tham gia phép toán.

<br>

<sub>— Hết phần giải thích —</sub>

---

</td>
</tr>
</table>
</details>

### 1.5.Zero

trong toán học giá trị `0` gần như bằng nhau nhưng trong biểu diễn số thực chuẩn IEEE754 dạng bit nhị phân nó lại biểu diễn khác ở phần sign. Ví dụ float (32bit) khi ta gắn gía trị `-0` thì biễu diễn tất cả các bit là 0 trừ sign là 1, nhưng gắn giá trị `+0` thì biễu diễn tất cả các bit là 0 và sign cũng không ngoại lệ. $$\large\pm0$$ trong biểu diễn số thực ở máy tính là âm hay dương tùy vào sign là 1 hay 0

> [!IMPORTANT]
> Trong IEEE biểu diễn dưới dạng bit thì giá trị `0` :
> - Exponent = 0
> - Fraction = 0
> - Sign = 1 hoặc 0

dù vậy nhưng nó vẫn quy định `+0 == -0` vẫn phải True. Tuy nhiên trong một phép toán, dấu của số 0 vẫn đươc bảo toàn ví dụ như $$\large\frac{1}{+0}=+\infty$$ hay $$\large\frac{1}{-0}=-\infty$$ . Nhờ vậy, CPU vẫn có thể xác định hướng mà một giá trị tiến tới 0 trong nhiều phép tính số học.

**Vì sao nó phải làm vậy?:** Ở đây, $$\large x -> 0^{-}$$ (tiến tới 0 từ phía âm) và $$\large x -> 0^{+}$$ (tiến tới 0 từ phía dương). Và trong giải tích hai giới hạn này khác nhau ở nhiều hàm ví dụ $$\large\frac{1}{x}$$ ở đây khi x tiến tới 0 từ phía âm ($$\large x -> 0^{-}$$) thì giá trị sẽ là âm vô hạn ($$\large-\infty$$) còn nếu khi x tiến tới 0 từ phía dương ($$\large x -> 0^{+}$$) thì giá trị sẽ là dương vô hạn ($$\large+\infty$$) IEEE quy định giữ lại dấu của giá trị `0` để phần cứng có thể phân biệt hai trường hợp này và cho ra kết quả đúng

<details>
	<summary><b>[Chi tiết]</b> ví dụ với C</summary>

<table>
<tr>
<td>

---

<br>

- cho đoạn C sau :

```c
#include <stdio.h>

int main(void){
	float x = 1 / 0; //chia cho +0
	float y = 1 / -0; // chi cho -0

	printf("1 / +0: %f\n 1 / -0: %f\n",x,y);
	return 0;
}
```

> gcc -o zero zero.c

<p align="center">
	<image alt="alt text" src="image/image8.png" width="680"/>
</p>

ta thấy khi runtime program, nó trả SIGFPE vậy lỗi này không phải SIGSEGV (truy cập vaddr không hợp lệ) **vậy nó là gì?**, tuy nó là có tên gọi là Floating-Pointing (FP) số thực dấu phẩy động nhưng thực chất lỗi này đại diện cho tất cả phép toán không phù hợp kể cả các lỗi tràn số (overflow) nghiêm trọng hoặc dùng phép tính như chia cho 0, căn bậc hai của một số âm mà không dùng thư viện số phức hay kết quả tính toán số thực không xác định. Ta cần sửa lại đoạn C thành:

```c
#include <stdio.h>

int main(void){
	float x = 1.0f / 0.0f; //chia cho +0
	float y = 1.0f / -0.0f; // chi cho -0

	printf("1 / +0: %f\n 1 / -0: %f\n",x,y);
	return 0;
}
```

<p align="center">
	<image alt="alt text" src="image/image9.png" width="680"/>
</p>

Đây là kết quả chính xác của phép $$\large x -> 0^{-} = -\infty$$ (tiến tới 0 từ phía âm) và $$\large x -> 0^{+} = +\infty$$ (tiến tới 0 từ phía dương) và $$\large\frac{1}{-0} = -\infty$$, $$\large\frac{1}{+0} = +\infty$$

**Vì sao khi chia cho 0 ở số thực này nó lại không bắn SIGFPE?:** Vì đây là phép chia dấu phẩy động CPU sẽ dùng FPU/SSE (divss, divsd,.. ) để thực hiện điều đó là tập lệnh phù hợp cho phép chia trong trường hợp này nên nó sẽ không gây ra lỗi gì

Lưu ý: trong C, phép chia số nguyên cho 0 trong C là undefined behavior (UB), trên linux CPU thực hiện lệnh idiv hoặc div và phần cứng sinh lỗi divide error exception nếu (#DE) nếu thấy chia cho 0 và kernel nhận exception này rôi gửi SIGFPE

<br>

<sub>--đã hết phần giải thích--</sub>

---

</td>
</tr>
</table>
</details>

### 1.6.scanf và các hàm lệnh đọc khác có thể đọc các chỉ thị nan, infinity

Trong C, các hàm như scanf có thể đọc các chỉ thị nan, infinity không chỉ là số thực. **Ví dụ** đọc dữ liệu đầu vào bằng `scanf()` và gán cho số thực, nó không chỉ đọc số thực nó còn đọc cả `nan, NaN, NAN, +nan, -nan, inf, infinity, -INF`. phần ví dụ có thể xem [tại đây](https://github.com/tranquanghao708/Solve-CaptureTheFlags/blob/main/thecommenter/chall12/writeup.md)

### 1.7.Trường Fraction (phần trị - significand)

- Là trường lưu các bit phía sau dấu chấm của số nhị phân sau khi đã chuẩn hóa số thực theo dạng chuẩn hóa $$\large1.b_{1}b_{2}b_{3}b_{4}b_{5}\times2^{N}$$:

<p align="center">
	<image alt="alt text" src="image/image0.png" width="680"/>
</p>

Trường Fraction quyết định precision (độ chính xác) của số thực. IEEE 754 càng dành nhiều bit cho trường Fraction thì càng biểu diễn được nhiều chữ số có nghĩa hơn. Lúc này, độ chính xác vì thế mà tăng. 

- **Điểm thường bị nhầm :** Values trong fraction $$\large\neq$$ độ chính xác. Cái quyết định độ chính xác là số lượng bit được cấp cho trường Fraction

#### 1.7.1.Hidden Bit

Hidden Bit giúp IEEE 754 chỉ lưu 23 bit fraction (float) nhưng lại đạt độ chính xác tương đương 24 bit, hay 52 bit (double) nhưng tương đương 53 bit. Trong số thực IEEE 754 chuẩn hóa (Normalized), bit 1 đứng trước dấu chấm nhị phân không được lưu vào bộ nhớ. Bit này được phần cứng tự động khôi phục khi thực hiện tính toán, nên được gọi là Hidden Bit, Implicit Leading Bit hoặc Implicit 1.

Sự phân biệt giữa hiddenbit và sign bit, khi nhắc tới đứng trước dấu chấm điều dễ nhầm nhất là hai khái niệm sign bit và hiddenbit tuy nhiên chúng không phải chung một khái niệm, phân biệt hidden bit khi thấy bit đứng trước dấu chấm (phải có dấu chấm) đối với số chuẩn hóa mới gọi là hidden bit còn phân biệt sign bit khi thấy bit không đứng trước dấu nào mà là bit MSB (bit có trọng số cao nhất) sau khi thực hiện ráp lại theo cấu trúc `sign | exponent | fraction` chuẩn IEEE đó mới gọi là sign bit. Tuy hai bit đều có độ rộng là 1 bit nhưng về mặt lý thuyết và kỹ thuật chúng phục vụ cho mục đích khác nhau

mục đích của hidden bit là giúp tăng độ chính xác của số thực, ví dụ nó lưu 23bit fraction float nhưng có độ chính xác tương đương với 24bit, điều này giúp tăng độ chính xác cao hơn. Còn mục đích của sign bit là giúp biểu diễn số thực là âm hay dương (Hai khái niệm này cần phân biệt rõ)

Bây giờ để hiểu rõ hiddenbit hơn ta cho **ví dụ** $$\large1.101001_{2}​\times2^{5}$$ trong bộ nhớ IEEE nó không lưu hiddenbit (bit trước dấu chấm) nó chỉ lưu phần phía sau dấm chấm (phần fraction) Khi FPU đọc giá trị này (giá trị trong bộ nhớ), phần cứng sẽ tự thêm lại bit 1 lúc đso nó lại thành $$\large1.101001_{2}$$ do đó gía trị dung để tính toán là $$\large1.101001_{2}​\times2^{5}$$

**Vì sao IEEE không lưu hiddenbit?**

mục đích chính là không lãng phí một bit luôn luôn bằng 1, vì khi đối với số thực đã chuẩn hóa thì hidden bit luôn là 1 và nó không bao giờ bằng 0 nếu lưu bit này sẽ lãng phí 1 bit nên IEEE quy định không lưu bit 1 đầu tiên, khi cần sử dụng thì FPU sẽ tự thêm lại. Thực chất hiddenbit không tự động là giúp số thực chính xác hơn tương đương với hơn một bit, cái làm tăng chính xác là khi đưa vào bộ nhớ hiddenbit bị loại bỏ và dùng vùng đó cho các bit có tác dụng, hidden bit chỉ phục vụ cho việc tính toán

Nhưng hidden bit không phải lúc nào cũng bằng 1, nó chỉ đúng với số khi chuẩn hóa (normalized) nhưng đối với số khử chuẩn hóa (denormalized) hidden bit là 0 còn với giá trị đặc biệt như nan hay infinity thì chúng không có hiddenbit đối với `hiddenbit = 0`, cho **ví dụ** số thực có dạng $$\large0.fraction\times2^{1-bias}$$ và `fraction = 100100... , exponent = 00000000` thì lúc này các kết quả số thực sẽ có dạng `0.100100...` chứ không phải `1.100100...`. Đây gọi là [khử chuẩn hóa số thực (Denormalized)](#12khử-chuẩn-hóa-số-thực-denormalized) là cơ chế giúp IEEE 754 biểu diễn được các số rất nhỏ gần bằng 0 mà không bị nhảy đột ngột từ số chuẩn hóa nhỏ nhất xuống 0.

<div align="center">

| Loại số                  | Hidden Bit    |
| ------------------------ | ------------- |
| Normalized               | 1 (Implicit)  |
| Denormalized (Subnormal) | 0             |
| Infinity                 | Không sử dụng |
| NaN                      | Không sử dụng |

</div>

#### 1.7.2.Trường hợp nếu actual exponent lớn hơn độ rộng trường fraction để dịch dấu chấm

Cho `actual exponent = 127`. Điều này có nghĩa khi khôi phục giá trị số thực, dấu chấm nhị phân phải được dịch sang phải `127` vị trí. Tuy nhiên, trường Fraction của float chỉ lưu 23 bit. Điều này dễ khiến người học nhầm rằng cần phải tạo ra một trường Fraction dài 127 bit, nhưng thực tế không phải vậy.

Chúng ta cần dịch dấu chấm bằng cách thêm các padding 0 cho những phần cần thiếu, nghĩa là chúng ta cứ việc dịch dấu chấm ở fraction trước đến khi dấu chấm vượt quá độ rộng của trường fraction khi đó chúng ta mới thêm dấu chấm sao cho dịch đủ `127` vị trí theo giá trị của actual exponent là được.

**Ví dụ** cho độ rộng trường fraction là 3 và actual exponent là 9, ta có `1.101` bây giờ ta dịch dấu chấm ở fraction sang bên phải 9 vị trí dịch trước 2 vị trí là dịch dấu chấm sao cho nó tới phần cuối cùng như `110.1` bây giờ ta thấy nó gần sắp vượt quá độ rộng của trường fraction. Bây giờ ta tiến hành thêm padding 0 vào và dịch sao cho đủ 9 vị trí (theo actual exponent), ta có $$\large\boxed{1101000000.0_{2}}$$ vậy là đủ 9 ô thỏa mãn actual exponent

> [!NOTE]
> kết quả $$\large1101000000.0_{2}$$ có thể bỏ `.0` ở cuối đi cũng ko sao, vì $$\large1101000000_{2}$$ cũng đúng

**vậy việc thêm padding thỏa mãn actual exponent có làm vi phạm độ rộng của trường fraction?**

Ví dụ trường fraction của float là 23bit, nhưng việc thêm padding vô tình làm chuỗi nhị phân lớn hơn 23bit với các bit zero. Tuy nhiên về cơ bản padding chúng không làm trường fraction vượt quá 23 bit, nếu phân biệt đúng giữa chuỗi biểu diễn trung gian và field fraction thực sự được lưu trong IEEE 754. Chúng ta cần phân biệt :

**Số nhị phân thực tế**

Nó có thể dài vô hạn, ko bị giới hạn bởi 23bit **ví dụ** như $$\large1.101101001011100001010001101\ldots_{2}$$

**Significand dùng khi chuẩn hóa/rounding**

ví dụ $$\large1.101101001011100001010001101\ldots_{2}$$ và có thể giữ thêm các bit sau để quyết định rounding

**Fraction field**

ví dụ :

$$\Large
\underbrace{10110100101110000101000​}_{\text{23bit fraction field}}
$$

Phần `1.` phía trước không được lưu, vì với số normalized nó là hidden bit.

**Padding trong quá trình biểu diễn trung gian**

đây là yếu tố góp một phần ở chương này, cũng là yếu tố khá dễ nhầm . Ở đây, ta cần phân tách riêng cho nó hai trường hợp, với chuỗi nhị phân có độ rộng nhỏ hơn độ rộng fraction field, và với chuỗi nhị phân có độ rộng lớn hơn độ rộng fraction field. Đối với chuỗi nhị phân có độ rộng nhỏ hơn độ rộng fraction field ví dụ $$\large1.11010_{2}$$ (có 5bit fraction) để có thể lắp đầy độ rộng của trường fraction ta cần thêm zero vào (đây cũng là kỹ thuật đã nói ở phần đầu tiên) sao cho lắp đầy đủ 23bit

nếu trường hợp độ rộng của chuỗi nhị phân lớn hơn độ rộng của trường fraction, ta thực hiện cắt và làm tròn. **Ví dụ** $$\large1.1101011010110101101011010_{2}$$ (có 25bit fraction) ta thực hiện cắt 2 bit dư đi ta được $$\large1.11010110101101011010110_{2}$$ và rounding

> [!NOTE]
> Với $$\large1.1101011010110101101011010_{2}$$ (25 bit fraction), CPU giữ 23 bit đầu làm Fraction Field. Hai bit còn lại cùng các bit phía sau (nếu có) sẽ được dùng để quyết định việc rounding theo chuẩn IEEE 754.

**Điểm quan trọng cần phân biệt:** Actual Exponent quyết định số lần dịch dấu chấm của giá trị số thực, còn Fraction Field chỉ quyết định số lượng bit được lưu trong bộ nhớ. Chuỗi nhị phân dùng trong quá trình chuẩn hóa hoặc khôi phục giá trị có thể dài hơn rất nhiều 23 bit, nhưng khi lưu vào float32, trường Fraction luôn chỉ chứa đúng 23 bit. Nếu số bit sau dấu chấm ít hơn 23 thì CPU thêm các bit 0 để lấp đầy; nếu nhiều hơn 23 thì các bit vượt quá sẽ được dùng để thực hiện rounding theo chuẩn IEEE 754.

**Tóm lại:** Padding để đủ 23 bit thì được. Nhưng padding không được phép làm thay đổi số bit mà field fraction chứa. Vì thế nó ko làm trường fraction vượt quá 23bit

### 1.8.Trường số mũ (Exponent)

- Là trường biểu diễn số mũ của số thực sau khi chuẩn hóa. Số mũ được xác định bằng số lần dịch dấu chấm để đưa số về dạng $$\large1.b_{1}b_{2}b_{3}b_{4}b_{5}\times2^{N}$$, **ví dụ** $$\large101.00110_{2} = 1.0100110_{2}$$ dịch chuyển dot sang trái 2 lần số mũ = 2 (dương), $$\large0.00110_{2} = 001.00110_{2} = 1.00110_{2}$$ dịch chuyển dot sang phải 3 lần số mũ = -3 (âm), rõ hơn đã nói trước ở [1.1.Chuẩn hóa số thực (normalized)](#11Chuẩn-hóa-số-thực-normalized)

- Exponent đóng vai trò quyết định độ lớn của số thực, **ví dụ** $$\large1.11111_{2}\times2^{2} = 7.875_{10}$$ nhưng đổi giá trị số mũ  $$\large1.11111_{2}\times2^{10} = 2016_{10}$$ giá trị đổi, mặc dù fraction không đổi

> [!IMPORTANT]
> Exponent quyết định độ lớn của số thực, tùy thuộc vào số mũ lớn nhỏ bao nhiêu
>
> Fraction quyết định chữ số có nghĩa (độ chính xác của số thực), tùy thuộc vào hệ thống cung cấp bao nhiêu bit cho nó
>
> **điều quan trọng** : Exponent quyết định scale (độ lớn) của số thực thông qua lũy thừa $$\large2^{N}$$ . Chỉ cần thay đổi Exponent một lượng nhỏ, giá trị của số thực có thể thay đổi rất lớn. Fraction thiên hướng về quyết định chữ số có nghĩa (độ chính xác của số thực) nhưng khi thay đổi các bit trong trường Fraction sẽ làm thay đổi giá trị của số thực, nhưng mức thay đổi thường nhỏ hơn nhiều so với việc thay đổi Exponent. **Precision (độ chính xác)** không phụ thuộc vào giá trị của Fraction mà phụ thuộc vào số lượng bit được **IEEE 754** cấp cho trường Fraction. **Ví dụ**, double có 52 bit Fraction nên biểu diễn số thực chính xác hơn float với 23 bit Fraction.

- **Điểm thường bị nhầm :** Trường exponent không lưu trực tiếp actual exponent (số mũ thực) ký hiệu `N` trong dạng chuẩn hóa $$\large1.b_{1}b_{2}b_{3}b_{4}b_{5}\times2^{N}$$ , giá trị của trường exponent được tính theo công thưc `Exponent Field = Actual exponent + Bias`.

#### 1.8.1.Độ lệch (Bias)

- Bias là một giá trị cố định được cộng vào mọi actual exponent, không phân biệt âm hay dương, trước khi lưu vào trường Exponent. **Ví dụ** với float 32bit, exponent là 8bit nhưng bias = $$\large2^{8-1}-1 = 127_{10}$$, là Tmax của exponent (8 bit), nếu `exponent = 3` thì thực hiện phép cộng $$\large3_{10} + 127_{10} = 130_{10}$$ CPU sẽ lưu $$\large10000010_{2}$$ hệ không dấu , còn nếu `exponent = -3` thì thực hiện phép cộng $$\large (-3) + 127 = 124_{10}$$ CPU sẽ lưu $$\large01111100_{2}$$ hệ không dấu, còn nếu muốn recover lại số `-3` thì tính ngược lại với phép trừ là $$\large124 - 127 = -3_{10}$$ lúc này sẽ là chính xác số âm được biểu diến lúc đầu

> [!NOTE]
> Công thức tính BIAS nếu biết bit của actual exponent thì dùng formula tính tmax như sau $$\large2^{N-1}-1$$ **ví dụ** exponent field của double (64bit) là 11bit thì $$\large2^{11-1}-1 = 1023$$

**Điều dễ nhầm khi học Bias này:** là cách CPU nó lưu values, với bias biểu diễn số thực IEEE 754 **ví dụ** khi exponent field (11bit) của kiểu double(64bit) khi tính phải lấy giá trị exponent cộng với bias khi biểu diễn số dương (quy tắc encode) và trừ với bias khi chuyển đổi lại sang âm (quy tắc decode) , **ví dụ** giá trị `exponent = 6` vì dịch dấu chấm sang trái 6 lần nhưng tính thì $$\large6_{10} + 2^{11-1}-1 = 6_{10} + 1023_{10} = 1029_{10}$$ và CPU sẽ lưu giá trị `1029` dạng mã nhị phân thay vì lưu trực tiếp giá trị 6. Còn **ví dụ** về số âm, `exponent = -7` vì dịch dấu chấm sang phải 7 lần thì $$\large-7_{10} + 1023_{10} = 1016_{10}$$ CPU sẽ lưu gía trị `1016` với nhị phân, thay vì lưu trực tiếp `-7`. Còn muốn phục hồi về `-7` thì nó sẽ dùng $$\large1016_{10} - 1023_{10} = -7_{10}$$

<details>
	<summary><b>[Câu hỏi]</b> vì sao IEEE 754 không dùng two_complement_code để biểu diễn số âm cho bias?</summary>

<table>
<tr>
<td>

---

<br>

- Nếu dùng two_complement_code cho bias, thì $$\large-1_{10}$$ sẽ là $$\large111111_{2}$$ và nó sẽ khá phức tạp, khó so sánh thứ tự. Nên IEEE 754 quy định mọi biểu diễn số âm trong số thực chuẩn đều được biểu diễn là dương và thực hiện phép cộng cho Tmax của exponent, vì thế thiết kế phần cứng và nhiều thứ sẽ được đơn giản hóa hơn so với việc phức tạp hóa vấn đề không cần thiết

<br>

<sub>--đã hết phần giải thích--</sub>

---

</td>
</tr>
</table>
</details>

- dạng có độ chính xác đơn tương ứng 32bit và dạng có độ chính xác kép tương ứng 64bit và kép mở rộng tương đương 80bit :

<div align="center">

| name                 | Tổng số bit | Exponent | Fraction |  Bias |
| ------------------- | :----------: | :-------: | :-------: | :----: |
| Single precision    |          32 |        8 |       23 |   127 |
| Double precision    |          64 |       11 |       52 |  1023 |
| Quadruple precision |         128 |       15 |      112 | 16383 |

</div>

IEEE 754 quy định các pattern phổ biến như bảng

**Khái niệm chính xác đơn (Single precision) và chính xác kép (Double precision) là gì?:** kiểu chính xác đơn là kiểu số thực IEEE dài 32bit ví dụ float, còn chính xác kép là kiểu IEEE dài 64bit ví du double vì trong lịch sử tên gọi đơn biểu thị cho độ chính xác ban đầu và kép biểu thị cho gấp đôi độ chính xác ban đầu

### 1.9.Trường số dấu (signed)

- Là trường chỉ tính `MSB = 1` hay `MSB = 0`, quyết định số âm hay dương. **Ví dụ** cho số thực $$\large19.6875_{10}$$ có sign là 0 (MSB = 0) vì nó không phải là số âm còn nếu cho $$\large-19.6875_{10}$$ thì sign là 1 (MSB = 1) vì nó là số âm

---

## 2.Chuyển đổi số thực sang hệ nhị phân và chuyển đổi hệ nhị phân sang số thực

> **Reading checkpoint**
>
> Đến đây, bạn cần hiểu:
>
> - Actual exponent là gì
> - Exponent field là gì
> - Bias dùng để làm gì
> - Chuẩn hóa số thực ra sao
> - Sign là gì
> - số âm, dương actual exponent của vị trí dấu chấm nhị phân
>
> Nếu đã rõ thì có thể tiếp tục.

### 2.1.Encode

- Phần này chuyển đổi số thực sang số nhị phân. Các bước như sau: 

#### 2.1.1.Chuyển phần nguyên sang nhị phân

- Ở đây chuyển phần nguyên sang nhị phân, ví dụ `29.81` phần này chỉ chú ý và chuyển 29 sang nhị phân kết quả là $$\large11101_{2}$$

#### 2.1.2.Chuyển phần thập phân sang nhị phân

- Ở đây sẽ chuyển phân thập phân sang nhị phân, ví dụ vừa rồi là $$\large29.81_{10}$$ ta đã chuyển thành $$\large11101_{2}.81_{10}$$ bây giờ còn phần thập phân là $$\large0.81_{10}$$ ta tiến hành chuyển đổi đổi nó, cách chuyển phần thập phân sang nhị phân phức tạp hơn phần nguyên. Thay vì liên tục chia cho 2 như phần nguyên, ta sẽ **liên tục nhân phần thập phân với 2**, sau mỗi lần nhân lấy phần nguyên của kết quả làm bit tiếp theo, rồi tiếp tục lặp với phần thập phân còn lại. Theo sơ đồ :

<table>
<tr>
<td>

| Bước | Giá trị | x2   | Bit lấy |
| :---: | :-------: | :----: | :-------: |
|    1 | 0.81    | 1.62 | 1       |
|    2 | 0.62    | 1.24 | 1       |
|    3 | 0.24    | 0.48 | 0       |
|    4 | 0.48    | 0.96 | 0       |
|    5 | 0.96    | 1.92 | 1       |
|    6 | 0.92    | 1.84  | 1     |
| 7 | 0.84 | 1.68 | 1 |
| 8 | 0.68 | 1.36 | 1 |
| 9 | 0.36 | 0.72 | 0 |
| 10 | 0.72 | 1.44 | 1 |
| 11 | 0.44 | 0.88 | 0 |

</td>
<td>

| Bước | Giá trị | x2   | Bit lấy |
| :---: | :-------: | :----: | :-------: |
| 12 | 0.88 | 1.76 | 1 |
| 13 | 0.76 | 1.52 | 1 |
| 14 | 0.52 | 1.04 | 1 |
| 15 | 0.04 | 0.08 | 0 |
| 16 | 0.08 | 0.16 | 0 |
| 17 | 0.16 | 0.32 | 0 |
| 18 | 0.32 | 0.64 | 0 |
| 19 | 0.64 | 1.28 | 1 |
| 20 | 0.28 | 0.56 | 0 |
| 21 | 0.56 | 1.12 | 1 |
| 22 | 0.12 | 0.24 | 0 |

</td>
</tr>
</table>

> số thực nhị phân vô hạn

<p align="center">
	<image alt="alt text" src="image/image10.png" width="680"/>
</p>

> trích từ : [Tin học đại cương bách khoa hà nội](https://www.youtube.com/watch?v=ITpspAmKpCk&pp=ygUkc-G7kSB04buxYyBk4bqldSBwaOG6qXkgxJHhu5luZyBJRWVl)

**như thế các bit theo thứ tự ta sẽ thu được :** $$\large0.81\approx0.1100111101011100001010..$$ suy ra nó là biểu diễn phần thập phân dưới dạng nhị phân, vậy ta có $$\large11101.1100111101011100001010_{2}$$.

> [!NOTE]
> **Lưu ý:** Quá trình nhân với 2 chỉ dừng khi phần dư bằng 0. Nếu phần dư cứ lặp lại và không bao giờ bằng 0 thì số đó có biểu diễn nhị phân vô hạn. Khi lưu vào IEEE 754, phần cứng sẽ cắt bớt các bit vượt quá số bit fraction cho phép và áp dụng quy tắc làm tròn (rounding) có ở chương [3.Rounding tổng quan và các chế độ làm tròn](#3rounding-tổng-quan-và-các-chế-độ-làm-tròn)

#### 2.1.3.Chuẩn hóa số thực

Tiếp theo là phần chuẩn hóa, phần này chúng ta đã biết tại chương [1.1.Chuẩn hóa số thực (normalized)](#11Chuẩn-hóa-số-thực-normalized) bây giờ chúng ta có $$\large11101.1100111101011100001010_{2}$$ và ta thực hiện di chuyển dấu chấm sang bên trái :

$$
\large11101.1100111101011100001010_{2} \xrightarrow{\text{dịch trái 4bit}} 1.11011100111101011100001010_{2}
$$

nó thành $$\large\boxed{1.11011100111101011100001010_{2}}$$ và ta nhớ ta dịch dấu chấm sang trái 4 lần, vì vậy ta có `actual exponent = 4` đây là mũ số thực (chưa cộng bias).

> [!IMPORTANT]
> Actual Exponent không phải là trường Exponent lưu trong IEEE 754. Đây chỉ là số mũ toán học sau khi chuẩn hóa. Trường Exponent trong IEEE sẽ được tính ở bước tiếp theo bằng công thức `exponent field = actual exponent + bias`

#### 2.1.4.Tính Exponent Field

Ta có `actual exponent = 4` từ phần thực hiện chuẩn hóa số thực, bây giờ chương này ta tính exponent field (trường số mũ), phần này ta dùng `actual exponent + bias`, khái niệm bias có tại chương [1.8.1.Độ lệch (Bias)](#181độ-lệch-bias) cũng ở chương đó ta có một bảng có 3 trường được phân bổ nhị phân do đó mỗi trường đều có độ rộng riêng cho nó, ở đây ta dùng hệ 32bit (float) vậy bias có giá trị là `127`

> [!NOTE]
> **Lưu ý:** giá trị `127` ở phần bias là kết quả của phép tính Tmax $$\large2^{N-1}-1$$, ở đây thực chất bias chỉ có độ rộng là 8bit thôi 

khi biết giá trị của bias ta tiến hành thực hiện tính trường số mũ (Exponent field) = $$\large4 + 127 = \boxed{131_{10}}$$ vậy suy ra trường số mũ có giá trị là `131`

#### 2.1.5.Lấy Fraction

IEEE754 quy định là phần này chỉ được lấy những bit sau dấu chấm, không được lấy các bit trước dấu chấm vậy ta có $$\large1.11011100111101011100001010_{2}\times2^{4}$$ thì ta lấy fraction `11011100111101011100001010` nhưng theo định dạng IEEE 754 binary32 (32-bit floating-point format) và dựa vào bảng ở chương bias ta thấy fraction có 23bit nhưng fraction là `11011100111101011100001010` (dư 3 bit) ta thực hiện cắt và làm tròn thành `11011100111101011100001` (do xét Guardbit = 0 nên giữ nguyên, theo quy tắc làm tròn có tại phần [3.2.Round to nearest, ties to even](#32round-to-nearest-ties-to-even))

> [!NOTE]
> Nếu trường hợp gắp số bit fraction nhiều hơn giới hạn toán hạn của fraction thì CPU sẽ thực hiện cắt bit và làm tròn (rounding), ví dụ fraction có độ rộng là 23bit nhưng đầu vào ở fraction là hơn 23bit thì CPU sẽ cắt sao cho đủ 23bit và rounding

#### 2.1.6.Ghép Sign | Exponent | Fraction

Phần này chỉ ghép lại thôi, bây giờ ta có sign = $$\large0_{2}$$ vì `29.81` là số dương, exponent field = $$\large131_{10} = 10000011_{2}\text{Chuẩn 8bit thỏa mãn trường số mũ}$$, Fraction field = $$\large11011100111101011100001_{2}$$ (sau khi cắt/rounding) :

<div align="center">

| sign | Exponent | fraction |
|------|----------|----------|
| 0 | 10000011 | 11011100111101011100001 |

</div>

**từ trên bảng ta có :** `0 10000011 11011100111101011100001`, bỏ dấu cách đi ta có `01000001111011100111101011100001`, suy ra $$\large29.81_{10} = \boxed{01000001111011100111101011100001_{2}}$$

### 2.2.Decode

Chương này nói về chuyển đổi số thực biểu diễn dưới dạng nhị phân sang số thực biểu diễn dưới dạng bình thường

#### 2.2.1.Tách Sign | Exponent | Fraction

đây là việc tách một đoạn binary biểu diễn số thực theo 3 trường (sign, exponent và fraction). Ta có `01000001111011100111101011100001`, tách chúng thành `0(sign) 10000011(exponent) 11011100111101011100001(fraction)`

#### 2.2.2.Khôi phục Actual Exponent

chúng ta đã tách được Sign | Exponent | Fraction, nhưng phần số mũ vẫn chưa phải số mũ thật bây giờ ta tính số mũ thật bằng cách lấy Exponent Field có giá trị nhị phân `10000011` bây giờ ta cần phải chuyển nhị phân này sang số nguyên $$\large10000011_{2} = 131_{10}$$ bây giờ ta lấy `131` là số nguyên vừa covert từ binary sang đem đi trừ với bias ta có Actual exponent = $$\large131 - 127 = \boxed{4_{10}}$$ (Đây chính là số mũ toán học thu được ở bước chuẩn hóa. Nó đúng bằng số lần dịch dấu chấm sang bên trái khi chuẩn hóa số thực) cũng chính là số mũ sẽ dùng ở bước cuối khi khôi phục giá trị số thực.

#### 2.2.3.Khôi phục Hidden Bit

Sau khi đã tính được Actual Exponent, bước tiếp theo là khôi phục Hidden Bit (hay còn gọi là Implicit Leading Bit). IEEE quy định rằng đối với số chuẩn hóa (normalized) bit `1` đứng trước dấu chấm sẽ không được lưu trong bộ nhớ bởi vì sau khi chuẩn hóa nó sẽ có dạng $$\large1.b_{1}b_{2}b_{3}\ldots\times2^{N}$$ do bit đứng trước dấu chấm bằng 1, IEEE không cần lưu để tiết kiệm một bit fraction. Vì vậy, khi giải mã (Decode), CPU sẽ tự động thêm lại bit này. ở bước tách sign, exponent, fraction ta đã tách được như sau :

<div align="center">

| sign | exponent | fraction |
|------|----------|----------|
| 0 | 10000011 | 11011100111101011100001 |

</div>

Và ta đã tính được `Actual exponent = 4` đồng thời nhận thấy $$\large\text{Exponent}\neq00000000$$ và $$\large\text{Exponent}\neq11111111$$ , nên đây là normalized number, CPU sẽ tự động thêm `hiddenbit = 1`. Vậy ta có fraction ban đầu là `11011100111101011100001` nhưng sau khi khôi phục hiddenbit ta có `1.11011100111101011100001` vậy suy ra kết quả là $$\large\boxed{1.11011100111101011100001_{2}}$$

> [!NOTE]
> Hidden Bit không tồn tại trong bộ nhớ. Nó chỉ được CPU tự động thêm vào trong quá trình Decode nếu số thuộc dạng Normalized. Đối với Denormalized Number (Exponent = 00000000), Hidden Bit không còn bằng 1 nữa mà bằng 0. Điều này đã được trình bày ở chương [1.2.Khử chuẩn hóa số thực (Denormalized)](#12khử-chuẩn-hóa-số-thực-denormalized)

#### 2.2.4.Nhân với 2^Exponent

Về mặt toán học đây vẫn là phép nhân với $$\large2^{\text{Exponent}}$$ nhưng trong hệ nhị phân, phép nhân với lũy thừa của 2 tương đương với dịch dấu chấm nhị phân, **ví dụ** khi encode việc chuẩn hóa dịch dấu chấm sang bên trái là số mũ actual exponent là dương còn sang bên phải nó là âm, thì bây giờ trong decode chúng ta có actual exponent đã giải ở phần [2.2.2.Khôi phục Actual Exponent](#222khôi-phục-actual-exponent), ta có `actual exponent = 4` vậy bây giờ encode mình dịch dấu chấm sang trái 4 lần là actual exponent là 4 thì bây giờ decode mình dịch dấu chấm sang phải như đang trả lại chỗ cũ thôi. Bây giờ ta có `1.11011100111101011100001` là kết quả của phần [2.2.3.Khôi phục Hidden Bit](#223khôi-phục-hidden-bit), ta tiến hành dịch dấu chấm sang phải 4 lần (theo giá trị của actual exponent mà ta đã tính ra ở phần khôi phục exponent) ta có :

$$
\large1.11011100111101011100001_{2} \xrightarrow{\text{dịch phải 4}} 11101.1100111101011100001_{2}
$$ 

vậy kết quả là $$\large\boxed{11101.1100111101011100001_{2}}$$ đây chính là số nhị phân ban đầu trước khi chuẩn hóa

#### 2.2.5.Áp dụng Sign

Đây là bước cuối cùng trong quá trình Decode. Sau khi đã khôi phục lại số nhị phân ban đầu, CPU chỉ cần dựa vào trường Sign để xác định kết quả là số dương hay số âm. Ta có **formula =**$$\large1.b_{1}b_{2}b_{3}b_{4}b_{5}\times2^{N}$$ **ví dụ** $$\large12345_{10}$$ = $$\large1.2345_{10}\times10^{4}$$, ở các bước trước ta đã khôi phục được `Sign = 0, Actual exponent = 4, Significand = 1.11011100111101011100001` và sau khi thực hiện nhân với $$\large2^{\text{Actual Exponent}}$$ ta có `11101.1100111101011100001`, vì `sign = 0` nên $$\large(-1)^{0} = 1$$ do đó giá trị vẫn giữ nguyên `11101.1100111101011100001`, bây giờ ta chỉ cần chuyển phần nguyên sang thập phân và tính toán fraction (phần dãy bit sau dấu chấm)

Đầu tiên ta có `11101.1100111101011100001` và ta cần chuyển phần nguyên sang thập phân $$\large11101_{2} = 29_{10}$$, bây giờ ta tiến hành tính toán phần fraction sau dấu chấm cách tính là ta lấy số bit nhân với trọng số lũy thừa số nguyên âm **ví dụ** $$\large1\times2^{-1} + 1\times2^{-2} + 0\times2^{-3} +....+ 0\times2^{-N}$$, ở đây ta thấy giá trị bit `0` luôn ra kết quả là `0` vì thế khi tính tổng nó không thay đổi gì, vậy ta chỉ cần đếm lũy thừa giảm dần và tính toán những bit `1` thôi (trong phần tính toán này phải dùng toán học, không phải nhị phân nên các bit khi tính toán kiểu này là nó có hệ cơ số 10 vì sẽ ra giá trị là hệ thập phân) :

| bit | trọng số | giá trị |
|:-----:|:----------:|:---------:|
| 1 | $$\large2^{-1}$$ | 0.5 |
| 1 | $$\large2^{-2}$$ | 0.25 |
| 1 | $$\large2^{-5}$$ | 0.03125 |
| 1 | $$\large2^{-6}$$ | 0.015625 |
| 1 | $$\large2^{-7}$$ | 0.0078125 |
| 1 | $$\large2^{-8}$$ | 0.00390625 |
| 1 | $$\large2^{-10}$$ |  0.0009765625 |
| 1 | $$\large2^{-12}$$ |  0.0002441406 |
| 1 | $$\large2^{-13}$$ |  0.00012207031 |
| 1 | $$\large2^{-14}$$ | 0.00006103516 |
| 1 | $$\large2^{-19}$$ | 0.00000190735 |

ta tiến hành tính tổng giá trị lại $$\large2^{-1} + 2^{-2} + 2^{-5} + 2^{-6} + 2^{-7} + 2^{-8} + 2^{-10} + 2^{-12} + 2^{-13} + 2^{-14} + 2^{-19} = 0.80999946594_{10}$$ bây giờ ghép lại ta có kết quả $$\large\boxed{29.80999946594_{10}}$$ . Chúng ta vẫn có thể ráp vào công thức như ở phần [1.Tổng quan về IEEE 754](#1Tổng-quan-về-ieee-754) là $$\large(-1)^{S} \times 1.m \times 2^{e-b}$$ ta có $$\large(-1)^{0} \times (1.863124966621399) \times 2^{4}$$ và vẫn ra kết quả khớp là $$\large29.80999946594_{10}$$. Giá trị `1.863124966621399` trong biểu thức là phần trị `Significand = 1.11011100111101011100001` cái phần được tách ở trường fraction lúc đầu, chúng ta quy đổi cả phần này về hệ cơ số 10 bằng cách nhân với trọng số âm như trên bảng vừa rồi

> [!IMPORTANT]
> Ta thấy nó bị chênh lệch số thực, số lúc đầu là `29.81` nhưng sau khi encode và decode ra kết quả lại là `29.80999946594`. Lý do là vì quá trình chuyển phần thập phân bị cắt sớm (vì nó là số nhị phân vô hạn có trong chương [3.1.biểu diễn nhị phân hữu hạn và biểu diễn nhị phân vô hạn](#31biểu-diễn-nhị-phân-hữu-hạn-và-biểu-diễn-nhị-phân-vô-hạn) ) theo giới hạn 23 bit fraction hay giới hạn bit fraction theo độ rộng của IEEE 754 single precision, nên suy ra nguyên nhân là do chuỗi nhị phân bị cắt sớm và rounding (do số thực nhị phân vô hạn)

#### 2.2.6.Phân biệt giữa exponent để tính trọng số bit fraction và exponent biểu thị cho dịch dấu chấm

Đây là phần cực kỳ dễ bị nhầm, ta cần phân biệt và hiểu rõ số mũ dùng để xét trọng số, vị trí bit và số mũ dùng để biểu diễn số lần dịch chuyển của dấu chấm trong decode số thực nhị phân. Hai khái niệm này có liên quan với nhau nhưng không phải là một. Nếu không phân biệt, đặc biệt khi xử lý số khử chuẩn hóa (subnormal), rất dễ hiểu sai tại sao các bit fraction lại có trọng số như $$\large2^{-127}$$ , $$\large2^{-128}$$ , ... mặc dù actual exponent của subnormal vẫn là `-126` đối với `binary32`. **Ví dụ** ta xét:

$$\large
1.1011_{2} \times 2^{-126}
$$

**Ở đây :** `-126` là actual exponent của toàn bộ số thực và nó quyết định dấu chấm nhị phân được dịch bao nhiêu vị trí. Nó không phải là exponent riêng của từng bit fraction. Sau khi khai triển ta có $$\large1.1011_{2} \times 2^{-126}$$ hay $$\large2^{-126} + 2^{-127} + 2^{-129} + 2^{-130}$$ và lúc này các số mũ `-126,-127,-129,-130` là trọng số của từng bit.

**Bây giờ đầu tiên đối với Actual exponent — exponent biểu thị cho dịch dấu chấm**

đối với số thực chuẩn hóa nó luôn có dạng $$\large1.x \times 2^{E}$$ trong đó E là actual exponent và giá trị này quyết định vị trí dấu chấm nhị phân. **Ví dụ** : 

$$\large
1.1011_{2} \times 2^{-126}
$$

nó có `E = -126` vậy vị trí của dấu chám nhị phân sẽ được dịch trái 126 lần bởi vì đây là decode là ngược lại số âm là dịch trái số dương là dịch phải, còn với encode chuẩn hóa thì số âm là dịch phải số dương là dịch trái vậy ta có 

$$\large
1.1011_{2}​\times2^{-126} = 0.000…00011011_{2}
$$

Còn nếu trường hợp mà E là dương thì chúng ta dịch phải ví dụ :

$$\large
1.1011_{2}​\times2^{3} = 1101.1_{2}
$$

**Tiếp theo đối với exponent của trọng số bit**

Sau khi có actual exponent ở trên rồi, thì chúng ta mới tính exponent của trọng số bit và mỗi bit trong significand sẽ có trọng số riêng với $$\large1.1011_{2}​\times2^{-126}$$ ta có :

<div align="center">

| Bit              | Vị trí |   Trọng số |
| ---------------- | :-----: | :---------: |
| hidden bit `1`   |      0 | $$\large2^{-126}$$ |
| fraction bit `1` |      1 | $$\large2^{-127}$$ |
| fraction bit `0` |      2 | $$\large2^{-128}$$ |
| fraction bit `1` |      3 | $$\large2^{-129}$$ |
| fraction bit `1` |      4 | $$\large2^{-130}$$ |

</div>

Do đó dựa trên bảng ta được với biểu thức sau :

$$\large
1.1011_{2}​\times2^{-126} = 
\underbrace{1\times2^{-126}}_{\text{Hidden Bit}}
+
\underbrace{1\times2^{-127}}_{\text{Fraction bit 1}}
+
\underbrace{1\times2^{-129}}_{\text{Fraction bit 3}}
+
\underbrace{1\times2^{-130}}_{\text{Fraction bit 4}}
$$

điểm quan trọng là $$\large-126 \neq -127 \neq -129 \neq -130$$ (đây là các bit-weight exponents) nhưng tất cả chúng đều được suy ra từ `actual exponent = -126`

> Phần giải thích bit-weight exponents

<details>
	<summary><b>[Câu hỏi]</b> bit-weight exponents là gì?</summary>

<table>
<tr>
<td>

---

<br>

hiểu đơn giản là số mũ nằm trên trọng số của một bit cụ thể. Nó không phải một trường riêng trong IEEE 754, cũng không phải một giá trị được lưu trong Exponent field. Đây chỉ là cách gọi để phân tích toán học. **Ví dụ** cho $$\large1.1011_{2}$$ ta xét :

| Bit | Vị trí | Trọng số | Bit-weight exponent |
| :---: | :-----: | :-------: | :------------------: |
| `1` |      0 |    $\large2^0$ |     $\large0$ |
| `1` |      1 | $\large2^{-1}$ |    $\large-1$ |
| `0` |      2 | $\large2^{-2}$ |    $\large-2$ |
| `1` |      3 | $\large2^{-3}$ |    $\large-3$ |
| `1` |      4 | $\large2^{-4}$ |    $\large-4$ |

Nên ta có : $$\large1.1011_{2} = 1 \times 2^{0} + 1 \times 2^{-1} + 0 \times 2^{-2} + 1 \times 2^{-3} + 1 \times 2^{-4}$$ .Ở đây các số mũ  `0, -1, -2, -3, -4` chính là `bit-weight exponents`. Và công thức tổng quan của nó là $$\large W_{i} = 2^{E-i}$$

<br>

<sub>— Hết phần giải thích —</sub>

---

</td>
</tr>
</table>
</details>

**Tại sao dù biết là exponent dịch dấu chấm là dương, âm để dịch trái,phải dấu chấm, nhưng sao tính exponent trọng số lại phải dùng số âm?**

Điều quan trọng là fraction bản thân nó hoàn toàn không âm. Dấu âm nằm ở trọng số như $$\large0.11111_{2} \times 2^{-126}$$ sẽ trở thành $$\large1 \times 2^{-126} + 1 \times 2^{-127} + 1 \times 2^{-128} + 1 \times 2^{-129} + 1 \times 2^{-130}$$ . Các số mũ âm chỉ có nghĩa là các trọng số nằm sau dấu chấm và rất nhỏ.

> [!IMPORTANT]
> actual exponent quyết định vị trí dấu chấm nhị phân và actual exponent của trọng số bit không chung một khái niệm chúng khác nhau nhưng dễ bị nhầm lẫn nhất.
>
> Về encode, actual exponent (E) quyết định vị trí dịch dấu chấm sang trái là số mũ dương và dịch dấu chấm sang phải là số mũ âm
>
> Nhưng đối với decode, actual exponent (E) quyết định vị trí dịch dấu chấm theo hướng ngược lại và tiếp tục tới phần exponent của trọng số bit. Nghĩa là dịch dấu chấm trước sau đó mới tính trọng số của fraction sau với số mũ âm

**Đối với khử chuẩn hóa số thực (denormalized)**

Subnormal không có hidden bit 1. Vì vậy bit đầu tiên của fraction có trọng số $$\large2^{-127}$$ đối với binary32, chứ không phải $$\large2^{-126}$$. Và subnormal (khử chuẩn hóa) có fraction $$\large\neq$$ 000000, exponent field = 000000, công thức của nó là $$\large(-1)^{S}\times(0.f)\times2^{1-\text{bias}}$$ (các khái niệm này đã được đề cập ở chương [1.2.Khử chuẩn hóa số thực (Denormalized)](#12khử-chuẩn-hóa-số-thực-denormalized))

Với binary32 thì `1 - bias = 1 - 127 = -126` (nó y chang kết quả với cái số thực chuẩn hóa phía trên), do khử chuẩn hóa (denormalized/subnormal) không có hiddenbit và nó là 0 nên ta được $$\large0.1011_{2}\times2^{-126}$$, khai triển ra ta có $$\large(2^{-1} + 2^{-3} + 2^{-4}) \times 2^{-126}$$ và các `bit-weight exponents` của nó là $$\large\boxed{2^{-127} , 2^{-129} , 2^{-130}}$$ . Có thể nhìn trực tiếp với bảng sau:

| Bit | Vị trí trong `0.f` | Trọng số trước nhân $$\large2^{-126}$$ | Bit-weight exponent sau nhân |
| :---: | :-----------------: | :-----------------------------: | :---------------------------: |
| `1` |                  1 |                       $$\large(2^{-1})$$ |                   $$\large(2^{-127})$$ |
| `0` |                  2 |                       $$\large(2^{-2})$$ |                   $$\large(2^{-128})$$ |
| `1` |                  3 |                       $$\large(2^{-3})$$ |                   $$\large(2^{-129})$$ |
| `1` |                  4 |                       $$\large(2^{-4})$$ |                   $$\large(2^{-130})$$ |

**Điều quan trọng nhất là tại sao actual exponent ở khử chuẩn hóa lại có kết quả giống với số chuẩn hóa?** : vì đơn giản nó là actual exponent của significand đối với normalized nhỏ nhất, và cũng là exponent cố định `1−bias` dùng trong công thức subnormal. và điều đó chỉ có ở phần số chuẩn hóa còn khử chuẩn hóa luôn là `hidden bit = 0` nên trường hợp này `-126` chính là exponent chung của toàn significand $$\large0.f\times2^{-126}$$ còn bản thân $$\large0.f$$ đã có các bit-weight $$\large2^{-1} , 2^{-2} , 2^{-3} ,...$$ và khi nhân toàn bộ với $$\large2^{-126}$$ ta cộng các số mũ `-1 + -126 = -127`, `-2 + -126 = -128`, `-3 + -126 = -129`,....

Cho nên `bit-weight exponent = -126 - i` (giá trị `-126` là kết quả của `1 - bias` ở trên), với `i = 1,2,3,...` đối với subnormal. Trong khi normalized có hidden bit ở vị trí `i = 0`, nên lần lượt là `i = 0,1,2,...` . Đó là lý do normalized bắt đầu ở $$\large2^{−126}$$, còn subnormal bắt đầu ở $$\large2^{−127}$$.

### 2.3.Số thực lớn nhất và tính toán số thực lớn nhất (Largest finite)

> **Reading checkpoint**
>
> Đến đây, bạn cần hiểu:
> - Decode số thực
> - Công thức tổng quan của IEEE
>
> Nếu đã rõ thì có thể tiếp tục

hay còn gọi là số thực hữu hạn lớn nhất, đối với float 32 bit chúng thường có dạng :

<div align="center">

| sign | exponent | fraction |
|------|----------|----------|
| 0 | 11111110 | 11111111111111111111111 |

</div>

**Lưu ý:** đối với exponent field để biểu diễn số thực lớn nhất tuyệt đối không đươc là `11111111` vì tất cả bit số 1 này được dùng riêng trong việc biểu diễn infinity và NaN. Như thế đối với 32bit ta có chuỗi bit của số thực hữu hạn lớn nhất như sau `01111111011111111111111111111111` việc decode ra sang số thực hệ cơ số 10 thì chúng ta làm tương tự như [2.2.Decode](#22decode) bây giờ chúng ta tiến hành tính toán số thực lớn nhất của ngành kiến trúc 32bit (float)

đầu tiên như trong chương decode, ta tách các bit ra ở đây chúng ta đã có và tách bit ở bảng trên rồi. Tiếp theo ta tính actual exponent bằng cách chuyển chuỗi nhị phân ở trường exponent sang hệ cơ số 10 $$\large11111110_{2} = 254_{10}$$ bây giờ ta lấy nó đi trừ với bias $$\large254 - 127 = 127$$ vậy actual exponent = $$\large\boxed{127}$$, tiếp theo chúng ta tiến hành tính toán phần trị, đầu tiên là khôi phục hiddenbit ta dịch dấu chấm theo actual exponent nhưng ta thấy nó lớn hơn độ rộng được có ở phần fraction nên chúng ta sẽ thêm padding là 0 để thỏa mãn actual exponent ta có $$\large11111111111111111111111100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000.0_{2}$$ tuy hơi dài nhưng nó đã thỏa mãn actual exponent do đây là số chuẩn hóa nên bit ẩn sẽ thêm 1 là bit ở phần có trọng số cao nhất. Bây giờ chúng ta tiến hành tính toán phần fraction với phép mũ âm ta có:

| bit | trọng số | gía trị |
|:-----:|:----------:|:---------:|
| 1 | $$\large2^{-1}$$ | 0.5 |
| 1 | $$\large2^{-2}$$ | 0.25 |
| .. | .. | .. |

như thế tính lần lượt cho hết bit 1 trong trường fraction. Dựa vào công thức có ở [1.Tổng quan về IEEE 754](#1Tổng-quan-về-ieee-754) là $$\large(-1)^{S} \times 1.m \times 2^{e-b}$$, ta tiến hành ráp vào bây giờ sign = 0, actual exponent = 127, bias = 127, tổng cấp số nhân gía trị fraction là $$\large2-2^{-23}$$ khi ráp ta được $$\large(-1)^{0} \times (2-2^{-23}) \times 2^{127}$$ bây giờ ta lấy casio tính cái biểu thức này ra ta được $$\large\boxed{3.40282346638528859811704183484516925440\times10^{38}}$$ đây chính là giá trị chính xác của số thực hữu hạn lớn nhất 32bit float

lý do giá trị phần trị lại là $$\large2-2^{-23}$$ vì đó chỉ là phần rút gọn theo cấp số nhân của phần trị số thực thôi, điều này thường sẽ nói rất rõ bên phía toán học

### 2.4.Số thực chuẩn hóa nhỏ nhất và tính toán số thực chuẩn hóa nhỏ nhất (Smallest normalized)


Số thực chuẩn hóa nhỏ nhất (Smallest Normalized) là số thực dương nhỏ nhất vẫn còn thuộc miền Normalized, nghĩa là trường Exponent không bằng toàn bit 0. **Ví dụ** với `float` có `exponent = 8, fraction = 23, bias = 127` bây giờ số thực chuẩn hóa nhỏ nhất của `float` là :

<div align="center">

| sign | exponent | fraction |
|------|----------|----------|
| 0 | 00000001 | 000000000000000000000000 |

</div>

do `exponent field = 1` nên ta có `actual exponent = 1 - 127 = -126` đồng thời fraction toàn bit 0 nên phần trị (significand) là `1.0` vậy ta có $$\large1.0_{2}\times2^{-126}$$ vậy kết quả là $$\large\boxed{1.17549435082\times10^{-38}}$$

> [!NOTE]
> một mẹo nhỏ là khi muốn biết nhanh số thực chuẩn hóa nhỏ nhất ta chỉ cần tính $$\large2^{1-bias}$$ và lấy casio bấm sẽ ra kết quả

> [!IMPORTANT]
> đối với số thực chuẩn hóa nhỏ nhất, trường sign và trường fraction luôn là `0`. Chỉ có trường exponent luôn có giá trị là `1` đối với số chuẩn hóa nhỏ nhất như trên bảng, nếu thay đổi một trong ba trường thì sẽ không phải là số nhỏ nhất nữa

### 2.5.Số thực khử chuẩn hóa nhỏ nhất và tính toán số thực khử chuẩn hóa nhỏ nhất (Smallest subnormal)

Số thực khử chuẩn hóa nhỏ nhất (Smallest subnormal) là số thực dương nhỏ nhất mà IEEE 754 còn biểu diễn được trước khi giá trị trở thành 0. Đây là giá trị nhỏ nhất trong toàn bộ tập số thực IEEE 754 (không tính số 0).

Đối với số khử chuẩn hóa, trường exponent luôn bằng toàn bit 0 và Hidden Bit không còn bằng 1 mà bằng 0. Để tạo ra giá trị nhỏ nhất khác 0 thì trường fraction chỉ được phép có đúng một bit 1 ở vị trí cuối cùng. **Ví dụ** với kiểu `float` ta có :

<div align="center">

| sign | exponent | fraction                |
| ---- | -------- | ----------------------- |
| 0    | 00000000 | 00000000000000000000001 |

</div>

> để ý là với số thực khử chuẩn hóa nhỏ nhất luôn có LSB trường fraction là bit 1

do `exponent field = 0` nên `hidden bit = 0` (yes sir, vì vốn dĩ khử chuẩn hóa đã hidden bit là 0 rồi nó được đề cập tại chương [1.2.Khử chuẩn hóa số thực (Denormalized)](#12khử-chuẩn-hóa-số-thực-denormalized)) và `actual exponent = 1 - 127 = -126` (vì khử chuẩn hóa là $$\large2^{1 - bias}$$) thì ta có phần trị (significand) là $$\large0.00000000000000000000001_{2}$$ do đó $$\large2^{-23}\times2^{-126} = \boxed{2^{-149}}$$

> giá trị `-23` là bao quát hết fraction của `float` còn nếu muốn lý do vì sao nó lại là số âm thì mở phần details

<details>
	<summary><b>[Câu hỏi]</b> vì sao lại là -23 (lại là số âm)?</summary>

<table>
<tr>
<td>

---

<br>

không có gì cao siêu, chỉ là phép tính decode bit fraction ở chương [2.2.5.Áp dụng Sign](#225áp-dụng-sign) . Ở đây, lý dó `-23` là số âm vì do dịch vị trí của bit. Cho bảng sau :

<div align="center">

| Vị trí     | Giá trị   |
| ---------- | :---------: |
| bit thứ 1  | $$\large2^{-1}$$  |
| bit thứ 2  | $$\large2^{-2}$$  |
| bit thứ 3  | $$\large2^{-3}$$  |
| ...        | ...       |
| bit thứ 23 | $$\large2^{-23}$$ |

</div>

Bit 1 duy nhất nằm ở vị trí thứ 23 sau dấu chấm, nên giá trị của significand là $$\large2^{-23}$$

<br>

<sub>— Hết phần giải thích —</sub>

---

</td>
</tr>
</table>
</details>

Vậy số thực khử chuẩn hóa nhỏ nhất của float là $$\large2^{-149} = \boxed{1.40129846432\times10^{-45}}$$

> [!NOTE]
> Một mẹo nhỏ là với float, số thực khử chuẩn hóa nhỏ nhất luôn bằng $$\large2^{-149}$$ hoặc cũng có thể tính bằng $$\large2^{1-\text{bias}-\text{fraction bit}}$$ thì với float $$\large2^{1-127-23} = 2^{-149}$$ hoặc dùng phép nhân như vừa rồi

> [!IMPORTANT]
> Đối với số thực khử chuẩn hóa nhỏ nhất:
> - Sign = 0
> - Exponent = toàn bit 0
> - Fraction chỉ có đúng bit cuối cùng bằng 1.
>
> Nếu Fraction cũng bằng toàn bit 0 thì giá trị không còn là số thực nhỏ nhất nữa mà chính là **+0**.

> trả lời câu hỏi tại phần details

<details>
	<summary><b>[Câu hỏi]</b> vậy phép tính actual exponent = 1 - 127 = -126 là tính 1 - bias à, này là của khử chuẩn hóa mà sao trước đó tại chương chuẩn hóa lại sử dụng và chương này cũng sử dụng chung phép tính này?</summary>

<table>
<tr>
<td>

---

<br>

Nhìn cách tính thì cũng giống nhưng lý do của hai cái hoàn khác. Đầu tiên là chuẩn hóa (normalized) nếu Fraction $$\large\neq$$ 00000 và Fraction $$\large\neq$$ 11111 thì `actual exponent = E - bias` điều này cũng khá đúng và đã được nêu ở phần tổng quan với formula rồi, ví dụ trên là `exponent = 1, bias = 127` thì nó tính actual `exponent = 1 - 127 = -126` là hoàn toàn bình thường

nhưng vẫn là một phép tính mà khử chuẩn hóa (denormalized) vẫn sử dụng chính phép tính đó, vì denormalized có hiddenbit là 0 , IEEE không đi dùng `actual exponent = 0 - bias` thay vào đó nó vẫn là `exponent = 1 - 127 = -126` dù hiddenbit là 0. Nghe có vẻ giống normalized, nhưng lý do hoàn toàn khác.

**Tại sao lại dùng 1 − Bias?**

Mục đích là để miền subnormal nối liên tục với miền normalized. **Ví dụ** với kiểu `float`  giả sử Smallest normalized ta có `exponent = 00000001, fraction = 000...` và giá trị của nó là $$\large1.0_{2}\times2^{-126}$$ và actual exponent là kết quả của phép tính `e - bias` trên. Còn đối với subnormal ta có `exponent = 00000000, fraction = 111...` và giá trị của nó là $$\large0.11111_{2} \times 2^{-126}$$ do với khử chuẩn hóa hiddenbit là 0 và nó chỉ nhỏ hơn một chút so với $$\large1.00000_{2} \times 2^{-126}$$ ta thấy hai miền nối sát nhau

Nếu IEEE dùng `actual exponent = 0 - 127 = -127` đối với khử chuẩn hóa thì số lớn nhất sẽ là $$\large0.11111_{2} \times 2^{-127}$$ nó nhỏ hơn đúng một nữa .Lúc đó sẽ xuất hiện một khoảng trống lớn giữa normalized và subnormal. IEEE 754 được thiết kế để không có khoảng trống này

<div align="center">

| Loại số    | Điều kiện           | Actual exponent |
| ---------- | ------------------- | --------------- |
| Normalized | `Exponent = 1..254` | `E - Bias`      |
| Subnormal  | `Exponent = 0`      | `1 - Bias`      |

</div>

**Quan trọng :**

 - `1 - 127 = -126` xuất hiện ở normalized nhỏ nhất vì `E = 1`.

 - `1 - 127 = -126` cũng xuất hiện ở mọi subnormal vì chuẩn IEEE quy định cố định như vậy.

**Hai phép tính cho ra cùng kết quả -126, nhưng nguồn gốc khác nhau:**

 - Normalized: do áp dụng công thức `E - Bias` với `E = 1`.

 - Subnormal: do IEEE định nghĩa đặc biệt là `1 - Bias`, không lấy `E = 0 - Bias`

<br>

<sub>— Hết phần giải thích —</sub>

---

</td>
</tr>
</table>
</details>

### 2.6.Số thực lớn nhất trong miền khử chuẩn hóa (Largest subnormal)

Là một giá trị khá quan trọng vì nó nằm ngay tại biên trên của miền subnormal, sát với biên dưới của miền normalized, là giá trị lớn nhất vẫn còn thuộc miền subnormal, ngay trước khi chuyển sang số normalized. Nó có dạng như sau :

<div align="center">

| sign | exponent | fraction |
|------|----------|----------|
| 0 | 00000000 | 11111111111111111111111 |

</div>

> ví dụ bảng là của float 32bit

**Vì sao đây là lớn nhất?:** với khử chuẩn hóa (denormalized) `exponent = 00000000, hiddenbit = 0, actual exponent cố định ở 1 - bias` và ở đây với float binary có `bias = 127` nên `actual exponent = 1 - 127 = -126`, do `hiddenbit = 0` nên significand lớn nhất là $$\large0.11111111111111111111111_{2}$$

Vậy $$\large0.11111111111111111111111_{2}\times2^{-126}$$ phần significand bằng $$\large0.11111111111111111111111_{2} = 1 - 2^{-23}$$ nên $$\large(1-2^{-23})2^{-126}$$ hay tương đương $$\large2^{-126}-2^{-149}$$ suy ra $$\large(1-2^{-23})2^{-126} = 2^{-126}-2^{-149} \approx\boxed{1.1754942106924411\times10^{−38}​}$$ (số xấp xỉ chính là giá trị số thực lớn nhất trong miền khử chuẩn hóa)

**chi tiết quan trọng:** Giá trị này nằm sát số chuẩn hóa nhỏ nhất (smallest normalized). Ta thấy ở chương [2.4.Số thực chuẩn hóa nhỏ nhất và tính toán số thực chuẩn hóa nhỏ nhất (Smallest normalized)](#24số-thực-chuẩn-hóa-nhỏ-nhất-và-tính-toán-số-thực-chuẩn-hóa-nhỏ-nhất-smallest-normalized) có một bảng số thực chuẩn hóa nhỏ nhất như sau :

<div align="center">

| sign | exponent | fraction |
|------|----------|----------|
| 0 | 00000001 | 000000000000000000000000 |

</div>

nghĩa là theo nhị phân, số thực khử chuẩn hóa lớn nhất và số thực chuẩn hóa nhỏ nhất nằm sát nhau. Ở đây, ta biết số thực khử chuẩn hóa lớn nhất có $$\large1 - 2^{-23}2^{-126}$$ và số chuẩn hóa nhỏ nhất có $$\large1.0_{2} \times 2^{-126}$$ vậy hiệu của chúng là $$\large2^{-126} - (1 - 2^{-23}2^{-126}) = \boxed{2^{-149}}$$ mà $$\large2^{-149}$$ lại là ULP/subnormal spacing ở vùng này. Do đó ta thấy :

```
Largest subnormal
	   |
       v
0.11111111111111111111111 x 2^-126
	   |
	   | + 2^-149
       v
1.00000000000000000000000 x 2^-126
	   |
       v
Smallest normal
```

**Đây chính là lý do subnormal rất quan trọng:** nó lấp khoảng trống giữa 0 và số normalized dương nhỏ nhất, thay vì để một khoảng nhảy lớn.

Đối với binary 32, ta có spacing = $$\large2^{-149}$$ từ đó suy ra tất cả subnormal dương có dạng $$\large k\times2^{-149}$$ với $$\large k = 1,2\ldots,2^{23}-1$$ do đó ta có :

```
0
|
| + 2^-149
v
2^-149
|
| + 2^-149
v
2×2^-149
|
|
v
...
|
|
v
(2^23 - 1)×2^-149
|
| + 2^-149
v
2^23×2^-149
```

mà $$\large2^{23}\times2^{-149} = 2^{-126}$$ và kết quả này chính là số chuẩn hóa nhỏ nhất (smallest normalized). Đây là cách nhìn rất đẹp về toàn bộ miền subnormal:

$$\large
\boxed{0\rightarrow2^{-149}\rightarrow2(2^{-149})\rightarrow\ldots\rightarrow(2^{23}-1)2^{-149}\rightarrow2^{-126}}
$$

Trong đó phần tử cuối cùng trước $$\large2^{-126}$$ chính là largest subnormal.

---

[còn tiếp ở writeup-p2.md](https://github.com/tranquanghao708/CSAPP-learning/blob/main/writeup/floating-point_number/writeup-p2.md)