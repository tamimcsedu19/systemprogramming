#include <iostream>
#include <string>
#include <unistd.h>
#include <bits/stdc++.h>

using namespace std;
const char* ls_path="/home/tamim/oslab/manualls/bin/Debug/manualls";
char cwd[1024];
int main()
{

    string command;
    while(getline(cin,command))
    {
        vector<string> tokens;
        istringstream iss(command);
        copy(istream_iterator<string>(iss),istream_iterator<string>(),back_inserter(tokens));
        pid_t pid = fork();
        if(pid == -1)
            exit(-1);
        else if(pid == 0)
        {
                char *argVec[10];

                int i=0;
                for(;i<tokens.size();++i)
                    argVec[i] = (char *)tokens[i].c_str();
                if (getcwd(cwd, sizeof(cwd)) == NULL)
                    perror("getcwd() error");
                else
                    argVec[i] = cwd;
                i++;


                argVec[i] = NULL;
                execv(ls_path, argVec);


        }
        else
        {
            cout<<"Continue to Parents\n";
        }
    }

}
