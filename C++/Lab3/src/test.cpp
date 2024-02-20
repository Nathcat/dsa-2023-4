#include <stdio.h>
#include <CircularDynamicArrayList.hpp>
#include <iostream>



int main() {
    const char* items[] = {"Hello", "World", "It's", "Me"};
    CircularDynamicArrayList<const char*>* list = CircularDynamicArrayList<const char*>::build<const char*>(items, 4);
    
    int insert_index = 2;
    int late_index = 1;
    const char* item = "Wow";
    const char* late_item = list->get_at(insert_index + late_index);
    list->insert_at(insert_index, item);
    
    std::cout << "Expect " << late_item << std::endl;
    std::cout << "Got " << list->get_at(insert_index + 1 + late_index) << std::endl;

    return 0;
}