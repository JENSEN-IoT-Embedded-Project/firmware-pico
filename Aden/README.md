För att Python koden ska kunna köras så måste både Telegram biblioteket, LCD biblioteket och MQTT biblioteket laddas upp på Picon.

1. Koppla in picon till datorn
2. Öppna Thonny och tryck på "File" längst upp til vänster
3. Tryck på "Open" och välj "This computer"
4. leta upp filen "simple.py" i "MQTT Library" mappen och välj den
5. Filen kommer öppnas i Thonny, tryck sedan på "File" igen längst upp till vänster
6. tryck på "Save as" och välj "Raspberry Pi Pico"
7. Skriv samma namn som filen, alltså "simple.py" och tryck sedan "OK"

Nu är filen sparad på picon, repetera samma steg för att spara "Telegram.py" och "pico_i2c_lcd.py".

För att picon ska kopplas till Wifi behöver du fylla i namnet på din WIFI (SSID) och lösenordet.

Du behöver även välja rätt GPIO Pin för Ultrasonic sensorn beroende på hur du har kopplat in den i Picon. Samma gäller LCD skärmen och Buzzer (lilla högtalaren).

Jag har redan fyllt i uppgifterna för min MQTT broker om du inte har en egen men om du har en egen så ändra de uppgifterna också.

Sist behöver du ändra uppgifterna till Telegram boten, alltså CHAT_ID och TELEGRAM_BOT_TOKEN så att du kan få notiser till din telefon.
