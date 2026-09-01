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

- [3.Rounding tổng quan và các chế độ làm tròn](#3rounding-tổng-quan-và-các-chế-độ-làm-tròn)

    - [3.1.biểu diễn nhị phân hữu hạn và biểu diễn nhị phân vô hạn](#31biểu-diễn-nhị-phân-hữu-hạn-và-biểu-diễn-nhị-phân-vô-hạn)

       - [3.1.1.Hai phương pháp xử lý biểu diễn nhị phân hữu hạn và vô hạn](#311hai-phương-pháp-xử-lý-biểu-diễn-nhị-phân-hữu-hạn-và-vô-hạn)

    - [3.2.Round to nearest, ties to even](#32round-to-nearest-ties-to-even)

       - [3.2.1.guard bit](#321guard-bit)

       - [3.2.2.round bit](#322round-bit)

       - [3.2.3.sticky bit](#323sticky-bit)

       - [3.2.4.cách phần cứng dùng các guard bit, round bit và sticky bit để xác định ba trường hợp](#324cách-phần-cứng-dùng-các-guard-bit-round-bit-và-sticky-bit-để-xác-định-ba-trường-hợp)

       - [3.2.5.Thao tác Bitwise Raw Manipulation trên uint32_t](#325thao-tác-bitwise-raw-manipulation-trên-uint32_t)

       - [3.2.6.Vì sao phần cứng biết vị trí của Guard, Round và Sticky Bit?](#326vì-sao-phần-cứng-biết-vị-trí-của-guard-round-và-sticky-bit)

    - [3.3.Round to nearest, ties away from zero (Ties to away)](#33round-to-nearest-ties-away-from-zero-ties-to-away)

    - [3.4.Round toward zero](#34round-toward-zero)

       - [3.4.1.biểu diễn làm tròn trên hệ nhị phân](#341biểu-diễn-làm-tròn-trên-hệ-nhị-phân)

    - [3.5.Round toward positive infinity (+∞)](#35round-toward-positive-infinity-)

    - [3.6.Round toward negative infinity (−∞)](#36round-toward-negative-infinity-)

    - [3.7.Tác dụng và mức biểu diễn độ chính xác của 5 quy tắc làm tròn, khi nào nên dùng quy tắc nào?](#37tác-dụng-và-mức-biểu-diễn-độ-chính-xác-của-5-quy-tắc-làm-tròn-khi-nào-nên-dùng-quy-tắc-nào)

- 4.Các phép toán trong số thực dấu phẩy động IEEE754

    - 4.1.Phép cộng

    - 4.2.Phép trừ

    - 4.3.Phép nhân

    - 4.4.Phép chia

       - 4.4.1.Chia lấy dư

       - 4.4.2.Chia ko lấy dư

- 5.kết luận

**Phần mở rộng**

- 1.Những vấn đề thường gặp khi làm việc với số thực

    - 1.1.Underflow

    - 1.2.Overflow

    - 1.3.Precision Loss

    - 1.4.Catastrophic Cancellation

    - 1.5.Floating-point comparison

    - 1.6.Gradual underflow

    - 1.7.ULP error

- 2.cancellation examples

---

# Phần trọng tâm

## 1.Tổng quan về IEEE 754.

<p align="center">
	<image alt="alt text" src="image/image1.png" width="680"/>
</p>

> không phải CS:APP, tham khảo từ cuốn kiến trúc máy tính vì tính dễ hiểu về formula

- `Số thực IEEE 754` là quy tắc biểu diễn số thực cho thiết bị nhị phân (máy tính) thế giới. **Formula tổng quan là** $$\Large(-1)^{S} \times 1.m \times 2^{e-b}$$, trong đó :

S : là bit dấu, viết tắt sign

m : hidden bit + fraction là phần trị (trường dãy số sau dấu chấm của số thực sau khi đã chuẩn hóa)

e : là giá trị của trường exponent

b : là độ lệch, viết tắt bias

- Ta có một structure của cái này như sau:

| S (sign) | E (Exponent) | m (Fraction) |
|----------|--------------|--------------|

### 1.1.Chuẩn hóa số thực (normalized)

<p align="center">
	<image alt="alt text" src="image/image2.png" width="680"/>
</p>

> Trích từ CS:APP

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
> nếu dịch dot sang trái số mũ là **số dương** và dịch dot sang phải thì số mũ sẽ là **số âm**. Độ lớn tuyệt đối của số mũ (|N|) bằng số lần dịch dấu chấm. Dấu của số mũ phụ thuộc vào hướng dịch, nó lớn theo âm-dương **ví dụ** dương lớn dần sẽ là `1,2,3,4,..` còn âm nhỏ dần sẽ là `-1,-2,-3,-4,..`
>
> Trong IEEE 754 (đối với các số normalized), sau khi chuẩn hóa, biểu diễn luôn có dạng: $$\large1.xxxxx\times2^{N}$$ .Nghĩa là trước dấu chấm luôn chỉ có đúng một bit 1. Chính vì bit đầu tiên luôn là 1, IEEE 754 không cần lưu bit này vào bộ nhớ (hidden bit), chỉ lưu phần phía sau dấu chấm trong trường Fraction.

<details>
	<summary><b>[Câu hỏi]</b> tại sao phải chuẩn hóa số thực?</summary>

<table>
<tr>
<td>

---

<br>

- Vì nếu không chuẩn hóa mọi số thực sẽ có cùng value nhưng nhiều cách biểu diễn sẽ khác nhau **ví dụ** $$\large1001.1_{2}\times2$$, $$\large100.11_{2}\times2^{1}$$, $$\large10.011_{2}\times2^{2}$$, $$\large1.0011_{2}\times2^{3}$$. Cùng giá trị nhưng dịch dot khác biểu diễn. Nên IEEE quy định sử dụng dạng $$\large1.xxxxx\times2^{N}$$ để mỗi số chỉ có một biểu diễn duy nhất. Ngoài ra, vì bit đầu tiên luôn là 1, CPU không cần lưu bit này (gọi là hidden bit hoặc implicit leading 1), nhờ đó tăng thêm một bit độ chính xác cho trường Fraction.

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

- Là việc bit đầu tiên là 0 nhưng nó thực hiện phép toán $$\large0.xxxxx\times2^{1-bias}$$. **Lúc này** hiddenbit không còn là 1 nữa, nó là 0 và exponent field luôn là 0. Giả sử float (32bits) ta có :

```
Exponent = 00000000
Fraction = 00000000000000000000001
```

thì đây không phải là pattern $$\large1.0000000000_{2}\times2^{-127}$$ mà là $$\large0.0000000000000000000001_{2}\times2^{-126}$$ vì hiddenbit đã bằng 0.

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

| Sign | Exponent | Fraction |
|------|----------|----------|
| 0 hoặc 1 | Toàn bộ bit = 1 | Toàn bộ bit = 0 |

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

| Sign | Exponent | Fraction |
|------|----------|----------|
| 0 hoặc 1 | Toàn bộ bit = 1 | Khác 0 |

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

- Là trường lưu các bit phía sau dấu chấm của số nhị phân sau khi đã chuẩn hóa số thực theo dạng chuẩn hóa $$\large1.xxxxx\times2^{N}$$:

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

| Loại số                  | Hidden Bit    |
| ------------------------ | ------------- |
| Normalized               | 1 (Implicit)  |
| Denormalized (Subnormal) | 0             |
| Infinity                 | Không sử dụng |
| NaN                      | Không sử dụng |

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

- Là trường biểu diễn số mũ của số thực sau khi chuẩn hóa. Số mũ được xác định bằng số lần dịch dấu chấm để đưa số về dạng $$\large1.xxxxx\times2^{N}$$, **ví dụ** $$\large101.00110_{2} = 1.0100110_{2}$$ dịch chuyển dot sang trái 2 lần số mũ = 2 (dương), $$\large0.00110_{2} = 001.00110_{2} = 1.00110_{2}$$ dịch chuyển dot sang phải 3 lần số mũ = -3 (âm), rõ hơn đã nói trước ở [1.1.Chuẩn hóa số thực (normalized)](#11Chuẩn-hóa-số-thực-normalized)

- Exponent đóng vai trò quyết định độ lớn của số thực, **ví dụ** $$\large1.11111_{2}\times2^{2} = 7.875_{10}$$ nhưng đổi giá trị số mũ  $$\large1.11111_{2}\times2^{10} = 2016_{10}$$ giá trị đổi, mặc dù fraction không đổi

> [!IMPORTANT]
> Exponent quyết định độ lớn của số thực, tùy thuộc vào số mũ lớn nhỏ bao nhiêu
>
> Fraction quyết định chữ số có nghĩa (độ chính xác của số thực), tùy thuộc vào hệ thống cung cấp bao nhiêu bit cho nó
>
> **điều quan trọng** : Exponent quyết định scale (độ lớn) của số thực thông qua lũy thừa $$\large2^{N}$$ . Chỉ cần thay đổi Exponent một lượng nhỏ, giá trị của số thực có thể thay đổi rất lớn. Fraction thiên hướng về quyết định chữ số có nghĩa (độ chính xác của số thực) nhưng khi thay đổi các bit trong trường Fraction sẽ làm thay đổi giá trị của số thực, nhưng mức thay đổi thường nhỏ hơn nhiều so với việc thay đổi Exponent. **Precision (độ chính xác)** không phụ thuộc vào giá trị của Fraction mà phụ thuộc vào số lượng bit được **IEEE 754** cấp cho trường Fraction. **Ví dụ**, double có 52 bit Fraction nên biểu diễn số thực chính xác hơn float với 23 bit Fraction.

- **Điểm thường bị nhầm :** Trường exponent không lưu trực tiếp actual exponent (số mũ thực) ký hiệu `N` trong dạng chuẩn hóa $$\large1.xxxxx\times2^{N}$$ , giá trị của trường exponent được tính theo công thưc `Exponent Field = Actual exponent + Bias`.

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

| name                 | Tổng số bit | Exponent | Fraction |  Bias |
| ------------------- | :----------: | :-------: | :-------: | :----: |
| Single precision    |          32 |        8 |       23 |   127 |
| Double precision    |          64 |       11 |       52 |  1023 |
| Quadruple precision |         128 |       15 |      112 | 16383 |

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

| sign | Exponent | fraction |
|------|----------|----------|
| 0 | 10000011 | 11011100111101011100001 |

**từ trên bảng ta có :** `0 10000011 11011100111101011100001`, bỏ dấu cách đi ta có `01000001111011100111101011100001`, suy ra $$\large29.81_{10} = \boxed{01000001111011100111101011100001_{2}}$$

### 2.2.Decode

Chương này nói về chuyển đổi số thực biểu diễn dưới dạng nhị phân sang số thực biểu diễn dưới dạng bình thường

#### 2.2.1.Tách Sign | Exponent | Fraction

đây là việc tách một đoạn binary biểu diễn số thực theo 3 trường (sign, exponent và fraction). Ta có `01000001111011100111101011100001`, tách chúng thành `0(sign) 10000011(exponent) 11011100111101011100001(fraction)`

#### 2.2.2.Khôi phục Actual Exponent

chúng ta đã tách được Sign | Exponent | Fraction, nhưng phần số mũ vẫn chưa phải số mũ thật bây giờ ta tính số mũ thật bằng cách lấy Exponent Field có giá trị nhị phân `10000011` bây giờ ta cần phải chuyển nhị phân này sang số nguyên $$\large10000011_{2} = 131_{10}$$ bây giờ ta lấy `131` là số nguyên vừa covert từ binary sang đem đi trừ với bias ta có Actual exponent = $$\large131 - 127 = \boxed{4_{10}}$$ (Đây chính là số mũ toán học thu được ở bước chuẩn hóa. Nó đúng bằng số lần dịch dấu chấm sang bên trái khi chuẩn hóa số thực) cũng chính là số mũ sẽ dùng ở bước cuối khi khôi phục giá trị số thực.

#### 2.2.3.Khôi phục Hidden Bit

Sau khi đã tính được Actual Exponent, bước tiếp theo là khôi phục Hidden Bit (hay còn gọi là Implicit Leading Bit). IEEE quy định rằng đối với số chuẩn hóa (normalized) bit `1` đứng trước dấu chấm sẽ không được lưu trong bộ nhớ bởi vì sau khi chuẩn hóa nó sẽ có dạng $$\large1.xxx..._{2}\times2^{N}$$ do bit đứng trước dấu chấm bằng 1, IEEE không cần lưu để tiết kiệm một bit fraction. Vì vậy, khi giải mã (Decode), CPU sẽ tự động thêm lại bit này. ở bước tách sign, exponent, fraction ta đã tách được như sau :

| sign | exponent | fraction |
|------|----------|----------|
| 0 | 10000011 | 11011100111101011100001 |

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

Đây là bước cuối cùng trong quá trình Decode. Sau khi đã khôi phục lại số nhị phân ban đầu, CPU chỉ cần dựa vào trường Sign để xác định kết quả là số dương hay số âm. Ta có **formula =**$$\large1.xxxxx\times2^{N}$$ **ví dụ** $$\large12345_{10}$$ = $$\large1.2345_{10}\times10^{4}$$, ở các bước trước ta đã khôi phục được `Sign = 0, Actual exponent = 4, Significand = 1.11011100111101011100001` và sau khi thực hiện nhân với $$\large2^{\text{Actual Exponent}}$$ ta có `11101.1100111101011100001`, vì `sign = 0` nên $$\large(-1)^{0} = 1$$ do đó giá trị vẫn giữ nguyên `11101.1100111101011100001`, bây giờ ta chỉ cần chuyển phần nguyên sang thập phân và tính toán fraction (phần dãy bit sau dấu chấm)

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

| Bit              | Vị trí |   Trọng số |
| ---------------- | :-----: | :---------: |
| hidden bit `1`   |      0 | $$\large2^{-126}$$ |
| fraction bit `1` |      1 | $$\large2^{-127}$$ |
| fraction bit `0` |      2 | $$\large2^{-128}$$ |
| fraction bit `1` |      3 | $$\large2^{-129}$$ |
| fraction bit `1` |      4 | $$\large2^{-130}$$ |

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

| sign | exponent | fraction |
|------|----------|----------|
| 0 | 11111110 | 11111111111111111111111 |

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

| sign | exponent | fraction |
|------|----------|----------|
| 0 | 00000001 | 000000000000000000000000 |

do `exponent field = 1` nên ta có `actual exponent = 1 - 127 = -126` đồng thời fraction toàn bit 0 nên phần trị (significand) là `1.0` vậy ta có $$\large1.0_{2}\times2^{-126}$$ vậy kết quả là $$\large\boxed{1.17549435082\times10^{-38}}$$

> [!NOTE]
> một mẹo nhỏ là khi muốn biết nhanh số thực chuẩn hóa nhỏ nhất ta chỉ cần tính $$\large2^{1-bias}$$ và lấy casio bấm sẽ ra kết quả

> [!IMPORTANT]
> đối với số thực chuẩn hóa nhỏ nhất, trường sign và trường fraction luôn là `0`. Chỉ có trường exponent luôn có giá trị là `1` đối với số chuẩn hóa nhỏ nhất như trên bảng, nếu thay đổi một trong ba trường thì sẽ không phải là số nhỏ nhất nữa

### 2.5.Số thực khử chuẩn hóa nhỏ nhất và tính toán số thực khử chuẩn hóa nhỏ nhất (Smallest subnormal)

Số thực khử chuẩn hóa nhỏ nhất (Smallest subnormal) là số thực dương nhỏ nhất mà IEEE 754 còn biểu diễn được trước khi giá trị trở thành 0. Đây là giá trị nhỏ nhất trong toàn bộ tập số thực IEEE 754 (không tính số 0).

Đối với số khử chuẩn hóa, trường exponent luôn bằng toàn bit 0 và Hidden Bit không còn bằng 1 mà bằng 0. Để tạo ra giá trị nhỏ nhất khác 0 thì trường fraction chỉ được phép có đúng một bit 1 ở vị trí cuối cùng. **Ví dụ** với kiểu `float` ta có :

| sign | exponent | fraction                |
| ---- | -------- | ----------------------- |
| 0    | 00000000 | 00000000000000000000001 |

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

| Vị trí     | Giá trị   |
| ---------- | :---------: |
| bit thứ 1  | $$\large2^{-1}$$  |
| bit thứ 2  | $$\large2^{-2}$$  |
| bit thứ 3  | $$\large2^{-3}$$  |
| ...        | ...       |
| bit thứ 23 | $$\large2^{-23}$$ |

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

| Loại số    | Điều kiện           | Actual exponent |
| ---------- | ------------------- | --------------- |
| Normalized | `Exponent = 1..254` | `E - Bias`      |
| Subnormal  | `Exponent = 0`      | `1 - Bias`      |

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

| sign | exponent | fraction |
|------|----------|----------|
| 0 | 00000000 | 11111111111111111111111 |

> ví dụ bảng là của float 32bit

**Vì sao đây là lớn nhất?:** với khử chuẩn hóa (denormalized) `exponent = 00000000, hiddenbit = 0, actual exponent cố định ở 1 - bias` và ở đây với float binary có `bias = 127` nên `actual exponent = 1 - 127 = -126`, do `hiddenbit = 0` nên significand lớn nhất là $$\large0.11111111111111111111111_{2}$$

Vậy $$\large0.11111111111111111111111_{2}\times2^{-126}$$ phần significand bằng $$\large0.11111111111111111111111_{2} = 1 - 2^{-23}$$ nên $$\large(1-2^{-23})2^{-126}$$ hay tương đương $$\large2^{-126}-2^{-149}$$ suy ra $$\large(1-2^{-23})2^{-126} = 2^{-126}-2^{-149} \approx\boxed{1.1754942106924411\times10^{−38}​}$$ (số xấp xỉ chính là giá trị số thực lớn nhất trong miền khử chuẩn hóa)

**chi tiết quan trọng:** Giá trị này nằm sát số chuẩn hóa nhỏ nhất (smallest normalized). Ta thấy ở chương [2.4.Số thực chuẩn hóa nhỏ nhất và tính toán số thực chuẩn hóa nhỏ nhất (Smallest normalized)](#24số-thực-chuẩn-hóa-nhỏ-nhất-và-tính-toán-số-thực-chuẩn-hóa-nhỏ-nhất-smallest-normalized) có một bảng số thực chuẩn hóa nhỏ nhất như sau :

| sign | exponent | fraction |
|------|----------|----------|
| 0 | 00000001 | 000000000000000000000000 |

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

## 3.Rounding tổng quan và các chế độ làm tròn

- không phải mọi số thập phân đều biểu diễn chính xác trong nhị phân, nên IEEE 754 phải làm tròn (rounding). Đây là nguyên nhân của những kết quả như `0.1 + 0.2 != 0.3` trong nhiều ngôn ngữ lập trình. Phần chương này sẽ biểu diễn và tổng quát về việc này

**Vì sao lại phải rounding?:** Trong hệ thống máy tính, bit nhị phân là hữu hạn nhưng biểu diễn số thực một cách chính xác lại phải vô hạn nên khi đến một ngưỡng nào đó đụng tới rào cản hữu hạn sẽ xem như làm tròn của bit nhị phân đó ví dụ 4 bit $$\large0000_{2}$$ thì số thực chỉ được biểu diễn ở phạm vi bit này, bit được cấp cho trường fraction và các trường khác lại rất ít nên độ chính xác vì thế mà giảm rất đáng kể

<details>
	<summary><b>[Chi tiết]</b> Ví dụ C</summary>

<table>
<tr>
<td>

---

<br>

Cho đoạn C như sau :

```c
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(void)
{
    float x = 0.1f + 0.2f;

    uint32_t bits;
    memcpy(&bits, &x, sizeof(bits));

    printf("value = %.20f\n", x);
    printf("bits  = 0x%08X\n", bits);
}
```

> gcc -o float_rounding float_rounding.c

<p align="center">
	<image alt="alt text" src="image/image11.png" width="680"/>
</p>

ta thấy số thực nó đã bị làm tròn ở đây khá hỗn loạn nên cũng là lý do x($$\large0.1_{10} + 0.2_{10}$$) $$\large\neq$$ 0.3, chỉ có thể biểu diễn **xấp xỉ** với trường hợp này chứ không thể dùng **tuyệt đối** như `==`

<br>

<sub>— Hết phần giải thích —</sub>

---

</td>
</tr>
</table>
</details>

Các chế độ của Rounding (làm tròn)

### 3.1.biểu diễn nhị phân hữu hạn và biểu diễn nhị phân vô hạn

Đây là chương sẽ lý giải tại sao cùng một phép cộng số thực nhưng `1.50 + 1.25 = 2.75` và không có khái niệm rounding nào xảy ra ở phép cộng `1.50`. Tất cả là do biểu diễn nhị phân hữu hạn và biểu diễn nhị phân vô hạn

**Biểu diễn nhị phân hữu hạn:** là việc biểu diễn nhị phân có độ rộng độ rộng được giới hạn ở một ngưỡng nào đó **ví dụ** $$\large1.101_{2}$$ chỉ có 3bit fraction rồi xong hết, còn các fraction nếu dư sẽ luôn có bit là 0. **Ví dụ2:** cho số $$\large1.50_{10}$$ nó cũng là hữu hạn. 

**Bằng chứng nào để chứng minh nó hữu hạn?:** Là khi số hữu hạn luôn thực hiện phép nhân và fraction có giá trị là 0, chúng ta dùng số gốc để nhân 2 và nếu có phần dư thì lấy phần dư nhân tiếp cho 2 **ví dụ** với số thực $$\large1.25_{10}$$ ta xét bit fraction là $$\large0.25_{10}$$ :

| Bước | Giá trị x2  | Bit | Phần dư |
| :----: | :-----------: | :---: | :-------: |
| 1    | 0.25×2=0.50 | 0   | 0.50    |
| 2    | 0.50×2=1.00 | 1   | 0       |

Dừng ở bước 2 do phần dư là 0, ta có $$\large0.25_{10} = 0.01_{2}$$ vì bit ở bước 1 và 2 lần lượt là 0 và 1, nên ta có $$\large1.25_{10} = \boxed{1.01_{2}}$$ . Đây là hữu hạn do phần dư là 0 ở bước hai, ta cho thêm **ví dụ** là $$\large0.75_{10}$$ tính fraction trước y nhưu trên :

| Bước | x2          | Bit | Dư   |
| :----: | :-----------: | :---: | :----: |
| 1    | 0.75×2=1.50 | 1   | 0.50 |
| 2    | 0.50×2=1.00 | 1   | 0    |

ta cũng dừng ở bước 2, ta có $$\large0.75_{10} = \boxed{0.11_{2}}$$, nó là hữu hạn vì số dư là 0 ở bước 2

<details>
	<summary><b>[Chi tiết]</b> Ví dụ với C</summary>

<table>
<tr>
<td>

---

<br>

```c
#include <stdio.h>

int main(void){
	float x = 1.50; //binary = 1.10
	printf("dump fration 23bit : %.23f\n",x);
}
```

> gcc -o dump_floating_point_fraction dump_floating_point_fraction.c

<p align="center">
	<image alt="alt text" src="image/image12.png" width="680"/>
</p>

Ta thấy khi gán vào x là 1.50, và ta dump ra nó vẫn đúng số 1.5 nhưng fraction phía sau này là giá trị 0 hết. Chúng ta thử thực hiện phép tính cộng vào xem sao

```c
#include <stdio.h>

int main(void){
	float x = 1.50; //binary = 1.10
	float y = 1.25; //binary = 1.01
	printf("dump fration 23bit : %.23f\n",x + y); //phần này sẽ biểu diễn số hữu hạn
}
```

<p align="center">
	<image alt="alt text" src="image/image13.png" width="680"/>
</p>

Ta thấy nó vẫn là kết quả chính xấc, không có rounding nào ở đây vì nó là số hữu hạn.

<br>

<sub>— Hết phần giải thích —</sub>

---

</td>
</tr>
</table>
</details>

**Biểu diễn nhị phân vô hạn:** là việc biểu diễn nhị phân có độ rộng độ rộng không được giới hạn tới khi bị cắt bởi phần cứng do giới hạn độ rộng độ rộng bên phía phần cứng **ví dụ** $$\large0.1_{2}$$ tính fraction nó với 2:

| Bước | x2      | Bit | Dư  |
| :----: | :-------: | :---: | :---: |
| 1    | $$\large0.1\rightarrow0.2$$ | 0   | 0.2 |
| 2    | $$\large0.2\rightarrow0.4$$ | 0   | 0.4 |
| 3    | $$\large0.4\rightarrow0.8$$ | 0   | 0.8 |
| 4    | $$\large0.8\rightarrow1.6$$ | 1   | 0.6 |
| 5    | $$\large0.6\rightarrow1.2$$ | 1   | 0.2 |
| 6    | $$\large0.2\rightarrow0.4$$ | 0   | 0.4 |
| 7    | $$\large0.4\rightarrow0.8$$ | 0   | 0.8 |
| 8    | $$\large0.8\rightarrow1.6$$ | 1   | 0.6 |

Ta thấy nó cứ lặp lại từ `0.2 -> 0.6` giống kim đồng hồ và số dư không có điểm dừng. Đây gọi là biểu diễn nhị phân vô hạn, và đây cũng là điều kiện để hệ thống rounding (làm tròn) dãy này

<details>
	<summary><b>[Chi tiết]</b> Ví dụ với C</summary>

<table>
<tr>
<td>

---

<br>

```c
#include <stdio.h>

int main(void){
	float x = 0.1;
	printf("dump fration 23bit : %.23f\n",x);
}
```

> gcc -o dump_floating_point_fraction3 dump_floating_point_fraction3.c

<p align="center">
	<image alt="alt text" src="image/image14.png" width="680"/>
</p>

Ta thấy khi gán vào x là 0.1, và ta dump ra nó đã bị rounding ở fraction phía sau do đây là biểu diễn nhị phân vô hạn. Chúng ta thử thực hiện phép tính cộng vào xem sao

```c
#include <stdio.h>

int main(void){
	float x = 0.1;
	float y = 0.2;
	printf("dump fration 23bit : %.23f\n",x + y); //xấp xỉ 0.3 chứ không phải tuyệt đối do rounding
}
```

<p align="center">
	<image alt="alt text" src="image/image15.png" width="680"/>
</p>

Ta thấy nó vẫn bị rounding

<br>

<sub>— Hết phần giải thích —</sub>

---

</td>
</tr>
</table>
</details>

**Định lý đẹp của biểu diễn vô hạn và hữu hạn:** một phân số tối giản $$\large\frac{a}{b}$$ sẽ có biểu diễn hữu hạn trong cơ số 2 khi và chỉ khi mẫu số b chỉ chứa thừa số nguyên tố 2. **Ví dụ** $$\large0.5_{10} = \frac{1}{2}$$ ta có mẫu là 2 suy ra nó hữu hạn, $$\large0.25_{10} = \frac{1}{4}$$ mẫu là $$\large2^{2}$$ suy ra nó hữu hạn, $$\large0.75_{10} = \frac{3}{4}$$ mẫu là $$\large2^{2}$$ suy ra nó hữu hạn. Nhưng còn, $$\large0.1_{10} = \frac{1}{10} = \frac{1}{2\times5}$$ mẫu có 5 và nó không thể viết hữu hạn trong cơ số 2, suy ra nó vô hạn

> [!IMPORTANT]
> **Điều quan trọng:** Không phải mọi phép cộng, trừ, nhân hay chia số thực đều sinh ra sai số làm tròn. Nếu các độ rộng và kết quả đều biểu diễn chính xác được trong IEEE 754 thì sẽ không phát sinh sai số tại bước biểu diễn hay bước làm tròn. **Ví dụ** `1.50 + 1.25 = 2.75` được biểu diễn chính xác nên kết quả vẫn đúng tuyệt đối.
>
> Ngược lại, nếu một số không thể biểu diễn chính xác trong IEEE 754 (chẳng hạn `0.1`, `0.2` có biểu diễn nhị phân vô hạn) thì ngay từ khi lưu vào bộ nhớ chúng đã phải làm tròn. Sau đó các phép toán tiếp theo sẽ làm việc trên các giá trị đã được làm tròn này, nên kết quả có thể tiếp tục xuất hiện sai số. Ví dụ `0.1 + 0.2` không cho đúng chính xác `0.3`.

#### 3.1.1.Hai phương pháp xử lý biểu diễn nhị phân hữu hạn và vô hạn

Phần này loại bỏ những yếu tố dư thừa để tối ưu thời gian khi làm việc với nhị phân vô hạn và hữu hạn khi biễu diễn số thực dưới dạng hệ cơ số 2. Chúng ta phân chúng theo hai trường hợp:

**trường hợp 1:** Nếu muốn tính số thực lấy nhị phân của significand hay được gọi đơn giản là phần thập phân, mục đích là lấy phần nguyên `0 hoặc 1` để phục vụ cho việc encode thì ta xét bảng, ví dụ :

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

**tổng cộng :** $$\large0.81\approx0.1100111101011100001010\ldots_{2}$$ (đây gọi là thu thập nhị phân của phần thập phân). Phần này dùng khi ta muốn chuyển phần thập phân sang hệ cơ số 2 (nhị phân)

<details>
	<summary><b>[Chi tiết]</b> làm việc số hữu hạn với Sigma</summary>

<table>
<tr>
<td>

---

<div align="center">

$$\Large
\sum_{k=m}^{n}b_k2^k
$$

</div>

Với $$\large b_{k}\in\{0,1\}$$ và chỉ có hữu hạn số hạng, đều có biểu diễn nhị phân hữu hạn. Trong đó ý nghĩa của biểu thức trong trường hợp này là :

- k : k là chỉ số (index). Nó lần lượt nhận các giá trị `m, m + 1, m + 2, ... n`

- m : cận dưới (lower bound) của k. Nó cho biết k bắt đầu từ đâu

- n : cận trên (upper bound) của k. Nó cho biết k dừng ở đâu

- $$\large b_{k}$$ : hệ số tại vị trí k ,chỉ nhận 0 hoặc 1.

- $$\large2^{k}$$ : tính trọng số theo hệ cơ số 2 (nhị phân)

<details>
	<summary><b>[Chi tiết]</b> Chi tiết về các ý nghĩa của biểu thức trên tại đây</summary>

<table>
<tr>
<td>

---

Đầu tiên là chỉ số ký hiệu (k) trong biểu thức này là biến chỉ số tới n lần theo số lượng từ cận dưới (m) tới giới hạn cận trên (n) và ký hiệu sigma ($$\large\sum$$) đây là ký hiệu yêu cầu cộng các giá trị tương ứng. **Ví dụ:**

<div align="center">

$$\Large
\sum_{k=5}^{7}k = 5 + 6 + 7
$$

</div>

Ở đây, k bắt đầu từ cận dưới 5, sau đó lần lượt nhận các giá trị 6 và 7. Khi k đạt tới cận trên 7, quá trình cộng kết thúc:

```
k = 5 -> lấy 5
k = 6 -> lấy 6
k = 7 -> lấy 7
```

Vì vậy :

<div align="center">

$$\Large
\sum_{k=5}^{7}k = 5 + 6 + 7 = 18
$$

</div>

Còn các giá trị như $$\large b_{k}$$ là hệ số tại vị trí k ,chỉ nhận 0 hoặc 1. Nghĩa là xét các vị trí của bit, **ví dụ** cho :

| vị trí bit | 5 | 4 | 3 | 2 | 1 | 0 |
|------------|---|---|---|---|---|---|
| các bit    | 0 | 1 | 1 | 0 | 1 | 0 |

vì vậy : $$\large b_{0} = 0$$, $$\large b_{1} = 1$$, $$\large b_{2} = 0$$, $$\large b_{3} = 1$$, $$\large b_{4} = 1$$, $$\large b_{5} = 0$$. Nên $$\large b_{k}$$ là bit tại vị trí k, đồng thời đóng vai trò là trọng số của hệ số $$\large2^{k}$$. Vì đây là hệ nhị phân nên $$\large b_{k} \in \{0,1\}$$

còn ký hiệu $$\large2^k$$ là trọng số của vị trí bit k trong hệ nhị phân. **Ví dụ:**

| $$\large k$$ | $$\large b_k$$ |    $$\large2^{k}$$ | $$\large b_k2^{k}$$ |
| :--: | :----: | :-------: | :-------: |
|   5 |     0 | $$\large2^{5}=32$$ |      0 |
|   4 |     1 | $$\large2^{4}=16$$ |     16 |
|   3 |     1 | $$\large2^{3}=8$$ |      8 |
|   2 |     0 | $$\large2^{2}=4$$ |      0 |
|   1 |     1 | $$\large2^{1}=2$$ |      2 |
|   0 |     0 | $$\large2^{0}=1$$ |      0 |

nó thuộc danh mục là tính trọng số và là giá trị hệ cơ số 10 của toàn chuỗi nhị phân sau khi cộng lại, nên nếu vị trí bit là 0 nó là 0 và 1 nó là chính giá trị trọng số của hệ số $$\large2^{k}$$. Điều này cũng đã được đề cập tới ở phần [two-complement-code](https://github.com/tranquanghao708/CSAPP-learning/blob/main/writeup/two-complement-code/two-complement-code.md).

Nên : $$\large0110102​_{2} = 0_{10} + 16_{10} + 8_{10} + 0_{10} + 2_{10} + 0_{10} = 26_{10}$$​ . Lúc này, dùng sigma mới thực sự ý nghĩa vì nó chỉ là gom gọn lại các phép toán dài hoằn của phép cộng lại thôi:

<div align="center">

$$\Large
\sum_{k=0}^{5}b_k2^k = 0 \times 2^{0} + 1 \times 2^{1} + 0 \times 2^{2} + 1 \times 2^{3} + 1 \times 2^{4} + 0 \times 2^{5} = 26
$$

</div>

Đây chính là toàn bộ ý nghĩa của biểu thức. Nó lấy các vị trí bit nhân với hệ số $$\large2^{k}$$ và cộng lại ra giá trị

<sub>--đã hết phần giải thích--</sub>

---

</td>
</tr>
</table>
</details>

<sub>--đã hết phần giải thích--</sub>

---

</td>
</tr>
</table>
</details>

**trường hợp 2:** Nếu chỉ muốn biết số thập phân này khi biểu diễn dưới hệ cơ số 2 (nhị phân) là số hữu hạn hay vô hạn, nhưng ko cần lấy nhị phân. Nghĩa là chỉ muốn biết nó là vô hạn hay hữu hạn chứ ko cần phải covert sang hệ nhị phân. Thì ta có hai cách, cách đầu tiên thì tính bảng giá trị như trên ra cũng ổn nhưng thực tế kỹ thuật này nó ko tối ưu hóa thời gian cho công đoạn này, bây giờ ta khám phá tới định lý toán học đã được đề cập tới ở chương [3.1.biểu diễn nhị phân hữu hạn và biểu diễn nhị phân vô hạn](#31biểu-diễn-nhị-phân-hữu-hạn-và-biểu-diễn-nhị-phân-vô-hạn)
đó là định lý tiêu chuẩn phân số

<p align="center">

<kbd>

<img src="image/image27.png" alt="định lý chương 3.1" width="980"/>

</kbd>

</p>

> định lý được đề cập tới tại chương 3.1

Ở đây, ta khám phá cách dùng định lý tiêu chuẩn phân số để tối ưu hóa thay vì cứ nhân hai liên tục như :

<p align="center">

<kbd>

<img src="image/image28.png" alt="nhân hai liên tục" width="680"/>

</kbd>

</p>

và điều này rất bất tiện, tốn times và gây rối lẫn sai nhiều hơn. Thay vào đó ta có cách phù hợp hơn khi làm việc chỉ để nhận biết số hữu hạn và vô hạn chính là dùng phân số. Cách làm đầu tiên ta cần chuyển số thập phân sang dạng phân số tối giản, tiếp theo là phân tích mẫu số và so sánh nếu mẫu số chỉ chứa thừa số nguyên tố $$\large2^{N}\rightarrow\text{hữu hạn}$$ ,nhưng nếu nó còn chứa bất kỳ thừa số nguyên tố nào khác `(3,5,7...)` $$\large\rightarrow\text{vô hạn}$$

**Ví dụ:** Ta muốn biết số `0.3` là số hữu hạn hay vô hạn, trước tiên ta biến đổi thập phân sang phân số trước đã, ta có $$\large0.3_{10} = \frac{3}{10}$$

<details>
	<summary><b>[Chi tiết]</b> Cách chuyển đổi số thập phân sang phân số</summary>

<table>
<tr>
<td>

---

Trước tiên về toán học căn bản, ta cần phải nhìn vào số thập phân xem, nó có bao nhiêu chữ số sau dấu phẩy để quyết định phần mẫu là số đơn vị, chục, trăm v.v.. Còn phần tử ta xem giá trị ước chung lớn nhất để suy ra. **Ví dụ** với số `0.25` đầu tiên ta cần phải hiểu, hệ cơ số của số nguyên là `10` trong tin học, tiếp theo như đã nói ta nhìn vào số thập phân ở đây là `0.25` nó có bao nhiêu số sau dấu phẩy, ta thấy nó có 2 số là `25` sau dấu phẩy vậy ta có $$\large10^{2} = 100_{10}$$ và số `10` chính là hệ cơ số của số nguyên

Vậy nên ta có mẫu là `100`, tiếp theo phần `tử` của phân số để biết ta tính ước chung lớn nhất `GCD` ta cần biết phải lấy gì vào ước chung lớn nhất, đó chính là tất cả giá trị ở phần đuôi sau dấu phẩy (ko lấy phàn nguyên) và số giá trị `n(value)`, ở đây ta có tất cả giá trị ở phần đuôi sau dấu phẩy `0.25` là `25` vì giá trị này nằm sau phần đuôi, tới lượt là số giá trị `n(value)` là `100` là cái mà ta nhìn vào phần số thập phân như trên. Vậy ta có `GCD(25,100) = 25`

Nên từ dữ kiện, ta có $$\large10^{2} = 100_{10}$$ cho mẫu và `GCD(25,100) = 25` cho tử thì ta lấy giá trị kết quả của ước chung lớn nhất chia cho cả mẫu và tử và ta có phân số 

<div align="center">

$$\large
\boxed{0.25 = \frac{25 \div 25}{100 \div 25} = \frac{1}{4}}
$$

</div>

ví dụ tiếp theo, ta cho `0.319` bây giờ ta thấy có 3 số sau dấu phẩy suy ra tử là `1000`, và mẫu là `GCD(319,1000) = 1` ta thấy 1 nghĩa là ko thể rút được nữa vì nếu chia cả hai mẫu và tử với 1 chúng vẫn là chính nó nên trường hợp này ta giữ nguyên. Suy ra :

<div align="center">

$\large
\boxed{0.319 = \frac{319}{1000}}
$

</div>

<sub>--đã hết phần giải thích--</sub>

---

</td>
</tr>
</table>
</details>

Bây giờ từ $$\large\frac{3}{10}$$ ta cần phân tích mẫu số với thừa số nguyên tố $$\large2^{N}$$, với `10` ta có $$\large2\times5 = 10_{10}$$ vậy trong đó có `5` mà gía trị số này lại ko chia hết cho 2, nên số thực `0.3` khi biểu diễn dưới dạng nhị phân là vô hạn. Đây chính xác là thứ ta muốn chứng minh mà không cần ngồi nhân 2 hàng chục/hàng trăm bước với trường hợp này

<details>
	<summary><b>[Câu hỏi]</b> Tại sao ko dùng printf để kiểm chứng, ví dụ printf nó in ra chuẩn xác số là hữu hạn còn có sự sai lệch là vô hạn?</summary>

---

Câu hỏi khá hay, điều này có một số lý do khiến cách này bị phế. Vậy dùng được ko, vốn dĩ cách này khá hiệu quả và dùng được với các số thuần như `1.0`, `0.1` v.v. chuẩn hệ cơ số 10 vào một biến. Nhưng với các số có hệ cơ số 16 như  chuỗi số `0x1.000002p-24f` ở phần [minh họa với C tại round toward infinity](#35round-toward-positive-infinity-), nếu dùng cách này với chuỗi số này thì các lập trình viên hay reverse engineer đều bị nó lừa vì sự sai số.

Cách này vốn dĩ ngắm vào sự sai số, hữu hạn thì chính xác còn vô hạn thì sai số vì rounding (cắt bit do giới hạn nhị phân). Nhưng với hệ cơ số 16 như trên thì hiếm hoặc rất khó có thể phân biệt được chúng là số vô hạn hay hữu hạn nếu dùng printf mà đi in ra terminal và soi số thập phân sau nó. Với hệ cơ số 16 như chuỗi `0x1.000002p-24f` ta bắt buộc phải đi dùng định lý phân số mới có thể xác định được, ko thể dùng printf hay đi nhân 2 liên tục vì một cái là bị lừa, một cái là cực hình. Proof để chứng minh printf vô dụng với hệ cơ số 16. Ở đoạn code tại phần [minh họa với C tại round toward infinity](#35round-toward-positive-infinity-) ta dùng nó và chạy. Ta thấy :

<p align="center">
	<img alt="Proof ko thể dùng printf để so sánh số thực hữu hạn vô hạn hệ cơ số 16" src="image/image30.png">
</p>

Từ trong ảnh, ta thấy dòng số hai là printf ra giá trị của chuỗi `0x1.000002p-24f` ra terminal, ta thấy 3 trường hợp in thấp hơn, vừa đủ, hơn 32bits fraction nó luôn đánh lừa là số đó trông như vô hạn tuần hoàn. Để so sánh hệ cơ số 16 bắt buộc phải dùng định lý phân số là cách khỏe hơn rồi

<sub>--Đã hết phần giải thích--</sub>

---

</details>

> [!IMPORTANT]
> **Lưu ý cực kỳ quan trọng:** Về định lý phân số suy ra biễu diễn nhị phân vô hạn hữu hạn hoàn toàn có thể làm được. Nhưng điều kiện rất nặng về phần nhân tố là phải chính xác, nếu phần nhân tố ko chính xác thì khả năng cao kết quả suy luận nhị phân hữu hạn hay vô hạn đều ko còn đúng nữa. 
>
> **Ví dụ** $$\large40 = 20 \times 2$$ ta thấy modulo với hai nhân tố `20` và `2` đều là chia hết nhưng ko có nghĩa nó là biễu diễn nhị phân hữu hạn, thực chất phép tính này chưa nhân tố hết. Nhân tố thực sự của `40` là $$\large40 = 2^{3} \times 5$$ ta thấy có số `5`, vậy suy ra số `40` là biễu diễn nhị phân vô hạn.
>
> Từ đó ta thấy, việc ko nhân tố hết giá trị hợp số sẽ rất dễ bị đánh lừa là suy đoán nó hữu hạn nhưng thực chất nó vô hạn. Nên việc nhân tố ở phần này là cực kỳ quan trọng phần nhân tố có chi tiết tại thẻ details ở phần ví dụ với C của chương [3.5.Round toward positive infinity (+∞)](#35round-toward-positive-infinity-)

### 3.2.Round to nearest, ties to even

- Đây là chế độ mặc định của việc làm tròn số thực dấu phẩy động của IEEE , nó thực hiện làm tròn về số gần nhất, nếu đúng giữa hai số thì chọn số chẵn. Ý tưởng gồm hai bước, đầu tiên là nó chọn giá trị gần nhất với số cần biểu diễn, thứ hai là phân theo ba trường hợp, trường hợp số nhỏ hơn nữa sẽ giữ nguyên, trường hợp số lớn hơn nữa sẽ làm tròn lên, trường hợp số đúng bằng nữa (tie) thì chọn số bit cuối là 0 (even)

**Đầu tiên :** làm tròn về số gần nhất, **ví dụ** `0.3244` làm tròn thành `0.324`, `0.3246` làm tròn thành `0.325` đơn giản là làm tròn về số gần nhât

**Thứ hai :** như trên sẽ phân theo ba trường hợp 

nếu trường hợp số nhỏ hơn nữa sẽ giữ nguyên **ví dụ** Cpu chỉ giữ 2 fraction ở bit, cho bit biểu diễn số thực như sau : $$\large1.010001_{2} = \mathbf{1.265625_{10}}$$ và bây giờ CPU lấy 2 fraction suy ra nó chỉ có thể biểu diễn làm tròn $$\large1.01_{2} = 0100_{2}$$ hoặc $$\large1.10_{2} = 1000_{2}$$ và bit bị cắt là $$\large0001_{2}$$

- **Lưu ý :** giá trị $$\large1.10_{2} = 1000_{2}$$ và $$\large1.01_{2} = 0100_{2}$$ ở đây ta thấy có phần nguyên là bit 1, nhưng việc quy đổi và so sánh ở trường hợp này là chỉ tính các bit fraction chứ không phải phần nguyên

bây giờ so sánh **phần bị cắt với đúng một ngưỡng là một nữa của ULP**:

> Phần details về ULP

<details>
	<summary><b>[Chi tiết]</b> ULP(unit in the last place)</summary>

<table>
<tr>
<td>

---

<br>

Đây là khái niệm dùng để giải thích vì sao CPU làm tròn bằng cách này, không phải cấu trúc chính của IEEE. Về nghĩa đen là giá trị của 1 đơn vị ở bit cuối cùng ở fraction, đơn giản hơn nó là khoảng cách giữa hai số IEEE 754 có thể biểu diễn được **ví dụ** sau chuẩn hóa ta có tập hợp $$\large(1.00_{2},1.01_{2},1.10_{2},1.11_{2})$$ và các số này lần lượt tương ứng với tập hợp $$\large(1.00_{10},1.25_{10},1.50_{10},1.75_{10})$$ và bây giờ khoảng cách giữa chúng là :

| phép tính | kết quả |
|:-----------:|:---------:|
| 1.25 - 1.00 | 0.25 |
| 1.50 - 1.25 | 0.25 |
| 1.75 - 1.50 | 0.25 |

Vậy ULP = 0.25, nếu gặp trường hợp như `một nữa của ULP` thì lấy đó chia hai lên thôi, ví dụ $$\large\frac{0.25}{2} = 0.125$$ thì con số `0.125` này chính là con số ở ngưỡng mà IEEE quyết định làm tròn 

<br>

<sub>— Hết phần giải thích —</sub>

---

</td>
</tr>
</table>
</td>
</tr>
</table>
</details>

Ở đây ta tiến hành tính ULP trước tiên phải biết $$\large1.01 = \mathbf{1.25_{10}}$$ và $$\large1.10 = \mathbf{1.50_{10}}$$ :

| phép tính | kết quả |
|:-----------:|:---------:|
| 1.50 - 1.25 | 0.25 |

$\large\mathrm{ULP} = \boxed{0.25}$ vậy bây giờ ta biết $$\large0.25_{10} = \mathbf{0.01_{2}}$$ bây giờ ta lấy nó chia cho hai vì half ULP mà $$\large\frac{0.25}{2} = \mathbf{0.125_{10}}$$ bây giờ ta biết $$\large0.125_{10} = 0.001_{2}$$ bây giờ viết đầy đủ 4bit ta có $$\large0.0010_{2}$$ và nó chính là ngưỡng làm tròn, tiến hành so sánh phần bị cắt với half ULP $$\large0001_{2} < 0010_{2}$$ ta thấy nó nhỏ hơn vậy nó sẽ giữ nguyên $$\large\boxed{1.01_{2}}$$

<details>
	<summary><b>[Câu hỏi]</b> Vì sao lại đem phần bị cắt đi so với half ULP?</summary> 

<table>
<tr>
<td>

---

<br>

- **Vì sao lại đem phần bit bị cắt đi so với half ULP:** Vì phần bị cắt chính là phần sai số (error) nếu giữ nguyên số hiện tại, IEEE cần biết lượng sai số này xem nó lớn hay nhỏ hơn với nữa khoảng cách giữa hai số biểu diễn được (half ULP) để quyết định giữ nguyên hay làm tròn lên, Bây giờ **giả sử** CPU chỉ giữ lại một số lượng bit fraction nhất định. Khi cắt bớt bit, phần bị cắt là phần sai số (lượng giá trị bị mất), sau khi đã xác định hai giá trị IEEE có thể biểu diễn gần nhất, IEEE chỉ cần xét phần giá trị bị mất (phần bị cắt) để quyết định làm tròn., nó chỉ biết lượng giá trị bị mất này lớn đến đâu, IEEE lấy lượng gía trị bị mất so sánh với một nữa ngưỡng khoảng cách biểu diễn giữa hai số (half ULP), phần bị cắt chính là sai số khi giữ nguyên, còn half ULP là ngưỡng quyết định. IEEE chỉ cần so sánh hai đại lượng này để biết nên giữ nguyên hay làm tròn lên. Đây cũng là bản chất thuật toán, CPU nó không so sánh hai số, nó chỉ so sánh số bit bị cắt với half ULP

<br>

<sub>— Hết phần giải thích —</sub>

---

</td>
</tr>
</table>
</td>
</tr>
</table>
</details>

nếu trường hợp số lớn hơn nữa sẽ làm tròn, **ví dụ** $$\large1.010011_{2}$$ và như cũ CPU giữ lại 2 fraction là $$\large1.01_{2}$$ và $$\large1.10_{2}$$ và số bit bị cắt là $$\large0011_{2}$$ bây giờ ta tính ULP:

| phép tính | kết quả |
|:-----------:|:---------:|
| 1.50 - 1.25 | 0.25 |

vẫn như cũ, $$\large\mathrm{ULP} = \boxed{0.25}$$ và ta biết half ULP của này là $$\large0.125_{10} = 0.001_{2}$$ tròn 4bit là $$\large0.0010_{2}$$ vì đó có sẵn ở ví dụ trước. Bây giờ so sánh phần sai số (round error) và nữa khoảng cách giữa hai số biểu diễn được (half ULP) suy ra $$\large0011_{2} > 0.0010_{2}$$ suy ra nó sẽ làm tròn thành $$\large\boxed{1.10}$$

> Câu hỏi về làm tròn

<details>
	<summary><b>[Câu hỏi]</b> Nhưng vấn đề mà chúng ta thường hay rối ở đây là nếu có lệnh quyết định làm tròn sau khi so sánh half ULP thì tự hỏi nó làm tròn một đơn vị bit hay làm tròn cả dãy bit theo mô hình toán học?</summary>

<table>
<tr>
<td>

---

<br>

- IEEE 754 không làm tròn từng bit bị cắt, cũng không làm tròn cả dãy bit theo kiểu toán học. Nó chỉ thay đổi đúng một đơn vị ở bit fraction cuối cùng được giữ lại (1 ULP của kết quả), rồi để phép cộng nhị phân tự lan carry nếu cần. **Ví dụ** giả sử CPU chỉ lưu 4 fraction `1.0111 100...` trong đó `100...` sau cùng này là số bit bị cắt, sau khi xét GRS (G = 1, R = 0, S = 0) nếu G = 1 rồi thì chắc chắn nó lớn hơn half ULP nên điều này quyết định làm tròn, bây giờ mới tới phần làm tròn CPU nó không biến `100...` thành `000...` hay xử lý từng bit phía sau nó chỉ thực hiện cộng thêm đúng một bit ở fraction cuối cùng được giữ.

**Ví dụ** $$\large1.0111_{2}$$ CPU giữ 4 fration trong đó là $$\large0111_{2}$$, bit cuối cùng của fraction là `1`, còn bit đầu tiên của fraction là `0`

<p align="center">
	<image alt="alt text" src="image/image19.png" width="680"/>
</p>

khi làm tròn, CPU chỉ thực hiện cộng một đơn vị bit vào bit cuối cùng của fraction thôi nghĩa là nó chỉ thực hiện:

```
 1.0111 (gốc)
+
 0.0001 (cộng một đơn vị vào bit cuối cùng)
--------
 1.1000 (kết quả làm tròn)
```

đó chính là cách CPU làm tròn bit khi số bit bị cắt lớn hơn half ULP

<br>

<sub>— Hết phần giải thích —</sub>

---

</td>
</tr>
</table>
</details>

nếu trường hợp số bằng đúng bằng nữa (tie) thì chọn số bit cuối là 0 (even) nó sẽ chọn số có LSB là 0, **ví dụ** ta có $$\large0.010010_{2}$$ với CPU chỉ giữ fraction ta có hai dạng như ví dụ trước là $$\large0.01_{2}$$ hay $$\large0.10_{2}$$ ở đây phần bị cắt là $$\large0010_{2}$$ và ta biết `half ULP = 0.125` vì nó vẫn tương tự ở các ví dụ trên thôi.

Bây giờ, ta so sánh thấy phần đặc biệt là half ULP bằng với bit bị cắt $$\mathbf{\large0010_{2}\text{(số bit bị cắt)} == 0010_{2}\text{(Half ULP)}}$$ vì $$\large0.125_{10} = 0.001_{2}\text{(half ULP)}$$ tính theo đúng 4bit sẽ là $$\large\mathbf{0010_{2} \text{(half ULP)}}$$ ở đây việc nó bằng nhau thế này ta gọi đó là trường hợp bằng đúng bằng nữa (tie) nghĩa là giá trị phần bị cắt (round error) bằng đúng half ULP, tức sai số khi giữ nguyên và sai số khi làm tròn lên là như nhau. Số cần biểu diễn nằm đúng ở chính giữa hai số IEEE 754 có thể biểu diễn được.

Lúc này, IEEE không được phép lúc nào cũng làm tròn lên vì nếu vậy thì nó sẽ sinh ra sai số dương tích lũy sau hàng triệu phép tính, thay vào đó nó quy định nếu đúng bằng half ULP thì chọn số có bit cuối cùng (LSB) bằng 0 (even). Ví dụ trường hợp này $$\mathbf{\large0010_{2}\text{(số bit bị cắt)} == 0010_{2}\text{(Half ULP)}}$$ thì đối tượng được làm tròn là $$\large0.10_{2}$$ hay $$\large0.01_{2}$$

Ta phân tích hai số này, $$\large0.10_{2}$$ có `LSB = 0` và $$\large0.01_{2}$$ có `LSB = 1` ta thấy IEEE quy định thì nó sẽ chọn số bit cuối cùng (LSB) bằng 0 (even) thì `LSB = 1` sẽ không được chọn vì nó khác 0, `LSB = 0` sẽ được chọn vì nó bằng 0. Nên, số làm tròn sẽ thành $$\large\boxed{0.10_{2}}$$ vì nó có `LSB = 0` (thỏa mãn quy định của IEEE)

> [!IMPORTANT]
> Round to nearest, ties to even là nghệ thuật làm tròn mặc định mà chuẩn IEEE quy định:
> - nếu `(half ULP) < (số bit bị cắt)`, đây được gọi là số lớn hơn nữa và nó sẽ được làm tròn 
> - nếu `(half ULP) > (số bit bị cắt)`, đây được gọi là số bé hơn nữa và nó sẽ được giữ nguyên
> - nếu `(half ULP) = (số bit bị cắt)`, đây được gọi là số bằng đúng bằng nữa (tie) và nó sẽ chọn LSB có bit là 0 (even)
>
> so sánh một nữa khoảng cách giữa hai số biểu diễn được (half ULP) với bit bị cắt, điều dễ nhầm là chúng ta thường lấy bit bị cắt đi so sánh với bit fraction

#### 3.2.1.guard bit

Guard bit là bit đầu tiên bị cắt bỏ ngay sau bit fraction cuối cùng mà CPU quyết định giữ lại. **Ví dụ** như các ví dụ trên thì CPU giữ 2fraction, ở đây lấy ví dụ với bit $$\large1.0101101_{2}$$ bây giờ fraction là $$\large1.01_{2}$$ còn bit bị cắt là $$\large01101_{2}$$ bây giờ CPU sẽ chia số bit bị cắt này ra 4 phần trong đó có fraction, guard bit (G) , round bit (R) và sticky bit (S), nó sẽ chia như sau :

| Fraction | G | R | S |
|----------|---|---|---|
| 1.01	   | 0 | 1 | 101 |

Ta thấy, `G = 0` suy ra `guard bit = 0`, `R = 1` suy ra `round bit = 1`, `S = 1` suy ra `sticky bit = 1 (vì ít nhất nó cũng có bit 1)`

**Guard bit dùng để làm gì?:** Guard bit là phép kiểm tra đầu tiên. Nếu G = 0 thì chắc chắn nhỏ hơn half ULP. Nếu G = 1 thì chưa thể kết luận đã vượt half ULP hay mới đúng bằng half ULP, nên CPU phải kiểm tra thêm Round bit và Sticky bit. Thay vì tính thủ công là ULP xong chia lấy half ULP xong so sánh round error v..v thì CPU chỉ cần nhìn Guardbit, roundbit, stickybit (GRS). Nhưng ở đây ta chỉ nói riêng về Guardbit, nếu CPU nhìn `guardbit = 0` chắc chắn `x < half ULP` còn nếu `guardbit = 1` thì cần phải soi thêm round và sticky

#### 3.2.2.round bit

Round bit là bit thứ hai bị cắt, nó nằm phía sau Guard bit. Nó có ý nghĩa nếu guardbit là 1, nếu guardbit (G) là 0 thì biết chắc chắn là `x < half ULP` rồi không cần phải soi round và sticky, nhưng nếu guard là 1 thì bây giờ mới soi round. Ở đây, cũng như ví dụ trên ta có :

| Fraction | G | R | S |
|:----------:|:---:|:---:|:---:|
| 1.01	   | 0 | 1 | 101 |

Cái này chắc chắn là `x < half ULP` vì `G = 0` nên round sẽ không có ý nghĩa, nhưng giả sử ta cho `G = 1` như :

| Fraction | G | R | S |
|:----------:|:---:|:---:|:---:|
| 1.01	   | 1 | 1 | 101 |

thì lúc này `G = 1` nó sẽ soi thêm R vì lúc này round mới thực sự có ý nghĩa, nếu `G = 1 và R = 1` thì nó chắc chắn sẽ lớn hơn half ULP `x > half ULP` lúc này sẽ làm tròn lên

> [!IMPORTANT]
> Nếu `G = 0` thì R và S sẽ không cần soi nữa, vì nó chỉ có ý nghĩa nếu `G = 1` là trước tiên xong mới tới R và mới tới S.
> - Nếu `G = 1 và R = 1` thì chắc chắn lớn hơn half ULP
> - Nếu `G = 1 và R = 0` thì phải soi thêm Sticky bit

#### 3.2.3.sticky bit

Sticky bit là bit thứ 3, nó đứng ngay sau round bit cái đặc biệt của sticky bit này không phải là một bit cụ thể bị cắt, mà là kết quả OR với tất cả các bit còn lại phía sau roundbit, nó luôn soi là sau roundbit còn bit nào nữa không, nếu không còn bit nào nữa thì `S = 0` còn nếu có thì `S = 1`. Đó là lý do mà sticky bit (S) là bit 0 hoặc bit 1 dù sau nó là hàng chục hay hàng trăm bit. Ví dụ ở trên là ;

| Fraction | G | R | S |
|:----------:|:---:|:---:|:---:|
| 1.01	   | 1 | 1 | 101 |

Ở đây ta thấy trường sticky bit có chuỗi nhị phân là `101` vậy nên sticky sẽ có bit 1 `S = 1`. Ví dụ khác :

| Fraction | G | R | S |
|:----------:|:---:|:---:|:---:|
| 1.01	   | 1 | 1 | 000 |

Ở đây ta thấy trường sticky bit có chuỗi nhị phân là `000` vậy nên sticky sẽ có bit 1 `S = 0` (do không có bit nào là 1). Ví dụ khác :

| Fraction | G | R | S |
|:----------:|:---:|:---:|:---:|
| 1.01	   | 1 | 1 | 010 |

Ở đây ta thấy trường sticky bit có chuỗi nhị phân là `010` vậy nên sticky sẽ có bit 1 `S = 1` (do có bit giữa là 1). Từ 3 ví dụ, ta thấy hễ một binary strings sau trường roundbit có một bit 1 thì `S = 1` còn nếu không có bit 1 nào thì `S = 0`

**Sticky bit dùng để làm gì?:** Nó được dùng khi `G = 1, R = 0` lúc này CPU vẫn chưa biết đang đúng half ULP `x == half ULP` hay đã lớn hơn half ULP `x > half ULP` sticky bit sẽ phân biệt hai trường hợp này

#### 3.2.4.cách phần cứng dùng các guard bit, round bit và sticky bit để xác định ba trường hợp

Theo 3 chương về guard bit, round bit, sticky bit (GRS) ta có bảng :

| G | R | S | Kết luận         |
| - | - | - | ---------------- |
| 0 | x | x | < half ULP       |
| 1 | 0 | 0 | = half ULP (tie) |
| 1 | 0 | 1 | > half ULP       |
| 1 | 1 | x | > half ULP       |

các important trên cho thấy, nếu `G = 0` chắc chắn `x < half ULP` nếu `R = 1, G = 1` chắc chắn `x > half ULP`. Nên phần cứng không thể soi riêng biệt một bit trừ khi bit đó có quy luật khi là 0 thì chắc chắn có giá trị này ví dụ như guard bit. Bảng trên thì đó là cách phần cứng dùng GRS để biết khi nào giữ nguyên, khi nào làm tròn và khi nào lấy LSB = 0.

<details>
	<summary><b>[Câu hỏi]</b> Vì sao không thể quan sát Guard, Round và Sticky bit trên một biến float?</summary>

<table>
<tr>
<td>

---

<br>

**Ý tưởng:** dùng số thực vô hạn để tạo ra hiệu ứng rounding của hệ thống, và tính toán lại để so sánh chế độ làm tròn round to nearest, ties to even xem có đúng như ban đầu không đồng thời truy tìm các bit bị cắt có thể là tầm 5 bit vì 2 bit cho G, R và 3 bit cho S. Ở đây, ta nhắm tới fraction và dùng float 32bit và fraction trong architecture này là 23bit bảng độ rộng được phân cho từng trường có tại chương [1.8.1.Độ lệch (Bias)](#181độ-lệch-bias)

```c
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main(void){
	float a = 0.1f; //số thực vô hạn
	int o,z;
	uint32_t raw;

	memcpy(&raw, &a, 4);

	printf(" infinity floating point numbers: %.23f\n raw: %08x\n binary: ",a,raw);

	for(int i = 0; i < 35; i++){ //cố tình để 35 in quá fraction
		o = (int)a; //ép kiểu để lấy phần nguyên, kết quả đầu tiên là 0
		printf("%d",o);
		a -= o; //lấy phần thập phân ví dụ 1 + 1.23 = 0.23
		a *= 2; //theo quy định encode thì phần thập phân nhân 2
	}
	printf("\n");
	return 0;
}
```

> gcc -o rounding_tester rounding_tester.c

<p align="center">
	<image alt="alt text" src="image/image16.png" width="680"/>
</p>

ta thấy đây là fraction sau khi IEEE754 đã hoàn tất quá trình encode và rounding, chứ không phải dãy bit vô hạn ban đầu và ta có `00001100110011001100110011010000000`

> Phần tính toán thủ công để lấy bit GRS và so sánh

<details>
	<summary><b>[Chi tiết]</b> tính toán (encode) lại sang nhị phân</summary>

<table>
<tr>
<td>

---

<br>

Để có thể xét, ta cần phải tính thủ công bằng tay. Encode số `0.1` theo chương [2.1.Encode](#21encode) thành nhị phân sao cho có phần bit bị cắt vượt quá 23 bit fraction. Lúc đó ta mới có thể thực hiện xét bit, rounding hay tính half ULP v.v. cũng hợp lệ vì ta đang dựng lại cách phần cứng thực sự tính toán số thực. Nhìn `0.1` ta biết ngay `sign = 0`, phần nguyên là 0 luôn bây giờ tính phần thập phân sang bit

| số  | nhân hai | bit lấy |
|:-----:|:----------:|:---------:|
| 0.1 | 0.2      | 0       |
| 0.2 | 0.4      | 0       |
| 0.4 | 0.8      | 0       |
| 0.8 | 1.6      | 1       |
| 0.6 | 1.2      | 1       |

`0.1` là số thực vô hạn, vòng tuần hoàn của nó là `0.1 -> (0.2 -> 0.4 -> 0.8 -> 0.6)` và quay lại `0.2` lần lượt theo trong ngoặc đơn. Vậy nên khi ta biết các bit của vòng tuần hoàn này là $$\large00011_{2}$$ ta tiến hành copy paste lên (vì dù sao cũng tính vẫn ra mà), nhưng bỏ bit ở số `0.1` đi ta có $$\large0011_{2}$$ vậy tiếp tục copy cho tới vượt qua 23bit fraction, ta có $$\large\boxed{00011001100110011001100110011_{2}}$$. Đây là nhị phân của phần fraction. Vậy còn sign ta có là `0` thì ta ghép vào đầu chuỗi nó sẽ thành như sau $$\large\boxed{\mathbf{0}00011001100110011001100110011_{2}}$$

đây là kết quả y chang như mã C đã tính cho chúng ta nhưng thực chất nó khác. Khác vì không có một bước trung gian nào khiến ta có thể bị che mắt, thay vào đó là tự tay tính để biết toàn bộ quá trình. Đây là cách chuẩn để lấy và so sánh GRS

<br>

<sub>— Hết phần giải thích —</sub>

---

</td>
</tr>
</table>
</details>

**nhưng ở đây dù có nhị phân đã được in quá fraction là 34bit trong đoạn code C thì chúng ta vẫn sẽ không đảm bảo thấy được GRS thật sự vì sao?**

vì nó là số vô hạn? hay vì nó không ở đầu bit bị cắt như lý thuyết?, tất cả đều sai. Nguyên nhân là do, trước khi đưa số thực như `0.1` vào float thực tế là phần cứng đã làm việc, tính toán, xét GRS và rounding trong lúc chuyển đổi literal, nên GRS đã bị bỏ. Ta chỉ có là số kết quả đã được làm tròn ngay từ lúc gán nó vào biến a kiểu float, vậy nên dù ta có xét GRS bit hay làm thế nào với số kết quả này `0.10000000149011611938477` bao nhiêu lần đi chăng nữa thì điều đó càng thêm vô lý cũng như vô ích với kết quả được được tính sẵn thế này.

Nên mới nói, dù ta có xét GRS, tính và so sánh bao nhiêu half ULP nếu không hiểu điều này rất dễ sinh nhầm lẫn là nhỏ hơn half ULP là giữ nguyên sao nó vẫn làm tròn, mà nó làm tròn bằng cách cộng 1 vào phần tử cuối fraction sao lại ra kết quả này (vì đó là số đã được tính và làm tròn trước khi gán vào float bởi phần cứng, GRS đã bị bại bỏ và chúng ta không thể tính gì thêm nữa)

Muốn biết GRS của quá trình encode ban đầu thì phải quan sát chuỗi bit trước khi làm tròn, dù có thể tự động hóa nào đó như dùng casio hay các phép tính nhân chia v.v. nhưng việc encode thì phải thủ công để suy ra xét GRS chính xác nhất. **Ví dụ** đoạn code trên cho binary gần sát như binary đã caculated thủ công nhưng việc xét GRS về cơ bản thì hòan toàn sai vì chúng ta không thể đảm bảo nó đúng

**Khác biệt giữa bit dùng để quyết định rounding và bit của kết quả sau khi rounding**

Bit dùng để quyết định rounding theo lý thuyết thường là 3bit đầu của bit bị cắt (đi quá fraction), bit của kết quả sau khi rounding thoáng qua giống với sự tính toán thủ công khi ta dùng các ngôn ngữ lập trình để tự động hóa nhưng về cơ bản chúng đã thực hiện rounding ở mức phần cứng và các bit thường sẽ không đảm bảo chắc chắn là nó chính xác như tính tay hay tính tay chính xác hay không. Loại bit của kết quả sau khi rounding là loại bit đã trải qua xử lý của phần cứng FPU để đưa ra kết quả **ví dụ như** output bit `00001100110011001100110011010000000` của đoạn C tính toán như trên là loại bit đã trải qua rounding

nhưng vấn đề khiến nó gần như trùng khớp với bit quyết định hay số thực được tính tay sang bit là sự sai số ở phần số thực diễn ra rất nhỏ xuất hiện tại bit bị cắt, hầu như còn nhỏ hơn 23-25 bit fraction. Để phân biệt hai loại bit này, ta cần phải hiễu rõ bit dùng để quyết định rounding phải chính xác (an toàn nhất là tính toán thủ công để lấy bit GRS), bit của kết quả sau khi rounding thường là bit của các chương trình nhị phân chẳng hạn như C tính toán, phần fraction luôn luôn là chính bit chuẩn xác, mức sai số chỉ xuất hiện với phần bit vượt quá phần fraction gọi là bit bị cắt và GRS cũng nằm ở 3bit đầu của phần bit bị cắt đó (Ta có thể tiếp tục tạo ra các bit phía sau từ giá trị float đã được làm tròn, nhưng các bit đó không còn là Guard, Round và Sticky bit của lần encode ban đầu. Chúng chỉ là các bit sinh ra từ giá trị đã được làm tròn)

<br>

<sub>— Hết phần giải thích —</sub>

---

</td>
</tr>
</table>
</details>

#### 3.2.5.Thao tác Bitwise Raw Manipulation trên uint32_t

Ở đây, chúng ta sẽ thao tác chính xác bit thô trên `uint32_t`. Trước hêt, cần phải hiểu rõ thao tác số thực với FPU và `uint32_t` khác nhau thế nào :

| Tiêu chí | FPU | uint32_t |
|----------|-----|----------|
| **Bản chất** | Mạch phần cứng đại số số thực | Thao tác trên dãy 32 ô nhớ nhị phân |
| **Đơn vị xử lý** | Giá trị số thực | Mẫu bit thuần túy |
| **Xử lý số vô hạn** | Tự động làm tròn (GRS) theo chuẩn IEEE 754 | Không quan tâm giá trị, chỉ đọc/dịch/đảo bit |
| **Ngôn ngữ C** | Thực hiện qua các toán tử +, -, *, / trên float | Thực hiện qua memcpy, toán tử &, |, ^, <<, >> |

vậy thao tác bitwise raw manipulation trên `uint32_t` là dùng các toán tử bitwise như &, | , ^, << , >> và thực hiện với memcpy để thao tác với tầng bit thô của số thực, sau khi sao chép bit sang `uint32_t`, các phép toán tiếp theo (&, |, ^, <<, >>) chỉ thao tác trên mẫu bit, không kích hoạt các phép toán số thực của FPU, điều này tránh đụng chạm tới phần FPU vì các phép toán trên `uint32_t` không sử dụng pipeline số thực và chúng được thực hiện bởi ALU, không phải FPU do đó chúng ta có thể xử lý và đọc lượng bit đó một cách chính xác trong bộ nhớ

**Lưu ý** FPU vẫn có thể được sử dụng cho việc làm tròn, xử lý số thực sang phần nguyên hay nhi phân trước đó phổ biến khi gán `0.1f` vào một valriable, chương này chỉ thao tác nghĩa là dịch bit, dùng các phép toán nhị phân để thao tác với số thực thay cho cú pháp bình thường sẽ lỗi nếu thao tác trực tiếp với biến số thực

<details>
	<summary><b>[Chi tiết]</b> ví dụ với C</summary>

<table>
<tr>
<td>

---

<br>

```c
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main() {
    float a = 0.1f; //vẫn qua rounding
    uint32_t raw;
    
    // Bê nguyên 32 bit từ vùng nhớ của a sang raw
    memcpy(&raw, &a, sizeof(raw));

    // Tách 3 thành phần IEEE 754 bằng Bitwise operators
    uint32_t sign     = (raw >> 31) & 0x01; // Bit 31 là cái phần sign
    uint32_t exponent = (raw >> 23) & 0xFF; // Bit 23 -> 30 (8 bits) gán vô exponent
    uint32_t fraction = raw & 0x7FFFFF; // Bit 0 -> 22  (23 bits) fraction

    printf("Sign: %u\n", sign);
    printf("Exponent (Biased): %u (Actual: %d)\n", exponent, exponent - 127);
    printf("fraction (Raw Hex): 0x%06X\nFraction binary: ", fraction);

	//phần lấy mã nhị phân của trường fraction
	int o;
	for(int i = 22; i >= 0; i--){
		o = (fraction >> i) & 1;
		printf("%d",o);
	}
	printf("\n");

    return 0;
}
```

> gcc -o bitwise_manipulation bitwise_manipulation.c

<p align="center">
	<image alt="alt text" src="image/image17.png" width="680"/>
</p>

từ đoạn mã ta có sơ đồ biểu diễn logic như sau (để tránh gây hiểu lầm):

<p align="center">
	<image alt="alt text" src="image/image18.png" width="680"/>
</p>

Vậy nên nó chỉ thao tác đọc ghi v.v. , chứ không ngăn được FPU đã xử lý phần 0.1f

<br>

<sub>— Hết phần giải thích —</sub>

---

</td>
</tr>
</table>
</details>

#### 3.2.6.Vì sao phần cứng biết vị trí của Guard, Round và Sticky Bit?

Thực tế, FPU không đi tìm Guard, Round, Sticky trong dữ liệu đã lưu. Ba bit này được phần cứng của FPU tạo ra tạm thời trong quá trình tính toán. Ba loại bit này không hề tồn tại trong bộ nhớ, nó chỉ là các bit tạm được FPU tạo ra vì chuẩn IEEE 754 định nghĩa việc làm tròn dựa trên các bit vượt quá độ chính xác lưu trữ. GRS là cách phần cứng biểu diễn các bit đó để quyết định các quy tắc làm tròn round to nearest tie to even thay vì tính một nữa khoảng cách hai giá trị (half ULP) và so sánh chúng. Sau khi ba bit này được FPU dùng và so sánh hoàn tất, chúng sẽ bị bác bỏ và các dãy nhị phân dù có trùng khớp là 3 bit cuối GRS (tùy trường hợp và ngữ cảnh) thì về bản chất đó chỉ là trùng hợp

> [!IMPORTANT]
> GRS được tạo ra từ kết quả trung gian trước khi làm tròn, rồi được dùng để quyết định cách làm tròn, sau khi làm tròn 3bit này bị bác bỏ và nếu có thể thấy 3bit cuối khi thực hiện dump nhị phân của số thực đó thực chất chỉ là sự trùng hợp

### 3.3.Round to nearest, ties away from zero (Ties to away)

### 3.4.Round toward zero

`Round toward Zero (làm tròn về 0 hay còn gọi là truncation)` là chế độ làm tròn trong đó phần lẻ bị loại bỏ, khiến kết quả luôn tiến gần về giá trị 0. Chế độ này không xét khoảng cách giữa hai số biểu diễn được như Round to Nearest, Ties to Even, mà chỉ đơn giản cắt bỏ phần không thể biểu diễn. **Ví dụ** :

| Giá trị | Kết quả |
|:---------:|:---------:|
| 3.9     | 3       |
| 3.1     | 3       |
| -3.9    | -3      |
| -3.1    | -3      |

Điểm hay bị nhầm `round toward zero` $$\large\neq$$ ceil và floor

> phần cho ceil và floor

<details>
	<summary><b>[Câu hỏi]</b> ceil và floor là gì?</summary>

<table>
<tr>
<td>

---

<br>

đây là hai hàm toán học dùng để làm tròn về phía trên hoặc phía dưới một số thực:

Floor (hàm sàn) luôn làm tròn về phía âm vô cực ($$\large-\infty$$) và có ký hiệu ($$\large\lfloor x \rfloor$$) định nghĩa của nó là số nguyên lớn nhất nhỏ hơn hoặc bằng x. **Ví dụ:** 

|  (x) | $$\large\lfloor x \rfloor$$ |
| :---: | :-------: |
|  3.8 |        3 |
|  3.0 |        3 |
|  3.1 |        3 |
| -3.1 |       -4 |
| -3.8 |       -4 |

Ở đây, $$\large3 \leq 3.8$$ nên kết quả là 3, và $$\large-4 \leq -3.8$$ kết quả là -4 vì -4 là số nguyên lớn nhất thỏa điều kiện

Ceil (hàm trần) luôn làm tròn về phía dương vô cực ($$\large+\infty$$) và có ký hiệu $$\large\lceil x \rceil$$ định nghĩa của nó là số nguyên nhỏ nhất lớn hơn hoặc bằng x. **ví dụ:**

|  (x) | Ceil(x) |
| :---: | :------: |
|  3.1 |       4 |
|  3.8 |       4 |
|  3.0 |       3 |
| -3.1 |      -3 |
| -3.8 |      -3 |

Ở đây, $$\large4 \geq 3.1$$ nên kết quả là 4 và $$\large-3 \geq -3.1$$ nên kết quả là -3. Có thể mở rộng lý thuyết của hai hàm làm tròn này [tại đây](https://en-wikipedia-org.translate.goog/wiki/Floor_and_ceiling_functions?_x_tr_sl=en&_x_tr_tl=vi&_x_tr_hl=vi&_x_tr_pto=tc)

<details>
	<summary><b>[Chi tiết]</b> dùng hàm floor(),ceil() trong thư viện math.h để tính floor,ceil trong C</summary>

<table>
<tr>
<td>

---

<br>

```c
#include <math.h>
#include <stdio.h>

int main (void){
	printf(" floor 3.8 = %f\n ceil 3.8 = %f\n floor -3.8 = %f\n ceil -3.8 = %f\n",
	floor(3.8), // 3.0
	ceil(3.8), // 4.0

	floor(-3.8), // -4.0
	ceil(-3.8) // -3.0
	);
}
```

> gcc -o floor_ceil floor_ceil.c

<p align="center">
	<image alt="alt text" src="image/image22.png" width="680"/>
</p>

**Lưu ý:** `floor()` và `ceil()` trả về kiểu dấu phẩy động (double hoặc phiên bản tương ứng như `floorf()` cho `float`), không phải `int`. **Ví dụ** `floor(3.8)` trả về `3.0`, không phải `3`.

<br>

<sub>— Hết phần giải thích —</sub>

---

</td>
</tr>
</table>
</details>

<br>

<sub>— Hết phần giải thích —</sub>

---

</td>
</tr>
</table>
</details>

**so sánh floor, ceil và toward zero**

Ta cho bảng so sánh như sau:

| Giá trị | Toward Zero | Floor | Ceil |
| :-------: | :----------: | :----: | :---: |
| 3.9     |           3 |     3 |    4 |
| -3.9    |          -3 |    -4 |   -3 |

đối với số âm thì sự khác biệt khá rõ, floor luôn đi về phía âm vô cực ($$\large-\infty$$) còn `round toward zero` luôn đi về 0. **Ví dụ** ta cho `-3.8` thì :

| Chế độ            | Kết quả |
| :-----------------: | :------: |
| Floor             |      -4 |
| Ceil              |      -3 |
| Round toward Zero |      -3 |

ta thấy floor luôn làm tròn về $$\large-\infty$$ và ceil luôn làm tròn về $$\large+\infty$$ và `round toward zero` luôn tiến về số 0

> [!NOTE]
> **Lưu ý:** Đối với số dương, `Round toward Zero` và Floor cho cùng một kết quả. Đối với số âm, `Round toward Zero` và `Ceil` cho cùng một kết quả. Sự khác biệt chỉ xuất hiện khi số có phần lẻ.

Do đó, về cơ bản chương `round toward zero` này chỉ có vậy. Nếu chế độ làm tròn này được bật thì FPU không cần phải xét GRS vì đó thuộc round to nearest tie to even

<details>
	<summary><b>[Câu hỏi]</b> liệu round toward zero và (int)x.x có phải là một không?</summary>

<table>
<tr>
<td>

---

<br>

Gần giống, nhưng chúng không cùng một khái niệm. Trong nhiều ví dụ thì chế độ `round toward zero` cho kết quả khá tương đương với `(int)x.x` nhưng về bản chất thì `(int)x.x` là chỉ ép kiểu sang phần nguyên bỏ phần lẻ, điều này giống với hành vi của `round toward zero`. Nhưng có hai đặc điểm để chứng minh hai cái này khác: 

**đặc điểm thứ nhất:** là kết quả của `(int)x.x` nó là số nguyên nó bỏ phần số thực đi suy ra `3.3 = 3`, còn `round toward zero` cũng có kết quả giá trị nhưng nó biểu diễn dạng số thực `3.3 = 3.0` và `3.0` cùng giá trị với `3` nhưng khác cách trình bày

**đặc điểm thứ hai:** `(int)x.x` là chuyển đổi kiểu dữ liệu từ số thực sang số nguyên theo quy tắc của ngôn ngữ C. `Round toward Zero` là một chế độ làm tròn của IEEE 754 dùng cho các phép toán dấu phẩy động.

Nên nhiều ví dụ thấy chúng gần như tương đồng nhau nhưng chúng không nằm chung một khái niệm

<br>

<sub>— Hết phần giải thích —</sub>

---

</td>
</tr>
</table>
</details>

#### 3.4.1.biểu diễn làm tròn trên hệ nhị phân

Để hiểu sâu hơn chúng ta cần phải hiểu rõ là `round toward zero` nó tác động lên bit nhị phân như thế nào đã, ở phần chương vừa rồi ta có lập bảng so sánh ở hệ cơ số 10, nhưng bây giờ ta cần phải xem thêm nó tác động tới hệ cơ số 2 như thế nào ở phần tính toán thủ công và minh họa với C. Bây giờ **ví dụ** chỉ cho phép 4bit fraction để dễ quan sát, kết quả trung gian là `1.101011100...` trong đó nó giữ lại `1.1010` và bit bị cắt là `11100...`

`round toward zero` nó không quan tâm bit bị bỏ là gì, không xét GRS hay đi tính một nữa khoảng cách biểu diễn được (half ULP) như round to nearest tie to even cần, nó chỉ biết `1.1010` là xong, suy ra kết quả :

$$
\large1.101011100\ldots_{2} \xrightarrow{\text{round toward zero}} \boxed{1.1010_{2}}
$$

Kết quả của nó là bit được giữ lại và không ngó gì tới bit bị cắt, tương tự với số âm `-1.101011100...` :

$$
\large-1.101011100\ldots_{2} \xrightarrow{\text{round toward zero}} \boxed{-1.1010_{2}}
$$

biểu diễn bit ở chế độ làm tròn này đơn giản chỉ có thế

<details>
	<summary><b>[Chi tiết]</b> minh họa với C</summary>

<table>
<tr>
<td>

---

<br>

```c
#include <stdio.h>
#include <fenv.h>

#pragma STDC FENV_ACCESS ON

int main(void){
	if (fesetround(FE_TOWARDZERO) != 0){
		printf("changed mode failed\n");
		return -1;
	} //chuyển đỏi sang round toward zero

	{
	volatile double a = 1.0;
    volatile double b = 10.0;
	double x = a / b;

    printf("%.20f\n", x);
	}

	volatile double a = 2.2;
	volatile double b = 3.4;
	double x = a * b;

	printf("%.20f\n", x);

	return 0;
}
```

> gcc -o round_toward_zero round_toward_zero.c -lm

<p align="center">
	<image alt="alt text" src="image/image23.png" width="680"/>
</p>

ta thấy `0.09999999999999999167` và `7.47999999999999953814`, đây chính là kết quả được làm tròn bởi `round toward zero`.

<details>
	<summary><b>[Câu hỏi]</b> Liệu sau khi chuyển chế độ sang round toward zero, thì FPU có thực hiện round to nearest tie to even khi gán số thực vào biến không?</summary>

<table>
<tr>
<td>

---

<br>

có thể có hoặc không, tùy thời điểm phép làm tròn diễn ra. Trường hợp đầu tiên là hằng số dấu phẩy động trong mã nguồn **ví dụ** `double a = 0.1;` số `0.1` trong mã nguồn không thể biểu diễn chính xác theo IEEE, vì nó là số vô hạn (có thể biểu diễn số này vô hạn tuần hoàn nhưng độ rộng fraction là hữu hạn).

Để biểu diễn chính xác thì phải cần biết nó có phải số hữu hạn hay vô hạn. Về cơ bản thì nếu việc gán vào cho biến kiểu số thực là số vô hạn thì nó vẫn rounding theo round to nearest tie to even như thường, vì nó xảy ra trước rồi và nó đã hardcode trong file nhị phân (file thực thi sau khi biên dịch) rồi

Còn về trường hợp các phép tính sau này về số thực đó thì đúng, nó dùng `round toward zero` như đã được thiết lập vì đây là lúc FPU sử dụng các lệnh tính toán số thực và kết quả của các lệnh này mới chịu ảnh hưởng bởi rounding mode hiện tại. Nêu thiết lập chế độ làm tròn nào thì kết quả sẽ tuân theo chế độ đó 

Còn về trường hợp dùng định dạng chuỗi chuyển sang số thực nghĩa là từ `"2.2"` thành `2.2` lúc này các thư viện C sẽ chuyển thành số thực, và việc chuyển đổi này có thể chịu ảnh hưởng của rounding mode, tùy cách hiện thực của libc và chuẩn mà thư viện tuân theo.

**Tóm lại là vậy:** khi gán số thực vào valriable, số thực đã được compiler mã hóa sẵn trong quá trình biên dịch rồi. Và các phép toán như `a * b` thì lúc này mới tuân theo rounding mode hiện tại (rounding mode mà đã được thiết lập trong mã)

**Lưu ý:** `fesetround()` chỉ ảnh hưởng đến các phép toán dấu phẩy động được FPU thực hiện trong lúc chương trình chạy (runtime). Các hằng số dấu phẩy động như `2.2`, `3.14` hay `0.1` thường đã được compiler chuyển sang định dạng IEEE 754 trong quá trình biên dịch, nên không chịu ảnh hưởng của `fesetround()` được gọi sau đó.

<br>

<sub>— Hết phần giải thích —</sub>

---

</td>
</tr>
</table>
</details>

Để biết được là `0.09999999999999999167` và `7.47999999999999953814` có phải là kết quả của `round toward zero` hay không thì trước hết phải biết các số thực được gán vào biến trong mã nguồn thuộc số thực vô hạn tuần hoàn hay hữu hạn. Bây giờ để có số liệu thì chúng ta lấy hai cái này đi encode sang nhị phân trước, encode giúp xác định chuỗi bit trước khi lưu vào IEEE 754, từ đó biết liệu giá trị toán học có biểu diễn hữu hạn hay vô hạn trong hệ nhị phân và hiểu vì sao FPU phải thực hiện làm tròn , với `0.09999999999999999167` ta có :

biết sign và phần nguyên có bit là `0` vậy nên ta chỉ cần nhân đôi thôi 

| phần số thực | nhân 2 | dư | giá trị bit |
|:-----:|:--------:|:----:|:-------------:|
| 0.09..167 | 0.2 | 0.2 | 0 |
| 0.2 | 0.4 | 0.4 | 0 |
| 0.4 | 0.8 | 0.8 | 0 |
| 0.8 | 1.6 | 0.6 | 1 |
| 0.6 | 1.2 | 0.2 | 1 |

ta có : `0.0001100011...000110 (4 phần kia bị cắt nên chỉ có bit 0)` và phần bị cắt là `0011` ta chuẩn hóa số thực này suy ra ta có `1.100011...000110` :

$$\Large
0.0001100011...000110_{2} \xrightarrow{\text{di chuyển dấu chấm sang phải 4 lần}} 1.100011...000110_{2}
$$

suy ra `actual exponent = -4` tính trường exponent là `exponent field = -4 + 1023 = 1019` và ta có $$\large1019_{10} = 01111111011_{2}$$ ráp lại ta có $$\large\boxed{001111111011100011...000110_{2}}$$ vậy ta thấy quá trình chuyển sang nhị phân xuất hiện chuỗi tuần hoàn `000110011...`, điều đó chứng tỏ giá trị toán học `0.09999999999999999167` không thể biểu diễn chính xác bằng khai triển nhị phân vô hạn. Khi encode sang IEEE 754, FPU sẽ cắt chuỗi này theo giới hạn 52 bit fraction (double) rồi làm tròn theo chế độ làm tròn hiện hành để tạo ra một mẫu bit hữu hạn.

Còn giá trị `7.47999999999999953814`, đầu tiên ta có `sign = 0` và $$\large7_{10} = 111_{2}$$ và tính fraction :

| phần số thực | nhân 2 | dư | giá trị bit |
|:-----:|:--------:|:----:|:-------------:|
| 0.4799..953814 | 0.96 | 0.96 | 0 |
| 0.96 | 1.92 | 0.92 | 1 |
| 0.92 | 1.84 | 0.84 | 1 |
| 0.84 | 1.68 | 0.68 | 1 |
| 0.68 | 1.36 | 0.36 | 1 |
| 0.36 | 0.72 | 0.72 | 0 |
| 0.72 | 1.44 | 0.44 | 1 |
| 0.44 | 0.88 | 0.88 | 0 |
| 0.88 | 1.76 | 0.76 | 0 |
| 0.76 | 1.52 | 0.52 | 1 |
| 0.52 | 1.04 | 0.04 | 1 |
| 0.04 | 0.08 | 0.08 | 0 |
| 0.08 | 0.16 | 0.16 | 0 |
| 0.16 | 0.32 | 0.32 | 0 |
| 0.32 | 0.64 | 0.64 | 0 |
| 0.64 | 1.28 | 0.28 | 1 |
| 0.28 | 0.56 | 0.56 | 0 |
| 0.56 | 1.12 | 0.12 | 1 |
| 0.12 | 0.24 | 0.24 | 0 |
| 0.24 | 0.48 | 0.48 | 0 |
| 0.48 | 0.96 | 0.96 | 0 |
| 0.96 | 1.92 | 0.92 | 1 |

ta có : `fraction = 0.111101001100001010001..010011 (11 bit bị cắt)` ta chuẩn hóa số thực thành `1.11101001100001010001..010011`:

$$\Large
0.111101001100001010001..010011_{2} \xrightarrow{\text{di chuyển dấu chấm sang phải 1 lần}} 1.11101001100001010001..010011_{2}
$$

suy ra `actual exponent = -1` ta tính `exponent field = -1 + 1023 = 1022` ta đổi $$\large1022_{10} = 01111111110_{2}$$ ta ráp lại thành $$\large\boxed{01101111111110111101001100001010001..010011_{2}}$$ ta thấy khi tính toán thì đoạn nhị phân này biểu diễn số thực vô hạn và có phần bị cắt là `00001010001`

**Vậy suy ra:** khai triển nhị phân của hai giá trị toán học `0.09999999999999999167` và `7.47999999999999953814` đều là chuỗi vô hạn tuần hoàn, nên không thể lưu chính xác trong định dạng IEEE 754 double. Trong quá trình biên dịch, compiler sẽ chuyển các hằng số dấu phẩy động này sang mẫu bit IEEE 754 gần nhất (thông thường theo quy tắc `round to nearest, ties to even`) rồi ghi trực tiếp mẫu bit đó vào file thực thi. Vì vậy, khi chương trình chạy, việc gán các hằng số này vào biến không chịu ảnh hưởng của `fesetround()`. Chỉ các phép toán dấu phẩy động được thực hiện trong runtime mới sử dụng rounding mode hiện hành.

Bây giờ theo tính toán để đoán ra dấu hiệu rõ của `round toward zero`, ta thấy các giá trị toán học khi thực hiện phép tính nó bị giảm đi một số rất nhỏ so với chuẩn toán học ban đầu. Ừm, nó không giống như rounding theo kiểu `round to nearest, tie to even` mà tăng lên hay giữ nguyên thay vào đó ở trường hợp này nó lại giảm xuống một chút cực kỳ nhỏ

suy ra chế độ làm tròn `round toward zero` khả năng cao đã hoạt động. Ta có thể dùng casio để biết rằng $$\large\frac{1.0}{10.0} = 0.1_{10}$$ , nếu là `round to nearest, tie to even` nó được giữ nguyên với giá trị `7.47999999999999953814` và `0.09999999999999999167` do `Guardbit = 0` nhưng ở đây nó lại giảm xuống suy ra có dấu hiệu chỉ giữ bit và bỏ luôn bit bị cắt đúng như lý thuyết vừa rồi. Nếu giữ nguyên thì vẫn là giá trị cao hơn so với giá trị này hay làm tròn 

nhưng về kỹ thuật chúng ta không thể kết luận chính xác tuyệt đối được vì `round to nearest, tie to even` không chỉ là tăng lên hay giữ nguyên, nó có thể tăng, giảm, giữ nguyên cả ba trường hợp tùy thuộc vào GRS có trong bit. Nhưng chắc chắn hai bit này nếu là `round to nearest, tie to even` thì sẽ giữ nguyên vì cả hai có guard bit là 0

**Nếu round to nearest mà nó nhỏ hơn half ULP thì nó giữ nguyên vậy chả khác gì hệ thống đã lấy bit bị cắt bỏ rồi và nó có hành vi giống round toward zero là lấy phần bit theo độ rộng fraction à?**

Trong trường hợp phần bị cắt nhỏ hơn ví dụ 0.5 ULP thì kết quả của `Round to Nearest, Ties to Even` và `Round Toward Zero` hoàn toàn có thể giống hệt nhau. Nhưng không đồng nghĩa hai thuật toán của chung tương đồng nhau, điều này khá hiếm có thể xảy ra ta có bảng so sánh :

| discarded part | Round-to-nearest      | Toward zero |
| :--------------: | :---------------------: | :-----------: |
| <0.5 ULP       | giữ nguyên            | giữ nguyên  |
| =0.5 ULP       | even                  | giữ nguyên  |
| >0.5 ULP       | tăng/giảm tới nearest | giữ nguyên  |

và thấy nếu cùng nhỏ hơn half ULP thì cả hai có kết quả y như nhau

<br>

<sub>— Hết phần giải thích —</sub>

---

</td>
</tr>
</table>
</details>

### 3.5.Round toward positive infinity (+∞)

hay còn gọi là roundUp hoặc round toward $$\large+\infty$$, là một trong 5 rounding mode (rounding-direction attributes) của IEEE754. Quy tắc của chế độ làm tròn này là chọn giá trị floating-point biểu diễn được nhỏ nhất nhưng vẫn lớn hơn hoặc bằng giá trị chính xác cần làm tròn. Nói đơn giản là nó làm tròn về $$\large+\infty$$.

**Ví dụ** với số dương giả sử precision chỉ cho phép $$\large1.001_{2}$$ nhưng giá trị thực là $$\large1.001101_{2}$$ ta có $$\large1.001_{2} < 1.001101_{2} < 1.010_{2}$$ vậy nên nó sẽ làm tròn thành $$\large\boxed{1.010_{2}}$$ vì round toward $$\large+\infty$$ phải chọn số lớn hơn hoặc bằng giá trị ban đầu tức là số dương bị làm tròn lên.

Nhưng với số âm điều này rất dễ bị nhầm trong quy tắc làm tròn này, **cho ví dụ** $$\large-1.001_{2}$$ và giá trị chính xác nằm giữa $$\large-1.001_{2}$$ và $$\large-1.010_{2}$$ và trên trục số :

```
-1.010        exact        -1.001
   |------------|-------------|
            -> +∞
```

Round toward $$\large+\infty$$ phải chọn giá trị lớn hơn, tức nằm về phía bên phải $$\large\boxed{-1.001_{2}}$$. Nó không phải là làm cho trị tuyệt đối lớn hơn. Ta có bảng so sánh và phép so sánh trực quan như : 

| Giá trị chính xác | Round toward +∞ |
| :----------------: | :--------------: |
|       $$\large1.001101_{2}$$ |        $$\large1.010_{2}$$ |
|      $$\large-1.001101_{2}$$ |       $$\large-1.001_{2}$$ |

**vì:** $$\large−1.001_{2} > −1.001101_{2} > −1.010_{2}$$ . Nên round toward $$\large+\infty$$ luôn chọn upper bound.

**Nếu số đã biểu diễn chính xác được:** ko có bit nào cần thay đổi ví dụ như $$\large1.010_{2}$$ thì vẫn là chính nó ,vì đã nằm đúng trên một giá trị floating-point có thể biểu diễn nên $$\large\boxed{1.010_{2}\rightarrow1.010_{2}}$$

<details>
	<summary><b>[Câu hỏi]</b> giá trị mà format floating-point hiện tại có thể lưu được là sao?</summary>

<table>
<tr>
<td>

---

Với một format cụ thể, máy tính chỉ có thể lưu một tập hữu hạn các giá trị. Những giá trị nằm trong tập đó gọi là các giá trị biểu diễn được (representable values). **Ví dụ** cho một đoạn nhị phân biểu diễn số thực như sau $$\large1.1001001_{2}$$ tuy nhiên CPU chỉ muốn lấy 3 bit fraction nên bit $$\large1001_{2}$$ phía sau bị cắt, trở thành một phần cho việc phục vụ rounding (GRS)

và ta có 3bit fraction sau khi cắt sau $$\large1.100_{2}$$ vậy gía trị mà format floating-point hiện tại có thể lưu được ở 3bit fraction này là :

```
1.101
1.110
1.111
```

3 giá trị trên chính là các giá trị representable của format này trong khoảng đó. Nhưng nếu :

```
1.0001
1.0011
1.0101
1.0111
```

không nằm trong tập đó, vì format chỉ có 3 bit sau dấu chấm. Ví dụ `1.101` -> representable, còn `1.0001` -> ko representable trong format 3bit này

**Tại sao với ví dụ này, cũng tương tự như máy tính chúng ko lưu được số bit vượt ngưỡng format độ rộng fraction hiện tại?**

ko phải nó ko biết số `1.0001` hay các số nhị phân khác. Mà là format của nó có độ rộng hữu hạng, và độ rộng fraction đó ko đủ để mã hóa số nhị phân đó. Với ví dụ trên format của chúng ta có quy định là $$\large1.xxx_{2}$$ chỉ có 3 vị trí :

```
1	.	x	x	x
		|	|	|_____ (bit1)
		|	|_________ (bit2)
		|_____________ (bit3)

        <-------->
		(tổng cộng 3 bit)
```

và trong khi số `1.0001` cần độ rộng fraction 4 bit, vì thế `1.0101` không phải là một giá trị mà format này có thể biểu diễn chính xác.

<sub>--Đã hết phần giải thích--</sub>

---

</td>
</tr>
</table>
</details>

> [!IMPORTANT]
> Điều kiện để round toward $$\large+\infty$$ :
> 
> $$\Large R_{+\infty}(x) = \begin{cases}
> x, & x \text{  representable}\\
> \text{gía trị representable nhỏ nhất} \ge x, & x \text{  ko representable}
> \end{cases}$$
>
> Nghĩa là x thuộc representable, là giá trị nằm trong khoảng miền mà format floating-point hiện tại có thể lưu được thì sẽ ko được làm tròn (rounding) thay vào đó chúng sẽ giữ nguyên. Còn nếu x ko thuộc representable thì mới xảy ra rounding, với chế độ này nó sẽ làm tròn về số gần nhất với dương vô cực ($$\large+\infty$$)

Cho trường hợp representable. Giả sử format có 3bit fraction $$\large x = 1.010_{2}$$ và chuỗi nhị phân $$\large1.010_{2}$$ là một giá trị thuộc miền mà format floating-point hiện tại có thể lưu được (representable) nên $$\large\boxed{R_{+\infty}(1.010_{2}) = 1.010_{2}}$$ nó vẫn giữ nguyên ko có rounding thực sự xảy ra

Trường hợp ko representable. cho $$\large x = 1.0101_{2}$$ nhưng với giả sử trên, format chỉ giữ được độ rộng fraction là 3bit thôi nên $$\large1.010 < 1.0101 < 1.011$$ , round toward $$\large+\infty$$ chọn giá trị phía $$\large+\infty$$ nên $$\large\boxed{R_{+\infty}(1.0101_{2}) = 1.011_{2}}$$

Cho thêm trường hợp đối với số âm, với $$\large(−1.011) < (−1.0101) < (−1.010)$$ thì Round toward $$\large+\infty$$ vẫn đi sang phải trên trục số vì nó chọn số gần với dương vô cực nhất, nên $$\large\boxed{R_{+\infty}(-1.0101_{2}) = -1.010_{2}}$$

**Mấu chốt ở đây là :** chế độ round toward $$\large+\infty$$ hướng về trên trục số, ko phải tăng bit hay tăng trị tuyệt đối

nhìn theo lower và upper Giả sử giá trị chính xác $$\large x$$ nằm giữa hai số floating-point liên tiếp $$\large L < x < U$$ thì round toward $$\large+\infty\rightarrow U$$ và $$\large-\infty\rightarrow L$$, còn nếu `x = L` hoặc `x = U` thì giữ nguyên (ko rounding). Vì vậy ta có :

$$\Large
RN_{+\infty}(x) = min\\{f \in F | f \ge x \\}
$$

Trong đó $$\large F$$ là tập các giá trị floating-point có thể biểu diễn. Biểu thức này có nghĩa là `trong tất cả các giá trị floating-point có thể biểu diễn mà lớn hơn hoặc bằng x, chọn giá trị nhỏ nhất.`

<details>
	<summary><b>[Chi tiết]</b> minh họa với C</summary>

<table>
<tr>
<td>

---

```c
#include <stdio.h>
#include <fenv.h>

#pragma STDC FENV_ACCESS ON

int main(void){
	if (fesetround(FE_UPWARD) != 0){
		printf("changed mode failed\n");
		return -1;
	} //chuyển đỏi sang round toward positive infinity

    volatile float a = 1.0f;
    volatile float b = 0x1.000002p-24f;

    float result = a + b;

	printf("%.23f\n", a);
	printf("%.23f\n", b);

    printf("%.23f\n", result);

	return 0;
}
```

> gcc -o round_toward_positive_infinity round_toward_positive_infinity.c -lm

<p align="center">
	<image alt="alt text" src="image/image24.png" width="980"/>
</p>

Ta có chuỗi số `1.00000011920928955079` ta thấy rõ ràng nó đã được làm tròn nhưng vẫn có sự can thiệp của `tie to even` trước khi tới `caculating`, ở phần transmit số thực hữu hạn `1.0f` vào biến a rồi và `0x1.000002p-24f` vào biến b. Ta vẫn chưa biết là sẽ xảy ra rounding hay chưa, nên việc ta cần làm đầu tiên là phân tích và xem gía trị cả hai chuỗi xem nó biễu diễn hữu hạn hay vô hạn bây giờ ta biết `1.0f` là hữu hạn tiếp theo là tính toán giá trị chuỗi số `0x1.000002p-24f`

> giải thích chuỗi số 0x1.000002p-24f

<details>
	<summary><b>[Câu hỏi]</b> chuỗi số 0x1.000002p-24f là gì?</summary>

---

chuỗi `0x1.000002p-24f` là một chuỗi số kết hợp với nhiều tiền tố, đây được gọi là `hexadecimal floating-point literal` của `C/C++`, không phải một chuỗi số thập phân bình thường. Bây giờ ta thử tách nó ra:

```
0x1.000002 p -24 f
│     │    │  │  |__ suffix f -> kiểu float
│     │    │  |_____ exponent = -24
│     │    |________ ký hiệu phân cách binary exponent trong hexadecimal floating-point literal.
│     |_____________ phần significand ở hệ 16
|___________________ tiền tố 0x -> hexadecimal (hệ thập lục phân)
```

Ý nghĩa chi tiết của từng yếu tố như sau :

với `suffix f (hậu tố f)` cho biết đây là kiểu số thực thuộc float, trong implementation đang xét, float là IEEE 754 binary32 nên có độ rộng 32 bit. Tiếp theo là `p-24`, cái này là binary exponent trong cú pháp hexadecimal floating-point literal của C, ký hiệu `p` chính là ký hiệu phân cách `binary exponent trong hexadecimal floating-point literal` và chúng đi chung cùng nhau, với `p-24` thì sẽ là $$\large\times2^{-24}$$. Công thức tổng quát của ký hiệu `p` là :

<div align="center">

$$\Large
0xH.HHHpE = H.HHH_{16}\times2^{E}
$$

</div>

**Ví dụ** cho `0x1.8p+1`, nghĩa là $$\large1.8_{16}\times2^{1}$$, số thực có hệ cơ số 2 do `0x` và số mũ là 1 do `p+1`. Hexadecimal chỉ dùng cho significand; exponent sau p vẫn là số mũ của cơ số 2.

Còn phần `...000002` là phần significand ở hệ 16, tại sao lại là hệ 16 thì phần `0x...` vốn dĩ đã là tiền tố của hexdecimal (hệ thập lục phân) rồi, theo hệ cơ số của hexa luôn là 16 nên đây là chuỗi số `hexadecimal float (số thực float theo hệ thập lục phân)` và các `actual exponent = -24`

Bây giờ ta khai triển biểu thức toán để tính toán giá trị của chuỗi `0x1.000002p-24f`, dựa vào chuỗi này với toán lớp 6 ($$\large abc = 123_{10} = 3\times1 + 2\times10 + 1\times100$$ vì `3` là hàng đơn vị nên nhân `1`, `2` là hàng chục nên nhân `10`, `1` là hàng trăm nên nhân `100`) nhưng bây giờ đơn giản và giúp cho trình bày dễ nhìn hơn ta dùng phép lũy thừa ta có $$\large123_{10} = 1\times10^{2} + 2\times10^{1} + 3\times10^{0}$$, và dùng phép lũy thừa khá giống với việc ta tính nhị phân decode (tính phần fraction ở chương decode) nó giống như tuân theo đoạn thẳng của số nguyên theo hướng ngược lại vậy.

> rõ hơn về toán học trên tại đây

<details>
	<summary><b>[Chi tiết]</b> rõ hơn</summary>

---

Với gía trị như `123` thì chúng ta có hai cách để tính ra giá trị này, cách 1 là dùng các số thủ công như $$\large abc = 123_{10} = 3\times1 + 2\times10 + 1\times100$$, theo toán lớp 6 thì cái này được nêu rõ như sau, ta tiến hành đọc số 3 trước (đọc từ phải qua trái), số 3 thuộc hàng đơn vị, ta đem nhân với 1 thì vẫn nguyên số 3, đọc tiếp số 2 thuộc hàng chục ta đi nhân với 10 thì là 20 mà `20 + 3 = 23`, tiếp tục ta đọc số 1 là hàng trăm vậy đi nhân 100 ta có 100 vậy `100 + 20 + 3 = 123` giá trị này đúng với giá trị ban đầu. Ta thấy hàng đơn vị, chục, trăm ... luôn luôn là `1,10,100...`

cách 2 là dùng số mũ $$\large123_{10} = 1\times10^{2} + 2\times10^{1} + 3\times10^{0}$$ cách này thường dùng ở việc tính nhị phân nhiều hơn vì nó đơn giản và dễ trình bày cũng dễ nhìn. Với cách này ta lấy số đem đi nhân với hệ cơ số của chính số đó và số mũ được xem là thứ quyết định hàng `đơn vị, chục, trăm v.v..` Số mũ càng lớn thì hàng đó sẽ thường nhiều hơn, với `123`, ta tiến hành tính:

Đầu tiên với số 3 nó thuộc hàng đơn vị vậy ta có $$\large10^{0}$$ số 10 là hệ cơ số, vì đây là số nguyên và nó luôn có hệ cơ số là 10. Bây giờ ta biết được mốc rồi ta chỉ cần đếm lần lượt thôi, ở đây đơn vị là mũ 0 vậy chục là mũ 1 và trăm là mũ 2 vậy ta xét:

<div align="center">

$$\Large
3_{10} = 10^{0} \text{ và } 2_{10} = 10^{1} \text{ và } 1_{10} = 10^{2}
$$

</div>

từ đó suy ra $$\large123_{10} = 1\times10^{2} + 2\times10^{1} + 3\times10^{0}$$ là đúng. Thêm một chi tiết nữa, bên trên ta có đề cập tới đoạn thẳng của số nguyên theo hướng ngược lại vậy bây giờ ta trình bày nó, gỉa sử ta có đoạn thẳng gồm số nguyên dương và số nguyên âm:

```
---|--|--|--|--|--|--|--|--|--|--|--|-->
  -4 -3 -2 -1  0  1  2  3  4  5  6  7
```

ta thấy đó gọi là đoạn thẳng số nguyên truyền thống, đoạn thẳng của số nguyên theo hướng ngược lại thì sẽ thế này:

```
<---|--|--|--|--|--|--|--|--|--|--|--|--
   4  3  2  1  0  -1 -2 -3 -4 -5 -6 -7
```

và số mũ với hệ cơ số 10 đều dựa vào đoạn thẳng của số nguyên theo hướng ngược lại thế này. Ví dụ với $$\large912.219_{10} = 9\times10^{2} + 1\times10^{1} + 2\times10^{0} + 2\times10^{-1} + 1\times10^{-2} + 9\times10^{-3}$$ ta thấy chúng dựa theo đoạn thẳng của số nguyên theo hướng ngược lại

<sub>--đã hết phần giải thích--</sub>

---

</details>

Nên bây giờ ta tiến hành khai triển $$\large0x1.000002_{16}$$ thành $$\large0x1.000002_{16} = 1 + 2 \times 16^{-6} = 1 + \frac{2}{16^{6}}$$ (vì 2 là một chữ số hexadecimal có giá trị 2, 1 là phần nguyên và $$\large16^{6}$$ là hệ cơ số thập lục phân và giá trị `2` nằm ở vị trí `-6`), lý do nó thành $$\large\frac{2}{16^{6}}$$ trong khi thực chất vị trí nó nằm ở `-6` , chính là trong toán học có 1 quy tắc là 

<div align="center">

$$\Large
a^{-m} = \frac{1}{a^{m}}
$$

</div>

Ta thấy theo quy tắc, ta có $$\large1 + 16^{-6} = 1 + \frac{1}{16^{6}}$$ từ đó ta áp dụng nhân chia trước, cộng trừ sau với phép này. Ta lấy giá trị `2` đi nhân với tử của $$\large\frac{1}{16^{6}}$$ ta có $$\large\frac{2}{16^{6}}$$, suy ra kết quả đúng là $$\large\boxed{1 + \frac{2}{16^{6}}}$$.

<details>
	<summary><b>[Câu hỏi]</b> Vậy số 2 từ đâu mà ra vì sao lại nhân cho hệ cơ số của lục phân? Tại sao ngay từ đầu lại có giá trị 2 nhưng sau này lại bỏ?</summary>

---

**Câu hỏi 1:** số 2 từ đâu mà ra vì sao lại nhân cho hệ cơ số của lục phân?

Trong $$\large0x1.000002_{16}$$, số `2` chính là chữ số `2` đang nằm ở vị trí thứ 6 sau dấu chấm.

```
1  .  0  0  0  0  0  2
      |  |  |  |  |  |
     -1 -2 -3 -4 -5 -6
```

vì giá trị `2` nằm ở vị trí `-6` và đây là hệ thập lục phân có hệ cơ số 16, để tính trọng số thì dùng `hệ cơ số` lũy thừa với `vị trí số` nên ta có $$\large2\times16^{-6}$$

Ví dụ khác, cho số $$\large123.004_{10}$$ ta khai triển như sau $$\large123.004_{10} = 1\times10^{2} + 2\times10^{1} + 3\times10^{0} + 4\times10^{-3}$$ vậy tại sao có $$\large4\times10^{-3}$$, ko phải là 10 tự sinh ra nó mà là do số 4 nằm ở vị trí `-3`:

```
1  2  3  .  0  0  4
|  |  |  |  |  |  |
2  1  0    -1 -2 -3 (4 nằm tại -3)
```

và số nguyên này có hệ cơ số `10` nên ta có $$\large4\times10^{-3}$$ và tương tự với hệ thập lục phân hay hệ nhị phân thôi

**Câu hỏi 2:** Tại sao ngay từ đầu lại có giá trị 2 nhưng sau này lại bỏ?

Thực chất nó không hề bỏ số 2. Nó chỉ được biến đổi từ chữ số thành hệ số của trọng số vị trí, rồi sau đó khi đổi sang dạng $$\large2^{−23}$$, nó được hấp thụ vào số mũ. Cụ thể, ta có $$\large0x1.000002_{16}$$ chữ số `2` ở vị trí `-6` nên $$\large1+2\times16^{-6}$$ dùng $$16^{-6} = \frac{1}{16^{6}}$$ vì quy tắc $$\large a^{-m} = \frac{1}{a^{m}}$$ ta được $$1 + 2 \times \frac{1}{16^{6}} = 1 + \frac{2}{16^{6}}$$ (lấy `2` nhân cho tử của phân số) và ta thấy số 2 vẫn còn nguyên

Sau đó mới đổi $$\large16 = 2^{4}$$ và $$\large16^{6} = (2^{4})^{6} = 2^{24}$$ suy ra ta có $$\large\frac{2}{16^{6}} = \frac{2}{2^{24}}$$, ta viết từ số 2 thành $$\large2^{1}$$ nên $$\large\frac{2^{1}}{2{24}} = 2^{1 - 24} = 2^{-23}$$

Vậy ta có $$\large1 + 2^{-23}$$. Cho nên số 2 đã đi đâu, nó ko biến mất mà nó đi từ 2 thành $$\large2^{1}$$ rồi gộp vào phép trừ số mũ $$\large\frac{2^{1}}{2^{24}} = 2^{1 - 24} = 2^{-23}$$. Đây chính là câu trả lời cho câu hỏi 2.

<sub>--đã hết phần giải thích--</sub>

---

</details>

tiếp theo ta bắt đầu tính rút gọn đi ở $$\large16^{6}$$, với giá trị `16` thì $$\large16 = 2^{4}$$

vậy ta có $$\large16^{6}$$ mà $$\large16 = 2^{4}$$ nên ta có $$\large16^{6} = (2^{4})^{6}$$ nghĩa là `6` giá trị `16` nhân lại với nhau mà `16` lại tương đương 2 mũ 4 sau khi rút gọn, vậy ta có 6 phép 2 mũ 4 nhân lại với nhau. Bây giờ có quy tắc toán là 

<div align="center">

$$\Large
(a^{m})^{n} = a^{m \times n}
$$

</div>

nên ta có $$\large(2^{4})^{6} = 2^{4 \times 6} = 2^{24}$$ vậy ta có $$\large16^{6} = 2^{24}$$ . Đây chỉ là đổi cách viết cùng một con số.

Bây giờ ta thế vào phép chia (phân số) ta có $$\large16^{6} = 2^{24}$$ vậy suy ra $$\large0x1.000002_{16} = 1 + \frac{2}{2^{24}}$$ (thay số 16 mũ -6 thành 2 mũ 24) và ta tính cái này ra $$\large\frac{2}{2^{24}} = 2^{-23}$$ lý do nó ra kết quả $$\large2^{-23}$$ là trong toán học có quy tắc :

<div align="center">

$$\Large
\frac{a^{m}}{a^{n}} = a^{m - n}
$$

</div>

nên $$\large\frac{2^{1}}{2^{24}} = 2^{1 - 24} = 2^{-23}$$. Rồi bây giờ ta biết chuỗi `0x1.000002` có `p -24` nghĩa là số mũ là `-24` vậy ta có : 

<div align="center">

$$\Large
0x1.000002_{16} = 1 + \frac{2}{16^{-6}} = (1 + 2^{-23})2^{-24} = \boxed{2^{-24} + 2^{-47}}
$$

</div>


tính biểu thức $$\large(1 + 2^{-23})2^{-24}$$ bằng đơn nhân đa, và áp dụng quy tăc 

<div align="center">

$$\Large
a^{m} \times a^{n} = a^{m + n}
$$

</div>

Từ đó suy ra kết quả của gía trị `0x1.000002p-24f` là $$\large\boxed{2^{-24} + 2^{-47}}$$ và số này thực ra được biểu diễn chính xác bằng binary32 cũng là phần liên quan trực tiếp tới chương rounding. Ta có, $$\large(1 + 2^{-23})2^{-24}$$ (biểu thức trước khi tính đơn nhân đa), ta viết thành $$\large1.00000000000000000000001_{2} \times 2^{-24}$$. Ở đây, $$\large1+2^{-23}$$ có đúng 23 bit fraction sau hidden bit 1. Binary32 có:

```
sign       = 1 bit
exponent   = 8 bits
fraction   = 23 bits
```

Nên giá trị này nằm đúng trên một giá trị binary32 representable.

<details>
	<summary><b>[Chi tiết]</b> Rõ hơn về phần 32bit này</summary>

---

Ta xét $$\large1+2^{-23}$$ và ta đã biết $$\large2^{-1} = \frac{1}{2^{1}} = \frac{1}{2}$$, $$\large2^{-2} = \frac{1}{2^{2}} = \frac{1}{4}$$... Vậy $$\large2^{-23}$$ chính là một bit `1` nằm ở vị trí thứ 23 sau dấu chấm nhị phân. **Ví dụ** $$\large1+2^{-1}=1.1_{2}$$, $$\large1+2^{-2}=1.01_{2}$$, $$\large1+2^{-3}=1.001_{2}$$... (giá trị `1` đằng trước là phần nguyên) vậy tương tự với $$\large1+2^{-23}=\boxed{1.00000000000000000000001_{2}}$$

**Vì sao nó lại liên quan tới 32bit?:** với 32bit (Float) biểu diễn cấu trúc nhị phân của số thực có dạng:

| sign | exponent | fraction |
|:-----:|:----------:|:----------:|
|  1  |    8     |    23    |

Điều quan trọng là `fraction = 23 bit` , Với một số normalized binary32, significand được hiểu là `1.fraction` nghĩa là theo chuẩn hóa thì `hiddenbit = 1` và có 23bit fraction ví dụ binary32 có `fraction = 00000000000000000000001` thì nó sẽ là $$\large\boxed{\mathrm{1}.00000000000000000000001_{2}}$$ và giá trị này đúng y hệt cái ta đang có ở biểu thức $$\large1+2^{-23}$$


Bây giờ tới phần ghép thêm $$\large2^{-24}$$, như đã nói phần gía trị `-24` đã được cho ở chuỗi `0x1.000002p-24f` (phần `p-24`) trước đó ta ghép lại thành $$\large(1 + 2^{-23})2^{-24}$$ cái này chỉ đơn giản là làm đúng dạng normalized theo như công thức ở chương [1.Tổng quan về IEEE 754](#1tổng-quan-về-ieee-754) là $$\large(-1)^{S}\times1.m\times2^{e - b}$$ với significand = $$\large1.00000000000000000000001_{2}$$ và actual exponent = -24

**điều dễ nhầm là :** `-24` không làm significand dài thêm. Nó chỉ làm là lấy significand này rồi dịch dấu chấm nhị phân 24 vị trí sang trái và phần này vừa khít với 1 hidden bit + 23 fraction bits

<sub>--đã hết phần giải thích--</sub>

---

</details>

Bây giờ ta chuyển chuỗi `0x1.000002p-24f` sang binary, ta vừa chuyển nó thành giá trị ở hệ cơ số 10 bây giờ là hệ cơ số 2. Bây giờ ta biết hiddenbit là 1, fraction là $$\large00000000000000000000001_{2}$$ và số mũ là `-24` ở phần `p-24` kiểu float (32bit). Cách tính chuỗi `0x1.000002p-24f` có ở phần details trên. Bây giờ tính trường số mũ (exponent field) bằng cách lấy `-24` cộng với bias, ta biết `bias = 127` trong hệ 32bits và `-24 + 127 = 103` và chuyển $$\large103_{10} = 01100111_{2}$$ ta có:

| sign | exponent | fraction |
|:-----:|:----------:|:----------:|
|  0  |    01100111     |    00000000000000000000001    |

ghép lại thành $$\large\boxed{00110011100000000000000000000001_{2}}$$. Đây là nhị phân của chuỗi `0x1.000002p-24f`

<sub>--đã hết phần giải thích--</sub>

---

</details>

bây giờ, ta đã biết gía trị số nguyên của chuỗi `0x1.000002p-24f` là $$\large2^{-24} + 2^{-47} = 5.960465188081798e-08_{10} = \boxed{0.00000005960465188081798_{10}}$$ (thêm 8 số 0 bên trái và chuẩn hóa số thực vì `e-08`) rõ hơn với giá trị `e-08` viết tắt là `exponent = -8` nghĩa là nhân hệ cơ số có lũy thừa `-08` nên :

<div align="center">

$$\large
5.960465188081798e-08_{10} = 5.960465188081798\times10^{-8}_{10}
$$

</div>

và giá trị nhị phân là $$\large\boxed{00110011100000000000000000000001_{2}}$$

> **câu hỏi mở rộng :** vì sao app máy tính casio trên điện thoại lại tính được $$\large2^{-24} + 2^{-47} = 0.0000000596_{10}$$ nhưng với máy tính terminal linux bên ngành kiến trúc CPU x86-64 lại ko mà nếu đổi má sang quy tắc toán học như $$\large a^{-m} = \frac{1}{a^{m}}$$ lại luôn ra giá trị `0` mà gõ trực tiếp thì bị lỗi cú pháp với $(())?

<details>
	<summary>Trả lời</summary>

---

Ko phải vì CPU ko biết tính được biểu thức trên, hiện tượng như :

<p align="center">
	<image alt="alt text" src="image/image25.png" width="680"/>
</p>

Đây ko phải là do architecture mà do bash syntax, vì cú pháp `$(())` chủ yếu làm việc với số nguyên **ví dụ** `echo $((1 / 2))` kết quả ra `0` như trên ảnh, ko phải vì $$\large\frac{1}{2} = 0_{10}$$ mà vì bash đang thực hiện integer division, nên $$\large\frac{1}{2} = 0.5_{10}$$ (thấy phần nguyên là `0`) nên bash lấy nó, ko có gì cao siêu

Vậy giải pháp, chúng ta dùng `python3`:

> python3

<p align="center">
	<image alt="alt text" src="image/image26.png" width="680"/>
</p>

và mọi chuyện ổn thỏa

<sub>--đã hết phần giải thích--</sub>

---

</details>

Tiếp đến, ta cần biết cái số mà của chuỗi `0x1.000002p-24f` có phải là số thực vô hạn khi biểu diễn dưới dạng nhị phân hay ko. Ta cần phải tính dựa trên kết quả, ta có $$\large0.00000005960465188081798_{10}$$ với hệ cơ số 10. Bây giờ, ta cần biết là số này là biểu diễn nhị phân vô hạn hay là biểu diễn nhị phân hữu hạn chứ ko phải lấy binary của giá trị trên, đó là mục đích chính và ta nhận thức được điều đó nên ta dùng định lý phân số ở chương [3.1.1.Hai phương pháp xử lý biểu diễn nhị phân hữu hạn và vô hạn](#311hai-phương-pháp-xử-lý-biểu-diễn-nhị-phân-hữu-hạn-và-vô-hạn)

Đầu tiên ta có 23 chữ số sau dấu phẩy nên phần mẫu là `10000000000000000000000`, bây giờ ta dùng ước chung lớn nhất để lấy phần tử ta có `GCD(5960465188081798, 10000000000000000000000) = 2` bây giờ ta lấy kết quả của ước chung lớn nhất chia cho cả hai mẫu và tử, ta có : 

<div align="center">

$$\Large
\boxed{5.960465188081798e-7_{10} = \frac{5960465188081798 \div 2}{10000000000000000000000 \div 2}
 = \frac{2980232594040899}{5e+21}}$$

</div>

giá trị $$\large5e+21$$ là $$\large5 \times 10^{21}$$ nghĩa là thêm 21 số 0 đằng sau ta có $$\large5e+21 = 5000000000000000000000_{10}$$ bây giờ ta tiến hành phân tích nó ra thành $$\large5e+21 \text{ mod } 2 = 0_{10}$$, bây giờ tiến hành chia $$\large5e+21 \div 2 = 2.5e+21_{10}$$ và bây giờ ta tính tiếp $$\large2.5e+21 \text{ mod } 2 = 0_{10}$$ vậy ta thấy cả hai giá trị `2` và `2.5e+21` đều chia hết cho 2, nên ta có :

<div align="center">

$$\Large
\boxed{5e+21 = (2.5e+21) \times 2}
$$

</div>

<details>
	<summary><b>[Chi tiết]</b> Rõ hơn về phép toán nhân tố thừa số</summary>

---

Với cách này khắc phục được vấn đề phân tích cấu trúc đại số cực kỳ lớn. **Ví dụ**, khi ta phân tích cấu trúc mấy đại số nhỏ như `10 = 2 x 5` hay `4 = 2 x 2` nó khá đơn giản. Nhưng với số cực lớn như `9e+52` hay các số cấp trăm tỷ, thì lúc đó ko thể áp dụng phân tích bằng cách đoán mò được. Ta cần phải hiểu và biết cách phân tích cấu trúc có hệ thống và logic hơn nhằm tiết kiệm thời gian và công sức.

Đầu tiên là chia lấy dư (modulo) với phép nhỏ nhất, ta cần phải dùng lần lượt các phép như `2,3,4,5,...,N` để chia lấy dư với giá trị. **Ví dụ** cho số $$\large4000$$ bây giờ ta thấy $$\large4000 \text{ mod } 2 = 0_{10}$$ vậy giá trị $$\large4000$$ chia hết cho 2. Tiếp theo, ta lấy giá trị bị chia chia tiếp cho 2, thành $$\large4000 \div 2 = 2000_{10}$$, và $$\large2000 \text{ mod } 2 = 0_{10}$$ và nó vẫn chia hết cho 2

Tiếp theo, khi đã biết nó chia hết cho 2 với phép chia lấy dư (suy ra thỏa mãn), ta tiến hành lấy giá trị chia và giá trị kết quả của phép $$\large4000 \div 2 = 2000_{10}$$ đem đi nhân lại, suy ra ta có $$\large\boxed{4000 = 2000 \times 2}$$. Nghe qua thì cũng logic, nhưng kết quả này chỉ là phép kiểm chứng rằng phép chia được thực hiện chính xác. Chưa phải bước cần thiết để suy ra chính xác, để nhân tố thừa số, ta cần các bước nữa

<details>
	<summary><b>[Câu hỏi]</b> Tại sao lại phải dùng phép kiểm chứng rằng phép chia được thực hiện chính xác?</summary>

---

Thực tế, phép kiểm chứng này không phải là bước bắt buộc của thuật toán phân tích thừa số hay các phép toán khác. Khi đã kiểm tra $$\large N\bmod p=0$$ thì ta đã biết chắc rằng $p$ là ước của $N$, và phép chia $$\large N\div p=q$$ cho ta một thương nguyên $\large q$. Do đó, ta có thể trực tiếp kết luận $$\large N=q\times p$$. Ví dụ:

<div align="center">

$$\Large40\bmod2=0$$

$$\Large\Rightarrow40\div2=20$$

$$\Large\text{ và: }40=20\times2$$

</div>

Việc nhân ngược như $$\large20\times2=40$$, chỉ nhằm kiểm chứng hoặc minh họa rằng phép chia đã được thực hiện đúng. Trong implementation thực tế, nếu phép chia được thực hiện bằng kiểu dữ liệu và phép toán phù hợp thì không cần thực hiện thêm phép kiểm chứng này sau mỗi lần chia.

<sub>--Đã hết phần giải thích--</sub>

---

</details>

**bước đầu tiên:** là kiểm tra nhanh các factor siêu nhỏ chỉ thử chia cho vài chục số nguyên tố nhỏ nhất `(2, 3, 5, 7, 11…)`. Nếu có thì lấy luôn. Nếu không có thì bỏ qua. Trước khi dùng những thuật toán phức tạp (Pollard's Rho, ECM…), người ta luôn kiểm tra xem số N có chia hết cho các số nguyên tố siêu nhỏ hay không. Các số nguyên tố cực nhỏ thường là `2; 3; 5; 7; 11; 13; 17; 19; 23; 29; 31; 37;...` (thường chỉ cần khoảng 20–50 số đầu tiên là đủ). Cách làm khá đơn giản chỉ cần chia nó với số nguyên tố cực nhỏ như :

```
Nếu N % 2 == 0  ->  2 là factor
Nếu N % 3 == 0  ->  3 là factor
Nếu N % 5 == 0  ->  5 là factor
Nếu N % 7 == 0  ->  7 là factor
...
```

- **Nếu tìm được số nào chia hết :** lấy luôn factor đó, rồi chia N cho nó và tiếp tục với phần còn lại.

- **Nếu không có số nào chia hết :** bỏ qua bước này, chuyển sang bước tiếp theo.

**Tại sao phải làm bước này?:** Vì nó cực kỳ rẻ. Chỉ tốn vài chục phép chia (máy tính làm trong tích tắc). Nhiều số trong thực tế có factor nhỏ (đặc biệt là các số không được tạo cẩn thận). Nếu bỏ qua bước này mà nhảy thẳng sang Pollard's Rho thì vẫn chạy được, nhưng hơi lãng phí thời gian nếu số đó may mắn có factor nhỏ.

**Cho ví dụ:** ta cho số $$\large N = 40$$, xét $$\large40 \bmod 2 = 0$$ ta thấy `2` là factor, vậy ta tiếp tục chia nó $$\large40 \div 2 = 20$$ và tiếp tục chia lấy dư $$\large20 \bmod 2 = 0$$ vậy nên ta có $$\large\boxed{40 = 20 \times 2}$$. Tuy nhiên nó vẫn có thể chia lấy dư tiếp với giá trị `20` vậy nên ta xét $$\large20 \div 2 = 10 \bmod 2 = 0$$ và $$\large10 \div 2 = 5 \bmod 2 = 1 (1 \neq 0)$$.

Từ đây ta đếm có bao nhiêu giá trị chia hết cho 2, `40,20,10` có 3 giá trị vậy ta có $$\large2^{3}$$ còn có một giá trị là `5` ko chia hết cho 2, vậy nên ta lấy gía trị ko chia hết này nhân với $$\large2^{3}$$. Vậy ta có, $$\large\boxed{40 = 2^{3} \times 5}$$ . Nhưng với trường hợp này với ví dụ này là số `40` có thể chia hết cho 2, chỉ khi $$\large N\bmod p \neq 0$$ thì mới chuyển sang factor/prime tiếp theo như `3,5,7,...N`

Logic chuẩn của cách này là :

<div align="center">

$$\Large N \bmod p = 0 \Rightarrow N \leftarrow N/p \Rightarrow \text{ kiểm tra lại } N \bmod p$$

</div>

> Tuy nhiên cách này với số lớn là một bản án cực hình, dưới đây là một ví dụ với số lớn nhưng ta cho nó ko chia hết cho tập hợp 30 số nguyên tố nhỏ nhất

ta cho số `N = 501349247128579388923`, vậy ta có :

<p align="center">
	<image alt="tính số modulo" src="image/image29.png" width="680"/>
</p>

Ta thấy như trong ảnh, khi thực hiện phép tính chia lấy dư nó luôn có dư , vậy 30 số nguyên tố nhỏ nhất ko chia hết cho gía trị `N` ở trên. Ta tiến hành đi sang bước tiếp theo

**Bước 2:** là bước kiểm tra xem $$\large N$$ có phải là số nguyên tố không, trước khi cố gắng phân tích thừa số (factor) của $\large N$, ta phải hỏi một câu rất quan trọng $\large N$ có phải là số nguyên tố không?. Nếu có thì việc phân tích thừa số đã xong luôn $$\large N=N$$ (chỉ có một thừa số là chính nó). Không cần chạy bất kỳ thuật toán factor nào nữa.

Nếu không (tức là $$\large N$$ là hợp số) thì mới tiếp tục sang bước tìm thừa số (Pollard's Rho…). Việc kiểm tra này rất quan trọng, vì nếu lỡ $$\large N$$ là nguyên tố mà ta vẫn cố chạy thuật toán factor thì vừa lãng phí thời gian, vừa không có kết quả và nếu $$\large N$$ là số nguyên tố thì không tồn tại non-trivial factor $$\large1 < d < N$$, do đó không cần chạy thuật toán factorization để tìm thừa số. Với số nhỏ hay đã biết nó là số nguyên tố thì khá đơn giản 

**ví dụ** cho số `11` và số `11` chính là số nguyên tố, vậy nếu biết số nguyên tố đơn giản là lấy chính nó rồi xong. Biết `11` là số nguyên tố, ta nhân tố như sau $$\large11 = 11 \times 1$$, hết vì $$\large N=N$$ nghĩa là nếu $$\large N$$ là số nguyên tố thì nó luôn là chính nó

> Để kiểm tra nhanh bước này, người ta thường dùng thuật toán Miller–Rabin. Một thuật toán kiểm tra nguyên tố kiểu xác suất và chạy rất nhanh, độ tin cậy khá cao

Với trong trường hợp số $$\large N = 501349247128579388923$$, thì đây là hợp số, ko phải là số nguyên tố. Nên ta mới tiếp tục sang bước 3 (dùng Pollard's Rho để tìm thừa số).

**Bước 3:** Tìm thừa số với thuật toán Pollard's Rho là một thuật toán xác suất dùng để tìm một thừa số không tầm thường của một số hợp $$\large N$$. Sau khi tìm được thừa số, ta có thể tiếp tục đệ quy để phân tích hoàn toàn $$\large N$$ thành các thừa số nguyên tố, nổi bật với tốc độ nhanh khi xử lý các số lớn, phù hợp cho trường hợp của chúng ta. Giả sử ,ta có số $$\large N$$ lớn, biết nó không phải nguyên tố, và muốn tìm một số $$\large d$$ sao cho: 

<div align="center">

$$\Large1 < d < N \quad \text{và} \quad d \text{ chia hết } N$$

</div>

cách ngốc là thử chia lần lượt từ 2 trở đi thì quá chậm. Thuật toán Pollard's Rho dẹp chuyện đó sang một bên, nó có dãy

<div align="center">

$$\Large x_{n+1} = (x_{n}^{2} + 1) \bmod N$$

</div>

Bây giờ, **ví dụ với** $$\large N = 15 = 3 \times 5$$, bây giờ giả sử ta ko biết 3 và 5. Ta có dãy như trên vậy nên ta xét $$\large x_{n+1} = x_{n}^{2} + 1 (\bmod 15)$$ ,ta bắt đầu :

<div align="center">

$$\Large x_{0} = 2$$ 

$$\large x_{1} = 2^{2} + 1 = 5$$

$$\large x_{2} = 5^{2} + 1 = 26 \bmod 15 = 11$$

$$\large x_{3} = 11^{2} + 1 = 122 \bmod 15 = 2$$. 

</div>

Từ đây, ta thấy nó lặp lại vô hạn tuần hoàn như sau, nhưng chưa thấy factor nào hết

<div align="center">

$$\Large2\rightarrow5\rightarrow11\rightarrow2\rightarrow5\rightarrow11\rightarrow\ldots$$

</div>

bây giờ, nhìn riêng modulo 3 đây mới là mấu chốt của phần này cũng là dấu hiệu mà thuật toán cần. Ta lấy dãy trên modulo 3, trước tiên ta cần phải tính trước để hiểu vì sao số 3 từ đâu chui qua đây. Bắt đầu khai triển:

<div align="center">

$$\Large N = 15, \quad f(x)=x^{2} + 1 \bmod 15$$

$$\Large\text{Khởi tạo: } x = y = 2$$

$$\Large\text{Vòng đầu: } x = f(2) = 5 ,\quad y = f(f(2)) = f(5) = 11$$

$$\Large\text{Tính: } d = gcd(|5-11|,15) = gcd(6,15) = 3 \Rightarrow \boxed{d = 3}$$

</div>

Từ phép tính trên, ta biết được số 3 từ kết quả của ước chung lớn nhất của hai con trỏ $$\large x, y$$ với $$\large N$$ là 15 từ vòng đầu tiên. Bây giờ biết được sự xuất hiện của số 3 ta tiến hành khai triển biểu thức modulo 3:

<div align="center">

$$\Large2 \bmod 3 = 2$$

$$\Large5 \bmod 3 = 2$$

$$\Large11 \bmod 3 = 2$$

$$\Large\Rightarrow\text{ Đều ra kết quả } : 2 \rightarrow 2 \rightarrow 2 \rightarrow\ldots$$

</div>

Có nghĩa là các giá trị khác nhau khi nhìn modulo 15 lại trùng nhau modulo 3 (dãy số đứng yên khi nhìn theo modulo 3). Điều này có ý nghĩa quan trọng là khi nhìn theo modulo 15 (toàn bộ $\large N$), các số 2, 5, 11 khác nhau. Nhưng khi nhìn theo modulo 3 (một thừa số của $\large N$), chúng giống nhau hết dù chúng không bằng nhau theo modulo 15. Điều này có nghĩa là:

<div align="center">

$$\Large2\equiv5\quad(\bmod 3),\quad5\equiv11\quad(\bmod 3),\quad11\equiv2\quad(\bmod3)$$

</div>

**Có một điểm khá dễ nhầm tại phần nhìn riêng mod với 3 là :** đa số người đọc tưởng rằng Pollard's Rho chỉ cần nhìn thấy các giá trị giống nhau rồi là factor xuất hiện khi xem qua ví dụ trên. Vậy điều này nghĩa là gì, trước hết phải nhấn mạnh là ví dụ trên chỉ minh họa cơ chế collision không phải mô phỏng đầy đủ implementation của Pollard's Rho. Thực tế cơ chế quan trọng là:

<div align="center">

$$\Large x_{i} \equiv x_{j} \quad (\bmod p) \Rightarrow p | (x_{i} - x_{j})$$

$$\Large\text{Sau đó:}$$

$$\Large d = gcd(|x_{i} - x_{j}|,N)$$

$$\Large\text{nếu như }1 < d < N \text{ thì } d \text{ là factor}$$

</div>

> Đây là phần giải thích kỹ về ước chung lớn nhất, là phần quan trọng nhất của thuật toán

**Pollard's Rho chọn** $$\large\mathrm{x_{i},x_{j}}$$ **như thế nào?:** Pollard's Rho không lấy mọi cặp $$\large x_{i},x_{j}$$ để so sánh với nhau. Nếu làm như vậy, số lượng cặp sẽ tăng rất nhanh :

<div align="center">

$$\Large(x_{1},x_{2}),(x_{1},x_{3}),\ldots,(x_{2},x_{3}),\ldots$$

</div>

Và bản thân việc tìm collision lại trở thành một bài toán lớn. Thay vào đó, Pollard's Rho sử dụng cycle detection để tìm dấu hiệu hai vị trí trong dãy đã gặp nhau mà không cần lưu và so sánh tất cả các giá trị trước đó. Một cách minh họa đơn giản là thuật toán Floyd's cycle detection, thường được gọi là phương pháp tortoise and hare, ở đây:

- **x (rùa) :** đi 1 bước mỗi vòng

- **y (thỏ) :** đi 2 bước mỗi vòng , nghĩa là đi gấp đôi x (rùa)

Từ đó ta xét :

<div align="center">

$$\Large f(x) = (x^{2} + x) \bmod N$$

</div>

Ta cập nhật hai biến, nghĩa là khi cái biểu thức trên được thực hiện xong thì nó sẽ gán kết quả vào hai biến liền :

<div align="center">

$$\Large x \leftarrow f(x)$$

$$\Large y \leftarrow f(f(y)) \text{ Chú ý tới phần nhân ngoài ngoặc}$$

</div>

Bây giờ, sau mỗi lần cập nhật nghĩa là gán kết quả vào hai biến. Ta tiến hành tính ước chung lớn nhất:

<div align="center">

$$\Large d = gcd(|x - y|,N)$$

$$\Large\text{Nếu }1 < d < N \text{ Thì tìm được factor}$$

</div>

**Nhưng tại sao chỉ cần so sánh** $$\large x$$ **và** $$\large y$$ **?** : Đây là điểm chí mạng rất dễ hiểu nhầm, nên ta giải thích kỹ phần này. Pollard's Rho không cần biết trước cặp $$\large i,j$$ nào sẽ tạo ra collision (va chạm). Nó cho hai con trỏ chạy với tốc độ khác nhau như trên là $$\large x = f(x)$$, $$\large y = f(f(y))$$ .Nếu dãy có chu kỳ, cuối cùng hai con trỏ sẽ gặp nhau theo modulo factor $$\large p$$. Khi đó :

<div align="center">

$$\Large x \equiv y \quad (\bmod p) \Rightarrow p|(x-y)$$

$$\Large\text{vì đồng thời: } p|N $$

$$\Large\text{Nên: } p|gcd(|x-y|,N)$$

$$\Large\text{Và ta thử: } d = gcd(|x-y|,N)$$

$$\Large\text{Nếu }1 < d < N \text{ thì }d\text{ chính là một non-trivial factor của }N$$

</div>

**Tại sao cái này quan trọng với Pollard's Rho?:** Vì khi hai giá trị $$\large x_{i}$$ ko đồng dư với $$\large x_{j}$$ khi thực hiện chia lấy dư với $$\large N$$ ($$\large x_{i}\not\equiv x_{j} (\bmod N)$$) nhưng lại đồng dư khi chia lấy dư với $$\large p$$ nghĩa là $$\large x_{i} \equiv x_{j} (\bmod p)$$ ở đây trong trường hợp ví dụ hiện tại là $\large p = 3$, thì hiệu của chúng sẽ chia hết cho $\large p$ ,tức là chúng khác nhau khi xét modulo $$\large N$$ nhưng đồng dư khi xét modulo $$\large p$$ và điều quan trọng là $$\large p\mid N$$. **Ví dụ:**

<div align="center">

$$\Large|5 - 2| = 3\quad\text{ chia hết cho 3 }$$

$$\Large|11 - 5| = 6\quad\text{ chia hết cho 3 }$$

$$\Large|11 - 2| = 9\quad\text{ chia hết cho 3 }$$

$$\Large\Rightarrow\text{ Khi ta tính gcd của hiệu đó với N = 15 , ta sẽ bắt được thừa số 3}$$

</div>

**Pollard's Rho lấy thừa số để làm gì?:** Khi Pollard's Rho tìm được một thừa số $\large d$, ta không dừng ở đó. Ta dùng nó để tách số $\large N$ ra thành hai phần nhỏ hơn. **Ví dụ**, nó biết thừa số của 15 là 3 như đã tính modulo ở trên, nó tiến hành lấy hai số này chia lại và ra kết quả $$\large15\div3=5$$, khi có kết quả là 5 nó có hai phần nhỏ là 5 và 3 suy ra nó có $$\large\boxed{15 = 5 \times 3}$$. Bây giờ nó lấy hai số này thực hiện như bước hai, biết nó là số nguyên tố vậy 5 và 3 chính là kết quả nhân tố của 15. Lúc này thuật toán đã hoàn thành

> xác nhận số nguyên tố bằng thuật toán kiểm tra nguyên tố Miller–Rabin / kiểm tra ước đến căn bậc hai.

Bây giờ **ví dụ** với số lớn lúc nãy là $$\large N = 501349247128579388923$$, đầu tiên xác định một thừa số của nó. Ko dùng tay, ta dùng thuật toán cho máy tính làm điều này, thuật toán có tại [Dự án caculator](https://github.com/tranquanghao708/Caculator-Project). Sau khi chạy thuật toán ta được :

<p align="center">
	<img src="image/hinh_anh_sau_nay.img" alt="Kết quả sau khi chạy thuật toán RHO">
</p>

và kết quả là :

<div align="center">

$$\Large501349247128579388923 = 370522189 \times 1353088322407$$

</div>

<details>
	<summary><b>[Chi tiết]</b> lý do ko tính tay với số lớn như trên</summary>

---

Khi dùng tay tính số lớn như trên, ta có :

<div align="center">

$$\Large x_{n+1} = x_{n}^{2} + 1 (\bmod 501349247128579388923)$$

$$\Large x_{0} = 97 \quad\text{ chọn một giá trị khởi tạo } x_{0}\text{ ,thường là một số nhỏ như 2}$$

$$\Large x_{1} = 97^{2} + 1 = 9410$$

$$\Large x_{2} = 9410^{2} + 1 = 88548101$$

$$\Large x_{3} = 88548101^{2} + 1 = 7840766190706202$$

$$\Large x_{4} = 7840766190706202^{2} + 1 = 61477614457321445630319481264805 \bmod 501349247128579388923 = 48870595701283080795$$

$$\Large x_{5} = 48870595701283080795^{2} + 1 = 2388335124198268335567405459326497832026 \bmod 501349247128579388923 = 48870595701283080795$$

$$\Large\ldots$$

$$\text{Phải đi qua hàng chục vòng, với cả số lớn và phải tính như thế này rất dễ sai và mệt}$$

</div>

Và hơn cả trăm lượt như thế, giống như cách ngốc nghếch kia chả khác gì lấy modulo chia từng bước. Nên ko ai tính tay với số như vậy, phải khai thác sức mạnh tính toán của CPU

<sub>--đã hết phần giải thích--</sub>

---

</details>

<sub>--đã hết phần giải thích--</sub>

---

</details>

tuy nhiên ta thấy $$\large2.5e+21 \text{ mod } 2 = 0_{10}$$, kết quả chia lấy dư là `0` nó chia hết cho `2`, mà nếu $$\large(2.5e+21) \times 2 = (5e+21) \text{ mod } 2 = 0_{10}$$ thì nó vẫn chia hết cho `2`. Ta thấy `2.5` với riêng lẻ chia cho `2` nó dư `0.5` nhưng với `2.5e+21` thì nhờ vào số mũ làm thay đổi giá trị rất lớn và nó khác hoàn toàn nên chia hết cho `2`.

Vậy nên nếu phép giá trị đã phân tích chia hết cho `2` thì suy ra chuỗi `0x1.000002p-24f` là biểu diễn nhị phân hữu hạn

<details>
	<summary><b>[Câu hỏi]</b> Tại sao có thể dùng phép kiểm chứng phép chia thực hiện chính xác để nhân tố số 5e+21 và có thể suy ra là số biễu diễn nhị phân hữu hạn?</summary>

---

Phần này cần phân biệt rõ, đây là phần rất tinh vi dễ gây nhầm nhất. Chúng ta cần phải phân biệt chia hết cho 2 và biễu diễn nhị phân hữu hạn, vô hạn, cùng với đó ta cần khám phá thêm khái niệm phân tích thành các thừa số và phân tích thành thừa số nguyên tố.

Đâù tiên là phân biệt chia hết cho 2 $$\large\neq$$ biễu diễn nhị phân hữu hạn, như đã nói ở phần important tại chương [3.1.1.Hai phương pháp xử lý biểu diễn nhị phân hữu hạn và vô hạn](#311hai-phương-pháp-xử-lý-biểu-diễn-nhị-phân-hữu-hạn-và-vô-hạn) :

<p align="center">
<kbd>
	<img alt="phần important chương 3.1.1" src="image/image31.png">
</kbd>
</p>

Nghĩa là việc dùng định lý phân số để suy ra hữu hạn và vô hạn là khả thi, nhưng việc nhân tố là điều rất quan trọng, tuy nhiên ko phải cứ chia hết cho 2 là biễu diễn hữu hạn. Ở phần important ta có thấy một ví dụ với số 40, ta thấy $$\large40 = 20 \times 2$$ và $$\large40 = 2^{3} \times 5$$ hai cái đều đúng, tuy nhiên $$\large20\times2$$ chỉ là một cách phân tích thành các thừa số, còn $$\large2^{3}\times5$$ là phân tích thành thừa số nguyên tố và hai cái này khác nhau

<sub>--Đã hết phần giải thích--</sub>

---

</details>

<sub>--đã hết phần giải thích--</sub>

---

</td>
</tr>
</table>
</details>

### 3.6.Round toward negative infinity (−∞)

### 3.7.Tác dụng và mức biểu diễn độ chính xác của 5 quy tắc làm tròn, khi nào nên dùng quy tắc nào?

từ 5 quy tắc làm tròn trên, trước hết ta có bảng so sánh :

| Rounding mode             | Ý nghĩa               |
| :-------------------------: | :---------------------: |
| **toward +∞**             | đi về `+∞`            |
| **toward −∞**             | đi về `−∞`            |
| **toward 0**              | đi về `0`             |
| **nearest, ties to even** | chọn giá trị gần nhất |
