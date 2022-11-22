<?php
ini_set('display_errors',1);
ini_set('display_startup_errors',1);
error_reporting(E_ALL);

include_once("vendor/autoload.php");
use Yvesniyo\IntouchSms\SmsSimple;
/** @var \Yvesniyo\IntouchSms\SmsSimple */
$messi="Mbega ukuntu bitangaje ntamuntu ufana??";
$sms = new SmsSimple();
$sms->recipients(["0788750979"])
    ->message($messi)
    ->sender("+250780496238")
    ->username("iradukundae")
    ->password("iradukunda@123")
    ->apiUrl("www.intouchsms.co.rw/api/sendsms/.json")
    ->callBackUrl("");
print_r($sms->send());
?>