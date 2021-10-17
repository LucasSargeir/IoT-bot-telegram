#include <Arduino.h>
#include <UniversalTelegramBot.h>


#define BOT_TOKEN "2040806579:AAFrN7RYxL6h260BjmduyIgzJEtwhUg00RY"

unsigned long bot_last_scan_time;
const unsigned long BOT_SCAN_INTERVAL = 100;


X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure wifi_secure_client;
UniversalTelegramBot bot(BOT_TOKEN, wifi_secure_client);


void setupUTCTime();
void setupTelegramCommandsDescription();




void telegramInit() {
    setupUTCTime();
    setupTelegramCommandsDescription();
}



void telegramLoop() {
    if(millis() - bot_last_scan_time < BOT_SCAN_INTERVAL) return;
    
    int totalNewMessages = bot.getUpdates(bot.last_message_received + 1);
    
    while (totalNewMessages){
        Serial.print("Nova solicitação: ");
        handleNewMessages(totalNewMessages);
        totalNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    
    bot_last_scan_time = millis();
}




void setupTelegramCommandsDescription() {
    String commands ="[";
    commands += "          {\"command\":\"led_on\",     \"description\":\"Liga o LED\"},";
    commands += "          {\"command\":\"led_off\",    \"description\":\"Desliga o LED\"},";
    commands += "          {\"command\":\"led_blink\",    \"description\":\"Pisca o LED\"},";
    commands += "          {\"command\":\"led_status\", \"description\":\"Status do LED\"},";
    commands += "          {\"command\":\"temperature\",\"description\":\"Retorna a temperatura do ambiente\"},";
    commands += "          {\"command\":\"humidity\",   \"description\":\"Retorna a umidade do ambiente\"},";
    commands += "          {\"command\":\"th\",         \"description\":\"Retorna a temperatura e a umidade do ambiente\"},";
    commands += "          {\"command\":\"help\",       \"description\":\"Lista os possiveis comandos\"}";
    commands += "     ]";
    bot.setMyCommands(commands);
}



void setupUTCTime() {
    Serial.println("--- configurando UTC ---");
    
    configTime(0, 0, "pool.ntp.org");
    wifi_secure_client.setTrustAnchors(&cert); // Root certificate for api.telegram.org

    // Sync NTP/Time
    time_t now = time(nullptr);
    while (now < 24 * 3600){
      delay(100);
      now = time(nullptr);
    }
    Serial.println("--- UTC configurado com sucesso ---");
}



/* ---------------------------------- MESSAGE CALLBACKS ------------------------------------ */

void led_on_and_notify(String chat_id) {
    ledTurnOn();
    bot.sendMessage(chat_id, "Led *LIGADO*", "Markdown");
}



void led_off_and_notify(String chat_id) {
    ledTurnOff();
    bot.sendMessage(chat_id, "Led *DESLIGADO*", "Markdown");
}

void led_blink_and_notify(String chat_id){
    ledBlink(100);
    bot.sendMessage(chat_id, "Led *PISCOU*", "Markdown");
}



void led_status_and_notify(String chat_id) {
    int ledStatus = getLedStatus();
    if(ledStatus){
        bot.sendMessage(chat_id, "Led *LIGADO*", "Markdown");
    }else{
        bot.sendMessage(chat_id, "Led *DESLIGADO*", "Markdown");    
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



void help(String chat_id, String username){
    String welcome = "Bem vindo ao Tuledbot " + username + " 😁. Aqui você pode acender e apagar leds, e além disso, ficar por dentro da temperatura e umidade do seu ambiente!\n\n";
    welcome += "Utilize os comandos abaixo para as ações:\n\n";
    welcome += "*/led_on*: Acender o led\n";
    welcome += "*/led_off*: Apagar o led\n";
    welcome += "*/led_blink*: Piscar o led\n";
    welcome += "*/led_status*: Verificar o status do led\n";
    welcome += "*/temperature*: Verificar a temperatura do ambiente\n";
    welcome += "*/humidity*: Verificar a umidade do ambiente\n";
    welcome += "*/th*: Verificar a temperatura e a umidade do ambiente\n";
    welcome += "*/help*: Listar comandos\n";
    bot.sendMessage(chat_id, welcome, "Markdown");
}



void handleNewMessages(int numNewMessages){
    for (int i = 0; i < numNewMessages; i++){
        String chat_id = bot.messages[i].chat_id;
        String text = bot.messages[i].text;
        String from_name = bot.messages[i].from_name;
    
        Serial.println(text);
        
        if (from_name == ""){
          from_name = "desconhecido";
        }
    
        if (text == "/led_on") led_on_and_notify(chat_id);
        if (text == "/led_off") led_off_and_notify(chat_id);
        if (text == "/led_blink") led_blink_and_notify(chat_id);
        if (text == "/led_status") led_status_and_notify(chat_id);
        if (text == "/temperature") temperature(chat_id);
        if (text == "/humidity") humidity(chat_id);
        if (text == "/th") th(chat_id);
        if (text == "/help" || text == "/start") help(chat_id, from_name);
    }
}
