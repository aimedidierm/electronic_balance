<?php
ini_set('display_errors',1);
ini_set('display_startup_errors',1);
error_reporting(E_ALL);
require 'php-includes/connect.php';
include_once("vendor/autoload.php");
use Yvesniyo\IntouchSms\SmsSimple;
//product price
if(isset($_POST['product'])){
    $product=$_POST['product'];
    $query = "SELECT * FROM products WHERE id = ?";
    $stmt = $db->prepare($query);
    $stmt->execute(array($product));
    $rows = $stmt->fetch(PDO::FETCH_ASSOC);
    $price=$rows['price'];
    $data = array('p' =>$price,'a' =>'1'); 
    echo $response = json_encode($data)."\n";
}
if(isset($_POST['bill'])){
    $product=$_POST['product'];
    $phone=$_POST['phone'];
    $total=$_POST['total'];
    $amount=$_POST['amount'];
    $mass=$_POST['mass'];
    $left=$total-$amount;
    //product name
    $query = "SELECT * FROM products WHERE id = ?";
    $stmt = $db->prepare($query);
    $stmt->execute(array($product));
    $rows = $stmt->fetch(PDO::FETCH_ASSOC);
    $productname=$rows['name'];
    $sql ="INSERT INTO sales(product_id,weight,price,payed,client) VALUES (?,?,?,?,?)";
    $stm = $db->prepare($sql);
    $stm->execute(array($product,$mass,$total,$left,$phone));
    /** @var \Yvesniyo\IntouchSms\SmsSimple */
    $messi="Dear customer you have bought ".$mass."Kg of ".$productname." you have paid ".$amount." Rwf you left with ".$left." Rwf, Thank you!";
    $sms = new SmsSimple();
    $sms->recipients([$phone])
        ->message($messi)
        ->sender("+250780496238")
        ->username("iradukundae")
        ->password("iradukunda@123")
        ->apiUrl("www.intouchsms.co.rw/api/sendsms/.json")
        ->callBackUrl("");
    print_r($sms->send());
}
?>