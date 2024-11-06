#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;
class account{
	int acno;
	char name[50];
	float deposit;
	char type;
public:
	void create_account();
	void show_account() const;
	void modify();
	void dep(int);
	void draw(int);
	void report() const;
	int retacno() const;
	int retdeposit() const;
	char rettype() const;
};
void account::create_account(){
	cout << "\n\t\t\tEnter the account no. : (Account no. must be 4 (or less) digits long): ";
	cin >> acno;
	cin.ignore();
	cout << "\n\n\t\t\tPlease enter the name of the account holder here : ";
	cin.getline(name, 50);
	do{
		cout << "\n\t\t\tEnter type of the account (C/S): ";
		cin >> type;
		type = toupper(type);
		if (type != 'C' && type != 'S'){
			cout << "\n\t\t\tInvalid type! Please enter 'C' for Current or 'S' for Savings.\n";
		}
	} while (type != 'C' && type != 'S');
	do {
		cout << "\n\t\t\tEnter the initial amount (must be positive): ";
		cin >> deposit;
		if (deposit <= 0) {
			cout << "\n\t\t\tInvalid amount! Please enter a positive amount.\n";
		}
	} while (deposit <= 0);
	cout << "\n\n\t\t\tAccount created..";
}
void account::show_account() const{
	cout << "\n\t\t\tAccount no. : " << acno;
	cout << "\n\t\t\tAccount holder name : ";
	cout << name;
	cout << "\n\t\t\tType of account : " << type;
	cout << "\n\t\t\tBalance amount : " << deposit;
}
void account::modify() {
    int choice;
    cout << "\n\t\t\tAccount No. : " << acno;
    cout << "\n\t\t\tWhat do you want to modify?\n";
    cout << "\t\t\t\t1. Account Holder Name\n";
    cout << "\t\t\t\t2. Account Type\n";
    cout << "\t\t\t\t3. Balance Amount\n";
    cout << "\n\t\t\tEnter your choice (1-3): ";
    cin >> choice;
    cin.ignore();
    switch(choice) {
        case 1:
            cout << "\n\t\t\tModify account holder name : ";
            cin.getline(name, 50);
            break;
        case 2:
            do {
                cout << "\n\t\t\tModify type of account (C/S): ";
                cin >> type;
                type = toupper(type);
                if (type != 'C' && type != 'S') {
                    cout << "\n\t\t\tInvalid type! Please enter 'C' for Current or 'S' for Savings.\n";
                }
            } while (type != 'C' && type != 'S');
            break;
        case 3:
            cout << "\n\t\t\tModify balance amount : ";
            cin >> deposit;
            while (deposit <= 0) {
                cout << "\n\t\t\tInvalid amount! Please enter a positive amount: ";
                cin >> deposit;
            }
            break;
        default:
            cout << "\n\t\t\tInvalid choice! No modifications made.";
            break;
    }
    cout << "\n\t\t\tAccount details updated.";
}
void account::dep(int x){
	deposit += x;
}
void account::draw(int x){
	deposit -= x;
}
void account::report() const{
	cout << acno << setw(10) << "\t" << name << setw(10) << "\t" << type << setw(6) << "\t" << deposit << endl;
}
int account::retacno() const{
	return acno;
}
int account::retdeposit() const{
	return deposit;
}
char account::rettype() const{
	return type;
}
void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);
int main(){
	char ch;
	int num;
	do{
		system("CLS");
		cout << "\n\n\t\t\t\t======================\n";
		cout << "\t\t\t\tBANK MANAGEMENT SYSTEM";
		cout << "\n\t\t\t\t======================\n";

		cout << "\t\t\t\t    ::MAIN MENU::\n";
		cout << "\n\t\t\t\t1. NEW ACCOUNT";
		cout << "\n\t\t\t\t2. DEPOSIT AMOUNT";
		cout << "\n\t\t\t\t3. WITHDRAW AMOUNT";
		cout << "\n\t\t\t\t4. BALANCE ENQUIRY";
		cout << "\n\t\t\t\t5. ALL ACCOUNT HOLDER LIST";
		cout << "\n\t\t\t\t6. CLOSE AN ACCOUNT";
		cout << "\n\t\t\t\t7. MODIFY AN ACCOUNT";
		cout << "\n\t\t\t\t8. EXIT";
		cout << "\n\n\t\t\t\tSelect Your Option (1-8): ";
		cin >> ch;

		switch (ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			system("CLS");
			cout << "\n\n\t\t\tEnter the account no. : "; cin >> num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			system("CLS");
			cout << "\n\n\t\t\tEnter the account no. : "; cin >> num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			system("CLS");
			cout << "\n\n\t\t\tEnter The account no. : "; cin >> num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			system("CLS");
			cout << "\n\n\t\t\tEnter the account no. : "; cin >> num;
			delete_account(num);
			break;
		case '7':
			system("CLS");
			cout << "\n\n\t\t\tEnter the account no. : "; cin >> num;
			modify_account(num);
			break;
		case '8':
			system("CLS");
			cout << "\n\n\t\tThank you for using our Banking System!!";
			break;
		default:cout << "\a";
		}
		cin.ignore();
		cin.get();
	} while (ch != '8');
	return 0;
}
void write_account(){
	account ac;
	ofstream outFile;
	outFile.open("account.dat", ios::binary | ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
	outFile.close();
}
void display_sp(int n){
	account ac;
	bool flag = false;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile){
		cout << "Error opening the file!! Press any key to continue...";
		return;
	}
	cout << "\n\t\t\tBALANCE DETAILS\n";
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account))){
		if (ac.retacno() == n){
			ac.show_account();
			flag = true;
		}
	}
	inFile.close();
	if (flag == false) cout << "\n\n\t\t\tAccount number does not exist.";
}
void modify_account(int n){
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File){
		cout << "Error opening the file!! Press any key to continue...";
		return;
	}
	while (!File.eof() && !found){
		File.read(reinterpret_cast<char*>(&ac), sizeof(account));
		if (ac.retacno() == n){
			ac.show_account();
			cout << "\n\n\t\t\tEnter the new details of account" << endl;
			cin.ignore();
			ac.modify();
			int pos = (-1) * static_cast<int>(sizeof(account));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*>(&ac), sizeof(account));
			cout << "\n\n\t\t\tRecord Updated";
			found = true;
		}
	}
	File.close();
	if (!found) cout << "\n\n\t\t\tRecord Not Found ";
}
void delete_account(int n){
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile){
		cout << "Error opening file!! Press any key to continue...";
		return;
	}
	outFile.open("Temp.dat", ios::binary);
	inFile.seekg(0, ios::beg);
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account))){
		if (ac.retacno() != n){
			outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat", "account.dat");
	cout << "\n\n\t\tRecord Deleted ..";
}
void display_all(){
	system("CLS");
	account ac;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile){
		cout << "\n\n\t\tError opening the file!! Press any key to continue...";
		return;
	}
	cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout << "====================================================\n";
	cout << "A/c no.      NAME           Type  Balance\n";
	cout << "====================================================\n";
	while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(account))) {
        ac.report();
        }
	inFile.close();
}
void deposit_withdraw(int n, int option){
	int amt;
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File){
		cout << "Error opening the file!! Press any key to continue...";
		return;
	}
	while (!File.eof() && found == false){
		File.read(reinterpret_cast<char*> (&ac), sizeof(account));
		if (ac.retacno() == n){
			ac.show_account();
			if (option == 1){
				cout << "\n\n\t\t\tTO DEPOSIT AMOUNT";
				cout << "\n\n\t\t\tEnter the amount to be deposited: ";
				cin >> amt;
				ac.dep(amt);
			}
			if (option == 2){
				cout << "\n\n\t\t\tTO WITHDRAW AMOUNT";
				cout << "\n\n\t\t\tEnter the amount to be withdraw: ";
				cin >> amt;
				int bal = ac.retdeposit() - amt;
				if (bal < 0) cout << "Insufficienct balance";
				else ac.draw(amt);
			}
			int pos = (-1) * static_cast<int>(sizeof(ac));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(account));
			cout << "\n\n\t\t\tRecord Updated";
			found = true;
		}
	}
	File.close();
	if (found == false) cout << "\n\n\t\t\tRecord Not Found ";
}
