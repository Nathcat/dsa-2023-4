#include <Testing.hpp>
#include <Numberify.hpp>
#include <HashFunction.hpp>
#include <ChainingHashMap.hpp>


int main() {
    //
    //  Test hash function and numberify
    //
    test<unsigned long long>("Test to_long", []() {
        int v = 5;

        return create_pair(5ULL, to_long((unsigned char*) &v, sizeof(int)));
    }, is_eq);

    test<unsigned long long>("Hash ex. 1", []() {
        int v = 5;
        unsigned long long v_long = to_long((unsigned char*) &v, sizeof(int));
        HashFunction* f = new HashFunction(v_long + 1);
        f->a = 1;
        f->b = 0;
        return create_pair((unsigned long long) v, f->hash(&v));
    }, is_eq);

    test<unsigned long long>("Hash ex. 2", []() {
        int v = 5;
        int offset = rand() % PRIME;
        unsigned long long v_long = to_long((unsigned char*) &v, sizeof(int));
        HashFunction* f = new HashFunction(v_long + 1 + offset);
        f->a = 1;
        f->b = offset;
        return create_pair(v_long + offset, f->hash(&v));
    }, is_eq);

    test<unsigned long long>("Hash ex. 3", []() {
        int v = 5;
        int offset = rand() % PRIME;
        int size = rand() + 1;
        unsigned long long v_long = to_long((unsigned char*) &v, sizeof(int));
        HashFunction* f = new HashFunction(size);
        f->a = 1;
        f->b = offset;
        return create_pair((v_long + offset) % size, f->hash(&v));
    }, is_eq);

    test<unsigned long long>("Hash ex. 4", []() {
        int v = 5;
        unsigned long long v_long = to_long((unsigned char*) &v, sizeof(int));
        HashFunction* f = new HashFunction(v_long + 1);
        f->a = 1;
        f->b = PRIME;
        return create_pair(v_long, f->hash(&v));
    }, is_eq);

    test<bool>("Test hashable comparisons 1", []() {
        int vA = 5;
        int vB = 5;
        Hashable<int> a(&vA);
        Hashable<int> b(&vB);
        return create_pair(true, a == b);
    }, is_eq);

    test<bool>("Test hashable comparisons 2", []() {
        int vA = 5;
        int vB = 6;
        Hashable<int>* a = new Hashable<int>(&vA);
        Hashable<int>* b = new Hashable<int>(&vB);

        return create_pair(false, a == b);
    }, is_eq);

    test<bool>("Test hashable comparisons 3", []() {
        int vA = 5;
        int vB = 5;
        Hashable<int>* a = new Hashable<int>(&vA);
        Hashable<int>* b = new Hashable<int>(&vB);
        return create_pair(true, *a == *b);
    }, is_eq);

    test<bool>("Test hashable comparisons 4", []() {
        int vA = 5;
        int vB = 6;
        Hashable<int>* a = new Hashable<int>(&vA);
        Hashable<int>* b = new Hashable<int>(&vB);
        return create_pair(false, *a == *b);
    }, is_eq);

    test<bool>("Test hashable comparisons 5", []() {
        const char* vA = "Hello world";
        const char* vB = "Hello world";
        Hashable<const char*> a(&vA);
        Hashable<const char*> b(&vB);
        return create_pair(true, a == b);
    }, is_eq);

    test<bool>("Test hashable comparisons 6", []() {
        const char* vA = "Hello world";
        const char* vB = "Hello";
        Hashable<const char*> a(&vA);
        Hashable<const char*> b(&vB);
        return create_pair(false, a == b);
    }, is_eq);

    test<bool>("Test hashable comparisons 7", []() {
        const char* vA = "Hello world";
        const char* vB = "Hello world";
        Hashable<const char*>* a = new Hashable<const char*>(&vA);
        Hashable<const char*>* b = new Hashable<const char*>(&vB);
        return create_pair(true, *a == *b);
    }, is_eq);

    test<bool>("Test hashable comparisons 8", []() {
        const char* vA = "Hello world";
        const char* vB = "Hello";
        Hashable<const char*>* a = new Hashable<const char*>(&vA);
        Hashable<const char*>* b = new Hashable<const char*>(&vB);
        return create_pair(false, *a == *b);
    }, is_eq);


    //
    //  Chaining hash map tests
    //
    test<bool>("Contains on empty map", []() {
        ChainingHashMap<int, const char*>* map = new ChainingHashMap<int, const char*>();
        int v = 5;
        Hashable<int> key(&v);
        return create_pair(false, map->contains(&key));
    }, is_eq);

    test<bool>("Contains", []() {
        const char* keys[] = {"A", "B", "C", "D", "E"};
        MapRecord<Hashable<const char*>, int> records[] = {
            {Hashable<const char*>::create(keys), 1},
            {Hashable<const char*>::create(keys + 1), 2},
            {Hashable<const char*>::create(keys + 2), 3},
            {Hashable<const char*>::create(keys + 3), 4},
            {Hashable<const char*>::create(keys + 4), 5}
        };

        ChainingHashMap<const char*, int>* map = ChainingHashMap<const char*, int>::build(records, 5, 2);
        MapRecord<Hashable<const char*>, int> v = records[rand() % 5];
        return create_pair(true, map->contains(&v.key));
    }, is_eq);

    test<bool>("Contains not", []() {
        const char* keys[] = {"A", "B", "C", "D", "E"};
        MapRecord<Hashable<const char*>, int> records[] = {
            {Hashable<const char*>::create(keys), 1},
            {Hashable<const char*>::create(keys + 1), 2},
            {Hashable<const char*>::create(keys + 2), 3},
            {Hashable<const char*>::create(keys + 3), 4},
            {Hashable<const char*>::create(keys + 4), 5}
        };

        ChainingHashMap<const char*, int>* map = ChainingHashMap<const char*, int>::build(records, 5, 2);
        const char* vK = "F";
        MapRecord<Hashable<const char*>, int> v = {Hashable<const char*>::create(&vK), 6};
        return create_pair(false, map->contains(&v.key));
    }, is_eq);

    test<int>("Contains then insert then get length", []() {
        const char* keys[] = {"A", "B", "C", "D", "E"};
        MapRecord<Hashable<const char*>, int> records[] = {
            {Hashable<const char*>::create(keys), 1},
            {Hashable<const char*>::create(keys + 1), 2},
            {Hashable<const char*>::create(keys + 2), 3},
            {Hashable<const char*>::create(keys + 3), 4},
            {Hashable<const char*>::create(keys + 4), 5}
        };

        ChainingHashMap<const char*, int>* map = ChainingHashMap<const char*, int>::build(records, 5, 2);
        const char* vK = "F";
        MapRecord<Hashable<const char*>, int> v = {Hashable<const char*>::create(&vK), 6};
        int length = map->getLength();
        map->insert(&v.key, v.value);
        return create_pair(length + 1, map->getLength());
    }, is_eq);

    test<int>("Get length", []() {
        const char* keys[] = {"A", "B", "C", "D", "E"};
        MapRecord<Hashable<const char*>, int> records[] = {
            {Hashable<const char*>::create(keys), 1},
            {Hashable<const char*>::create(keys + 1), 2},
            {Hashable<const char*>::create(keys + 2), 3},
            {Hashable<const char*>::create(keys + 3), 4},
            {Hashable<const char*>::create(keys + 4), 5}
        };

        ChainingHashMap<const char*, int>* map = ChainingHashMap<const char*, int>::build(records, 5, 2);
        return create_pair(5, map->getLength());
    }, is_eq);

    test<int>("Get on empty map", []() {
        ChainingHashMap<const char*, int>* map = new ChainingHashMap<const char*, int>();

        try {
            const char* s = "Hello world";
            map->get(new Hashable<const char*>(&s));
        } catch (int err) {
            return create_pair(ChainingHashMap<const char*, int>::KEY_ERROR, err);
        }

        return create_pair(-1, 1);
    }, is_eq);

    test<int>("Insert on empty map then get length", []() {
        ChainingHashMap<const char*, int>* map = new ChainingHashMap<const char*, int>();

        const char* s = "Hello world";
        map->insert(new Hashable<const char*>(&s), 1);

        return create_pair(1, map->getLength());
    }, is_eq);

    test<int>("Insert twice on empty map then get length", []() {
        const char* keys[] = {"A"}; 

        ChainingHashMap<const char*, int>* map = new ChainingHashMap<const char*, int>();
        map->insert(new Hashable<const char*>(keys), 1);
        map->insert(new Hashable<const char*>(keys), 2);
        
        return create_pair(1, map->getLength());
    }, is_eq);

    test<bool>("Insert on empty map then contains", []() {
        ChainingHashMap<const char*, int>* map = new ChainingHashMap<const char*, int>();
        const char* key = "A"; int v = 5;
        map->insert(new Hashable<const char*>(&key), v);

        return create_pair(true, map->contains(new Hashable<const char*>(&key)));
    }, is_eq);

    test<bool>("Insert on empty map then remove then contains", []() {
        ChainingHashMap<const char*, int>* map = new ChainingHashMap<const char*, int>();
        const char* key = "A"; int v = 5;
        map->insert(new Hashable<const char*>(&key), v);
        map->remove(new Hashable<const char*>(&key));
        return create_pair(false, map->contains(new Hashable<const char*>(&key)));
    }, is_eq);

    test<int>("Insert on empty map then get", []() {
        ChainingHashMap<const char*, int>* map = new ChainingHashMap<const char*, int>();
        const char* key = "A"; int v = 5;
        map->insert(new Hashable<const char*>(&key), v);
        return create_pair(v, map->get(new Hashable<const char*>(&key)));
    }, is_eq);

    test<int>("Insert twice on empty map then get", []() {
        ChainingHashMap<const char*, int>* map = new ChainingHashMap<const char*, int>();
        const char* key = "A";

        map->insert(new Hashable<const char*>(&key), 5);
        map->insert(new Hashable<const char*>(&key), 6);
        return create_pair(6, map->get(new Hashable<const char*>(&key)));
    }, is_eq);

    test<int>("Insert on empty map then remove", []() {
        ChainingHashMap<const char*, int>* map = new ChainingHashMap<const char*, int>();
        const char* key = "A";
        map->insert(new Hashable<const char*>(&key), 5);
        return create_pair(5, map->remove(new Hashable<const char*>(&key)));
    }, is_eq);

    test<int>("Insert on empty map then remove twice", []() {
        ChainingHashMap<const char*, int>* map = new ChainingHashMap<const char*, int>();
        const char* key = "A";
        map->insert(new Hashable<const char*>(&key), 5);
        map->remove(new Hashable<const char*>(&key));

        try {
            map->remove(new Hashable<const char*>(&key));
        } catch (int err) {
            return create_pair(ChainingHashMap<const char*, int>::KEY_ERROR, err);
        }
        return create_pair(-1, 1);
    }, is_eq);

    test<bool>("Insert then contains", []() {
        const char* keys[] = {"A", "B", "C", "D", "E", "F"};
        MapRecord<Hashable<const char*>, int> records[] = {
            {Hashable<const char*>::create(keys), 1},
            {Hashable<const char*>::create(keys + 1), 2},
            {Hashable<const char*>::create(keys + 2), 3},
            {Hashable<const char*>::create(keys + 3), 4},
            {Hashable<const char*>::create(keys + 4), 5}
        };

        ChainingHashMap<const char*, int>* map = ChainingHashMap<const char*, int>::build(records, 5, 2);
        map->insert(new Hashable<const char*>(keys + 5), 6);

        return create_pair(true, map->contains(new Hashable<const char*>(keys + 5)));
    }, is_eq);

    test<int>("Insert then get", []() {
        const char* keys[] = {"A", "B", "C", "D", "E", "F"};
        MapRecord<Hashable<const char*>, int> records[] = {
            {Hashable<const char*>::create(keys), 1},
            {Hashable<const char*>::create(keys + 1), 2},
            {Hashable<const char*>::create(keys + 2), 3},
            {Hashable<const char*>::create(keys + 3), 4},
            {Hashable<const char*>::create(keys + 4), 5}
        };

        ChainingHashMap<const char*, int>* map = ChainingHashMap<const char*, int>::build(records, 5, 2);
        map->insert(new Hashable<const char*>(keys + 5), 6);

        return create_pair(6, map->get(new Hashable<const char*>(keys + 5)));
    }, is_eq);

    test<int>("Insert then remove", []() {
        const char* keys[] = {"A", "B", "C", "D", "E", "F"};
        MapRecord<Hashable<const char*>, int> records[] = {
            {Hashable<const char*>::create(keys), 1},
            {Hashable<const char*>::create(keys + 1), 2},
            {Hashable<const char*>::create(keys + 2), 3},
            {Hashable<const char*>::create(keys + 3), 4},
            {Hashable<const char*>::create(keys + 4), 5}
        };

        ChainingHashMap<const char*, int>* map = ChainingHashMap<const char*, int>::build(records, 5, 2);
        map->insert(new Hashable<const char*>(keys + 5), 6);
        return create_pair(6, map->remove(new Hashable<const char*>(keys + 5)));
    }, is_eq);

    test<int>("Insert then remove twice", []() {
        const char* keys[] = {"A", "B", "C", "D", "E", "F"};
        MapRecord<Hashable<const char*>, int> records[] = {
            {Hashable<const char*>::create(keys), 1},
            {Hashable<const char*>::create(keys + 1), 2},
            {Hashable<const char*>::create(keys + 2), 3},
            {Hashable<const char*>::create(keys + 3), 4},
            {Hashable<const char*>::create(keys + 4), 5}
        };

        ChainingHashMap<const char*, int>* map = ChainingHashMap<const char*, int>::build(records, 5, 2);
        map->insert(new Hashable<const char*>(keys + 5), 6);
        map->remove(new Hashable<const char*>(keys + 5));

        try {
            map->remove(new Hashable<const char*>(keys + 5));
        } catch (int err) {
            return create_pair(ChainingHashMap<const char*, int>::KEY_ERROR, err);
        }
        return create_pair(-1, 1);
    }, is_eq);

    test<int>("Remove on empty map", []() {
        ChainingHashMap<const char*, int> map;
        const char* k = "A";
        try {
            map.remove(new Hashable<const char*>(&k));
        } catch (int err) {
            return create_pair(ChainingHashMap<const char*, int>::KEY_ERROR, err);
        }
        return create_pair(-1, 1);
    }, is_eq);

    return 0;
}