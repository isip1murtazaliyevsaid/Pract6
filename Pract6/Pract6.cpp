#include <iostream>

using namespace std;

class BankAccount {
private:
    int accountNumber;
    double balance;
    double interestRate;

public:
    BankAccount(int accNum, double initialBalance) {
        this->accountNumber = accNum;
        if (initialBalance < 0) {
            cout << "Ошибка: Начальный баланс не может быть отрицательным" << endl;
            initialBalance = 0;
        }
        this->balance = initialBalance;
        this->interestRate = 0;
    }

    //внесение средств на счёт
    bool deposit(double amount) {
        if (amount <= 0) {
            cout << "Ошибка: Некорректная сумма перевода" << endl;
            return false;
        }
        balance += amount;
        cout << "Средства успешно внесены. Остаток на счёте: " << balance << endl;
        return true;
    }

    //снятие средств со счёта
    bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "Ошибка: Некорректная сумма снятия" << endl;
            return false;
        }
        if (amount > balance) {
            cout << "Ошибка: Недостаточно средств для снятия" << endl;
            return false;
        }
        balance -= amount;
        cout << "Средства успешно сняты. Остаток на счёте: " << balance << endl;
        return true;
    }

    
    double getBalance() const {
        return balance;
    }

    
    double getInterest() const {
        return balance * interestRate * (1 / 12);
    }

    
    void setInterestRate(double rate) {
        this->interestRate = rate;
    }

    
    int getAccountNumber() const {
        return accountNumber;
    }

    
    friend bool transfer(BankAccount& fromAccount, BankAccount& toAccount, double amount);
};

bool transfer(BankAccount& fromAccount, BankAccount& toAccount, double amount) {
    if (fromAccount.balance >= amount) {
        fromAccount.balance -= amount;
        toAccount.balance += amount;
        cout << "Перевод успешно выполнен" << endl;
        return true;
    }
    else {
        cout << "Ошибка: Недостаточно средств для перевода" << endl;
        return false;
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    int accNumber1, accNumber2;
    double initialBalance1, initialBalance2;
    cout << "Введите номер первого счёта: ";
    cin >> accNumber1;
    cout << "Введите начальный баланс первого счёта: ";
    cin >> initialBalance1;

    cout << "Введите номер второго счёта: ";
    cin >> accNumber2;
    cout << "Введите начальный баланс второго счёта: ";
    cin >> initialBalance2;

    BankAccount acc1(accNumber1, initialBalance1);
    BankAccount acc2(accNumber2, initialBalance2);

    int choice;
    double amount;
    while (true) {
        cout << "\nВыберите действие:\n"
            << "1. Внести средства на счёт\n"
            << "2. Снять средства со счёта\n"
            << "3. Перевести средства с одного счёта на другой\n"
            << "4. Показать текущий баланс\n"
            << "5. Выход\n";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введите сумму для внесения на счёт: ";
            cin >> amount;
            acc1.deposit(amount);
            break;
        case 2:
            cout << "Введите сумму для снятия со счёта: ";
            cin >> amount;
            acc1.withdraw(amount);
            break;
        case 3:
            cout << "Введите сумму для перевода с первого счета на второй: ";
            cin >> amount;
            transfer(acc1, acc2, amount);
            break;
        case 4:
            cout << "Остаток на счете: " << acc1.getBalance() << endl;
            break;
        case 5:
            cout << "Выход из программы." << endl;
            return 0;
        default:
            cout << "Некорректный ввод. Попробуйте ещё раз." << endl;
        }
    }
    return 0;
}