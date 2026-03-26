#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// ─────────────────────────────────────────────
//  LCD  (I2C address 0x27, 16 columns, 2 rows)
// ─────────────────────────────────────────────
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ─────────────────────────────────────────────
//  DHT11
// ─────────────────────────────────────────────
#define DHTPIN  2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ─────────────────────────────────────────────
//  Rain Sensor (DSK MH-RD)
// ─────────────────────────────────────────────
#define RAIN_DO 3      // Digital  OUT  pin of rain module
#define RAIN_AO A0     // Analog   OUT  pin of rain module

// ─────────────────────────────────────────────
//  MQ135 Air-Quality Sensor
// ─────────────────────────────────────────────
#define GAS_DO  4      // Digital  OUT  pin of MQ135
#define GAS_AO  A1     // Analog   OUT  pin of MQ135

// ─────────────────────────────────────────────
//  Thresholds
// ─────────────────────────────────────────────
#define GAS_CLEAN    30   // % below → Clean air
#define GAS_MODERATE 60   // % below → Moderate pollution

void setup() {
  Serial.begin(9600);

  // Sensor init
  dht.begin();
  pinMode(RAIN_DO, INPUT);
  pinMode(GAS_DO,  INPUT);

  // LCD init
  lcd.init();
  lcd.backlight();

  // Splash screen
  lcd.setCursor(0, 0);
  lcd.print("  Weather Watch ");
  lcd.setCursor(0, 1);
  lcd.print("  Initializing..");
  delay(2000);
  lcd.clear();
}

void loop() {

  // ── Read DHT11 ──────────────────────────────
  float temp = dht.readTemperature();   // °C
  float hum  = dht.readHumidity();      // %

  if (isnan(temp) || isnan(hum)) {
    lcd.setCursor(0, 0);
    lcd.print("DHT Read Error! ");
    Serial.println("ERROR: DHT11 read failed");
    delay(2000);
    return;
  }

  // ── Read Rain Sensor ────────────────────────
  int rainD = digitalRead(RAIN_DO);   // LOW  = rain detected
  int rainA = analogRead(RAIN_AO);    // 0-1023 (lower = wetter)

  // Convert analog to 0-100 % (0% = dry, 100% = very wet)
  int rainPercent = map(rainA, 1023, 0, 0, 100);

  // ── Read MQ135 ──────────────────────────────
  int gasA = analogRead(GAS_AO);       // 0-1023
  int gasD = digitalRead(GAS_DO);      // LOW = threshold exceeded

  int gasPercent = map(gasA, 0, 1023, 0, 100);

  // Determine air-quality label
  String airStatus;
  if      (gasPercent < GAS_CLEAN)    airStatus = "Clean   ";
  else if (gasPercent < GAS_MODERATE) airStatus = "Moderate";
  else                                 airStatus = "Danger! ";

  // ── LCD Display (alternating screens) ───────
  // Screen 1: Temperature & Humidity
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temp, 1);
  lcd.print((char)223);   // degree symbol
  lcd.print("C H:");
  lcd.print((int)hum);
  lcd.print("%   ");

  // Screen 1, row 2: Rain status
  lcd.setCursor(0, 1);
  lcd.print("Rain:");
  if (rainD == LOW) {
    lcd.print("YES ");
    lcd.print(rainPercent);
    lcd.print("%  ");
  } else {
    lcd.print("NO       ");
  }

  delay(3000);

  // Screen 2: Air Quality
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Air Quality:");
  lcd.setCursor(0, 1);
  lcd.print(airStatus);
  lcd.print(" ");
  lcd.print(gasPercent);
  lcd.print("%     ");

  delay(3000);
  lcd.clear();

  // ── Serial Monitor Output ───────────────────
  Serial.println("=============================");
  Serial.print("Temperature : "); Serial.print(temp);  Serial.println(" C");
  Serial.print("Humidity    : "); Serial.print(hum);   Serial.println(" %");
  Serial.print("Rain        : "); Serial.println(rainD == LOW ? "YES" : "NO");
  Serial.print("Rain Level  : "); Serial.print(rainPercent); Serial.println(" %");
  Serial.print("Gas Raw     : "); Serial.println(gasA);
  Serial.print("Gas Level   : "); Serial.print(gasPercent);  Serial.println(" %");
  Serial.print("Air Status  : "); Serial.println(airStatus);
  Serial.println("=============================\n");
}
