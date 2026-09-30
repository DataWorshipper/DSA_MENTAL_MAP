#include <bits/stdc++.h>
using namespace std;
#define v vector
#define ll long long

class Account
{
    private:
    string accountNumber;
    string holderName;
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
    bool withdraw(double amount)
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


/*GEMINI GAVE THIS MAIN CODE FOR TESTING*/
int main() {
    std::cout << "=== Phase 1: Basic Operations ===" << std::endl;
    Account a1("ACC1001", "Alice", 5000.0);

    std::cout << "Initial balance: " << a1.getBalance() << std::endl;
    a1.deposit(1500.0);
    std::cout << "After deposit 1500: " << a1.getBalance() << std::endl;

    bool w1 = a1.withdraw(2000.0);
    std::cout << "Withdraw 2000 success? " << (w1 ? "Yes" : "No") 
              << " | Current balance: " << a1.getBalance() << std::endl;

    bool w2 = a1.withdraw(6000.0);
    std::cout << "Withdraw 6000 success? " << (w2 ? "Yes" : "No") 
              << " | Current balance: " << a1.getBalance() << std::endl;

    std::cout << "Total successful transactions: " << a1.getTransactionCount() << std::endl;

    std::cout << "\n=== Phase 2: Deep Copy Verification ===" << std::endl;
    Account a2 = a1; // Copy constructor fires here

    std::cout << "Original a1 txn count: " << a1.getTransactionCount() << std::endl;
    std::cout << "Copied   a2 txn count: " << a2.getTransactionCount() << std::endl;

    // Mutate a1 with another transaction
    std::cout << "\nPerforming deposit on a1 only..." << std::endl;
    a1.deposit(500.0);

    std::cout << "a1 txn count (should be +1): " << a1.getTransactionCount() << std::endl;
    std::cout << "a2 txn count (should stay unchanged): " << a2.getTransactionCount() << std::endl;

    if (a1.getTransactionCount() != a2.getTransactionCount()) {
        std::cout << ">> Deep copy SUCCESS: distinct heap allocations verified! <<" << std::endl;
    } else {
        std::cout << ">> Shallow copy detected! Both point to the same memory! <<" << std::endl;
    }

    std::cout << "\n=== Phase 3: 'this' pointer test ===" << std::endl;
    a1.setBalance(10000.0);
    std::cout << "Updated a1 balance via setBalance: " << a1.getBalance() << std::endl;

    std::cout << "\nExiting main... Destructors should run cleanly without double-free errors." << std::endl;
    return 0;
}