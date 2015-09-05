#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <bits/stdc++.h>
#include <ext/stdio_filebuf.h>
#include <fstream>
using namespace std;
int global_pipefd[2];

bool isPrime(int a)
{
    if(a<2)
        return false;
    for(int i=2;i<a;++i)
        if(a%i == 0)
            return false;
    return true;
}
void computePrimes(int ca,int cb)
{
    cout<<" cpu number: "<<sched_getcpu()<<"\n";
    close(global_pipefd[0]);
    FILE *f = fdopen(global_pipefd[1],"w");
    for(int i=ca;i<=cb;++i)
    {
        if(isPrime(i))
        {
            //printf("%d ",i);
            fprintf(f,"%d ",i);
        }
    }
    return;
}
void sort_numbers(int s)
{

    printf("sorting ^_^\n");
    FILE *f = fdopen(global_pipefd[0],"r");
    int x;
    vector<int> nums;
    while(fscanf(f,"%d",&x) == 1)
        nums.push_back(x);
    sort(nums.begin(),nums.end());
    for(int x: nums)
        cout<<x<<" ";

}
int main(int argc, char *argv[])
{
    pid_t cpid;
    char buf;
    if (pipe(global_pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    int a,b,N;
    cin>>a>>b>>N;
    int range = (b-a)/N;
    int ca = a-range,cb = a-1;
    for(int i=1; i<=N; ++i)
    {

        ca = cb+1;
        cb = min(ca+range,b);
        cpid = fork();
        if (cpid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (cpid == 0)
        {
            cout<<"in child\n";
            computePrimes(ca,cb);
            exit(0);
        }
    }

    close(global_pipefd[1]);

    signal(SIGALRM, sort_numbers);
    alarm(5);
    sleep(10);








}
