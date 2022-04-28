<?php
//get a random number for folder name to prevent conflicts when multiple people using at same time
$folder = rand();
while (file_exists($folder)) {
    $folder = rand();
}

//system to delete old folders
//write the current time and compare to previous ones
$fileTimes = fopen('times.txt', "a+");
$currentTime = time() / 86400;
$times = explode(" ", fread($fileTimes, filesize("times.txt")));
fwrite($fileTimes, $currentTime);
fwrite($fileTimes, " ");
fclose($fileTimes);

//clear folders if applicable
if (($currentTime - $times[0]) > 1) {
    $infile = fopen("folders.txt", "r");
    $folders = explode(" ", fread($infile, filesize("folders.txt")));
    foreach ($folders as $name){
        shell_exec("rm " . $name . " -r");
    }
    fclose($infile);
    //empty folders.txt
    $infile = fopen("folders.txt", "w");
    fclose($infile);
    //remake the times.txt file with the latest time
    $fileTimes = fopen('times.txt', "w");
    fwrite($fileTimes, $currentTime);
    fwrite($fileTimes, " ");
    fclose($fileTimes);
}

//log the folder name
$fileNames = fopen('folders.txt', 'a');
fwrite($fileNames, $folder);
fwrite($fileNames, " ");
fclose($fileNames);

//make the new folder
$commandMkdir = escapeshellcmd("mkdir " . $folder);
$outputMkdir = shell_exec($commandMkdir);

//copy the file over
shell_exec(escapeshellcmd("cp edit.cpp " . $folder));
shell_exec(escapeshellcmd("cp edit.php " . $folder));
shell_exec(escapeshellcmd("cp start.php " . $folder));
//enter folder, compile the file, leave folder
shell_exec("cd " . $folder . ";g++ -std=c++1y -o edit.exe edit.cpp;cd ..")

?>

<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="utf-8">
        <meta name="author" content="David, Sean">
        <title>Text Editor</title>
        <meta name="description" content="Upload a file or create a new one to edit and then save/download it">
        <link href="style.css" rel="stylesheet" type="text/css" media="screen" />
    </head>
    <body>
        <form enctype="multipart/form-data" action="edit.php" method="POST">
            <p>Upload a text file to edit:</p>
            <input type="file" name="file-upload" /><br />
            <input type="hidden" name="choice" value="0">
            <input type="hidden" name="folder" value="<?php echo $folder; ?>">
            <input type="submit" value="Upload" />
        </form>

        <form enctype="multipart/form-data" action="edit.php" method="POST">
            <p>Create a new file:</p>
            <input type="hidden" name="choice" value="1">
            <input type="hidden" name="folder" value="<?php echo $folder; ?>">
            <input type="submit" value="Get Started" />
        </form>
    </body>
</html>