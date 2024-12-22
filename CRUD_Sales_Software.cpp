#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// ADT for Order
struct Order
{
    string product_id;
    string customer_name;
    string email;
    string product_name;
    int price;
    vector<string> additional_services;
    string support_plan;
    int support_price;

    Order *next;
};

// Generate random product ID
string generateProductID()
{
    srand(time(0));
    string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string digits = "0123456789";
    string id;
    id += letters[rand() % letters.length()];
    for (int i = 0; i < 9; ++i)
    {
        id += digits[rand() % digits.length()];
    }
    return id;
}

// Linked list for Orders
class OrderList
{
private:
    Order *head;

public:
    OrderList() : head(nullptr) {}

    void addOrder(Order *newOrder)
    {
        if (head == nullptr)
        {
            head = newOrder;
        }
        else
        {
            Order *temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newOrder;
        }
    }

    Order *findOrder(string product_id)
    {
        Order *temp = head;
        while (temp != nullptr)
        {
            if (temp->product_id == product_id)
            {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    void displayOrders()
    {
        Order *temp = head;
        while (temp != nullptr)
        {
            cout << "ID Produk: " << temp->product_id << endl;
            temp = temp->next;
        }
    }
};

// Stack for Additional Services
class ServiceStack
{
private:
    vector<string> stack;

public:
    void push(const string &service)
    {
        stack.push_back(service);
    }

    void pop()
    {
        if (!stack.empty())
        {
            stack.pop_back();
        }
    }

    void display()
    {
        for (const string &service : stack)
        {
            cout << service << endl;
        }
    }

    bool isEmpty()
    {
        return stack.empty();
    }
};

// Main Function
int main()
{
    OrderList orders;
    ServiceStack serviceStack;
    int choice;

    do
    {
        cout << "\n============== SOFTWARE SALES ================" << endl;
        cout << "Menu:" << endl;
        cout << "1. Masukkan data customer" << endl;
        cout << "2. Cek detail Orderan" << endl;
        cout << "3. Tambah Pelayanan" << endl;
        cout << "4. Tambah Support Plan" << endl;
        cout << "5. Proses Transaksi" << endl;
        cout << "0. Keluar" << endl;
        cout << "Masukkan opsi yang mau dipilih: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            // Input customer details
            string customer_name, customer_email;
            cout << "Nama Lengkap: ";
            getline(cin, customer_name);
            cout << "Email: ";
            getline(cin, customer_email);

            // Choose software product
            cout << "Pilih produk:" << endl;
            cout << "1. Aplikasi POS (Point Of Sales) Untuk Manajemen UMKM - Rp. 4,500,000" << endl;
            cout << "2. Aplikasi Pembuatan Blog CMS (Content Managemen System) Berbasis Laravel - Rp. 7,500,000" << endl;
            cout << "3. Sistem Tata Kelola IOT Untuk Smart Eco-House - Rp. 15,000,000" << endl;
            cout << "4. Aplikasi Booking Perhotelan Berbasis Flutter + Swift - Rp. 10,200,000" << endl;
            int product_choice;
            cin >> product_choice;

            string product_name;
            int price;

            switch (product_choice)
            {
            case 1:
                product_name = "Aplikasi POS (Point Of Sales) Untuk Manajemen UMKM";
                price = 4500000;
                break;
            case 2:
                product_name = "Aplikasi Pembuatan Blog CMS (Content Managemen System) Berbasis Laravel";
                price = 7500000;
                break;
            case 3:
                product_name = "Sistem Tata Kelola IOT Untuk Smart Eco-House";
                price = 15000000;
                break;
            case 4:
                product_name = "Aplikasi Booking Perhotelan Berbasis Flutter + Swift";
                price = 10200000;
                break;
            default:
                cout << "Opsi tidak ada." << endl;
                continue;
            }

            string product_id = generateProductID();
            cout << "Orderan kamu sudah di-booking nih, dengan ID: " << product_id << endl;

            // Add order to list
            Order *newOrder = new Order{product_id, customer_name, customer_email, product_name, price, {}, "", 0, nullptr};
            orders.addOrder(newOrder);
        }
        else if (choice == 2)
        {
            // Check order details
            string product_id;
            cout << "Masukin ID Orderan: ";
            cin >> product_id;

            Order *order = orders.findOrder(product_id);
            if (order)
            {
                cout << "ID Pemesanan: " << order->product_id << endl;
                cout << "Nama Customer: " << order->customer_name << endl;
                cout << "Produk: " << order->product_name << endl;
                cout << "Harga: Rp. " << order->price << endl;
                if (!order->additional_services.empty())
                {
                    cout << "Pelayanan Tambahan: ";
                    for (const string &service : order->additional_services)
                    {
                        cout << service << " ";
                    }
                    cout << endl;
                }
                else
                {
                    cout << "Tidak ada pelayanan tambahan yang dimasukkan." << endl;
                }
                if (!order->support_plan.empty())
                {
                    cout << "Support Plan: " << order->support_plan << endl;
                    cout << "Harga Support Plan: Rp. " << order->support_price << endl;
                }
                else
                {
                    cout << "Tidak ada Support Plan yang ditambahkan." << endl;
                }
            }
            else
            {
                cout << "Orderan tidak ada." << endl;
            }
        }
        else if (choice == 3)
        {
            // Add Additional Services
            string product_id;
            cout << "Masukin ID Orderan: ";
            cin >> product_id;

            Order *order = orders.findOrder(product_id);
            if (order)
            {
                cout << "Pilih Pelayanan Tambahan:" << endl;
                cout << "1. Cloud Backup - Rp. 350,000" << endl;
                cout << "2. Data Recovery - Rp. 420,000" << endl;
                cout << "3. Premium Support - Rp. 475,000" << endl;
                int service_choice;
                cin >> service_choice;

                switch (service_choice)
                {
                case 1:
                    order->additional_services.push_back("Cloud Backup");
                    order->support_price += 350000;
                    break;
                case 2:
                    order->additional_services.push_back("Data Recovery");
                    order->support_price += 420000;
                    break;
                case 3:
                    order->additional_services.push_back("Premium Support");
                    order->support_price += 475000;
                    break;
                default:
                    cout << "Opsi tidak ada!" << endl;
                    continue;
                }
                cout << "Pelayanan Tambahan berhasil ditambahkan~" << endl;
            }
            else
            {
                cout << "Orderan tidak ada!" << endl;
            }
        }
        else if (choice == 4)
        {
            // Add Support Plan
            string product_id;
            cout << "Masukin ID Orderan: ";
            cin >> product_id;

            Order *order = orders.findOrder(product_id);
            if (order)
            {
                cout << "Pilih Support Plan yang diinginkan:" << endl;
                cout << "1. Basic Support (Gratis)" << endl;
                cout << "2. Premium Support - Rp. 300,000" << endl;
                int plan_choice;
                cin >> plan_choice;

                if (plan_choice == 1)
                {
                    order->support_plan = "Basic Support";
                }
                else if (plan_choice == 2)
                {
                    order->support_plan = "Premium Support";
                    order->support_price += 300000;
                }
                else
                {
                    cout << "Opsi tidak ada." << endl;
                }
                cout << "Support plan berhasil ditambahkan~" << endl;
            }
            else
            {
                cout << "Orderan tidak ada." << endl;
            }
        }
        else if (choice == 5)
        {
            // Process Payment
            string product_id;
            cout << "Masukin ID Orderan: ";
            cin >> product_id;

            Order *order = orders.findOrder(product_id);
            if (order)
            {
                int total_price = order->price + order->support_price;
                cout << "Total Bayar: Rp. " << total_price << endl;
                cout << "Pembayaran berhasil~" << endl;
            }
            else
            {
                cout << "Orderan tidak ada." << endl;
            }
        }
    } while (choice != 0);

    return 0;
}
