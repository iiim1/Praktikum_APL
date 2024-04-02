#include <iostream>
#include <iomanip>
using namespace std;

void clrscr() {
    system("cls");
}

struct Date {
    int day;
    int month;
    int year;
};

struct ToDo {
    string nama;
    Date deadline;
    string status;
};

struct User {
    string username;
    string password;
};

bool registerUser(User users[], int& userCount) {
    try {
        string username, password;
        cout << "Registrasi Akun\n";
        cout << "Masukkan Nama Lengkap: ";
        getline(cin, username);
        cout << "Masukkan NIM: ";
        getline(cin, password);
        
        if (username.empty() || password.empty()) {
            throw invalid_argument("Input tidak boleh kosong.");
        }

        for (int i = 0; i < userCount; ++i) {
            if (users[i].username == username) {
                cout << "Akun sudah terdaftar dengan nama tersebut.\n";
                return false;
            }
        }
    
        users[userCount].username = username;
        users[userCount].password = password;
        userCount++;
        cout << "Registrasi berhasil!\n";
        return true;
    } catch(const invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
        return false;
    }
}

bool login(User users[], int userCount) {
    int percobaan = 0;
    string usernameInput, passwordInput;

    do {
        clrscr();
        cout << "==========================================================" << endl;
        cout << "|Anda Harus Login Untuk Mengakses Menu To Do List Planner|" << endl;
        cout << "==========================================================" << endl;
        cout << "Username : ";
        getline(cin, usernameInput);
        cout << "NIM : ";
        getline(cin, passwordInput);
        for (int i = 0; i < userCount; ++i) {
            if (users[i].username == usernameInput && users[i].password == passwordInput) {
                cout << "Login berhasil!" << endl;
                return true;
            }
        }
        percobaan++;
        cout << "Password atau Username anda salah!!" << endl;
        if (percobaan < 3) {
            cout << "Login gagal. Silakan coba lagi (" << percobaan << "/3)" << endl;
            clrscr();
        } else {
            cout << "Maaf anda telah gagal login sebanyak 3 kali." << endl;
            cout << "Program berhenti." << endl;
            return false;
        }
    } while (percobaan < 3);
    return false;
}

void tambahToDo(ToDo* tugas, int& jml) {
    cout << "Tambah To Do \n";

    cout << "Masukkan Nama To Do : ";
    cin.ignore();
    getline(cin, tugas[jml].nama);

    cout << "Masukkan Deadline To Do (dd mm yyyy): ";
    cin >> tugas[jml].deadline.day >> tugas[jml].deadline.month >> tugas[jml].deadline.year;
    tugas[jml].status = "Not Yet";

    jml++;
}

void editToDo(ToDo* tugas, int& jml) {
    int indeks;
    cout << "Edit To Do\n";
    cout << "Masukkan indeks tugas yang ingin diedit: ";
    cin >> indeks;
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
            getline(cin, tugas[indeks - 1].nama);
            break;
        case 2:
            cout << "Masukkan Deadline Baru To Do (dd mm yyyy) : ";
            cin >> tugas[indeks - 1].deadline.day >> tugas[indeks - 1].deadline.month >> tugas[indeks - 1].deadline.year;
        case 3:
            int status;
            cout << "1. Selesai\n2. Belum Selesai\nMasukkan Status Baru To Do : ";
            cin >> status;
            if (cin.fail() || (status != 1 && status != 2)) {
                cout << "Input tidak valid. Masukkan angka 1 atau 2.\n";
                cin.clear();
                cin.ignore();
                return;
            }
            if (status == 1) {
                tugas[indeks - 1].status = "Finished";
            } else {
                tugas[indeks - 1].status = "Not Yet";
            }
            break;
    }

    cout << "Tugas berhasil diubah.\n";
}

void tampilkanToDo(ToDo* tugas, int& jml) {
    cout << "To Do List :\n";

    if (jml > 0) {
        cout << setw(5) << "No" << setw(40) << "Nama" << setw(40) << "Deadline" << setw(15) << "Status" << endl;
        cout << setfill('-') << setw(100) << "-" << setfill(' ') << endl;

        for (int i = 0; i < jml; i++) {
            cout << setw(5) << i + 1 << setw(40) << tugas[i].nama << setw(40) << tugas[i].deadline.day << "/" << tugas[i].deadline.month << "/" << tugas[i].deadline.year << setw(15) << tugas[i].status << endl;
        }
    } else {
        cout << "Belum ada To do\n";
    }
}

void hapusToDo(ToDo* tugas, int& jml) {
    int indeks;
    cout << "Hapus To Do : \n";
    cout << "Masukkan indeks tugas yang ingin dihapus: ";
    cin >> indeks;

    for (int i = indeks - 1; i < jml - 1; i++) {
        tugas[i] = tugas[i + 1];
    }
    jml--;
    cout << "Tugas berhasil dihapus.\n";
}

bool ulangiMenu() {
    char jawaban;
    cout << "Apakah Anda ingin kembali ke menu? (y/n): ";
    cin >> jawaban;

    cin.ignore();
    if (jawaban == 'y' || jawaban == 'Y') {
        clrscr();
        return true;
    } else if (jawaban == 'n' || jawaban == 'N') {
        clrscr();
        cout << "Program Selesai.\n";
        return false;
    } else {
        cout << "Masukkan tidak valid. Silakan jawab dengan y/n.";
        return ulangiMenu();
    }
}

void mainMenu(User users[], int userCount, ToDo tugas[], int& jml) {
    int pilihan;
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
            break;
        case 2:
            clrscr();
            tampilkanToDo(tugas, jml);
            editToDo(tugas, jml);
            break;
        case 3:
            clrscr();
            tampilkanToDo(tugas, jml);
            break;
        case 4:
            clrscr();
            hapusToDo(tugas, jml);
            break;
        default:
            cout << "ERRORR!!\nPilihan tidak valid.\n";
            break;
    }

    if (ulangiMenu()) {
        mainMenu(users, userCount, tugas, jml);
    }
}

void displayRegisterLoginMenu(User users[], int& userCount, ToDo tugas[], int& jml) {
    int choice;
    do {
        clrscr();
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1:
                registerUser(users, userCount);
                break;
            case 2:
                if (login(users, userCount)) {
                    clrscr(); 
                    mainMenu(users, userCount, tugas, jml); 
                }
                break;
            case 3:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 3);
}

int main() {
    const int MAX_USERS = 100;
    User users[MAX_USERS];
    int userCount = 0;
    ToDo tugas[MAX_USERS];
    int jmlTugas = 0;

    displayRegisterLoginMenu(users, userCount, tugas, jmlTugas);

    return 0;
}