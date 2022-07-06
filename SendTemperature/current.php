
<?php
    $connect = mysqli_connect("localhost", "database_name", "YourStrongPassword", "database_username");
        
    $sql = "SELECT * FROM temperature ORDER BY id DESC LIMIT 0,1";
    $result = mysqli_query($connect, $sql);

    if ($result) {
        $row = mysqli_fetch_assoc($result);
        echo $row['temperature'];
    } else {
        echo "No data";
    }
