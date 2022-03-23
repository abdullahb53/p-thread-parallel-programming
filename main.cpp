    #include <iostream>
    #include <stdio.h>
    #include <pthread.h>
    #include <sys/time.h>
    #include <mutex>

    #define N 20000000
    #define NTHREADS 8

using namespace std;





pthread_mutex_t kilit = PTHREAD_MUTEX_INITIALIZER;

double globalPi = 0.0;


double ownPi[NTHREADS] = {0.0};


void  *helloLoop1(void* pArg){

    double x;
    double sum;

    double step = 1.0 / N;

    int myId = *((int*)pArg);
    cout << "\n my Thread id = " << myId;
    for(int i = myId;i<N;i+=NTHREADS){
        x = (i + 0.5f)*step;
        pthread_mutex_lock(&kilit);
        globalPi += step*4.0/(1.0 + x*x);
        pthread_mutex_unlock(&kilit);
    }


    //ownPi[myId] = sum;

}

void pThreadFunc(){

    pthread_t threadTutucu[NTHREADS];
    int threadNumbers[NTHREADS];

    for(int j=0;j<NTHREADS;++j){
        threadNumbers[j] = j;
        pthread_create(&threadTutucu[j],NULL,helloLoop1,(void*)&threadNumbers[j]);

    }

    for(int i = 0;i<NTHREADS; ++i){
        pthread_join (threadTutucu[i],NULL);


    }

    /*for(int i = 0;i<NTHREADS; ++i){

    globalPi += ownPi[i];

    }*/




}


int main()
{
    timeval tim;
    gettimeofday(&tim,NULL);
    double t1 = 1.0e6 * tim.tv_sec + tim.tv_usec;
    //---FUNC---
    pThreadFunc();
    //---FUNC---
    gettimeofday(&tim,NULL);
    double t2 = 1.0e6 * tim.tv_sec + tim.tv_usec;

    cout <<"\n[Function Void Time] = "<<t2-t1;
    cout <<"\n[Global Pi Degiskeni=]"<<globalPi;

    //cout << "Hello world!" << endl;
    return 0;
}
