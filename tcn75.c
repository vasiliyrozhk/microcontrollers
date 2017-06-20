#define TCN_address 0x90
#define I2C_write_cmd 0x00
#define I2C_read_cmd 0x01
uint16_t TCN_T;
uint8_t  TCN_config;
uint16_t TCN_hysteresis;
uint16_t TCN_limitset;

void TCN_write_config(int8_t conf_data) {
			SoftI2CStart();
			SoftI2CWriteByte(TCN_address + I2C_write_cmd);
			SoftI2CWriteByte(0x01);
			SoftI2CWriteByte(conf_data);
			SoftI2CStop();
			            }
						
void TCN_write_hysteresis(int16_t hyst_data) {
	SoftI2CStart();
	SoftI2CWriteByte(TCN_address + I2C_write_cmd);
	SoftI2CWriteByte(0x02);
	SoftI2CWriteByte(hyst_data>>8);
	SoftI2CWriteByte(hyst_data);
	SoftI2CStop();
}

void TCN_write_limitset(int16_t ls_data) {
	SoftI2CStart();
	SoftI2CWriteByte(TCN_address + I2C_write_cmd);
	SoftI2CWriteByte(0x03);
	SoftI2CWriteByte(ls_data>>8);
	SoftI2CWriteByte(ls_data);
	SoftI2CStop();
}

void TCN_get_temp() {
			SoftI2CStart();
			SoftI2CWriteByte(TCN_address + I2C_write_cmd);
			SoftI2CWriteByte(0x00); //temperature register
			
			SoftI2CStart();
			SoftI2CWriteByte(TCN_address + I2C_read_cmd);
			TCN_T = (SoftI2CReadByte(1)<<8);
			TCN_T += SoftI2CReadByte(0);
			SoftI2CStop();
					}
					
void TCN_get_all() {

			SoftI2CStart();
			SoftI2CWriteByte(TCN_address + I2C_write_cmd);
			SoftI2CWriteByte(0x00); //temperature register
			
			SoftI2CStart();
			SoftI2CWriteByte(TCN_address + I2C_read_cmd);
			TCN_T = (SoftI2CReadByte(1)<<8);
			TCN_T = TCN_T + SoftI2CReadByte(0);
			SoftI2CStop();
			
_delay_ms(5);


SoftI2CStart();
SoftI2CWriteByte(TCN_address + I2C_write_cmd);
SoftI2CWriteByte(0x01); //config register

SoftI2CStart();
SoftI2CWriteByte(TCN_address + I2C_read_cmd);
TCN_config = SoftI2CReadByte(0);
SoftI2CStop();

_delay_ms(5);

			SoftI2CStart();
			SoftI2CWriteByte(TCN_address + I2C_write_cmd);
			SoftI2CWriteByte(0x02); //hysteresis register

			SoftI2CStart();
			SoftI2CWriteByte(TCN_address + I2C_read_cmd);
			TCN_hysteresis = SoftI2CReadByte(1)<<8;
			TCN_hysteresis += SoftI2CReadByte(0);
			SoftI2CStop();

_delay_ms(5);

SoftI2CStart();
SoftI2CWriteByte(TCN_address + I2C_write_cmd);
SoftI2CWriteByte(0x03); //limitset register

SoftI2CStart();
SoftI2CWriteByte(TCN_address + I2C_read_cmd);
TCN_limitset = SoftI2CReadByte(1)<<8;
TCN_limitset += SoftI2CReadByte(0);
SoftI2CStop();


}