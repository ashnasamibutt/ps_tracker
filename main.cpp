#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>

using namespace std;

struct Expense {
    int id;
    string type;
    string category;
    double amount;
    string date;
    string note;
};

const int Max = 500;
Expense records[Max];
int totalrecords = 0;
const string FILE_NAME = "data.txt";

void displayMenu() {
    cout<<"\n";
    cout <<" =========================\n ";
    cout<<"Personal Finance Tracker\n";
    cout <<" =========================\n ";
    cout<<"Add expense\n";
    cout<<"Add income\n";
    cout<<"View all records\n";
    cout<<"View by category\n";
    cout<<"Financial Summary\n";
    cout<<"Monthly report\n";
    cout<<"Delete a record\n";
    cout<<"Save and Exit\n";
    cout <<" =========================\n ";
    cout<<"Choice: ";
}

string getDate() {
    string date;
    cout<<"Enter Date: (YYYY-MM-DD) ";
    cin>>date;
    return date;
}

bool validateAmount(double a) {
    if (a <= 0) {
        cout<<"Invalid! Add amount greater than Zero\n";
        return false;
    }
    else 
    return true;
}

string pickCategory(string type) {
    int category;
    if(type == "expense") {
        cout<<" \n Expense Categories \n ";
        cout<<" 1.Food\n";
        cout<<" 2.Rent\n";
        cout<<" 3.Transport\n";
        cout<<" 4.Utilities\n";
        cout<<" 5.Health\n";
        cout<<" 6.Entertainment\n";
        cout<<" 7.Shopping\n";
        cout<<" 8.Other\n";
        cout<<"Choice: ";
        cin>>category;

        switch (category) {
            case 1: return "Food";
            case 2: return "Rent";
            case 3: return "Transport";
            case 4: return "Utilities";
            case 5: return "Health";
            case 6: return "Entertainment";
            case 7: return "Shopping";
            deafault: return "Other";
        }
    }
    else {
        cout<<"\n Income Categories \n ";
        cout<<"1. Salary\n";
        cout<<"2. Freelance\n";
        cout<<"3. Business\n";
        cout<<"4. Gift\n";
        cout<<"5. Other\n";
        cout<<"Choice: ";
        cin>>category;

        switch (category) {
            case 1: return "Salary";
            case 2: return "Freelance";
            case 3: return "Business";
            case 4: return "Gift";
            deafault: return "Other";
        }
    }
}

void addRecord(string type) {
    if(totalrecords >= Max) {
        cout<<"Storsge Full\n";
        return;
    }

    Expense e;

    e.id = totalrecords + 1;
    e.type = type;

    e.category = pickCategory(type);
    e.date = getDate();

    cout<<"Enter Amount: ";
    cin>>e.amount;
    if(!validateAmount(e.amount)) {
        cout<<"Record not added. Try again.\n";
        return;
    }

    cout<<" Note: ";
    cin.ignore();
    getline(cin,e.note);

    records[totalrecords] = e;
    totalrecords++;
}

void viewAll() {
    if(totalrecords == 0) {
        cout<<"No records found.\n";
        return;
    }

    cout<<"\n";
    cout<<" "<<left 
        <<setw(5)<<"ID"
        <<setw(10)<<"Type"
        <<setw(15)<<"Category"
        <<setw(10)<<"Amount"
        <<setw(15)<<"Date"
        <<"Note"<<"\n";
    cout<<" "<<string(65,'-')<<"\n";

    for(int i = 0; i < totalrecords; i++) {
        cout<<" "<<left
        <<setw(5) << records[i].id
        <<setw(10) <<records[i].type
        <<setw(15) <<records[i].category
        <<setw(10) <<fixed <<setprecision(2) <<records[i].amount
        <<setw(15) <<records[i].date
        <<records[i].note <<"\n";
    }
}

void saveData() {
    ofstream file(FILE_NAME);

    if(!file) {
        cout<<"Couldn't open file\n";
        return;
    }

    for(int i = 0; i < totalrecords; i++) {
        file << records[i].id  <<"|"
             << records[i].type <<"|"
             <<records[i].category <<"|"
             << fixed << setprecision(2) << records[i].amount << "|"
             <<records[i].date <<"|"
             <<records[i].note <<"\n";
    }

    file.close();
    cout<<"Data saved successfully.\n";
}

void loadData() {
    ifstream file(FILE_NAME);
    if(!file) return;

    while(totalrecords < Max) {
        string idStr,amountStr;

        if(!getline(file,idStr,'|'))  break;
        if(!getline(file,records[totalrecords].type,'|'))  break;
        if(!getline(file,records[totalrecords].category,'|'))  break;
        if(!getline(file,amountStr,'|'))  break;
        if(!getline(file,records[totalrecords].date,'|'))  break;
        if(!getline(file,records[totalrecords].note )) break;

        records[totalrecords].id = stoi(idStr);
        records[totalrecords].amount = stod(amountStr);

        totalrecords++;
    }

    file.close();
    cout<<totalrecords<<"Records loaded successfully.\n";
}

