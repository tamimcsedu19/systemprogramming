#include <iostream>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libgen.h>

using namespace std;
void lsR(bool rec,string cwd)
{
  DIR *dirp = opendir(cwd.c_str());
  struct dirent *file;
  while(true)
  {

    file = readdir(dirp);
    if(file == NULL)
        break;
    if(strcmp(file->d_name,".") == 0 ||  strcmp(file->d_name,"..") == 0)
        continue;





    string curFile = cwd+"/"+string(file->d_name);
    const char *c_curFile = curFile.c_str();


    struct stat file_stat;
   // printf("Opening %s",c_curFile);
    int staterr = stat(c_curFile,&file_stat);
    if(staterr == -1)
    {
        printf("Error opening %s\n",strerror(errno));
        exit(-200);
    }
    printf("%s %ld\n",file->d_name,(long)file_stat.st_uid);

    if(S_ISDIR(file_stat.st_mode) && rec)
    {

            DIR *dirp = opendir(c_curFile);

            lsR(rec,curFile);

    }
  }
  closedir(dirp);
  return;
}
int main(int argc,const char* argv[])
{

    printf("In child\n");
    for(int i=0;i<argc;++i)
        printf("%s\n",argv[i]);
    DIR *dirp;
    if(argc == 3)
    {

        lsR(1,string(argv[2]));
    }
    else
    {

        lsR(1,string(argv[1]));
    }




}
