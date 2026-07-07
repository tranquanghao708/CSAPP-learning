# Writeup : phép true false boolean dưới dạng mã bit 

**mục lục**

- 1.Phép true false là gì và boolean dưới dạng mã bit là gì

- 1.1.Bốn phép toán Boolean cơ bản trên bit đơn lẻ

- 2.Tác dụng của phép bit boolean so với mảng các biến boolean

- 3.Biểu diễn Tập hợp bằng Bit Vectors

- 3.1.Bit Vectors là gì?

- 3.2.Biểu diễn tập hợp bằng bit vectors

- 4.Mở rộng phép toán Boolean lên Chuỗi Bit (Bit Vectors)

- 4.1.Khái niệm chuỗi bit là gì?

- 4.2.Mở rộng phép toán boolean lên chuỗi bit

- 5.Kết luận

---

## 1.Phép true false là gì và boolean dưới dạng mã bit là gì

- Phép true và false chỉ thị cho việc đúng/sai của chương trình, ví dụ nếu if(1) -> true, sẽ thực thi lệnh trong if nhưng if(0) -> falsem sẽ thực thi lệnh trong else

- boolean dưới dạng mã bit là biểu thị cho các phép tính bit như  `^ (xor), & (And), ~ (Not), | (Or)` thực hiện tính toán bit theo bảng chân trị của mỗi phép toán và trả về ra kết quả cuối là true hay false, ví dụ `1 & 1 = 1 -> true` , `1 & 0 = 0 -> false`

## 2.Tác dụng của phép bit boolean so với mảng các biến boolean

- tác dụng của phép bit boolean là tối ưu hiệu suất, làm cho chương trình nhanh chóng hơn so với mảng các biến boolean như `bool`. Lý do là việc tính các bit với các cổng trực tiếp của CPU nên nó nhanh hơn rất nhiều

- tiếp theo là tiết kiệm bộ nhớ

## 3.Biểu diễn Tập hợp bằng Bit Vectors

#### 3.1.Bit Vectors là gì?