#version 330

// Definisikan variabel untuk posisi jarum-jarum jam
uniform float currentSecondPointer;
uniform float currentMinutePointer;
uniform float currentHourPointer;

// Definisikan variabel untuk warna
uniform vec4 color1;
uniform vec4 color2;
uniform vec4 color3;

// Output akhir warna
layout(location = 0) out vec4 color;

// Variabel interpolasi untuk posisi vertex
varying vec2 vPos;

void main()
{
    // Inisialisasi warna awal ke putih
    color = vec4(1.0, 1.0, 1.0, 1.0);
    
    // Hitung jarak dari titik tengah (0,0)
    float distance = length(vPos);

    // Cek jika jarak kurang dari atau sama dengan 0.8
    if (distance <= 0.8)
    {
        // Jika jarak kurang dari atau sama dengan 0.8, tetapkan warna ke putih
        color = vec4(1.0, 1.0, 1.0, 1.0);
    }

    // Membuat jarum detik
    float dotSecond = dot(normalize(vPos), vec2(cos(currentSecondPointer), sin(currentSecondPointer)));
    if (distance >= 0.3 && distance <= 0.4 && dotSecond < sin(currentSecondPointer))
    {
        // Jika dalam jarak tertentu dan berada di bawah jarum detik, ubah warna menjadi color3
        color = color3;
    }

    // Membuat jarum menit
    float dotMinute = dot(normalize(vPos), vec2(0.6 * cos(currentMinutePointer), 0.6 * sin(currentMinutePointer)));
    if (distance >= 0.5 && distance <= 0.6 && dotMinute < 0.6 * sin(currentMinutePointer))
    {
        // Jika dalam jarak tertentu dan berada di bawah jarum menit, ubah warna menjadi color2
        color = color2;
    }

    // Membuat jarum jam
    float dotHour = dot(normalize(vPos), vec2(0.8 * cos(currentHourPointer), 0.8 * sin(currentHourPointer)));
    if (distance >= 0.7 && distance <= 0.8 && dotHour < 0.8 * sin(currentHourPointer))
    {
        // Jika dalam jarak tertentu dan berada di bawah jarum jam, ubah warna menjadi color1
        color = color1;    
    }
}
