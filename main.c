#include<stdio.h>
int main(){
    int choice;
    do{
        printf("1-Add Products\n");
        printf("2-Display Products\n");
        printf("3-Search Prodcut\n");
        printf("4-Update Products\n");
        printf("5-Delete Product\n");
        printf("6-Generate bill\n");
        printf("7-manage customers\n");
        printf("8-check low stock\n");
        printf("9-Exit\n");
        scanf("%d",&choice);
        switch(choice){
            case 1: {
                addProduct();
                break;
            }
            case 2:{
                displayProducts();
                break;
            }
            case 3:{
                searchProduct();
                break;
            }
            case 4:{
                updateProduct();
                break;
            }
            case 5: {
                deleteProduct();
                break;
            }
            case 6: {
                generateBill();
                break;
            }
            case 7:{
                manageCustomers();
                break;
            }
            case 8:{
                checkLowstock();
                break;
            }
            case 9:{
                printf("Exiting the program.\n");
                break;
            }
             default:
            printf("Invalid choice. Please try again.\n");
        }
    }while(choice != 9);
}
void addProduct(){
    int id;
}