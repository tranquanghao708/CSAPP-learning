# CSAPP : data size (dung lượng)

**index**

- 1.dung lượng là gì?

- 2.sự thay đổi dung lượng của chương trình, kiểu dữ liệu khi tới chuỗi nhị phân khác

- 3.Vì sao khi tới chuỗi nhị phân khác lại thay đổi data size?

- 4.Kết luận

---

## 1.dung lượng là gì?

- Là biểu thị cho sưc nặng của files, chương tình, kiểu dữ liệu. Ký hiệu có thể là b, Kb, Mb, Gb, Tb v.v. mỗi lần quy đổi đều là 1024, 1 KB = 1024 B, tương tự với ký hiệu khác

## 2.sự thay đổi dung lượng của chương trình, kiểu dữ liệu khi tới ngành kiến trúc khác

- khi chuyển đổi chuỗi nhị phân khác 32bit sang 64bit hay ngược lại thì data size sẽ bị đổi, như long vốn 4byte 32bit nhưng 8byte ở 64bit từ đó chênh lệch file 64bit nặng hơn so với 32bit

## 3.Vì sao khi tới chuỗi nhị phân khác lại thay đổi data size?

- Sự khác biệt về lưu trữ : khi chuyển 32bit sang 64bit, nhiều hệ thống thường gộp lại các byte như 8byte. Nếu nó ko phải là bội của 8 byte đó thì sẽ thêm padding thêm dẫn tới tăng kích thước

- bổ sung metadata : đảm bảo system đọc đúng thứ tự endianess (tùy vào system), hệ thống thường phải gắn thêm các thẻ header hoặc thông tin kiểm tra lỗi (parity bits) vào luồng nhị phân. Việc này làm tăng tổng kích thước tệp