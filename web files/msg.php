<?php

$msg = $_POST['message'];

if ($msg == '') {
    echo 'go away';
    exit;
}

echo $msg;