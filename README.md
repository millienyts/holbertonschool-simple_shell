# Holberton Shell

This task integrates concepts covered throughout the course, serving as the culmination of the section focused exclusively on mastering C programming.

# list of allowed functions and system calls

- access (man 2 access) 

- chdir (man 2 chdir)

- close (man 2 close)

- closedir (man 3 closedir)

- execve (man 2 execve)

- exit (man 3 exit)

- _exit (man 2 _exit)

- fflush (man 3 fflush)

- fork (man 2 fork)

- free (man 3 free)

- getcwd (man 3 getcwd)

- getline (man 3 getline)

- getpid (man 2 getpid)

- isatty (man 3 isatty)

- kill (man 2 kill)

- malloc (man 3 malloc)

- open (man 2 open)

- opendir (man 3 opendir)

- perror (man 3 perror)

- printf (man 3 printf)

- fprintf (man 3 fprintf)

- vfprintf (man 3 vfprintf)

- sprintf (man 3 sprintf)

- putchar (man 3 putchar)

- read (man 2 read)

- readdir (man 3 readdir)

- signal (man 2 signal)

- stat (__xstat) (man 2 stat)

- lstat (__lxstat) (man 2 lstat)

- fstat (__fxstat) (man 2 fstat)

- strtok (man 3 strtok)

- wait (man 2 wait)

- waitpid (man 2 waitpid)

- wait3 (man 2 wait3)

-  wait4 (man 2 wait4)

- write (man 2 write)


# Installing

Compile the shell using the following command:

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

# Testing

	$ ./hsh
	($) /bin/ls
	hsh main.c shell.c
	($)
	($) exit
	$
# Examples
$ ls

file_1	file_2	file_3

$ cat file_2

(Display file_2 content)

$

# Files

The primary file being utilized is simple_shell.c wich contains the shell function itself. This file is linked to a header file named shell.h, which contains the libraries and prototypes of each function. In the AUTHORS file you will find the name and contact of the creators and in the man_1_simple_shell file there is a guide on how to use the created shell.

# Authors 

Millieny Torres and Juan Gabriel Collazo
