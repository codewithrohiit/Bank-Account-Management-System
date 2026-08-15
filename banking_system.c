#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for storing bank account details
struct Account
{
    int accountNumber;
    char name[50];
    float balance;
};

// Function declarations
void createAccount();
void deposit();
void withdrawMoney();
void balanceEnquiry();


int main()
{
    int choice;

    while (1)
    {
        printf("\n\n====================================\n");
        printf("     BANK ACCOUNT MANAGEMENT SYSTEM\n");
        printf("====================================\n");

        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Balance Enquiry\n");
        printf("5. Exit\n");

        printf("\nEnter your choice: ");
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
                printf("\nThank you for using our Banking System!\n");
                exit(0);

            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}


// Function to create a new account
void createAccount()
{
    struct Account account;
    FILE *fp;

    // Open file in append binary mode
    fp = fopen("accounts.dat", "ab");

    if (fp == NULL)
    {
        printf("\nError opening file!\n");
        return;
    }

    printf("\nENTER DETAILS FOR CREATING YOUR ACCOUNT\n ");

    printf("Enter Account Number: ");
    scanf("%d", &account.accountNumber);

    // Clear input buffer
    getchar();

    printf("Enter Account Holder Name: ");
    fgets(account.name, sizeof(account.name), stdin);

    // Remove newline from name
    account.name[strcspn(account.name, "\n")] = '\0';

    printf("Enter Initial Deposit: ");
    scanf("%f", &account.balance);

    if (account.balance < 0)
    {
        printf("\nInitial deposit cannot be negative!\n");
        fclose(fp);
        return;
    }

    // Write account data into file
    fwrite(&account, sizeof(account), 1, fp);

    fclose(fp);

    printf("\nAccount created successfully!\n");
    printf("Account Number: %d\n", account.accountNumber);
    printf("Account Holder: %s\n", account.name);
    printf("Balance: %.2f\n", account.balance);
}


// Function to deposit money
void deposit()
{
    struct Account account;
    FILE *fp;
    int accountNumber;
    float amount;
    int found = 0;

    fp = fopen("accounts.dat", "rb+");

    if (fp == NULL)
    {
        printf("\nNo account file found!\n");
        return;
    }

    printf("\n========== DEPOSIT MONEY ==========\n");

    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);

    // Read accounts one by one
    while (fread(&account, sizeof(account), 1, fp) == 1)
    {
        if (account.accountNumber == accountNumber)
        {
            found = 1;

            printf("Account Holder: %s\n", account.name);
            printf("Current Balance: %.2f\n", account.balance);

            printf("Enter amount to deposit: ");
            scanf("%f", &amount);

            if (amount <= 0)
            {
                printf("\nInvalid deposit amount!\n");
                fclose(fp);
                return;
            }

            account.balance = account.balance + amount;

            // Move file pointer back to beginning of current record
            fseek(fp, -sizeof(account), SEEK_CUR);

            // Write updated record
            fwrite(&account, sizeof(account), 1, fp);

            printf("\nDeposit successful!\n");
            printf("New Balance: %.2f\n", account.balance);

            break;
        }
    }

    if (found == 0)
    {
        printf("\nAccount not found!\n");
    }

    fclose(fp);
}


// Function to withdraw money
void withdrawMoney()
{
    struct Account account;
    FILE *fp;
    int accountNumber;
    float amount;
    int found = 0;

    fp = fopen("accounts.dat", "rb+");

    if (fp == NULL)
    {
        printf("\nNo account file found!\n");
        return;
    }

    printf("\n========== WITHDRAW MONEY ==========\n");

    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);

    while (fread(&account, sizeof(account), 1, fp) == 1)
    {
        if (account.accountNumber == accountNumber)
        {
            found = 1;

            printf("Account Holder: %s\n", account.name);
            printf("Current Balance: %.2f\n", account.balance);

            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);

            if (amount <= 0)
            {
                printf("\nInvalid withdrawal amount!\n");
                fclose(fp);
                return;
            }

            if (amount > account.balance)
            {
                printf("\nInsufficient balance!\n");
            }
            else
            {
                account.balance = account.balance - amount;

                // Move file pointer back to current record
                fseek(fp, -sizeof(account), SEEK_CUR);

                // Save updated account
                fwrite(&account, sizeof(account), 1, fp);

                printf("\nWithdrawal successful!\n");
                printf("Remaining Balance: %.2f\n", account.balance);
            }

            break;
        }
    }

    if (found == 0)
    {
        printf("\nAccount not found!\n");
    }

    fclose(fp);
}


// Function to display balance
void balanceEnquiry()
{
    struct Account account;
    FILE *fp;
    int accountNumber;
    int found = 0;

    fp = fopen("accounts.dat", "rb");

    if (fp == NULL)
    {
        printf("\nNo account file found!\n");
        return;
    }

    printf("\n========== BALANCE ENQUIRY ==========\n");

    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);

    while (fread(&account, sizeof(account), 1, fp) == 1)
    {
        if (account.accountNumber == accountNumber)
        {
            found = 1;

            printf("\nAccount Details\n");
            printf("Account Number : %d\n", account.accountNumber);
            printf("Account Holder : %s\n", account.name);
            printf("Balance        : %.2f\n", account.balance);

            break;
        }
    }

    if (found == 0)
    {
        printf("\nAccount not found!\n");
    }

    fclose(fp);
}