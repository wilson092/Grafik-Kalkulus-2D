# 📈 Grafik Kalkulus 2D

![C++](https://img.shields.io/badge/C++-17-blue.svg)
![SFML](https://img.shields.io/badge/SFML-Graphics-green.svg)
![Status](https://img.shields.io/badge/Project-Completed-success.svg)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)

Program visualisasi grafik fungsi matematika 2D menggunakan **C++** dan **SFML**.  
User dapat memasukkan fungsi matematika secara langsung dan melihat grafiknya secara real-time.

---

## ✨ Features

- Input fungsi matematika (contoh: `sin(x)`, `x^2 + 3*x - 1`)
- Mendukung operator:
  - `+  -  *  /  ^`
- Mendukung fungsi matematika:
  - `sin(x)`
  - `cos(x)`
  - `tan(x)`
  - `sqrt(x)`
  - `log(x)`
  - `exp(x)`
  - `abs(x)`
- Input custom `X Min` dan `X Max`
- Auto scaling sumbu Y
- Grid dinamis
- Tampilan GUI interaktif (SFML)
- Output hasil akhir ke CLI setelah window ditutup

---

## 🛠 Tech Stack

- C++17
- SFML (Simple and Fast Multimedia Library)
- Custom Expression Parser
- Object-Oriented Programming

---

## 📂 Project Structure

```text
grafik-2D/
├── main.cpp
├── run.sh
├── OpenSans-Regular.ttf
└── README.md
```

---

## 🧠 Architecture Overview

### 🔹 Expression Parser
Menggunakan struct `Parser` untuk:
- Parsing ekspresi matematika
- Mendukung prioritas operator
- Mendukung nested expression `( )`
- Evaluasi fungsi dengan variabel `x`

### 🔹 Coordinate Transformation
Konversi koordinat matematika → koordinat layar:
- `sx(x)` → transformasi sumbu X
- `sy(y)` → transformasi sumbu Y

### 🔹 Rendering System
Menggunakan:
- `sf::LineStrip` untuk menggambar grafik
- `sf::Vertex` untuk grid
- `sf::Text` untuk label angka
- `sf::RectangleShape` untuk axis

---

## ⚙️ Installation & Setup

### 1️⃣ Install SFML

Download SFML dari:
https://www.sfml-dev.org/download.php

Pastikan sudah:
- Include path diset
- Library path diset
- Linker ditambahkan:
  ```
  sfml-graphics
  sfml-window
  sfml-system
  ```

---

### 2️⃣ Compile (Windows - g++ Example)

```bash
g++ main.cpp -o graph -lsfml-graphics -lsfml-window -lsfml-system
```

---

### 3️⃣ Run

```bash
./graph
```

Atau jalankan langsung dari IDE (Visual Studio / CodeBlocks / MinGW).

---

## 🖥 How To Use

1. Jalankan program
2. Masukkan fungsi di kolom `f(x)`
3. Atur `X Min` dan `X Max`
4. Tekan Enter
5. Grafik akan otomatis diperbarui
6. Tutup window untuk melihat hasil numerik di CLI

---

## 📊 Example Input

```
sin(x)
x^2
x^3 - 4*x
sqrt(abs(x))
```

---

## 🧮 Mathematical Range

Default:
```
X : -10 → 10
Y : Auto-scale mengikuti rasio layar
```

---

## 🎯 Concepts Applied

- Expression Parsing
- Recursive Descent Parser
- Coordinate Mapping
- Real-time Rendering
- GUI Programming with SFML
- OOP Struct Design
- Mathematical Visualization

---

## 📌 Future Improvements

- Zoom dengan mouse scroll
- Drag to pan
- Multiple function plotting
- Color selection
- Save graph as image

---

## 👨‍💻 Author

Project dibuat sebagai implementasi visualisasi kalkulus 2D menggunakan C++ dan SFML.
