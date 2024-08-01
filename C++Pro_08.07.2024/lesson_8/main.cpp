#include <iostream> 
#include <vector> 
#include <string> 
#include <algorithm> // For std::sort 
 
struct Person { 
    std::string first_name; 
    std::string last_name; 
    int age; 
}; 
 
// Function to print the list of people 
void printPeople(const std::vector<Person>& people) { 
    for (const auto& person : people) { 
        std::cout << person.first_name << " " << person.last_name << " (" << person.age << ")\n"; 
    } 
    std::cout << std::endl; 
} 
 
int main() { 
    // Example data for sorting 
    std::vector<Person> people = { 
        {"Yoda", "", 900}, 
        {"Obi-Wan", "Kenobi", 38}, 
        {"Leia", "Organa", 25}, 
        {"Anakin", "Skywalker", 22} 
    }; 
 
    // Sort by first_name 
    std::sort(people.begin(), people.end(), [](const Person& a, const Person& b) { 
        return a.first_name < b.first_name; 
    }); 
    std::cout << "Sorted by first_name:\n"; 
    printPeople(people); 
 
    // Sort by last_name 
    std::sort(people.begin(), people.end(), [](const Person& a, const Person& b) { 
        return a.last_name < b.last_name; 
    }); 
    std::cout << "Sorted by last_name:\n"; 
    printPeople(people); 
 
    // Sort by age 
    std::sort(people.begin(), people.end(), [](const Person& a, const Person& b) { 
        return a.age < b.age; 
    }); 
    std::cout << "Sorted by age:\n"; 
    printPeople(people); 
 
    return 0; 
}
