<?php
    // takes raw data from the request 
    $json = file_get_contents('php://input');

    $date = date('Y-m-d H:i:s');
    $time = ", \"date\": \"".$date."\"}";
    $json = str_replace("}", $time, $json);

    $file = 'sensor_data.json';

    // Open the file to get existing content
    $current = file_get_contents($file);

    // Append a new record to the file
    $current .= $json.",\n";


    $record = json_decode($json, true);

    // Write the contents back to the file
    file_put_contents($file, $current);

    $connect = mysqli_connect("localhost", "database_name", "YourStrongPassword", "database_username");
        
    $sql = "INSERT INTO temperature (id, sensor, temperature, raw_value, date_time) VALUES (null, '{$record["sensor"]}', '{$record["value"]}', '{$record["raw"]}', '{$record["date"]}');";
    mysqli_query($connect, $sql);
