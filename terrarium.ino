#include <BH1750.h>

BH1750 sensor(0x23, Wire);

String light_level;
bool light_hit;

void setup()
{
  sensor.begin();
  sensor.set_sensor_mode(BH1750::forced_mode_high_res2);

  //Particle.variable("light_level", light_level);
  Particle.variable("light_hit", light_hit);

  Serial.begin();
}

void loop()
{
  sensor.make_forced_measurement();

  light_level = String::format("%f", sensor.get_light_level());
  
  if (std::stof((std::string)light_level) > 15.0f) {
    light_hit = true;
  } else {
    light_hit = false;
  }
  
  Serial.println("Light level: " + light_level);
  Serial.println("Light hit: " + String(light_hit));
  //Particle.publish("light_hit", String(light_hit));

  delay(1000); // Poll every second
}

