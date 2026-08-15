# 🏦 Bank Account Management System

A simple **Bank Account Management System written in C** that allows users to create bank accounts, deposit money, withdraw money, and check account balances.

The project uses **Structures and File Handling** to store account information permanently in a binary file.

## 📌 Features

- Create a new bank account
- Store account number, account holder name, and balance
- Deposit money into an account
- Withdraw money from an account
- Check account balance
- Permanent data storage using file handling
- Menu-driven console interface
- Input validation for deposits and withdrawals

## 🛠️ Technologies Used

- **C Programming**
- **Structures**
- **File Handling**
- **Binary Files**
- **Pointers**
- **Functions**
- **Standard C Libraries**

## 📂 Project Structure

```text
Bank-Account-Management-System/
│
├── bank.c
├── accounts.dat
└── README.md
```

> `accounts.dat` is automatically created by the program when the first account is created.

## ⚙️ How It Works

The program provides the following menu:

```text
====================================
     BANK ACCOUNT MANAGEMENT SYSTEM
====================================

1. Create Account
2. Deposit Money
3. Withdraw Money
4. Balance Enquiry
5. Exit
```

### 1. Create Account

The user enters:

- Account Number
- Account Holder Name
- Initial Deposit

The account information is stored permanently in `accounts.dat`.

### 2. Deposit Money

The user enters an account number and the amount to deposit.

The program searches for the account and updates its balance.

### 3. Withdraw Money

The user enters an account number and withdrawal amount.

The program checks whether sufficient balance is available before performing the withdrawal.

### 4. Balance Enquiry

The user enters an account number and the program displays:

```text
Account Number
Account Holder
Balance
```

## 💾 File Handling

The program uses a binary file named:

```text
accounts.dat
```

Different file modes are used for different operations:

| Mode | Purpose |
|------|---------|
| `ab` | Create/add a new account |
| `rb+` | Read and update existing accounts |
| `rb` | Read account information |

Account records are stored using:

```c
fwrite()
```

and retrieved using:

```c
fread()
```

## 🧱 Structure Used

The program uses the following structure:

```c
struct Account
{
    int accountNumber;
    char name[50];
    float balance;
};
```

Each account contains:

- Account Number
- Account Holder Name
- Account Balance

## ▶️ How to Run

### Using GCC

Compile the program:

```bash
gcc bank.c -o bank
```

Run the program:

### Windows

```bash
bank.exe
```

### Linux / macOS

```bash
./bank
```

## 📋 Example

```text
========== CREATE ACCOUNT ==========

Enter Account Number: 1001
Enter Account Holder Name: Rohit Mishra
Enter Initial Deposit: 5000

Account created successfully!

Account Number: 1001
Account Holder: Rohit Mishra
Balance: 5000.00
```

After depositing ₹2000:

```text
Deposit successful!
New Balance: 7000.00
```

## 🎯 Concepts Demonstrated

This project demonstrates practical implementation of:

- `struct`
- Functions
- Pointers
- `FILE *`
- `fopen()`
- `fclose()`
- `fread()`
- `fwrite()`
- `fseek()`
- `fgets()`
- `scanf()`
- Binary file handling
- Menu-driven programming
- Basic input validation

## 🚀 Future Improvements

The project can be extended with:

- Delete Account
- Update Account Details
- Search Account
- Display All Accounts
- Account Password/PIN
- Transaction History
- Transfer Money Between Accounts
- Admin Login
- Better input validation
- Separate transaction file
- Encryption/security features

## 👨‍💻 Author

**Rohit Mishra**

B.Tech AI & ML Student

---

⭐ If you find this project useful, consider giving the repository a star!
