<?php
ini_set('display_errors',1);
ini_set('display_startup_errors',1);
error_reporting(E_ALL);
require '../php-includes/connect.php';
require 'php-includes/check-login.php';
if(isset($_POST['save'])){
    $names=$_POST['names'];
    $price=$_POST['price'];
    $sql ="INSERT INTO products(name, price) VALUES (?,?)";
    $stm = $db->prepare($sql);
    if ($stm->execute(array($names,$price))) {
        print "<script>alert('product added');window.location.assign('products.php')</script>";

    } else{
        echo "<script>alert('Error! try again');window.location.assign('products.php')</script>";
}
}
?>
<!DOCTYPE html>
<html lang="en">

<head>

    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta name="description" content="">
    <meta name="author" content="">

    <title>Admin - settings</title>

    <!-- Bootstrap Core CSS -->
    <link href="../vendor/bootstrap/css/bootstrap.min.css" rel="stylesheet">

    <!-- MetisMenu CSS -->
    <link href="../vendor/metisMenu/metisMenu.min.css" rel="stylesheet">

    <!-- DataTables CSS -->
    <link href="../vendor/datatables-plugins/dataTables.bootstrap.css" rel="stylesheet">

    <!-- DataTables Responsive CSS -->
    <link href="../vendor/datatables-responsive/dataTables.responsive.css" rel="stylesheet">

    <!-- Custom CSS -->
    <link href="../dist/css/sb-admin-2.css" rel="stylesheet">

    <!-- Custom Fonts -->
    <link href="../vendor/font-awesome/css/font-awesome.min.css" rel="stylesheet" type="text/css">

    <!-- HTML5 Shim and Respond.js IE8 support of HTML5 elements and media queries -->
    <!-- WARNING: Respond.js doesn't work if you view the page via file:// -->
    <!--[if lt IE 9]>
        <script src="https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js"></script>
        <script src="https://oss.maxcdn.com/libs/respond.js/1.4.2/respond.min.js"></script>
    <![endif]-->

</head>

<body>

    <div id="wrapper">

        <!-- Navigation -->
        <?php require 'php-includes/nav.php';?>

        <div id="page-wrapper">
            <div class="row">
                <div class="col-lg-12">
                    <h1 class="page-header">Settings</h1>
                </div>
                <!-- /.col-lg-12 -->
            </div>
            <!-- /.row -->
            <div class="row">
                <div class="col-lg-12">
                    <div class="panel panel-default">
                        <div class="panel-heading">
                            You can update your details
                        </div>
                        <!-- /.panel-heading -->
                        <div class="panel-body">
                        <div class="panel-body">
                        <div class="row">
                            <div class="col-lg-6">
                            <?php
                                    $query = "SELECT * FROM admin WHERE email= ? limit 1";
                                    $stmt = $db->prepare($query);
                                    $stmt->execute(array($_SESSION['code']));
                                    $rows = $stmt->fetch(PDO::FETCH_ASSOC);
                                    if ($stmt->rowCount()>0) {
                                      $names=$rows['names'];
                                      $email=$rows['email'];
                                      $address=$rows['address'];
                                      $telephone=$rows['phone'];
                                    }
                                    if(isset($_POST['update'])){
                                    $uaddress=$_POST['address'];
                                    $uphone=$_POST['phone'];
                                    $cpassword=md5($_POST['cpassword']);
                                    $apassword=md5($_POST['apassword']);
                                    if ($apassword == $cpassword){
                                        if($apassword == $cpassword){
                                            $sql ="UPDATE admin SET address = ?, phone = ? , password = ? WHERE email = ?";
                                            $stm = $db->prepare($sql);
                                            if ($stm->execute(array($uaddress, $uphone, $cpassword, $_SESSION['code']))) {
                                                print "<script>alert('your data updated');window.location.assign('settings.php')</script>";

                                                }
                                        } else{
                                            echo "<script>alert('Passwords are not match');window.location.assign('settings.php')</script>";
                                        }
                                    } else{
                                        echo "<script>alert('Passwords are not match');window.location.assign('account.php')</script>";
                                    }
                                    }
                                    ?>
                                    <form method="post">
                                        <div class="form-group">
                                            <label>Names</label>
                                            <input class="form-control" value="<?php echo $names?>" disabled>
                                        </div>
                                        <div class="form-group">
                                            <label>Email</label>
                                            <input class="form-control" value="<?php echo $email?>" disabled>
                                        </div>
                                        <div class="form-group">
                                            <label>Address</label>
                                            <input class="form-control" value="<?php echo $address?>" name="address">
                                        </div>
                                        <div class="form-group">
                                            <label>Mobile number</label>
                                            <input class="form-control" value="<?php echo $telephone?>" name="phone">
                                        </div>
                                        <div class="form-group">
                                            <label>Password</label>
                                            <input class="form-control" type="password" name="cpassword">
                                        </div>
                                        <div class="form-group">
                                            <label>Confirm password</label>
                                            <input class="form-control" type="password" name="apassword">
                                        </div>
                                        <div class="form-group">
                                        <button type="submit" class="btn btn-success" name="update"><span class="glyphicon glyphicon-check"></span> Update</button>
                                        </div>
                                    </form>
                            </div>
                        </div>
                    </div>
                        </div>
                        <!-- /.panel-body -->
                    </div>
                    <!-- /.panel -->
                </div>
                <!-- /.col-lg-12 -->
            </div>
        </div>
        <!-- /#page-wrapper -->

    </div>
    <!-- /#wrapper -->

    <!-- jQuery -->
    <script src="../vendor/jquery/jquery.min.js"></script>

    <!-- Bootstrap Core JavaScript -->
    <script src="../vendor/bootstrap/js/bootstrap.min.js"></script>

    <!-- Metis Menu Plugin JavaScript -->
    <script src="../vendor/metisMenu/metisMenu.min.js"></script>

    <!-- DataTables JavaScript -->
    <script src="../vendor/datatables/js/jquery.dataTables.min.js"></script>
    <script src="../vendor/datatables-plugins/dataTables.bootstrap.min.js"></script>
    <script src="../vendor/datatables-responsive/dataTables.responsive.js"></script>

    <!-- Custom Theme JavaScript -->
    <script src="../dist/js/sb-admin-2.js"></script>

    <!-- Page-Level Demo Scripts - Tables - Use for reference -->
    <script>
    $(document).ready(function() {
        $('#dataTables-example').DataTable({
            responsive: true
        });
    });
    </script>

</body>

</html>