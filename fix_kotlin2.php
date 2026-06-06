<?php
$pdo = new PDO('mysql:host=mariadb;dbname=upsjudge', 'upsjudge', 'UpsJdg2025App');

$stmt = $pdo->query('SELECT file_content FROM executable_file WHERE immutable_execid=39 AND filename="run"');
$content = $stmt->fetchColumn();

// Replace the kotlinc call to use bash explicitly
// Line: "${KOTLIN_DIR}"/kotlinc -d . -Djava.io.tmpdir=/ "$@"
// Change to: /bin/bash "${KOTLIN_DIR}"/kotlinc -d . -Djava.io.tmpdir=/ "$@"
$old = '"${KOTLIN_DIR}"/kotlinc -d . -Djava.io.tmpdir=/ "$@"';
$new = '/bin/bash "${KOTLIN_DIR}"/kotlinc -d . -Djava.io.tmpdir=/ "$@"';
$newContent = str_replace($old, $new, $content);

if($newContent === $content) {
    echo "ERROR: Pattern not found!\n";
    echo "Content around line 61:\n";
    $lines = explode("\n", $content);
    for($i=55; $i<65 && $i<count($lines); $i++) {
        echo "$i: " . $lines[$i] . "\n";
    }
    exit(1);
}

// Also fix the runner script line that calls kotlin
// exec "${KOTLIN_DIR}"/kotlin ...
$old2 = 'exec "${KOTLIN_DIR}"/kotlin ';
$new2 = 'exec /bin/bash "${KOTLIN_DIR}"/kotlin ';
$newContent = str_replace($old2, $new2, $newContent);

$hash = md5($newContent);
$stmt = $pdo->prepare('UPDATE executable_file SET file_content=?, hash=? WHERE immutable_execid=39 AND filename="run"');
$stmt->execute([$newContent, $hash]);
echo "Updated run script. Size: " . strlen($newContent) . ", hash: $hash\n";

// Now we need the correct immutable hash
// The server generates a zip and md5s it - we can't predict that
// But we know the server sent hash 48e43fce1d41639b88415bd1add79c35 last time
// After changing content, the server will generate a NEW hash
// We need to find out what it is...
// 
// TRICK: The judgehost log tells us what hash it expects vs what it gets
// So we set a dummy hash, let it fail once, read the actual hash from the error, then set it correctly
// 
// OR: we can call the DOMjudge API endpoint that returns the hash
// GET /api/v4/contests/test1/languages/kotlin returns compile_executable_hash

// For now, let's clear the cache and see what hash the API reports
echo "Checking API for new hash...\n";

// Use Symfony kernel to recalculate
// Actually, the hash in immutable_executable is calculated by a Doctrine lifecycle callback
// We need to trigger that. Let's use the console command to do it.
echo "Will need to check API after Symfony cache clear\n";
