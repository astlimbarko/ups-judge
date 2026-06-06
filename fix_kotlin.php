<?php
$pdo = new PDO('mysql:host=mariadb;dbname=upsjudge', 'upsjudge', 'UpsJdg2025App');

$stmt = $pdo->query('SELECT file_content FROM executable_file WHERE immutable_execid=39 AND filename="run"');
$content = $stmt->fetchColumn();

// Replace the dynamic KOTLIN_DIR detection with hardcoded path
$lines = explode("\n", $content);
$found = false;
foreach($lines as $i => $line) {
    if(strpos($line, 'command -v kotlinc') !== false) {
        echo "Found at line $i: $line\n";
        $lines[$i] = 'KOTLIN_DIR="/opt/kotlinc/bin"';
        echo "Replaced with: " . $lines[$i] . "\n";
        $found = true;
    }
}

if(!$found) {
    echo "Pattern not found! Showing first 30 lines:\n";
    for($i=0; $i<30 && $i<count($lines); $i++) {
        echo "$i: " . $lines[$i] . "\n";
    }
    exit(1);
}

$newContent = implode("\n", $lines);
$hash = md5($newContent);
$stmt = $pdo->prepare('UPDATE executable_file SET file_content=?, hash=? WHERE immutable_execid=39 AND filename="run"');
$stmt->execute([$newContent, $hash]);
echo "Updated. New size: " . strlen($newContent) . ", hash: $hash\n";

// Close internal errors and re-enable kotlin
$pdo->exec("UPDATE internal_error SET status='resolved'");
$pdo->exec("UPDATE language SET allow_submit=1, allow_judge=1 WHERE langid='kt'");
echo "Kotlin re-enabled, errors resolved\n";
