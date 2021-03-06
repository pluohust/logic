#include "gates.h"
#include "arithmetic.h"
#include <stdio.h>

#include "components.h"
#include "ram.h"

void RAM(RAMComp* ram);

void initRAM(RAMComp* ram) {
	int i;
	ram->store = '0';
	ram->clock = '0';
	ram->address = '0';
	for (i = 0; i < 8; i++) ram->data[i] = '0';
	initDMux(&ram->dmux);
	for (i = 0; i < 2; i++) initRegister(&ram->reg[i]);
	initMux8(&ram->mux8);
	RAM(ram);
}

void RAM(RAMComp* ram) {
	int i, j;
	ram->dmux.store = ram->address;
	ram->dmux.data = ram->store;
	DMux(&ram->dmux);
	for (i = 0; i < 2; i++) {
		ram->reg[i].store = ram->dmux.out[1 - i];
		for (j = 0; j < 8; j++) ram->reg[i].data[j] = ram->data[j];
		ram->reg[i].clock = ram->clock;
		Register(&ram->reg[i]);
		for (j = 0; j < 8; j++) ram->mux8.data[i][j] = ram->reg[1 - i].out[j];
	}
	ram->mux8.store = ram->address;
	Mux8(&ram->mux8);
	for (i = 0; i < 8; i++) ram->out[i] = ram->mux8.out[i];
}

void RAM4(RAM4Comp* ram4);

void initRAM4(RAM4Comp* ram4) {
	int i;
	ram4->store = '0';
	ram4->clock = '0';
	for (i = 0; i < 2; i++) ram4->address[i] = '0';
	for (i = 0; i < 8; i++) ram4->data[i] = '0';
	initDMux(&ram4->dmux);
	for (i = 0; i < 2; i++) initRAM(&ram4->ram[i]);
	initMux8(&ram4->mux8);
	RAM4(ram4);
}

void RAM4(RAM4Comp* ram4) {
	int i, j;
	ram4->dmux.store = ram4->address[0];
	ram4->dmux.data = ram4->store;
	DMux(&ram4->dmux);
	for (i = 0; i < 2; i++) {
		ram4->ram[i].address = ram4->address[1];
		ram4->ram[i].store = ram4->dmux.out[1 - i];
		for (j = 0; j < 8; j++) ram4->ram[i].data[j] = ram4->data[j];
		ram4->ram[i].clock = ram4->clock;
		RAM(&ram4->ram[i]);
		for (j = 0; j < 8; j++) ram4->mux8.data[i][j] = ram4->ram[1 - i].out[j];
	}
	ram4->mux8.store = ram4->address[0];
	Mux8(&ram4->mux8);
	for (i = 0; i < 8; i++) ram4->out[i] = ram4->mux8.out[i];
}

void RAM8(RAM8Comp* ram8);

void initRAM8(RAM8Comp* ram8) {
	int i;
	ram8->store = '0';
	ram8->clock = '0';
	for (i = 0; i < 3; i++) ram8->address[i] = '0';
	for (i = 0; i < 8; i++) ram8->data[i] = '0';
	initDMux(&ram8->dmux);
	for (i = 0; i < 2; i++) initRAM4(&ram8->ram4[i]);
	initMux8(&ram8->mux8);
	RAM8(ram8);
}

void RAM8(RAM8Comp* ram8) {
	int i, j;
	ram8->dmux.store = ram8->address[0];
	ram8->dmux.data = ram8->store;
	DMux(&ram8->dmux);
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++) ram8->ram4[i].address[j] = ram8->address[j + 1];
		ram8->ram4[i].store = ram8->dmux.out[1 - i];
		for (j = 0; j < 8; j++) ram8->ram4[i].data[j] = ram8->data[j];
		ram8->ram4[i].clock = ram8->clock;
		RAM4(&ram8->ram4[i]);
		for (j = 0; j < 8; j++) ram8->mux8.data[i][j] = ram8->ram4[1 - i].out[j];
	}
	ram8->mux8.store = ram8->address[0];
	Mux8(&ram8->mux8);
	for (i = 0; i < 8; i++) ram8->out[i] = ram8->mux8.out[i];
}

void RAM16(RAM16Comp* ram16);

void initRAM16(RAM16Comp* ram16) {
	int i;
	ram16->store = '0';
	ram16->clock = '0';
	for (i = 0; i < 4; i++) ram16->address[i] = '0';
	for (i = 0; i < 8; i++) ram16->data[i] = '0';
	initDMux(&ram16->dmux);
	for (i = 0; i < 2; i++) initRAM8(&ram16->ram8[i]);
	initMux8(&ram16->mux8);
	RAM16(ram16);
}

void RAM16(RAM16Comp* ram16) {
	int i, j;
	ram16->dmux.store = ram16->address[0];
	ram16->dmux.data = ram16->store;
	DMux(&ram16->dmux);
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 3; j++) ram16->ram8[i].address[j] = ram16->address[j + 1];
		ram16->ram8[i].store = ram16->dmux.out[1 - i];
		for (j = 0; j < 8; j++) ram16->ram8[i].data[j] = ram16->data[j];
		ram16->ram8[i].clock = ram16->clock;
		RAM8(&ram16->ram8[i]);
		for (j = 0; j < 8; j++) ram16->mux8.data[i][j] = ram16->ram8[1 - i].out[j];
	}
	ram16->mux8.store = ram16->address[0];
	Mux8(&ram16->mux8);
	for (i = 0; i < 8; i++) ram16->out[i] = ram16->mux8.out[i];
}

void RAM32(RAM32Comp* ram32);

