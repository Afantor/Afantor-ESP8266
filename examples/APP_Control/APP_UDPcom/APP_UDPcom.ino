#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
 
const char *ssid = "MyWIFI";//这里是我的wifi，你使用时修改为你要连接的wifi ssid
const char *password = "123123123";//你要连接的wifi密码
const char *UDPhost = "255.255.255.255";//局域网全网UDP广播地址，也可以使用你本地网段后缀为255也行，不过适应能力就弱了
WiFiClient client;
const int udpPort = 4321;//修改为你建立的Server服务端的端口号
unsigned int localPort = 3888;//UDP端口侦听
char packetBuffer[255]; //存放接收到的UDP数据
char  whoamiBuffer[128]="Udp Test01";
char  ReplyBuffer[255] = "I Received packet!";       // 回复广播发送者
WiFiUDP Udp;
 
void setup()
{
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");//写几句提示，哈哈
  Serial.println(ssid);
  WiFi.begin(ssid, password);//连接WIFI热点
 
  while (WiFi.status() != WL_CONNECTED)//WiFi.status() ，这个函数是wifi连接状态，返回wifi链接状态
  {
    delay(500);
    Serial.print(".");//如果没有连通向串口发送.....
  }
 
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());//WiFi.localIP()返回8266获得的本机ip地址
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");//整几个高大上的数字，比如信号强度啥米的，呵呵
 
  // 开始UDP端口侦听
  Udp.begin(localPort);
 
  //先把自己是谁广播出去
  Udp.beginPacket(UDPhost, udpPort);
  Udp.write(whoamiBuffer); 
  Udp.endPacket();
  Serial.println(UDPhost);
}
void loop()
{
 
  //UDP广播数据到达处理
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remoteIp = Udp.remoteIP();//获取远程广播包发送IP
    Serial.print(remoteIp);
    Serial.print(", port ");
    Serial.println(Udp.remotePort());
 
    // 将到达的数据包读入packetBufffer
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
    }
    Serial.println("Contents:");
    Serial.println(packetBuffer);
 
    // 回复信息给广播发送IP
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
//    strcat(ReplyBuffer,Udp.remoteIP());
    Udp.write(Udp.remoteIP());
    Udp.write(ReplyBuffer);
    Udp.endPacket();
  }
}
