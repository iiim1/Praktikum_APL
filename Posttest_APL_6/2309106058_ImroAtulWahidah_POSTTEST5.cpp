#include <iostream>
#include <iomanip>
#include <windows.h>
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
    clrscr();
    string username, password;
    cout << "Registrasi Akun\n";
    cout << "Masukkan Nama Lengkap: ";
    getline(cin, username);
    cout << "Masukkan NIM: ";
    getline(cin, password);
    
    if (username.empty() || password.empty()) {
        cout << "Input tidak boleh kosong.\n";
        return false;
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
}

bool login(User users[], int userCount) {
    int percobaan = 0;
    string usernameInput, passwordInput;

    do {
        clrscr();
        cout << "==========================================================" << endl;
        cout << "|Anda Harus Login Untuk Mengakses Menu To Do List Planner|" << endl;
        cout << "==========================================================" << endl;
        Sleep(1000);
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
            Sleep(1200);
            clrscr();
        } else {
            cout << "Maaf anda telah gagal login sebanyak 3 kali." << endl;
            Sleep(1000);
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
    cin.ignore(); 
    tugas[jml].status = "Not Yet";

    jml++;
}

void editToDo(ToDo* tugas, int& jml) {
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
                getline(cin, tugas[indeks - 1].nama);
                break;
            case 2:
                cout << "Masukkan Deadline Baru To Do (dd mm yyyy) : ";
                cin >> tugas[indeks - 1].deadline.day >> tugas[indeks - 1].deadline.month >> tugas[indeks - 1].deadline.year;
                break; 
            case 3:
                int status;
                cout << "1. Finished\n"
                << "2. Not Yet\n"
                << "Masukkan Status Baru To Do : ";
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
            default:
                cout << "Pilihan tidak valid.\n";
                break;
        }
        cout << "Tugas berhasil diubah.\n";
    } else {
        cout << "Indeks tidak valid.\n";
    }
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

    if (indeks >= 1 && indeks <= jml) {
        for (int i = indeks - 1; i < jml - 1; i++) {
            tugas[i] = tugas[i + 1];
        }
        jml--;
        cout << "Tugas berhasil dihapus.\n";
    } else {
        cout << "Indeks tidak valid.\n";
    }
}

void insertionSortAscending(ToDo arr[], int n) {
    int i, j;
    ToDo key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && (arr[j].deadline.year > key.deadline.year || (arr[j].deadline.year == key.deadline.year && arr[j].deadline.month > key.deadline.month) || (arr[j].deadline.year == key.deadline.year && arr[j].deadline.month == key.deadline.month && arr[j].deadline.day > key.deadline.day))) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

//asc
void interpolationSearchByDate(ToDo* tugas, int& jml, Date searchDate) {
    bool found = false;
    cout << "To Do List dengan Deadline pada " << searchDate.day << "/" << searchDate.month << "/" << searchDate.year << ":\n";
    cout << setw(5) << "No" << setw(40) << "Nama" << setw(40) << "Deadline" << setw(15) << "Status" << endl;
    cout << setfill('-') << setw(100) << "-" << setfill(' ') << endl;

    for (int i = 0; i < jml; i++) {
        if (tugas[i].deadline.day == searchDate.day && 
            tugas[i].deadline.month == searchDate.month && 
            tugas[i].deadline.year == searchDate.year) {
            found = true;
            cout << setw(5) << i + 1 << setw(40) << tugas[i].nama << setw(40) << tugas[i].deadline.day << "/" << tugas[i].deadline.month << "/" << tugas[i].deadline.year << setw(15) << tugas[i].status << endl;
        }
    }

    if (!found) {
        cout << "Tidak ada ToDo dengan deadline pada tanggal tersebut.\n";
    }
}

//descending
void interpolationSearchByName(ToDo* tugas, int& jml, string searchName) {
    bool found = false;
    cout << "To Do List dengan Nama " << searchName << ":\n";
    cout << setw(5) << "No" << setw(40) << "Nama" << setw(40) << "Deadline" << setw(15) << "Status" << endl;
    cout << setfill('-') << setw(100) << "-" << setfill(' ') << endl;

    for (int i = 0; i < jml; i++) {
        if (tugas[i].nama == searchName) {
            found = true;
            cout << setw(5) << i + 1 << setw(40) << tugas[i].nama << setw(40) << tugas[i].deadline.day << "/" << tugas[i].deadline.month << "/" << tugas[i].deadline.year << setw(15) << tugas[i].status << endl;
        }
    }

    if (!found) {
        cout << "Tidak ada ToDo dengan nama tersebut.\n";
    }
}

void shellSortDescending(ToDo arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            string temp = arr[i].nama;
            int j;
            for (j = i; j >= gap && arr[j - gap].nama < temp; j -= gap) { 
                arr[j].nama = arr[j - gap].nama;
            }
            arr[j].nama = temp;
        }
    }
}

void selectionSort(ToDo arr[], int n, string key) {
    int i, j, first_idx;
    for (i = 0; i < n - 1; i++) {
        first_idx = i;
        for (j = i + 1; j < n; j++) {
            if (key == "asc") {
                if (arr[j].status < arr[first_idx].status) {
                    first_idx = j;
                }
            } else {
                if (arr[j].status > arr[first_idx].status) {
                    first_idx = j;
                }
            }
        }
        string swap = arr[first_idx].status;
        arr[first_idx].status = arr[i].status;
        arr[i].status = swap;
    }
}

