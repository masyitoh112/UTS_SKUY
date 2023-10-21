#version 330

// Mendefinisikan input atribut posisi sebagai vektor dua dimensi
layout (location = 0) in vec2 pos;

// Mendeklarasikan variabel vPos sebagai vektor dua dimensi yang akan digunakan pada fragmen shader
varying vec2 vPos;

void main()
{
    // Mengatur posisi akhir (gl_Position) dengan posisi yang diberikan, dan mengatur z dan w ke 0 dan 1
    gl_Position = vec4(pos.xy, 0.0, 1.0);
    
    // Mengisi variabel vPos dengan posisi xy dari input
    vPos = pos.xy;
}
