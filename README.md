# DataGovProject

The purpose of this project was to implement code that helped implement data governance policies. The three modules can be used together to do the following:
1) Block all access except for the super user during certain periods of time.
2) Keep a log for every access attempt for specified files. 

It has 3 modules:
1) A program that reads the file paths in the json and reads the attributes of the given files before the lockdown so that the initial properties of the files can be restored.
2) A program that will check if the system time is currently in the range of the lockdown times specified in the json to let the inotify daemon know when it needs to run.
3) An inotify daemon that is able to parse a json to find the files to monitor, and then keep a record of anyone who has attempted to access the file during the times specified in the json. It logs all records in a file.
All my work is done in C on an RHEL system.


Json Generating program:
To ensure that the original properties of the files are not lost, this program created a json which contained file paths and the initial attributes of each of these files so that they could be restored after lockdown is over. 


Time Checker program:
I made my own functions to compare the current system time to the time range in the json. I converted most of the times to integers and simply compared them. I put the checker at an interval of every 15 minutes.

Inotify Daemon:
I have used a library available on Github to parse the json. From the json, I get the paths of the files to be monitored. I then add an inotify instance for these files that keeps a check on the programs, and feeds all records to a log file.

All the modules work with each other to create a way of blocking and keeping a record of any access attempts in a given period of time.

When we run the program, the first module that we run is the json generator. It parses the json containing the files to be monitored, and obtains the file paths. The program then finds the file properties(chmod) of the files, and generates a json which contains the file paths and its respective properties. It is necessary to have the initial properties of the file so that they can be restored when outside the lockdown time.

The program then uses the time checker module to compare the system times with the specified lockdown times in the json file. If the system time is within the lockdown range for any file, the program changes the file owner to the superuser, and then changes the chmod to 700, so only the superuser has access to the file.

Finally, after the time checker, the program proceeds to the inotify module that obtains the file paths from the file json and then places an inotify watch on each of those files. It then generates a log for every access, modification, deletion, of everything inside the file paths specified.
