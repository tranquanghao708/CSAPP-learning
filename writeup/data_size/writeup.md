# CSAPP : data size (dung lượng)

**index**

- 1.data size

- 1.1.dung lượng là gì?

- 1.2.data size là gì?

- 1.3.khác nhau giữa data size và dung lượng là gì?

- 1.4.kích thước trên đĩa (size on disk) 

- 2.byte và word

- 2.1.word là gì?

- 3.sự thay đổi dung lượng của chương trình, kiểu dữ liệu khi tới kiến trúc (architecture) khác

- 3.1.kiến trúc (architecture) là gì?

- 3.2.kích thước của kiểu dữ liệu

- 3.3.sự thay đổi dung lượng của chương tình, kiểu dữ liệu khi tới kiến trúc khác

- 4.Vì sao khi tới chuỗi nhị phân khác lại thay đổi data size?

- 5.Alignment và padding

- 6.Ví dụ thực tế trên IA-32 và x86-64

- 7.Kết luận

---

## 1.data size

#### 1.1.dung lượng là gì?

- Lượng bộ nhớ hoặc số byte cần để lưu trữ một đối tượng. Có các ký hiệu b (bit), B (byte), Kb , Mb v.v. 

> [!IMPORTANT]
> tuy nhiên khác nhau hệ quy đổi ở 2 hệ. Hệ 1 là SI ở đây 1 KB = 1000 B, còn hệ IEC là 1KiB = 1024 B

#### 1.2.data size là gì?

- là kích thước dữ liệu hoặc kích thước của kiểu dữ liệu trong bộ nhớ. Thường có ký hiệu tương tự nhưng nhỏ hơn như kb, mb, gb

#### 1.3.khác nhau giữa data size và dung lượng là gì?

- data size là lượng không gian thực tế mà một program, image đang chiếm dụng còn dung lượng là lượng bộ nhớ hoặc số byte cần để lưu trữ cái program đó. Ví dụ, image.png nặng 200kb đó là data size, thiết bị A có ổ hhd là 500GB đó là dung lượng

- data size thường xác định tệp đó nặng hay nhẹ còn dung lượng là xác định thiết bị đó có thể chứ được bao nhiêu tệp

#### 1.4.kích thước trên đĩa (size on disk)

- Kích thước trên đĩa thường lớn hơn kích thước thực tế của tệp tin, do hệ điều hành lưu trữ dữ liệu theo từng khối (cluster) cố định, ví dụ file_a có data size là 1kb nhưng khi lưu vào ổ cứng chạy hệ điều hành linux hay windows thì nó sẽ lớn hơn. 

- từng khối (cluster) là gì? là những chỉ thị lưu trữ dữ liệu xuống ổ cứng do hệ điều hành thực hiện, ko phải hệ điều hành nào cũng có chỉ thị giống nhau nhưng ví dụ file có 1 kb nó cấp phát 4kb thì chỉ lưu 1kb là data size, 3kb còn lại là lãng phí vì ko lưu data size nào thật

<details>
	<summary>ví dụ thực tế</summary>
1 ký tự a là 1 byte, 1KB thường là 1024 byte vậy :

```c
#include <stdio.h>
int main(void){

	int a = 0;
	while ( a <= 1024 ){
		printf("a");
		a++;
	}
	return 0;
}
```

> gcc -o kk kk.c

- lúc đầu k.txt là 0:

![alt text](image/image0.png)

- nhưng khi cho 1024 chữ a vào tròn 1kb là :

> ./kk > k.txt

![alt text](image/image1.png)

- nó đã lên 4kb, thực tế program chỉ chiếm 1kb thôi nhưng do hệ điều hành cấp phát 3Kb theo cluster và nó cực kỳ lãng phí

</details>

## 2.byte và word

#### 2.1.word là gì?

## 3.sự thay đổi dung lượng của chương trình, kiểu dữ liệu khi tới ngành kiến trúc khác

#### 3.1.kiến trúc (architecture) là gì?

- là những bản thiết kế vận hành của CPU , máy tính. Nó tác động tới tập lệnh, binary, thanh ghi v.v..
