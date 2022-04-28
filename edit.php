<?php
//get info from form of previous page
$choice = $_POST["choice"];
$folder = $_POST["folder"];

//delete directory if its exit
if ($choice == 3) {
    shell_exec("rm " . $folder . " -r");
    header("Location: start.php");
}

//move the uploaded file into the folder if it was the first time
if ($choice == 0) {
    //make sure its a text file
    if (substr($_FILES["file-upload"]["name"], -4) == ".txt") {
        if (move_uploaded_file($_FILES["file-upload"]["tmp_name"], $folder . "/edit.txt")) {
            echo "<p>File Upload Successful!</p>";
        }
    }
    else {
        echo "<p>File Upload Failed</p>";
    }
}

//saving
if ($choice == 2 || $choice == 4 || $choice == 5) {
    $edit = fopen($folder . "/edit.txt", "w");
    fwrite($edit, $_POST["text-body"]);
    fclose($edit);
}

//to download the file
if ($choice == 5) {
    header('Content-Description: File Transfer');
    header('Content-Type: application/octet-stream');
    header('Content-Disposition: attachment; filename="edit.txt"');
    header('Expires: 0');
    header('Cache-Control: must-revalidate');
    header('Pragma: public');
    header('Content-Length: ' . filesize($folder . "/edit.txt"));
    readfile($folder . "/edit.txt");
}

//enter folder, run, leave folder
$output = shell_exec("cd " . $folder . ";./edit.exe " . $choice . ";cd ..");
$outputs = explode('☐', $output);
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
            <input type="hidden" name="folder" value="<?php echo $folder ?>">
            <?php
            echo "<p class='stats'>Letter Count: " . $outputs[1];
            echo ", Word Count: " . $outputs[2];
            echo ", Line Count: " . $outputs[3] . "</p>";
            echo $outputs[0];
            ?>
            <br/>
            <button type="submit" name = "choice" value="2">Update</button>
            <button type="submit" name = "choice" value="4">Caveman</button>
            <button type="submit" name = "choice" value="5">Download</button>
            <button type="submit" name = "choice" value="3">Exit</button>
        </form>
    </body>
</html>