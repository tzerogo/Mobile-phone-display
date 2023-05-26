#include <ESP8266WiFi.h>

char* ssid     = "esp8266tz";
char* password = "111222333";
const int x_size=3,y_size=4;

char temp[4000]; //网页显示内容
String rx_data="";
String serial_test="";
int i=0;

String p_x[x_size]="",p_y[y_size]="";
String p_x_sum="",p_y_sum="";

WiFiServer server(80);



void setup()
{
  
    Serial.begin(115200);
    delay(10);
    // 程序从连接一个wifi网络开始
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.print("IP adress: ");
    Serial.println(WiFi.localIP());
    server.begin();

    
}

void loop(){
  if(Serial.available()>0){
    while(Serial.available()>0){
      rx_data+=char(Serial.read());
      delay(2);
    }
    serial_test=rx_data;
    rx_data="";
    Serial.println(":"+serial_test);
    if(serial_test[0]=='0'&&serial_test[1]=='x'&&serial_test[2]=='5'&&serial_test[3]=='5'){
      Serial.println("serial start");
      serialEvent();
    }else{
      serial_test="";
    }
  }
  
  WiFiClient client = server.available();   // 监听新连接的客户端11111111111111111111111111111111111111111111111111111111111111111111111
  

  //snprintf (temp, 2000,"<html> <head> <meta http-equiv='refresh' content='5000' charset='utf-8' /> <title>特性曲线</title> <style> body { background-color: #ffffff; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; } canvas { margin:0 auto; display:block; } </style> </head> <body> <h1 style='text-align:center'>特征曲线</h1> <!-- 创建画布 --> <canvas id='cavsElem'> </canvas> <p></p> <canvas id='cavsElem2'> </canvas> <p>|</p><p>|</p><p>|</p><p>|</p><p>|</p><p>|</p><p>|</p><p>|</p><p>|</p><p>|</p><p>|</p><p>|</p><p>|</p><p>|</p><p>|</p><p>|</p><p>|</p><p>|</p><p>|</p><p>|</p><p>|</p> <!-- 此处%s会被输出语句最后的变量值代换 --> <p>test1x: </p> <!-- <p id='x_sum'></p> --> <p id='x_sum'>1 2 3 4 5 6 7 8 9 10 11 12 13.2 13.5 13.6 13.8 14 14.5 15 16 17</p> <p>test1y: </p> <!-- <p id='y_sum'></p> --> <p id='y_sum'>0 0 0 0 0 0 0 0 0 0.1 0.3 0.6 1.3 1.8 2 3 7 30 50</p> <p>test2x: </p> <p id='xc_sum'>0.05 0.2 0.3 0.4 1 1.6 2.7 3.84  5 6 7 8 9 10 11 12 13 14 14.5 15 16 17</p> <p>test2y: </p> <p id='y1_sum'>4 6 7.8 8.4 9.1 9.4 9.7 9.95 10 10 10 10 10 10 10 10 10 10 10 10 </p> <p id='y2_sum'>3 5 5.8 6.3 7.2 7.6 7.9 8 8 8 8 8 8 8 8 8 8 8 8 8 </p> <p id='y3_sum'>0.1 0.7 0.9 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1</p> <p id='test'>0000</p> <script> var x_sum=document.getElementById('x_sum'); var p_x_s=x_sum.innerHTML.split(' '); var y_sum=document.getElementById('y_sum'); var p_y_s=y_sum.innerHTML.split(' '); var xc_sum=document.getElementById('xc_sum'); var p_xc_s=xc_sum.innerHTML.split(' '); var y1_sum=document.getElementById('y1_sum'); var p_y1_s=y1_sum.innerHTML.split(' '); var y2_sum=document.getElementById('y2_sum'); var p_y2_s=y2_sum.innerHTML.split(' '); var y3_sum=document.getElementById('y3_sum'); var p_y3_s=y3_sum.innerHTML.split(' '); document.getElementById('test').innerHTML=p_x_s[2]; </script> <script type='text/javascript'> var canvas = document.getElementById('cavsElem'); var context = canvas.getContext('2d'); // getContext('2d') 对象是内建的 HTML5 对象，拥有多种绘制路径、矩形、圆形、字符以及添加图像的方法。 canvas.width = 450; canvas.height = 500; canvas.style.border = '4px solid #A9A9A9'; context.beginPath(); context.moveTo(50, 10); context.lineTo(50, 450); context.moveTo(50, 450); context.lineTo(400, 450); context.moveTo(40, 20); context.lineTo(50, 10); context.lineTo(60, 20); context.moveTo(390, 440); context.lineTo(400, 450); context.lineTo(390, 460); function power(context) { var x_int= new Array(); var y_int= new Array(); for(i=0;i<100;i++) { x_int[i]=parseFloat(p_x_s[i]); y_int[i]=parseFloat(p_y_s[i]); } var x = 0,y=0; context.moveTo(50 , 450);  // 原点 for (var i = 0; i <100; i++) { x = 20*x_int[i]; y = 20*y_int[i]; context.lineTo(50+x, 450-y); } } power(context); context.stroke(); //画出路径 context.font='25px Arial'; context.fillText('输入特性曲线',135,490); </script> <script type='text/javascript'> var canvas  = document.getElementById('cavsElem2'); var context = canvas.getContext('2d'); // getContext('2d') 对象是内建的 HTML5 对象，拥有多种绘制路径、矩形、圆形、字符以及添加图像的方法。 canvas.width = 450; canvas.height = 500; canvas.style.border = '4px solid #A9A9A9'; context.beginPath(); context.moveTo(50, 10); context.lineTo(50, 450); context.moveTo(50, 450); context.lineTo(400, 450); context.moveTo(40, 20); context.lineTo(50, 10); context.lineTo(60, 20); context.moveTo(390, 440); context.lineTo(400, 450); context.lineTo(390, 460); function power(context) { var xc_int= new Array(); var y1_int= new Array(); var y2_int= new Array(); var y3_int= new Array(); for(i=0;i<100;i++) { xc_int[i]=parseFloat(p_xc_s[i]); y1_int[i]=parseFloat(p_y1_s[i]); y2_int[i]=parseFloat(p_y2_s[i]); y3_int[i]=parseFloat(p_y3_s[i]); } var x = 0, y = 0 ; context.moveTo(50 , 450);  // 原点 for (var i = 0; i <100; i++) { x = 20*xc_int[i]; y = 23*y1_int[i]; context.lineTo(50+x, 450-y); } context.moveTo(50 , 450);  // 原点 for (var i = 0; i <100; i++) { x = 20*xc_int[i]; y = 20*y2_int[i]; context.lineTo(50+x, 450-y); } context.moveTo(50 , 450);  // 原点 for (var i = 0; i <100; i++) { x = 20*xc_int[i]; y = 10*y3_int[i]; context.lineTo(50+x, 450-y); } } power(context); context.stroke(); //画出路径 context.font='25px Arial'; context.fillText('输出特性曲线',135,490); </script> </body> </html>");
snprintf (temp, 4000,"<html> <head> <meta http-equiv='refresh' content='5000' charset='utf-8' /> <title>特性曲线</title> <style> body { background-color: #ffffff; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; } canvas { margin:0 auto; display:block; } </style> </head> <body> <h1 style='text-align:center'>特征曲线</h1> <canvas id='cavsElem'> </canvas> <p></p> <canvas id='cavsElem2'> </canvas> <p>|</p><p>|</p><p>|</p><p>|</p><p>|</p><p>|</p><p>|</p><p>|</p><p>|</p><p>|</p><p>|</p><p>|</p><p>|</p><p>|</p><p>|</p><p>|</p><p>|</p><p>|</p><p>|</p><p>|</p><p>|</p> <p>test1x: </p> <p id='x_sum'>1 2 3 4 5 6 7 8 9 10 11 12 13.2 13.5 13.6 13.8 14 14.5 15 16 17</p> <p>test1y: </p> <p id='y_sum'>0 0 0 0 0 0 0 0 0 0.1 0.3 0.6 1.3 1.8 2 3 7 30 50</p> <p>test2x: </p> <p id='xc_sum'>0.05 0.2 0.3 0.4 1 1.6 2.7 3.84  5 6 7 8 9 10 11 12 13 14 14.5 15 16 17</p> <p>test2y: </p> <p id='y1_sum'>4 6 7.8 8.4 9.1 9.4 9.7 9.95 10 10 10 10 10 10 10 10 10 10 10 10 </p> <p id='y2_sum'>3 5 5.8 6.3 7.2 7.6 7.9 8 8 8 8 8 8 8 8 8 8 8 8 8 </p> <p id='y3_sum'>0.1 0.7 0.9 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1</p> <p id='test'>0000</p> <script> var x_sum=document.getElementById('x_sum'); var p_x_s=x_sum.innerHTML.split(' '); var y_sum=document.getElementById('y_sum'); var p_y_s=y_sum.innerHTML.split(' '); var xc_sum=document.getElementById('xc_sum'); var p_xc_s=xc_sum.innerHTML.split(' '); var y1_sum=document.getElementById('y1_sum'); var p_y1_s=y1_sum.innerHTML.split(' '); var y2_sum=document.getElementById('y2_sum'); var p_y2_s=y2_sum.innerHTML.split(' '); var y3_sum=document.getElementById('y3_sum'); var p_y3_s=y3_sum.innerHTML.split(' '); document.getElementById('test').innerHTML=p_x_s[2]; </script> <script type='text/javascript'> var canvas = document.getElementById('cavsElem'); var context = canvas.getContext('2d'); canvas.width = 450; canvas.height = 500; canvas.style.border = '4px solid #A9A9A9'; context.beginPath(); context.moveTo(50, 10); context.lineTo(50, 450); context.moveTo(50, 450); context.lineTo(400, 450); context.moveTo(40, 20); context.lineTo(50, 10); context.lineTo(60, 20); context.moveTo(390, 440); context.lineTo(400, 450); context.lineTo(390, 460); function power(context) { var x_int= new Array(); var y_int= new Array(); for(i=0;i<100;i++) { x_int[i]=parseFloat(p_x_s[i]); y_int[i]=parseFloat(p_y_s[i]); } var x = 0,y=0; context.moveTo(50 , 450); for (var i = 0; i <100; i++) { x = 20*x_int[i]; y = 20*y_int[i]; context.lineTo(50+x, 450-y); } } power(context); context.stroke(); context.font='25px Arial'; context.fillText('输入特性曲线',135,490); </script> <script type='text/javascript'> var canvas  = document.getElementById('cavsElem2'); var context = canvas.getContext('2d'); canvas.width = 450; canvas.height = 500; canvas.style.border = '4px solid #A9A9A9'; context.beginPath(); context.moveTo(50, 10); context.lineTo(50, 450); context.moveTo(50, 450); context.lineTo(400, 450); context.moveTo(40, 20); context.lineTo(50, 10); context.lineTo(60, 20); context.moveTo(390, 440); context.lineTo(400, 450); context.lineTo(390, 460); function power(context) { var xc_int= new Array(); var y1_int= new Array(); var y2_int= new Array(); var y3_int= new Array(); for(i=0;i<100;i++) { xc_int[i]=parseFloat(p_xc_s[i]); y1_int[i]=parseFloat(p_y1_s[i]); y2_int[i]=parseFloat(p_y2_s[i]); y3_int[i]=parseFloat(p_y3_s[i]); } var x = 0, y = 0 ; context.moveTo(50 , 450); for (var i = 0; i <100; i++) { x = 20*xc_int[i]; y = 23*y1_int[i]; context.lineTo(50+x, 450-y); } context.moveTo(50 , 450); for (var i = 0; i <100; i++) { x = 20*xc_int[i]; y = 20*y2_int[i]; context.lineTo(50+x, 450-y); } context.moveTo(50 , 450); for (var i = 0; i <100; i++) { x = 20*xc_int[i]; y = 10*y3_int[i]; context.lineTo(50+x, 450-y); } } power(context); context.stroke(); context.font='25px Arial'; context.fillText('输出特性曲线',135,490); </script> </body> </html>");                                          
                                            //snprintf (temp, 2000,"");11111111111111111111111111111111111111111111111111111111111111
  //snprintf (temp, 2000,"<html><head><meta http-equiv='refresh' content='5000' charset='utf-8'/><title>周期波形</title><style>body{background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }</style></head><body><canvas id='cavsElem'></canvas><h1>波形信息与显示</h1><p>f(kHz)：</p><p id='f'>%s</p><p>THDx(°/。)：</p><p id='thdx'>%s</p><p>归一化波形: </p><p>一次谐波: </p><p id='a1'>%s</p><p>二次谐波: </p><p id='a2'>%s</p><p>三次谐波：</p><p id='a3'>%s</p><p>四次谐波：</p><p id='a4'>%s</p><p>五次谐波：</p><p id='a5'>%s,%d,%d,%d,%d</p><script type='text/javascript'>var canvas = document.getElementById('cavsElem');var context = canvas.getContext('2d');canvas.width = 400;canvas.height = 500;canvas.style.border='1px solid #000';context.beginPath();context.moveTo(50,10);context.lineTo(50,500);context.moveTo(50,250);context.lineTo(400,250);context.moveTo(40,20);context.lineTo(50,10); context.lineTo(60,20);context.moveTo(390,240);context.lineTo(400,250); context.lineTo(390,260);function power(context){var x=0;context.moveTo(50+x,250);      var box3=document.getElementById('a1');var box33=parseFloat(box3.innerText);  var box4=document.getElementById('a2');var box44=parseFloat(box4.innerText); var box5=document.getElementById('a3');var box55=parseFloat(box5.innerText);  var box6=document.getElementById('a4');var box66=parseFloat(box6.innerText);  var box7=document.getElementById('a5');var box77=parseFloat(box7.innerText);      for(var i=1;i<=500;i++){x=i/50; y=Math.sin(x)*box33+Math.sin(2*x)*box44+Math.sin(3*x)*box55+Math.sin(4*x)*box66+Math.sin(5*x)*box77;b=250-80*y;context.lineTo(50*x+50,b);}}power(context);context.stroke();</script></body></html>");
  
  if(client){                             // 如果有客户端连接
    Serial.println("New Client.");          // 打印信息到串口
    String currentLine = "";                // 创建一个字符串来保存来自客户端的传入数据
    while (client.connected()) {           // 当客户端连接时保持循环
      if (client.available()) {           // 如果有来自客户端的数据可以读取
        char c = client.read();             // 读取一个字节
        //Serial.write(c);                    // 打印到串口
        if (c == '\n') {                    // 如果是换行符

          // 如果当前行为空，在一行中会有两个换行符。
          // 这是客户端HTrP请求的结束标志，所以发送一个响应:
          if (currentLine.length() == 0) {
            // HTTP 头经常以一串响应代码开始，即(e.g. HTTP/1.1 200 OK)
            // 然后是一个内容类型，这样客户就知道收到了什么，然后是一个空白行:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            client.println(temp);

            //跳出循环
            break;
          } else {    //如果你收到了新行，则清空currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // //如果收到除回车符以外的其他字符，
          currentLine += c;      // 将其加到currentLine的末尾
        }

      }
    }
  }
}


//串口中断入口
 void serialEvent() 
{

  for (i=0;i<x_size;i++){
    
        while(true)
        {
          rx_data="";
          while(Serial.available()>0)
          {
            rx_data+=char(Serial.read());
            delay(10);
          }
          if(rx_data!="")
          {
            p_x[i]=rx_data;
            p_x_sum+=rx_data;
            p_x_sum+=' ';
            rx_data="";
            delay(2);
            break;
          }
        }
        
  }
  
  Serial.println(p_x_sum);
  

  for (i=0;i<y_size;i++){
    
        while(true)
        {
          rx_data="";
          while(Serial.available()>0)
          {
            rx_data+=char(Serial.read());
            delay(10);
          }
          if(rx_data!="")
          {
            p_y[i]=rx_data;
            p_y_sum+=rx_data;
            p_y_sum+=' ';
            rx_data="";
            delay(2);
            break;
          }
        }

  }

  
  Serial.println(p_y_sum);


}
