#include<Arduino.h>
#include <UniversalTelegramBot.h>

#define BOT_TOKEN "2040806579:AAFrN7RYxL6h260BjmduyIgzJEtwhUg00RY"

unsigned long bot_last_scan_time;
const unsigned long BOT_SCAN_INTERVAL = 100;

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure wifi_secure_client;
UniversalTelegramBot bot(BOT_TOKEN, wifi_secure_client);

const int ledPin = D0;

void setupUTCTime();
void setupTelegramCommands();

void telegramInit() {
  setupUTCTime();
  setupTelegramCommands();
}

void telegramLoop() {

    if(millis() - bot_last_scan_time < BOT_SCAN_INTERVAL) return;
    
    int totalNewMessages = bot.getUpdates(bot.last_message_received + 1);
    
    while (totalNewMessages){
        Serial.print("Nova mensagem: ");
        handleNewMessages(totalNewMessages);
        totalNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    
    bot_last_scan_time = millis();
}

void setupTelegramCommands() {
    String commands = "[{\"command\":\"led_on\", \"description\":\"Liga o LED\"},{\"command\":\"led_off\",\"description\":\"Desliga o LED\"},{\"command\":\"led_status\",\"description\":\"Status do LED\"},{\"command\":\"temperature\",\"description\":\"Retorna a temperatura do ambiente\"},{\"command\":\"humidity\",\"description\":\"Retorna a umidade do ambiente\"},{\"command\":\"th\",\"description\":\"Retorna a temperatura e a umidade do ambiente\"}]";

    bot.setMyCommands(commands);
}

void setupUTCTime() {
  configTime(0, 0, "pool.ntp.org");
  wifi_secure_client.setTrustAnchors(&cert); // Root certificate for api.telegram.org

  // Sync NTP/Time
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);
}

/* MESSAGE CALLBACKS */

void led_on_and_notify(String chat_id) {
    ledTurnOn();
    bot.sendMessage(chat_id, "Led **LIGADO**", "MarkdownV2");
}

void led_off_and_notify(String chat_id) {
    ledTurnOff();
    bot.sendMessage(chat_id, "Led **DESLIGADO**", "Markdown");
}

void led_status_and_notify(String chat_id) {
    int ledStatus = getLedStatus();
    if(ledStatus){
        bot.sendMessage(chat_id, "Led **LIGADO**", "Markdown");
    }else{
        bot.sendMessage(chat_id, "Led **DESLIGADO**", "Markdown");    
    }
}

void temperature(String chat_id) {
    float temperature = dhtGetTemperature();
    String message = "Temperatura atual: " + (String) temperature;
    
    bot.sendMessage(chat_id, message, "");
}

void humidity(String chat_id) {
    float humidity = dhtGetHumidity();
    String message = "Umidade atual: " + (String) humidity;
    
    bot.sendMessage(chat_id, message, "");
}

void th(String chat_id){
    float temperature = dhtGetTemperature();
    float humidity = dhtGetHumidity();

    String message = "Temperatura: " + (String) temperature + "\n" + "Umidade: " + (String) humidity;
    bot.sendMessage(chat_id, message, "");
}

void help(String chat_id){
    String welcome = "Welcome to Universal Arduino Telegram Bot library,.\n";
    welcome += "This is Flash Led Bot example.\n\n";
    welcome += "/ledon : to switch the Led ON\n";
    welcome += "/ledoff : to switch the Led OFF\n";
    welcome += "/led_status : Returns current status of LED\n";
    bot.sendMessage(chat_id, welcome, "Markdown");
}

void handleNewMessages(int numNewMessages){
    
  for (int i = 0; i < numNewMessages; i++){
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;
    String from_name = bot.messages[i].from_name;

    Serial.println(text);
    
    if (from_name == ""){
      from_name = "Otário";
    }

    if (text == "/led_on") led_on_and_notify(chat_id);
    if (text == "/led_off") led_off_and_notify(chat_id);
    if (text == "/led_status") led_status_and_notify(chat_id);
    if (text == "/temperature") temperature(chat_id);
    if (text == "/humidity") humidity(chat_id);
    if (text == "/th") th(chat_id);
    if (text == "/help") help(chat_id);
  }
}
