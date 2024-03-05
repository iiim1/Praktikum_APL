#include <iostream>
#include <cstdlib>
#include<windows.h>
using namespace std;

void clrscr() {
    system("cls");
}

bool login() {
    int percobaan = 0;
    string usernameInput, passwordInput;
    string username = "imro";
    string password = "2309106058";

    do {
        cout << "Username : "; cin >> usernameInput;
        cout << "NIM : "; cin >> passwordInput;
        if (usernameInput == username && passwordInput == password) {
            cout << "Login berhasil!" << endl;
            return true;
        } else {
            percobaan++;
            cout << "Password atau Username anda salah!!"  << endl;
            if (percobaan < 3){
                cout << "Login gagal. Silakan coba lagi (" << percobaan << "/3)" << endl;
                Sleep(1200);
                clrscr();
            }
        }
    } while (percobaan < 3);

    Sleep(1200);
    clrscr();
    cout << "Maaf anda telah gagal login sebanyak 3 kali." << endl;
    Sleep(1000);
    cout << "Program berhenti." << endl;
    return false;
}

void konversiKMJam(double nilai) {
    double cmPerSec = nilai * 27.7778;  
    double mPerSec = nilai * 0.27778;   
    double milPerJam = nilai * 0.621371; 

    cout << nilai << " Kilometer/jam =\n";
    cout << cmPerSec << " Centimeter/detik\n";
    cout << mPerSec << " Meter/detik\n";
    cout << milPerJam << " Mil/jam\n";
}

void konversiCMDtk(double nilai) {
    double kmPerJam = nilai * 0.036;      
    double mPerSec = nilai * 0.01;       
    double milPerJam = nilai * 0.0223694; 

    cout << nilai << " Centimeter/detik =\n";
    cout << kmPerJam << " Kilometer/jam\n";
    cout << mPerSec << " Meter/detik\n";
    cout << milPerJam << " Mil/jam\n";
}

void konversiMDtk(double nilai) {
    double kmPerJam = nilai * 3.6;      
    double cmPerSec = nilai * 100;       
    double milPerJam = nilai * 2.23694;  

    cout << nilai << " Meter/detik =\n";
    cout << kmPerJam << " Kilometer/jam\n";
    cout << cmPerSec << " Centimeter/detik\n";
    cout << milPerJam << " Mil/jam\n";
}

void konversiMILJam(double nilai) {
    double kmPerJam = nilai * 1.60934;   
    double cmPerSec = nilai * 44.704;    
    double mPerSec = nilai * 0.44704;    

    cout << nilai << " Mil/jam =\n";
    cout << kmPerJam << " Kilometer/jam\n";
    cout << cmPerSec << " Centimeter/detik\n";
    cout << mPerSec << " Meter/detik\n";
}

int main(){
    int pilihan;
    double nilai;
    cout << "===============================================" << endl;
    cout << "|Anda Harus Login Untuk Mengakses Menu Konversi|" << endl;
    cout << "===============================================" << endl;
    Sleep(1000);
    
    if (login()) {
        char ulang = 'y';
        while(ulang == 'y'){
            clrscr();
            cout << "=============================================================================" << endl;
            cout << "|Konversi Kecepatan" << endl;
            cout << "=============================================================================" << endl;
            cout << "|1. Konversi Kilometer/jam ke (Centimeter/detik, Meter/detik, Mil/jam)       |" << endl;
            cout << "|2. Konversi Centimeter/detik ke (Kilometer/jam, Meter/detik, Mil/jam)       |" << endl;
            cout << "|3. Konversi Meter / detik ke(Kilometer / jam, Meter / detik, Mil / jam)     |" << endl;
            cout << "|4. Konversi Mil / jam ke(Kilometer / jam, Centimeter / detik, Meter / detik)|" << endl;
            cout << "=============================================================================" << endl;
            cout << "Masukan pilihan anda: "; cin >> pilihan;
            cout << "Masukkan nilai untuk konversi: "; cin >> nilai;
            clrscr();
            Sleep(1000);
            switch (pilihan) {
                case 1:
                    konversiKMJam(nilai);
                    break;
                case 2:
                    konversiCMDtk(nilai);
                    break;
                case 3:
                    konversiMDtk(nilai);
                    break;
                case 4:
                    konversiMILJam(nilai);
                    break;
                default:
                    cout << "Pilihan yang anda inputkan tidak valid!!" << endl;
            }
            cout << "Apakah kamu ingin mengulang? (y/t)"; cin >> ulang;
        }
        clrscr();
        Sleep(500);
        cout << "Program Selesai.";
    }
    return 0;
}