#include "myThreads.hpp"
#include "utils.hpp"

// Mappers function
void *mapper(void *arg) {
    pack *pkt = (pack *) arg;
    string input_file;

    while (1) {
        pthread_mutex_lock(&pkt->mutex_pop);
        // check if queue is not empty
        if (!pkt->files_queue.empty()) {
            input_file = pkt->files_queue.top().second;
            pkt->files_queue.pop();
        } else {
            pthread_mutex_unlock(&pkt->mutex_pop);
            break;
        }
        pthread_mutex_unlock(&pkt->mutex_pop);

        ifstream fin(input_file);
        if (!fin.is_open()) {
            cout<<"File cannot be open.\n";
            exit(-1);
        }
        
        int n, nr, left, right, mid;
        fin>>n; 
        for (int i = 0; i < n; ++i) {
            fin>>nr;
            for (int exp = 2; exp <= pkt->nr_reducers + 1; ++exp) {
                left = 1;
                right = (int)sqrt(nr);
                while (left <= right) {
                    mid = (left + right) / 2;

                    if (pow(mid, exp) == nr) {
                        pthread_mutex_lock(&pkt->mutex_push);
                        pkt->p_lists->at(exp).push_back(nr);
                        pthread_mutex_unlock(&pkt->mutex_push);
                        break;
                    } else if (pow(mid, exp) > nr) {
                        right = mid - 1;
                    } else {
                        left = mid + 1;
                    }
                }
                
            }
        }
        fin.close();
    }
    
    pthread_exit(NULL);
}

// Reducers function
void *reducer(void *arg) {
    return NULL;
}