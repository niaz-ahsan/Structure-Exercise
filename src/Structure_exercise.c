/*
 ======================================================================================================
Problem Statement: Decode a 32 bit packet, extract respective bits & store them in an user defined var
 ======================================================================================================
 */

#include <stdio.h>
#include <stdint.h>

struct packet_data {
	uint32_t crc:2; 		// 2 bits
	uint32_t status:1;		// 1 bit
	uint32_t payload:12;	// 12 bits
	uint32_t bat:3;		// 3 bits
	uint32_t sensor:3;		// 3 bits
	uint32_t long_addr:8;	// 8 bits
	uint32_t short_addr:2;	// 2 bits
	uint32_t addr_mode:1;	// 1 bits
};

int extract_bit(uint32_t *data, uint8_t bit_start_position, uint8_t bit_end_position) {
	uint32_t mask = 4294967295;
	mask = ~(mask << ((bit_end_position - bit_start_position) + 1));

	uint32_t output = (*data >> bit_start_position) & mask;
	return output;
}

void print_packet(struct packet_data *ptr) {
	printf("crc = %d\n", ptr->crc);
	printf("status = %d\n", ptr->status);
	printf("payload = %d\n", ptr->payload);
	printf("bat = %d\n", ptr->bat);
	printf("sensor = %d\n", ptr->sensor);
	printf("long_addr = %d\n", ptr->long_addr);
	printf("short_addr = %d\n", ptr->short_addr);
	printf("addr_mode = %d\n", ptr->addr_mode);
}

int main(void) {
	uint32_t packet_value;
	struct packet_data packet;

	printf("Enter your 32 bit packet value: ");
	scanf("%d", &packet_value);

	uint8_t crc = (uint8_t) extract_bit(&packet_value, 0, 1);
	packet.crc = crc;

	uint8_t status = (uint8_t) extract_bit(&packet_value, 2, 2);
	packet.status = status;

	uint16_t payload = (uint16_t) extract_bit(&packet_value, 3, 14);
	packet.payload = payload;

	uint8_t bat = (uint8_t) extract_bit(&packet_value, 15, 17);
	packet.bat = bat;

	uint8_t sensor = (uint8_t) extract_bit(&packet_value, 18, 20);
	packet.sensor = sensor;

	uint8_t long_addr = (uint8_t) extract_bit(&packet_value, 21, 28);
	packet.long_addr = long_addr;

	uint8_t short_addr = (uint8_t) extract_bit(&packet_value, 29, 30);
	packet.short_addr = short_addr;

	uint8_t addr_mode = (uint8_t) extract_bit(&packet_value, 31, 31);
	packet.addr_mode = addr_mode;

	print_packet(&packet);

	printf("Size of decoded packet: %d bytes\n", sizeof(packet));
}
