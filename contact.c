#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook, int sortCriteria) 
{ 
    if(addressBook->contactCount == 0) {
        printf("No contacts to display.\n");
        return;
    }

    // Bubble sort based on sortCriteria
   for(int i = 0; i < addressBook->contactCount - 1; i++) {
        for(int j = 0; j < addressBook->contactCount - i - 1; j++) {
            // strcmp returns negative if first < second, positive if first > second, 0 if equal
            if(strcmp(addressBook->contacts[j].name, addressBook->contacts[j+1].name) > 0) {
                // Swap contacts
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j+1];
                addressBook->contacts[j+1] = temp;
            }
        }
    }

    printf("%-20s %-15s %-25s\n", "Name", "Phone", "Email");
    printf("---------------------------------------------------------\n");

    for(int i = 0; i < addressBook->contactCount; i++) {
        printf("%-20s %-15s %-25s\n",
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }
}


void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);

    // Load contcts from file in initilization
    loadContactsFromFile(addressBook);
    
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

// validation functions
int ValidName(const char *name) //name
{
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (!(name[i] >= 'A' && name[i] <= 'Z') &&
            !(name[i] >= 'a' && name[i] <= 'z') &&
            name[i] != ' ')
        {
            return 0;
        }
    }
    return 1;
}

int ValidPhone(const char *phone) // phone
{
    if (strlen(phone) != 10)
        return 0;

    for (int i = 0; i < 10; i++)
    {
        if (phone[i] < '0' || phone[i] > '9')
            return 0;
    }
    return 1;
}

int ValidEmail(const char *email) //email
{
    int len = strlen(email);

    // must end with @gmail.com
    if (len < 10 || strcmp(email + len - 10, "@gmail.com") != 0)
        return 0;

    for (int i = 0; email[i] != '\0'; i++)
    {
        if (!(email[i] >= 'a' && email[i] <= 'z') &&
            !(email[i] >= '0' && email[i] <= '9') &&
            email[i] != '.' &&
            email[i] != '_' &&
            email[i] != '@')
        {
            return 0;
        }
    }
    return 1;
}

void createContact(AddressBook *addressBook)
{
    // Check address book capacity
       printf("\n========== CREATE NEW CONTACT ==========\n");

    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("❌ Address book is full.\n");
        return;
    }

    char name[50], phone[50], email[50];

    while (1)
    {
        printf("Enter Name  : ");
        scanf(" %[^\n]", name);  // Read name including spaces
        
        // Validate name (alphabets and spaces only)
        if (!ValidName(name))
        {
            printf("❌ Invalid name (alphabets and spaces only).\n");
            continue;
        }
        break; // Exit loop if valid
    }
    
    //-------------------------------------------------
    // Read, validate and check duplicate phone number
    //-------------------------------------------------

    while (1)
    {
        int duplicate = 0; // Flag to check duplicate phone

        printf("Enter Phone : ");
        scanf(" %[^\n]", phone); // Read phone number

        if (!ValidPhone(phone))
        {
            printf("❌ Invalid phone number (10 digits only).\n");
            continue;
        }

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].phone, phone) == 0)
            {
                printf("❌ Phone number already exists.\n");
                duplicate = 1;
                break;
            }
        }

        if (!duplicate)
            break;   // Exit loop if phone is valid and unique
    }

    //-------------------------------------------------
    // Read, validate and check duplicate email ID
    //-------------------------------------------------

    while (1)
    {
        int duplicate = 0; // Flag to check duplicate email

        printf("Enter Email : ");
        scanf(" %[^\n]", email);
        
        // Validate email format
        if (!ValidEmail(email))
        {
            printf("❌ Invalid email (lowercase, @gmail.com only).\n");
            continue;
        }
        
        // Check for duplicate email ID
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].email, email) == 0)
            {
                printf("❌ Email already exists.\n");
                duplicate = 1;
                break;
            }
        }

        if (!duplicate) // Exit loop if email is valid and unique
            break;  
    }
    
    //-------------------------------------------------
    // Store contact details into address book
    //-------------------------------------------------

    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email);

    addressBook->contactCount++; // Increment contact count
    
     // Display success message
    printf("✅ Contact created successfully.\n");
}


