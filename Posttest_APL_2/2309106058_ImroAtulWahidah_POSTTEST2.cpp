#include <iostream>
#include <iomanip>
#include <windows.h>
using namespace std;

void clrscr() {
    system("cls");
}

bool login() {
    int percobaan = 0;
    string usernameInput, passwordInput;
    string username = "imro atul wahidah";
    string password = "2309106058";

    do {
        clrscr();
        cout << "==========================================================" << endl;
        cout << "|Anda Harus Login Untuk Mengakses Menu To Do List Planner|" << endl;
        cout << "==========================================================" << endl;
        Sleep(1000);
        cout << "Username : ";
        getline(cin, usernameInput);
        cout << "NIM : "; cin >> passwordInput;
        cin.ignore();
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

void tambahToDo(string tugas[][3], int& jml) {
    cout << "Tambah To Do \n";

    cout << "Masukkan Nama To Do : ";
    cin.ignore();
    getline(cin, tugas[jml][0]);

    cout << "Masukkan Deadline To Do : ";
    getline(cin, tugas[jml][1]);
    cin.ignore();
    tugas[jml][2] = "Not Yet";

    jml++;
}

void editToDo(string tugas[][3], int& jml) {
    int indeks;
    cout << "Edit To Do\n";
    cout << "Masukkan indeks tugas yang ingin diedit: ";
    cin >> indeks;

    if (indeks >= 1 && indeks <= jml) {
        clrscr();
        cout << "1. Edit Nama To Do\n";
        cout << "2. Edit Deadline To Do\n";
        cout << "3. Edit Status To Do\n";
        cout << "Masukkan pilihan Anda: ";

        int pilihan;
        cin >> pilihan;
        switch (pilihan) {
            case 1:
                cout << "Masukkan Nama Baru To Do : ";
                cin.ignore();
                getline(cin, tugas[indeks - 1][0]);
                break;
            case 2:
                cout << "Masukkan Deadline Baru To Do : ";
                cin.ignore();
                getline(cin, tugas[indeks - 1][1]);
                break;
            case 3:
                int status;
                cout << "1. Selesai\n2. Belum Selesai\nMasukkan Status Baru To Do : ";
                cin >> status;
                if (status == 1){
                    tugas[indeks - 1][2] = "Finished";
                } else {
                    tugas[indeks - 1][2] = "Not Yet";
                }
                break;
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }

        cout << "Tugas berhasil diubah.\n";
    } else {
        cout << "Indeks tidak valid.\n";
    }
}

void tampilkanToDo(string tugas[][3], int& jml) {
    cout << "To Do List :\n";
    
    if (jml > 0) {
        cout << setw(5) << "No" << setw(40) << "Nama" << setw(40) << "Deadline" << setw(15) << "Status" << endl;
        cout << setfill('-') << setw(100) << "-" << setfill(' ') << endl;

        for (int i = 0; i < jml; i++) {
            cout << setw(5) << i + 1 << setw(40) << tugas[i][0] << setw(40) << tugas[i][1] << setw(15) << tugas[i][2] << endl;
        }
    } else {
        cout << "Belum ada To do\n";
    }
}

void hapusToDo(string tugas[][3], int& jml) {
    int indeks;
    cout << "Hapus To Do : \n";
    cout << "Masukkan indeks tugas yang ingin dihapus: ";
    cin >> indeks;

    if (indeks >= 1 && indeks <= jml) {
        for (int i = indeks - 1; i < jml - 1; i++) {
            for (int j = 0; j < 3; j++) {
                tugas[i][j] = tugas[i + 1][j];
            }
        }
        jml--;
        cout << "Tugas berhasil dihapus.\n";
    } else {
        cout << "Indeks tidak valid.\n";
    }
}

int main() {
    int jml = 0, pilihan;
    string tugas[100][3]; 
    
    if (login()) {
        string ulang = "y";
        while (ulang == "y") {
            clrscr();
            cout << "Menu :\n"
                << "1. Tambah To Do \n"
                << "2. Edit To Do \n"
                << "3. Tampilkan To Do \n"
                << "4. Hapus To Do \n"
                << "Masukkan Pilihan Anda : ";
            cin >> pilihan;
            switch (pilihan) {
            case 1:
                clrscr();
                tambahToDo(tugas, jml);
                cout << "\n";
                tampilkanToDo(tugas, jml);
                break;
            case 2:
                clrscr();
                tampilkanToDo(tugas, jml);
                cout << "\n";
                editToDo(tugas, jml);
                clrscr();
                tampilkanToDo(tugas, jml);
                break;
            case 3:
                clrscr();
                tampilkanToDo(tugas, jml);
                break;
            case 4:
                clrscr();
                tampilkanToDo(tugas, jml);
                cout << "\n";
                hapusToDo(tugas, jml);
                clrscr();
                tampilkanToDo(tugas, jml);
                break;
            default:
                cout << "ERRORR!!\nPilihan tidak valid.\n";
                break;
            }

            cout << "Apakah ingin mengulang? (y/n) : ";
            cin >> ulang;
            if (ulang != "y") {
                clrscr();
                Sleep(500);
                cout << "Program Selesai.";
                break;
            }
        }
    }
    return 0;
}
