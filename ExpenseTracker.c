#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Structure for an Expense record
typedef struct {
    char date[11];
    char type[30];
    double amount;
} Expense;

// Structure for an Income record
typedef struct {
    char date[11];
    char source[30];
    double amount;
} Income;

// Maximum number of records
#define MAX_RECORDS 100

// Global arrays and counters for expenses and incomes
Expense expensesArray[MAX_RECORDS];
int expenseCount = 0;

Income incomeArray[MAX_RECORDS];
int incomeCount = 0;

// File paths
#define INCOME_FILE "income.dat"
#define EXPENSE_FILE "expense.dat"

// Function prototypes
void addIncomeArray();
void editIncomeArray();
void deleteIncomeArray();
void viewIncomesArray();
void viewTotalIncomeArray();

void addExpenseArray();
void editExpenseArray();
void deleteExpenseArray();
void viewExpensesArray();
void viewTotalArray();

void viewSummary();
void exportSummaryToCSV();

void saveDataToFile();
void loadDataFromFile();

// Income Functions
void addIncomeArray() {
    if (incomeCount >= MAX_RECORDS) {
        printf("Income list is full.\n");
        return;
    }
    Income newIncome;

    printf("Enter date (dd/mm/yyyy): ");
    scanf("%s", newIncome.date);
    printf("Enter source of income: ");
    scanf("%s", newIncome.source);
    do {
        printf("Enter amount: ");
        scanf("%lf", &newIncome.amount);
        if (newIncome.amount < 0) {
            printf("Amount cannot be negative.\n");
        }
    } while (newIncome.amount < 0);

    incomeArray[incomeCount++] = newIncome;
    printf("Income added successfully.\n");
}

void editIncomeArray() {
    viewIncomesArray();
    int index;
    printf("Enter the index of the income to edit: ");
    scanf("%d", &index);

    if (index < 1 || index > incomeCount) {
        printf("Invalid index.\n");
        return;
    }
    index--;

    Income *inc = &incomeArray[index];
    printf("Enter new date (dd/mm/yyyy): ");
    scanf("%s", inc->date);
    printf("Enter new source: ");
    scanf("%s", inc->source);

    do {
        printf("Enter new amount: ");
        scanf("%lf", &inc->amount);
        if (inc->amount < 0) {
            printf("Amount cannot be negative.\n");
        }
    } while (inc->amount < 0);

    printf("Income updated successfully.\n");
}

void deleteIncomeArray() {
    viewIncomesArray();
    int index;
    printf("Enter the index of the income to delete: ");
    scanf("%d", &index);

    if (index < 1 || index > incomeCount) {
        printf("Invalid index.\n");
        return;
    }
    index--;

    for (int i = index; i < incomeCount - 1; i++) {
        incomeArray[i] = incomeArray[i + 1];
    }
    incomeCount--;
    printf("Income deleted successfully.\n");
}

void viewIncomesArray() {
    if (incomeCount == 0) {
        printf("No incomes recorded.\n");
        return;
    }

    printf("%-5s %-15s %-15s %-10s\n", "No.", "Date", "Source", "Amount");
    for (int i = 0; i < incomeCount; i++) {
        printf("%-5d %-15s %-15s \u09F3%.2f\n", i + 1, incomeArray[i].date, incomeArray[i].source, incomeArray[i].amount);
    }
}

void viewTotalIncomeArray() {
    double total = 0;
    for (int i = 0; i < incomeCount; i++) {
        total += incomeArray[i].amount;
    }
    printf("Total Income: \u09F3%.2f\n", total);
}

// Expense Functions
void addExpenseArray() {
    if (expenseCount >= MAX_RECORDS) {
        printf("Expense list is full.\n");
        return;
    }
    Expense newExpense;

    printf("Enter date (dd/mm/yyyy): ");
    scanf("%s", newExpense.date);
    printf("Enter type of expense: ");
    scanf("%s", newExpense.type);
    do {
        printf("Enter amount: ");
        scanf("%lf", &newExpense.amount);
        if (newExpense.amount < 0) {
            printf("Amount cannot be negative.\n");
        }
    } while (newExpense.amount < 0);

    expensesArray[expenseCount++] = newExpense;
    printf("Expense added successfully.\n");
}

void editExpenseArray() {
    if (expenseCount == 0) {
        printf("No expenses recorded.\n");
        return;
    }

    viewExpensesArray();
    int index;

    // Get the index to edit
    printf("Enter the index of the expense to edit: ");
    scanf("%d", &index);

    if (index < 1 || index > expenseCount) {
        printf("Invalid index.\n");
        return;
    }
    index--; // Convert to zero-based index

    Expense *exp = &expensesArray[index];

    // Clear the input buffer
    while (getchar() != '\n');

    // Update the date
    printf("Enter new date (dd/mm/yyyy) (current: %s): ", exp->date);
    fgets(exp->date, sizeof(exp->date), stdin);
    exp->date[strcspn(exp->date, "\n")] = 0; // Remove newline character

    // Update the type
    printf("Enter new type of expense (current: %s): ", exp->type);
    fgets(exp->type, sizeof(exp->type), stdin);
    exp->type[strcspn(exp->type, "\n")] = 0; // Remove newline character

    // Update the amount
    do {
        printf("Enter new amount (current: %.2f): ", exp->amount);
        scanf("%lf", &exp->amount);
        if (exp->amount < 0) {
            printf("Amount cannot be negative.\n");
        }
    } while (exp->amount < 0);

    printf("Expense updated successfully.\n");
}