void binarySearch(ToDo* tugas, int& jml, int searchStatus) {
    string namaStatus;
    bool found = false;
    int awal = 0;
    int akhir = jml - 1;
    namaStatus = (searchStatus == 1) ? "Finished" : "Not Yet";

    cout << "Daftar ToDo dengan status " << namaStatus << ":" << endl;
    while (awal <= akhir) {
        int tengah = (awal + akhir) / 2;
        if (tugas[tengah].status == namaStatus) {
            found = true;
            cout << setw(40) << "Nama" << setw(40) << "Deadline" << setw(15) << "Status" << endl;
            cout << setfill('-') << setw(100) << "-" << setfill(' ') << endl;
            cout << setw(40) << tugas[tengah].nama << setw(40) << tugas[tengah].deadline.day << "/" << tugas[tengah].deadline.month << "/" << tugas[tengah].deadline.year << setw(15) << tugas[tengah].status << endl;

            int idx = tengah - 1;
            while (idx >= 0 && tugas[idx].status == namaStatus) {
                cout << setw(40) << tugas[idx].nama << setw(40) << tugas[idx].deadline.day << "/" << tugas[idx].deadline.month << "/" << tugas[idx].deadline.year << setw(15) << tugas[idx].status << endl;
                idx--;
            }
            
            idx = tengah + 1;
            while (idx < jml && tugas[idx].status == namaStatus) {
                cout << setw(40) << tugas[idx].nama << setw(40) << tugas[idx].deadline.day << "/" << tugas[idx].deadline.month << "/" << tugas[idx].deadline.year << setw(15) << tugas[idx].status << endl;
                idx++;
            }
            return;
        } else if (tugas[tengah].status < namaStatus) {
            awal = tengah + 1;
        } else {
            akhir = tengah - 1;
        }
    }
    if (!found) {
        cout << "Tidak ada ToDo dengan status " << namaStatus << endl;
    }
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
    bool ulang = true;
    do {
        cout << "Menu :\n"
             << "1. Tambah To Do \n"
             << "2. Edit To Do \n"
             << "3. Tampilkan & Cari To Do berdasarkan tanggal terdahulu\n"
             << "4. Tampilkan & Cari To Do berdasarkan nama menurun\n"
             << "5. Tampilkan & Cari To Do berdasarkan status\n"
             << "6. Hapus To Do \n"
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
                insertionSortAscending(tugas, jml);
                tampilkanToDo(tugas, jml);
                {
                char jawaban;
                cout << "Apakah Anda ingin mencari To Do? (y/n): ";
                cin >> jawaban;
                if (jawaban == 'y' || jawaban == 'Y') {
                    int day, month, year;
                    cout << "Masukkan tanggal, bulan, dan tahun yang dicari (dd mm yyyy): ";
                    cin >> day >> month >> year;
                    cout << endl;
                    Date searchDate = {day, month, year};
                    clrscr();
                    interpolationSearchByDate(tugas, jml, searchDate);
                    break;
                } else {
                    ulang = false;
                }
                }
                break;
            case 4:
                clrscr();
                shellSortDescending(tugas, jml);
                tampilkanToDo(tugas, jml);
                {
                char jawaban;
                cout << "Apakah Anda ingin mencari To Do? (y/n): ";
                cin >> jawaban;
                if (jawaban == 'y' || jawaban == 'Y') {
                    string searchName;
                    cout << "Masukkan nama To Do yang dicari: ";
                    cin.ignore();
                    getline(cin, searchName);
                    clrscr();
                    interpolationSearchByName(tugas, jml,searchName);
                    break;
                } else {
                    ulang = false;
                }
                }
                break;
            case 5:
                clrscr();
                int pilSort, pilStatus;
                cout << "Pilihan Sorting Status\n"
                << "1. Tampilkan Ascending\n"
                << "2. Tampilkan Descending\n"
                << "Masukkan Angka Pilihan sorting yang diinginkan: ";
                cin >> pilSort;
                if (pilSort == 1) {
                    selectionSort(tugas, jml, "asc");
                } else {
                    selectionSort(tugas, jml, "desc");
                }
                clrscr();
                tampilkanToDo(tugas, jml);
                {
                char jawaban;
                cout << "Apakah Anda ingin mencari To Do? (y/n): ";
                cin >> jawaban;
                if (jawaban == 'y' || jawaban == 'Y') {
                    cout << "Status:\n"
                    << "1. Finished\n"
                    << "2. Not Yet\n";
                    int searchStatus;
                    cout << "Masukkan nomor status To Do yang dicari: ";
                    cin >> searchStatus;
                    clrscr();
                    binarySearch(tugas, jml, searchStatus);
                    break;
                } else {
                    ulang = false;
                }
                }
                break;
            case 6:
                clrscr();
                tampilkanToDo(tugas, jml);
                cout << "\n";
                hapusToDo(tugas, jml);
                clrscr();
                tampilkanToDo(tugas, jml);
                break;
            default:
                cout << "Pilihan tidak valid!!!\n";
                break;
        }
        ulang = ulangiMenu(); 
    } while (ulang);
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