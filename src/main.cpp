#include <iostream>
#include <time.h>
#include <dataStructures/BinarySearchTree.h>
#include <cmath>

int main(int, char**){
    srand(time(NULL));
    BinarySearchTree<int*>* bst = new BinarySearchTree<int*>();

    const int MAX_ORDER = 5;

    for( int o{}; o <= MAX_ORDER; o++){
        const int n = pow(10, o);
        clock_t start = clock();
        for (int i{}; i < n; i++){
            int* random_number = new int(((rand() << 16) | rand()) % 1000);
            bst->insert(
                random_number,
                [](int* const & a, int* const & b)->bool {
                    return *a < *b;
                }
            );
        }
        clock_t end = clock();
        std::cout << "Inserting " << n << " elements took " << (double)(end - start) / CLOCKS_PER_SEC << " seconds | " << "Height of the tree: " << bst->bst_height() << std::endl;

        const int m = pow (10 , 4) ;
        int hits = 0;
        start = clock();
        for (int i{}; i<m; i++){
            int* random_number = new int(((rand() << 16) | rand()) % 1000); 
            auto result = bst->search(
                random_number,
                [](int* const & a, int* const & b)->bool {
                    return *a < *b;
                }
            );
            if (result){
                hits++;
            }
        }
        end = clock();

        std::cout << "Searching " << m << " elements took " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;

        bst->clear(
            [](int* const & a)->void{
                delete a;
            }
        );

    }

    delete bst;
    bst = nullptr;

    return 0;
}