void deleteExpenseArray() {
    viewExpensesArray();
    int index;
    printf("Enter the index of the expense to delete: ");
    scanf("%d", &index);

    if (index < 1 || index > expenseCount) {
        printf("Invalid index.\n");
        return;
    }
    index--;

    for (int i = index; i < expenseCount - 1; i++) {
        expensesArray[i] = expensesArray[i + 1];
    }
    expenseCount--;
    printf("Expense deleted successfully.\n");
}

void viewExpensesArray() {
    if (expenseCount == 0) {
        printf("No expenses recorded.\n");
        return;
    }

    printf("%-5s %-15s %-15s %-10s\n", "No.", "Date", "Type", "Amount");
    for (int i = 0; i < expenseCount; i++) {
        printf("%-5d %-15s %-15s \u09F3%.2f\n", i + 1, expensesArray[i].date, expensesArray[i].type, expensesArray[i].amount);
    }
}

void viewTotalArray() {
    double total = 0;
    for (int i = 0; i < expenseCount; i++) {
        total += expensesArray[i].amount;
    }
    printf("Total Expense: \u09F3%.2f\n", total);
}

// View Summary
void viewSummary() {
    double totalIncome = 0, totalExpense = 0;

    for (int i = 0; i < incomeCount; i++) {
        totalIncome += incomeArray[i].amount;
    }

    for (int i = 0; i < expenseCount; i++) {
        totalExpense += expensesArray[i].amount;
    }

    printf("\n======== Summary ========\n");
    printf("Total Income:       \u09F3%.2f\n", totalIncome);
    printf("Total Expenses:     \u09F3%.2f\n", totalExpense);
    printf("Net Savings:        \u09F3%.2f\n", totalIncome - totalExpense);
    printf("========================\n");
}

void exportSummaryToCSV() {
    if (incomeCount == 0 && expenseCount == 0) {
        printf("No income or expense records available to export.\n");
        return;
    }

    FILE *file = fopen("summary.csv", "w");
    if (file == NULL) {
        printf("Unable to create CSV file.\n");
        return;
    }

    fprintf(file, "Type,Date,Description,Amount\n");

    double totalIncome = 0, totalExpense = 0;

    // Write income records
    for (int i = 0; i < incomeCount; i++) {
        fprintf(file, "Income,%s,%s,%.2f\n", incomeArray[i].date, incomeArray[i].source, incomeArray[i].amount);
        totalIncome += incomeArray[i].amount;
    }

    // Write expense records
    for (int i = 0; i < expenseCount; i++) {
        fprintf(file, "Expense,%s,%s,%.2f\n", expensesArray[i].date, expensesArray[i].type, expensesArray[i].amount);
        totalExpense += expensesArray[i].amount;
    }

    // Add summary rows
    double netSavings = totalIncome - totalExpense;
    fprintf(file, "\nTotal Income,,,%.2f\n", totalIncome);
    fprintf(file, "Total Expense,,,%.2f\n", totalExpense);
    fprintf(file, "Total Savings or Loss,,,(%s) %.2f\n", netSavings >= 0 ? "Savings" : "Loss" , fabs(netSavings));

    fclose(file);
    printf("Detailed records exported to 'summary.csv' with Total Savings or Loss.\n");
}

// Save data to files
void saveDataToFile() {
    FILE *incomeFile = fopen(INCOME_FILE, "wb");
    FILE *expenseFile = fopen(EXPENSE_FILE, "wb");

    if (incomeFile == NULL || expenseFile == NULL) {
        printf("Error saving data.\n");
        return;
    }

    fwrite(&incomeCount, sizeof(int), 1, incomeFile);
    fwrite(incomeArray, sizeof(Income), incomeCount, incomeFile);

    fwrite(&expenseCount, sizeof(int), 1, expenseFile);
    fwrite(expensesArray, sizeof(Expense), expenseCount, expenseFile);

    fclose(incomeFile);
    fclose(expenseFile);

    printf("Data saved successfully.\n");
}

// Load data from files
void loadDataFromFile() {
    FILE *incomeFile = fopen(INCOME_FILE, "rb");
    FILE *expenseFile = fopen(EXPENSE_FILE, "rb");

    if (incomeFile != NULL) {
        fread(&incomeCount, sizeof(int), 1, incomeFile);
        fread(incomeArray, sizeof(Income), incomeCount, incomeFile);
        fclose(incomeFile);
    }

    if (expenseFile != NULL) {
        fread(&expenseCount, sizeof(int), 1, expenseFile);
        fread(expensesArray, sizeof(Expense), expenseCount, expenseFile);
        fclose(expenseFile);
    }

    printf("Data loaded successfully.\n");
}

// Main Function
int main() {
    loadDataFromFile();
    int choice;
    while (1) {
        printf("\n1. Add Income\n2. Edit Income\n3. Delete Income\n4. View Incomes\n5. View Total Income\n");
        printf("6. Add Expense\n7. Edit Expense\n8. Delete Expense\n9. View Expenses\n10. View Total Expenses\n");
        printf("11. View Summary\n12. Export Summary to CSV\n13. Save Data\n14. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addIncomeArray(); break;
            case 2: editIncomeArray(); break;
            case 3: deleteIncomeArray(); break;
            case 4: viewIncomesArray(); break;
            case 5: viewTotalIncomeArray(); break;
            case 6: addExpenseArray(); break;
            case 7: editExpenseArray(); break;
            case 8: deleteExpenseArray(); break;
            case 9: viewExpensesArray(); break;
            case 10: viewTotalArray(); break;
            case 11: viewSummary(); break;
            case 12: exportSummaryToCSV(); break;
            case 13: saveDataToFile(); break;
            case 14: saveDataToFile(); exit(0);
            default: printf("Invalid option.\n");
        }
    }
}
