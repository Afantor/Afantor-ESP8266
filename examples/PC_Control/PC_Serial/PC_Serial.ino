/*这篇把8266作为TCPcleint，加入电脑创建的tcpServer中来控制一个继电器*/
 
#include <ESP8266WiFi.h>
 
#define relayPin    2                   //继电器连接在ESP8266的GPIO2上

const char *ssid     = "TP_LINK_6960";  //这里是我的路由器wifi，你使用时修改为你要连接的wifi ssid
const char *password = "123456789";     //你要连接的wifi密码
const char *host = "192.168.0.100";     //修改为你建立的Server服务端的IP地址，即你的PC电脑在路由器上的IP
WiFiClient client;
const int tcpPort = 8266;               //修改为你建立的Server服务端的端口号
 
 
void setup()
{
    Serial.begin(115200);    
    pinMode(relayPin,OUTPUT);
    delay(10);
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");     //写几句提示，哈哈
    Serial.println(ssid);
 
    WiFi.begin(ssid, password);
 
    while (WiFi.status() != WL_CONNECTED)//WiFi.status() ，这个函数是wifi连接状态，返回wifi链接状态
                                         //这里就不一一赘述它返回的数据了，有兴趣的到ESP8266WiFi.cpp中查看
    {
        delay(500);
        Serial.print(".");
    }//如果没有连通向串口发送.....
 
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());//WiFi.localIP()返回8266获得的ip地址
}
 
 
void loop()
{
    while (!client.connected())//几个非连接的异常处理
    {
        if (!client.connect(host, tcpPort))
        {
            Serial.println("connection....");
            //client.stop();
            delay(500);
 
        }
    }
 
    while (client.available())//available()同ARDUINO，不解释了
    {
        char val = client.read();//read()同arduino
        if(val=='a'){//pc端发送0和1来控制
           digitalWrite(relayPin, LOW);
        }
        if(val=='b')
        {
            digitalWrite(relayPin, HIGH);
        }
    }
}