#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Enums
enum ItemType {
    TYPE_LOST,
    TYPE_FOUND
};

enum ItemStatus {
    STATUS_LOST,
    STATUS_FOUND,
    STATUS_CLAIMED,
    STATUS_RETURNED
};

// Struct
struct Item {
    int id;
    ItemType type;
    ItemStatus status;
    string name;
    string description;
    string location;
    string dateReported;
    vector<string> tags;
};

// Global storage
vector<Item> items;
int nextID = 1;

// function to split tags
vector<string> splitTags(string input) {
    vector<string> result;
    string temp = "";

    for (int i = 0; i < input.length(); i++) {
        if (input[i] == ',') {
            result.push_back(temp);
            temp = "";
        } else if (input[i] != ' ') {
            temp += input[i];
        }
    }
    result.push_back(temp);
    return result;
}

// Add lost item
void addLostItem() {
    Item item;
    item.id = nextID++;
    item.type = TYPE_LOST;
    item.status = STATUS_LOST;

    cout << "Item name: ";
    getline(cin, item.name);

    cout << "Description: ";
    getline(cin, item.description);

    cout << "Location: ";
    getline(cin, item.location);

    cout << "Date: ";
    getline(cin, item.dateReported);

    string tagInput;
    cout << "Tags (comma separated): ";
    getline(cin, tagInput);
    item.tags = splitTags(tagInput);

    items.push_back(item);
    cout << "Lost item added with ID: " << item.id << endl;
}

// Add found item
void addFoundItem() {
    Item item;
    item.id = nextID++;
    item.type = TYPE_FOUND;
    item.status = STATUS_FOUND;

    cout << "Item name: ";
    getline(cin, item.name);

    cout << "Description: ";
    getline(cin, item.description);

    cout << "Location: ";
    getline(cin, item.location);

    cout << "Date: ";
    getline(cin, item.dateReported);

    string tagInput;
    cout << "Tags (comma separated): ";
    getline(cin, tagInput);
    item.tags = splitTags(tagInput);

    items.push_back(item);
    cout << "Found item added with ID: " << item.id << endl;
}

// Matching lost items with found items
void viewMatches() {
    int lostID;
    cout << "Enter Lost Item ID: ";
    cin >> lostID;
    cin.ignore();

    Item* lostItem = nullptr;

    for (int i = 0; i < items.size(); i++) {
        if (items[i].id == lostID && items[i].type == TYPE_LOST) {
            lostItem = &items[i];
        }
    }

    if (lostItem == nullptr) {
        cout << "Lost item not found.\n";
        return;
    }

    cout << "\nPossible matches:\n";

    for (int i = 0; i < items.size(); i++) {
        if (items[i].type == TYPE_FOUND && items[i].status == STATUS_FOUND) {
            int matchCount = 0;

            for (int j = 0; j < lostItem->tags.size(); j++) {
                for (int k = 0; k < items[i].tags.size(); k++) {
                    if (lostItem->tags[j] == items[i].tags[k]) {
                        matchCount++;
                    }
                }
            }

            if (matchCount > 0) {
                cout << "Found Item ID: " << items[i].id << endl;
                cout << "Name: " << items[i].name << endl;
                cout << "Matching tags: " << matchCount << endl;
                cout << "---------------------\n";
            }
        }
    }
}

// Mark claimed/returned
void updateStatus() {
    int id;
    cout << "Enter Item ID: ";
    cin >> id;
    cin.ignore();

    for (int i = 0; i < items.size(); i++) {
        if (items[i].id == id) {
            if (items[i].status == STATUS_FOUND || items[i].status == STATUS_LOST) {
                items[i].status = STATUS_CLAIMED;
                cout << "Item marked as CLAIMED.\n";
            } else if (items[i].status == STATUS_CLAIMED) {
                items[i].status = STATUS_RETURNED;
                cout << "Item marked as RETURNED.\n";
            } else {
                cout << "Item already returned.\n";
            }
            return;
        }
    }

    cout << "Item not found.\n";
}

// Export summary 
void exportSummary() {
    ofstream file("weekly_summary.txt");

    int lost = 0, found = 0, claimed = 0, returned = 0;

    for (int i = 0; i < items.size(); i++) {
        if (items[i].type == TYPE_LOST) lost++;
        if (items[i].type == TYPE_FOUND) found++;
        if (items[i].status == STATUS_CLAIMED) claimed++;
        if (items[i].status == STATUS_RETURNED) returned++;
    }

    file << "WEEKLY SUMMARY\n";
    file << "Lost: " << lost << endl;
    file << "Found: " << found << endl;
    file << "Claimed: " << claimed << endl;
    file << "Returned: " << returned << endl;

    file.close();
    cout << "Summary exported to weekly_summary.txt\n";
}

// Main menu
int main() {
    int choice;

    while (true) {
        cout << "\n====== LOST & FOUND ======\n";
        cout << "1. Report Lost Item\n";
        cout << "2. Report Found Item\n";
        cout << "3. View Possible Matches\n";
        cout << "4. Mark Item as Claimed/Returned\n";
        cout << "5. Export Weekly Summary\n";
        cout << "6. Exit\n";
        cout << "Choose: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            addLostItem();
        } 
        else if (choice == 2) {
            addFoundItem();
        } 
        else if (choice == 3) {
            viewMatches();
        } 
        else if (choice == 4) {
            updateStatus();
        } 
        else if (choice == 5) {
            exportSummary();
        } 
        else if (choice == 6) {
            cout << "Goodbye!\n";
            break;
        } 
        else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
