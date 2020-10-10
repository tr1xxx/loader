<?php

    require_once "config.php";

    $username = $_POST['username'];
    $password = $_POST['password'];
    $hwid = $_POST['hwid'];

    $query = "SELECT * FROM users WHERE username='$username'";
    $result = mysqli_query($link, $query);
    $res = mysqli_fetch_assoc($result);

    $DBhwid = $res['hwid'];
    $id = $res['id'];

    $data = [
        'success' => false,
        'username' => '',
        'id' => '',
        'hwid' => '',
        'new_hwid' => '',
        'primary_group' => '',
        'other_groups' => '',
    ];

    $json = json_decode($data, true);

    if ($username != $res['username'] || !password_verify($password, $res['password'])) {
        $json['success'] = false;

        header('Content-type: application/json');
        echo json_encode($json);
        exit;
    }
    else {

        if (strlen($DBhwid) > 1) {

            if ($hwid != $DBhwid) {
                $json['success'] = true;
                $json['hwid'] = false;
                $json['new_hwid'] = false;
            }
            else {
                $json['success'] = true;
                $json['hwid'] = true;
                $json['new_hwid'] = false;
            }

        }
        else {

            $query_worked = "UPDATE users SET hwid='$hwid' WHERE username='$username'";

            if (mysqli_query($link, $query_worked)) {
                $json['success'] = true;
                $json['hwid'] = false;
                $json['new_hwid'] = true;
            }

        }

        $json['username'] = $username;
        $json['id'] = $id;

        header('Content-type: application/json');
        echo json_encode($json);
        exit;

    }