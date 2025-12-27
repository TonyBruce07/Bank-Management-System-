#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BankAccount {
    int acc_no;
    char name[50];
    float balance;
};

void addAccount();
void viewAccounts();
void searchAccount();
void depositMoney();
void withdrawMoney();

int main() {
    int choice;

    while(1) {
        printf("\n====== BANK MANAGEMENT SYSTEM ======\n");
        printf("1. Add New Account\n");
        printf("2. View All Accounts\n");
        printf("3. Search Account\n");
        printf("4. Deposit Money\n");
        printf("5. Withdraw Money\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addAccount(); break;
            case 2: viewAccounts(); break;
            case 3: searchAccount(); break;
            case 4: depositMoney(); break;
            case 5: withdrawMoney(); break;
            case 6: exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }
}

void addAccount() {
    FILE *fp = fopen("bank_records.txt", "a");
    struct BankAccount acc;

    printf("\nEnter Account Number: ");
    scanf("%d", &acc.acc_no);
    printf("Enter Name: ");
    scanf("%s", acc.name);
    printf("Enter Initial Balance: ");
    scanf("%f", &acc.balance);

    fprintf(fp, "%d %s %.2f\n", acc.acc_no, acc.name, acc.balance);
    fclose(fp);

    printf("Account added successfully!\n");
}

void viewAccounts() {
    FILE *fp = fopen("bank_records.txt", "r");
    struct BankAccount acc;

    printf("\n--- All Accounts ---\n");
    while(fscanf(fp, "%d %s %f", &acc.acc_no, acc.name, &acc.balance) != EOF) {
        printf("Acc No: %d | Name: %s | Balance: %.2f\n", acc.acc_no, acc.name, acc.balance);
    }
    fclose(fp);
}

void searchAccount() {
    FILE *fp = fopen("bank_records.txt", "r");
    struct BankAccount acc;
    int search_no, found = 0;

    printf("\nEnter account number to search: ");
    scanf("%d", &search_no);

    while(fscanf(fp, "%d %s %f", &acc.acc_no, acc.name, &acc.balance) != EOF) {
        if(acc.acc_no == search_no) {
            printf("\nAccount Found!\n");
            printf("Acc No: %d | Name: %s | Balance: %.2f\n", acc.acc_no, acc.name, acc.balance);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if(!found)
        printf("Account not found!\n");
}

void depositMoney() {
    FILE *fp = fopen("bank_records.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct BankAccount acc;
    int acc_no;
    float amount;
    int found = 0;

    printf("\nEnter account number: ");
    scanf("%d", &acc_no);
    printf("Enter deposit amount: ");
    scanf("%f", &amount);

    while(fscanf(fp, "%d %s %f", &acc.acc_no, acc.name, &acc.balance) != EOF) {
        if(acc.acc_no == acc_no) {
            acc.balance += amount;
            found = 1;
        }
        fprintf(temp, "%d %s %.2f\n", acc.acc_no, acc.name, acc.balance);
    }

    fclose(fp);
    fclose(temp);
    remove("bank_records.txt");
    rename("temp.txt", "bank_records.txt");

    if(found) printf("Amount deposited successfully!\n");
    else printf("Account not found!\n");
}

void withdrawMoney() {
    FILE *fp = fopen("bank_records.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct BankAccount acc;
    int acc_no;
    float amount;
    int found = 0;

    printf("\nEnter account number: ");
    scanf("%d", &acc_no);
    printf("Enter withdrawal amount: ");
    scanf("%f", &amount);

    while(fscanf(fp, "%d %s %f", &acc.acc_no, acc.name, &acc.balance) != EOF) {
        if(acc.acc_no == acc_no) {
            if(acc.balance >= amount) {
                acc.balance -= amount;
                found = 1;
            } else {
                printf("Insufficient balance!\n");
            }
        }
        fprintf(temp, "%d %s %.2f\n", acc.acc_no, acc.name, acc.balance);
    }

    fclose(fp);
    fclose(temp);
    remove("bank_records.txt");
    rename("temp.txt", "bank_records.txt");

    if(found) printf("Amount withdrawn successfully!\n");
    else printf("Account not found!\n");
}
