//
// Lab Test 3
// Sadie Simek
// 2.19.2026
//

#include <utmp.h>   // utmp header for utmp structure and UTMP_FILE location
#include <fcntl.h>  // file control library for open function
#include <unistd.h> // library for read and close functions
#include <stdio.h>  // standard I/O library
#define SHOWHOST 1; // enable host display (1 = on, 0 = off)

/*
 *  show info()
 *   displays contents of the utmp struct in human readable form
 *   *note* these sizes should not be hardwired
 */

void show_info(struct utmp *utbufp) // Function takes a pointer to utmp structure as input
{
    printf("%-8.8s\n", utbufp->ut_user); // Print username, limited to 8 characters, left-justified
                                       // meaning, add padding to the right-hand side of the string
    printf(" ");                       // Add a space between fields
    printf("%-8.8s\n", utbufp->ut_line); // Print terminal line (e.g., tty1), limited to 8 charact>
    printf(" ");

#ifdef SHOWHOST
    printf("(%s\n)", utbufp->ut_host); // Print hostname in parentheses if SHOWHOST is defined
#endif
    printf("\n"); // Move to a new line after each record

    // Added 2.19.2026 from in-class notes
    printf("%s %s %s \n", utbufp->ut_user, utbufp->ut_line, utbufp->ut_host);
}
int main()
{
//Dereferencing causes seg fault
    struct utmp current_record;         // a utmp structure to store each record read from file
    int utmpfd;                          // file descriptor for the utmp file
                                         // This also acts as an pointer to the file's location,
                                         // which we will learn in a future session
    int reclen = sizeof(current_record); // Calculate the size of the utmp structure for reading

    if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1)
    {                      // Open utmp file in read-only mode; fopen returns -1 if failure happens
        perror(UTMP_FILE); // Print error message if file opening fails, using UTMP_FILE>
        return 1;          // Return 1 to indicate error and exit
    }

    while (read(utmpfd, &current_record, reclen) == reclen) // Read utmp records until end or error
    {
        //**** We will come back to this in the future!
        //Pass the memory address instead of adding pointer in struct utmp declaration
        //
        show_info(&current_record);
    }

    close(utmpfd); // Close the utmp file descriptor to free resources
    return 0;      // Return 0 to indicate successful execution of the code
}
