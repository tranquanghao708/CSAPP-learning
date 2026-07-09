# CSAPP : Data Sizes – Kích thước dữ liệu trong bộ nhớ

**index**

- [1.data size](#1data-size)

- [1.1.dung lượng là gì?](#11dung-lượng-là-gì)

- [1.2.data size là gì?](#12data-size-là-gì)

- [1.3.khác nhau giữa data size và dung lượng là gì?](#13khác-nhau-giữa-data-size-và-dung-lượng-là-gì)

- [1.4.kích thước trên đĩa (size on disk)](#14kích-thước-trên-đĩa-size-on-disk) 

- [1.5.làm thế nào để biết chính xác file size thực tế?](#15làm-thế-nào-để-biết-chính-xác-file-size-thực-tế)

- [2.word](#2word)

- 2.1.word là gì?

- 3.sự thay đổi data size của kiểu dữ liệu khi tới kiến trúc (architecture) khác

- 3.1.kiến trúc (architecture) là gì?

- 3.2.sự thay đổi data size của chương tình, kiểu dữ liệu khi tới kiến trúc khác

- 5.Alignment và padding

- 6.Ví dụ thực tế trên IA-32 và x86-64

- 7.Kết luận

---

## 1.data size

#### 1.1.dung lượng là gì?

- Lượng bộ nhớ hoặc số byte cần để lưu trữ một đối tượng. Có các ký hiệu b (bit), B (byte), Kb , Mb v.v. 

> [!IMPORTANT]
> tuy nhiên khác nhau hệ quy đổi ở 2 hệ. Hệ 1 là SI ở đây 1 KB = 1000 B, còn hệ IEC là 1KiB = 1024 B. Phân biệt ký hiệu in hoa và thường, KB = killobyte, kb = killobit -> KB $$\large\neq$$ kb tương tự với các kiểu dữ liệu khác

#### 1.2.data size là gì?

- là kích thước dữ liệu hoặc kích thước của kiểu dữ liệu trong bộ nhớ. Thường đo bằng byte. Trong C data size thường được xác định bằng toán tử sizeof

#### 1.3.khác nhau giữa data size và dung lượng là gì?

- data size là kích thước kiểu dữ liệu hoặc đối tượng trong bộ nhớ còn dung lượng là lượng bộ nhớ hoặc số byte cần để lưu trữ cái program đó. Ví dụ, kiểu int có size 4byte trong bộ nhớ đó là data size, thiết bị A có ổ hhd là 500GB đó là dung lượng

- data size thường xác định kiểu dữ liệu đó nặng hay nhẹ còn dung lượng là xác định thiết bị đó có thể chứa được bao nhiêu tệp

#### 1.4.kích thước trên đĩa (size on disk)

- khái niệm file size cũng là một loại kích thước dữ liệu, nhưng nó nói về tệp trên hệ thống tệp chứ không phải đối tượng trong RAM.

- Kích thước trên đĩa thường lớn hơn kích thước thực tế của tệp tin, do hệ điều hành lưu trữ dữ liệu theo từng khối (cluster) cố định, ví dụ file_a có file size là 1kb nhưng khi lưu vào ổ cứng chạy hệ điều hành linux hay windows thì nó sẽ lớn hơn. 

- từng khối (cluster) là gì? là đơn vị cấp phát nhỏ nhất của hệ thống tệp (filesystem). Xuống ổ cứng do hệ điều hành thực hiện, ko phải hệ điều hành nào cũng có đơn vị giống nhau nhưng ví dụ file có 1 kb nó cấp phát 4kb thì chỉ lưu 1kb là file size, 3kb còn lại là lãng phí vì ko lưu file size nào thật

<details>
	<summary>ví dụ thực tế</summary>
1 ký tự a là 1 byte, 1KB thường là 1024 byte vậy :

```c
#include <stdio.h>
int main(void){

	int a = 0;
	while ( a < 1024 ){
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

- nó đã lên 4kb, thực tế k.txt chỉ chiếm 1kb thôi nhưng do hệ điều hành cấp phát 3Kb theo cluster và nó cực kỳ lãng phí

</details>

#### 1.5.làm thế nào để biết chính xác data size thực tế?

- khá đơn giản, ta click chuột trái vào file cần xem, ấn `Properties` nó có chỉ thị size và size on disk, size là file size gốc của file còn size on disk là data file gốc + cluster:

![alt text](image/image2.png)

- nếu muốn terminal linux thì dùng `du -bh` để soi disk usage (dùng nhanh nếu xem sơ qua) hoặc dùng `ls -lh` ví dụ :

> du -bh k.txt

![alt text](image/image3.png)

terminal là 1.0kb còn properties là 1.0 kb là 1024 byte dữ liệu

- nếu thuần chính xác từng bit, soi tận block và quyền hạn của một file thì dùng `stat` :

> stat k.txt 

![alt text](image/image4.png)

size = 1024, block = 8 và nhiều info khác

## 2.byte và word

#### 2.1.word là gì?

## 3.sự thay đổi data size của chương trình, kiểu dữ liệu khi tới ngành kiến trúc khác

#### 3.1.kiến trúc (architecture) là gì?

- là những bản thiết kế vận hành của CPU , máy tính. Nó tác động tới tập lệnh, binary, thanh ghi v.v..
