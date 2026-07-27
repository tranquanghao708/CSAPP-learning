# CSAPP : Floating point numbers - IEEE 754 (số thực dấu phẩy động chuẩn IEEE 754)

> Ngày bắt đầu viết : 13/7/2026

> Ngày hoàn thành :

**mục lục**

- [1.Tổng quan về IEEE 754](#1Tổng-quan-về-ieee-754)

- [1.1.Chuẩn hóa số thực (normalized)](#11Chuẩn-hóa-số-thực-normalized)

- [1.1.1.Khử chuẩn hóa số thực (Denormalized)](#111khử-chuẩn-hóa-số-thực-denormalized)

- [1.1.2.Khi nào IEEE 754 sử dụng Normalized và Denormalized?](#112Khi-nào-ieee-754-sử-dụng-normalized-và-denormalized)

- [1.1.3.Vô hạn (infinity)](#113Vô-hạn-infinity)

- [1.1.4.ko phải một số (NaN)](#114ko-phải-một-số-nan)

- [1.1.5.zero](#115zero)

- [1.2.Trường Fraction (phần trị - significand)](12Trường-fraction-phần-trị---significand)

- [1.3.Trường số mũ (Exponent)](#13Trường-số-mũ-exponent)

- [1.3.1.Độ lệch (Bias)](#131độ-lệch-bias)

- [1.4.Trường số dấu (signed)](#14trường-số-dấu-signed)

- [2.Rounding tổng quan và các chế độ làm tròn](#2rounding-tổng-quan-và-các-chế-độ-làm-tròn)

- [2.1.Round to nearest, ties to even](#21round-to-nearest-ties-to-even)

- [2.1.1.guard bit](#211guard-bit)

- [2.1.2.round bit](#212round-bit)

- 2.1.3.sticky bit

- 2.1.4.cách phần cứng dùng các guard bit, round bit và sticky bit để xác định ba trường hợp

- 2.1.5.Vị trí của 3bit này nằm ở đâu, vì sao phần cứng lại biết và nhắm tới chính xác vị trí của 3bit này để soi?

- 2.2.Round toward zero

- 2.3.Round toward infinity positive floating numbers

- 2.4.Round toward infinity negative floating numbers

- [3.Chuyển đổi số thực sang hệ nhị phân và chuyển đổi hệ nhị phân sang số thực](#2chuyển-đổi-số-thực-sang-hệ-nhị-phân-và-chuyển-đổi-hệ-nhị-phân-sang-số-thực)

- [3.1.Encode](#21encode)

- [3.1.1. Chuyển phần nguyên sang nhị phân](#211chuyển-phần-nguyên-sang-nhị-phân)

- 3.1.2. Chuyển phần thập phân sang nhị phân

- 3.1.3. Chuẩn hóa số thực

- 3.1.4. Tính Actual Exponent

- 3.1.5. Tính Exponent Field (Exponent + Bias)

- 3.1.6. Lấy Fraction

- 3.1.7. Ghép Sign | Exponent | Fraction

- 3.1.8. Ví dụ hoàn chỉnh

- 3.2.Decode

- 3.2.1. Tách Sign | Exponent | Fraction

- 3.2.2. Khôi phục Actual Exponent

- 3.2.3. Khôi phục Hidden Bit

- 3.2.4. Tính giá trị Significand

- 3.2.5. Nhân với 2^Exponent

- 3.2.6. Áp dụng Sign

- 3.2.7. Ví dụ hoàn chỉnh

- [3.Số thực lớn nhất và tính toán số thực lớn nhất](#3số-thực-lớn-nhất-và-tính-toán-số-thực-lớn-nhất)

- 4.Những lỗi về số thực khi lập trình cấp thấp

- 4.1.Underflow

- 4.2.Overflow

- 4.3.Precision Loss

- 5.Biểu diễn số thực trong bộ nhớ,sơ đồ

- 6.kết luận

---

## 1.Tổng quan về IEEE 754.

![alt text](image/image1.png)

> Ko phải CS:APP, tham khảo từ cuốn kiến trúc máy tính vì tính dễ hiểu về formula

- `Số thực IEEE 754` là quy tắc biểu diễn số thực cho thiết bị nhị phân (máy tính) thế giới. **Formula tổng quan là** $$\Large(-1)^{S} \times 1.m \times 2^{e-b}$$, trong đó :

S : là bit dấu, viết tắt sign

m : hidden bit + fraction là phần trị (trường dãy số sau dấu chấm của số thực sau khi đã chuẩn hóa)

e : là giá trị của trường exponent

b : là độ lệch, viết tắt bias

- Ta có một structure của cái này như sau:

| S (sign) | E (Exponent) | m (Fraction) |
|----------|--------------|--------------|

#### 1.1.Chuẩn hóa số thực (normalized)

![alt text](image/image2.png)

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
	<summary>tại sao phải chuẩn hóa số thực?</summary>

- Vì nếu ko chuẩn hóa mọi số thực sẽ có cùng value nhưng nhiều cách biểu diễn sẽ khác nhau **ví dụ** $$\large1001.1_{2}\times2$$, $$\large100.11_{2}\times2^{1}$$, $$\large10.011_{2}\times2^{2}$$, $$\large1.0011_{2}\times2^{3}$$. Cùng giá trị nhưng dịch dot khác biểu diễn. Nên IEEE quy định sử dụng dạng $$\large1.xxxxx\times2^{N}$$ để mỗi số chỉ có một biểu diễn duy nhất. Ngoài ra, vì bit đầu tiên luôn là 1, CPU không cần lưu bit này (gọi là hidden bit hoặc implicit leading 1), nhờ đó tăng thêm một bit độ chính xác cho trường Fraction.

</details>

#### 1.1.1.Khử chuẩn hóa số thực (Denormalized)

![alt text](image/image3.png)

> trích từ CS:APP

- Là việc bit đầu tiên là 0 nhưng nó thực hiện phép toán $$\large0.xxxxx\times2^{1-bias}$$. **Lúc này** hiddenbit ko còn là 1 nữa, nó là 0 và exponent field luôn là 0. Giả sử float (32bits) ta có :

```
Exponent = 00000000
Fraction = 00000000000000000000001
```

thì đây ko phải là parent $$\large1.0000000000_{2}\times2^{127}$$ mà là $$\large0.0000000000000000000001_{2}\times2^{-126}$$ vì hiddenbit đã bằng 0. **Vậy vì sao phải làm như vậy?**, ta biết normalized nó sẽ có bit đầu luôn là 1, exponent của nó là dương hay âm tùy thuộc vào cách dịch dấu chấm là trái hay phải ,nhưng điều gì sẽ xảy ra nếu số thực cực kỳ nhỏ **ví dụ** $$\large2^{-150}$$ hay $$\large0.000000000000000000000001_{2}$$, nếu vẫn cố chuẩn hóa về $$\large1.xxxxx\times2^{N}$$ thì kết quả sẽ bị underflow tức là bị làm tròn thành 0

> [!IMPORTANT]
> Đối với normalized numbers, IEEE754 dùng $$\large1.xxxxx\times2^{N}$$ nên số đầu tiên luôn là 1
>
> Còn với Denormalized numbers, IEEE754 dùng $$\large0.xxxxx\times2^{1 - Bias}$$ nên `exponent field = 0` và hiddenbit được xem là 0. Khử chuẩn hóa được thiết kế để biểu diễn với số gần 0 nhất **tránh bị underflow** quá sớm

#### 1.1.2.Khi nào IEEE 754 sử dụng Normalized và Denormalized?

- `Normalized` được ưu tiên khi biểu diễn số thực vì dạng này tận dụng hiddenbit, giúp tăng thêm một bit chính xác, dùng cho hầu hết các số thực 

- Nếu `normalized` không biểu diễn được nhưng vẫn còn nằm trong phạm vi **subnormal** mới được chọn tới `denormalized` để biểu diễn các số sát `0` nhất có thể. Tuy nhiên độ chính xác sẽ thấp hơn, dùng cho số rất nhỏ gần sát `0`

> [!IMPORTANT]
> `Normalized` được IEEE ưu tiên vì độ chính xác cao hơn, tận dụng hiddenbit với dạng $$\large1.xxxxx\times2^{N}$$. Nhưng nếu số quá nhỏ cần phải dùng tới `Denormalized` với dạng $$\large0.xxxxx\times2^{1 - bias}$$ , điều này giúp biễu diễn các số sát `0` nhất có thể, tuy nhiên độ chính xác thấp hơn.
>
> Nếu `Denormalized` ko thể sử dụng được nữa (nhỏ hơn cả subnormal nhỏ nhất) thì gía trị số thực sẽ bị underflow và kết quả sẽ thành `0`

#### 1.1.3.Vô hạn (infinity)

![alt text](image/image4.png)

> Trích từ CS:APP

- Trong IEEE chuẩn còn định nghĩa là dương vô cực ($$\large+\infty$$) và âm vô cực ($$\large-\infty$$), infinity xuất hiện khi kết quả của một phép tính vượt quá phạm vi biểu diễn của kiểu số thực. **Ví dụ** biểu thức cho float (32bits) $$\large3.5\times10^{38}\times10 = +\infty$$ với giá trị của biểu thức vừa rồi lớn hơn giá trị float lớn nhất (số thực lớn nhất) nên nó sẽ là dương vô cực ($$\large+\infty$$) vì `sign = 0` là số dương. Phần số thực lớn nhất ở mục [3.Số thực lớn nhất và tính toán số thực lớn nhất](#3số-thực-lớn-nhất-và-tính-toán-số-thực-lớn-nhất)

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
	<summary>ví dụ với C</summary>

- Cho đoạn C sau :

```c
#include <stdio.h>

int main(void){
	float a = 1e39f
	printf("%f\n",a);
	return 0;
}
```

> gcc -o float_infinity float_infinity.c

khi compiled ra ta thấy compiler nó cảnh baó với info `warning: floating constant exceeds range of ‘float’ [-Woverflow]` đó là chúng ta cần test, bây giờ chạy thử :

![alt text](image/image5.png)

ta thấy hiện `inf` nghĩa là dương vô cực $$\large+\infty$$

</details>

#### 1.1.4.ko phải một số (NaN)

![alt text](image/image6.png)

> trích từ CS:APP

- là một giá trị đặc biệt, chỉ thị cho không xác định hoặc số đó ko phải là số thực $$\large\frac{0}{0} = \text{NaN}$$, $$\large\infty-\infty=\text{NaN}$$, $$\large\sqrt{-1}=\text{NaN}$$ (đối với số thực). IEEE 754 quy định NaN có dạng như :

| Sign | Exponent | Fraction |
|------|----------|----------|
| 0 hoặc 1 | Toàn bộ bit = 1 | Khác 0 |

Nghĩa là Exponent phải là tòan bộ bit là một và Fraction phải có ít nhất một bit khác 0 cấu trúc như trong image trên từ CS:APP

> [!IMPORTANT]
> NaN chỉ xảy ra khi exponent toàn bộ bit phải là 1 và frantion $$\large\neq$$ 0
>
> Điểm cần phân biệt :
> - Fraction = 0 : infinity ($$\large+\infty$$, $$\large-\infty$$)
> - Fraction $$\large\neq$$ 0 : NaN

NaN có tính chất đặc biệt là **ko bằng bất kỳ giá trị nào kể cả chính nó**

<details>
	<summary>Ví dụ với C</summary>

- Cho đoạn C sau :

```c
#include <math.h>
#include <stdio.h>

int main(void){
	double x = NAN;
	printf("dounle NaN x == x is : %d\n",x == x); // kết quả là 0
	printf("dounle NaN x != x is : %d\n",x != x); // kết quả là 1
	printf("dounle NaN x < x is : %d\n",x < x); // kết quả là 0
	printf("dounle NaN x > x is : %d\n",x > x); // kết quả là 0
	return 0;
}
```

> gcc -o Double_NaN Double_NaN.c

![alt text](image/image7.png)

**Vì sao nó lại ra 0?:** Theo chuẩn IEEE 754, mọi phép so sánh bằng (==) với NaN đều trả về false, kể cả khi so sánh chính nó. `0` và `1` được xem làm gía trị boolean true false trong việc này. Ở đây so sánh `x == x` vốn dĩ x lại là NaN nên giá trị là `False = 0`. Điều này cũng như vậy với phép so sánh khác như lớn hơn, bé hơn, lớn hơn hoặc bằng và bé hơn hoặc bằng trừ các hàm chuyên biệt như `isnan()`

Điều này khiến việc kiểm tra NaN phải dùng hàm `isnan()` trong `<math.h>` thay vì toán tử `==`.

</details>

Nếu trong condition ta thấy `if(x != x)` thì điều đó chỉ đúng khi `x = NaN` vì NaN là thứ duy nhất giúp `x != x` trả true. Đây là một mẹo thường gặp trong các câu hỏi về C, compiler và IEEE 754. Vì NaN là giá trị duy nhất mà biểu thức `x != x` luôn đúng, một số mã nguồn hoặc trình biên dịch có thể dùng tính chất này để phát hiện NaN.

#### 1.1.5.Zero

- trong toán học giá trị `0` gần như bằng nhau nhưng trong biểu diễn số thực chuẩn IEEE754 dạng bit nhị phân nó lại biểu diễn khác ở phần sign. Ví dụ float (32bit) khi ta gắn gía trị `-0` thì biễu diễn tất cả các bit là 0 trừ sign là 1, nhưng gắn giá trị `+0` thì biễu diễn tất cả các bit là 0 và sign cũng ko ngoại lệ. $$\large\pm0$$ trong biểu diễn số thực ở máy tính là âm hay dương tùy vào sign là 1 hay 0

> [!IMPORTANT]
> Trong IEEE biểu diễn dưới dạng bit thì giá trị `0` :
> - Exponent = 0
> - Fraction = 0
> - Sign = 1 hoặc 0

dù vậy nhưng nó vẫn quy định `+0 == -0` vẫn phải True. Tuy nhiên trong một phép toán, dấu của số 0 vẫn đươc bảo toàn ví dụ như $$\large\frac{1}{+0}=+\infty$$ hay $$\large\frac{1}{-0}=-\infty$$ . Nhờ vậy, CPU vẫn có thể xác định hướng mà một giá trị tiến tới 0 trong nhiều phép tính số học.

**Vì sao nó phải làm vậy?:** Ở đây, $$\large x -> 0^{-}$$ (tiến tới 0 từ phía âm) và $$\large x -> 0^{+}$$ (tiến tới 0 từ phía dương). Và trong giải tích hai giới hạn này khác nhau ở nhiều hàm ví dụ $$\large\frac{1}{x}$$ ở đây khi x tiến tới 0 từ phía âm ($$\large x -> 0^{-}$$) thì giá trị sẽ là âm vô hạn ($$\large-\infty$$) còn nếu khi x tiến tới 0 từ phía dương ($$\large x -> 0^{+}$$) thì giá trị sẽ là dương vô hạn ($$\large+\infty$$) IEEE quy định giữ lại dấu của giá trị `0` để phần cứng có thể phân biệt hai trường hợp này và cho ra kết quả đúng

<details>
	<summary>ví dụ với C</summary>

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

![alt text](image/image8.png)

ta thấy khi runtime program, nó trả SIGFPE vậy lỗi này ko phải SIGSEGV (truy cập vaddr ko hợp lệ) **vậy nó là gì?**, tuy nó là có tên gọi là Floating-Pointing (FP) số thực dấu phẩy động nhưng thực chất lỗi này đại diện cho tất cả phép toán ko phù hợp kể cả các lỗi tràn số (overflow) nghiêm trọng hoặc dùng phép tính như chia cho 0, căn bậc hai của một số âm mà ko dùng thư viện số phức hay kết quả tính toán số thực ko xác định. Ta cần sửa lại đoạn C thành:

```c
#include <stdio.h>

int main(void){
	float x = 1.0f / 0.0f; //chia cho +0
	float y = 1.0f / -0.0f; // chi cho -0

	printf("1 / +0: %f\n 1 / -0: %f\n",x,y);
	return 0;
}
```

![alt text](image/image9.png)

Đây là kết quả chính xác của phép $$\large x -> 0^{-} = -\infty$$ (tiến tới 0 từ phía âm) và $$\large x -> 0^{+} = +\infty$$ (tiến tới 0 từ phía dương) và $$\large\frac{1}{-0} = -\infty$$, $$\large\frac{1}{+0} = +\infty$$

**Vì sao khi chia cho 0 ở số thực này nó lại ko bắn SIGFPE?:** Vì đây là phép chia dấu phẩy động CPU sẽ dùng FPU/SSE (divss, divsd,.. ) để thực hiện điều đó là tập lệnh phù hợp cho phép chia trong trường hợp này nên nó sẽ ko gây ra lỗi gì

Lưu ý: trong C, phép chia số nguyên cho 0 trong C là undefined behavior (UB), trên linux CPU thực hiện lệnh idiv hoặc div và phần cứng sinh lỗi divide error exception nếu (#DE) nếu thấy chia cho 0 và kernel nhận exception này rôi gửi SIGFPE

</details>

#### 1.2.Trường Fraction (phần trị - significand)

- Là trường lưu các bit phía sau dấu chấm của số nhị phân sau khi đã chuẩn hóa số thực theo dạng chuẩn hóa $$\large1.xxxxx\times2^{N}$$:

![alt text](image/image0.png)

Trường Fraction quyết định precision (độ chính xác) của số thực. IEEE 754 càng dành nhiều bit cho trường Fraction thì càng biểu diễn được nhiều chữ số có nghĩa hơn. Lúc này, độ chính xác vì thế mà tăng. 

- **Điểm thường bị nhầm :** Values trong fraction $$\large\neq$$ độ chính xác. Cái quyết định độ chính xác là số lượng bit được cấp cho trường Fraction

#### 1.3.Trường số mũ (Exponent)

- Là trường biểu diễn số mũ của số thực sau khi chuẩn hóa. Số mũ được xác định bằng số lần dịch dấu chấm để đưa số về dạng $$\large1.xxxxx\times2^{N}$$, **ví dụ** $$\large101.00110_{2} = 1.0100110_{2}$$ dịch chuyển dot sang trái 2 lần số mũ = 2 (dương), $$\large0.00110_{2} = 001.00110_{2} = 1.00110_{2}$$ dịch chuyển dot sang phải 3 lần số mũ = -3 (âm), rõ hơn đã nói trước ở [1.1.Chuẩn hóa số thực](#11Chuẩn-hóa-số-thực)

- Exponent đóng vai trò quyết định độ lớn của số thực, **ví dụ** $$\large1.11111_{2}\times2^{2} = 7.875_{10}$$ nhưng đổi giá trị số mũ  $$\large1.11111_{2}\times2^{10} = 2016{10}$$ giá trị đổi, mặc dù fraction ko đổi

> [!IMPORTANT]
> Exponent quyết định độ lớn của số thực, tùy thuộc vào số mũ lớn nhỏ bao nhiêu
>
> Fraction quyết định chữ số có nghĩa (độ chính xác của số thực), tùy thuộc vào hệ thống cung cấp bao nhiêu bit cho nó
>
> **điều quan trọng** : Exponent quyết định scale (độ lớn) của số thực thông qua lũy thừa $$\large2^{N}$$ . Chỉ cần thay đổi Exponent một lượng nhỏ, giá trị của số thực có thể thay đổi rất lớn. Fraction thiên hướng về quyết định chữ số có nghĩa (độ chính xác của số thực) nhưng khi thay đổi các bit trong trường Fraction sẽ làm thay đổi giá trị của số thực, nhưng mức thay đổi thường nhỏ hơn nhiều so với việc thay đổi Exponent. **Precision (độ chính xác)** không phụ thuộc vào giá trị của Fraction mà phụ thuộc vào số lượng bit được **IEEE 754** cấp cho trường Fraction. **Ví dụ**, double có 52 bit Fraction nên biểu diễn số thực chính xác hơn float với 23 bit Fraction.

- **Điểm thường bị nhầm :** Trường exponent ko lưu trực tiếp actual exponent (số mũ thực) ký hiệu `N` trong dạng chuẩn hóa $$\large1.xxxxx\times2^{N}$$ , giá trị của trường exponent được tính theo công thưc `Exponent Field = Actual exponent + Bias`.

#### 1.3.1.Độ lệch (Bias)

- Bias là một giá trị cố định được cộng vào mọi actual exponent, không phân biệt âm hay dương, trước khi lưu vào trường Exponent. **Ví dụ** với float 32bit, exponent là 8bit nhưng bias = $$\large2^{8-1}-1 = 127_{10}$$, là Tmax của exponent (8 bit), nếu `exponent = 3` thì thực hiện phép cộng $$\large3_{10} + 127_{10} = 130_{10}$$ CPU sẽ lưu $$\large10000010_{2}$$ hệ ko dấu , còn nếu `exponent = -3` thì thực hiện phép cộng $$\large (-3) + 127 = 124_{10}$$ CPU sẽ lưu $$\large01111100_{2}$$ hệ ko dấu, còn nếu muốn recover lại số `-3` thì tính ngược lại với phép trừ là $$\large124 - 127 = -3_{10}$$ lúc này sẽ là chính xác số âm được biểu diến lúc đầu

> [!NOTE]
> Công thức tính BIAS nếu biết bit của actual exponent thì dùng formula tính tmax như sau $$\large2^{N-1}-1$$ **ví dụ** exponent field của double (64bit) là 11bit thì $$\large2^{11-1}-1 = 1023$$

**Điều dễ nhầm khi học Bias này:** là cách CPU nó lưu values, với bias biểu diễn số thực IEEE 754 **ví dụ** khi exponent field (11bit) của kiểu double(64bit) khi tính phải lấy giá trị exponent cộng với bias khi biểu diễn số dương (quy tắc encode) và trừ với bias khi chuyển đổi lại sang âm (quy tắc decode) , **ví dụ** giá trị `exponent = 6` vì dịch dấu chấm sang trái 6 lần nhưng tính thì $$\large6_{10} + 2^{11-1}-1 = 6_{10} + 1023_{10} = 1029_{10}$$ và CPU sẽ lưu giá trị `1029` dạng mã nhị phân thay vì lưu trực tiếp giá trị 6. Còn **ví dụ** về số âm, `exponent = -7` vì dịch dấu chấm sang phải 7 lần thì $$\large-7_{10} + 1023_{10} = 1016_{10}$$ CPU sẽ lưu gía trị `1016` với nhị phân, thay vì lưu trực tiếp `-7`. Còn muốn phục hồi về `-7` thì nó sẽ dùng $$\large1016_{10} - 1023_{10} = -7_{10}$$

<details>
	<summary>vì sao IEEE 754 ko dùng two_complement_code để biểu diễn số âm cho bias?</summary>

- Nếu dùng two_complement_code cho bias, thì $$\large-1_{10}$$ sẽ là $$\large111111_{2}$$ và nó sẽ khá phức tạp, khó so sánh thứ tự. Nên IEEE 754 quy định mọi biểu diễn số âm trong số thực chuẩn đều được biểu diễn là dương và thực hiện phép cộng cho Tmax của exponent, vì thế thiết kế phần cứng và nhiều thứ sẽ được đơn giản hóa hơn so với việc phức tạp hóa vấn đề ko cần thiết

</details>

- dạng có độ chính xác đơn tương ứng 32bit và dạng có độ chính xác kép tương ứng 64bit và kép mở rộng tương đương 128bit :

| name                 | Tổng số bit | Exponent | Fraction |  Bias |
| ------------------- | ---------- | ------- | ------- | ---- |
| Single precision    |          32 |        8 |       23 |   127 |
| Double precision    |          64 |       11 |       52 |  1023 |
| Quadruple precision |         128 |       15 |      112 | 16383 |

IEEE 754 quy định các parent phổ biến như bảng

**Khái niệm chính xác đơn (Single precision) và chính xác kép (Double precision) là gì?:** kiểu chính xác đơn là kiểu số thực IEEE dài 32bit ví dụ float, còn chính xác kép là kiểu IEEE dài 64bit ví du double vì trong lịch sử tên gọi đơn biểu thị cho độ chính xác ban đầu và kép biểu thị cho gấp đôi độ chính xác ban đầu

#### 1.4.Trường số dấu (signed)

- Là trường chỉ tính `MSB = 1` hay `MSB = 0`, quyết định số âm hay dương. **Ví dụ** cho số thực $$\large19.6875_{10}$$ có sign là 0 (MSB = 0) vì nó không phải là số âm còn nếu cho $$\large-19.6875_{10}$$ thì sign là 1 (MSB = 1) vì nó là số âm

## 2.Rounding tổng quan và các chế độ làm tròn

- không phải mọi số thập phân đều biểu diễn chính xác trong nhị phân, nên IEEE 754 phải làm tròn (rounding). Đây là nguyên nhân của những kết quả như `0.1 + 0.2 != 0.3` trong nhiều ngôn ngữ lập trình. Phần chương này sẽ biểu diễn và tổng quát về việc này

**Vì sao lại phải rounding?:** Trong hệ thống máy tính, bit nhị phân là hữu hạn nhưng biểu diễn số thực một cách chính xác lại phải vô hạn nên khi đến một ngưỡng nào đó đụng tới rào cản hữu hạn sẽ xem như làm tròn của bit nhị phân đó ví dụ 4 bit $$\large0000_{2}$$ thì số thực chỉ được biểu diễn ở phạm vi bit này, bit được cấp cho trường fraction và các trường khác lại rất ít nên độ chính xác vì thế mà giảm rất đáng kể

<details>
	<summary>Ví dụ C</summary>

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

![alt text](image/image11.png)

ta thấy số thực nó đã bị làm tròn ở đây khá hỗn loạn nên cũng là lý do x($$\large0.1_{10} + 0.2_{10}$$) $$\large\neq$$ 0.3, chỉ có thể biểu diễn **xấp xỉ** với trường hợp này chứ ko thể dùng **tuyệt đối** như `==`

</details>

Các chế độ của Rounding (làm tròn)

#### 2.1.Round to nearest, ties to even

- Đây là chế độ mặc định của việc làm tròn số thực dấu phẩy động của IEEE , nó thực hiện làm tròn về số gần nhất, nếu đúng giữa hai số thì chọn số chẵn. Ý tưởng gồm hai bước, đầu tiên là nó chọn giá trị gần nhất với số cần biểu diễn, thứ hai là phân theo ba trường hợp, trường hợp số nhỏ hơn nữa sẽ giữ nguyên, trường hợp số lớn hơn nữa sẽ làm tròn lên, trường hợp số đúng bằng nữa (tie) thì chọn số bit cuối là 0 (even)

Đầu tiên : làm tròn về số gần nhất, **ví dụ** `0.3244` làm tròn thành `0.324`, `0.3246` làm tròn thành `0.325` đơn giản là làm tròn về số gần nhât

Thứ hai : như trên sẽ phân theo ba trường hợp 

nếu trường hợp số nhỏ hơn nữa sẽ giữ nguyên **ví dụ** Cpu chỉ giữ 2 fraction ở bit, cho bit biểu diễn số thực như sau : $$\large1.010001_{2} = \mathbf{1.265625_{10}}$$ và bây giờ CPU lấy 2 fraction suy ra nó chỉ có thể biểu diễn làm tròn $$\large1.01_{2} = 0100_{2}$$ hoặc $$\large1.10_{2} = 1000_{2}$$ và bit bị cắt là $$\large0001_{2}$$

- **Lưu ý :** giá trị $$\large1.10_{2} = 1000_{2}$$ và $$\large1.01_{2} = 0100_{2}$$ ở đây ta thấy có phần nguyên là bit 1, nhưng việc quy đổi và so sánh ở trường hợp này là chỉ tính các bit fraction chứ ko phải phần nguyên

bây giờ so sánh **phần bị cắt với đúng một ngưỡng là một nữa của ULP**:

> Phần details về ULP

<details>
	<summary>ULP(unit in the last place)</summary>

Đây là khái niệm dùng để giải thích vì sao CPU làm tròn bằng cách này, ko phải cấu trúc chính của IEEE. Về nghĩa đen là giá trị của 1 đơn vị ở bit cuối cùng ở fraction, đơn giản hơn nó là khoảng cách giữa hai số IEEE 754 có thể biểu diễn được **ví dụ** sau chuẩn hóa ta có tập hợp $$\large(1.00_{2},1.01_{2},1.10_{2},1.11_{2})$$ và các số này lần lượt tương ứng với tập hợp $$\large(1.00_{10},1.25_{10},1.50_{10},1.75_{10})$$ và bây giờ khoảng cách giữa chúng là :

| phép tính | kết quả |
|-----------|---------|
| 1.25 - 1.00 | 0.25 |
| 1.50 - 1.25 | 0.25 |
| 1.75 - 1.50 | 0.25 |

Vậy ULP = 0.25, nếu gặp trường hợp như `một nữa của ULP` thì lấy đó chia hai lên thôi, ví dụ $$\large\frac{0.25}{2} = 0.125$$ thì con số `0.125` này chính là con số ở ngưỡng mà IEEE quyết định làm tròn 

</details>

Ở đây ta tiến hành tính ULP trước tiên phải biết $$\large1.01 = \mathbf{1.25_{10}}$$ và $$\large1.10 = \mathbf{1.50_{10}}$$ :

| phép tính | kết quả |
|-----------|---------|
| 1.50 - 1.25 | 0.25 |

$\large\mathrm{ULP} = \boxed{0.25}$ vậy bây giờ ta biết $$\large0.25_{10} = \mathbf{0.01_{2}}$$ bây giờ ta lấy nó chia cho hai vì half ULP mà $$\large\frac{0.25}{2} = \mathbf{0.125_{10}}$$ bây giờ ta biết $$\large0.125_{10} = 0.001_{2}$$ bây giờ viết đầy đủ 4bit ta có $$\large0.0010_{2}$$ và nó chính là ngưỡng làm tròn, tiến hành so sánh phần bị cắt với half ULP $$\large0001_{2} < 0010_{2}$$ ta thấy nó nhỏ hơn vậy nó sẽ giữ nguyên $$\large\boxed{1.01_{2}}$$

<details>
	<summary>Vì sao lại đem phần bị cắt đi so với half ULP?</summary> 

- **Vì sao lại đem phần bit bị cắt đi so với half ULP:** Vì phần bị cắt chính là phần sai số (error) nếu giữ nguyên số hiện tại, IEEE cần biết lượng sai số này xem nó lớn hay nhỏ hơn với nữa khoảng cách giữa hai số biểu diễn được (half ULP) để quyết định giữ nguyên hay làm tròn lên, Bây giờ **giả sử** CPU chỉ giữ lại một số lượng bit fraction nhất định. Khi cắt bớt bit, phần bị cắt là phần sai số (lượng giá trị bị mất), sau khi đã xác định hai giá trị IEEE có thể biểu diễn gần nhất, IEEE chỉ cần xét phần giá trị bị mất (phần bị cắt) để quyết định làm tròn., nó chỉ biết lượng giá trị bị mất này lớn đến đâu, IEEE lấy lượng gía trị bị mất so sánh với một nữa ngưỡng khoảng cách biểu diễn giữa hai số (half ULP), phần bị cắt chính là sai số khi giữ nguyên, còn half ULP là ngưỡng quyết định. IEEE chỉ cần so sánh hai đại lượng này để biết nên giữ nguyên hay làm tròn lên. Đây cũng là bản chất thuật toán, CPU nó ko so sánh hai số, nó chỉ so sánh số bit bị cắt với half ULP

</details>

nếu trường hợp số lớn hơn nữa sẽ làm tròn, **ví dụ** $$\large1.010011_{2}$$ và như cũ CPU giữ lại 2 fraction là $$\large1.01_{2}$$ và $$\large1.10_{2}$$ và số bit bị cắt là $$\large0011_{2}$$ bây giờ ta tính ULP:

| phép tính | kết quả |
|-----------|---------|
| 1.50 - 1.25 | 0.25 |

vẫn như cũ, $$\large\mathrm{ULP} = \boxed{0.25}$$ và ta biết half ULP của này là $$\large0.125_{10} = 0.001_{2}$$ tròn 4bit là $$\large0.0010_{2}$$ vì đó có sẵn ở ví dụ trước. Bây giờ so sánh phần sai số (round error) và nữa khoảng cách giữa hai số biểu diễn được (half ULP) suy ra $$\large0011_{2} > 0.0010_{2}$$ suy ra nó sẽ làm tròn thành $$\large\boxed{1.10}$$

nếu trường hợp số bằng đúng bằng nữa (tie) thì chọn số bit cuối là 0 (even) nó sẽ chọn số có LSB là 0, **ví dụ** ta có $$\large0.010010_{2}$$ với CPU chỉ giữ fraction ta có hai dạng như ví dụ trước là $$\large0.01_{2}$$ hay $$\large0.10_{2}$$ ở đây phần bị cắt là $$\large0010_{2}$$ và ta biết `half ULP = 0.125` vì nó vẫn tương tự ở các ví dụ trên thôi. Bây giờ, ta so sánh thấy phần đặc biệt là half ULP bằng với bit bị cắt $$\mathbf{\large0010_{2}\text{(số bit bị cắt)} == 0010_{2}\text{(Half ULP)}}$$ vì $$\large0.125_{10} = 0.001_{2}\text{(half ULP)}$$ tính theo đúng 4bit sẽ là $$\large\mathbf{0010_{2} \text{(half ULP)}}$$ ở đây việc nó bằng nhau thế này ta gọi đó là trường hợp bằng đúng bằng nữa (tie) nghĩa là giá trị phần bị cắt (round error) bằng đúng half ULP, tức sai số khi giữ nguyên và sai số khi làm tròn lên là như nhau. Số cần biểu diễn nằm đúng ở chính giữa hai số IEEE 754 có thể biểu diễn được.

Lúc này, IEEE ko được phép lúc nào cũng làm tròn lên vì nếu vậy thì nó sẽ sinh ra sai số dương tích lũy sau hàng triệu phép tính, thay vào đó nó quy định nếu đúng bằng half ULP thì chọn số có bit cuối cùng (LSB) bằng 0 (even). Ví dụ trường hợp này $$\mathbf{\large0010_{2}\text{(số bit bị cắt)} == 0010_{2}\text{(Half ULP)}}$$ thì đối tượng được làm tròn là $$\large1.10_{2}\text{hay}1.01_{2}$$ ta phân tích hai số này, $$\large1.10_{2}$$ có `LSB = 0` và $$\large1.01_{2}$$ có `LSB = 1` ta thấy IEEE quy định thì nó sẽ chọn số bit cuối cùng (LSB) bằng 0 (even) thì `LSB = 1` sẽ ko được chọn vì nó khác 0, `LSB = 0` sẽ được chọn vì nó bằng 0. Nên, số làm tròn sẽ thành $$\large\boxed{1.10_{2}}$$ vì nó có `LSB = 0` (thỏa mãn quy định của IEEE)

> [!IMPORTANT]
> Round to nearest, ties to even là nghệ thuật làm tròn mặc định mà chuẩn IEEE quy định:
> - nếu `(half ULP) < (số bit bị cắt)`, đây được gọi là số lớn hơn nữa và nó sẽ được làm tròn 
> - nếu `(half ULP) > (số bit bị cắt)`, đây được gọi là số bé hơn nữa và nó sẽ được giữ nguyên
> - nếu `(half ULP) = (số bit bị cắt)`, đây được gọi là số bằng đúng bằng nữa (tie) và nó sẽ chọn LSB có bit là 0 (even)
>
> so sánh một nữa khoảng cách giữa hai số biểu diễn được (half ULP) với bit bị cắt, điều dễ nhầm là chúng ta thường lấy bit bị cắt đi so sánh với bit fraction

#### 2.1.1.guard bit

Guard bit là bit đầu tiên bị cắt bỏ ngay sau bit fraction cuối cùng mà CPU quyết định giữ lại. **Ví dụ** như các ví dụ trên thì CPU giữ 2fraction, ở đây lấy ví dụ với bit $$\large1.0101101_{2}$$ bây giờ fraction là $$\large1.01_{2}$$ còn bit bị cắt là $$\large01101_{2}$$ bây giờ CPU sẽ chia số bit bị cắt này ra 4 phần trong đó có fraction, guard bit (G) , round bit (R) và sticky bit (S), nó sẽ chia như sau :

| Fraction | G | R | S |
|----------|---|---|---|
| 1.01	   | 0 | 1 | 101 |

Ta thấy, `G = 0` suy ra `guard bit = 0`, `R = 1` suy ra `round bit = 1`, `S = 1` suy ra `sticky bit = 1 (vì ít nhất nó cũng có bit 1)`

**Guard bit dùng để làm gì?:** Nó giúp CPU biết số bit bị cắt đã vượt qua half ULP hay chưa, thay vì tính thủ công là ULP xong chia lấy half ULP xong so sánh round error v..v thì CPU chỉ cần nhìn Guardbit, roundbit, stickybit (GRS). Nhưng ở đây ta chỉ nói riêng về Guardbit, nếu CPU nhìn `guardbit = 0` chắc chắn `x < half ULP` còn nếu `guardbit = 1` thì cần phải soi thêm round và sticky

#### 2.1.2.round bit

Round bit là bit thứ hai bị cắt, nó nằm phía sau Guard bit. Nó có ý nghĩa nếu guardbit là 1, nếu guardbit (G) là 0 thì biết chắc chắn là `x < half ULP` rồi ko cần phải soi round và sticky, nhưng nếu guard là 1 thì bây giờ mới soi round. Ở đây, cũng như ví dụ trên ta có :

| Fraction | G | R | S |
|----------|---|---|---|
| 1.01	   | 0 | 1 | 101 |

Cái này chắc chắn là `x < half ULP` vì `G = 0` nên round sẽ ko có ý nghĩa, nhưng giả sử ta cho `G = 1` như :

| Fraction | G | R | S |
|----------|---|---|---|
| 1.01	   | 1 | 1 | 101 |

thì lúc này `G = 1` nó sẽ soi thêm R vì lúc này round mới thực sự có ý nghĩa, nếu `G = 1 và R = 1` thì nó chắc chắn sẽ lớn hơn half ULP `x > half ULP` lúc này sẽ làm tròn lên

> [!IMPORTANT]
> Nếu `G = 0` thì R và S sẽ ko cần soi nữa, vì nó chỉ có ý nghĩa nếu `G = 1` là trước tiên xong mới tới R và mới tới S.
> - Nếu `G = 1 và R = 1` thì chắc chắn lớn hơn half ULP
> - Nếu `G = 1 và R = 0` thì phải soi thêm Sticky bit

## 3.Chuyển đổi số thực sang hệ nhị phân và chuyển đổi hệ nhị phân sang số thực

#### 3.1.Encode

- Phần này chuyển đổi số thực sang số nhị phân. Các bước như sau: 

#### 3.1.1. Chuyển phần nguyên sang nhị phân

- Ở đây chuyển phần nguyên sang nhị phân, ví dụ `29.81` phần này chỉ chú ý và chuyển 29 sang nhị phân kết quả là $$\large11101_{2}$$

#### 3.1.2. Chuyển phần thập phân sang nhị phân

- Ở đây sẽ chuyển phân thập phân sang nhị phân, ví dụ vừa rồi là $$\large29.81_{10}$$ ta đã chuyển thành $$\large11101_{2}.81_{10}$$ bây giờ còn phần thập phân là $$\large0.81_{10}$$ ta tiến hành chuyển đổi đổi nó, cách chuyển phần thập phân sang nhị phân phức tạp hơn phần nguyên. Thay vì liên tục chia cho 2 như phần nguyên, ta sẽ **liên tục nhân phần thập phân với 2**, sau mỗi lần nhân lấy phần nguyên của kết quả làm bit tiếp theo, rồi tiếp tục lặp với phần thập phân còn lại. Theo sơ đồ :

| Bước | Giá trị | ×2   | Bit lấy |
| ---: | ------- | ---- | ------- |
|    1 | 0.81    | 1.62 | 1       |
|    2 | 0.62    | 1.24 | 1       |
|    3 | 0.24    | 0.48 | 0       |
|    4 | 0.48    | 0.96 | 0       |
|    5 | 0.96    | 1.92 | 1       |
|  ... | ...     | ...  | ...     |

![alt text](image/image10.png)

> trích từ : [Tin học đại cương bách khoa hà nội](https://www.youtube.com/watch?v=ITpspAmKpCk&pp=ygUkc-G7kSB04buxYyBk4bqldSBwaOG6qXkgxJHhu5luZyBJRWVl)

**như thế các bit theo thứ tự ta sẽ thu được :** $$\large0.81\approx0.11001..$$