<!DOCTYPE html>
<html>
<head>
    <title>CY243L</title>
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css">
</head>
<body>
    <nav class="navbar navbar-expand-lg navbar-light bg-light">
        <a class="navbar-brand" href="https://github.com/theflash2k/CY243-L">CY243L</a>
    </nav>

    <div class="container mt-5">
        <div class="row justify-content-center">
            <div class="col-md-6">
                <div class="text-center">
                    <h3>Enter the page name you want to load</h3>
                </div>
                <form method="get" action="index.php">
                    <div class="input-group mb-3">
                        <input type="text" class="form-control" placeholder="Page Name" name="page">
                        <div class="input-group-append">
                            <button class="btn btn-primary" type="submit">Load</button>
                        </div>
                    </div>
                </form>
            </div>
        </div>
    </div>
    <script src="https://code.jquery.com/jquery-3.5.1.slim.min.js"></script>
    <script src="https://cdn.jsdelivr.net/npm/@popperjs/core@2.5.3/dist/umd/popper.min.js"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/js/bootstrap.min.js"></script>
</body>
</html>

<?php
if (isset($_GET['page'])) {
    try {
        echo '<div class="text-center"><pre>';
        include($_GET['page']);
        echo '</pre></div>';
        if (file_exists($_GET['page'])) {
            echo '<div class="text-center"><pre style="color: green;">Loaded '. $_GET['page'] . ' successfully..</pre></div>';
        }
        else {
            echo '<div class="text-center"><pre style="color: red;">Failed to load '. $_GET['page'] . '...</pre></div>';
        }
    }
    catch (Exception $e) {
        echo '<div class="text-center"><pre style="color: red;">Failed to load '. $_GET['page'] . '...</pre></div>';
    }
}
?>
