#include <iostream>
#include <vector>
#include <algorithm>

void updatedInventory(std::vector<std::string>& inventory, const std::vector<std::string>& shipment, const std::vector<std::string>& soldOut) {
    for (const auto& item : soldOut) inventory.erase(std::remove(inventory.begin(), inventory.end(), item), inventory.end());
    for (const auto& item : shipment) if (std::find(inventory.begin(), inventory.end(), item) == inventory.end()) inventory.push_back(item);
}

void print(const std::vector<std::string>& vec) {
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) std::cout << "\"" << vec[i] << "\"" << (i < vec.size() - 1 ? ", " : "");
    std::cout << "]\n";
}

int main() {
    std::vector<std::string> inventory = {"apples", "bananas", "oranges", "pears"};
    std::vector<std::string> shipment = {"kiwis", "bananas", "grapes"};
    std::vector<std::string> soldOut = {"apples", "oranges"};

    std::cout << "Current Inventory: "; print(inventory);
    std::cout << "Shipment: "; print(shipment);
    std::cout << "Sold-out items: "; print(soldOut); std::cout << "\n";

    updatedInventory(inventory, shipment, soldOut);

    std::cout << "Updated Inventory: "; print(inventory);
    
    return 0;
}