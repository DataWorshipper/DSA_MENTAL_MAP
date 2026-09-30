#include <bits/stdc++.h>
using namespace std;
#define v vector
#define ll long long

class Account
{
    private:
    string accountNumber;
    string holderName;
    protected:
    double balance;
    int* transactionCount;
    public:
    Account(string s1,string s2,double b1)
    {

        accountNumber=s1;
        holderName=s2;
        balance=b1;
        transactionCount=new int(0);
    }
    Account(Account &a)
    {
        this->accountNumber=a.accountNumber;
        this->balance=a.balance;
        this->holderName=a.holderName;
        this->transactionCount=new int(*(a.transactionCount));
    }
    ~Account()
    {
        delete transactionCount;
    }
    void deposit(double amount)
    {
        balance+=amount;
        /*My previous mistake was that i was doing *(transactionCount)++ ,  the ++ has higher precedence , so the addres will increase by 4 byes(since its int)  and then dereference it */
        (*transactionCount)++;
    }
     virtual bool withdraw(double amount)
    {
        if(amount<=balance && amount>0)
        {
            balance-=amount;
            (*transactionCount)++;
            return true;
        }
        return false;
    }
    void setBalance(double balance)
    {
        this->balance=balance;
    }

    string getAccountNumber()
    {
        return accountNumber;
    }
    string getHolderName()
    {
        return holderName;
    }
    double getBalance()
    {
        return this->balance;
    }
    int getTransactionCount()
    {
        return *(transactionCount);
    }
};

class SavingsAccount:public Account
{
    private:
    double interestRate;
    public:
    SavingsAccount(string s1,string s2,double b1,double rate):Account(s1,s2,b1)
    {
        interestRate=rate;
    }
    public:
    void addInterest()
    {
         double i_amt=balance*interestRate;
        deposit(i_amt);
    }
};

class CurrentAccount:public Account
{
        private:
        double overdraftLimit;
        public:
        CurrentAccount(string s1,string s2,double b1,double o1):Account(s1,s2,b1)
        {
            overdraftLimit=o1;
        }
        bool withdraw(double amount) override{
            if(amount>0 && amount<balance+overdraftLimit)
            {
                balance-=amount;
                (*transactionCount)++;
                return true;
            }
            return false;
        }

};

int main() {
    std::cout << "=== Phase 4 & 5: Savings & Current Accounts ===" << std::endl;

    // 1. Test SavingsAccount
    SavingsAccount sa("SAV101", "Bob", 10000.0, 0.05);
    std::cout << "Savings Initial Balance: " << sa.getBalance() << std::endl;
    
    sa.addInterest(); // 5% of 10000 = 500 added
    std::cout << "Savings Balance after interest: " << sa.getBalance() << std::endl;
    std::cout << "Savings Txn Count: " << sa.getTransactionCount() << std::endl;

    std::cout << "\n--- CurrentAccount (Overdraft) ---" << std::endl;

    // 2. Test CurrentAccount: balance = 1000, overdraft limit = 500 (max pull = 1500)
    CurrentAccount ca("CUR202", "Charlie", 1000.0, 500.0);
    std::cout << "Current Initial Balance: " << ca.getBalance() << std::endl;

    // Should succeed: leaves balance at -300
    bool ok1 = ca.withdraw(1300.0);
    std::cout << "Withdraw 1300 (uses overdraft)? " << (ok1 ? "Yes" : "No")
              << " | Balance: " << ca.getBalance() << std::endl;

    // Should fail: remaining capacity is only 200 (since balance is -300 and limit is 500)
    bool ok2 = ca.withdraw(300.0);
    std::cout << "Withdraw 300 (exceeds overdraft)? " << (ok2 ? "Yes" : "No")
              << " | Balance: " << ca.getBalance() << std::endl;

    std::cout << "Current Txn Count: " << ca.getTransactionCount() << std::endl;

    return 0;
}