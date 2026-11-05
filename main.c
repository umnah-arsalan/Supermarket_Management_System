#include<stdio.h>
#include<string.h>

struct Product inventory[100] = {0};
struct Order orderHistory[500] = {0};

struct Product {
    int productID;
    char name[50];
    float price;
    int stockQuantity;
};

struct Order {
    int orderID;
    char customerName[50];
    int itemsPurchased;
    float totalBill;
};

void displayProducts();
void searchProduct();
void updateStock();
void addProduct();
void deleteProduct();
void purchaseProduct();
void generateBill();
void manageCustomers();
void lowStockAlert();

int main(){
    int choice;

    do {
        printf("\nINVENTORY MANAGEMENT SYSTEM\n\n");
        printf("1. Display Products\n");
        printf("2. Search Product\n");
        printf("3. Update Stock\n");
        printf("4. Purchase Product\n");
        printf("5. Check Low Stock\n");
        printf("6. Exit\n");
        scanf("%d",&choice);

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
                lowStockAlert();
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    } while(choice != 6);

    return 0;
}

void displayProducts() {
    printf("Product Inventory:\n");
    printf("\n%-6s %-20s %-10s %-10s\n",
           "ID", "Name", "Quantity", "Price");
    
    if(!inventory[0].productID) {
        return;
    }

    for(int i = 0; i < 100; i++) {
        if(inventory[i].productID != 0) {
            printf("%-6d %-20s %-10.2f %-10.2f\n",
                   inventory[i].productID, inventory[i].name, inventory[i].stockQuantity, inventory[i].price);
        }
    }
    printf("\n");
}

void searchProduct() {
    int id, found = 0;

    printf("\nEnter product ID: ");
    while(scanf("%d", &id) != 1 && (id < 1 || id > 100)) {
        printf("\nInvalid product ID. Please enter a value between 1 and 100: ");
        scanf("%d", &id);
    }

    for(int i = 0; i < 100; i++) {
        if(inventory[i].productID == id) {
            printf("\nProduct ID: %d\n", inventory[i].productID);
            printf("Name: %s\n", inventory[i].name);
            printf("Price: %.2f\n", inventory[i].price);
            printf("Stock Quantity: %d\n\n", inventory[i].stockQuantity);
            found = 1;
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
            updateStock();
            break;
        case 3:
            deleteProduct();
            break;
        default:
            printf("Invalid choice. Please try again.\n");
    }
}

void addProduct() {
    int id;

    printf("\nEnter Product ID: ");
    while(scanf("%d", &id) != 1 && (id < 1 || id > 100)) {
        printf("\nInvalid Product ID. Please enter a value between 1 and 100: ");
        scanf("%d", &id);
    }

    for(int i = 0; i < 100; i++) {
        if(inventory[i].productID == id) {
            printf("\nProduct: %d already exists. Please use a different ID.\n", id);
            return;
        }
    }

    inventory[id - 1].productID = id;
    printf("\nEnter Product Name: ");
    scanf(" %[^\n]", inventory[id - 1].name);
    printf("\nEnter product price: ");
    scanf("%f", &inventory[id - 1].price);
    printf("\nEnter quantity: ");
    scanf("%d", &inventory[id - 1].stockQuantity);

    printf("\nProduct added successfully!\n\n");
}

void updateStock() {
    int id, found = 0;

    printf("\nEnter Product ID to update stock: ");
    while(scanf("%d", &id) != 1 && (id < 1 || id > 100)) {
        printf("\nInvalid product ID. Please enter a value between 1 and 100: ");
        scanf("%d", &id);
    }

    for(int i = 0; i < 100; i++) {
        if(inventory[i].productID == id) {
            printf("\nEnter new stock quantity: ");
            scanf("%d", &inventory[i].stockQuantity);
            found = 1;
            printf("\nStock updated successfully!\n\n");
        }
    }

    if(!found) {
        printf("\nProduct: %d not found!\n\n", id);
    }
}

void deleteProduct() {
    int id, found = 0;

    printf("\nEnter Product ID to delete: ");
    while(scanf("%d", &id) != 1 && (id < 1 || id > 100)) {
        printf("\nInvalid product ID. Please enter a value between 1 and 100: ");
        scanf("%d", &id);
    }

    for(int i = 0; i < 100; i++) {
        if(inventory[i].productID == id) {
            inventory[i].productID = 0;
            found = 1;
            printf("\nProduct deleted successfully!\n\n");
        }
    }

    if(!found) {
        printf("\nProduct: %d not found!\n\n", id);
    }
}