# M3OEP-MPL-ssander-dmelkumo

## Authors:
* David Melkumov
* Sean Sander

## Directions:
1. Download/Clone the repository
2. Transfer the following files to your server (alternatively the entire folder)
    * start.php
    * edit.php
    * edit.cpp
    * style.css
3. Navigate to start.php to begin editing text
4. Check out this example: https://dmelkumo.w3.uvm.edu/cs120/M3OEP-MPL-ssander-dmelkumo/start.php

## Summary:
This project is an online text file editor which allows you to upload a text file to work on. In the landing page 
(start.php), the user is prompted to either upload an existing file or start fresh with a new one. In either case,
a folder with a randomly-generated name is made to contain the text file uploaded/created. From there, the website
redirects to the edit page (edit.php), where the user can update/save, use caveman (more on that later), download the
file, and exit. The update button writes the contents of the text-area element to a file, where the C++ program will 
then read from to continue displaying/redisplay the file and its stats. The caveman button will add a randomly-generated
sentence structure to the text file. Clicking the download button will download an 'edit.txt' file, where 'edit.txt' is 
the most-recently saved version of the file. The exit button deletes the containing folder and its contents. To combat 
clutter formed by cases where a session is cut short because they didn't click exit, start.php will delete old folders 
after a certain amount of time. This functions by logging the timestamps and folder names in some text files, and 
checking if the oldest logged run is more than one day old. If so, it will delete all other folders and clear out the 
text files.

## Citations:
https://www.php.net/manual/en/function.readfile.php