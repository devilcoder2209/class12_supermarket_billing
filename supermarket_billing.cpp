#include <iostream>
#include <fstream>
#include <string>

class Product {
    int pno;
    std::string name;
    float price, qty, tax, dis;

public:
    void createProduct() {
        std::cout << "\nPlease Enter The Product No. of The Product: ";
        std::cin >> pno;
        std::cout << "\nPlease Enter The Name of The Product: ";
        std::cin.ignore();
        std::getline(std::cin, name);
        std::cout << "\nPlease Enter The Price of The Product: ";
        std::cin >> price;
        std::cout << "\nPlease Enter The Discount (%): ";
        std::cin >> dis;
    }

    void showProduct() {
        std::cout << "\nThe Product No. of The Product: " << pno;
        std::cout << "\nThe Name of The Product: " << name;
        std::cout << "\nThe Price of The Product: " << price;
        std::cout << "\nDiscount (%): " << dis;
    }

    int getpno() const {
        return pno;
    }

    float getPrice() const {
        return price;
    }

    const std::string& getName() const {
        return name;
    }

    int getDiscount() const {
        return dis;
    }
};

std::fstream fp;
Product pr;

void writeProduct() {
    fp.open("Shop.dat", std::ios::out | std::ios::app);
    pr.createProduct();
    fp.write(reinterpret_cast<const char*>(&pr), sizeof(Product));
    fp.close();
    std::cout << "\n\nThe Product Has Been Created ";
}

void displayAll() {
    std::cout << "\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    fp.open("Shop.dat", std::ios::in);
    while (fp.read(reinterpret_cast<char*>(&pr), sizeof(Product))) {
        pr.showProduct();
        std::cout << "\n\n====================================\n";
    }
    fp.close();
}

void displaySpecific(int n) {
    int flag = 0;
    fp.open("Shop.dat", std::ios::in);
    while (fp.read(reinterpret_cast<char*>(&pr), sizeof(Product))) {
        if (pr.getpno() == n) {
            pr.showProduct();
            flag = 1;
            break;
        }
    }
    fp.close();
    if (flag == 0)
        std::cout << "\n\nRecord not exist";
}

void modifyProduct() {
    int no, found = 0;
    std::cout << "\n\n\tTo Modify ";
    std::cout << "\n\n\tPlease Enter The Product No. of The Product: ";
    std::cin >> no;
    fp.open("Shop.dat", std::ios::in | std::ios::out);
    while (fp.read(reinterpret_cast<char*>(&pr), sizeof(Product)) && found == 0) {
        if (pr.getpno() == no) {
            pr.showProduct();
            std::cout << "\nPlease Enter The New Details of Product" << std::endl;
            pr.createProduct();
            int pos = -1 * sizeof(pr);
            fp.seekp(pos, std::ios::cur);
            fp.write(reinterpret_cast<const char*>(&pr), sizeof(Product));
            std::cout << "\n\n\t Record Updated";
            found = 1;
        }
    }
    fp.close();
    if (found == 0)
        std::cout << "\n\n Record Not Found ";\
}
void deleteProduct() {
int no;
std::cout << "\n\n\n\tDelete Record";
std::cout << "\n\nPlease Enter The product no. of The Product You Want To Delete: ";
std::cin >> no;
fp.open("Shop.dat", std::ios::in | std::ios::out);
std::fstream fp2;
fp2.open("Temp.dat", std::ios::out);
fp.seekg(0, std::ios::beg);
while (fp.read(reinterpret_cast<char*>(&pr), sizeof(Product))) {
if (pr.getpno() != no) {
fp2.write(reinterpret_cast<const char*>(&pr), sizeof(Product));
}
}
fp2.close();
fp.close();
std::remove("Shop.dat");
std::rename("Temp.dat", "Shop.dat");
std::cout << "\n\n\tRecord Deleted ..";
}

void displayMenu() {
std::cout << "\n\n\t\tProduct MENU\n\n";
std::cout << "====================================================\n";
std::cout << "P.NO.\t\tNAME\t\tPRICE\n";
std::cout << "====================================================\n";
fp.open("Shop.dat", std::ios::in);
if (!fp) {
    std::cout << "ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File";
    std::cout << "\n\n\n Program is closing ....";
    std::exit(0);
}

while (fp.read(reinterpret_cast<char*>(&pr), sizeof(Product))) {
    std::cout << pr.getpno() << "\t\t" << pr.getName() << "\t\t" << pr.getPrice() << std::endl;
}
fp.close();

}

void placeOrder() {
int order_arr[50], quan[50], c = 0;
float amt, damt, total = 0;
char ch = 'Y';
displayMenu();
std::cout << "\n============================";
std::cout << "\n PLACE YOUR ORDER";
std::cout << "\n============================\n";
do {
std::cout << "\nEnter The Product No. Of The Product: ";
std::cin >> order_arr[c];
std::cout << "\nQuantity in number: ";
std::cin >> quan[c];
c++;
std::cout << "\nDo You Want To Order Another Product? (y/n)";
std::cin >> ch;
} while (ch == 'y' || ch == 'Y');
std::cout << "\n\nThank You For Placing The Order";
std::cout << "\n\n****************************INVOICE********************\n";
std::cout << "\nPr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount after discount\n";
for (int x = 0; x < c; x++) {
    fp.open("Shop.dat", std::ios::in);
    while (fp.read(reinterpret_cast<char*>(&pr), sizeof(Product))) {
        if (pr.getpno() == order_arr[x]) {
            amt = pr.getPrice() * quan[x];
            damt = amt - (amt * pr.getDiscount() / 100);
            std::cout << "\n" << order_arr[x] << "\t" << pr.getName() << "\t" << quan[x] << "\t\t" << pr.getPrice() << "\t" << amt << "\t\t" << damt;
            total += damt;
            break;
        }
    }
    fp.close();
}
std::cout << "\n\n\t\t\t\t\tTOTAL = " << total;
}

void adminMenu() {
char ch2;
std::cout << "\n\n\n\tADMIN MENU";
std::cout << "\n\n\t1.CREATE PRODUCT";
std::cout << "\n\n\t2.DISPLAY ALL PRODUCTS";
std::cout << "\n\n\t3.QUERY ";
std::cout << "\n\n\t4.MODIFY PRODUCT";
std::cout << "\n\n\t5.DELETE PRODUCT";
std::cout << "\n\n\t6.VIEW PRODUCT MENU";
std::cout << "\n\n\t7.BACK TO MAIN MENU";
std::cout << "\n\n\tPlease Enter Your Choice (1-7): ";
std::cin >> ch2;
switch (ch2) {
case '1':
writeProduct();
break;
case '2':
displayAll();
break;
case '3': {
int num;
std::cout << "\n\n\tPlease Enter The Product No.: ";
std::cin >> num;
displaySpecific(num);
break;
}

case '4':
modifyProduct();
break;
case '5':
deleteProduct();
break;
case '6':
displayMenu();
break;
case '7':
break;
default:
std::cout << "\a";
adminMenu();
}
}
void mainMenu() {
char ch;
do {
std::cout << "\n\n\n\tMAIN MENU";
std::cout << "\n\n\t01. CUSTOMER";
std::cout << "\n\n\t02. ADMINISTRATOR";
std::cout << "\n\n\t03. EXIT";
std::cout << "\n\n\tPlease Select Your Option (1-3): ";
std::cin >> ch;
switch (ch) {
case '1':
placeOrder();
break;
case '2':
adminMenu();
break;
case '3':
exit(0);
default:
std::cout << "\a";
}
} while (ch != '3');
}

int main() {
mainMenu();
return 0;
}
