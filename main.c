#include<stdio.h>
#include<string.h>

struct Product {
    int productID;
    char name[50];
    float price;
    int stockQuantity;
};

struct Customer {
    char name[50];
    char phoneNumber[15];
    int orderCount;
};

struct Order {
    int orderID;
    char customerName[50];
    float originalBill;
    float finalBill;
    int discountApplied;
};

struct Product inventory[100] = {0};
struct Customer customers[100] = {0};

struct CustOrder {
    int totalOrders;
    struct Order orderHistory[500];
};

struct CustOrder customerOrders[100] = {0};

int totalCustomers = 0;
int totalProducts = 0;
int nextOrderID = 1;

void displayProducts();
void searchProduct();
void updateStock();
void addProduct();
void updateProduct();
void deleteProduct();
void purchaseProduct();
void viewOrderHistory();
void lowStockAlert();

int main() {
    int choice;

    for(int i = 0; i < 100; i++) {
        inventory[i].productID = 0;
        inventory[i].name[0] = '\0';
        inventory[i].price = 0.0;
        inventory[i].stockQuantity = 0;
    }

    do {
        printf("\n=== SUPERMARKET MANAGEMENT SYSTEM ===\n");
        printf("1. Display Products\n");
        printf("2. Search Product\n");
        printf("3. Update Stock\n");
        printf("4. Purchase Product\n");
        printf("5. View Order History\n");
        printf("6. Check Low Stock\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                displayProducts();
                break;
            case 2:
                searchProduct();
                break;
            case 3:
                updateStock();
                break;
            case 4:
                purchaseProduct();
                break;
            case 5:
                viewOrderHistory();
                break;
            case 6:
                lowStockAlert();
                break;
            case 7:
                printf("\nExiting program. Thank you!\n");
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    } while(choice != 7);

    return 0;
}

void displayProducts() {
    printf("\n\n========= PRODUCT INVENTORY =========\n");
    printf("%-6s %-50s %-10s %-10s\n\n",
           "ID", "Name", "Quantity", "Price");
    
    if(inventory[0].productID == 0) {
        return;
    }

    for(int i = 0; i < totalProducts; i++) {
        if(inventory[i].productID != 0) {
            printf("%-6d %-50s %-10d %-10.2f\n",
                   inventory[i].productID, inventory[i].name, inventory[i].stockQuantity, inventory[i].price);
        }
    }
    printf("\n");
}

void searchProduct() {
    int id, found = 0;

    printf("\nEnter product ID to search: ");
    if(scanf("%d", &id) != 1 && (id < 1 || id > 100)) {
        printf("\nInvalid product ID. Please enter a value between 1 and 100.\n\n");
        return;
    }

    for(int i = 0; i < totalProducts; i++) {
        if(inventory[i].productID == id) {
            printf("\nProduct ID: %d\n", inventory[i].productID);
            printf("Name: %s\n", inventory[i].name);
            printf("Price: %.2f\n", inventory[i].price);
            printf("Stock Quantity: %d\n\n", inventory[i].stockQuantity);
            found = 1;
            break;
        }
    }

    if(!found) {
        printf("\nProduct: %d not found!\n\n", id);
    }
}

void updateStock() {
    int choice;
    printf("\n1. Add Product\n");
    printf("2. Update Product\n");
    printf("3. Delete Product\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            addProduct();
            break;
        case 2:
            updateProduct();
            break;
        case 3:
            deleteProduct();
            break;
        default:
            printf("Invalid choice. Please try again.\n\n");
    }
}

void addProduct() {
    int id;

    printf("\nEnter product ID to add: ");
    if(scanf("%d", &id) != 1 && (id < 1 || id > 100)) {
        printf("\nInvalid product ID. Please enter a value between 1 and 100.\n\n");
        return;
    }

    for(int i = 0; i < totalProducts; i++) {
        if(inventory[i].productID == id) {
            printf("\nProduct: %d already exists. Please use a different ID.\n\n", id);
            return;
        }
    }

    inventory[totalProducts].productID = id;
    printf("\nEnter product Name: ");
    scanf(" %[^\n]", inventory[totalProducts].name);
    printf("\nEnter product price: ");
    scanf("%f", &inventory[totalProducts].price);
    printf("\nEnter product quantity: ");
    scanf("%d", &inventory[totalProducts].stockQuantity);

    totalProducts++;
    printf("\nProduct added successfully!\n\n");
}

void updateProduct() {
    int id, found = 0;

    printf("\nEnter product ID to update: ");
    if(scanf("%d", &id) != 1 && (id < 1 || id > 100)) {
        printf("\nInvalid product ID. Please enter a value between 1 and 100.\n\n");
        return;
    }

    for(int i = 0; i < totalProducts; i++) {
        if(inventory[i].productID == id) {
            printf("\nEnter new product price: ");
            scanf("%f", &inventory[i].price);
            printf("\nEnter new stock quantity: ");
            scanf("%d", &inventory[i].stockQuantity);
            found = 1;
            printf("\nProduct updated successfully!\n\n");
            break;
        }
    }

    if(!found) {
        printf("\nProduct: %d not found!\n\n", id);
    }
}

void deleteProduct() {
    int id, found = 0;

    printf("\nEnter product ID to delete: ");
    if(scanf("%d", &id) != 1 && (id < 1 || id > 100)) {
        printf("\nInvalid product ID. Please enter a value between 1 and 100.\n\n");
        return;
    }

    for(int i = 0; i < totalProducts; i++) {
        if(inventory[i].productID == id) {
            found = 1;
            break;
        }
    }

    if(found) {
        for(int i = id - 1; i < 99; i++) {
            inventory[i] = inventory[i + 1];
        }

        inventory[99].productID = 0;
        strcpy(inventory[99].name, "");
        inventory[99].price = 0.0;
        inventory[99].stockQuantity = 0;

        printf("\nProduct deleted successfully and inventory shifted!\n\n");
    } else {
        printf("\nProduct ID %d not found!\n\n", id);
    }
}

void purchaseProduct() {
    int cartID[50], cartQty[50];
    int count = 0;
    char custName[50], phone[15];
    int more;

    printf("\n========= CUSTOMER CHECKOUT =========\n");
    printf("\nEnter customer name: ");
    scanf(" %[^\n]", custName);
    printf("\nEnter customer phone number: ");
    scanf(" %[^\n]", phone);

    do {
        int id, qty, found = 0;
        printf("\nEnter product ID to purchase: ");

        if(scanf("%d", &id) != 1 && (id < 1 || id > 100)) {
            printf("\nInvalid product ID. Please enter a value between 1 and 100.\n\n");
            return;
        }

        for(int i = 0; i < totalProducts; i++) {
            if(inventory[i].productID == id) {
                found = 1;
                break;
            }
        }

        if(!found) {
            printf("\nProduct: %d not found.\n", id);
        } else {
            printf("\nEnter quantity to purchase: ");
            scanf("%d", &qty);

            if(inventory[id - 1].stockQuantity < qty) {
                printf("\nInsufficient stock! Available: %d\n", inventory[id - 1].stockQuantity);
            } else {
                cartID[count] = id;
                cartQty[count] = qty;
                count++;
                inventory[id - 1].stockQuantity -= qty;
                printf("\nProduct added to cart successfully.\n");
            }
        }

        printf("\nDo you want to buy another product? (1 for Yes, 0 for No): ");
        scanf("%d", &more);
    } while(more == 1 && count < 50);

    if(!count) {
        printf("\nNo products purchased.\n\n");
        return;
    }

    int cIndex, cust = 0;
    for(int i = 0; i < totalCustomers; i++) {
        if(strcmp(customers[i].phoneNumber, phone) == 0) {
            cIndex = i;
            cust = 1;
            break;
        }
    }

    if(!cust) {
        strcpy(customers[totalCustomers].name, custName);
        strcpy(customers[totalCustomers].phoneNumber, phone);
        customers[totalCustomers].orderCount = 0;
        cIndex = totalCustomers;
        totalCustomers++;
    }

    float totalBill = 0.0;
    printf("\n========= BILL DETAILS =========\n");
    printf("%-5s %-30s %-8s %-8s %-12s\n\n", "ID", "Name", "Qty", "Price", "Total");

    for(int i = 0; i < count; i++) {
        int index = cartID[i] - 1;
        float inBill = inventory[index].price * cartQty[i];
        printf("%-5d %-30s %-8d Rs.%-5.2f Rs.%-8.2f\n", 
               cartID[i], inventory[index].name, cartQty[i], inventory[index].price, inBill);
        totalBill += inBill;
    }
    printf("\nTotal bill: Rs.%.2f\n", totalBill);
    customers[cIndex].orderCount++;

    float finalBill = totalBill;
    int discountApplied = 0;

    if(customers[cIndex].orderCount >= 10) {
        finalBill = totalBill * 0.70;
        discountApplied = 1;
        printf("\n[REWARD UNLOCKED] Regular customer!\n");
        printf("Customers who ordered more than 10 times are placed in Regular customers list and enjoy a 30%% discount!\n");
        printf("Total orders placed: %d\n", customers[cIndex].orderCount);
    }

    printf("\nFinal bill to pay: Rs.%.2f\n\n", finalBill);
    int orders = customerOrders[cIndex].totalOrders;

    if(orders < 500) {
        customerOrders[cIndex].orderHistory[orders].orderID = nextOrderID;
        strcpy(customerOrders[cIndex].orderHistory[orders].customerName, custName);
        customerOrders[cIndex].orderHistory[orders].originalBill = totalBill;
        customerOrders[cIndex].orderHistory[orders].finalBill = finalBill;
        customerOrders[cIndex].orderHistory[orders].discountApplied = discountApplied;
        customerOrders[cIndex].totalOrders++;  
    } else {
        printf("Order history limit reached for this customer. Cannot record more orders.\n\n");
    }
    
    nextOrderID++;
}

void viewOrderHistory() {
    int found = 0;
    char phone[15];
    printf("\nEnter Customer Phone Number to view order history: ");
    scanf(" %[^\n]", phone);

    for(int i = 0; i < totalCustomers; i++) {
        if(strcmp(customers[i].phoneNumber, phone) == 0) {
            printf("\n========= ORDER HISTORY LOG =========\n");
            if(customerOrders[i].totalOrders) {
                printf("%-8s %-25s %-15s %-15s %-10s\n\n", "Order ID", "Customer Name", "Original (Rs.)", "Final (Rs.)", "Discount");
                for(int j = 0; j < customerOrders[i].totalOrders; j++) {
                    printf("%-8d %-25s Rs.%-12.2f Rs.%-12.2f %-10s\n",
                            customerOrders[i].orderHistory[j].orderID,
                            customerOrders[i].orderHistory[j].customerName,
                            customerOrders[i].orderHistory[j].originalBill,
                            customerOrders[i].orderHistory[j].finalBill,
                            customerOrders[i].orderHistory[j].discountApplied ? "30%% Off" : "None");
                    printf("\n");
                }
            }
            found = 1;
            break;
        }
    }

    if(!found) {
        printf("\nCustomer not found!\n\n");
    }
}

void lowStockAlert() {
    printf("\n========= LOW STOCK ALERT =========\n");
    printf("\n%-6s %-50s %-10s\n", "ID", "Name", "Quantity");

    for(int i = 0; i < totalProducts; i++) {
        if(inventory[i].productID != 0 && inventory[i].stockQuantity < 5) {
            printf("%-6d %-50s %-10d\n",
                   inventory[i].productID, inventory[i].name, inventory[i].stockQuantity);
        }
    }

    printf("\n");
}