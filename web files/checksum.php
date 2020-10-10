<?php

    $checkhash = $_POST['hash'];

    $data = [
        'success' => false,
        'hash' => ''
    ];

    $json = json_decode($data, true);

    $json['hash'] = '4BF2A0C1A79710F5AAADC962E206C36EA4E757A3C2A8CFA9FC7C2A88A3CB1584F82E5380FBCF265753DA246F2219F459F4A744876714061BC6618071D049082F';

    if ($checkhash == '') {
        echo 'ok bud';
        exit;
    }

    if ($checkhash != $json['hash']) {
        $json['success'] = false;

        header('Content-type: application/json');
        echo json_encode($json);
        exit;
    }
    else {
        $json['success'] = true;

        header('Content-type: application/json');
        echo json_encode($json);
        exit;
    }