void searchContact(AddressBook *addressBook) 
{
    int choice; // Variable to store user choice
    char searchTerm[50]; // Variable to store search input
    int flag = 0; // Flag to count matching contacts
    
    printf("1. Name  2. Phone  3. Email\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    // Ask input based on selected option
    if(choice == 1) {
        printf("Enter name: ");
    }
    else if(choice == 2) {
        printf("Enter phone number: ");
    }
    else if(choice == 3) {
        printf("Enter email: ");
    }
    else {
        printf("Invalid choice!\n"); // Handle invalid input
        return;
    }
    
    scanf("%s", searchTerm); // Read search term from user
    
    printf("\n--- Search Results ---\n");
    printf("Name\t\tPhone\t\tEmail\n");
    printf("---------------------------------------------\n");
    
    // Loop through all contacts
    for(int i = 0; i < addressBook->contactCount; i++) {
        int match = 0; // Variable to check match
        
         // Search by name (partial match)
        if(choice == 1) {
            if(strstr(addressBook->contacts[i].name, searchTerm) != NULL) {
                match = 1;
            }
        } // Search by phone (exact match)
        else if(choice == 2) {
            if(strcmp(addressBook->contacts[i].phone, searchTerm) == 0) {
                match = 1;
            }
        } // Search by email (exact match)
        else if(choice == 3) {
            if(strcmp(addressBook->contacts[i].email, searchTerm) == 0) {
                match = 1;
            }
        } // Print contact details if match is found
        if(match) {
            printf("%s\t\t%s\t%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
            flag++;
        }
    } 
    // Display result based on match count
    if(flag == 0) {
        printf("No contacts found matching '%s'\n", searchTerm);
    } else {
        printf("\nTotal matches found: %d\n", flag);
    }
}

void editContact(AddressBook *addressBook)
{
	{
    //Search the contact and edit the contact 
    int choice; // Stores search criteria choice
    char searchTerm[50]; // Stores value to search
    char newValue[50]; // Stores updated value
    int found = 0; // Flag to check if contact is found
    
    // Display search options
    printf("1. Name  2. Phone  3. Email\n");
    printf("Enter search criteria: ");
    scanf("%d", &choice); // Read user choice
    
    // Prompt input based on choice
    if(choice == 1) {
        printf("Enter name to search: ");
    }
    else if(choice == 2) {
        printf("Enter phone number to search: ");
    }
    else if(choice == 3) {
        printf("Enter email to search: ");
    }
    else {
        printf("Invalid choice!\n");
        return;
    }
    
    scanf("%s", searchTerm); // Read search term
    
    for(int i = 0; i < addressBook->contactCount; i++) {
        int match = 0;  // Flag for match
        
        if(choice == 1 && strstr(addressBook->contacts[i].name, searchTerm) != NULL) {
            match = 1;
        }
        else if(choice == 2 && strcmp(addressBook->contacts[i].phone, searchTerm) == 0) {
            match = 1;
        }
        else if(choice == 3 && strcmp(addressBook->contacts[i].email, searchTerm) == 0) {
            match = 1;
        }
        
        // If contact is found
        if(match) {
            printf("\nContact found: %s | %s | %s\n", 
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
            
            // Ask field to edit
            printf("What do you want to edit? (1. Name  2. Phone  3. Email): ");
            int editChoice;
            scanf("%d", &editChoice);

            // Edit selected field
            if(editChoice == 1) {
                printf("Enter new name: ");
                scanf("%s", newValue);
                strcpy(addressBook->contacts[i].name, newValue);
            }
            else if(editChoice == 2) {
                printf("Enter new phone: ");
                scanf("%s", newValue);
                strcpy(addressBook->contacts[i].phone, newValue);
            }
            else if(editChoice == 3) {
                printf("Enter new email: ");
                scanf("%s", newValue);
                strcpy(addressBook->contacts[i].email, newValue);
            }
            
            printf("Contact updated successfully!\n");
            found = 1; // Mark contact found
            break;
        }
    }
    // If contact not found
    if(!found) {
        printf("Contact not found!\n");
    }
}
    
}

void deleteContact(AddressBook *addressBook)
{
    int choice; // Stores delete criteria choice
    char searchTerm[50]; // Stores input value for search
    int found = 0; // Flag to indicate deletion status
    
    // Display delete options
    printf("Delete by:\n");
    printf("1. Name  2. Phone  3. Email\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    // Prompt input based on delete choice
    if(choice == 1) {
        printf("Enter letters from name to search: ");
    }
    else if(choice == 2) {
        printf("Enter phone number to delete: ");
    }
    else if(choice == 3) {
        printf("Enter email to delete: ");
    }
    else {
        printf("Invalid choice!\n");
        return;
    }

    scanf("%s", searchTerm); // Read search term

    //---------------------------------------------------------------
    //        NAME DELETE with partial match and user selection
    //---------------------------------------------------------------
    if(choice == 1)
    {
        int matchIndexes[50]; // Stores indexes of matched contacts
        int matchCount = 0; // Number of matched contacts


        // Collect partial matches
        for(int i = 0; i < addressBook->contactCount; i++)
        {
            if(strstr(addressBook->contacts[i].name, searchTerm) != NULL)
            {
                matchIndexes[matchCount++] = i;
            }
        }
        
        // If no matching names found
        if(matchCount == 0) {
            printf("No matching names found!\n");
            return;
        }

        // Show matching contacts
        printf("\nMatching Contacts:\n");
        for(int i = 0; i < matchCount; i++)
        {
            int idx = matchIndexes[i];
            printf("%d. %s | %s | %s\n",
                   i+1,
                   addressBook->contacts[idx].name,
                   addressBook->contacts[idx].phone,
                   addressBook->contacts[idx].email);
        }

        // Ask which contact to delete
        int delChoice;
        printf("\nEnter the number of contact to delete: ");
        scanf("%d", &delChoice);

        if(delChoice < 1 || delChoice > matchCount) {
            printf("Invalid selection!\n");
            return;
        }

        int delIndex = matchIndexes[delChoice - 1]; // Actual index to delete

        // Delete by shifting
        for(int j = delIndex; j < addressBook->contactCount - 1; j++) {
            addressBook->contacts[j] = addressBook->contacts[j + 1];
        }

        addressBook->contactCount--;  // Decrease contact count
        printf("Contact deleted successfully!\n");
        
        // Display updated contact list
        printf("\nUpdated Contact List:\n");
        listContacts(addressBook, 1);
        return;
    }

    
    //PHONE and EMAIL delete (EXACT MATCH – original logic)

    for(int i = 0; i < addressBook->contactCount; i++) {
        int match = 0; // Flag for exact match

        // Check phone or email exact match
        if(choice == 2 && strcmp(addressBook->contacts[i].phone, searchTerm) == 0)
            match = 1;
        else if(choice == 3 && strcmp(addressBook->contacts[i].email, searchTerm) == 0)
            match = 1;
          
        // If match found, delete contact    
        if(match) {
            for(int j = i; j < addressBook->contactCount - 1; j++) {
                addressBook->contacts[j] = addressBook->contacts[j + 1];
            }

            addressBook->contactCount--; // Reduce contact count
            printf("Contact deleted successfully!\n");

            found = 1; // Mark deletion successful
            break;
        }
    }
     
    // Display final result
    if(!found)
        printf("Contact not found!\n");
    else {
        printf("\nUpdated Contact List:\n");
        listContacts(addressBook, 1);
    }
}
