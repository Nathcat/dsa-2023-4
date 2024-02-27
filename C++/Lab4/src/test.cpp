#include <iostream>
#include <Testing.hpp>
#include <BinarySearch.hpp>
#include <InsertionSort.hpp>
#include <MergeSort.hpp>
#include <SelectionSort.hpp>
#include <ArrayMap.hpp>

int main() {
    //  ===================
    //  Binary search tests
    //  ===================
    std::cout << "\n\n\t===================\n\tBinary search tests\n\t===================\n";

    test<int>("Binary search when contained", []() {
        int items[] = {1, 1, 2, 2, 3, 4};
        return create_pair(0, binary_search<int>(1, items, 6));
    }, is_eq);

    test<int>("Binary search when not contained", []() {
        int items[] = {1, 1, 2, 2, 3, 4};
        return create_pair(-1, binary_search<int>(7, items, 6));
    }, is_eq);

    //  ===================
    //  Insertion sort test
    //  ===================
    std::cout << "\n\n\t===================\n\tInsertion sort test\n\t===================\n";

    test<int>("Insertion sort works", []() {
        int items[] = {4, 3, 2, 1};
        insertion_sort(items, 4);

        int res = 1;
        for (int i = 0; i < 3; i++) {
            if (items[i] > items[i+1]) {
                res = 0;
                break;
            }
        }

        return create_pair(1, res);
    }, is_eq);

    //  ===============
    //  Merge sort test
    //  ===============
    std::cout << "\n\n\t===============\n\tMerge sort test\n\t===============\n";

    test<int>("Merge sort works", []() {
        int items[] = {4, 3, 2, 1};
        struct ReturnPair<int> pair = merge_sort(items, 4);
        int* arr = pair.array;
        int n = pair.n;

        int res = 1;
        for (int i = 0; i < n - 1; i++) {
            if (arr[i] > arr[i+1]) {
                res = 0;
                break;
            }
        }

        return create_pair(1, res);
    }, is_eq);

    //  ===================
    //  Selection sort test
    //  ===================
    std::cout << "\n\n\t===================\n\tSelection sort test\n\t===================\n";

    test<int>("Selection sort works", []() {
        int items[] = {4, 3, 2, 1};
        selection_sort(items, 4);

        int res = 1;
        for (int i = 0; i < 3; i++) {
            if (items[i] > items[i+1]) {
                res = 0;
                break;
            }
        }

        return create_pair(1, res);
    }, is_eq);

    //  ==============
    //  Array map test
    //  ==============
    std::cout << "\n\n\t==============\n\tArray map test\n\t==============\n";

    test<int>("Insert on empty map then get length", []() {
        ArrayMap<const char*, int>* map = new ArrayMap<const char*, int >();
        map->insert("Hello world", 1);
        return create_pair(1, map->get_length());
    }, is_eq);

    test<int>("Insert then contains", []() {
        MapRecord<const char*, int> records[] = {
            {"A", 1},
            {"B", 2},
            {"C", 3},
            {"D", 4}
        };
    
        ArrayMap<const char*, int>* map = ArrayMap<const char*, int>::build(records, 4);
        const char* key = "E";
        map->insert(key, 5);
        return create_pair(1, map->contains(key));
    }, is_eq);

    test<int>("Insert then get length", []() {
        MapRecord<const char*, int> records[] = {
            {"A", 1},
            {"B", 2},
            {"C", 3},
            {"D", 4}
        };
    
        ArrayMap<const char*, int>* map = ArrayMap<const char*, int>::build(records, 4);
        int length = map->get_length();
        const char* key = "E";
        map->insert(key, 5);
        return create_pair(length + 1, map->get_length());
    }, is_eq);

    test<int>("Insert then get", []() {
        MapRecord<const char*, int> records[] = {
            {"A", 1},
            {"B", 2},
            {"C", 3},
            {"D", 4}
        };
    
        ArrayMap<const char*, int>* map = ArrayMap<const char*, int>::build(records, 4);
        const char* key = "E";
        map->insert(key, 5);
        return create_pair(5, map->get(key));
    }, is_eq);

    test<int>("Insert then remove", []() {
        MapRecord<const char*, int> records[] = {
            {"A", 1},
            {"B", 2},
            {"C", 3},
            {"D", 4}
        };
    
        ArrayMap<const char*, int>* map = ArrayMap<const char*, int>::build(records, 4);
        const char* key = "E";
        map->insert(key, 5);
        return create_pair(5, map->remove(key));
    }, is_eq);

    test<int>("Insert then remove then contains", []() {
        MapRecord<const char*, int> records[] = {
            {"A", 1},
            {"B", 2},
            {"C", 3},
            {"D", 4}
        };
    
        ArrayMap<const char*, int>* map = ArrayMap<const char*, int>::build(records, 4);
        const char* key = "E";
        map->insert(key, 5);
        map->remove(key);
        return create_pair(0, map->contains(key));
    }, is_eq);

    test<int>("Insert then remove then get", []() {
        MapRecord<const char*, int> records[] = {
            {"A", 1},
            {"B", 2},
            {"C", 3},
            {"D", 4}
        };
    
        ArrayMap<const char*, int>* map = ArrayMap<const char*, int>::build(records, 4);
        const char* key = "E";
        map->insert(key, 5);
        map->remove(key);
        
        try {
            map->get(key);
        } catch (int err) {
            return create_pair(ArrayMap<const char*, int>::KEY_ERROR, err);
        }

        return create_pair(-1, 0);
    }, is_eq);

    test<int>("Insert on empty map then remove then get length", []() {
        ArrayMap<const char*, int>* map = new ArrayMap<const char*, int>();
        const char* key = "A";
        map->insert(key, 1);
        map->remove(key);
        return create_pair(0, map->get_length());
    }, is_eq);

    test<int>("Remove on empty map", []() {
        ArrayMap<const char*, int>* map = new ArrayMap<const char*, int>();
        
        try {
            map->remove("A");
        } catch (int err) {
            return create_pair(ArrayMap<const char*, int>::KEY_ERROR, err);
        }

        return create_pair(-1, 0);
    }, is_eq);

    test<int>("Remove", []() {
        MapRecord<const char*, int> records[] = {
            {"A", 1},
            {"B", 2},
            {"C", 3},
            {"D", 4}
        };
    
        ArrayMap<const char*, int>* map = ArrayMap<const char*, int>::build(records, 4);
        return create_pair(records[0].value, map->remove(records[0].key));
    }, is_eq);

    //  =====================
    //  Sorted array map test
    //  =====================
    std::cout << "\n\n\t=====================\n\tSorted array map test\n\t=====================\n";

    test<int>("Insert on empty map then get length", []() {
        std::cout << "WTF is happening" << std::endl;
        SortedArrayMap<int, const char*>* map = new SortedArrayMap<int, const char*>();
        map->insert(1, "Hello world");
        return create_pair(1, map->get_length());
    }, is_eq);

    test<int>("Insert then contains", []() {
        MapRecord<int, const char*> records[] = {
            {1, "A"},
            {2, "B"},
            {3, "C"},
            {4, "D"}
        };
    
        SortedArrayMap<int, const char*>* map = SortedArrayMap<int, const char*>::build(records, 4);
        int key = 5;
        map->insert(key, "E");
        return create_pair(1, map->contains(key));
    }, is_eq);

    test<int>("Insert then get length", []() {
        MapRecord<int, const char*> records[] = {
            {1, "A"},
            {2, "B"},
            {3, "C"},
            {4, "D"}
        };
    
        SortedArrayMap<int, const char*>* map = SortedArrayMap<int, const char*>::build(records, 4);
        int length = map->get_length();
        int key = 5;
        map->insert(key, "E");
        return create_pair(length + 1, map->get_length());
    }, is_eq);

    test<const char*>("Insert then get", []() {
        MapRecord<int, const char*> records[] = {
            {1, "A"},
            {2, "B"},
            {3, "C"},
            {4, "D"}
        };
    
        SortedArrayMap<int, const char*>* map = SortedArrayMap<int, const char*>::build(records, 4);
        int key = 5;
        const char* val = "E";
        map->insert(key, val);
        return create_pair(val, map->get(key));
    }, is_eq);

    test<const char*>("Insert then remove", []() {
        MapRecord<int, const char*> records[] = {
            {1, "A"},
            {2, "B"},
            {3, "C"},
            {4, "D"}
        };
    
        SortedArrayMap<int, const char*>* map = SortedArrayMap<int, const char*>::build(records, 4);
        int key = 5;
        const char* val = "E";
        map->insert(key, val);
        return create_pair(val, map->remove(key));
    }, is_eq);

    test<int>("Insert then remove then contains", []() {
        MapRecord<int, const char*> records[] = {
            {1, "A"},
            {2, "B"},
            {3, "C"},
            {4, "D"}
        };
    
        SortedArrayMap<int, const char*>* map = SortedArrayMap<int, const char*>::build(records, 4);
        int key = 5;
        const char* val = "E";
        map->insert(key, val);
        map->remove(key);
        return create_pair(0, map->contains(key));
    }, is_eq);

    test<int>("Insert then remove then get", []() {
        MapRecord<int, const char*> records[] = {
            {1, "A"},
            {2, "B"},
            {3, "C"},
            {4, "D"}
        };
    
        SortedArrayMap<int, const char*>* map = SortedArrayMap<int, const char*>::build(records, 4);
        int key = 5;
        const char* val = "E";
        map->insert(key, val);
        map->remove(key);
        
        try {
            map->get(key);
        } catch (int err) {
            return create_pair(SortedArrayMap<int, const char*>::KEY_ERROR, err);
        }

        return create_pair(-1, 0);
    }, is_eq);

    test<int>("Insert on empty map then remove then get length", []() {
        SortedArrayMap<int, const char*>* map = new SortedArrayMap<int, const char*>();
        int key = 1;
        const char* val = "A";
        map->insert(key, val);
        map->remove(key);
        return create_pair(0, map->get_length());
    }, is_eq);

    test<int>("Remove on empty map", []() {
        SortedArrayMap<int, const char*>* map = new SortedArrayMap<int, const char*>();
        
        try {
            map->remove(1);
        } catch (int err) {
            return create_pair(SortedArrayMap<int, const char*>::KEY_ERROR, err);
        }

        return create_pair(-1, 0);
    }, is_eq);

    test<const char*>("Remove", []() {
        MapRecord<int, const char*> records[] = {
            {1, "A"},
            {2, "B"},
            {3, "C"},
            {4, "D"}
        };
    
        SortedArrayMap<int, const char*>* map = SortedArrayMap<int, const char*>::build(records, 4);
        return create_pair(records[0].value, map->remove(records[0].key));
    }, is_eq);
}