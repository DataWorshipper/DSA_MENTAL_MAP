#include <bits/stdc++.h>
using namespace std;
#define v vector
#define ll long long
class BankTransferService;
class Account
{   
    friend void auditAccount(Account &obj);
    friend class BankTransferService;
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

void auditAccount(Account &obj)
{
    cout<<obj.accountNumber<<" "<<obj.holderName<<" "<<obj.balance<<" "<<*(obj.transactionCount);
}

class BankTransferService
{       
    public:
        bool transferFunds(Account &from,Account &to,double amount)
        {
            if(amount>0 && from.balance>=amount)
            {
                from.balance-=amount;
                to.balance+=amount;
                (*from.transactionCount)++;
                (*to.transactionCount)++;
                return true;
            }
            return false;
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
    std::cout << "=== Friend Function & Friend Class Exercise ===" << std::endl;

    Account a1("ACC001", "Alice", 5000.0);
    Account a2("ACC002", "Bob", 2000.0);

    std::cout << "\n--- Testing Friend Function: Initial Audit ---" << std::endl;
    auditAccount(a1);
    auditAccount(a2);

    std::cout << "\n--- Testing Friend Class: BankTransferService ---" << std::endl;
    BankTransferService transferService;

    // Test a valid transfer
    bool t1 = transferService.transferFunds(a1, a2, 1500.0);
    std::cout << "Transfer ₹1500 from Alice to Bob: " << (t1 ? "SUCCESS" : "FAILED") << std::endl;

    // Test an invalid transfer (insufficient funds)
    bool t2 = transferService.transferFunds(a1, a2, 10000.0);
    std::cout << "Transfer ₹10000 from Alice to Bob: " << (t2 ? "SUCCESS" : "FAILED (expected)") << std::endl;

    std::cout << "\n--- Testing Friend Function: Post-Transfer Audit ---" << std::endl;
    auditAccount(a1); // Should show balance 3500, txn count 1
    auditAccount(a2); // Should show balance 3500, txn count 1

    return 0;
}