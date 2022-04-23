    #include <iostream>
    #include <stdio.h>
    #include <pthread.h>
    #include <sys/time.h>
    #include <mutex>

    #define N 202300072
    #define NTHREADS 5

using namespace std;





pthread_mutex_t kilit = PTHREAD_MUTEX_INITIALIZER;

double globalPi = 0.0;
int mod = (N%NTHREADS);
int buffer = (N / NTHREADS) + mod;


double ownPi[NTHREADS] = {0.0};


void  *helloLoop1(void* pArg){
    //cout << "\n N/NTHREADS ="<<N/NTHREADS<<"\n N%NTHREADS="<<N%NTHREADS<<"\n N="<<N<<"\n buffer ="<<buffer<< "\n buffer * nthreads="<<buffer * NTHREADS<<"\n NThreads = "<<NTHREADS<<"\n";
    int myId = *((int*)pArg);
    double x,pi,step;
    pi = 0;
    step = 1.0 / (double) (buffer * NTHREADS);

     pthread_mutex_lock(&kilit);
     cout << "\nmy Thread id: " << myId<<"\n";
     pthread_mutex_unlock(&kilit);
    for(int i = myId*buffer;i < (buffer*(myId+1));i++){
        x = (i + 0.5f) * step;
        pi = pi + ( step *  4.0/(1.0+x*x) );
    }

    pthread_mutex_lock(&kilit);
    globalPi += pi;
    pthread_mutex_unlock(&kilit);
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
}


int main()
{
    timeval tim;
    gettimeofday(&tim,NULL);
    double t1 = 1.0e6 * tim.tv_sec + tim.tv_usec;
    //---FUNCTION---
    pThreadFunc();
    //---FUNCTION---
    gettimeofday(&tim,NULL);
    double t2 = 1.0e6 * tim.tv_sec + tim.tv_usec;
    cout <<"\n[Function Void Time] = "<<t2-t1;
    cout <<"\n[Global Pi Degiskeni=]"<<globalPi;
    getchar();
    return 0;
}
