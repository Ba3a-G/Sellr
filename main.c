#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_RECORDS 50
struct property
{
    char address[50];
    char type[50];
    int price;
};

// Function to write property data to disc in csv format
void write_to_file(struct property *records, int num_records)
{
    // Open file in write mode
    FILE *fp = fopen("records.csv", "w");
    // Write empty data to disc
    fprintf(fp, "");
    // Write property data to file
    for (int i = 0; i < num_records; i++)
    {
        fprintf(fp, "%s,%s,%d\n", records[i].address,
                records[i].type, records[i].price);
    }
    // Close file
    fclose(fp);
}

// Function to read property data from disc in csv format
void read_from_file(struct property *records, int *num_records)
{
    // Open file in read mode
    FILE *fp = fopen("records.csv", "r");
    // Check if file exists
    if (fp == NULL)
    {
        return;
    }
    // Read property data from file
    char line[100];
    while (fgets(line, 100, fp) != NULL)
    {
        sscanf(line, "%[^,],%[^,],%d", records[*num_records].address, records[*num_records].type, &records[*num_records].price);
        (*num_records)++;
    }
    // Close file
    fclose(fp);
}

// Function to add a new property record
void add_new_record(struct property *records, int *num_records) {
    // Check if maximum number of records has been reached
    if (*num_records == MAX_RECORDS)
    {
        printf("Maximum number of records reached.\n");
        return;
    }
    // Get new record details from user
    printf("Enter property address: ");
    scanf(" %[^\n]", records[*num_records].address);
    printf("Enter property type: ");
    scanf(" %[^\n]", records[*num_records].type);
    printf("Enter property price: ");
    scanf("%d", &records[*num_records].price);
    // Increase number of records
    (*num_records)++;
    printf("Record added.\n");
}

// Function to display available property
void display_record(struct property *records, int num_records) {
    // Check if there are any records
    if (num_records == 0)
    {
        printf("No records available.\n");
        return;
    }
    // Display all available properties
    printf("%-20s %-20s %-10s\n", "Address", "Type", "Price");
    for (int i = 0; i < num_records; i++)
    {
        if (records[i].price > 0)
        {
            printf("%-20s %-20s Rs %-9d\n", records[i].address, records[i].type, records[i].price);
        }
    }
}

// Function to search for a property record
void search_record(struct property *records, int num_records)
{
    // Check if there are any records
    if (num_records == 0)
    {
        printf("No records available.\n");
        return;
    }
    // Get search query from user
    char search_query[50];
    printf("Enter property address or type to search: ");
    scanf(" %[^\n]", search_query);
    // Search for property record
    int found = 0;
    for (int i = 0; i < num_records; i++)
    {
        if (strcmp(records[i].address, search_query) == 0 ||
            strcmp(records[i].type, search_query) == 0)
        {
            printf("\n%-20s %-20s $%-9d\n", records[i].address,
                   records[i].type, records[i].price);
            found = 1;
        }
    }
    // Display message if no record was found
    if (!found)
    {
        printf("No matching records found.\n");
    }
}

// Function to buy/sell a property record
void buy_sell_record(struct property *records, int num_records) {
    // Check if there are any records
    if (num_records == 0)
    {
        printf("No records available.\n");
        return;
    }
    // Get address of property to buy/sell from user
    char address[50];
    printf("Enter property address to buy/sell: ");
    scanf(" %[^\n]", address);
    // Search for property record
    int index = -1;
    for (int i = 0; i < num_records; i++)
    {
        if (strcmp(records[i].address, address) == 0)
        {
            index = i;
            break;
        }
    }
    // Display message if property was not found
    if (index == -1)
    {
        printf("Property");
    } // Display property details
    printf("%-20s %-20s $%-9d\n", records[index].address,
           records[index].type, records[index].price);
    // Get transaction type from user
    printf("Enter 'buy' to buy property or 'sell' to sell property: ");
    char transaction_type[10];
    scanf(" %[^\n]", transaction_type);
    // Perform transaction
    if (strcmp(transaction_type, "buy") == 0)
    {
        if (records[index].price == 0)
        {
            printf("This property is not for sale.\n");
        }
        else
        {
            printf("Property bought for $%d.\n",
                   records[index].price);
            records[index].price = 0;
        }
    }
    else if (strcmp(transaction_type, "sell") == 0)
    {
        if (records[index].price > 0)
        {
            printf("This property is already for sale.\n");
        }
        else
        {
            printf("Enter new property price: ");
            scanf("%d", &records[index].price);
            printf("Property put up for sale for $%d.\n",
                   records[index].price);
        }
    }
    else
    {
        printf("Invalid transaction type.\n");
    }
}