void initRAM32(RAM32Comp* ram32) {
	int i;
	ram32->store = '0';
	ram32->clock = '0';
	for (i = 0; i < 5; i++) ram32->address[i] = '0';
	for (i = 0; i < 8; i++) ram32->data[i] = '0';
	initDMux(&ram32->dmux);
	for (i = 0; i < 2; i++) initRAM16(&ram32->ram16[i]);
	initMux8(&ram32->mux8);
	RAM32(ram32);
}

void RAM32(RAM32Comp* ram32) {
	int i, j;
	ram32->dmux.store = ram32->address[0];
	ram32->dmux.data = ram32->store;
	DMux(&ram32->dmux);
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 4; j++) ram32->ram16[i].address[j] = ram32->address[j + 1];
		ram32->ram16[i].store = ram32->dmux.out[1 - i];
		for (j = 0; j < 8; j++) ram32->ram16[i].data[j] = ram32->data[j];
		ram32->ram16[i].clock = ram32->clock;
		RAM16(&ram32->ram16[i]);
		for (j = 0; j < 8; j++) ram32->mux8.data[i][j] = ram32->ram16[1 - i].out[j];
	}
	ram32->mux8.store = ram32->address[0];
	Mux8(&ram32->mux8);
	for (i = 0; i < 8; i++) ram32->out[i] = ram32->mux8.out[i];
}

void RAM64(RAM64Comp* ram64);

void initRAM64(RAM64Comp* ram64) {
	int i;
	ram64->store = '0';
	ram64->clock = '0';
	for (i = 0; i < 6; i++) ram64->address[i] = '0';
	for (i = 0; i < 8; i++) ram64->data[i] = '0';
	initDMux(&ram64->dmux);
	for (i = 0; i < 2; i++) initRAM32(&ram64->ram32[i]);
	initMux8(&ram64->mux8);
	RAM64(ram64);
}

void RAM64(RAM64Comp* ram64) {
	int i, j;
	ram64->dmux.store = ram64->address[0];
	ram64->dmux.data = ram64->store;
	DMux(&ram64->dmux);
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 5; j++) ram64->ram32[i].address[j] = ram64->address[j + 1];
		ram64->ram32[i].store = ram64->dmux.out[1 - i];
		for (j = 0; j < 8; j++) ram64->ram32[i].data[j] = ram64->data[j];
		ram64->ram32[i].clock = ram64->clock;
		RAM32(&ram64->ram32[i]);
		for (j = 0; j < 8; j++) ram64->mux8.data[i][j] = ram64->ram32[1 - i].out[j];
	}
	ram64->mux8.store = ram64->address[0];
	Mux8(&ram64->mux8);
	for (i = 0; i < 8; i++) ram64->out[i] = ram64->mux8.out[i];
}

void RAM128(RAM128Comp* ram128);

void initRAM128(RAM128Comp* ram128) {
	int i;
	ram128->store = '0';
	ram128->clock = '0';
	for (i = 0; i < 7; i++) ram128->address[i] = '0';
	for (i = 0; i < 8; i++) ram128->data[i] = '0';
	initDMux(&ram128->dmux);
	for (i = 0; i < 2; i++) initRAM64(&ram128->ram64[i]);
	initMux8(&ram128->mux8);
	RAM128(ram128);
}

void RAM128(RAM128Comp* ram128) {
	int i, j;
	ram128->dmux.store = ram128->address[0];
	ram128->dmux.data = ram128->store;
	DMux(&ram128->dmux);
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 6; j++) ram128->ram64[i].address[j] = ram128->address[j + 1];
		ram128->ram64[i].store = ram128->dmux.out[1 - i];
		for (j = 0; j < 8; j++) ram128->ram64[i].data[j] = ram128->data[j];
		ram128->ram64[i].clock = ram128->clock;
		RAM64(&ram128->ram64[i]);
		for (j = 0; j < 8; j++) ram128->mux8.data[i][j] = ram128->ram64[1 - i].out[j];
	}
	ram128->mux8.store = ram128->address[0];
	Mux8(&ram128->mux8);
	for (i = 0; i < 8; i++) ram128->out[i] = ram128->mux8.out[i];
}

void RAM256(RAM256Comp* ram256);

void initRAM256(RAM256Comp* ram256) {
	int i;
	ram256->store = '0';
	ram256->clock = '0';
	for (i = 0; i < 8; i++) ram256->address[i] = '0';
	for (i = 0; i < 8; i++) ram256->data[i] = '0';
	initDMux(&ram256->dmux);
	for (i = 0; i < 2; i++) initRAM128(&ram256->ram128[i]);
	initMux8(&ram256->mux8);
	RAM256(ram256);
}

void RAM256(RAM256Comp* ram256) {
	int i, j;
	ram256->dmux.store = ram256->address[0];
	ram256->dmux.data = ram256->store;
	DMux(&ram256->dmux);
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 7; j++) ram256->ram128[i].address[j] = ram256->address[j + 1];
		ram256->ram128[i].store = ram256->dmux.out[1 - i];
		for (j = 0; j < 8; j++) ram256->ram128[i].data[j] = ram256->data[j];
		ram256->ram128[i].clock = ram256->clock;
		RAM128(&ram256->ram128[i]);
		for (j = 0; j < 8; j++) ram256->mux8.data[i][j] = ram256->ram128[1 - i].out[j];
	}
	ram256->mux8.store = ram256->address[0];
	Mux8(&ram256->mux8);
	for (i = 0; i < 8; i++) ram256->out[i] = ram256->mux8.out[i];
}
