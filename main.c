/* Name: Sudarshan V
Description: Address book

(Create Contact)
Input:
User enters:
1. Name
2. Phone number
3. Email ID

Output:
Contact details have been successfully stored in the address book.

(List Contact)
Input:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Save contacts
7. Exit

Input: 5

Output:
All saved contacts are displayed in sorted order by name.

(Edit Contact)
Input:
User selects search option:
1. Name
2. Phone
3. Email
Then, enter the search value.

Output:
If contact is found, contact details are displayed.
Otherwise, the message "No contacts found matching" is printed.

(Delete Contact)
Input:
User selects the delete option:
1. Name
2. Phone
3. Email
Then, enter the value.

Output:
If contact exists, it is deleted successfully.
Otherwise, the message "No contacts found matching" is displayed.
*/

#include <stdio.h>
#include "contact.h"

int main() {
    int choice, sortChoice=0;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	  printf("6. Save contacts\n");		
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:          
                listContacts(&addressBook, sortChoice);
                break;
            case 6:
                printf("Saving\n");
                saveContactsToFile(&addressBook);
                break;   
            case 7:
                printf("Exiting\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);
       return 0;
}
