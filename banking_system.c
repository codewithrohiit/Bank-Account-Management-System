#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account
{
    int accountNumber;
    char name[50];
    float balance;
};

void createAccount();
void deposit();
void withdrawMoney();
void balanceEnquiry();

int main()
{
    int choice;

    while (1)
    {
        printf("\n==============================\n");
        printf(" BANK ACCOUNT MANAGEMENT SYSTEM\n");
        printf("==============================\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Balance Enquiry\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                createAccount();
                break;

            case 2:
                deposit();
                break;

            case 3:
                withdrawMoney();
                break;

            case 4:
                balanceEnquiry();
                break;

            case 5:
                printf("Thank you!\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

void createAccount()
{
    struct Account a;
    FILE *fp;

    fp = fopen("accounts.dat", "ab");

    if (fp == NULL)
    {
        printf("File could not be opened.\n");
        return;
    }

    printf("\n--- Create Account ---\n");

    printf("Enter account number: ");
    scanf("%d", &a.accountNumber);

    getchar();

    printf("Enter account holder name: ");
    fgets(a.name, sizeof(a.name), stdin);

    a.name[strcspn(a.name, "\n")] = '\0';

    printf("Enter initial deposit: ");
    scanf("%f", &a.balance);

    if (a.balance < 0)
    {
        printf("Balance cannot be negative.\n");
        fclose(fp);
        return;
    }

    fwrite(&a, sizeof(a), 1, fp);

    fclose(fp);

    printf("\nAccount created successfully.\n");
}

void deposit()
{
    struct Account a;
    FILE *fp;
    int number;
    float amount;
    int found = 0;

    fp = fopen("accounts.dat", "rb+");

    if (fp == NULL)
    {
        printf("No accounts found.\n");
        return;
    }

    printf("\n--- Deposit Money ---\n");

    printf("Enter account number: ");
    scanf("%d", &number);

    while (fread(&a, sizeof(a), 1, fp) == 1)
    {
        if (a.accountNumber == number)
        {
            found = 1;

            printf("Account holder: %s\n", a.name);
            printf("Current balance: %.2f\n", a.balance);

            printf("Enter amount: ");
            scanf("%f", &amount);

            if (amount <= 0)
            {
                printf("Invalid amount.\n");
                fclose(fp);
                return;
            }

            a.balance += amount;

            fseek(fp, -sizeof(a), SEEK_CUR);
            fwrite(&a, sizeof(a), 1, fp);

            printf("Deposit successful.\n");
            printf("New balance: %.2f\n", a.balance);

            break;
        }
    }

    if (found == 0)
    {
        printf("Account not found.\n");
    }

    fclose(fp);
}

void withdrawMoney()
{
    struct Account a;
    FILE *fp;
    int number;
    float amount;
    int found = 0;

    fp = fopen("accounts.dat", "rb+");

    if (fp == NULL)
    {
        printf("No accounts found.\n");
        return;
    }

    printf("\n--- Withdraw Money ---\n");

    printf("Enter account number: ");
    scanf("%d", &number);

    while (fread(&a, sizeof(a), 1, fp) == 1)
    {
        if (a.accountNumber == number)
        {
            found = 1;

            printf("Account holder: %s\n", a.name);
            printf("Current balance: %.2f\n", a.balance);

            printf("Enter amount: ");
            scanf("%f", &amount);

            if (amount <= 0)
            {
                printf("Invalid amount.\n");
                fclose(fp);
                return;
            }

            if (amount > a.balance)
            {
                printf("Insufficient balance.\n");
            }
            else
            {
                a.balance -= amount;

                fseek(fp, -sizeof(a), SEEK_CUR);
                fwrite(&a, sizeof(a), 1, fp);

                printf("Withdrawal successful.\n");
                printf("Remaining balance: %.2f\n", a.balance);
            }

            break;
        }
    }

    if (found == 0)
    {
        printf("Account not found.\n");
    }

    fclose(fp);
}

void balanceEnquiry()
{
    struct Account a;
    FILE *fp;
    int number;
    int found = 0;

    fp = fopen("accounts.dat", "rb");

    if (fp == NULL)
    {
        printf("No accounts found.\n");
        return;
    }

    printf("\n--- Balance Enquiry ---\n");

    printf("Enter account number: ");
    scanf("%d", &number);

    while (fread(&a, sizeof(a), 1, fp) == 1)
    {
        if (a.accountNumber == number)
        {
            found = 1;

            printf("\nAccount Number : %d\n", a.accountNumber);
            printf("Account Holder : %s\n", a.name);
            printf("Balance        : %.2f\n", a.balance);

            break;
        }
    }

    if (found == 0)
    {
        printf("Account not found.\n");
    }

    fclose(fp);
}