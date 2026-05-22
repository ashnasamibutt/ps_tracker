#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>

using namespace std;

string getDate();
bool   validateAmount(double a);
void   displayMenu();
string pickCategory(string type);
void   addRecord(string type);
void   viewAll();
void   viewByCategory();
void   summary();
void   monthlyReport();
void   deleteRecord();
void   saveData();
void   loadData();

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
            default: return "Other";
        }
    }
    return "Other";
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

void viewByCategory() {
    string cat = pickCategory("expense");
    double subtotal = 0;
    bool found = false;

    cout<<"\n Records For: "<<cat<<endl;
    cout<<" "<<string('-',65)<<endl;

    cout<<left
        <<setw(5)  <<"ID"
        <<setw(10) <<"Type"
        <<setw(15) <<"Amount"
        <<setw(10) <<"Date"
        <<"Note"<<endl;

    cout<<" "<<string('-',65)<<endl;

    for(int i = 0; i < totalrecords; i++) {
        if(records[i].category == cat) {
          cout<<" "<<left
        <<setw(5) << records[i].id
        <<setw(10) <<records[i].type
        <<setw(15) <<records[i].category
        <<setw(10) <<fixed <<setprecision(2) <<records[i].amount
        <<setw(15) <<records[i].date
        <<records[i].note <<"\n";

        subtotal += records[i].amount;
        found = true;
        }
    }

    if(!found) {
        cout<<"No records in this category"<<endl;
    }
    else {
        cout <<" " << string('-',65) << endl;
        cout << "Subtotal: Rs.  "<<fixed << setprecision(2) << subtotal << endl;
    }
 }

 void deleteRecord() {
     if(totalrecords == 0) {
        cout<<"No records to delete"<<endl;
        return;
     }

     viewAll();
     int id;
     cout<<"Enter ID to delete"<<endl;
     cin>>id;

     for(int i = 0; i < totalrecords; i++) {
        if(records[i].id == id) {
            for(int j = i; j < totalrecords-1; j++){
               records[j] = records[j+1];
            }
            totalrecords--;
            cout<<"Record deleted"<<endl;
            return;
        }
        cout<<"ID not found"<<endl;
     }
 }

 void monthlyReport() {
    string mm,yyyy;
    cout<<"Enter month (01-12): "<<mm<<endl;
    cout<<"Enter year(YYYY):  "<<yyyy<<endl;
    cin>> mm;
    cin>> yyyy;

    string filter = yyyy + '-' + mm;

    double income = 0;
    double expense = 0;
    bool found = false;

    cout << "\n Report for: "<< mm << "/" << yyyy << endl;

    cout<<" "<<string('-',65)<<endl;

    cout<<left
        <<setw(5)  <<"ID"
        <<setw(10) <<"Type"
        <<setw(15) <<"Amount"
        <<setw(10) <<"Date"
        <<"Note"<<endl;

    cout<<" "<<string('-',65)<<endl;

    for(int i = 0; i < totalrecords; i++) {
        if(records[i].date.substr(0,7) == filter) {
         cout<<" "<< left
        <<setw(5)  << records[i].id
        <<setw(10) <<records[i].type
        <<setw(15) <<records[i].category
        <<setw(10) <<fixed <<setprecision(2) <<records[i].amount
        <<setw(15) <<records[i].date
        <<records[i].note <<"\n";

        if(records[i].type == "income") 
            income += records[i].amount;
        else 
           expense += records[i].amount;
        found = true;
    }
  }

  if(!found) {
       cout<<"No records for this month"<<endl;
       return;
  }

  cout << "  " << string(60, '-') << "\n";
  cout << "  Income  : Rs. " << fixed << setprecision(2) << income << "\n";
  cout << "  Expense : Rs. " << fixed << setprecision(2) << expense << "\n";
  cout << "  Balance : Rs. " << fixed << setprecision(2) << income - expense << "\n";
}

void summary() {
   if(totalrecords = 0) {
      cout<<"No records found"<<endl;
      return;
   }

   double totalIncome = 0;
   double totalExpense = 0;

   for(int i = 0; i < totalrecords; i++) {
    if(records[i].type == "income")
        totalIncome += records[i].amount;
    else 
        totalExpense += records[i].amount;
   }

   double balance = totalIncome - totalExpense;
   double percentageUsed = (totalIncome > 0) ? (totalExpense/totalIncome) * 100 : 0;
   double percentageLeft = 100 - percentageUsed;
   double savings = (totalIncome > 0) ? (balance/totalIncome) * 100 : 0;

    cout << "\n";
    cout << "  ================================\n";
    cout << "       Financial Summary\n";
    cout << "  ================================\n";
    cout << "  Total Income   : Rs. " << fixed << setprecision(2) << totalIncome  << "\n";
    cout << "  Total Expenses : Rs. " << fixed << setprecision(2) << totalExpense << "\n";
    cout << "  Net Balance    : Rs. " << fixed << setprecision(2) << balance      << "\n";
    cout << "  --------------------------------\n";
    cout << "  Budget Used    : " << fixed << setprecision(1) << percentageUsed << "%\n";
    cout << "  Budget Left    : " << fixed << setprecision(1) << percentageLeft << "%\n";
    cout << "  Savings Rate   : " << fixed << setprecision(1) << savings << "%\n";
    cout << "  ================================\n";

    string cats[8] = {"Food","Rent","Transport","Utilities","Health","Entertainment","Shopping","Other"};

    cout << "\n  --- Expense Breakdown by Category ---\n";
     cout << "  " << left << setw(16) << "Category"
         << setw(14) << "Amount"
         << "% of Expenses\n";
    cout << "  " << string(45, '-') << "\n";

    for(int c = 0; c < 8; c++) {
        double catTotal = 0;
        for(int i = 0; i < totalrecords; i++) {
             if(records[i].type == "expense" && records[i].category == cats[c])
               catTotal += records[i].amount;
        }
        if(catTotal > 0) {
            double pct = (totalExpense > 0) ? (catTotal/totalExpense) * 100 : 0;
                cout << "  " << left
                << setw(16) << cats[c]
                << setw(14) << fixed << setprecision(2) << catTotal
                << fixed << setprecision(1) << pct << "%\n";
        }
    }
}

int main() {
    loadData();
     
    int choice;

    do {
      displayMenu();
      cin>>choice;

      switch(choice) {
        case 1: addRecord("expense"); break;
        case 2: addRecord("income"); break;
        case 3: viewAll(); break;
        case 4: viewByCategory(); break;
        case 5: summary(); break;
        case 6: monthlyReport(); break;
        case 7: deleteRecord(); break;
        case 8: saveData(); break;
        default: cout<<"Invalid choice. Try again "<<endl;
      }

    } while(choice != 8);

    return 0;
}