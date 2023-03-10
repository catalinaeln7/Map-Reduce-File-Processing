#include <pthread.h>
#include <cstring>
#include <cstdlib>

#include "utils.hpp"
#include "myThreads.hpp"

using namespace std;


int main(int argc, char *argv[]) {
    check_args(argc);

    int nr_mappers;
    int nr_reducers;
    string input_file;

    nr_mappers = atoi(argv[1]);
    nr_reducers = atoi(argv[2]);
    input_file = string(argv[3]);
    int P = nr_mappers + nr_reducers;
    
    pthread_t threads[P];
    pack *pkt = new pack;

    pkt->nr_reducers = nr_reducers;
    pthread_mutex_init(&pkt->mutex_pop, NULL);
    pthread_mutex_init(&pkt->mutex_push, NULL);
    pthread_mutex_init(&pkt->mutex_test, NULL);
    // pkt.mutex_push = new pthread_mutex_t;
    // for (int i = 0; i < nr_reducers; ++i) {
    //     pthread_mutex_init(&pkt.mutex_push[i], NULL);
    // }
    pkt->files_queue = get_files_q(input_file);  
    pkt->p_lists = initialize_lists(nr_reducers);

    for (int i = 0; i < nr_mappers; ++i) {
        int r = pthread_create(&threads[i], NULL, mapper, pkt);

        if (r) {
			printf("Eroare la crearea mapper-ului %d\n", i);
			exit(-1);
		} 
    }

    

    for (int i = 0; i < nr_mappers; ++i) {
        pthread_join(threads[i], NULL);
    }

    for (auto i : *pkt->p_lists) {
        for (auto j : i.second) {
            std::cout << j <<" ";
        }
        std::cout << std::endl;
    }
    
    pthread_mutex_destroy(&pkt->mutex_pop);
    pthread_mutex_destroy(&pkt->mutex_push);
    delete pkt;
}