// Function to edit/delete a property record
void edit_delete_record(struct property *records, int *num_records) {
    // Check if there are any records
    if (*num_records == 0)
    {
        printf("No records available.\n");
        return;
    } // Get address of property to edit/delete from user
    char address[50];
    printf("Enter property address to edit/delete: ");
    scanf(" %[^\n]", address);
    // Search for property record
    int index = -1;
    for (int i = 0; i < *num_records; i++)
    {
        if (strcmp(records[i].address, address) == 0)
        {
            index = i;
            break;
        }
    }
    // Display message if property was not found
    if (index == -1)
    {
        printf("Property not found.\n");
        return;
    }
    // Display property details
    printf("%-20s %-20s $%-9d\n", records[index].address,
           records[index].type, records[index].price);
    // Get action from user
    printf("Enter 'edit' to edit property or 'delete' to delete property: ");
    char action[10];
    scanf(" %[^\n]", action);
    // Perform action
    if (strcmp(action, "edit") == 0)
    {
        // Get new property details from user
        printf("Enter new property address (leave blank to keep current value \"%s\"): ", records[index].address);
        char new_address[50];
        scanf(" %[^\n]", new_address);
        if (strcmp(new_address, "") != 0)
        {
            strcpy(records[index].address, new_address);
        }
        printf("Enter new property type (leave blank to keep current value \"%s\"): ", records[index].type);
        char new_type[50];
        scanf(" %[^\n]", new_type);
        if (strcmp(new_type, "") != 0)
        {
            strcpy(records[index].type, new_type);
        }
        printf("Enter new property price (leave blank to keep current value \"$%d\"): ", records[index].price);
        char new_price_str[50];
        scanf(" %[^\n]", new_price_str);
        if (strcmp(new_price_str, "") != 0)
        {
            int new_price = atoi(new_price_str);
            records[index].price = new_price;
        }
        printf("Property details updated.\n");
    }
    else if (strcmp(action, "delete") == 0)
    {
        // Delete property record
        for (int i = index; i < *num_records - 1; i++)
        {
            records[i] = records[i + 1];
        }
        (*num_records)--;
        printf("Property record deleted.\n");
    }
    else
    {
        printf("Invalid action.\n");
    }
}

// Main
int main() {
    struct property records[MAX_RECORDS];
    int num_records = 0; // Display menu
    read_from_file(records, &num_records); // Read records from file
    while (1)
    {
        printf("\nReal Estate Management System\n");
        printf("1. Add new property record\n");
        printf("2. Display available properties\n");
        printf("3. Search property\n");
        printf("4. Buy/sell property\n");
        printf("5. Edit/delete property record\n");
        printf("6. Exit\n");
        // Get user input
        int choice;
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);
        // Perform action based on user choice
        switch (choice)
        {
        case 1:
            add_new_record(records, &num_records);
            break;
        case 2:
            display_record(records, num_records);
            break;
        case 3:
            search_record(records, num_records);
            break;
        case 4:
            buy_sell_record(records, num_records);
            break;
        case 5:
            edit_delete_record(records, &num_records);
            break;
        case 6:
            write_to_file(records, num_records);
            exit(0);
        default:
            printf("Invalid choice.\n");
            break;
        }
    }
    return 0;
}