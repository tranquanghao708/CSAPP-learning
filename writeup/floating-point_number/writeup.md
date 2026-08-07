- 2.Biểu diễn số thực trong bộ nhớ,sơ đồ

- 7.Cách nhận diện số thực dạng nhị phân, lục phân trong reverse engineering

- 8.Cách viết số thực trong hợp ngữ

6.1 Biểu diễn số thực trong bộ nhớ

6.2 Little Endian

6.3 Nhận diện float trong hex dump

6.4 Nhận diện float trong disassembly

6.5 SSE/XMM Register

6.6 movss

6.7 movsd

6.8 addss

6.9 mulss

6.10 cvtsi2ss

6.11 cvttss2si

7. IEEE 754 trong Assembly

7.1 movss

7.2 movsd

7.3 cvtss2sd

7.4 cvttss2si

7.5 cvtsi2ss

7.6 x87 FPU

7.7 SSE

7.8 AVX

câu cần thêm sau này

Vì Hidden Bit không được lưu trong bộ nhớ nên khi xem trực tiếp dữ liệu IEEE 754 bằng debugger, hex editor hoặc reverse engineering, ta sẽ không nhìn thấy Hidden Bit. Muốn biết giá trị thực của significand, cần khôi phục Hidden Bit dựa vào giá trị của trường Exponent.