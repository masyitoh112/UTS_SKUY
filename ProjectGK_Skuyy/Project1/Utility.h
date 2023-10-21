#pragma once

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

// Fungsi untuk membaca isi dari sebuah file berdasarkan nama file yang diberikan
string readFile(string fileName)
{
    cout << "Reading File " << fileName << endl;
    string fileText;

    // Membuka file dengan nama yang diberikan
    ifstream myFile(fileName);

    string tempText;

    // Membaca file baris per baris dan menyimpannya dalam string fileText
    while (getline(myFile, tempText))
    {
        fileText += tempText + "\n";
    }

    // Menampilkan isi file yang dibaca ke layar (ini mungkin bisa dihilangkan di produksi)
    cout << fileText << endl;

    return fileText;
}
