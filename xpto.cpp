#include <bits/stdc++.h>
#include <thread>
#include <chrono>
using namespace std;    

string itens[7] = {
    "Bicicleta nova na cor amarela, aro 26, com 18 marchas - Valor promocional: R$ 999,99",
    "Bicicleta usada na cor azul, aro 26, com 18 marchas - Valor promocional: R$ 400,00",
    "Capacete de proteção - Valor: R$ 59,99",
    "Freio a disco - Valor: R$ 89,99",
    "Troca de pneu - Valor: R$ 55,99",
    "Lavagem completa - Valor: R$ 12,99",
    "Ajuste de freio - Valor: R$ 10,99"
    };

    float value[7] = {
        999.99,
        400.00,
        59.99,
        89.99,
        55.99,
        12.99,
        10.99
    };

    int cart[3] = {-1, -1, -1};
    int cartSize = 0;

    void clearScreen() {
        cout << "\033[2J\033[1;1H"; 
    }

    string welcomeMessage() {
       string name;
       cout << "Welcome to the Bicycle Shop! Please enter your name: ";
       cin >> name;
    
       return name;
    }

    int menu(){
        int option;
        cout << "\n---------- MENU PRINCIPAL ----------" << endl;
        cout << "Option 1 - View promotions" << endl;
        cout << "Option 2 - Request maintenance service " << endl;
        cout << "Option 3 - View Cart" << endl;
        cout << "Option 4 - Finalize Purchase" << endl;
        cout << "Option 0 - Exit" << endl;
        cout << "Enter your option: ";
        cin >> option;

        return option;
    }

    void addCart(int screen){
        int index;
        int code;

        cout << "Enter the code of the item you want to add to the cart: ";
        cin >> code;

        if (screen == 1) {
            if (code < 101 || code > 104){
                cout << "[ERROR] Invalid code for the promotions menu." << endl;
                return;
            }
        }

        else if (screen == 2) {
            if (code < 201 || code > 203){
                cout << "[ERROR] Invalid code for the maintenance menu." << endl;
                return;
            }
        }

        if (cartSize >= 3) {
            cout << "[ERROR] Cart is full. Cannot add more items." << endl;
        } else {
            if (code >= 101 && code <= 104){
                index = code - 101;
                cart[cartSize] = index;
                cartSize++;
                cout << "------ Item added to cart successfully! ------" << endl;
            } else if (code >= 201 && code <= 203) {
                index = code - 197;
                cart[cartSize] = index;
                cartSize++;
                cout << "------ Item added to cart successfully! ------" << endl;
            } else {
                cout << "[ERROR] Invalid code. Please try again." << endl;
            }
        }
    }

    void inputData(int screen){
        int option;
        cout << "Enter the desired option: "<< endl;
        cin >> option;

        while (option != 0 && option != 8){
            cout << "[ERROR] Invalid option. Choose (8) to add an item and (0) to return to the menu:" << endl;
            cin >> option;
        } 
            if (option == 0){
                clearScreen();
                cout << "Returning to the main menu..." << endl;
                this_thread::sleep_for(chrono::milliseconds(1000));
            } 
            if (option == 8){
                addCart(screen);
            }
    }

    void viewPromotions(){
        int vetorSize = 4;

        clearScreen();
        cout << "------------------------------" << endl;
        for (int i = 0; i < vetorSize; i++){
            cout << "Code " << 101 + i << ": " << itens[i]<< endl;
        }
        cout << "------------------------------" << endl;
        cout << "Option (8) - Add item to cart" << endl;
        cout << "Option (0) - Return to main menu" << endl;
        cout << "------------------------------" << endl;

        inputData(1);
    }

    void requestService(){
        int vetorSize = 7;

        clearScreen();
        cout << "------------------------------" << endl;
        for (int i = 4; i < vetorSize; i++){
            cout << "Code " << 197 + i << ": " << itens[i]<< endl;
        }
        cout << "------------------------------" << endl;
        cout << "Option (8) - Add item to cart" << endl;
        cout << "Option (0) - Return to main menu" << endl;
        cout << "------------------------------" << endl;

        inputData(2);
    }

    float calculateTotal(){
        float total = 0.0;
        int index;

        for (int i = 0; i < cartSize; i++){
            index = cart[i];
            total = total + value[index];
        }
        return total;
    }

    float calculateDiscount(float total){
        total = total * 0.9;
        return total;
    }

    void viewCart(string name){
        clearScreen();

        if (cartSize == 0){
            cout << "Your cart is empty." << endl;
        } else {
            cout << "------ " << name << "'s Cart ------" << endl;
            for (int i = 0; i < cartSize; i++){
                cout << "Item " << i + 1 << ": " << itens[cart[i]] << endl;
            }
            cout << "Total: R$ " << calculateTotal() << endl;
        }

        this_thread::sleep_for(chrono::milliseconds(4000));
    }

    void clearCart(){
        cart[0] = -1;
        cart[1] = -1;
        cart[2] = -1;
        cartSize = 0;
    }

    void finalizeCart(string name){
        clearScreen();

        if (cartSize == 0){
            cout << "Your cart is empty. Cannot finalize purchase." << endl;
            this_thread::sleep_for(chrono::milliseconds(4000));
        } else {
            float total = calculateTotal();
            int payment;

            cout << "------ " << name << "'s Purchase Summary ------" << endl;

            for (int i = 0; i < cartSize; i++){
                cout << "Item " << i + 1 << ": " << itens[cart[i]] << endl;
            }
            cout << "Subtotal: R$ " << total << endl;
            cout << "Payment options - Money(1) or Credit Card(2): " << endl;
            cin >> payment;

            while (payment != 1 && payment != 2){
                cout << "[ERROR] Invalid payment option. Please choose (1) for Money or (2) for Credit Card: " << endl;
                cin >> payment;
            }
            if (payment == 1){
                total = calculateDiscount(total);
                cout << "------ 10% discount applied! ------" << endl;
            }

            cout << "------ Final Total: R$ " << total << " ------" << endl;
            this_thread::sleep_for(chrono::milliseconds(3000));

            cout << "Thank you for your purchase, " << name << "! We hope to see you again soon." << endl;
            this_thread::sleep_for(chrono::milliseconds(5000));
            clearCart();
            clearScreen();
        }
    }

int main(){
    string name = welcomeMessage();
    int option = 1;

    while (option != 0){
        option = menu();

        switch (option){
            case 1:
                viewPromotions();
                break;
            case 2:
                requestService();
                break;
            case 3:
                viewCart(name);
                break;
            case 4:
                finalizeCart(name);
                break;
            case 0:
                 cout << "Exiting the program. Goodbye!" << endl;
                 this_thread::sleep_for(chrono::milliseconds(4000));   
                 clearScreen();
                 break;
            default:
                cout << "[ERROR] Invalid option. Please try again." << endl;
                this_thread::sleep_for(chrono::milliseconds(4000));   
                clearScreen();
        }
    }

    return 0;
}