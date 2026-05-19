#include<iostream>
#include<string>
using namespace std;

struct Expense {
  int id;
  string type;
  string category;
  double amount;
  string date;
};

const int Max = 500;
Expense records[Max];
int totalrecords = 0;

void displayMenu() {
    cout << "\n";
    cout << "  ================================\n";
    cout << "     Personal Finance Tracker\n";
    cout << "  ================================\n";
    cout << "  1. Add Expense\n";
    cout << "  2. Add Income\n";
    cout << "  3. View All Records\n";
    cout << "  4. View by Category\n";
    cout << "  5. Financial Summary\n";
    cout << "  6. Monthly Report\n";
    cout << "  7. Delete a Record\n";
    cout << "  8. Save & Exit\n";
    cout << "  ================================\n";
    cout << "  Choice: ";
}

int main(){
    displayMenu();
}