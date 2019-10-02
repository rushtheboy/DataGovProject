#define _POSIX_SOURCE
 
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <limits.h>
#include <json.h>

#define MAX_EVENTS 1024 /*Max. number of events to process at one go*/
#define LEN_NAME 16 /*Assuming that the length of the filename won't exceed 16 bytes*/
#define EVENT_SIZE  ( sizeof (struct inotify_event) ) /*size of one event*/
#define BUF_LEN     ( MAX_EVENTS * ( EVENT_SIZE + LEN_NAME )) /*buffer to store the data of events*/

#undef _POSIX_SOURCE
 


void filewatch(char *s)
{

  int length, i = 0, wd;
  int fd;
  char buffer[BUF_LEN];
 
  /* Initialize Inotify*/
  fd = inotify_init();
  if ( fd < 0 ) {
    perror( "Couldn't initialize inotify");
  }

  //This is where I open and initialise the requirements for the log file
  FILE *fptr;
  fptr = fopen("/home/rushilroy/Documents/IBMProject2019/Accesslog", "a");
  char sentence1[] = "File was accessed.";
  char sentence2[] = "File was opened.";
  char sentence3[] = "File was created.";
  char sentence4[] = "File was deleted.";
  char sentence5[] = "File was modified.";  
  
  
   if(fptr == NULL)
   {
      printf("Error!");
      exit(1);
   }

   time_t orig_format;
   time(&orig_format);

//Done with the log file requirements

//CHMOD TESTING

char fn[] = "/home/rushilroy/Downloads/ClassifiedFile3";

// Done


  /* add watch to starting directory */
  wd = inotify_add_watch(fd, s, IN_OPEN | IN_ACCESS | IN_CREATE | IN_MODIFY | IN_DELETE | IN_DELETE_SELF | IN_MOVE_SELF);
 
  if (wd == -1)
    {
      printf("Couldn't add watch to %s\n",s);
    }
  else
    {
      printf("Watching: %s\n",s);
    }

//info for log file
  int uid = getuid();
  int gid = getegid();
  char hostname[1024];
  hostname[1023] = '\0';
  gethostname(hostname, 1023);
  struct stat stats;
  int forstat = stat(s, &stats);
  

  /* do it forever*/
  while(1)
    {
      i = 0;
      length = read( fd, buffer, BUF_LEN );  
 
      if ( length < 0 ) {
        perror( "read" );
      }  
 
      while ( i < length ) {
        struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
        if ( event->len ) {
          if ( event->mask & IN_OPEN) {
            if (event->mask & IN_ISDIR){
              printf( "The directory %s was opened. \n", event->name ); 
              rewind(fptr);
              int a11 = fprintf(fptr, "\nLog Version:0.01  "); 
              int a12 = fprintf(fptr, "Path:%s  ", s);
              int a13 = fprintf(fptr, "Hostname: %s ", hostname);
              int a14 = fprintf(fptr, "%s:%s %s ", event->name, sentence2,asctime(gmtime(&orig_format)));
              int a15 = fprintf(fptr, "inode: %d ", stats.st_ino);
              int a16 = fprintf(fptr, "UID:%d ", uid);
              int a17 = fprintf(fptr, "GID:%d\n",gid);
              }     
            else{
              printf( "The file %s was opened with WD %d\n", event->name, event->wd ); 
              rewind(fptr);
              int a21 = fprintf(fptr, "\nLog Version:0.01  "); 
              int a22 = fprintf(fptr, "Path:%s  ", s);
              int a23 = fprintf(fptr, "Hostname: %s ", hostname);
              int a24 = fprintf(fptr, "%s:%s %s ", event->name, sentence2,asctime(gmtime(&orig_format)));
              int a25 = fprintf(fptr, "inode: %d ", stats.st_ino);
              int a26 = fprintf(fptr, "UID:%d ", uid);
              int a27 = fprintf(fptr, "GID:%d\n",gid);
              }     
          }
           
         if ( event->mask & IN_ACCESS) {
//         if (chmod(fn, S_IRWXU) != 0)
//              perror("chmod() error");
            if (event->mask & IN_ISDIR){
              printf( "The directory %s was accessed.\n", event->name );
              rewind(fptr);
              int b11 = fprintf(fptr, "\nLog Version:0.01  "); 
              int b12 = fprintf(fptr, "Path:%s  ", s);
              int b13 = fprintf(fptr, "Hostname: %s ", hostname);
              int b14 = fprintf(fptr, "%s:%s %s ", event->name, sentence1,asctime(gmtime(&orig_format)));
              int b15 = fprintf(fptr, "inode: %d ", stats.st_ino);
              int b16 = fprintf(fptr, "UID:%d ", uid);
              int b17 = fprintf(fptr, "GID:%d\n",gid);
              }
            else{
              printf( "The file %s was accessed with WD %d\n", event->name, event->wd ); 
              rewind(fptr);
              int b21 = fprintf(fptr, "\nLog Version:0.01  "); 
              int b22 = fprintf(fptr, "Path:%s  ", s);
              int b23 = fprintf(fptr, "Hostname: %s ", hostname);
              int b24 = fprintf(fptr, "%s:%s %s ", event->name, sentence1,asctime(gmtime(&orig_format)));
              int b25 = fprintf(fptr, "inode: %d ", stats.st_ino);
              int b26 = fprintf(fptr, "UID:%d ", uid);
              int b27 = fprintf(fptr, "GID:%d\n",gid);
              }      
          }  
          
//           unlink(fn);
          
          if ( event->mask & IN_CREATE) {
            if (event->mask & IN_ISDIR){
             printf( "The directory %s was Created.\n", event->name ); 
             rewind(fptr);
              int c11 = fprintf(fptr, "\nLog Version:0.01  "); 
              int c12 = fprintf(fptr, "Path:%s  ", s);
              int c13 = fprintf(fptr, "Hostname: %s ", hostname);
              int c14 = fprintf(fptr, "%s:%s %s ", event->name, sentence3,asctime(gmtime(&orig_format)));
              int c15 = fprintf(fptr, "inode: %d ", stats.st_ino);
              int c16 = fprintf(fptr, "UID:%d ", uid);
              int c17 = fprintf(fptr, "GID:%d\n",gid); 
              }     
            else{
              printf( "The file %s was Created with WD %d\n", event->name, event->wd );  
              rewind(fptr);
              int c21 = fprintf(fptr, "\nLog Version:0.01  "); 
              int c22 = fprintf(fptr, "Path:%s  ", s);
              int c23 = fprintf(fptr, "Hostname: %s ", hostname);
              int c24 = fprintf(fptr, "%s:%s %s ", event->name, sentence3,asctime(gmtime(&orig_format)));
              int c25 = fprintf(fptr, "inode: %d ", stats.st_ino);
              int c26 = fprintf(fptr, "UID:%d ", uid);
              int c27 = fprintf(fptr, "GID:%d\n",gid);
              }     
          }
           
          if ( event->mask & IN_MODIFY) {
            if (event->mask & IN_ISDIR){
              printf( "The directory %s was modified.\n", event->name );
              rewind(fptr);
              int d11 = fprintf(fptr, "\nLog Version:0.01  "); 
              int d12 = fprintf(fptr, "Path:%s  ", s);
              int d13 = fprintf(fptr, "Hostname: %s ", hostname);
              int d14 = fprintf(fptr, "%s:%s %s ", event->name, sentence5,asctime(gmtime(&orig_format)));
              int d15 = fprintf(fptr, "inode: %d ", stats.st_ino);
              int d16 = fprintf(fptr, "UID:%d ", uid);
              int d17 = fprintf(fptr, "GID:%d\n",gid);
              }       
            else{
              printf( "The file %s was modified with WD %d\n", event->name, event->wd );       
              rewind(fptr);
              int d21 = fprintf(fptr, "\nLog Version:0.01  "); 
              int d22 = fprintf(fptr, "Path:%s  ", s);
              int d23 = fprintf(fptr, "Hostname: %s ", hostname);
              int d24 = fprintf(fptr, "%s:%s %s ", event->name, sentence5,asctime(gmtime(&orig_format)));
              int d25 = fprintf(fptr, "inode: %d ", stats.st_ino);
              int d26 = fprintf(fptr, "UID:%d ", uid);
              int d27 = fprintf(fptr, "GID:%d\n",gid);
              }
          }
          
           
          if ( event->mask & IN_DELETE) {
            if (event->mask & IN_ISDIR){
              printf( "The directory %s was deleted.\n", event->name );   
              rewind(fptr);
              int e11 = fprintf(fptr, "\nLog Version:0.01  "); 
              int e12 = fprintf(fptr, "Path:%s  ", s);
              int e13 = fprintf(fptr, "Hostname: %s ", hostname);
              int e14 = fprintf(fptr, "%s:%s %s ", event->name, sentence4,asctime(gmtime(&orig_format)));
              int e15 = fprintf(fptr, "inode: %d ", stats.st_ino);
              int e16 = fprintf(fptr, "UID:%d ", uid);
              int e17 = fprintf(fptr, "GID:%d\n",gid);
              }    
            else{
              printf( "The file %s was deleted with WD %d\n", event->name, event->wd ); 
              rewind(fptr);
              int e21 = fprintf(fptr, "\nLog Version:0.01  "); 
              int e22 = fprintf(fptr, "Path:%s  ", s);
              int e23 = fprintf(fptr, "Hostname: %s ", hostname);
              int e24 = fprintf(fptr, "%s:%s %s ", event->name, sentence4,asctime(gmtime(&orig_format)));
              int e25 = fprintf(fptr, "inode: %d ", stats.st_ino);
              int e26 = fprintf(fptr, "UID:%d ", uid);
              int e7 = fprintf(fptr, "GID:%d\n",gid);
              }      
          }
          
          if ( event->mask & IN_DELETE_SELF) {
           if (event->mask & IN_ISDIR){
              printf( "The directory watched %s was deleted.\n", event->name );  
              rewind(fptr);
              int f11 = fprintf(fptr, "\nLog Version:0.01  "); 
              int f12 = fprintf(fptr, "Path:%s  ", s);
              int f13 = fprintf(fptr, "Hostname: %s ", hostname);
              int f14 = fprintf(fptr, "%s:%s %s ", event->name, sentence4,asctime(gmtime(&orig_format)));
              int f15 = fprintf(fptr, "inode: %d ", stats.st_ino);
              int f16 = fprintf(fptr, "UID:%d ", uid);
              int f17 = fprintf(fptr, "GID:%d\n",gid);
              }     
           else{
              printf( "The file watched %s was deleted with WD %d\n", event->name, event->wd );      
              rewind(fptr);
              int f21 = fprintf(fptr, "\nLog Version:0.01  "); 
              int f22 = fprintf(fptr, "Path:%s  ", s);
              int f23 = fprintf(fptr, "Hostname: %s ", hostname);
              int f24 = fprintf(fptr, "%s:%s %s ", event->name, sentence4,asctime(gmtime(&orig_format)));
              int f25 = fprintf(fptr, "inode: %d ", stats.st_ino);
              int f26 = fprintf(fptr, "UID:%d ", uid);
              int f27 = fprintf(fptr, "GID:%d\n",gid);
              } 
            }
            
           if ( event->mask & IN_MOVE_SELF) {
            if (event->mask & IN_ISDIR){
              printf( "The directory watched %s was moved.\n", event->name ); 
              rewind(fptr);
              int g11 = fprintf(fptr, "\nLog Version:0.01  "); 
              int g12 = fprintf(fptr, "Path:%s  ", s);
              int g13 = fprintf(fptr, "Hostname: %s ", hostname);
              int g14 = fprintf(fptr, "%s:%s %s ", event->name, sentence5,asctime(gmtime(&orig_format)));
              int g15 = fprintf(fptr, "inode: %d ", stats.st_ino);
              int g16 = fprintf(fptr, "UID:%d ", uid);
              int g17 = fprintf(fptr, "GID:%d\n",gid);
              }      
            else{
              printf( "The file watched %s was moved with WD %d\n", event->name, event->wd );       
              rewind(fptr);
              int g21 = fprintf(fptr, "\nLog Version:0.01  "); 
              int g22 = fprintf(fptr, "Path:%s  ", s);
              int g23 = fprintf(fptr, "Hostname: %s ", hostname);
              int g24 = fprintf(fptr, "%s:%s %s ", event->name, sentence5,asctime(gmtime(&orig_format)));
              int g25 = fprintf(fptr, "inode: %d ", stats.st_ino);
              int g26 = fprintf(fptr, "UID:%d ", uid);
              int g27 = fprintf(fptr, "GID:%d\n",gid);
              }
            }
 
 
          i += EVENT_SIZE + event->len;
        }
      }
    }
  
}





int main( int argc, char **argv ) 
{
//Requirements for parsing
struct json_object *dir_object, *dir_array, *dir_array_object, *dir_array_object_path, *dir_array_object_start, *dir_array_object_end;
int arraylen, arraylooper;
char path[1000];
char start[5];
char end[5];
static const char filename[] = "/home/rushilroy/Documents/IBMProject2019/timeaccess2.json";
dir_object = json_object_from_file(filename);
dir_array = json_object_object_get(dir_object, "Directories");

// dir_array is an array of objects
arraylen = json_object_array_length(dir_array);

//End of parsing requirements
  

for (arraylooper = 0; arraylooper < arraylen; arraylooper++) {
  // get the i-th object in dir_array
//breakpoint
  dir_array_object = json_object_array_get_idx(dir_array, arraylooper);
  // get the name attribute in the i-th object
  dir_array_object_path = json_object_object_get(dir_array_object, "Path");
   
  if(fork()==0)
  filewatch(json_object_get_string(dir_array_object_path));
} 



  /* Clean up*/
//  inotify_rm_watch( fd, wd );
//  close( fd );
//  fclose(fptr);
//  return 0;
}


