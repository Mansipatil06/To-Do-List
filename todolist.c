#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EVENTS 100

// Define a structure to represent an event
typedef struct {
    char description[100];
    char date[20];
    int priority; // Priority level (0 - low, 1 - medium, 2 - high)
    char reminder[20]; // Reminder date and time (e.g., DD/MM/YYYY HH:MM)
} Event;

// Function to add an event
void addEvent(Event events[], int* eventCount, const char* description, const char* date, int priority, const char* reminder) {
    if (*eventCount >= MAX_EVENTS) {
        printf("Event list is full. Cannot add more events.\n");
        return;
    }

    strcpy(events[*eventCount].description, description);
    strcpy(events[*eventCount].date, date);
    events[*eventCount].priority = priority;
    strcpy(events[*eventCount].reminder, reminder);
    (*eventCount)++;
    printf("Event added: %s on %s (Priority: %d, Reminder: %s)\n", description, date, priority, reminder);
}

// Function to display events with filters
void displayEvents(const Event events[], int eventCount, int minPriority, const char* searchString) {
    if (eventCount == 0) {
        printf("No events to display.\n");
    } else {
        printf("Events:\n");
        for (int i = 0; i < eventCount; i++) {
            if (events[i].priority >= minPriority &&
                (searchString == NULL || strstr(events[i].description, searchString) != NULL)) {
                printf("%d. %s on %s (Priority: %d, Reminder: %s)\n", i + 1, events[i].description, events[i].date, events[i].priority, events[i].reminder);
            }
        }
    }
}

int main() {
    Event events[MAX_EVENTS];
    int eventCount = 0;

    while (1) {
        printf("\nOptions:\n");
        printf("1. Add Event\n");
        printf("2. Display Events\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter event description: ");
                char description[100];
                scanf(" %[^\n]", description);

                printf("Enter event date (e.g., DD/MM/YYYY): ");
                char date[20];
                scanf("%s", date);

                printf("Enter event priority (0 - low, 1 - medium, 2 - high): ");
                int priority;
                scanf("%d", &priority);

                printf("Enter event reminder date and time (e.g., DD/MM/YYYY HH:MM), or leave blank: ");
                char reminder[20];
                scanf(" %[^\n]", reminder);

                addEvent(events, &eventCount, description, date, priority, reminder);
                break;
            case 2:
                printf("Display Options:\n");
                printf("1. Display All Events\n");
                printf("2. Filter by Priority\n");
                printf("3. Search by Description\n");
                printf("Enter your display choice: ");

                int displayChoice;
                scanf("%d", &displayChoice);

                switch (displayChoice) {
                    case 1:
                        displayEvents(events, eventCount, 0, NULL);
                        break;
                    case 2:
                        printf("Enter minimum priority (0 - low, 1 - medium, 2 - high): ");
                        int minPriority;
                        scanf("%d", &minPriority);
                        displayEvents(events, eventCount, minPriority, NULL);
                        break;
                    case 3:
                        printf("Enter a search string: ");
                        char searchString[100];
                        scanf(" %[^\n]", searchString);
                        displayEvents(events, eventCount, 0, searchString);
                        break;
                    default:
                        printf("Invalid display choice. Please select a valid option.\n");
                }
                break;
            case 3:
                return 0;
            default:
                printf("Invalid choice. Please select a valid option.\n");
                break;
        }
    }

    return 0;
}
